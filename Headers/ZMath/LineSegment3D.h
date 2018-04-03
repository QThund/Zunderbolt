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

#ifndef __LINESEGMENT3D__
#define __LINESEGMENT3D__

#include <algorithm>
#include "BaseLineSegment.h"
#include "LineSegment.h"
#include "Plane.h"
#include "ESpaceRelation.h"
#include "BaseOrb.h"
#include "BaseTriangle.h"
#include "BaseHexahedron.h"
#include "ZMath/Quaternion.h"
#include "DualQuaternion.h"
#include "SPoint.h"
#include "TransformationMatrix.h"
#include "TranslationMatrix.h"
#include "SpaceConversionMatrix.h"
#include "RotationMatrix3x3.h"
#include "ScalingMatrix3x3.h"
#include "ZMath/Vector3.h"
#include "ZMath/Vector4.h"



namespace z
{

/// <summary>
/// Class which represents a chunk (segment) of straight line in 3D space, defined by two endpoints A and B.
/// </summary>
/// <remarks>
/// These points may be expressed as 3D points or vectors, depending on the template parameter,
/// which may be 3D vector or 4D vector.<br/>
/// Please note there's really no "source" and "end" points implicit, that is, it's not an oriented segment.
/// </remarks>
/// <typeparam name="VectorT">Allowed types: Vector3, Vector4.</typeparam>
template <class VectorT>
class LineSegment3D : public LineSegment<VectorT>
{
    // BASE TYPE USINGS
    // ---------------
public:

    using LineSegment<VectorT>::Intersection;
    using LineSegment<VectorT>::IntersectionPoint;
    using LineSegment<VectorT>::MinDistance;


     // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor.
    /// </summary>
    LineSegment3D()
    {
    }

    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="segment">[IN] Line segment from which we want to create a copy in the resident segment.</param>
    LineSegment3D(const LineSegment3D &segment) : LineSegment<VectorT>(segment.A, segment.B)
    {
    }

    /// <summary>
    /// Base type constructor.
    /// </summary>
    /// <param name="segment">[IN] Line segment in which we want resident segment to be based.</param>
    LineSegment3D(const BaseLineSegment<VectorT> &segment) : LineSegment<VectorT>(segment.A, segment.B)
    {
    }

    /// <summary>
    /// Constructor from two vectors.
    /// </summary>
    /// <param name="vA">[IN] Vector to define endpoint A.</param>
    /// <param name="vB">[IN] Vector to define endpoint B.</param>
    LineSegment3D(const VectorT &vA, const VectorT &vB) : LineSegment<VectorT>(vA,vB)
    {
    }


    // PROPERTIES
    // ---------------
public:

    /// <summary>
    /// Unit segment lying on positive X axis (it's length equals 1).
    /// </summary>
    /// <returns>
    /// A 1-length line segment.
    /// </returns>
    static const LineSegment3D<VectorT>& GetUnitLine()
    {
        static const LineSegment3D<VectorT> UNITLINE(VectorT::GetNullVector(), VectorT::GetUnitVectorX());
        return UNITLINE;
    }

    /// <summary>
    /// Zero segment lying in the coordinates center whose endpoints both equals (0, 0, 0) and it's length equals 0.
    /// </summary>
    /// <returns>
    /// A 0-length line segment.
    /// </returns>
    static const LineSegment3D<VectorT>& GetLineZero()
    {
        static const LineSegment3D<VectorT> LINEZERO(VectorT::GetNullVector(), VectorT::GetNullVector());
        return LINEZERO;
    }


    // METHODS
    // ---------------
public:

    /// <summary>
    /// Assignation operator. Assigns the provided line segment to the resident line segment.
    /// </summary>
    /// <param name="segment">[IN] The line segment to be assigned.</param>
    /// <returns>
    /// A reference to the modified line segment.
    /// </returns>
    LineSegment3D& operator=(const BaseLineSegment<VectorT> &segment)
    {
        BaseLineSegment<VectorT>::operator=(segment);
        return *this;
    }

    /// <summary>
    /// Checks if the line segment intersects with the provided plane.
    /// </summary>
    /// <remarks>
    /// Since a plane divides space into two sides (positive and negative), we can check how the end points of
    /// the line segment satisfies the plane equation.<br/>
    /// Being the plane equation:<br/><br/>
    /// \f$ ax + by + cz + d = 0 \f$,<br/><br/>
    /// and the end points of the line segment \f$ A(A_x, A_y, A_z)\f$, \f$ B(B_x, B_y, B_z)\f$,
    /// we have to check the value of:<br/><br/>
    /// (1) \f$ a\cdot A_x + b\cdot A_y + c\cdot A_z + d \f$
    /// <br/>
    /// (2) \f$ a\cdot B_x + b\cdot B_y + c\cdot B_z + d \f$
    /// <br/><br/>
    /// If (1) = 0 or (2) = 0, then the line segment intersects the plane (one of the end points lies on plane).<br/>
    /// If the sign of (1) and (2) are different, each end point is in a different side of the space
    /// divided by the plane, and then the line segment intersects the plane.<br/>
    /// If (1) and (2) have the same sign, then they are in the same side of the space divided by the plane,
    /// and the line segment does not intersect with the plane.<br/>
    /// If one end point of the line segment lies on the plane, we consider there is an intersection.
    /// </remarks>
    /// <param name="plane">[IN] The plane we want check if intersects with resident line segment. If the plane is null,
    /// the behavior is undefined.</param>
    /// <returns>
    /// A boolean value that indicates whether the segment and the plane intersect or not.<br/>
    /// <br/>
    /// <b>True</b><br/>
    /// The segment and the plane intersect, including the following cases:
    /// - The endpoints are in different sides of the space divided by the plane.
    /// - The segment is contained in the plane.
    /// - Only one endpoint belongs to the plane.
    ///
    /// <b>False</b><br/>
    /// The line segment does not intersect with the plane.
    /// </returns>
    bool Intersection(const BasePlane &plane) const
    {
        // The length of the segment should be greater than zero
        Z_ASSERT_WARNING(this->A != this->B, "The length of the segment should be greater than zero");

        // The plane shouldn't be null
        Z_ASSERT_WARNING( SFloat::IsNotZero(plane.a) || SFloat::IsNotZero(plane.b) || SFloat::IsNotZero(plane.c), "The input plane shouldn't be null" );

        const float_z &DIST_A = plane.a * this->A.x + plane.b * this->A.y + plane.c * this->A.z + plane.d;

        if (SFloat::IsZero(DIST_A))
            return true;

        const float_z &DIST_B = plane.a * this->B.x + plane.b * this->B.y + plane.c * this->B.z + plane.d;

        if (SFloat::IsZero(DIST_B))
            return true;

        return SFloat::IsNegative(DIST_A * DIST_B);
    }

    /// <summary>
    /// Checks if the line segment intersects with the provided triangle.
    /// </summary>
    /// <param name="triangle">[IN] The triangle we want check if intersects with resident line segment. If any of its vertices 
    /// coincide, the behavior is undefined.</param>
    /// <returns>
    /// A boolean value that indicates whether the segment and the triangle intersect or not.<br/>
    /// <br/>
    /// <b>True</b><br/>
    /// The segment and the triangle intersect, including the following cases:
    /// - The segment intersects with one or two edges of the triangle.
    /// - The segment intersects with a vertex of the triangle.
    /// - Only one endpoint is inside of the triangle (not intersecting with any edge).
    /// - The segment intersects with the interior (the face) of the triangle (not intersecting with any edge and not being contained).
    /// - The segment is completely contained in the triangle.
    /// - An endpoint of the segment is contained in an edge of the triangle, even if the other endpoint is inside of the triangle.
    /// - The segment is contained in an edge of the triangle.
    /// - The segment contains an edge of the triangle.
    /// - One or both endpoints coincide with the vertices of the triangle.
    /// 
    /// <b>False</b><br/>
    /// The line segment does not intersect with the triangle.
    /// </returns>
    bool Intersection(const BaseTriangle<VectorT> &triangle) const
    {
        // The length of the segment should be greater than zero
        Z_ASSERT_WARNING(this->A != this->B, "The length of the segment should be greater than zero");

        // Vertices of the triangle should not coincide
        Z_ASSERT_WARNING(triangle.A != triangle.B && triangle.B != triangle.C && triangle.C != triangle.A, "Vertices of the triangle should not coincide");

        // Calculates if segment intersects with the plane defined by the triangle.

        // Plane equation
        Plane auxP(triangle.A, triangle.B, triangle.C);

        // Line Segment don't intersects the triangle plane.
        if (!this->Intersection(auxP))
            return false;

        // If both end points satisfy plane equation, the line segment lies on plane
        const float_z &DOT1 = auxP.a * this->B.x + auxP.b * this->B.y + auxP.c * this->B.z + auxP.d;
        const float_z &DOT2 = auxP.a * this->A.x + auxP.b * this->A.y + auxP.c * this->A.z + auxP.d;

        if (SFloat::IsZero(DOT1) && SFloat::IsZero(DOT2))
        {
            // Both triangle and line segment are coplanars. If the line segment
            // intersects one of the edges of the triangle, then the line segment intersects the triangle.
            if (this->LineSegment<VectorT>::Intersection(LineSegment<VectorT> (triangle.A, triangle.B)) ||
                this->LineSegment<VectorT>::Intersection(LineSegment<VectorT> (triangle.B, triangle.C)) ||
                this->LineSegment<VectorT>::Intersection(LineSegment<VectorT> (triangle.C, triangle.A)))
                return true;

            // If not, we check if segment is fully contained in the triangle
            // We only check "A" end point, since if "A" is inside, "B" must be inside too (see previus test).
            else
                return PointInsideTriangle(triangle, this->A);
        }

        Z_ASSERT_WARNING(SFloat::IsNotZero(DOT2 - DOT1), "The variables \"DOT2\" and \"DOT1\" should not be equal (maybe line endpoints coincide)");

        // The point which satisfies both line and plane equations.
        VectorT vAux = this->A + (this->B - this->A) * DOT2/(DOT2 - DOT1);

        // Tests if the point is inside the triangle.
        return PointInsideTriangle(triangle, vAux);
    }
    
    /// <summary>
    /// Checks if resident line segment intersects with the provided hexahedron.
    /// </summary>
    /// <param name="hexahedron">[IN] The hexahedron to be used for intersection calculation. If any of its vertices 
    /// coincide, the behavior is undefined.</param>
    /// <returns>
    /// A boolean value that indicates whether the segment and the hexahedron intersect or not.<br/>
    /// <br/>
    /// <b>True</b><br/>
    /// The segment and the hexahedron intersect, including the following cases:
    /// - The segment intersects with two faces of the hexahedron.
    /// - The segment intersects with a vertex of the hexahedron.
    /// - An endpoint is contained in a face of the hexahedron.
    /// - The entire segment is contained in a face of the hexahedron.
    /// - Only one endpoint is contained in the hexahedron.
    /// - Only one endpoint belongs to an edge of the hexahedron.
    /// - The segment is fully contained in the hexahedron.
    /// - The segment is contained in an edge of the hexahedron.
    /// - The segment intersects with an edge of the hexahedron, even if it does not intersect with any vertex.
    /// - One or both endpoints coincide with vertices of the hexahedron.
    /// 
    /// <b>False</b><br/>
    /// The line segment does not intersect with the hexahedron.
    /// </returns>
    bool Intersection(const BaseHexahedron<VectorT> &hexahedron) const
    {
        // The length of the segment should be greater than zero
        Z_ASSERT_WARNING(this->A != this->B, "The length of the segment should be greater than zero");

        // Checks if there is an intersection with any face.
        if (QuadrilateralIntersection(*this, hexahedron.A, hexahedron.B, hexahedron.C, hexahedron.D) ||
            QuadrilateralIntersection(*this, hexahedron.E, hexahedron.F, hexahedron.G, hexahedron.H) ||
            QuadrilateralIntersection(*this, hexahedron.A, hexahedron.B, hexahedron.H, hexahedron.E) ||
            QuadrilateralIntersection(*this, hexahedron.B, hexahedron.C, hexahedron.G, hexahedron.H) ||
            QuadrilateralIntersection(*this, hexahedron.A, hexahedron.D, hexahedron.F, hexahedron.E) ||
            QuadrilateralIntersection(*this, hexahedron.C, hexahedron.D, hexahedron.F, hexahedron.G) ||
            (this->PointInsideHexahedron(hexahedron, this->A) && this->PointInsideHexahedron(hexahedron, this->B)) )
            return true;
        else
            return false;
    }

    /// <summary>
    /// This method receives a plane, and computes the point where the resident line segment intersects with it,
    /// if it exists.
    /// </summary>
    /// <remarks>
    /// If there's no intersection point or if there are infinite, the output
    /// parameter used for storing that point won't be modified.
    /// </remarks>
    /// <param name="plane">[IN] The plane whose intersection with resident line segment we want to check. If the plane is null,
    /// the behavior is undefined.</param>
    /// <param name="vIntersection">[OUT] The point where they intersect that is closest to A (segment).</param>
    /// <returns>
    /// An enumerated value that indicates how many intersections were found:<br/>
    /// <br/>
    /// <b>None</b><br/>
    /// There are no intersections.<br/>
    ///
    /// <b>One</b><br/>
    /// There is one intersection.<br/>
    /// - The endpoints belong to different sides of the space divided by the plane.
    /// - Only one endpoint belongs to the plane.
    ///
    /// <b>Infinite</b><br/>
    /// There are infinite intersections.<br/>
    /// - The segment is contained in the plane.
    /// </returns>
    EIntersections IntersectionPoint(const BasePlane &plane, VectorT &vIntersection) const
    {
        // The length of the segment should be greater than zero
        Z_ASSERT_WARNING(this->A != this->B, "The length of the segment should be greater than zero");

        // The plane shouldn't be null
        Z_ASSERT_WARNING( SFloat::IsNotZero(plane.a) || SFloat::IsNotZero(plane.b) || SFloat::IsNotZero(plane.c), "The input plane shouldn't be null" );

        const float_z &DIST_A = plane.a * this->A.x + plane.b * this->A.y + plane.c * this->A.z + plane.d;
        const float_z &DIST_B = plane.a * this->B.x + plane.b * this->B.y + plane.c * this->B.z + plane.d;

        const bool &IS_ZERO_DIST_A = SFloat::IsZero(DIST_A);
        const bool &IS_ZERO_DIST_B = SFloat::IsZero(DIST_B);

        if (IS_ZERO_DIST_A && !IS_ZERO_DIST_B) // A point lies on plane
        {
            vIntersection = this->A;
            return EIntersections::E_One;
        }
        else if (!IS_ZERO_DIST_A && IS_ZERO_DIST_B) // B point lies on plane
        {
            vIntersection = this->B;
            return EIntersections::E_One;
        }
        else if (IS_ZERO_DIST_A && IS_ZERO_DIST_B) // All line segment lies on plane
            return EIntersections::E_Infinite;
        else if ( SFloat::IsLessThan(DIST_A * DIST_B, SFloat::_0) ) // Line segment intersects plane in a point
        {
            // Being n the plane direction vector, v floating point parameter
            // Point which satisfies plane equation: P.n + d = 0              (1)
            // Point in segment: P: A + v (B - A)                             (2)
            // Therefore:
            // (A + v (B-A)).n + d = 0
            // Reordering:
            // A.n + d + v (B + d - A - d).n = 0; A.n + d = fDistA; B.n + d = fDistB, then
            // fDistA + v (fDistB - fDistA) = 0
            // v = - fDistA/(fDistB - fDistA) = fDistA/(fDistA - fDistB)
            // then we replace v in (2) and we get the intersection point

            const float_z &DENOM = DIST_A - DIST_B;

            Z_ASSERT_WARNING(DENOM != SFloat::_0, "The variable \"DENOM\" must not equal zero, this will cause a division by zero");

            vIntersection = this->A + DIST_A * (this->B - this->A) / DENOM;

            return EIntersections::E_One;
        }
        else // Line segment don't intersects plane
            return EIntersections::E_None;
    }

    /// <summary>
    /// Computes the points where the line segment and a triangle intersect.
    /// </summary>
    /// <remarks>
    /// If there's no intersection point or if there are infinite, the output
    /// parameter used for storing that point won't be modified.<br/>
    /// </remarks>
    /// <param name="triangle">[IN] The triangle to be used for intersection calculation. If any of its vertices coincide,
    /// the behavior is undefined.</param>
    /// <param name="vIntersection">[OUT] A vector where to store the closest intersection point to endpoint A (segment).</param>
    /// <returns>
    /// An enumerated value that indicates how many intersections were found:<br/>
    /// <br/>
    /// <b>None</b><br/>
    /// There are no intersections.<br/>
    ///
    /// <b>One</b><br/>
    /// There is one intersection.<br/>
    /// - The line segment intersects with one edge of the triangle (not intersecting with any vertex).
    /// - The segment intersects with one vertex of the triangle.
    /// - Only one endpoint belongs to the triangle (not intersecting any edge or vertex).
    /// - Only one endpoint belongs to an edge of the triangle, even if the other endpoint is inside of the triangle.
    /// - An endpoint coincides with a vertex of the triangle.
    /// - The line segment intersects with the interior (the face) of the triangle (not intersecting with any edge or vertex).
    ///
    /// <b>Two</b><br/>
    /// There are two intersections.<br/>
    /// - The line segment intersects with two edges of the triangle.
    /// - The line segment intersects with two vertices of the triangle.
    /// - The line segment belongs to an edge of the triangle.
    /// - The segment and an edge of the triangle coincide partially, so there is a vertex inside of the segment, and an endpoint inside of the edge.
    ///
    /// <b>Infinite</b><br/>
    /// There are infinite intersections.<br/>
    /// - The segment is contained in the triangle (endpoints are not tangent to any edge).
    /// </returns>
    EIntersections IntersectionPoint(const BaseTriangle<VectorT> &triangle, VectorT &vIntersection) const
    {
        // [TODO] Thund: This must be optimized
        // Calculates if segment intersects with the plane defined by the triangle.
        VectorT vAux;
        return this->IntersectionPoint(triangle, vIntersection, vAux);
    }

    /// <summary>
    /// Computes the points where the line segment and a triangle intersect.
    /// </summary>
    /// <remarks>
    /// If there are no intersection points or if there are infinite, the output
    /// parameters used for storing those points will not be modified.<br/>
    /// </remarks>
    /// <param name="triangle">[IN] The triangle whose intersection with resident line segment we want to check. If any of its vertices coincide,
    /// the behavior is undefined.</param>
    /// <param name="vIntersection1">[OUT] A vector where to store the closest intersection point to endpoint A (segment).</param>
    /// <param name="vIntersection2">[OUT] A vector where to store the furthest intersection point to endpoint A (segment).</param>
    /// <returns>
    /// An enumerated value that indicates how many intersections were found:<br/>
    /// <br/>
    /// <b>None</b><br/>
    /// There are no intersections.<br/>
    ///
    /// <b>One</b><br/>
    /// There is one intersection.<br/>
    /// - The line segment intersects with one edge of the triangle (not intersecting with any vertex).
    /// - The segment intersects with one vertex of the triangle.
    /// - Only one endpoint belongs to the triangle (not intersecting any edge or vertex).
    /// - Only one endpoint belongs to an edge of the triangle, even if the other endpoint is inside of the triangle.
    /// - An endpoint coincides with a vertex of the triangle.
    /// - The line segment intersects with the interior (the face) of the triangle (not intersecting with any edge or vertex).
    ///
    /// <b>Two</b><br/>
    /// There are two intersections.<br/>
    /// - The line segment intersects with two edges of the triangle.
    /// - The line segment intersects with two vertices of the triangle.
    /// - The line segment belongs to an edge of the triangle.
    /// - The segment and an edge of the triangle coincide partially, so there is a vertex inside of the segment, and an endpoint inside of the edge.
    ///
    /// <b>Infinite</b><br/>
    /// There are infinite intersections.<br/>
    /// - The segment is contained in the triangle (endpoints are not tangent to any edge).
    /// </returns>
    EIntersections IntersectionPoint(const BaseTriangle<VectorT> &triangle, VectorT &vIntersection1, VectorT &vIntersection2) const
    {
        // The length of the segment should be greater than zero
        Z_ASSERT_WARNING(this->A != this->B, "The length of the segment should be greater than zero");

        // Vertices of the triangle should not coincide
        Z_ASSERT_WARNING(triangle.A != triangle.B && triangle.B != triangle.C && triangle.C != triangle.A, "Vertices of the triangle should not coincide");

        // Plane equation
        Plane auxP(triangle.A, triangle.B, triangle.C);

        VectorT vPoint;

        EIntersections value = this->IntersectionPoint(auxP, vPoint);

        if (value == EIntersections::E_None) // Line segment don't intersects the triangle plane.
            return EIntersections::E_None;
        else if (value == EIntersections::E_One) // Line segment has one intersection with the triangle plane.
        {
            if (PointInsideTriangle(triangle, vPoint))
            {
                vIntersection1 = vPoint;
                return EIntersections::E_One;
            }
            else
                return EIntersections::E_None;
        }
        else // Line segment and triangle are coplanars (value == EIntersections::E_Infinite)
        {
            const bool &A_IS_INSIDE = PointInsideTriangle(triangle, this->A);
            const bool &B_IS_INSIDE = PointInsideTriangle(triangle, this->B);

            if (A_IS_INSIDE && B_IS_INSIDE) // Both line segment end points are inside triangle.
            {
                // A or B are vertex
                const bool &A_IS_VERTEX = (this->A == triangle.A || this->A == triangle.B || this->A == triangle.C);
                const bool &B_IS_VERTEX = (this->B == triangle.A || this->B == triangle.B || this->B == triangle.C);

                if (A_IS_VERTEX && B_IS_VERTEX) // Both endpoints are vertices of triangle
                {
                    vIntersection1 = this->A;
                    vIntersection2 = this->B;
                    return EIntersections::E_Two;
                }
                else if (A_IS_VERTEX) // Only A endpoint is a vertex of triangle
                {
                    vIntersection1 = this->A;

                    if (SFloat::IsZero(LineSegment<VectorT>(triangle.A, triangle.B).MinDistance(this->B))) // B is in AB triangle edge
                    {
                        if (this->A == triangle.A || this->A == triangle.B) // A and B are in the same edge
                            return EIntersections::E_One;
                        else
                        {
                            vIntersection2 = this->B;
                            return EIntersections::E_Two;
                        }
                    }
                    else if (SFloat::IsZero(LineSegment<VectorT>(triangle.B, triangle.C).MinDistance(this->B))) // B is in BC triangle edge
                    {
                        if (this->A == triangle.B || this->A == triangle.C) // A and B are in the same edge
                            return EIntersections::E_One;
                        else
                        {
                            vIntersection2 = this->B;
                            return EIntersections::E_Two;
                        }
                    }
                    else if (SFloat::IsZero(LineSegment<VectorT>(triangle.C, triangle.A).MinDistance(this->B))) // B is in CA triangle edge
                    {
                        if (this->A == triangle.C || this->A == triangle.A) // A and B are in the same edge
                            return EIntersections::E_One;
                        else
                        {
                            vIntersection2 = this->B;
                            return EIntersections::E_Two;
                        }
                    }
                    else // B is not in an edge
                    {
                        vIntersection1 = this->A;
                        return EIntersections::E_One;
                    }
                }
                else if (B_IS_VERTEX)
                {
                    if (SFloat::IsZero(LineSegment<VectorT>(triangle.A, triangle.B).MinDistance(this->A))) // A is in AB triangle edge
                    {
                        if (this->B == triangle.A || this->B == triangle.B) // A and B are in the same edge
                        {
                            vIntersection1 = this->B;
                            return EIntersections::E_One;
                        }
                        else
                        {
                            vIntersection1 = this->A;
                            vIntersection2 = this->B;
                            return EIntersections::E_Two;
                        }
                    }
                    else if (SFloat::IsZero(LineSegment<VectorT>(triangle.B, triangle.C).MinDistance(this->A))) // B is in BC triangle edge
                    {
                        if (this->B == triangle.B || this->B == triangle.C) // A and B are in the same edge
                        {
                            vIntersection1 = this->B;
                            return EIntersections::E_One;
                        }
                        else
                        {
                            vIntersection1 = this->A;
                            vIntersection2 = this->B;
                            return EIntersections::E_Two;
                        }
                    }
                    else if (SFloat::IsZero(LineSegment<VectorT>(triangle.C, triangle.A).MinDistance(this->A))) // B is in CA triangle edge
                    {
                        if (this->B == triangle.C || this->B == triangle.A) // A and B are in the same edge
                        {
                            vIntersection1 = this->B;
                            return EIntersections::E_One;
                        }
                        else
                        {
                            vIntersection1 = this->A;
                            vIntersection2 = this->B;
                            return EIntersections::E_Two;
                        }
                    }
                    else
                    {
                        vIntersection1 = this->B;
                        return EIntersections::E_One;
                    }
                }
                else // Neither A or B are vertices of triangle
                {
                    if (SFloat::IsZero(LineSegment<VectorT>(triangle.A, triangle.B).MinDistance(this->A))) // A is in AB triangle edge (but not a vertex)
                    {
                        vIntersection1 = this->A;

                        if (SFloat::IsZero(LineSegment<VectorT>(triangle.A, triangle.B).MinDistance(this->B)) || // B is in AB triangle edge (but not a vertex)
                            SFloat::IsZero(LineSegment<VectorT>(triangle.B, triangle.C).MinDistance(this->B)) || // B is in other edge (but not a vertex)
                            SFloat::IsZero(LineSegment<VectorT>(triangle.C, triangle.A).MinDistance(this->B)) )
                        {
                            vIntersection2 = this->B;
                            return EIntersections::E_Two;
                        }
                        else // B is not in an edge
                        {
                            return EIntersections::E_One;
                        }
                    }
                    else if (SFloat::IsZero(LineSegment<VectorT>(triangle.B, triangle.C).MinDistance(this->A))) // A is in BC triangle edge (but not a vertex)
                    {
                        vIntersection1 = this->A;

                        if (SFloat::IsZero(LineSegment<VectorT>(triangle.B, triangle.C).MinDistance(this->B)) || // B is in BC triangle edge (but not a vertex)
                            SFloat::IsZero(LineSegment<VectorT>(triangle.A, triangle.B).MinDistance(this->B)) || // B is in other edge (but not a vertex)
                            SFloat::IsZero(LineSegment<VectorT>(triangle.C, triangle.A).MinDistance(this->B)) )
                        {
                            vIntersection2 = this->B;
                            return EIntersections::E_Two;
                        }
                        else // B is not in an edge
                        {
                            return EIntersections::E_One;
                        }
                    }
                    else if (SFloat::IsZero(LineSegment<VectorT>(triangle.C, triangle.A).MinDistance(this->A))) // A is in CA triangle edge (but not a vertex)
                    {
                        vIntersection1 = this->A;

                        if (SFloat::IsZero(LineSegment<VectorT>(triangle.C, triangle.A).MinDistance(this->B)) || // B is in CA triangle edge (but not a vertex)
                            SFloat::IsZero(LineSegment<VectorT>(triangle.A, triangle.B).MinDistance(this->B)) || // B is in other edge (but not a vertex)
                            SFloat::IsZero(LineSegment<VectorT>(triangle.B, triangle.C).MinDistance(this->B)) )
                        {
                            vIntersection2 = this->B;
                            return EIntersections::E_Two;
                        }
                        else // B is not in an edge
                        {
                            return EIntersections::E_One;
                        }
                    }
                    else // A is not in an edge
                    {
                        if ( SFloat::IsZero(LineSegment<VectorT>(triangle.A, triangle.B).MinDistance(this->B)) || // B is in an edge (but not a vertex)
                             SFloat::IsZero(LineSegment<VectorT>(triangle.B, triangle.C).MinDistance(this->B)) ||
                             SFloat::IsZero(LineSegment<VectorT>(triangle.C, triangle.A).MinDistance(this->B)) )
                        {
                            // B belongs to an edge
                            vIntersection1 = this->B;
                            return EIntersections::E_One;
                        }
                        else // A and B don't belong to any edge and are inside the triangle
                            return EIntersections::E_Infinite;
                    }
                }
            }
            else if (!A_IS_INSIDE && !B_IS_INSIDE) // Both line segment end points are outside triangle.
            {
                VectorT vPointAB1, vPointBC1, vPointCA1;
                VectorT vPointAB2, vPointBC2, vPointCA2;

                EIntersections value2AB = this->IntersectionPoint(LineSegment3D<VectorT>(triangle.A, triangle.B), vPointAB1, vPointAB2);

                if (value2AB == EIntersections::E_Two) // Line segment contains AB edge of triangle
                {
                    vIntersection1 = vPointAB1;
                    vIntersection2 = vPointAB2;
                    return EIntersections::E_Two;
                }
                else if(value2AB == EIntersections::E_Infinite)
                {
                    vIntersection1 = this->A;
                    vIntersection2 = this->B;
                    return EIntersections::E_Two;
                }

                // Line segment contains BC edge of triangle
                EIntersections value2BC = this->IntersectionPoint(LineSegment3D<VectorT>(triangle.B, triangle.C), vPointBC1, vPointBC2);
                if (value2BC == EIntersections::E_Two)
                {
                    vIntersection1 = vPointBC1;
                    vIntersection2 = vPointBC2;
                    return EIntersections::E_Two;
                }
                else if(value2BC == EIntersections::E_Infinite)
                {
                    vIntersection1 = this->A;
                    vIntersection2 = this->B;
                    return EIntersections::E_Two;
                }

                // Line segment contains CA edge of triangle
                EIntersections value2CA = this->IntersectionPoint(LineSegment3D<VectorT>(triangle.C, triangle.A), vPointCA1, vPointCA2);
                if (value2CA == EIntersections::E_Two)
                {
                    vIntersection1 = vPointCA1;
                    vIntersection2 = vPointCA2;
                    return EIntersections::E_Two;
                }
                else if(value2CA == EIntersections::E_Infinite)
                {
                    vIntersection1 = this->A;
                    vIntersection2 = this->B;
                    return EIntersections::E_Two;
                }

                if (value2AB == EIntersections::E_One) // Line segment intersects AB edge of triangle
                {
                    if (value2BC == EIntersections::E_One) // Line segment intersects BC edge of triangle
                    {
                        if (vPointAB1 == vPointBC1) // Are the same point
                        {
                            if (value2CA == EIntersections::E_One) // Line segment intersects CA edge of triangle
                            {
                                if  ( (vPointAB1 - this->A).GetSquaredLength() < (vPointCA1 - this->A).GetSquaredLength() ) // Returns closest point to A end point of line segment
                                {
                                    vIntersection1 = vPointAB1;
                                    vIntersection2 = vPointCA1;
                                }
                                else
                                {
                                    vIntersection1 = vPointCA1;
                                    vIntersection2 = vPointAB1;
                                }
                                return EIntersections::E_Two;
                            }
                            else
                            {
                                vIntersection1 = vPointAB1;
                                return EIntersections::E_One;
                            }
                        }
                        else
                        {
                            if  ( (vPointAB1 - this->A).GetSquaredLength() < (vPointBC1 - this->A).GetSquaredLength() ) // Returns closest point to A end point of line segment
                            {
                                vIntersection1 = vPointAB1;
                                vIntersection2 = vPointBC1;
                            }
                            else
                            {
                                vIntersection1 = vPointBC1;
                                vIntersection2 = vPointAB1;
                            }

                            return EIntersections::E_Two;
                        }
                    }
                    else if (value2CA == EIntersections::E_One) // Line segment intersects CA edge of triangle
                    {
                        if (vPointAB1 == vPointCA1) // Are the same point
                        {
                            vIntersection1 = vPointAB1;
                            return EIntersections::E_One;
                        }
                        else
                        {
                            if  ( (vPointAB1 - this->A).GetSquaredLength() < (vPointCA1 - this->A).GetSquaredLength() ) // Returns closest point to A end point of line segment
                            {
                                vIntersection1 = vPointAB1;
                                vIntersection2 = vPointCA1;
                            }
                            else
                            {
                                vIntersection1 = vPointCA1;
                                vIntersection2 = vPointAB1;
                            }

                            return EIntersections::E_Two;
                        }
                    }
                }
                else if (value2BC == EIntersections::E_One) // Line segment intersects BC edge of triangle
                {
                    if (value2CA == EIntersections::E_One) // Line segment intersects CA edge of triangle
                    {
                        if (vPointBC1 == vPointCA1) // Are the same point
                        {
                            vIntersection1 = vPointBC1;
                            return EIntersections::E_One;
                        }
                        else
                        {
                            if  ( (vPointBC1 - this->A).GetSquaredLength() < (vPointCA1 - this->A).GetSquaredLength() ) // Returns closest point to A end point of line segment
                            {
                                vIntersection1 = vPointBC1;
                                vIntersection2 = vPointCA1;
                            }
                            else
                            {
                                vIntersection1 = vPointCA1;
                                vIntersection2 = vPointBC1;
                            }

                            return EIntersections::E_Two;
                        }
                    }
                }

                // Line segment don't intersects triangle
                if (value2AB == EIntersections::E_None && value2BC == EIntersections::E_None && value2CA == EIntersections::E_None)
                    return EIntersections::E_None;
            }
            else // one line segment end point is inside and the other one is outside triangle.
            {
                VectorT vAux; // To store intersection points

                if (A_IS_INSIDE) // this->A is inside triangle
                {
                    if (this->A == triangle.A) // this->A is A triangle vertex
                    {
                        vIntersection1 = this->A;

                        EIntersections value2 = this->IntersectionPoint(LineSegment3D<VectorT>(triangle.B, triangle.C), vAux);
                        if (value2 == EIntersections::E_One) // ls intersects opposite edge
                        {
                            vIntersection2 = vAux;
                            return EIntersections::E_Two;
                        }
                        else
                            return EIntersections::E_One; // ls only intersects triangle in A vertex
                    }
                    else if (this->A == triangle.B) // this->A is B triangle vertex
                    {
                        vIntersection1 = this->A;

                        EIntersections value2 = this->IntersectionPoint(LineSegment3D<VectorT>(triangle.C, triangle.A), vAux);
                        if (value2 == EIntersections::E_One) // ls intersects opposite edge
                        {
                            vIntersection2 = vAux;
                            return EIntersections::E_Two;
                        }
                        else
                            return EIntersections::E_One; // ls only intersects triangle in B vertex
                    }
                    else if (this->A == triangle.C) // this->A is C triangle vertex
                    {
                        vIntersection1 = this->A;

                        EIntersections value2 = this->IntersectionPoint(LineSegment3D<VectorT>(triangle.B, triangle.A), vAux);
                        if (value2 == EIntersections::E_One) // ls intersects opposite edge
                        {
                            vIntersection2 = vAux;
                            return EIntersections::E_Two;
                        }
                        else
                            return EIntersections::E_One;  // ls only intersects triangle in C vertex
                    }
                    else if (SFloat::IsZero(LineSegment<VectorT>(triangle.A, triangle.B).MinDistance(this->A))) // this->A is in AB triangle edge (but not a vertex)
                    {
                        vIntersection1 = this->A;

                        // ls intersects other edges
                        EIntersections value2 = this->IntersectionPoint(LineSegment3D<VectorT>(triangle.B, triangle.C), vAux);
                        if (value2 == EIntersections::E_One)
                        {
                            if (vAux == triangle.B || vAux == triangle.C) // Both intersections are in the same edge
                                return EIntersections::E_One;

                            vIntersection2 = vAux;
                            return EIntersections::E_Two;
                        }
                        else if ((value2 = this->IntersectionPoint(LineSegment3D<VectorT>(triangle.C, triangle.A), vAux)) == EIntersections::E_One)
                        {
                            if (vAux == triangle.C || vAux == triangle.A) // Both intersections are in the same edge
                                return EIntersections::E_One;

                            vIntersection2 = vAux;
                            return EIntersections::E_Two;
                        }
                        else
                            return EIntersections::E_One;
                    }
                    else if (SFloat::IsZero(LineSegment<VectorT>(triangle.B, triangle.C).MinDistance(this->A))) // this->A is in BC triangle edge (but not a vertex)
                    {
                        vIntersection1 = this->A;

                         // ls intersects other edges
                        EIntersections value2 = this->IntersectionPoint(LineSegment3D<VectorT>(triangle.A, triangle.B), vAux);
                        if (value2 == EIntersections::E_One)
                        {
                            if (vAux == triangle.A || vAux == triangle.B) // Both intersections are in the same edge
                                return EIntersections::E_One;

                            vIntersection2 = vAux;
                            return EIntersections::E_Two;
                        }
                        else if ((value2 = this->IntersectionPoint(LineSegment3D<VectorT>(triangle.C, triangle.A), vAux)) == EIntersections::E_One)
                        {
                            if (vAux == triangle.C || vAux == triangle.A) // Both intersections are in the same edge
                                return EIntersections::E_One;

                            vIntersection2 = vAux;
                            return EIntersections::E_Two;
                        }
                        else
                            return EIntersections::E_One;
                    }
                    else if (SFloat::IsZero(LineSegment<VectorT>(triangle.C, triangle.A).MinDistance(this->A))) // this->A is in CA triangle edge (but not a vertex)
                    {
                        vIntersection1 = this->A;

                         // ls intersects other edges
                        EIntersections value2 = this->IntersectionPoint(LineSegment3D<VectorT>(triangle.B, triangle.C), vAux);
                        if (value2 == EIntersections::E_One)
                        {
                            if (vAux == triangle.B || vAux == triangle.C) // Both intersections are in the same edge
                                return EIntersections::E_One;

                            vIntersection2 = vAux;
                            return EIntersections::E_Two;
                        }
                        else if ((value2 = this->IntersectionPoint(LineSegment3D<VectorT>(triangle.A, triangle.B), vAux)) == EIntersections::E_One)
                        {
                            if (vAux == triangle.A || vAux == triangle.B) // Both intersections are in the same edge
                                return EIntersections::E_One;

                            vIntersection2 = vAux;
                            return EIntersections::E_Two;
                        }
                        else
                            return EIntersections::E_One;
                    }
                    else // this->A is strictly inside triangle: it is not in a vertex or edge
                    {
                        EIntersections value2 = this->IntersectionPoint(LineSegment3D<VectorT>(triangle.A, triangle.B), vAux);
                        if (value2 == EIntersections::E_One)
                            vIntersection1 = vAux;
                        else if ((value2 = this->IntersectionPoint(LineSegment3D<VectorT>(triangle.B, triangle.C), vAux)) == EIntersections::E_One)
                            vIntersection1 = vAux;
                        else if ((value2 = this->IntersectionPoint(LineSegment3D<VectorT>(triangle.C, triangle.A), vAux)) == EIntersections::E_One)
                            vIntersection1 = vAux;

                        return EIntersections::E_One;
                    }
                }
                else // this->B is inside triangle (A is outside)
                {
                    if (this->B == triangle.A) // this->B is triangle.A vertex
                    {

                        EIntersections value2 = this->IntersectionPoint(LineSegment3D<VectorT>(triangle.B, triangle.C), vAux);
                        if (value2 == EIntersections::E_One) // ls intersects opposite edge
                        {
                            vIntersection1 = vAux;
                            vIntersection2 = this->B;
                            return EIntersections::E_Two;
                        }
                        else // ls only intersects in A vertex
                        {
                            vIntersection1 = this->B;
                            return EIntersections::E_One;
                        }
                    }
                    else if (this->B == triangle.B) // this->B is triangle.B vertex
                    {
                        EIntersections value2 = this->IntersectionPoint(LineSegment3D<VectorT>(triangle.C, triangle.A), vAux);
                        if (value2 == EIntersections::E_One) // ls intersects opposite edge
                        {
                            vIntersection1 = vAux;
                            vIntersection2 = this->B;
                            return EIntersections::E_Two;
                        }
                        else // ls only intersects in B vertex
                        {
                            vIntersection1 = this->B;
                            return EIntersections::E_One;
                        }
                    }
                    else if (this->B == triangle.C) // this->B is triangle.C vertex
                    {
                        EIntersections value2 = this->IntersectionPoint(LineSegment3D<VectorT>(triangle.A, triangle.B), vAux);
                        if (value2 == EIntersections::E_One) // ls intersects opposite edge
                        {
                            vIntersection1 = vAux;
                            vIntersection2 = this->B;
                            return EIntersections::E_Two;
                        }
                        else // ls only intersects in C vertex
                        {
                            vIntersection1 = this->B;
                            return EIntersections::E_One;
                        }
                    }
                    else if (SFloat::IsZero(LineSegment<VectorT>(triangle.A, triangle.B).MinDistance(this->B))) // this->B is in AB triangle edge (but not a vertex)
                    {
                        // ls intersects the other edges
                        EIntersections value2 = this->IntersectionPoint(LineSegment3D<VectorT>(triangle.B, triangle.C), vAux);
                        if (value2 == EIntersections::E_One)
                        {
                            vIntersection1 = vAux;

                            if (vAux == triangle.B || vAux == triangle.C) // Both intersections are in the same edge
                                return EIntersections::E_One;

                            vIntersection2 = this->B;
                            return EIntersections::E_Two;
                        }
                        else if ((value2 = this->IntersectionPoint(LineSegment3D<VectorT>(triangle.C, triangle.A), vAux)) == EIntersections::E_One)
                        {
                            vIntersection1 = vAux;

                            if (vAux == triangle.C || vAux == triangle.A) // Both intersections are in the same edge
                                return EIntersections::E_One;

                            vIntersection2 = this->B;
                            return EIntersections::E_Two;
                        }
                        else // There is no other intersection
                        {
                            vIntersection1 = this->B;
                            return EIntersections::E_One;
                        }
                    }
                    else if (SFloat::IsZero(LineSegment<VectorT>(triangle.B, triangle.C).MinDistance(this->B))) // this->B is in BC triangle edge (but not a vertex)
                    {
                        // ls intersects the other edges
                        EIntersections value2 = this->IntersectionPoint(LineSegment3D<VectorT>(triangle.A, triangle.B), vAux);
                        if (value2 == EIntersections::E_One)
                        {
                            vIntersection1 = vAux;

                            if (vAux == triangle.A || vAux == triangle.B) // Both intersections are in the same edge
                                return EIntersections::E_One;

                            vIntersection2 = this->B;
                            return EIntersections::E_Two;
                        }
                        else if ((value2 = this->IntersectionPoint(LineSegment3D<VectorT>(triangle.C, triangle.A), vAux)) == EIntersections::E_One)
                        {
                            vIntersection1 = vAux;
                            vIntersection2 = this->B;
                            return EIntersections::E_Two;
                        }
                        else // There is no other intersection
                        {
                            vIntersection1 = this->B;
                            return EIntersections::E_One;
                        }
                    }
                    else if (SFloat::IsZero(LineSegment<VectorT>(triangle.C, triangle.A).MinDistance(this->B))) // this->B is in CA triangle edge (but not a vertex)
                    {
                        // ls intersects the other edges
                        EIntersections value2 = this->IntersectionPoint(LineSegment3D<VectorT>(triangle.B, triangle.C), vAux);
                        if (value2 == EIntersections::E_One)
                        {
                            vIntersection1 = vAux;

                            if (vAux == triangle.B || vAux == triangle.C) // Both intersections are in the same edge
                                return EIntersections::E_One;

                            vIntersection2 = this->B;
                            return EIntersections::E_Two;
                        }
                        else if ((value2 = this->IntersectionPoint(LineSegment3D<VectorT>(triangle.A, triangle.B), vAux)) == EIntersections::E_One)
                        {
                            vIntersection1 = vAux;

                            if (vAux == triangle.A || vAux == triangle.B) // Both intersections are in the same edge
                                return EIntersections::E_One;

                            vIntersection2 = this->B;
                            return EIntersections::E_Two;
                        }
                        else // There is no other intersection
                        {
                            vIntersection1 = this->B;
                            return EIntersections::E_One;
                        }
                    }
                    else // this->B is strictly inside triangle: is not in a vertex or edge.
                    {
                        EIntersections value2 = this->IntersectionPoint(LineSegment3D<VectorT>(triangle.A, triangle.B), vAux);
                        if (value2 == EIntersections::E_One)
                            vIntersection1 = vAux;
                        else if ((value2 = this->IntersectionPoint(LineSegment3D<VectorT>(triangle.B, triangle.C), vAux)) == EIntersections::E_One)
                            vIntersection1 = vAux;
                        else if ((value2 = this->IntersectionPoint(LineSegment3D<VectorT>(triangle.C, triangle.A), vAux)) == EIntersections::E_One)
                            vIntersection1 = vAux;

                        return EIntersections::E_One;
                    }
                }
            }
        }

        // Something was wrong, this line should be never reached
        Z_ASSERT_WARNING(false, "Something went really wrong, this code branch must never be reached");

        return EIntersections::E_None;
    }
    
    /// <summary>
    /// Computes the points where the line segment and a hexahedron intersect.
    /// </summary>
    /// <remarks>
    /// If there's no intersection point of if there are infinite, the output parameter used for storing that point won't be modified.
    /// </remarks>
    /// <param name="hexahedron">[IN] The hexahedron whose intersections with the line segment are to be checked. If any of its vertices coincide,
    /// the behavior is undefined.</param>
    /// <param name="vIntersection">[OUT] A vector where to store the closest intersection point to endpoint A (segment).</param>
    /// <returns>
    /// An enumerated value that indicates how many intersections were found:<br/>
    /// <br/>
    /// <b>None</b><br/>
    /// There are no intersections.<br/>
    ///
    /// <b>One</b><br/>
    /// There is one intersection.<br/>
    /// - The line segment intersects with a vertex of the hexahedron.
    /// - Only one endpoint is contained in a face of the hexahedron, even if the other endpoint is inside of the hexahedron.
    /// - Only one endpoint is contained in the hexahedron.
    /// - Only one endpoint is contained in an edge of the hexahedron.
    /// - The line segment intersects with an edge of the hexahedron, being both endpoints outside.
    /// - An endpoint coincide with a vertex of the hexahedron.
    ///
    /// <b>Two</b><br/>
    /// There are two intersections.<br/>
    /// - The segment intersects with two faces of the hexahedron.
    /// - Both endpoints belong to two different faces of the hexahedron.
    /// - Both endpoints belong to the same edge of the hexahedron.
    /// - An endpoint is contained in a face and the other is contained in an edge of the hexahedron.
    ///
    /// <b>Infinite</b><br/>
    /// There are infinite intersections.<br/>
    /// - The segment is contained in the hexahedron (endpoints are not tangent to any face).
    /// </returns>
    EIntersections IntersectionPoint(const BaseHexahedron<VectorT> &hexahedron, VectorT &vIntersection) const
    {
        // The length of the segment should be greater than zero
        Z_ASSERT_WARNING(this->A != this->B, "The length of the segment should be greater than zero");

        VectorT vAuxPoint, vAux;
        bool bPreviousInt = false;

        // Check if resident line segment intersects ABCD face
        EIntersections value1 = QuadrilateralIntersectionPoint(*this, hexahedron.A, hexahedron.B, hexahedron.C, hexahedron.D, vAux);

        if ( value1 == EIntersections::E_Two ) // There are 2 intersections
        {
            vIntersection = vAux;
            return EIntersections::E_Two;
        }
        else if (value1 == EIntersections::E_One) // There is only one intersection
        {
            vAuxPoint = vAux;
            bPreviousInt = true;
        }
        else if (value1 == EIntersections::E_Infinite) // Line segment lies in this face (without intersections with any edge or vertex)
        {
            vIntersection = this->A;
            return EIntersections::E_Two;
        }

        // Check if resident line segment intersects EFGH face
        EIntersections value2 = QuadrilateralIntersectionPoint(*this, hexahedron.E, hexahedron.F, hexahedron.G, hexahedron.H, vAux);

        if ( value2 == EIntersections::E_Two ) // There are 2 intersections
        {
            vIntersection = vAux;
            return EIntersections::E_Two;
        }
        else if (value2 == EIntersections::E_One) // There is only one intersection
        {
            if (bPreviousInt && (vAuxPoint != vAux)) // There is one intersection with other face and both points are not the same
            {
                if  ( (vAuxPoint - this->A).GetSquaredLength() < (vAux - this->A).GetSquaredLength() ) // Computes the closest intersection to A end point
                    vIntersection = vAuxPoint;
                else
                    vIntersection = vAux;
                return EIntersections::E_Two;
            }
            else
            {
                vAuxPoint = vAux;
                bPreviousInt = true;
            }
        }
        else if (value2 == EIntersections::E_Infinite) // Line segment lies in this face (without intersections with any edge or vertex)
        {
            vIntersection = this->A;
            return EIntersections::E_Two;
        }

        // Check if resident line segment intersects ABHE face
        EIntersections value3 = QuadrilateralIntersectionPoint(*this, hexahedron.A, hexahedron.B, hexahedron.H, hexahedron.E, vAux);

        if (value3 == EIntersections::E_Two ) // There are 2 intersections
        {
            vIntersection = vAux;
            return EIntersections::E_Two;
        }
        else if (value3 == EIntersections::E_One) // There is only one intersection
        {
            if (bPreviousInt && (vAuxPoint != vAux)) // There is one intersection with other face and both points are not the same
            {
                if  ( (vAuxPoint - this->A).GetSquaredLength() < (vAux - this->A).GetSquaredLength() ) // Computes the closest intersection to A end point
                    vIntersection = vAuxPoint;
                else
                    vIntersection = vAux;
                return EIntersections::E_Two;
            }
            else
            {
                vAuxPoint = vAux;
                bPreviousInt = true;
            }
        }
        else if (value3 == EIntersections::E_Infinite) // Line segment lies in this face (without intersections with any edge or vertex)
        {
            vIntersection = this->A;
            return EIntersections::E_Two;
        }

        // Check if resident line segment intersects BCGH face
        EIntersections value4 = QuadrilateralIntersectionPoint(*this, hexahedron.B, hexahedron.C, hexahedron.G, hexahedron.H, vAux);

        if ( value4 == EIntersections::E_Two ) // There are 2 intersections
        {
            vIntersection = vAux;
            return EIntersections::E_Two;
        }
        else if (value4 == EIntersections::E_One) // There is only one intersection
        {
            if (bPreviousInt && (vAuxPoint != vAux)) // There is one intersection with other face and both points are not the same
            {
                if  ( (vAuxPoint - this->A).GetSquaredLength() < (vAux - this->A).GetSquaredLength() ) // Computes the closest intersection to A end point
                    vIntersection = vAuxPoint;
                else
                    vIntersection = vAux;
                return EIntersections::E_Two;
            }
            else
            {
                vAuxPoint = vAux;
                bPreviousInt = true;
            }
        }
        else if (value4 == EIntersections::E_Infinite) // Line segment lies in this face (without intersections with any edge or vertex)
        {
            vIntersection = this->A;
            return EIntersections::E_Two;
        }

        // Check if resident line segment intersects ADFE face
        EIntersections value5 = QuadrilateralIntersectionPoint(*this, hexahedron.A, hexahedron.D, hexahedron.F, hexahedron.E, vAux);

        if ( value5 == EIntersections::E_Two ) // There are 2 intersections
        {
            vIntersection = vAux;
            return EIntersections::E_Two;
        }
        else if (value5 == EIntersections::E_One) // There is only one intersection
        {
            if (bPreviousInt && (vAuxPoint != vAux)) // There is one intersection with other face and both points are not the same
            {
                if  ( (vAuxPoint - this->A).GetSquaredLength() < (vAux - this->A).GetSquaredLength() ) // Computes the closest intersection to A end point
                    vIntersection = vAuxPoint;
                else
                    vIntersection = vAux;
                return EIntersections::E_Two;
            }
            else
            {
                vAuxPoint = vAux;
                bPreviousInt = true;
            }
        }
        else if (value5 == EIntersections::E_Infinite) // Line segment lies in this face (without intersections with any edge or vertex)
        {
            vIntersection = this->A;
            return EIntersections::E_Two;
        }

        // Check if resident line segment intersects CDFG face
        EIntersections value6 = QuadrilateralIntersectionPoint(*this, hexahedron.C, hexahedron.D, hexahedron.F, hexahedron.G, vAux);

        if ( value6 == EIntersections::E_Two ) // There are 2 intersections
        {
            vIntersection = vAux;
            return EIntersections::E_Two;
        }
        else if (value6 == EIntersections::E_One) // There is only one intersection
        {
            if (bPreviousInt && (vAuxPoint != vAux)) // There is one intersection with other face and both points are not the same
            {
                if  ( (vAuxPoint - this->A).GetSquaredLength() < (vAux - this->A).GetSquaredLength() ) // Computes the closest intersection to A end point
                    vIntersection = vAuxPoint;
                else
                    vIntersection = vAux;
                return EIntersections::E_Two;
            }
            else
            {
                vAuxPoint = vAux;
                bPreviousInt = true;
            }
        }
        else if (value6 == EIntersections::E_Infinite) // Line segment lies in this face (without intersections with any edge or vertex)
        {
            vIntersection = this->A;
            return EIntersections::E_Two;
        }

        if (bPreviousInt) // There is only one intersection with hexahedron
        {
            vIntersection = vAuxPoint;
            return EIntersections::E_One;
        }
        else // There are no intersections with hexahedron
        {
            const bool &A_IS_INSIDE = PointInsideHexahedron(hexahedron, this->A);
            const bool &B_IS_INSIDE = PointInsideHexahedron(hexahedron, this->B);

            if (A_IS_INSIDE && B_IS_INSIDE) // Both line segment end points are inside hexahedron
                return EIntersections::E_Infinite;
            else if (!A_IS_INSIDE && !B_IS_INSIDE) // Both line segment end points are outside hexahedron
                return EIntersections::E_None;
        }

        // Something was wrong, this line should be never reached
        Z_ASSERT_WARNING(false, "Something went really wrong, this code branch must never be reached");

        return EIntersections::E_None;
    }

    /// <summary>
    /// Computes the points where the line segment and a hexahedron intersect.
    /// </summary>
    /// <remarks>
    /// If there's no intersection point or there are infinite, the output parameters used for storing the intersection points won't be modified.
    /// </remarks>
    /// <param name="hexahedron">[IN] The hexahedron whose intersections with resident line segment we want to check. If any of its vertices coincide,
    /// the behavior is undefined.</param>
    /// <param name="vIntersection1">[OUT] A vector where to store the closest intersection point to endpoint A (segment).</param>
    /// <param name="vIntersection2">[OUT] A vector where to store the furthest intersection point to endpoint A (segment).</param>
    /// <returns>
    /// An enumerated value that indicates how many intersections were found:<br/>
    /// <br/>
    /// <b>None</b><br/>
    /// There are no intersections.<br/>
    ///
    /// <b>One</b><br/>
    /// There is one intersection.<br/>
    /// - The line segment intersects with a vertex of the hexahedron.
    /// - Only one endpoint is contained in a face of the hexahedron, even if the other endpoint is inside of the hexahedron.
    /// - Only one endpoint is contained in the hexahedron.
    /// - Only one endpoint is contained in an edge of the hexahedron.
    /// - The line segment intersects with an edge of the hexahedron, being both endpoints outside.
    /// - An endpoint coincide with a vertex of the hexahedron.
    ///
    /// <b>Two</b><br/>
    /// There are two intersections.<br/>
    /// - The segment intersects with two faces of the hexahedron.
    /// - Both endpoints belong to two different faces of the hexahedron.
    /// - Both endpoints belong to the same edge of the hexahedron.
    /// - An endpoint is contained in a face and the other is contained in an edge of the hexahedron.
    ///
    /// <b>Infinite</b><br/>
    /// There are infinite intersections.<br/>
    /// - The segment is contained in the hexahedron (endpoints are not tangent to any face).
    /// </returns>
    EIntersections IntersectionPoint(const BaseHexahedron<VectorT> &hexahedron, VectorT &vIntersection1, VectorT &vIntersection2) const
    {
        // The length of the segment should be greater than zero
        Z_ASSERT_WARNING(this->A != this->B, "The length of the segment should be greater than zero");

        VectorT vAuxPoint, vAux1, vAux2;
        bool bPreviousInt = false;

        // Check if resident line segment intersects ABCD face
        EIntersections value1 = QuadrilateralIntersectionPoint(*this, hexahedron.A, hexahedron.B, hexahedron.C, hexahedron.D, vAux1, vAux2);

        if ( value1 == EIntersections::E_Two ) // There are 2 intersections
        {
            vIntersection1 = vAux1;
            vIntersection2 = vAux2;
            return EIntersections::E_Two;
        }
        else if (value1 == EIntersections::E_One) // There is only one intersection
        {
            vAuxPoint = vAux1;
            bPreviousInt = true;
        }
        else if (value1 == EIntersections::E_Infinite) // Line segment lies in this face (without intersections with any edge or vertex)
        {
            vIntersection1 = this->A;
            vIntersection2 = this->B;
            return EIntersections::E_Two;
        }

        // Check if resident line segment intersects EFGH face
        EIntersections value2 = QuadrilateralIntersectionPoint(*this, hexahedron.E, hexahedron.F, hexahedron.G, hexahedron.H, vAux1, vAux2);

        if ( value2 == EIntersections::E_Two ) // There are 2 intersections
        {
            vIntersection1 = vAux1;
            vIntersection2 = vAux2;
            return EIntersections::E_Two;
        }
        else if (value2 == EIntersections::E_One) // There is only one intersection
        {
            if (bPreviousInt && (vAuxPoint != vAux1)) // There is one intersection with other face and both points are not the same
            {
                if  ( (vAuxPoint - this->A).GetSquaredLength() < (vAux1 - this->A).GetSquaredLength() ) // Computes the closest intersection to A end point
                {
                    vIntersection1 = vAuxPoint;
                    vIntersection2 = vAux1;
                }
                else
                {
                    vIntersection1 = vAux1;
                    vIntersection2 = vAuxPoint;
                }
                return EIntersections::E_Two;
            }
            else
            {
                vAuxPoint = vAux1;
                bPreviousInt = true;
            }
        }
        else if (value2 == EIntersections::E_Infinite) // Line segment lies in this face (without intersections with any edge or vertex)
        {
            vIntersection1 = this->A;
            vIntersection2 = this->B;
            return EIntersections::E_Two;
        }

        // Check if resident line segment intersects ABHE face
        EIntersections value3 = QuadrilateralIntersectionPoint(*this, hexahedron.A, hexahedron.B, hexahedron.H, hexahedron.E, vAux1, vAux2);

        if ( value3 == EIntersections::E_Two ) // There are 2 intersections
        {
            vIntersection1 = vAux1;
            vIntersection2 = vAux2;
            return EIntersections::E_Two;
        }
        else if (value3 == EIntersections::E_One) // There is only one intersection
        {
            if (bPreviousInt && (vAuxPoint != vAux1)) // There is one intersection with other face and both points are not the same
            {
                if  ( (vAuxPoint - this->A).GetSquaredLength() < (vAux1 - this->A).GetSquaredLength() ) // Computes the closest intersection to A end point
                {
                    vIntersection1 = vAuxPoint;
                    vIntersection2 = vAux1;
                }
                else
                {
                    vIntersection1 = vAux1;
                    vIntersection2 = vAuxPoint;
                }
                return EIntersections::E_Two;
            }
            else
            {
                vAuxPoint = vAux1;
                bPreviousInt = true;
            }
        }
        else if (value3 == EIntersections::E_Infinite) // Line segment lies in this face (without intersections with any edge or vertex)
        {
            vIntersection1 = this->A;
            vIntersection2 = this->B;
            return EIntersections::E_Two;
        }

        // Check if resident line segment intersects BCGH face
        EIntersections value4 = QuadrilateralIntersectionPoint(*this, hexahedron.B, hexahedron.C, hexahedron.G, hexahedron.H, vAux1,vAux2);

        if ( value4 == EIntersections::E_Two ) // There are 2 intersections
        {
            vIntersection1 = vAux1;
            vIntersection2 = vAux2;
            return EIntersections::E_Two;
        }
        else if (value4 == EIntersections::E_One) // There is only one intersection
        {
            if (bPreviousInt && (vAuxPoint != vAux1)) // There is one intersection with other face and both points are not the same
            {
                if  ( (vAuxPoint - this->A).GetSquaredLength() < (vAux1 - this->A).GetSquaredLength() ) // Computes the closest intersection to A end point
                {
                    vIntersection1 = vAuxPoint;
                    vIntersection2 = vAux1;
                }
                else
                {
                    vIntersection1 = vAux1;
                    vIntersection2 = vAuxPoint;
                }
                return EIntersections::E_Two;
            }
            else
            {
                vAuxPoint = vAux1;
                bPreviousInt = true;
            }
        }
        else if (value4 == EIntersections::E_Infinite) // Line segment lies in this face (without intersections with any edge or vertex)
        {
            vIntersection1 = this->A;
            vIntersection2 = this->B;
            return EIntersections::E_Two;
        }

        // Check if resident line segment intersects ADFE face
        EIntersections value5 = QuadrilateralIntersectionPoint(*this, hexahedron.A, hexahedron.D, hexahedron.F, hexahedron.E, vAux1, vAux2);

        if ( value5 == EIntersections::E_Two ) // There are 2 intersections
        {
            vIntersection1 = vAux1;
            vIntersection2 = vAux2;
            return EIntersections::E_Two;
        }
        else if (value5 == EIntersections::E_One) // There is only one intersection
        {
            if (bPreviousInt && (vAuxPoint != vAux1)) // There is one intersection with other face and both points are not the same
            {
                if  ( (vAuxPoint - this->A).GetSquaredLength() < (vAux1 - this->A).GetSquaredLength() ) // Computes the closest intersection to A end point
                {
                    vIntersection1 = vAuxPoint;
                    vIntersection2 = vAux1;
                }
                else
                {
                    vIntersection1 = vAux1;
                    vIntersection2 = vAuxPoint;
                }
                return EIntersections::E_Two;
            }
            else
            {
                vAuxPoint = vAux1;
                bPreviousInt = true;
            }
        }
        else if (value5 == EIntersections::E_Infinite) // Line segment lies in this face (without intersections with any edge or vertex)
        {
            vIntersection1 = this->A;
            vIntersection2 = this->B;
            return EIntersections::E_Two;
        }

        // Check if resident line segment intersects CDFG face
        EIntersections value6 = QuadrilateralIntersectionPoint(*this, hexahedron.C, hexahedron.D, hexahedron.F, hexahedron.G, vAux1, vAux2);

        if ( value6 == EIntersections::E_Two ) // There are 2 intersections
        {
            vIntersection1 = vAux1;
            vIntersection2 = vAux2;
            return EIntersections::E_Two;
        }
        else if (value6 == EIntersections::E_One) // There is only one intersection
        {
            if (bPreviousInt && (vAuxPoint != vAux1)) // There is one intersection with other face and both points are not the same
            {
                if  ( (vAuxPoint - this->A).GetSquaredLength() < (vAux1 - this->A).GetSquaredLength() ) // Computes the closest intersection to A end point
                {
                    vIntersection1 = vAuxPoint;
                    vIntersection2 = vAux1;
                }
                else
                {
                    vIntersection1 = vAux1;
                    vIntersection2 = vAuxPoint;
                }
                return EIntersections::E_Two;
            }
            else
            {
                vAuxPoint = vAux1;
                bPreviousInt = true;
            }
        }
        else if (value6 == EIntersections::E_Infinite) // Line segment lies in this face (without intersections with any edge or vertex)
        {
            vIntersection1 = this->A;
            vIntersection2 = this->B;
            return EIntersections::E_Two;
        }

        if (bPreviousInt) // There is only one intersection with hexahedron
        {
            vIntersection1 = vAuxPoint;
            return EIntersections::E_One;
        }
        else // There are no intersections with hexahedron
        {
            const bool &A_IS_INSIDE = PointInsideHexahedron(hexahedron, this->A);
            const bool &B_IS_INSIDE = PointInsideHexahedron(hexahedron, this->B);

            if (A_IS_INSIDE && B_IS_INSIDE) // Both line segment end points are inside hexahedron
                return EIntersections::E_Infinite;
            else if (!A_IS_INSIDE && !B_IS_INSIDE) // Both line segment end points are outside hexahedron
                return EIntersections::E_None;
        }

        // Something was wrong, this line should be never reached
        Z_ASSERT_WARNING(false, "Something went really wrong, this code branch must never be reached");

        return EIntersections::E_None;
    }

    /// <summary>
    /// Calculates the maximum distance between the resident line segment and a plane provided.
    /// </summary>
    /// <remarks>
    /// The plane must be normalized to obtain correct result.
    /// </remarks>
    /// <param name="plane">[IN] The plane we want to know the maximum distance from the line segment. If it is null, the result
    /// is undefined.</param>
    /// <returns>
    /// A floating point value containing the maximum distance between the resident line segment and a plane provided.
    /// </returns>
    float_z MaxDistance(const Plane &plane) const
    {
        Z_ASSERT_WARNING( SFloat::IsNotZero(plane.a) || SFloat::IsNotZero(plane.b) || SFloat::IsNotZero(plane.c), "Input plane should not be null" );

        const float_z &DIST_A = plane.PointDistance(this->A);
        const float_z &DIST_B = plane.PointDistance(this->B);

        return std::max(DIST_A, DIST_B);
    }

    /// <summary>
    /// Calculates the minimum distance between the resident line segment and a plane provided.
    /// </summary>
    /// <remarks>
    /// The plane must be normalized to obtain correct result.
    /// </remarks>
    /// <param name="plane">[IN] The plane we want to know the minimum distance from the line segment. If it is null, the result
    /// is undefined.</param>
    /// <returns>
    /// A floating point value containing the minimum distance between the resident line segment and a plane provided.
    /// </returns>
    float_z MinDistance(const Plane &plane) const
    {
        Z_ASSERT_WARNING( SFloat::IsNotZero(plane.a) || SFloat::IsNotZero(plane.b) || SFloat::IsNotZero(plane.c), "Input plane should not be null" );

        // [TODO] Thund: This has to be optimized, maybe with an additional constructor in Vector4
        const float_z PLANE_POINT_COMPONENTS[] = {plane.a * -plane.d, plane.b * -plane.d, plane.c * -plane.d, SFloat::_0};
        const VectorT PLANE_POINT = VectorT(PLANE_POINT_COMPONENTS);

        // If the line and the plane don't intersect...
        if(SFloat::IsGreaterOrEquals(PLANE_POINT.DotProduct(this->A), SFloat::_0) == SFloat::IsGreaterOrEquals(PLANE_POINT.DotProduct(this->B), SFloat::_0) ||
           SFloat::IsNegative(PLANE_POINT.DotProduct(this->A)) == SFloat::IsNegative(PLANE_POINT.DotProduct(this->B)))
        {
            const float_z &DIST_A = plane.PointDistance(this->A);
            const float_z &DIST_B = plane.PointDistance(this->B);
            return std::min(DIST_A, DIST_B);
        }

        return SFloat::_0;
    }

    /// <summary>
    /// Projects the resident line segment over the plane provided.
    /// </summary>
    /// <remarks>
    /// The plane must be normalized to obtain correct result.
    /// </remarks>
    /// <param name="plane">[IN] The plane where we want to project the resident line segment. If it is null, the result
    /// is undefined.</param>
    /// <returns>
    /// The projected segment.
    /// </returns>
    LineSegment3D<VectorT> ProjectToPlane(const Plane &plane) const
    {
        // The plane must not be null
        Z_ASSERT_WARNING( SFloat::IsNotZero(plane.a) || SFloat::IsNotZero(plane.b) || SFloat::IsNotZero(plane.c), "The input plane must not be null" );

        return LineSegment3D<VectorT>(plane.PointProjection(this->A),
                                          plane.PointProjection(this->B));
    }

    /// <summary>
    /// Checks the relation between resident line segment and the provided plane.
    /// </summary>
    /// <remarks>
    /// Since a plane divides space into two parts, we can check if the "distances" (allowing distances having sign) from
    /// the plane to both end points of line segment are 0, or have diferent sign, in which case the segment crosses the plane.<br/>
    /// If distances from plane to both end points have the same sign, all line segment is in the same
    /// side of the space, and they haven't a common point.<br/>
    /// Note that if only one end point of the resident line segment lies on the plane, we consider that it is
    /// in one of the sides in which the plane divides the space.
    /// </remarks>
    /// <param name="plane">[IN] The plane we want check the relation with resident line segment. If it is null, the result
    /// is undefined.</param>
    /// <returns>
    /// An integer value like follows:<br/><ul>
    /// <li>Contained: All the line segment lies on plane.</li>
    /// <li>Positive Side: The line segment is fully contained in the positive side of the space defined by the plane.</li>
    /// <li>Negative Side: The line segment is fully contained in the negative side of the space defined by the plane.</li>
    /// <li>BothSides: One end point of the line segment is in the positive side and the other is in the negative one.</li>
    /// </ul><br/>
    /// We consider "positive part of the space" the locus of points which verifies \f$ Ax + By + Cz + D > 0 \f$.
    /// </returns>
    ESpaceRelation SpaceRelation(const BasePlane &plane) const
    {
        // The plane must not be null
        Z_ASSERT_WARNING( SFloat::IsNotZero(plane.a) || SFloat::IsNotZero(plane.b) || SFloat::IsNotZero(plane.c), "The input plane must not be null" );

        const float_z &DIST_A = plane.a * this->A.x + plane.b * this->A.y + plane.c * this->A.z + plane.d;
        const float_z &DIST_B = plane.a * this->B.x + plane.b * this->B.y + plane.c * this->B.z + plane.d;

        if (SFloat::IsZero(DIST_A) && SFloat::IsZero(DIST_B))
            return ESpaceRelation::E_Contained;
        else if ( SFloat::IsGreaterOrEquals(DIST_A, SFloat::_0) && SFloat::IsGreaterOrEquals(DIST_B, SFloat::_0) )
            return ESpaceRelation::E_PositiveSide;
        else if ( SFloat::IsLessOrEquals(DIST_A, SFloat::_0) && SFloat::IsLessOrEquals(DIST_B, SFloat::_0) )
            return ESpaceRelation::E_NegativeSide;
        else
            return ESpaceRelation::E_BothSides;
    }

    /// <summary>
    /// Transforms the resident line segment.
    /// </summary>
    /// <param name="transformation">[IN] 4x3 Matrix which contains the transformation.</param>
    /// <returns>
    /// The transformed segment.
    /// </returns>
    LineSegment3D<VectorT> Transform(const TransformationMatrix<Matrix4x3> &transformation) const
    {
        LineSegment3D<VectorT> auxLineSegment = *this;
        SPoint::Transform(transformation, rcast_z(&auxLineSegment, VectorT*), 2);
        return auxLineSegment;
    }

    /// <summary>
    /// Transforms the resident line segment.
    /// </summary>
    /// <param name="transformation">[IN] 4x4 Matrix which contains the transformation.</param>
    /// <returns>
    /// The transformed segment.
    /// </returns>
    LineSegment3D<VectorT> Transform(const TransformationMatrix<Matrix4x4> &transformation) const
    {
        LineSegment3D<VectorT> auxLineSegment = *this;
        SPoint::Transform(transformation, rcast_z(&auxLineSegment, VectorT*), 2);
        return auxLineSegment;
    }

    /// <summary>
    /// Transforms the resident line segment.
    /// </summary>
    /// <param name="spaceConversion">[IN] Space conversion matrix which contains the transformation.</param>
    /// <returns>
    /// The converted segment.
    /// </returns>
    LineSegment3D<VectorT> Transform(const SpaceConversionMatrix &spaceConversion) const
    {
        LineSegment3D<VectorT> auxLineSegment = *this;
        SPoint::Transform(spaceConversion, rcast_z(&auxLineSegment, VectorT*), 2);
        return auxLineSegment;
    }

    /// <summary>
    /// Transforms the resident line segment using a pivot.
    /// </summary>
    /// <remarks>
    /// When using 4D vectors, the W component of the pivot point doesn't affect the result.
    /// </remarks>
    /// <param name="transformation">[IN] 4x3 Matrix which contains the transformation.</param>
    /// <param name="vPivot">[IN] Vector used as pivot for the rotation.</param>
    /// <returns>
    /// The transformed segment.
    /// </returns>
    LineSegment3D<VectorT> TransformWithPivot(const TransformationMatrix<Matrix4x3> &transformation, const VectorT &vPivot) const
    {
        LineSegment3D<VectorT> auxLineSegment = *this;
        SPoint::TransformWithPivot(transformation, vPivot, rcast_z(&auxLineSegment, VectorT*), 2);
        return auxLineSegment;
    }

    /// <summary>
    /// Transforms the resident line segment using a pivot.
    /// </summary>
    /// <remarks>
    /// When using 4D vectors, the W component of the pivot point doesn't affect the result.
    /// </remarks>
    /// <param name="transformation">[IN] 4x4 Matrix which contains the transformation.</param>
    /// <param name="vPivot">[IN] Vector used as pivot for the rotation.</param>
    /// <returns>
    /// The transformed segment.
    /// </returns>
    LineSegment3D<VectorT> TransformWithPivot(const TransformationMatrix<Matrix4x4> &transformation, const VectorT &vPivot) const
    {
        LineSegment3D<VectorT> auxLineSegment = *this;
        SPoint::TransformWithPivot(transformation, vPivot, rcast_z(&auxLineSegment, VectorT*), 2);
        return auxLineSegment;
    }
    
    /// <summary>
    /// Translates the line segment.
    /// </summary>
    /// <param name="vTranslation">[IN] Vector that contains the translation to be applied.</param>
    /// <returns>
    /// The translated segment.
    /// </returns>
    LineSegment3D<VectorT> Translate(const BaseVector3 &vTranslation) const
    {
        LineSegment3D<VectorT> auxLineSegment = *this;
        SPoint::Translate(vTranslation, rcast_z(&auxLineSegment, VectorT*), 2);
        return auxLineSegment;
    }

    /// <summary>
    /// Translates the line segment.
    /// </summary>
    /// <param name="fTranslationX">[IN] Scalar that contains the translation on X axis.</param>
    /// <param name="fTranslationY">[IN] Scalar that contains the translation on Y axis.</param>
    /// <param name="fTranslationZ">[IN] Scalar that contains the translation on Z axis.</param>
    /// <returns>
    /// The translated segment.
    /// </returns>
    LineSegment3D<VectorT> Translate(const float_z fTranslationX, const float_z fTranslationY, const float_z fTranslationZ) const
    {
        LineSegment3D<VectorT> auxLineSegment = *this;
        SPoint::Translate(fTranslationX, fTranslationY, fTranslationZ, rcast_z(&auxLineSegment, VectorT*), 2);
        return auxLineSegment;
    }

    /// <summary>
    /// Translates the line segment.
    /// </summary>
    /// <param name="translation">[IN] 4x3 Matrix which contains the translation to be applied.</param>
    /// <returns>
    /// The translated segment.
    /// </returns>
    LineSegment3D<VectorT> Translate(const TranslationMatrix<Matrix4x3> &translation) const
    {
        LineSegment3D<VectorT> auxLineSegment = *this;
        SPoint::Translate(translation, rcast_z(&auxLineSegment, VectorT*), 2);
        return auxLineSegment;
    }

    /// <summary>
    /// Translates the line segment.
    /// </summary>
    /// <param name="translation">[IN] 4x4 Matrix which contains the translation to be applied.</param>
    /// <returns>
    /// The translated segment.
    /// </returns>
    LineSegment3D<VectorT> Translate(const TranslationMatrix<Matrix4x4> &translation) const
    {
        LineSegment3D<VectorT> auxLineSegment = *this;
        SPoint::Translate(translation, rcast_z(&auxLineSegment, VectorT*), 2);
        return auxLineSegment;
    }

    /// <summary>
    /// Rotates the line segment.
    /// </summary>
    /// <param name="qRotation">[IN] Quaternion that represents the rotation.</param>
    /// <returns>
    /// The rotated segment.
    /// </returns>
    LineSegment3D<VectorT> Rotate(const Quaternion &qRotation) const
    {
        LineSegment3D<VectorT> auxLineSegment = *this;
        SPoint::Rotate(qRotation, rcast_z(&auxLineSegment, VectorT*), 2);
        return auxLineSegment;
    }

    /// <summary>
    /// Rotates the line segment.
    /// </summary>
    /// <param name="rotation">[IN] Matrix which contains the rotation to be applied.</param>
    /// <returns>
    /// The rotated segment.
    /// </returns>
    LineSegment3D<VectorT> Rotate(const RotationMatrix3x3 &rotation) const
    {
        LineSegment3D<VectorT> auxLineSegment = *this;
        SPoint::Rotate(rotation, rcast_z(&auxLineSegment, VectorT*), 2);
        return auxLineSegment;
    }

    /// <summary>
    /// Rotates the line segment using a pivot.
    /// </summary>
    /// <param name="qRotation">[IN] Quaternion that represents the rotation.</param>
    /// <param name="vPivot">[IN] Vector used as pivot for the rotation.</param>
    /// <returns>
    /// The rotated segment.
    /// </returns>
    LineSegment3D<VectorT> RotateWithPivot(const Quaternion &qRotation, const VectorT &vPivot) const
    {
        LineSegment3D<VectorT> auxLineSegment = *this;
        SPoint::RotateWithPivot(qRotation, vPivot, rcast_z(&auxLineSegment, VectorT*), 2);
        return auxLineSegment;
    }

    /// <summary>
    /// Rotates the line segment using a pivot.
    /// </summary>
    /// <param name="rotation">[IN] Matrix which contains the rotation to be applied.</param>
    /// <param name="vPivot">[IN] Vector used as pivot for the rotation.</param>
    /// <returns>
    /// The rotated segment.
    /// </returns>
    LineSegment3D<VectorT> RotateWithPivot(const RotationMatrix3x3 &rotation, const VectorT &vPivot) const
    {
        LineSegment3D<VectorT> auxLineSegment = *this;
        SPoint::RotateWithPivot(rotation, vPivot, rcast_z(&auxLineSegment, VectorT*), 2);
        return auxLineSegment;
    }

     /// <summary>
    /// Scales the line segment.
    /// </summary>
    /// <param name="vScale">[IN] Vector that contains the scale to be applied.</param>
    /// <returns>
    /// The scaled segment.
    /// </returns>
    LineSegment3D<VectorT> Scale(const Vector3 &vScale) const
    {
        LineSegment3D<VectorT> auxLineSegment = *this;
        SPoint::Scale(vScale, rcast_z(&auxLineSegment, VectorT*), 2);
        return auxLineSegment;
    }

     /// <summary>
    /// Scales the line segment.
    /// </summary>
    /// <param name="fScaleX">[IN] Scalar that contains the scale on X axis.</param>
    /// <param name="fScaleY">[IN] Scalar that contains the scale on Y axis.</param>
    /// <param name="fScaleZ">[IN] Scalar that contains the scale on Z axis.</param>
    /// <returns>
    /// The scaled segment.
    /// </returns>
    LineSegment3D<VectorT> Scale(const float_z fScaleX, const float_z fScaleY, const float_z fScaleZ) const
    {
        LineSegment3D<VectorT> auxLineSegment = *this;
        SPoint::Scale(fScaleX, fScaleY, fScaleZ, rcast_z(&auxLineSegment, VectorT*), 2);
        return auxLineSegment;
    }

     /// <summary>
    /// Scales the line segment.
    /// </summary>
    /// <param name="scale">[IN] Matrix which contains the scale to be applied.</param>
    /// <returns>
    /// The scaled segment.
    /// </returns>
    LineSegment3D<VectorT> Scale(const ScalingMatrix3x3& scale) const
    {
        LineSegment3D<VectorT> auxLineSegment = *this;
        SPoint::Scale(scale, rcast_z(&auxLineSegment, VectorT*), 2);
        return auxLineSegment;
    }

     /// <summary>
    /// Scales the line segment using a pivot.
    /// </summary>
    /// <param name="vScale">[IN] Vector that contains the scale to be applied.</param>
    /// <param name="vPivot">[IN] Vector used as pivot for the scale.</param>
    /// <returns>
    /// The scaled segment.
    /// </returns>
    LineSegment3D<VectorT> ScaleWithPivot(const Vector3 &vScale, const VectorT &vPivot) const
    {
        LineSegment3D<VectorT> auxLineSegment = *this;
        SPoint::ScaleWithPivot(vScale, vPivot, rcast_z(&auxLineSegment, VectorT*), 2);
        return auxLineSegment;
    }

     /// <summary>
    /// Scales the line segment using a pivot.
    /// </summary>
    /// <param name="fScaleX">[IN] Scalar that contains the scale on X axis.</param>
    /// <param name="fScaleY">[IN] Scalar that contains the scale on Y axis.</param>
    /// <param name="fScaleZ">[IN] Scalar that contains the scale on Z axis.</param>
    /// <param name="vPivot">[IN] Vector used as pivot for the scale.</param>
    /// <returns>
    /// The scaled segment.
    /// </returns>
    LineSegment3D<VectorT> ScaleWithPivot(const float_z fScaleX, const float_z fScaleY, const float_z fScaleZ, const VectorT &vPivot) const
    {
        LineSegment3D<VectorT> auxLineSegment = *this;
        SPoint::ScaleWithPivot(fScaleX, fScaleY, fScaleZ, vPivot, rcast_z(&auxLineSegment, VectorT*), 2);
        return auxLineSegment;
    }

     /// <summary>
    /// Scales the line segment using a pivot.
    /// </summary>
    /// <param name="scale">[IN] Matrix which contains the scale to be applied.</param>
    /// <param name="vPivot">[IN] Vector used as pivot for the scale.</param>
    /// <returns>
    /// The scaled segment.
    /// </returns>
    LineSegment3D<VectorT> ScaleWithPivot(const ScalingMatrix3x3& scale, const VectorT& vPivot) const
    {
        LineSegment3D<VectorT> auxLineSegment = *this;
        SPoint::ScaleWithPivot(scale, vPivot, rcast_z(&auxLineSegment, VectorT*), 2);
        return auxLineSegment;
    }

protected:

    /// <summary>
    /// Calculates if a point is inside the triangle provided applying barycentric technique.
    /// </summary>
    /// <typeparam name="VectorParamT">Allowed types: Vector3, Vector4.</typeparam>
    /// <param name="triangle">[IN] The triangle that may contain the point.</param>
    /// <param name="vPoint">[IN] The point that may be contained in the triangle.</param>
    /// <returns>
    /// True if the point is inside the triangle; False otherwise.
    /// </returns>
    template <class VectorParamT>
    bool PointInsideTriangle(const BaseTriangle<VectorParamT> &triangle, const VectorParamT &vPoint) const
    {
        // Compute vectors
        const VectorParamT &V0(triangle.C - triangle.A);
        const VectorParamT &V1(triangle.B - triangle.A);
        const VectorParamT &V2(vPoint - triangle.A);

        // Compute dot products
        const float_z &DOT_00 = V0.DotProduct(V0);
        const float_z &DOT_01 = V0.DotProduct(V1);
        const float_z &DOT_02 = V0.DotProduct(V2);
        const float_z &DOT_11 = V1.DotProduct(V1);
        const float_z &DOT_12 = V1.DotProduct(V2);

        // Compute barycentric coordinates
        const float_z &DENOM = DOT_00 * DOT_11 - DOT_01 * DOT_01;

        Z_ASSERT_WARNING(DENOM != SFloat::_0, "The variable \"DENOM\" must not equal zero, this will cause a division by zero");

        const float_z &INV_DENOM = SFloat::_1 / DENOM;

        const float_z &fU = (DOT_11 * DOT_02 - DOT_01 * DOT_12) * INV_DENOM;
        const float_z &fV = (DOT_00 * DOT_12 - DOT_01 * DOT_02) * INV_DENOM;

        // Check if point is in triangle
        return SFloat::IsGreaterOrEquals(fU, SFloat::_0) && 
               SFloat::IsGreaterOrEquals(fV, SFloat::_0) && 
               SFloat::IsLessOrEquals(fU + fV, SFloat::_1);
    }

    /// <summary>
    /// Calculates if a point is inside the convex quadrilateral provided by the vertex A, B, C and D,
    /// applying barycentric technique. Is supossed that quadrilateral vertex are consecutive.
    /// </summary>
    /// <typeparam name="VectorParamT">Allowed types: Vector3, Vector4.</typeparam>
    /// <param name="vA">[IN] The point A of the quadrilateral.</param>
    /// <param name="vB">[IN] The point B of the quadrilateral.</param>
    /// <param name="vC">[IN] The point C of the quadrilateral.</param>
    /// <param name="vD">[IN] The point D of the quadrilateral.</param>
    /// <param name="vPoint">[IN] The point that may be contained in the quadrilateral.</param>
    /// <returns>
    /// True if the point belongs to the quadrilateral; False otherwise.
    /// </returns>
    template <class VectorParamT>
    bool PointInsideQuadrilateral(const VectorParamT &vA, const VectorParamT &vB,
                                  const VectorParamT &vC, const VectorParamT &vD, const VectorParamT &vPoint) const
    {
        // Compute vectors
        const VectorParamT &V0(vC - vA);
        const VectorParamT &V1(vB - vA);
        const VectorParamT &V2(vPoint - vA);

        // Compute dot products
        const float_z &DOT_00 = V0.DotProduct(V0);
        const float_z &DOT_01 = V0.DotProduct(V1);
        const float_z &DOT_02 = V0.DotProduct(V2);
        const float_z &DOT_11 = V1.DotProduct(V1);
        const float_z &DOT_12 = V1.DotProduct(V2);

        // Compute barycentric coordinates
        const float_z &DENOM = DOT_00 * DOT_11 - DOT_01 * DOT_01;

        Z_ASSERT_WARNING(DENOM != SFloat::_0, "The variable \"DENOM\" must not equal zero, this will cause a division by zero");

        const float_z &INV_DENOM = SFloat::_1 / DENOM;

        const float_z &fU = (DOT_11 * DOT_02 - DOT_01 * DOT_12) * INV_DENOM;
        const float_z &fV = (DOT_00 * DOT_12 - DOT_01 * DOT_02) * INV_DENOM;

        // Check if point is in triangle
        if ( SFloat::IsGreaterOrEquals(fU, SFloat::_0) && 
             SFloat::IsGreaterOrEquals(fV, SFloat::_0) && 
             SFloat::IsLessOrEquals(fU + fV, SFloat::_1) )
            return true;

        // Compute new vector
        const VectorParamT &V3(vD - vA);

        // Compute new dot products
        const float_z &DOT_03 = V0.DotProduct(V3);
        const float_z &DOT_33 = V3.DotProduct(V3);
        const float_z &DOT_32 = V3.DotProduct(V2);

        // Compute new barycentric coordinates
        const float_z &DENOM2 = DOT_00 * DOT_33 - DOT_03 * DOT_03;

        Z_ASSERT_WARNING(DENOM2 != SFloat::_0, "The variable \"DENOM2\" must not equal zero, this will cause a division by zero");

        const float_z &INV_DENOM2 = SFloat::_1 / DENOM2;

        const float_z &fU2 = (DOT_33 * DOT_02 - DOT_03 * DOT_32) * INV_DENOM2;
        const float_z &fV2 = (DOT_00 * DOT_32 - DOT_03 * DOT_02) * INV_DENOM2;

        // Check if point is in triangle
        return SFloat::IsGreaterOrEquals(fU2, SFloat::_0) && 
               SFloat::IsGreaterOrEquals(fV2, SFloat::_0) && 
               SFloat::IsLessOrEquals(fU2 + fV2, SFloat::_1);
    }

    /// <summary>
    /// Calculates if two points are in the same side of a plane defined by 3 points.
    /// </summary>
    /// <typeparam name="VectorParamT">Allowed types: Vector3, Vector4.</typeparam>
    /// <param name="vPoint1">[IN] The first point to be checked.</param>
    /// <param name="vPoint2">[IN] The second point to be checked.</param>
    /// <param name="vA">[IN] One of the points that define the plane that divides the space in two parts.</param>
    /// <param name="vB">[IN] One of the points that define the plane that divides the space in two parts.</param>
    /// <param name="vC">[IN] One of the points that define the plane that divides the space in two parts.</param>
    /// <returns>
    /// True if both points lies in the same side of the plane.
    /// </returns>
    template <class VectorParamT>
    bool PointsInSameSideOfPlane(const VectorParamT &vPoint1, const VectorParamT &vPoint2,
                                 const VectorParamT &vA, const VectorParamT &vB, const VectorParamT &vC) const
    {
        Plane p(vA, vB, vC);

        const float_z &DIST_P1 = p.a * vPoint1.x + p.b * vPoint1.y + p.c * vPoint1.z + p.d;
        const float_z &DIST_P2 = p.a * vPoint2.x + p.b * vPoint2.y + p.c * vPoint2.z + p.d;

        return SFloat::IsGreaterOrEquals(DIST_P1 * DIST_P2, SFloat::_0);
    }

    // [TODO] Thund: This may be replaced with a call to Hexahedron::Contains. This would add a dependency to Hexahedron.
    
    /// <summary>
    /// Checks whether a point is contained or not in a hexahedron.
    /// </summary>
    /// <typeparam name="VectorParamT">Allowed types: Vector3, Vector4.</typeparam>
    /// <param name="hexahedron">[IN] The hexahedron where the point may be contained.</param>
    /// <param name="vPoint">[IN] The point to be checked.</param>
    /// <returns>
    /// True if the point is inside the hexahedron (if it lies in a face, it is considered as inside); False otherwise.
    /// </returns>
    template <class VectorParamT>
    bool PointInsideHexahedron(const BaseHexahedron<VectorParamT> &hexahedron, const VectorParamT &vPoint) const
    {
        return (PointsInSameSideOfPlane(vPoint, hexahedron.E, hexahedron.A, hexahedron.B, hexahedron.C) &&
                PointsInSameSideOfPlane(vPoint, hexahedron.A, hexahedron.E, hexahedron.F, hexahedron.G) &&
                PointsInSameSideOfPlane(vPoint, hexahedron.C, hexahedron.A, hexahedron.B, hexahedron.H) &&
                PointsInSameSideOfPlane(vPoint, hexahedron.A, hexahedron.B, hexahedron.C, hexahedron.G) &&
                PointsInSameSideOfPlane(vPoint, hexahedron.C, hexahedron.A, hexahedron.D, hexahedron.F) &&
                PointsInSameSideOfPlane(vPoint, hexahedron.A, hexahedron.C, hexahedron.D, hexahedron.F) );
    }

    /// <summary>
    /// Checks if a segment intersects a cuadrilateral.
    /// </summary>
    /// <remarks>
    /// It's supossed that A, B, C, D are consecutive vertices of a cuadrilateral.
    /// </remarks>
    /// <typeparam name="VectorParamT">Allowed types: Vector3, Vector4.</typeparam>
    /// <param name="segment">[IN] The segment whose intersections are to be calculated.</param>
    /// <param name="vA">[IN] The point A of the quadrilateral.</param>
    /// <param name="vB">[IN] The point B of the quadrilateral.</param>
    /// <param name="vC">[IN] The point C of the quadrilateral.</param>
    /// <param name="vD">[IN] The point D of the quadrilateral.</param>
    /// <returns>
    /// A boolean value that indicates whether the segment and the quadrilateral intersect or not.<br/>
    /// <br/>
    /// <b>True</b><br/>
    /// The segment and the quadrilateral intersect, including the following cases:
    /// - The line segment intersects with a vertex of the quadrilateral.
    /// - Only one endpoint is contained in the quadrilateral.
    /// - Only one endpoint is contained in an edge of the quadrilateral.
    /// - The line segment intersects with an edge of the quadrilateral, being both endpoints outside.
    /// - An endpoint coincide with a vertex of the quadrilateral.
    /// - The segment intersects with two edges of the quadrilateral.
    /// - Both endpoints belong to two different edges of the quadrilateral.
    /// - Both endpoints belong to the same edge of the quadrilateral.
    /// - The segment is contained in the quadrilateral (endpoints are not tangent to any edge).
    ///
    /// <b>False</b><br/>
    /// The line segment does not intersect with the quadrilateral.
    /// </returns>
    template <class VectorParamT>
    bool QuadrilateralIntersection(const LineSegment3D<VectorParamT> &segment,
                                   const VectorParamT &vA, const VectorParamT &vB,
                                   const VectorParamT &vC, const VectorParamT &vD) const
    {
        // Plane equation
        Plane auxP(vA, vB, vC);

        // Line Segment don't intersects the cuadrilateral plane.
        if (!segment.Intersection(auxP))
            return false;

        // If both end points satisfy plane equation, the line segment lies on plane
        const float_z &DOT1 = auxP.a * segment.B.x + auxP.b * segment.B.y + auxP.c * segment.B.z + auxP.d;
        const float_z &DOT2 = auxP.a * segment.A.x + auxP.b * segment.A.y + auxP.c * segment.A.z + auxP.d;

        if (SFloat::IsZero(DOT1) && SFloat::IsZero(DOT2))
        {
            if (segment.LineSegment<VectorParamT>::Intersection(LineSegment<VectorParamT> (vA, vB)) ||   // Both cuadrilateral and line segment are coplanar. If the line segment
                segment.LineSegment<VectorParamT>::Intersection(LineSegment<VectorParamT> (vB, vC)) ||   // intersects one of the edges of the cuadrilateral, then the line segment intersects the cuadrilateral.
                segment.LineSegment<VectorParamT>::Intersection(LineSegment<VectorParamT> (vC, vD)) ||
                segment.LineSegment<VectorParamT>::Intersection(LineSegment<VectorParamT> (vD, vA)))
                return true;
            else if ( PointInsideQuadrilateral(vA, vB, vC, vD, segment.A) ) // Now we check if segment is fully contained in the cuadrilateral
                return true;                                           // We only check "A" end point, since if "A" is inside, "B" must be inside too (see previus test).
            else
                return false;
        }

        Z_ASSERT_WARNING(SFloat::IsNotZero(DOT2 - DOT1), "The variables \"DOT1\" and \"DOT2\" must not be equal (maybe segment endpoints coincide), this will cause a division by zero");

        // The point which satisfies both line and plane equations.
        VectorParamT vAux = segment.A + (segment.B - segment.A) * DOT2/(DOT2 - DOT1);

        // For every edge, it tests if the intersection point is in the same side of each edge
        // than any other vextex (not of the edge). If it does, then it's inside the cuadrilateral,
        // otherwise it's outside.
        return PointInsideQuadrilateral(vA, vB, vC, vD, vAux);
    }
        
    /// <summary>
    /// Computes the intersection between a line segment and a cuadrilateral. 
    /// </summary>
    /// <remarks>
    /// It's supossed that A, B, C, D are consecutive vertices of a cuadrilateral.
    /// </remarks>
    /// <typeparam name="VectorParamT">Allowed types: Vector3, Vector4.</typeparam>
    /// <param name="segment">[IN] The segment whose intersections are to be calculated.</param>
    /// <param name="vA">[IN] The point A of the quadrilateral.</param>
    /// <param name="vB">[IN] The point B of the quadrilateral.</param>
    /// <param name="vC">[IN] The point C of the quadrilateral.</param>
    /// <param name="vD">[IN] The point D of the quadrilateral.</param>
    /// <param name="vIntersection">[OUT] The closest intersection point to the endpoint A.</param>
    /// <returns>
    /// An enumerated value that indicates how many intersections were found:<br/>
    /// <br/>
    /// <b>None</b><br/>
    /// There are no intersections.<br/>
    ///
    /// <b>One</b><br/>
    /// There is one intersection.<br/>
    /// - The line segment intersects with a vertex of the quadrilateral.
    /// - Only one endpoint is contained in the quadrilateral.
    /// - Only one endpoint is contained in an edge of the quadrilateral.
    /// - The line segment intersects with an edge of the quadrilateral, being both endpoints outside.
    /// - An endpoint coincide with a vertex of the quadrilateral.
    ///
    /// <b>Two</b><br/>
    /// There are two intersections.<br/>
    /// - The segment intersects with two edges of the quadrilateral.
    /// - Both endpoints belong to two different edges of the quadrilateral.
    /// - Both endpoints belong to the same edge of the quadrilateral.
    ///
    /// <b>Infinite</b><br/>
    /// There are infinite intersections.<br/>
    /// - The segment is contained in the quadrilateral (endpoints are not tangent to any edge).
    /// </returns>
    template <class VectorParamT>
    EIntersections QuadrilateralIntersectionPoint(const LineSegment3D<VectorParamT> &segment,
                                                   const VectorParamT &vA, const VectorParamT &vB,
                                                   const VectorParamT &vC, const VectorParamT &vD,
                                                   VectorParamT &vIntersection) const
    {
        VectorParamT vAux;
        return this->QuadrilateralIntersectionPoint(segment, vA, vB, vC, vD, vIntersection, vAux);
    }

    /// <summary>
    /// Computes the intersection between a line segment and a cuadrilateral. 
    /// </summary>
    /// <remarks>
    /// It's supossed that A, B, C, D are consecutive vertices of a cuadrilateral.
    /// </remarks>
    /// <typeparam name="VectorParamT">Allowed types: Vector3, Vector4.</typeparam>
    /// <param name="segment">[IN] The segment whose intersections are to be calculated.</param>
    /// <param name="vA">[IN] The point A of the quadrilateral.</param>
    /// <param name="vB">[IN] The point B of the quadrilateral.</param>
    /// <param name="vC">[IN] The point C of the quadrilateral.</param>
    /// <param name="vD">[IN] The point D of the quadrilateral.</param>
    /// <param name="vIntersection1">[OUT] The closest intersection point to the endpoint A.</param>
    /// <param name="vIntersection2">[OUT] The furthest intersection point to the endpoint B.</param>
    /// <returns>
    /// An enumerated value that indicates how many intersections were found:<br/>
    /// <br/>
    /// <b>None</b><br/>
    /// There are no intersections.<br/>
    ///
    /// <b>One</b><br/>
    /// There is one intersection.<br/>
    /// - The line segment intersects with a vertex of the quadrilateral.
    /// - Only one endpoint is contained in the quadrilateral.
    /// - Only one endpoint is contained in an edge of the quadrilateral.
    /// - The line segment intersects with an edge of the quadrilateral, being both endpoints outside.
    /// - An endpoint coincide with a vertex of the quadrilateral.
    ///
    /// <b>Two</b><br/>
    /// There are two intersections.<br/>
    /// - The segment intersects with two edges of the quadrilateral.
    /// - Both endpoints belong to two different edges of the quadrilateral.
    /// - Both endpoints belong to the same edge of the quadrilateral.
    ///
    /// <b>Infinite</b><br/>
    /// There are infinite intersections.<br/>
    /// - The segment is contained in the quadrilateral (endpoints are not tangent to any edge).
    /// </returns>
    template <class VectorParamT>
    EIntersections QuadrilateralIntersectionPoint(const LineSegment3D<VectorParamT> &segment,
                                                   const VectorParamT &vA, const VectorParamT &vB,
                                                   const VectorParamT &vC, const VectorParamT &vD,
                                                   VectorParamT &vIntersection1, VectorParamT &vIntersection2) const
    {
        // Plane equation
        Plane auxP(vA, vB, vC);
        VectorParamT vAux;

        const EIntersections &VALUE = segment.IntersectionPoint(auxP, vAux);

        if (VALUE == EIntersections::E_None) // Line Segment don't intersects the cuadrilateral plane.
            return EIntersections::E_None;
        else if (VALUE == EIntersections::E_One) // Line segment has one intersection with quadrilateral plane
        {
            if (PointInsideQuadrilateral(vA, vB, vC, vD, vAux))
            {
                vIntersection1 = vAux;
                return EIntersections::E_One;
            }
            else
                return EIntersections::E_None;
        }
        else // Line segment lies on plane (value == EIntersections::E_Infinite)
        {
            const bool &A_IS_INSIDE = PointInsideQuadrilateral(vA, vB, vC, vD, segment.A);
            const bool &B_IS_INSIDE = PointInsideQuadrilateral(vA, vB, vC, vD, segment.B);

            if (A_IS_INSIDE && B_IS_INSIDE) // Both line segment end points are inside quadrilateral.
            {
                // A or B are vertex
                const bool &A_IS_VERTEX = (segment.A == vA || segment.A == vB || segment.A == vC || segment.A == vD);
                const bool &B_IS_VERTEX = (segment.B == vA || segment.B == vB || segment.B == vC || segment.B == vD);

                if (A_IS_VERTEX && B_IS_VERTEX) // Both endpoints are vertices of quadrilateral
                {
                    vIntersection1 = segment.A;
                    vIntersection2 = segment.B;
                    return EIntersections::E_Two;
                }
                else if (A_IS_VERTEX) // Only A endpoint is a vertex of quadrilateral
                {
                    if (SFloat::IsZero(LineSegment<VectorParamT>(vA, vB).MinDistance(segment.B))) // B is in vAvB edge
                    {
                        if (segment.A == vA || segment.A == vB) // A and B are in the same edge
                        {
                            vIntersection1 = segment.A;
                            return EIntersections::E_One;
                        }
                        else
                        {
                            vIntersection1 = segment.A;
                            vIntersection2 = segment.B;
                            return EIntersections::E_Two;
                        }
                    }
                    else if (SFloat::IsZero(LineSegment<VectorParamT>(vB, vC).MinDistance(segment.B))) // B is in vBvC edge
                    {
                        if (segment.A == vB || segment.A == vC) // A and B are in the same edge
                        {
                            vIntersection1 = segment.A;
                            return EIntersections::E_One;
                        }
                        else
                        {
                            vIntersection1 = segment.A;
                            vIntersection2 = segment.B;
                            return EIntersections::E_Two;
                        }
                    }
                    else if (SFloat::IsZero(LineSegment<VectorParamT>(vC, vD).MinDistance(segment.B))) // B is in vCvD edge
                    {
                        if (segment.A == vC || segment.A == vD) // A and B are in the same edge
                        {
                            vIntersection1 = segment.A;
                            return EIntersections::E_One;
                        }
                        else
                        {
                            vIntersection1 = segment.A;
                            vIntersection2 = segment.B;
                            return EIntersections::E_Two;
                        }
                    }
                    else if (SFloat::IsZero(LineSegment<VectorParamT>(vD, vA).MinDistance(segment.B))) // B is in vDvA edge
                    {
                        if (segment.A == vD || segment.A == vA) // A and B are in the same edge
                        {
                            vIntersection1 = segment.A;
                            return EIntersections::E_One;
                        }
                        else
                        {
                            vIntersection1 = segment.A;
                            vIntersection2 = segment.B;
                            return EIntersections::E_Two;
                        }
                    }
                    else // B is not in an edge
                    {
                        vIntersection1 = segment.A;
                        return EIntersections::E_One;
                    }
                }
                else if (B_IS_VERTEX)
                {
                    if (SFloat::IsZero(LineSegment<VectorParamT>(vA, vB).MinDistance(segment.A))) // A is in vAvB edge
                    {
                        if (segment.B == vA || segment.B == vB) // A and B are in the same edge
                        {
                            vIntersection1 = segment.B;
                            return EIntersections::E_One;
                        }
                        else
                        {
                            vIntersection1 = segment.A;
                            vIntersection2 = segment.B;
                            return EIntersections::E_Two;
                        }
                    }
                    else if (SFloat::IsZero(LineSegment<VectorParamT>(vB, vC).MinDistance(segment.A))) // B is in vBvC edge
                    {
                        if (segment.B == vB || segment.B == vC) // A and B are in the same edge
                        {
                            vIntersection1 = segment.B;
                            return EIntersections::E_One;
                        }
                        else
                        {
                            vIntersection1 = segment.A;
                            vIntersection2 = segment.B;
                            return EIntersections::E_Two;
                        }
                    }
                    else if (SFloat::IsZero(LineSegment<VectorParamT>(vC, vD).MinDistance(segment.A))) // B is in vCvD edge
                    {
                        if (segment.B == vC || segment.B == vD) // A and B are in the same edge
                        {
                            vIntersection1 = segment.B;
                            return EIntersections::E_One;
                        }
                        else
                        {
                            vIntersection1 = segment.A;
                            vIntersection2 = segment.B;
                            return EIntersections::E_Two;
                        }
                    }
                    else if (SFloat::IsZero(LineSegment<VectorParamT>(vD, vA).MinDistance(segment.A))) // B is in vDvA edge
                    {
                        if (segment.B == vD || segment.B == vA) // A and B are in the same edge
                        {
                            vIntersection1 = segment.B;
                            return EIntersections::E_One;
                        }
                        else
                        {
                            vIntersection1 = segment.A;
                            vIntersection2 = segment.B;
                            return EIntersections::E_Two;
                        }
                    }
                    else
                    {
                        vIntersection1 = segment.B;
                        return EIntersections::E_One;
                    }
                }
                else // Neither A or B are vertices of quadrilateral
                {
                    if (SFloat::IsZero(LineSegment<VectorParamT>(vA, vB).MinDistance(segment.A))) // A is in vAvB edge (but not a vertex)
                    {
                        vIntersection1 = segment.A;

                        if (SFloat::IsZero(LineSegment<VectorParamT>(vA, vB).MinDistance(segment.B)) || // B is in vAvB edge (but not a vertex)
                            SFloat::IsZero(LineSegment<VectorParamT>(vB, vC).MinDistance(segment.B)) || // B is in other edge (but not a vertex)
                            SFloat::IsZero(LineSegment<VectorParamT>(vC, vD).MinDistance(segment.B)) ||
                            SFloat::IsZero(LineSegment<VectorParamT>(vD, vA).MinDistance(segment.B)))
                        {
                            
                            vIntersection2 = segment.B;
                            return EIntersections::E_Two;
                        }
                        else // B is not in an edge
                        {
                            return EIntersections::E_One;
                        }
                    }
                    else if (SFloat::IsZero(LineSegment<VectorParamT>(vB, vC).MinDistance(segment.A))) // A is in vBvC edge (but not a vertex)
                    {
                        vIntersection1 = segment.A;

                        if (SFloat::IsZero(LineSegment<VectorParamT>(vB, vC).MinDistance(segment.B)) || // B is in vBvC edge (but not a vertex)
                            SFloat::IsZero(LineSegment<VectorParamT>(vA, vB).MinDistance(segment.B)) || // B is in other edge (but not a vertex)
                            SFloat::IsZero(LineSegment<VectorParamT>(vC, vD).MinDistance(segment.B)) ||
                            SFloat::IsZero(LineSegment<VectorParamT>(vD, vA).MinDistance(segment.B)))
                        {
                            vIntersection2 = segment.B;
                            return EIntersections::E_Two;
                        }
                        else // B is not in an edge
                        {
                            return EIntersections::E_One;
                        }
                    }
                    else if (SFloat::IsZero(LineSegment<VectorParamT>(vC, vD).MinDistance(segment.A))) // A is in vCvD edge (but not a vertex)
                    {
                        vIntersection1 = segment.A;

                        if (SFloat::IsZero(LineSegment<VectorParamT>(vC, vD).MinDistance(segment.B)) || // B is in vCvD edge (but not a vertex)
                            SFloat::IsZero(LineSegment<VectorParamT>(vA, vB).MinDistance(segment.B)) || // B is in other edge (but not a vertex)
                            SFloat::IsZero(LineSegment<VectorParamT>(vB, vC).MinDistance(segment.B)) ||
                            SFloat::IsZero(LineSegment<VectorParamT>(vD, vA).MinDistance(segment.B)))
                        {
                            vIntersection2 = segment.B;
                            return EIntersections::E_Two;
                        }
                        else // B is not in an edge
                        {
                            return EIntersections::E_One;
                        }
                    }
                    else if (SFloat::IsZero(LineSegment<VectorParamT>(vD, vA).MinDistance(segment.A))) // A is in vDvA edge (but not a vertex)
                    {
                        vIntersection1 = segment.A;

                        if (SFloat::IsZero(LineSegment<VectorParamT>(vD, vA).MinDistance(segment.B)) || // B is in vDvA edge (but not a vertex)
                            SFloat::IsZero(LineSegment<VectorParamT>(vA, vB).MinDistance(segment.B)) || // B is in other edge (but not a vertex)
                            SFloat::IsZero(LineSegment<VectorParamT>(vB, vC).MinDistance(segment.B)) ||
                            SFloat::IsZero(LineSegment<VectorParamT>(vC, vD).MinDistance(segment.B)))
                        {
                            vIntersection2 = segment.B;
                            return EIntersections::E_Two;
                        }
                        else // B is not in an edge
                        {
                            return EIntersections::E_One;
                        }
                    }
                    else if (SFloat::IsZero(LineSegment<VectorParamT>(vD, vA).MinDistance(segment.A))) // A is in DA quad edge (but not a vertex)
                    {
                        vIntersection1 = segment.A;

                        if (SFloat::IsZero(LineSegment<VectorParamT>(vD, vA).MinDistance(segment.B)) || // B is in DA quad edge (but not a vertex)
                            SFloat::IsZero(LineSegment<VectorParamT>(vA, vB).MinDistance(segment.B)) || // B is in other edge (but not a vertex)
                            SFloat::IsZero(LineSegment<VectorParamT>(vB, vC).MinDistance(segment.B)) ||
                            SFloat::IsZero(LineSegment<VectorParamT>(vC, vD).MinDistance(segment.B)))
                        {
                            vIntersection2 = segment.B;
                            return EIntersections::E_Two;
                        }
                        else // B is not in an edge
                        {
                            return EIntersections::E_One;
                        }
                    }
                    else // A is not in an edge
                    {
                        if (SFloat::IsZero(LineSegment<VectorParamT>(vA, vB).MinDistance(segment.B)) || // B is in an edge (but not a vertex)
                            SFloat::IsZero(LineSegment<VectorParamT>(vB, vC).MinDistance(segment.B)) ||
                            SFloat::IsZero(LineSegment<VectorParamT>(vC, vD).MinDistance(segment.B)) ||
                            SFloat::IsZero(LineSegment<VectorParamT>(vD, vA).MinDistance(segment.B)))
                        {
                            vIntersection1 = segment.B;
                            return EIntersections::E_One;
                        }
                        else // B is not in an edge, so A and B are inside the quadrilateral
                            return EIntersections::E_Infinite;
                    }
                }
            }
            else if (!A_IS_INSIDE && !B_IS_INSIDE) // Both line segment end points are outside quadrilateral.
            {
                VectorParamT vPointAB, vPointBC, vPointCD, vPointDA;

                EIntersections value2AB = segment.IntersectionPoint(LineSegment3D<VectorParamT>(vA, vB), vPointAB);

                if (value2AB == EIntersections::E_Infinite) // Line segment contains AB edge of quadrilateral
                {
                    if  ( (vA - segment.A).GetSquaredLength() < (vB - segment.A).GetSquaredLength() ) // Returns closest point to A end point of line segment
                    {
                        vIntersection1 = vA;
                        vIntersection2 = vB;
                    }
                    else
                    {
                        vIntersection1 = vB;
                        vIntersection2 = vA;
                    }
                    return EIntersections::E_Two;
                }

                // Line segment contains BC edge of quadrilateral
                EIntersections value2BC = segment.IntersectionPoint(LineSegment3D<VectorParamT>(vB, vC), vPointBC);
                if (value2BC == EIntersections::E_Infinite)
                {
                    if  ( (vB - segment.A).GetSquaredLength() < (vC - segment.A).GetSquaredLength() ) // Returns closest point to A end point of line segment
                    {
                        vIntersection1 = vB;
                        vIntersection2 = vC;
                    }
                    else
                    {
                        vIntersection1 = vC;
                        vIntersection2 = vB;
                    }
                    return EIntersections::E_Two;
                }

                // Line segment contains CA edge of quadrilateral
                EIntersections value2CD = segment.IntersectionPoint(LineSegment3D<VectorParamT>(vC, vD), vPointCD);
                if (value2CD == EIntersections::E_Infinite)
                {
                    if  ( (vC - segment.A).GetSquaredLength() < (vD - segment.A).GetSquaredLength() ) // Returns closest point to A end point of line segment
                    {
                        vIntersection1 = vC;
                        vIntersection2 = vD;
                    }
                    else
                    {
                        vIntersection1 = vD;
                        vIntersection2 = vC;
                    }
                    return EIntersections::E_Two;
                }

                // Line segment contains DA edge of quadrilateral
                EIntersections value2DA = segment.IntersectionPoint(LineSegment3D<VectorParamT>(vD, vA), vPointDA);
                if (value2DA == EIntersections::E_Infinite)
                {
                    if  ( (vD - segment.A).GetSquaredLength() < (vA - segment.A).GetSquaredLength() ) // Returns closest point to A end point of line segment
                    {
                        vIntersection1 = vD;
                        vIntersection2 = vA;
                    }
                    else
                    {
                        vIntersection1 = vA;
                        vIntersection2 = vD;
                    }
                    return EIntersections::E_Two;
                }

                if (value2AB == EIntersections::E_One) // Line segment intersects AB edge of quadrilateral
                {
                    if (value2BC == EIntersections::E_One) // Line segment intersects BC edge of quadrilateral
                    {
                        if (vPointAB == vPointBC) // Are the same point
                        {
                            if (value2CD == EIntersections::E_One) // Line segment intersects CD edge of quadrilateral
                            {
                                // Returns closest point to A end point of line segment
                                if  ( (vPointAB - segment.A).GetSquaredLength() < (vPointCD - segment.A).GetSquaredLength() )
                                {
                                    vIntersection1 = vPointAB;
                                    vIntersection2 = vPointCD;
                                }
                                else
                                {
                                    vIntersection1 = vPointCD;
                                    vIntersection2 = vPointAB;
                                }

                                return EIntersections::E_Two;
                            }
                            else if (value2DA == EIntersections::E_One) // Line segment intersects DA edge of quadrilateral
                            {
                                // Returns closest point to A end point of line segment
                                if  ( (vPointAB - segment.A).GetSquaredLength() < (vPointDA - segment.A).GetSquaredLength() )
                                {
                                    vIntersection1 = vPointAB;
                                    vIntersection2 = vPointDA;
                                }
                                else
                                {
                                    vIntersection1 = vPointDA;
                                    vIntersection2 = vPointAB;
                                }

                                return EIntersections::E_Two;
                            }
                            else
                            {
                                vIntersection1 = vPointAB;
                                return EIntersections::E_One;
                            }
                        }
                        else
                        {
                            if  ( (vPointAB - segment.A).GetSquaredLength() < (vPointBC - segment.A).GetSquaredLength() ) // Returns closest point to A end point of line segment
                            {
                                vIntersection1 = vPointAB;
                                vIntersection2 = vPointBC;
                            }
                            else
                            {
                                vIntersection1 = vPointBC;
                                vIntersection2 = vPointAB;
                            }
                            return EIntersections::E_Two;
                        }
                    }
                    else if (value2CD == EIntersections::E_One) // Line segment intersects CD edge of quadrilateral
                    {
                        // Returns closest point to A end point of line segment
                        if  ( (vPointAB - segment.A).GetSquaredLength() < (vPointCD - segment.A).GetSquaredLength() )
                        {
                            vIntersection1 = vPointAB;
                            vIntersection2 = vPointCD;
                        }
                        else
                        {
                            vIntersection1 = vPointCD;
                            vIntersection2 = vPointAB;
                        }

                        return EIntersections::E_Two;
                    }
                    else if (value2DA == EIntersections::E_One) // Line segment intersects DA edge of quadrilateral
                    {
                        if (vPointAB == vPointDA) // Are the same point
                        {
                            vIntersection1 = vPointAB;
                            return EIntersections::E_One;
                        }
                        else
                        {
                            // Returns closest point to A end point of line segment
                            if  ( (vPointAB - segment.A).GetSquaredLength() < (vPointDA - segment.A).GetSquaredLength() )
                            {
                                vIntersection1 = vPointAB;
                                vIntersection2 = vPointDA;
                            }
                            else
                            {
                                vIntersection1 = vPointDA;
                                vIntersection2 = vPointAB;
                            }

                            return EIntersections::E_Two;
                        }
                    }
                }
                else if (value2BC == EIntersections::E_One) // Line segment intersects BC edge of quadrilateral
                {
                    if (value2CD == EIntersections::E_One) // Line segment intersects CA edge of quadrilateral
                    {
                        if (vPointBC == vPointCD) // Are the same point
                        {
                            if (value2DA ==EIntersections::E_One) // Line segment intersects DA edge of quadrilateral
                            {
                                // Returns closest point to A end point of line segment
                                if  ( (vPointBC - segment.A).GetSquaredLength() < (vPointDA - segment.A).GetSquaredLength() )
                                {
                                    vIntersection1 = vPointBC;
                                    vIntersection2 = vPointDA;
                                }
                                else
                                {
                                    vIntersection1 = vPointDA;
                                    vIntersection2 = vPointBC;
                                }

                                return EIntersections::E_Two;
                            }
                            else
                            {
                                vIntersection1 = vPointBC;
                                return EIntersections::E_One;
                            }
                        }
                        else
                        {
                            // Returns closest point to A end point of line segment
                            if  ( (vPointBC - segment.A).GetSquaredLength() < (vPointCD - segment.A).GetSquaredLength() )
                            {
                                vIntersection1 = vPointBC;
                                vIntersection2 = vPointCD;
                            }
                            else
                            {
                                vIntersection1 = vPointCD;
                                vIntersection2 = vPointBC;
                            }

                            return EIntersections::E_Two;
                        }
                    }
                    else if (value2DA ==EIntersections::E_One)
                    {
                        // Returns closest point to A end point of line segment
                        if  ( (vPointBC - segment.A).GetSquaredLength() < (vPointDA - segment.A).GetSquaredLength() )
                        {
                            vIntersection1 = vPointBC;
                            vIntersection2 = vPointDA;
                        }
                        else
                        {
                            vIntersection1 = vPointDA;
                            vIntersection2 = vPointBC;
                        }

                        return EIntersections::E_Two;
                    }
                }
                else if (value2CD == EIntersections::E_One) // Line segment intersects CD edge of quadrilateral
                {
                    if (value2DA == EIntersections::E_One) // Line segment intersects DA edge of quadrilateral
                    {
                        if (vPointCD == vPointDA) // Are the same point
                        {
                            vIntersection1 = vPointCD;
                            return EIntersections::E_One;
                        }
                        else
                        {
                            // Returns closest point to A end point of line segment
                            if  ( (vPointCD - segment.A).GetSquaredLength() < (vPointDA - segment.A).GetSquaredLength() )
                            {
                                vIntersection1 = vPointCD;
                                vIntersection2 = vPointDA;
                            }
                            else
                            {
                                vIntersection1 = vPointDA;
                                vIntersection2 = vPointCD;
                            }

                            return EIntersections::E_Two;
                        }
                    }
                }
                else                    // line segment must intersects none, two or three edges, never only one.
                    return EIntersections::E_None; // There are no intersections.
            }
            else // one line segment end point is inside and the other one is outside triangle.
            {
                if (A_IS_INSIDE) // segment.A is inside quadrilateral
                {
                    if (segment.A == vA) // segment.A is vA vertex
                    {
                        vIntersection1 = segment.A;

                        // segment intersects opposite edges
                        EIntersections value2 = segment.IntersectionPoint(LineSegment3D<VectorParamT>(vB, vC), vAux);
                        if (value2 == EIntersections::E_One)
                        {
                            vIntersection2 = vAux;
                            return EIntersections::E_Two;
                        }
                        else if ((value2 = segment.IntersectionPoint(LineSegment3D<VectorParamT>(vC, vD), vAux)) == EIntersections::E_One)
                        {
                            vIntersection2 = vAux;
                            return EIntersections::E_Two;
                        }
                        else
                            return EIntersections::E_One;
                    }
                    else if (segment.A == vB) // segment.A is vB vertex
                    {
                        vIntersection1 = segment.A;

                        // segment intersects opposite edges
                        EIntersections value2 = segment.IntersectionPoint(LineSegment3D<VectorParamT>(vC, vD), vAux);
                        if (value2 == EIntersections::E_One)
                        {
                            vIntersection2 = vAux;
                            return EIntersections::E_Two;
                        }
                        else if ((value2 = segment.IntersectionPoint(LineSegment3D<VectorParamT>(vD, vA), vAux)) == EIntersections::E_One)
                        {
                            vIntersection2 = vAux;
                            return EIntersections::E_Two;
                        }
                        else
                            return EIntersections::E_One;
                    }
                    else if (segment.A == vC) // segment.A is vC vertex
                    {
                        vIntersection1 = segment.A;

                        // segment intersects opposite edges
                        EIntersections value2 = segment.IntersectionPoint(LineSegment3D<VectorParamT>(vD, vA), vAux);
                        if (value2 == EIntersections::E_One)
                        {
                            vIntersection2 = vAux;
                            return EIntersections::E_Two;
                        }
                        else if ((value2 = segment.IntersectionPoint(LineSegment3D<VectorParamT>(vA, vB), vAux)) == EIntersections::E_One)
                        {
                            vIntersection2 = vAux;
                            return EIntersections::E_Two;
                        }
                        else
                            return EIntersections::E_One;
                    }
                    else if (segment.A == vD) // segment.A is vD vertex
                    {
                        vIntersection1 = segment.A;

                        // segment intersects opposite edges
                        EIntersections value2 = segment.IntersectionPoint(LineSegment3D<VectorParamT>(vA, vB), vAux);
                        if (value2 == EIntersections::E_One)
                        {
                            vIntersection2 = vAux;
                            return EIntersections::E_Two;
                        }
                        else if ((value2 = segment.IntersectionPoint(LineSegment3D<VectorParamT>(vB, vC), vAux)) == EIntersections::E_One)
                        {
                            vIntersection2 = vAux;
                            return EIntersections::E_Two;
                        }
                        else
                            return EIntersections::E_One;
                    }
                    else if (SFloat::IsZero(LineSegment<VectorParamT>(vA, vB).MinDistance(segment.A))) // segment.A is in vAvB edge (but not a vertex)
                    {
                        vIntersection1 = segment.A;

                        // segment intersects other edges
                        EIntersections value2 = segment.IntersectionPoint(LineSegment3D<VectorParamT>(vB, vC), vAux);
                        if (value2 == EIntersections::E_One)
                        {
                            if (vAux == vB || vAux == vC) // Both intersections are in the same edge
                                return EIntersections::E_One;

                            vIntersection2 = vAux;
                            return EIntersections::E_Two;
                        }
                        else if ((value2 = segment.IntersectionPoint(LineSegment3D<VectorParamT>(vC, vD), vAux)) == EIntersections::E_One)
                        {
                            if (vAux == vC || vAux == vD) // Both intersections are in the same edge
                                return EIntersections::E_One;

                            vIntersection2 = vAux;
                            return EIntersections::E_Two;
                        }
                        else if ((value2 = segment.IntersectionPoint(LineSegment3D<VectorParamT>(vD, vA), vAux)) == EIntersections::E_One)
                        {
                            if (vAux == vD || vAux == vA) // Both intersections are in the same edge
                                return EIntersections::E_One;

                            vIntersection2 = vAux;
                            return EIntersections::E_Two;
                        }
                        else
                            return EIntersections::E_One;
                    }
                    else if (SFloat::IsZero(LineSegment<VectorParamT>(vB, vC).MinDistance(segment.A))) // segment.A is in vBvC edge (but not a vertex)
                    {
                        vIntersection1 = segment.A;

                         // segment intersects other edges
                        EIntersections value2 = segment.IntersectionPoint(LineSegment3D<VectorParamT>(vA, vB), vAux);
                        if (value2 == EIntersections::E_One)
                        {
                            if (vAux == vA || vAux == vB) // Both intersections are in the same edge
                                return EIntersections::E_One;

                            vIntersection2 = vAux;
                            return EIntersections::E_Two;
                        }
                        else if ((value2 = segment.IntersectionPoint(LineSegment3D<VectorParamT>(vC, vD), vAux)) == EIntersections::E_One)
                        {
                            if (vAux == vC || vAux == vD) // Both intersections are in the same edge
                                return EIntersections::E_One;

                            vIntersection2 = vAux;
                            return EIntersections::E_Two;
                        }
                        else if ((value2 = segment.IntersectionPoint(LineSegment3D<VectorParamT>(vD, vA), vAux)) == EIntersections::E_One)
                        {
                            if (vAux == vD || vAux == vA) // Both intersections are in the same edge
                                return EIntersections::E_One;

                            vIntersection2 = vAux;
                            return EIntersections::E_Two;
                        }
                        else
                            return EIntersections::E_One;
                    }
                    else if (SFloat::IsZero(LineSegment<VectorParamT>(vC, vD).MinDistance(segment.A))) // segment.A is in vCvD edge (but not a vertex)
                    {
                        vIntersection1 = segment.A;

                         // segment intersects other edges
                        EIntersections value2 = segment.IntersectionPoint(LineSegment3D<VectorParamT>(vB, vC), vAux);
                        if (value2 == EIntersections::E_One)
                        {
                            if (vAux == vB || vAux == vC) // Both intersections are in the same edge
                                return EIntersections::E_One;

                            vIntersection2 = vAux;
                            return EIntersections::E_Two;
                        }
                        else if ((value2 = segment.IntersectionPoint(LineSegment3D<VectorParamT>(vA, vB), vAux)) == EIntersections::E_One)
                        {
                            if (vAux == vA || vAux == vB) // Both intersections are in the same edge
                                return EIntersections::E_One;

                            vIntersection2 = vAux;
                            return EIntersections::E_Two;
                        }
                        else if ((value2 = segment.IntersectionPoint(LineSegment3D<VectorParamT>(vD, vA), vAux)) == EIntersections::E_One)
                        {
                            if (vAux == vD || vAux == vA) // Both intersections are in the same edge
                                return EIntersections::E_One;

                            vIntersection2 = vAux;
                            return EIntersections::E_Two;
                        }
                        else
                            return EIntersections::E_One;
                    }
                    else if (SFloat::IsZero(LineSegment<VectorParamT>(vD, vA).MinDistance(segment.A))) // segment.A is in vDvA edge (but not a vertex)
                    {
                        vIntersection1 = segment.A;

                         // segment intersects other edges
                        EIntersections value2 = segment.IntersectionPoint(LineSegment3D<VectorParamT>(vB, vC), vAux);
                        if (value2 == EIntersections::E_One)
                        {
                            if (vAux == vB || vAux == vC) // Both intersections are in the same edge
                                return EIntersections::E_One;

                            vIntersection2 = vAux;
                            return EIntersections::E_Two;
                        }
                        else if ((value2 = segment.IntersectionPoint(LineSegment3D<VectorParamT>(vC, vD), vAux)) == EIntersections::E_One)
                        {
                            if (vAux == vC || vAux == vD) // Both intersections are in the same edge
                                return EIntersections::E_One;

                            vIntersection2 = vAux;
                            return EIntersections::E_Two;
                        }
                        else if ((value2 = segment.IntersectionPoint(LineSegment3D<VectorParamT>(vA, vB), vAux)) == EIntersections::E_One)
                        {
                            if (vAux == vA || vAux == vB) // Both intersections are in the same edge
                                return EIntersections::E_One;

                            vIntersection2 = vAux;
                            return EIntersections::E_Two;
                        }
                        else
                            return EIntersections::E_One;
                    }
                    else // segment.A is strictly inside quadrilateral: is not in a vertex or edge.
                    {
                        EIntersections value2 = segment.IntersectionPoint(LineSegment3D<VectorParamT>(vA, vB), vAux);
                        if (value2 == EIntersections::E_One)
                            vIntersection1 = vAux;
                        else if ((value2 = segment.IntersectionPoint(LineSegment3D<VectorParamT>(vB, vC), vAux)) == EIntersections::E_One)
                            vIntersection1 = vAux;
                        else if ((value2 = segment.IntersectionPoint(LineSegment3D<VectorParamT>(vC, vD), vAux))== EIntersections::E_One)
                            vIntersection1 = vAux;
                        else if ((value2 = segment.IntersectionPoint(LineSegment3D<VectorParamT>(vD, vA), vAux))== EIntersections::E_One)
                            vIntersection1 = vAux;

                        return EIntersections::E_One;
                    }
                }
                else // segment.B is inside quadrilateral (A is outside)
                {
                    if (segment.B == vA) // segment.B is vA vertex
                    {
                        // segment intersects opposite edges
                        EIntersections value2 = segment.IntersectionPoint(LineSegment3D<VectorParamT>(vB, vC), vAux);
                        if (value2 == EIntersections::E_One)
                        {
                            vIntersection1 = vAux;
                            vIntersection2 = segment.B;
                            return EIntersections::E_Two;
                        }
                        else if ((value2 = segment.IntersectionPoint(LineSegment3D<VectorParamT>(vC, vD), vAux)) == EIntersections::E_One)
                        {
                            vIntersection1 = vAux;
                            vIntersection2 = segment.B;
                            return EIntersections::E_Two;
                        }
                        else
                        {
                            vIntersection1 = segment.B;
                            return EIntersections::E_One;
                        }
                    }
                    else if (segment.B == vB) // segment.B is vB vertex
                    {
                        // segment intersects opposite edges
                        EIntersections value2 = segment.IntersectionPoint(LineSegment3D<VectorParamT>(vC, vD), vAux);
                        if (value2 == EIntersections::E_One)
                        {
                            vIntersection1 = vAux;
                            vIntersection2 = segment.B;
                            return EIntersections::E_Two;
                        }
                        else if ((value2 = segment.IntersectionPoint(LineSegment3D<VectorParamT>(vD, vA), vAux)) == EIntersections::E_One)
                        {
                            vIntersection1 = vAux;
                            vIntersection2 = segment.B;
                            return EIntersections::E_Two;
                        }
                        else
                        {
                            vIntersection1 = segment.B;
                            return EIntersections::E_One;
                        }
                    }
                    else if (segment.B == vC) // segment.B is vC vertex
                    {
                        // segment intersects opposite edges
                        EIntersections value2 = segment.IntersectionPoint(LineSegment3D<VectorParamT>(vD, vA), vAux);
                        if (value2 == EIntersections::E_One)
                        {
                            vIntersection1 = vAux;
                            vIntersection2 = segment.B;
                            return EIntersections::E_Two;
                        }
                        else if ((value2 = segment.IntersectionPoint(LineSegment3D<VectorParamT>(vA, vB), vAux)) == EIntersections::E_One)
                        {
                            vIntersection1 = vAux;
                            vIntersection2 = segment.B;
                            return EIntersections::E_Two;
                        }
                        else
                        {
                            vIntersection1 = segment.B;
                            return EIntersections::E_One;
                        }
                    }
                    else if (segment.B == vD) // segment.B is vB vertex
                    {
                        // segment intersects opposite edges
                        EIntersections value2 = segment.IntersectionPoint(LineSegment3D<VectorParamT>(vA, vB), vAux);
                        if (value2 == EIntersections::E_One)
                        {
                            vIntersection1 = vAux;
                            vIntersection2 = segment.B;
                            return EIntersections::E_Two;
                        }
                        else if ((value2 = segment.IntersectionPoint(LineSegment3D<VectorParamT>(vB, vC), vAux)) == EIntersections::E_One)
                        {
                            vIntersection1 = vAux;
                            vIntersection2 = segment.B;
                            return EIntersections::E_Two;
                        }
                        else
                        {
                            vIntersection1 = segment.B;
                            return EIntersections::E_One;
                        }
                    }
                    else if (SFloat::IsZero(LineSegment<VectorParamT>(vA, vB).MinDistance(segment.B))) // segment.B is in vAvB edge (but not a vertex)
                    {
                        // segment intersects the other edges
                        EIntersections value2 = segment.IntersectionPoint(LineSegment3D<VectorParamT>(vB, vC), vAux);
                        if (value2 == EIntersections::E_One)
                        {
                            vIntersection1 = vAux;

                            if (vAux == vB || vAux == vC) // Both intersections are in the same edge
                                return EIntersections::E_One;

                            vIntersection2 = segment.B;
                            return EIntersections::E_Two;
                        }
                        else if ((value2 = segment.IntersectionPoint(LineSegment3D<VectorParamT>(vC, vD), vAux)) == EIntersections::E_One)
                        {
                            vIntersection1 = vAux;

                            if (vAux == vC || vAux == vD) // Both intersections are in the same edge
                                return EIntersections::E_One;

                            vIntersection2 = segment.B;
                            return EIntersections::E_Two;
                        }
                        else if ((value2 = segment.IntersectionPoint(LineSegment3D<VectorParamT>(vD, vA), vAux)) == EIntersections::E_One)
                        {
                            vIntersection1 = vAux;

                            if (vAux == vD || vAux == vA) // Both intersections are in the same edge
                                return EIntersections::E_One;

                            vIntersection2 = segment.B;
                            return EIntersections::E_Two;
                        }
                        else // There is no other intersection
                        {
                            vIntersection1 = segment.B;
                            return EIntersections::E_One;
                        }
                    }
                    else if (SFloat::IsZero(LineSegment<VectorParamT>(vB, vC).MinDistance(segment.B))) // segment.B is in vBvC edge (but not a vertex)
                    {
                        // segment intersects the other edges
                        EIntersections value2 = segment.IntersectionPoint(LineSegment3D<VectorParamT>(vA, vB), vAux);
                        if (value2 == EIntersections::E_One)
                        {
                            vIntersection1 = vAux;

                            if (vAux == vA || vAux == vB) // Both intersections are in the same edge
                                return EIntersections::E_One;

                            vIntersection2 = segment.B;
                            return EIntersections::E_Two;
                        }
                        else if ((value2 = segment.IntersectionPoint(LineSegment3D<VectorParamT>(vC, vD), vAux)) == EIntersections::E_One)
                        {
                            vIntersection1 = vAux;

                            if (vAux == vC || vAux == vD) // Both intersections are in the same edge
                                return EIntersections::E_One;

                            vIntersection2 = segment.B;
                            return EIntersections::E_Two;
                        }
                        else if ((value2 = segment.IntersectionPoint(LineSegment3D<VectorParamT>(vD, vA), vAux)) == EIntersections::E_One)
                        {
                            vIntersection1 = vAux;

                            if (vAux == vD || vAux == vA) // Both intersections are in the same edge
                                return EIntersections::E_One;

                            vIntersection2 = segment.B;
                            return EIntersections::E_Two;
                        }
                        else // There is no other intersection
                        {
                            vIntersection1 = segment.B;
                            return EIntersections::E_One;
                        }
                    }
                    else if (SFloat::IsZero(LineSegment<VectorParamT>(vC, vD).MinDistance(segment.B))) // segment.B is in vCvD edge (but not a vertex)
                    {
                        // segment intersects the other edges
                        EIntersections value2 = segment.IntersectionPoint(LineSegment3D<VectorParamT>(vB, vC), vAux);
                        if (value2 == EIntersections::E_One)
                        {
                            vIntersection1 = vAux;

                            if (vAux == vB || vAux == vC) // Both intersections are in the same edge
                                return EIntersections::E_One;

                            vIntersection2 = segment.B;
                            return EIntersections::E_Two;
                        }
                        else if ((value2 = segment.IntersectionPoint(LineSegment3D<VectorParamT>(vA, vB), vAux)) == EIntersections::E_One)
                        {
                            vIntersection1 = vAux;

                            if (vAux == vA || vAux == vB) // Both intersections are in the same edge
                                return EIntersections::E_One;

                            vIntersection2 = segment.B;
                            return EIntersections::E_Two;
                        }
                        else if ((value2 = segment.IntersectionPoint(LineSegment3D<VectorParamT>(vD, vA), vAux)) == EIntersections::E_One)
                        {
                            vIntersection1 = vAux;

                            if (vAux == vD || vAux == vA) // Both intersections are in the same edge
                                return EIntersections::E_One;

                            vIntersection2 = segment.B;
                            return EIntersections::E_Two;
                        }
                        else // There is no other intersection
                        {
                            vIntersection1 = segment.B;
                            return EIntersections::E_One;
                        }
                    }
                    else if (SFloat::IsZero(LineSegment<VectorParamT>(vD, vA).MinDistance(segment.B))) // segment.B is in vDvA edge (but not a vertex)
                    {
                        // segment intersects the other edges
                        EIntersections value2 = segment.IntersectionPoint(LineSegment3D<VectorParamT>(vB, vC), vAux);
                        if (value2 == EIntersections::E_One)
                        {
                            vIntersection1 = vAux;

                            if (vAux == vB || vAux == vC) // Both intersections are in the same edge
                                return EIntersections::E_One;

                            vIntersection2 = segment.B;
                            return EIntersections::E_Two;
                        }
                        else if ((value2 = segment.IntersectionPoint(LineSegment3D<VectorParamT>(vC, vD), vAux)) == EIntersections::E_One)
                        {
                            vIntersection1 = vAux;

                            if (vAux == vC || vAux == vD) // Both intersections are in the same edge
                                return EIntersections::E_One;

                            vIntersection2 = segment.B;
                            return EIntersections::E_Two;
                        }
                        else if ((value2 = segment.IntersectionPoint(LineSegment3D<VectorParamT>(vA, vB), vAux)) == EIntersections::E_One)
                        {
                            vIntersection1 = vAux;

                            if (vAux == vA || vAux == vB) // Both intersections are in the same edge
                                return EIntersections::E_One;

                            vIntersection2 = segment.B;
                            return EIntersections::E_Two;
                        }
                        else // There is no other intersection
                        {
                            vIntersection1 = segment.B;
                            return EIntersections::E_One;
                        }
                    }
                    else // segment.B is strictly inside quadrilateral: is not in a vertex or edge.
                    {
                        EIntersections value2 = segment.IntersectionPoint(LineSegment3D<VectorParamT>(vA, vB), vAux);
                        if (value2 == EIntersections::E_One)
                            vIntersection1 = vAux;
                        else if ((value2 = segment.IntersectionPoint(LineSegment3D<VectorParamT>(vB, vC), vAux)) == EIntersections::E_One)
                            vIntersection1 = vAux;
                        else if ((value2 = segment.IntersectionPoint(LineSegment3D<VectorParamT>(vC, vD), vAux)) == EIntersections::E_One)
                            vIntersection1 = vAux;
                        else if ((value2 = segment.IntersectionPoint(LineSegment3D<VectorParamT>(vD, vA), vAux)) == EIntersections::E_One)
                            vIntersection1 = vAux;

                        return EIntersections::E_One;
                    }
                }
            }
        }

        // Something was wrong, this line should be never reached
        Z_ASSERT_WARNING(false, "Something went really wrong, this code branch must never be reached");

        return EIntersections::E_None;
    }
};


// SPECIALIZATION EXPORTATIONS
// -----------------------------
#ifdef Z_MATH_TEMPLATE_SPECIALIZATION_SYMBOLS

template class Z_LAYER_MATH_SYMBOLS LineSegment3D<Vector3>;
template class Z_LAYER_MATH_SYMBOLS LineSegment3D<Vector4>;

#endif // Z_MATH_TEMPLATE_SPECIALIZATION_SYMBOLS

} // namespace z


#endif // __LINESEGMENT3D__
