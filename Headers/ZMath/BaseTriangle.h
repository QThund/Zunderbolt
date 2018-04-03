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

#ifndef __BASETRIANGLE__
#define __BASETRIANGLE__

#include "ZCommon/Assertions.h"
#include "ZCommon/DataTypes/SFloat.h"
#include "ZCommon/DataTypes/SVF32.h"
#include "ZMath/Vector2.h"
#include "ZMath/Vector3.h"
#include "ZMath/Vector4.h"



namespace z
{

/// <summary>
/// Class which represents a triangle in the space.
/// </summary>
/// <typeparam name="VectorT">Allowed types: BaseVector2, BaseVector3, BaseVector4, Vector2, Vector3, Vector4.</typeparam>
template <class VectorT>
class BaseTriangle
{

    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor.
    /// </summary>
    BaseTriangle() : A(SFloat::_0), B(SFloat::_0), C(SFloat::_0)
    {
    }

    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="triangle">[IN] The triangle from which we want to create a copy in the resident triangle.</param>
    BaseTriangle(const BaseTriangle &triangle) : A(triangle.A), B(triangle.B), C(triangle.C)
    {
    }

    /// <summary>
    /// Constructor from three vectors.
    /// </summary>
    /// <param name="vA">[IN] Vector to define vertex A.</param>
    /// <param name="vB">[IN] Vector to define vertex B.</param>
    /// <param name="vC">[IN] Vector to define vertex C.</param>
    BaseTriangle(const VectorT &vA, const VectorT &vB, const VectorT &vC) :
                            A(vA), B(vB), C(vC)
    {
    }

    /// <summary>
    /// Constructor from a pointer to floating point values to define each vertex.
    /// </summary>
    /// <remarks>
    /// Pointer must have two, three or four values depending on VectorT.
    /// </remarks>
    /// <param name="arValuesA">[IN] Array of values that define the vertex A. If the pointer is null, the behavior  
    /// is undefined.</param>
    /// <param name="arValuesB">[IN] Array of values that define the vertex B. If the pointer is null, the behavior  
    /// is undefined.</param>
    /// <param name="arValuesC">[IN] Array of values that define the vertex C. If the pointer is null, the behavior 
    /// is undefined.</param>
    BaseTriangle(const float_z* arValuesA, const float_z* arValuesB, const float_z* arValuesC)
    {
        // Checkout to ensure pointers are not null.
        Z_ASSERT_ERROR( (arValuesA != null_z) && (arValuesB != null_z) && (arValuesC != null_z) , "Input values must not be null");

        A = VectorT(arValuesA);
        B = VectorT(arValuesB);
        C = VectorT(arValuesC);
    }

    /// <summary>
    /// Constructor from three 4x32 packed floating point values to define each vertex.
    /// </summary>
    /// <param name="valueA">[IN] 4x32 packed value which defines vertex A.</param>
    /// <param name="valueB">[IN] 4x32 packed value which defines vertex B.</param>
    /// <param name="valueC">[IN] 4x32 packed value which defines vertex C.</param>
    BaseTriangle(const vf32_z valueA, const vf32_z valueB, const vf32_z valueC) :
                             A(valueA), B(valueB), C(valueC)
    {
    }


    // METHODS
    // ---------------
public:

    /// <summary>
    /// Equality operator. Compares two triangles.
    /// </summary>
    /// <param name="triangle">[IN] Triangle with which to compare.</param>
    /// <returns>
    /// True if triangles are the same, false otherwise.
    /// </returns>
    bool operator==(const BaseTriangle<VectorT> &triangle) const
    {
        return ( this->A == triangle.A && this->B == triangle.B && this->C == triangle.C );
    }

    /// <summary>
    /// Inequality operator. Compares two triangles.
    /// </summary>
    /// <param name="triangle">[IN] Triangle with which to compare.</param>
    /// <returns>
    /// True if triangles are not the same, false otherwise.
    /// </returns>
    bool operator!=(const BaseTriangle<VectorT> &triangle) const
    {
        return !(*this == triangle);
    }


    // ATTRIBUTES
    // ---------------
public:

    /// <summary>
    /// Vector which represents a vextex of the triangle.
    /// </summary>
    VectorT A;

    /// <summary>
    /// Vector which represents a vextex of the triangle.
    /// </summary>
    VectorT B;

    /// <summary>
    /// Vector which represents a vextex of the triangle.
    /// </summary>
    VectorT C;

};


// SPECIALIZATION EXPORTATIONS
// -----------------------------
#ifdef Z_MATH_TEMPLATE_SPECIALIZATION_SYMBOLS

template class Z_LAYER_MATH_SYMBOLS BaseTriangle<Vector2>;
template class Z_LAYER_MATH_SYMBOLS BaseTriangle<Vector3>;
template class Z_LAYER_MATH_SYMBOLS BaseTriangle<Vector4>;

#endif // Z_MATH_TEMPLATE_SPECIALIZATION_SYMBOLS

} // namespace z


#endif // __BASETRIANGLE__
