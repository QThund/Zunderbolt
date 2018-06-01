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

#ifndef __TRIANGLE__
#define __TRIANGLE__

#include "BaseTriangle.h"

#include "ZCommon/Assertions.h"
#include "ZMath/MathDefinitions.h"
#include "ZMath/Vector2.h"
#include "ZMath/Vector3.h"
#include "ZMath/Vector4.h"



namespace z
{

/// <summary>
/// Represents a triangle in the space.
/// </summary>
/// <remarks>
/// The triangle may be represented in either 2D or 3D (using either points or vectors), depending on the parameter of the template, which may be
/// 2D vector, 3D vector or 4D vector.
/// </remarks>
/// <typeparam name="VectorT">Allowed types: Vector2, Vector3, Vector4.</typeparam>
template <class VectorT>
class Triangle : public BaseTriangle<VectorT>
{

    // BASE CLASS USINGS
    // -------------------
public:

    using BaseTriangle<VectorT>::A;
    using BaseTriangle<VectorT>::B;
    using BaseTriangle<VectorT>::C;


    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor.
    /// </summary>
    Triangle()
    {
    }

    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="triangle">[IN] The triangle from which we want to create a copy in the resident triangle.</param>
    Triangle(const Triangle<VectorT> &triangle) : BaseTriangle<VectorT>(triangle)
    {
    }

    /// <summary>
    /// Base type constructor.
    /// </summary>
    /// <param name="triangle">[IN] The triangle in which we want resident triangle to be based.</param>
    Triangle(const BaseTriangle<VectorT> &triangle) : BaseTriangle<VectorT>(triangle)
    {
    }

    /// <summary>
    /// Constructor from three vectors, one for each vertex.
    /// </summary>
    /// <param name="vA">[IN] Vector to define vertex A.</param>
    /// <param name="vB">[IN] Vector to define vertex B.</param>
    /// <param name="vC">[IN] Vector to define vertex C.</param>
    Triangle(const VectorT &vA, const VectorT &vB, const VectorT &vC) : BaseTriangle<VectorT>(vA, vB, vC)
    {
    }

    /// <summary>
    /// Constructor from three pointer-to-float type, one for each vertex.
    /// </summary>
    /// <param name="arValuesA">[IN] Array of components of the vertex A. If it is null, the behavior is undefined.</param>
    /// <param name="arValuesB">[IN] Array of components of the vertex B. If it is null, the behavior is undefined.</param>
    /// <param name="arValuesC">[IN] Array of components of the vertex C. If it is null, the behavior is undefined.</param>
    Triangle(const float_z* arValuesA, const float_z* arValuesB, const float_z* arValuesC) :
                         BaseTriangle<VectorT>(arValuesA, arValuesB, arValuesC)
    {
    }

    /// <summary>
    /// Constructor from three 4x32 packed floating point values, one for each vertex.
    /// </summary>
    /// <param name="valueA">[IN] 4x32 packed value which defines vertex A.</param>
    /// <param name="valueB">[IN] 4x32 packed value which defines vertex B.</param>
    /// <param name="valueC">[IN] 4x32 packed value which defines vertex C.</param>
    Triangle(const vf32_z valueA, const vf32_z valueB, const vf32_z valueC) : BaseTriangle<VectorT>(valueA, valueB, valueC)
    {
    }


    // METHODS
    // ---------------
public:

    /// <summary>
    /// Assignation operator.<br/>
    /// Assigns the provided triangle to the resident triangle.
    /// </summary>
    /// <param name="triangle">[IN] Triangle that will be assigned to current triangle.</param>
    /// <returns>
    /// The assigned value.
    /// </returns>
    Triangle<VectorT>& operator=(const BaseTriangle<VectorT> &triangle)
    {
        BaseTriangle<VectorT>::operator=(triangle);
        return *this;
    }

    /// <summary>
    /// Calculates the surface of the triangle.
    /// </summary>
    /// <remarks>
    /// The points of the triangle should not coincide with each other in order to obtain a valid result.
    /// When using 4D vectors, it's not guaranteed that the result will be what expected if the W component has a different 
    /// value for some of the implied points.
    /// </remarks>
    /// <returns>
    /// The surface of the triangle in a float point type.
    /// </returns>
    float_z GetSurface() const
    {
        // The triangle's points should not coincide, otherwise it would not exist
        Z_ASSERT_WARNING( !(this->A == this->B && this->A == this->C), "Triangle's points should not coincide, otherwise it would not exist" );

        VectorT u = B - A;
        VectorT v = C - A;

        float_z fSqrLengthU = u.GetSquaredLength();
        float_z fSqrLengthV = v.GetSquaredLength();

        float_z fDotProduct = u.DotProduct(v);

        return sqrt_z(fSqrLengthU * fSqrLengthV - (fDotProduct * fDotProduct)) * SFloat::_0_5;
    }

    /// <summary>
    /// Calculates the angle formed by edges AB and AC.
    /// </summary>
    /// <remarks>
    /// The points of the triangle should not coincide with each other in order to obtain a valid result.
    /// When using 4D vectors, it's not guaranteed that the result will be what expected if the W component has a different 
    /// value for some of the implied points.
    /// </remarks>
    /// <returns>
    /// Returns the angle in a float point type.
    /// </returns>
    float_z GetAngleA() const
    {
        // The triangle's points should not coincide, otherwise it would not exist
        Z_ASSERT_WARNING( !(this->A == this->B && this->A == this->C), "Triangle's points should not coincide, otherwise it would not exist" );

        VectorT u = B - A;
        VectorT v = C - A;

        return u.AngleBetween(v);
    }

    /// <summary>
    /// Calculates the angle formed by edges BA and BC.
    /// </summary>
    /// <remarks>
    /// The points of the triangle should not coincide with each other in order to obtain a valid result.
    /// When using 4D vectors, it's not guaranteed that the result will be what expected if the W component has a different 
    /// value for some of the implied points.
    /// </remarks>
    /// <returns>
    /// Returns the angle in a float point type.
    /// </returns>
    float_z GetAngleB() const
    {
        // The triangle's points should not coincide, otherwise it would not exist
        Z_ASSERT_WARNING( !(this->A == this->B && this->A == this->C), "Triangle's points should not coincide, otherwise it would not exist" );

        VectorT u = A - B;
        VectorT v = C - B;

        return u.AngleBetween(v);
    }

    /// <summary>
    /// Calculates the angle formed by edges CB and CA.
    /// </summary>
    /// <remarks>
    /// The points of the triangle should not coincide with each other in order to obtain a valid result.
    /// When using 4D vectors, it's not guaranteed that the result will be what expected if the W component has a different 
    /// value for some of the implied points.
    /// </remarks>
    /// <returns>
    /// Returns the angle in a float point type.
    /// </returns>
    float_z GetAngleC() const
    {
        // The triangle's points should not coincide, otherwise it would not exist
        Z_ASSERT_WARNING( !(this->A == this->B && this->A == this->C), "Triangle's points should not coincide, otherwise it would not exist" );

        const VectorT u = A - C;
        const VectorT v = B - C;

        return u.AngleBetween(v);
    }

    /// <summary>
    /// Calculates the incenter of the triangle.
    /// </summary>
    /// <remarks>
    /// The incenter is the center of the incircle or inscribed circle of a triangle, which is 
    /// the largest circle contained in it; it touches (is tangent to) the three sides.<br/>
    /// The points of the triangle should not coincide with each other in order to obtain a valid result.
    /// </remarks>
    /// <returns>
    /// The incenter.
    /// </returns>
    VectorT GetIncenter() const
    {
        // The triangle's points should not coincide, otherwise it would not exist
        Z_ASSERT_WARNING( !(this->A == this->B && this->A == this->C), "Triangle's points should not coincide, otherwise it would not exist" );

        const VectorT vtSideA = C - B;
        const VectorT vtSideB = A - C;
        const VectorT vtSideC = B - A;

        const float_z fLengthA = vtSideA.GetLength();
        const float_z fLengthB = vtSideB.GetLength();
        const float_z fLengthC = vtSideC.GetLength();

        const float_z fP = SFloat::_1 / (fLengthA + fLengthB + fLengthC);

        return (fLengthA * A + fLengthB * B + fLengthC * C) * fP;
    }

    /// <summary>
    /// Calculates the centroid of the triangle.
    /// </summary>
    /// <remarks>
    /// The centroid or geomatric center is the arithmetic mean ("average") 
    /// position of all the points in the triangle. The centroid will always coincide with the first third of the segment
    /// that starts at the middle of an edge and ends in the opposite vertex.<br/>
    /// The points of the triangle should not coincide with each other in order to obtain a valid result.
    /// </remarks>
    /// <returns>
    /// The centroid.
    /// </returns>
    VectorT GetCentroid() const
    {
        // The triangle's points should not coincide, otherwise it would not exist
        Z_ASSERT_WARNING( !(this->A == this->B && this->A == this->C), "Triangle's points should not coincide, otherwise it would not exist" );

        return (A + B + C) / SFloat::_3;
    }

    /// <summary>
    /// Converts triangle into a string.
    /// </summary>
    /// <remarks>
    /// The format of the string is:<br/>
    /// "T(a($A),b($B),c($C))"<br/>
    /// Where "$" means "string representation of".
    /// </summary>
    /// <returns>
    /// The string in the specified format.
    /// </returns>
    string_z ToString() const
    {
        return string_z("T(a(") + A.ToString() + Z_L("),b(") + B.ToString() + Z_L("),c(") + C.ToString() + Z_L("))");
    }
};


// SPECIALIZATION EXPORTATIONS
// -----------------------------
#ifdef Z_MATH_MODULE_TEMPLATE_SPECIALIZATION_SYMBOLS

template class Z_MATH_MODULE_SYMBOLS Triangle<Vector2>;
template class Z_MATH_MODULE_SYMBOLS Triangle<Vector3>;
template class Z_MATH_MODULE_SYMBOLS Triangle<Vector4>;

#endif // Z_MATH_MODULE_TEMPLATE_SPECIALIZATION_SYMBOLS

} // namespace z


#endif // __Triangle__
