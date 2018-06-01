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

#ifndef __BASELINESEGMENT__
#define __BASELINESEGMENT__

#include "ZCommon/DataTypes/SFloat.h"
#include "ZCommon/DataTypes/SVF32.h"
#include "ZMath/Vector2.h"
#include "ZMath/Vector3.h"
#include "ZMath/Vector4.h"



namespace z
{

/// <summary>
/// Class which represents a segment of straight line in the space, defined by the points at both ends.
/// </summary>
/// <remarks>
/// These points may be expressed as 2D or 3D points or vectors, depending on the template parameter,
/// which may be 2D vector, 3D vector or 4D vector.
/// </remarks>
/// <typeparam name="VectorT">Allowed types: BaseVector2, BaseVector3, BaseVector4, Vector2, Vector3, Vector4.</typeparam>
template <class VectorT>
class BaseLineSegment
{

    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor.
    /// </summary>
    BaseLineSegment() : A(SFloat::_0), B(SFloat::_0) { }

    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="segment">[IN] The segment from which we want to create a copy in the resident segment.</param>
    BaseLineSegment(const BaseLineSegment &segment) : A(segment.A), B(segment.B)
    {
    }

    /// <summary>
    /// Constructor from two vectors.
    /// </summary>
    /// <param name="vA">[IN] Vector to define end A.</param>
    /// <param name="vB">[IN] Vector to define end B.</param>
    BaseLineSegment(const VectorT &vA, const VectorT &vB) : A(vA), B(vB)  { }


    // METHODS
    // ---------------
public:

    /// <summary>
    /// Equality operator. Compares two line segments.
    /// </summary>
    /// <param name="segment">[IN] Line segment with which to compare.</param>
    /// <returns>
    /// True if line segments are the same, false otherwise.
    /// </returns>
    bool operator==(const BaseLineSegment<VectorT> &segment) const
    {
        return ( this->A == segment.A && this->B == segment.B );
    }

    /// <summary>
    /// Inequality operator. Compares two line segments.
    /// </summary>
    /// <param name="segment">[IN] Line segment with which to compare.</param>
    /// <returns>
    /// True if line segments are not the same, false otherwise.
    /// </returns>
    bool operator!=(const BaseLineSegment<VectorT> &segment) const
    {
        return !(*this == segment);
    }


    // ATTRIBUTES
    // ---------------
public:

    /// <summary>
    /// Vector which represents a end of the segment.
    /// </summary>
    VectorT A;

    /// <summary>
    /// Vector which represents the other end of the segment.
    /// </summary>
    VectorT B;
};


// SPECIALIZATION EXPORTATIONS
// -----------------------------
#ifdef Z_MATH_MODULE_TEMPLATE_SPECIALIZATION_SYMBOLS

template class Z_MATH_MODULE_SYMBOLS BaseLineSegment<Vector2>;
template class Z_MATH_MODULE_SYMBOLS BaseLineSegment<Vector3>;
template class Z_MATH_MODULE_SYMBOLS BaseLineSegment<Vector4>;

#endif // Z_MATH_MODULE_TEMPLATE_SPECIALIZATION_SYMBOLS

} // namespace z


#endif // __BASELINESEGMENT__
