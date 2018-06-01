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

#ifndef __BASEHEXAHEDRON__
#define __BASEHEXAHEDRON__

#include "ZCommon/DataTypes/SFloat.h"
#include "ZCommon/DataTypes/SVF32.h"
#include "ZMath/Vector3.h"
#include "ZMath/Vector4.h"



namespace z
{

/// <summary>
/// Class which represents a hexahedron in the space. 
/// </summary>
/// <remarks>
/// The hexahedron is defined by its eight vertices.<br/>
/// It is supossed that ABCD defines a face of the hexahedron (eventually the top face) and
/// EFGH defines the opposite face (eventually the bottom one).<br/>
/// It is developer's reponsibility to keep the fourth component of all the points (when using 4D vectors) set to the same value.<br/>
/// </remarks>
/// <typeparam name="VectorT">Allowed types: BaseVector3, BaseVector4, Vector3, Vector4.</typeparam>
template <class VectorT>
class BaseHexahedron
{

    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor.
    /// </summary>
    BaseHexahedron() : A(SFloat::_0), B(SFloat::_0), C(SFloat::_0), D(SFloat::_0),
                       E(SFloat::_0), F(SFloat::_0), G(SFloat::_0), H(SFloat::_0)
    {
    }

    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="hexahedron">[IN] The hexahedron from which we want to create a copy in the resident hexahedron.</param>
    BaseHexahedron(const BaseHexahedron &hexahedron) : A(hexahedron.A), B(hexahedron.B), C(hexahedron.C), D(hexahedron.D),
                                                       E(hexahedron.E), F(hexahedron.F), G(hexahedron.G), H(hexahedron.H)
    {
    }

    /// <summary>
    /// Constructor from eight vectors, one for each vertex.
    /// </summary>
    /// <param name="vA">[IN] Vector to define vertex A.</param>
    /// <param name="vB">[IN] Vector to define vertex B.</param>
    /// <param name="vC">[IN] Vector to define vertex C.</param>
    /// <param name="vD">[IN] Vector to define vertex D.</param>
    /// <param name="vE">[IN] Vector to define vertex E.</param>
    /// <param name="vF">[IN] Vector to define vertex F.</param>
    /// <param name="vG">[IN] Vector to define vertex G.</param>
    /// <param name="vH">[IN] Vector to define vertex H.</param>
    BaseHexahedron(const VectorT &vA, const VectorT &vB, const VectorT &vC, const VectorT &vD,
                   const VectorT &vE, const VectorT &vF, const VectorT &vG, const VectorT &vH) :
                                A(vA), B(vB), C(vC), D(vD), E(vE), F(vF), G(vG), H(vH)
    {
    }

    /// <summary>
    /// Constructor from two vectors which defines two opposite vertices, with no common faces between them
    /// (the ends of any inner diagonals).
    /// </summary>
    /// <remarks>
    /// Top face is compound of A, B, C and D points whilst bottom face is compound of E, F, G and H points. A point shares
    /// edge with B, D and E points whereas G point shares edge with C, F and H points.<br/>
    /// When using 4D vectors, the W component of the top-face's points will equal the A point's and the W component of the 
    /// bottom-face's points will equal the G point's.
    /// </remarks>
    /// <param name="vA">[IN] Vector which defines one vertex of a inner diagonal (it will be used to initialize A).</param>
    /// <param name="vG">[IN] Vector which defines the other vertex of the inner diagonal (it will be used to initialize G).</param>
    BaseHexahedron(const VectorT &vA, const VectorT &vG)
    {
        //    A --- D
        //   /|    /|
        //  B --- C |
        //  | E --| F
        //  |/    |/
        //  H --- G

        A = B = C = D = vA;
        E = F = G = H = vG;

        B.z = C.z = vG.z;
        C.x = D.x = vG.x;
        E.x = H.x = vA.x;
        E.z = F.z = vA.z;
    }

    /// <summary>
    /// Constructor from a vector which defines the gravity center of the box and three floating
    /// points values which defines its height (Y), width (X) and depth (Z).
    /// </summary>
    /// <remarks>
    /// It's supossed that all edges are parallel to one of the axis.<br/>
    /// When using 4D vectors, the W component of all the points will equal the central point's.
    /// </remarks>
    /// <param name="vCenter">[IN] Center point of the box.</param>
    /// <param name="fLengthX">[IN] Length of an edge parallel to X axis (width).</param>
    /// <param name="fLengthY">[IN] Length of an edge parallel to Y axis (height).</param>
    /// <param name="fLengthZ">[IN] Length of an edge parallel to Z axis (depth).</param>
    BaseHexahedron(const VectorT &vCenter, const float_z fLengthX, const float_z fLengthY, const float_z fLengthZ)
    {
        // Ensures that all vectors/points are in same coordinates format.
        A = vCenter;

        A.x -= fLengthX*SFloat::_0_5;
        A.y += fLengthY*SFloat::_0_5;
        A.z += fLengthZ*SFloat::_0_5;

        B = A;
        B.z -= fLengthZ;

        C = B;
        C.x += fLengthX;

        D = C;
        D.z = A.z;

        E = A;
        E.y -= fLengthY;

        F = D;
        F.y = E.y;

        G = C;
        G.y = E.y;

        H = B;
        H.y = E.y;
    }

    // METHODS
    // ---------------
public:

    /// <summary>
    /// Equality operator. Compares two hexahedrons.
    /// </summary>
    /// <param name="hexahedron">[IN] Hexahedron with which to compare.</param>
    /// <returns>
    /// True if hexahedrons are the same, false otherwise.
    /// </returns>
    bool operator==(const BaseHexahedron<VectorT> &hexahedron) const
    {
        return ( this->A == hexahedron.A && this->B == hexahedron.B && this->C == hexahedron.C && this->D == hexahedron.D &&
                 this->E == hexahedron.E && this->F == hexahedron.F && this->G == hexahedron.G && this->H == hexahedron.H);
    }

    /// <summary>
    /// Inequality operator. Compares two hexahedrons.
    /// </summary>
    /// <param name="hexahedron">[IN] Hexahedron with which to compare.</param>
    /// <returns>
    /// True if hexahedrons are not the same, false otherwise.
    /// </returns>
    bool operator!=(const BaseHexahedron<VectorT> &hexahedron) const
    {
        return !(*this == hexahedron);
    }

    // ATTRIBUTES
    // ---------------
public:

    /// <summary>
    /// Vector which represents a vextex of the box.
    /// </summary>
    VectorT A;

    /// <summary>
    /// Vector which represents a vextex of the box.
    /// </summary>
    VectorT B;

    /// <summary>
    /// Vector which represents a vextex of the box.
    /// </summary>
    VectorT C;

    /// <summary>
    /// Vector which represents a vextex of the box.
    /// </summary>
    VectorT D;

    /// <summary>
    /// Vector which represents a vextex of the box.
    /// </summary>
    VectorT E;

    /// <summary>
    /// Vector which represents a vextex of the box.
    /// </summary>
    VectorT F;

    /// <summary>
    /// Vector which represents a vextex of the box.
    /// </summary>
    VectorT G;

    /// <summary>
    /// Vector which represents a vextex of the box.
    /// </summary>
    VectorT H;

};


// SPECIALIZATION EXPORTATIONS
// -----------------------------
#ifdef Z_MATH_MODULE_TEMPLATE_SPECIALIZATION_SYMBOLS

template class Z_MATH_MODULE_SYMBOLS BaseHexahedron<Vector3>;
template class Z_MATH_MODULE_SYMBOLS BaseHexahedron<Vector4>;

#endif // Z_MATH_MODULE_TEMPLATE_SPECIALIZATION_SYMBOLS

} // namespace z


#endif // __BASEHEXAHEDRON__
