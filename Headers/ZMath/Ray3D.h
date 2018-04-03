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

#ifndef __RAY3D__
#define __RAY3D__

#include "Ray.h"
#include "ZMath/Vector3.h"
#include "LineSegment.h"
#include "Plane.h"
#include "ESpaceRelation.h"
#include "BaseOrb.h"
#include "BaseTriangle.h"
#include "BaseHexahedron.h"
#include "SPoint.h"
#include "ZMath/Vector3.h"
#include "ZMath/Vector4.h"
#include "TransformationMatrix.h"



namespace z
{

/// <summary>
/// Represents a ray in 3D space, which consists of a origin point or position, and a direction.
/// </summary>
/// <remarks>
/// The direction symbolizes a line with only one end (which coincides with the origin) and that extends to the infinite.
/// </remarks>
/// <typeparam name="VectorT">Allowed types: Vector3, Vector4.</typeparam>
template <class VectorT>
class Ray3D : public Ray<VectorT, Vector3>
{
    // BASE CLASS USINGS
    // ------------------
public:

    using Ray<VectorT, Vector3>::Intersection;
    using Ray<VectorT, Vector3>::IntersectionPoint;


    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor.
    /// </summary>
    Ray3D()
    {
    }

    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="ray">[IN] The 3D ray from which we want to create a copy in the resident 3D ray.</param>
    Ray3D(const Ray3D<VectorT> &ray) : Ray<VectorT, Vector3>(ray)
    {
    }

    /// <summary>
    /// Base type constructor.
    /// </summary>
    /// <param name="ray">[IN] The 3D ray in which we want resident 3D ray to be based.</param>
    Ray3D(const BaseRay<VectorT, Vector3> &ray) : Ray<VectorT, Vector3>(ray)
    {
    }

    /// <summary>
    /// Constructor that receives the ray's position and direction.
    /// </summary>
    /// <remarks>
    /// The direction vector must be normalized to construct the ray properly.
    /// </remarks>
    /// <param name="vOrigin">[IN] Ray's position.</param>
    /// <param name="vDirection">[IN] Ray's direction.</param>
    Ray3D(const VectorT &vOrigin, const Vector3 &vDirection) : Ray<VectorT, Vector3>(vOrigin, vDirection)
    {
    }


    // PROPERTIES
    // ---------------
public:

    /// <summary>
    /// Gets a ray placed at the coordinate origin and whose direction vector is null.
    /// </summary>
    /// <returns>
    /// The null ray.
    /// </returns>
    static const Ray3D<VectorT>& GetNullRay()
    {
        static const Ray3D<VectorT> NULL_RAY(VectorT::GetNullVector(), Vector3::GetNullVector());
        return NULL_RAY;
    }

    /// <summary>
    /// Gets a ray placed at the coordinate origin and whose direction vector is in X growing direction.
    /// </summary>
    /// <returns>
    /// A ray that points to X direction.
    /// </returns>
    static const Ray3D<VectorT>& GetRayX()
    {
        static const Ray3D<VectorT> RAY_X(VectorT::GetNullVector(), Vector3::GetUnitVectorX());
        return RAY_X;
    }

    /// <summary>
    /// Gets a ray placed at the coordinate origin and whose direction vector is in Y growing direction.
    /// </summary>
    /// <returns>
    /// A ray that points to Y direction.
    /// </returns>
    static const Ray3D<VectorT>& GetRayY()
    {
        static const Ray3D<VectorT> RAY_Y(VectorT::GetNullVector(), Vector3::GetUnitVectorY());
        return RAY_Y;
    }

    /// <summary>
    /// Gets a ray placed at the coordinate origin and whose direction vector is in Z growing direction.
    /// </summary>
    /// <returns>
    /// A ray that points to Z direction.
    /// </returns>
    static const Ray3D<VectorT>& GetRayZ()
    {
        static const Ray3D<VectorT> RAY_Z(VectorT::GetNullVector(), Vector3::GetUnitVectorZ());
        return RAY_Z;
    }


    // METHODS
    // ---------------
public:

    /// <summary>
    /// Assignation operator that receives another ray.
    /// </summary>
    /// <param name="ray">[IN] An existing ray.</param>
    /// <returns>
    /// A reference to this ray, after assignation.
    /// </returns>
    Ray3D& operator=(const BaseRay<VectorT, Vector3> &ray)
    {
        BaseRay<VectorT, Vector3>::operator=(ray);
        return *this;
    }

    /// <summary>
    /// Checks if the ray intersects with the provided one.
    /// </summary>
    /// <remarks>
    /// If the direction of any of the rays is null, the result is undefined.<br/>
    /// How it is calculated:<br/>
    /// <br/>
    /// If both rays intersect, the intersection point must verify both vectorial ecuations:<br/>
    /// <br/>
    /// \f$ P \equiv P_1 + t_1 \cdot D_1 \f$<br/>
    /// <br/>
    /// \f$ P \equiv P_2 + t_2 \cdot D_2 \f$<br/>
    /// <br/>
    /// This ecuation is solved via vectorial products as follovs:<br/>
    /// <br/>
    /// \f$ t_1 = \frac{\begin{vmatrix} (P_2 - P_1)_x & (P_2 - P_1)_y & (P_2 - P_1)_z \\ D_{2x} & D_{2y} & D_{2z}
    /// \\ (D_1 \times D_2)_x & (D_1 \times D_2)_y & (D_1 \times D_2)_z \end{vmatrix}}{\left | D_1 \times D_2 \right |^2} \f$<br/>
    /// <br/>
    /// \f$ t_2 = \frac{\begin{vmatrix} (P_2 - P_1)_x & (P_2 - P_1)_y & (P_2 - P_1)_z \\ D_{1x} & D_{1y} & D_{1z}
    /// \\ (D_1 \times D_2)_x & (D_1 \times D_2)_y & (D_1 \times D_2)_z \end{vmatrix}}{\left | D_1 \times D_2 \right |^2} \f$<br/>
    /// <br/>
    /// Both \f$ t_1 \f$ and \f$ t_2 \f$ are forced to be greater or equal to 0, to ensure ray direction is being followed, and
    /// it is verified that \f$ P_1 + t_1 \cdot D_1 = P_2 + t_2 \cdot D_2 \f$<br/>
    /// When rays direction vector are parallel, one ray containing the other ray origin point is checked.
    /// </remarks>
    /// <param name="ray">[IN] The ray whose intersection with resident one will be checked.</param>
    /// <returns>
    /// A boolean value that indicates whether the rays intersect or not.<br/>
    /// <br/>
    /// <b>True</b><br/>
    /// The rays intersect, including the following cases:
    /// - The rays intersect in one point.
    /// - The rays are the same.
    /// - The origin of one ray is contained in the other ray.
    /// - The origin of both rays coincides.
    /// - One ray contains the other.
    /// - Both rays point to each other.
    /// 
    /// <b>False</b><br/>
    /// The rays do not intersect.
    /// </returns>
    bool Intersection(const Ray3D<VectorT> &ray) const
    {
        // Direction vector of rays should not be null
        Z_ASSERT_WARNING( !ray.Direction.IsZero() && !this->Direction.IsZero(), "Direction vector of rays should not be null" );

        const Vector3& vP = Vector3(ray.Origin - this->Origin); // Difference of positions
        Vector3 vCross = this->Direction.CrossProduct(ray.Direction); // Cross product of directions

        const float_z &DENOMINATOR = vCross.GetSquaredLength(); // That is always positive

        if ( SFloat::IsZero(DENOMINATOR) ) // Both directions are parallel
        {
            if ( this->Contains(ray.Origin) )
                return true;
            else
                return ( ray.Contains(this->Origin) );
        }
        else // Directions are not parallel
        {
            const float_z NUMERATOR1 = vP.x * ray.Direction.y * vCross.z +   vP.y * ray.Direction.z * vCross.x +
                                       vP.z * ray.Direction.x * vCross.y - ( vP.z * ray.Direction.y * vCross.x +
                                       vP.y * ray.Direction.x * vCross.z +   vP.x * ray.Direction.z * vCross.y );

            if ( SFloat::IsGreaterOrEquals(NUMERATOR1, SFloat::_0) ) // Remember that the denominator is always positive
            {
                const float_z &NUMERATOR2 = vP.x * this->Direction.y * vCross.z +   vP.y * this->Direction.z * vCross.x +
                                            vP.z * this->Direction.x * vCross.y - ( vP.z * this->Direction.y * vCross.x +
                                            vP.y * this->Direction.x * vCross.z +   vP.x * this->Direction.z * vCross.y );

                if ( SFloat::IsGreaterOrEquals(NUMERATOR2, SFloat::_0) ) // Remember that the denominator is always positive
                {
                    const Vector3 &P_INT1 = Vector3(this->Origin) + (NUMERATOR1/DENOMINATOR) * this->Direction;
                    const Vector3 &P_INT2 = Vector3(ray.Origin) + (NUMERATOR2/DENOMINATOR) * ray.Direction;

                    if (P_INT1 == P_INT2)
                        return true;
                    else
                        return false;
                }
                else
                    return false;
            }
            else
                return false;
        }
    }

    /// <summary>
    /// Checks if the ray and the provided line segment intersects.
    /// </summary>
    /// <remarks>
    /// If the direction of the ray is null, the result is undefined.<br/>
    /// How it is calculated:<br/>
    /// <br/>
    /// A ray with direction from A to B with origin in A is constructed.<br/>
    /// If both rays intersects, the intersection point must verify both vectorial ecuations:<br/>
    /// <br/>
    /// \f$ P \equiv P_1 + t_1 \cdot D_1 \f$<br/>
    /// <br/>
    /// \f$ P \equiv P_2 + t_2 \cdot D_2 \f$<br/>
    /// <br/>
    /// This ecuation is solved via vectorial products as follows:<br/>
    /// <br/>
    /// \f$ t_1 = \frac{\begin{vmatrix} (P_2 - P_1)_x & (P_2 - P_1)_y & (P_2 - P_1)_z \\ D_{2x} & D_{2y} & D_{2z}
    /// \\ (D_1 \times D_2)_x & (D_1 \times D_2)_y & (D_1 \times D_2)_z \end{vmatrix}}{\left | D_1 \times D_2 \right |^2} \f$<br/>
    /// <br/>
    /// \f$ t_2 = \frac{\begin{vmatrix} (P_2 - P_1)_x & (P_2 - P_1)_y & (P_2 - P_1)_z \\ D_{1x} & D_{1y} & D_{1z}
    /// \\ (D_1 \times D_2)_x & (D_1 \times D_2)_y & (D_1 \times D_2)_z \end{vmatrix}}{\left | D_1 \times D_2 \right |^2} \f$<br/>
    /// <br/>
    /// Both \f$ t_1 \f$ and \f$ t_2 \f$ are forced to be greater or equal to 0, to ensure ray direction is being followed,
    /// and \f$ t_2 \f$ is forced to be in [0, 1] interval, to ensure the point is inside segment.<br/>
    /// Finally it's verified that \f$ P_1 + t_1 \cdot D_1 = P_2 + t_2 \cdot D_2 \f$<br/>
    /// When rays direction vector are parallel, one ray containing the other ray origin point is checked.
    /// </remarks>
    /// <param name="segment">[IN] The line segment whose intersection with the ray will be checked.</param>
    /// <returns>
    /// A boolean value that indicates whether the ray and the line segment intersect or not.<br/>
    /// <br/>
    /// <b>True</b><br/>
    /// The ray and the line segment intersect, including the following cases:
    /// - The ray intersect with the line segment between endpoints A and B.
    /// - The origin of the ray coincides with an endpoint of the segment and the ray contains the segment.
    /// - The origin of the ray belongs to the line segment.
    /// - The origin of the ray only coincides with one endpoint.
    /// - The ray intersects with one or with both endpoints.
    /// 
    /// <b>False</b><br/>
    /// The ray and the line segment do not intersect.
    /// </returns>
    bool Intersection(const BaseLineSegment<VectorT> &segment) const
    {
        // Direction vector belonging to the ray cannot be null and the length of the segment should be greater than zero (either or both of this rules may have failed)
        Z_ASSERT_WARNING( segment.A != segment.B && !this->Direction.IsZero(), "Direction vector belonging to the ray cannot be null and the length of the segment should be greater than zero (either or both of this rules may have failed)" );

        // Same method that intersection with other ray. A ray with Position in A and direction B-A is created.
        // After intersection method, the ray parameter is forced to be in [0, 1] interval.
        BaseRay<Vector3, Vector3> ray(Vector3(segment.A), Vector3(segment.B - segment.A));

        const Vector3& vP = Vector3(segment.A - this->Origin); // Difference of positions

        Vector3 vCross = this->Direction.CrossProduct(ray.Direction); // Cross product of directions

        const float_z &DENOMINATOR = vCross.GetSquaredLength(); // That is always positive

        if ( SFloat::IsZero(DENOMINATOR) ) // Both directions are parallels
        {
            if ( this->Contains(segment.A) )
                return true;
            else
                return this->Contains(segment.B);
        }
        else // Directions are not parallel
        {
            const float_z NUMERATOR1 = vP.x * ray.Direction.y * vCross.z +   vP.y * ray.Direction.z * vCross.x +
                                       vP.z * ray.Direction.x * vCross.y - ( vP.z * ray.Direction.y * vCross.x +
                                       vP.y * ray.Direction.x * vCross.z +   vP.x * ray.Direction.z * vCross.y );

            if ( SFloat::IsGreaterOrEquals(NUMERATOR1, SFloat::_0) ) // Remember that the denominator is always positive
            {
                const float_z &NUMERATOR2 = vP.x * this->Direction.y * vCross.z +   vP.y * this->Direction.z * vCross.x +
                                            vP.z * this->Direction.x * vCross.y - ( vP.z * this->Direction.y * vCross.x +
                                            vP.y * this->Direction.x * vCross.z +   vP.x * this->Direction.z * vCross.y );

                const float_z PARAM2 = NUMERATOR2 / DENOMINATOR;
                if ( SFloat::IsGreaterOrEquals(NUMERATOR2, SFloat::_0) && SFloat::IsLessOrEquals(PARAM2, SFloat::_1) ) // Remember that the denominator is always positive
                {
                    const Vector3 &P_INT1 = Vector3(this->Origin) + (NUMERATOR1 / DENOMINATOR) * this->Direction;
                    const Vector3 &P_INT2 = ray.Origin + PARAM2 * ray.Direction;

                    if (P_INT1 == P_INT2)
                        return true;
                    else
                        return false;
                }
                else
                    return false;
            }
            else
                return false;
        }
    }

    /// <summary>
    /// Checks if the ray intersects with the provided plane.
    /// </summary>
    /// <remarks>
    /// If the direction of the ray is null, the result is undefined.<br/>
    /// Intersection point \f$ P_0 \f$ must verify both ecuations:<br/>
    /// <br/>
    /// Ray equation: \f$ P_0 = P + t \cdot V \f$<br/>
    /// <br/>
    /// Plane equation: \f$ aP_{0x} + bP_{0y} + cP_{0z} + d = N \cdot P_0 + d = 0 \f$<br/>
    /// <br/>
    /// That is:<br/>
    /// <br/>
    /// \f$ t = \frac{-(d + N \cdot P)}{N \cdot V} \f$<br/>
    /// <br/>
    /// - If \f$ N \cdot V = 0 \f$ ray and plane are parallels.<br/>
    ///  - Then, if \f$ d + N \cdot P = 0 \f$ ray lies on plane, otherwise there are no intersection.<br/>
    /// - If t < 0, there are no intersection (the ray straight line intersects the plane backwards the ray origin).
    /// </remarks>
    /// <param name="plane">[IN] The plane we want check if intersects with resident ray. If the plane is null, the result is undefined.</param>
    /// <returns>
    /// A boolean value that indicates whether the ray and the plane intersect or not.<br/>
    /// <br/>
    /// <b>True</b><br/>
    /// The ray and the plane intersect, including the following cases:
    /// - The origin of the ray belongs to one side of the space divided by the plane and points to the other side.
    /// - The ray is completely contained in the plane.
    /// - Only the origin of the ray belongs to the plane.
    /// 
    /// <b>False</b><br/>
    /// The ray and the plane do not intersect.
    /// - The ray is parallel to the plane and is not contained in it.
    /// - The origin of the ray belongs to one side of the space divided by the plane and does not point to the other side.
    /// </returns>
    bool Intersection(const BasePlane &plane) const
    {
        // The plane shouldn't be null
        Z_ASSERT_WARNING( !(SFloat::IsZero(plane.a) && SFloat::IsZero(plane.b) && SFloat::IsZero(plane.c)), "The input plane shouldn't be null" );

        // The direction vector of the ray mustn't be null
        Z_ASSERT_WARNING( !this->Direction.IsZero(), "The direction vector of the ray mustn't be null" );

        const Vector3 vN(plane.a, plane.b, plane.c); // Normal to plane (Normalize not necessary)
        const Vector3 vP(this->Origin); // Homogeinizing vector types

        const float_z &NUMERATOR = -(plane.d + vP.DotProduct(vN));
        const float_z &DENOMINATOR = this->Direction.DotProduct(vN);

        if ( SFloat::IsZero(DENOMINATOR) )
            return SFloat::IsZero(NUMERATOR);
        else
            return SFloat::IsGreaterOrEquals(NUMERATOR / DENOMINATOR, SFloat::_0);
    }

    /// <summary>
    /// Checks if the ray intersects with the provided triangle.
    /// </summary>
    /// <remarks>
    /// If the direction of the ray is null, the result is undefined.
    /// </remarks>
    /// <param name="triangle">[IN] The triangle whose intersection with the ray will be checked. If any of its vertices coincide, 
    /// the result is undefined.</param>
    /// <returns>
    /// A boolean value that indicates whether the ray and the triangle intersect or not.<br/>
    /// <br/>
    /// <b>True</b><br/>
    /// The ray and the triangle intersect, including the following cases:
    /// - The ray intersects with two edges of the triangle.
    /// - The ray intersects with a vertex of the triangle.
    /// - The origin of the ray is contained in the triangle (and the ray does not intersects with any edge).
    /// - The origin of the ray is contained in the triangle (and the ray intersects with an edge).
    /// - The origin of the ray belongs to an edge of the triangle.
    /// - The ray intersects with an edge of the triangle in only one point.
    /// - The origin of the ray coincides with a vertex of the triangle.
    ///
    /// <b>False</b><br/>
    /// The ray and the triangle do not intersect.
    /// </returns>
    bool Intersection(const BaseTriangle<VectorT> &triangle) const
    {
        // Vertices of the triangle must not coincide
        Z_ASSERT_WARNING( triangle.A != triangle.B && 
                   triangle.B != triangle.C &&
                   triangle.C != triangle.A, "Vertices of the triangle must not coincide" );

        // The direction vector of the ray shouldn't be null
        Z_ASSERT_WARNING( !this->Direction.IsZero(), "The direction vector of the ray shouldn't be null" );

        // Plane that contains triangle
        Plane auxPlane(triangle.A, triangle.B, triangle.C);

        VectorT vIntersectionPoint;

        const EIntersections &NUM_INTERSECT = this->IntersectionPoint(auxPlane, vIntersectionPoint);
        if (NUM_INTERSECT == EIntersections::E_Infinite) // Ray and plane are coplanar.
        {
            return ( this->Intersection(BaseLineSegment<VectorT>(triangle.A, triangle.B)) ||
                     this->Intersection(BaseLineSegment<VectorT>(triangle.B, triangle.C)) ||
                     this->Intersection(BaseLineSegment<VectorT>(triangle.C, triangle.A)) );
        }
        else if (NUM_INTERSECT == EIntersections::E_One) // Ray and plane intersects in one point
        {
            return this->PointInsideTriangle(triangle, vIntersectionPoint);
        }
        else
            return false;
    }

    /// <summary>
    /// Checks if the ray intersects with the provided hexahedron.
    /// </summary>
    /// <remarks>
    /// If the direction of the ray is null, the result is undefined.
    /// </remarks>
    /// <param name="hexahedron">[IN] The hexahedron we want check if intersects with the ray. It must be convex for the operation to return correct 
    /// results. If any of its vertices coincide, the result is undefined.</param>
    /// <returns>
    /// A boolean value that indicates whether the ray and the hexahedron intersect or not.<br/>
    /// <br/>
    /// <b>True</b><br/>
    /// The ray and the hexahedron intersect, including the following cases:
    /// - The ray intersects with two of the faces of the hexahedron.
    /// - The ray intersects with a vertex of the hexahedron.
    /// - The origin of the ray belongs to a face of the hexahedron.
    /// - The origin of the ray belongs to a face of the hexahedron and the ray intersects one of the edges of the same face.
    /// - The origin of the ray is contained in the hexahedron.
    /// - The origin of the ray belongs to an edge of the hexahedron.
    /// - The ray intersects with an edge of the hexahedron.
    /// - The origin of the ray coincides with a vertex of the hexahedron.
    ///
    /// <b>False</b><br/>
    /// The ray and the hexahedron do not intersect.
    /// </returns>
    bool Intersection(const BaseHexahedron<VectorT> &hexahedron) const
    {
        // The direction vector of the ray mustn't be null
        Z_ASSERT_WARNING( !this->Direction.IsZero(), "The direction vector of the ray mustn't be null" );

         // Checks if there is an intersection with any face.
        return (this->Intersection(hexahedron.A, hexahedron.B, hexahedron.C, hexahedron.D) ||
                this->Intersection(hexahedron.E, hexahedron.F, hexahedron.G, hexahedron.H) ||
                this->Intersection(hexahedron.A, hexahedron.B, hexahedron.H, hexahedron.E) ||
                this->Intersection(hexahedron.B, hexahedron.C, hexahedron.G, hexahedron.H) ||
                this->Intersection(hexahedron.A, hexahedron.D, hexahedron.F, hexahedron.E) ||
                this->Intersection(hexahedron.C, hexahedron.D, hexahedron.F, hexahedron.G));
    }


    /// <summary>
    /// Computes the intersection point between resident and provided ray.
    /// </summary>
    /// <remarks>
    /// If there's no intersection point or there are infinite,
    /// the output parameter used for storing that point won't be modified.<br/>
    /// <br/>
    /// If the rays intesect, the intersection point must verify both vectorial ecuations:<br/>
    /// <br/>
    /// \f$ P \equiv P_1 + t_1 \cdot D_1 \f$<br/>
    /// <br/>
    /// \f$ P \equiv P_2 + t_2 \cdot D_2 \f$<br/>
    /// <br/>
    /// This ecuation is solved via vectorial products as follovs:<br/>
    /// <br/>
    /// \f$ t_1 = \frac{\begin{vmatrix} (P_2 - P_1)_x & (P_2 - P_1)_y & (P_2 - P_1)_z \\ D_{2x} & D_{2y} & D_{2z}
    /// \\ (D_1 \times D_2)_x & (D_1 \times D_2)_y & (D_1 \times D_2)_z \end{vmatrix}}{\left | D_1 \times D_2 \right |^2} \f$<br/>
    /// <br/>
    /// \f$ t_2 = \frac{\begin{vmatrix} (P_2 - P_1)_x & (P_2 - P_1)_y & (P_2 - P_1)_z \\ D_{1x} & D_{1y} & D_{1z}
    /// \\ (D_1 \times D_2)_x & (D_1 \times D_2)_y & (D_1 \times D_2)_z \end{vmatrix}}{\left | D_1 \times D_2 \right |^2} \f$<br/>
    /// <br/>
    /// Both \f$ t_1 \f$ and \f$ t_2 \f$ are forced to be greater or equal to 0, to ensure ray direction is being followed, and
    /// it is verified that:<br/>
    /// <br/>
    /// \f$ P_1 + t_1 \cdot D_1 = P_2 + t_2 \cdot D_2 \f$<br/>
    /// <br/>
    /// When rays direction vector are parallel, one ray containing the other ray origin point is checked.
    /// </remarks>
    /// <param name="ray">[IN] The ray whose intersection with the resident ray will be checked.</param>
    /// <param name="vIntersection">[OUT] The closest intersection point to the resident ray's origin.</param>
    /// <returns>
    /// An enumerated value that indicates how many intersections were found:<br/>
    /// <br/>
    /// <b>None</b><br/>
    /// There are no intersections.<br/>
    ///
    /// <b>One</b><br/>
    /// There is one intersection.<br/>
    /// - The rays intersect in one point.
    /// - The origin of one ray is contained in the other ray.
    /// - The origin of both rays coincide.
    /// - One ray is contained in the other.
    ///
    /// <b>Two</b><br/>
    /// There are two intersections.<br/>
    /// - Both rays point to each other.
    ///
    /// <b>Infinite</b><br/>
    /// There are infinite intersections.<br/>
    /// - The rays are the same.
    /// </returns>
    EIntersections IntersectionPoint(const Ray3D<VectorT> &ray, VectorT &vIntersection) const
    {
        // The direction vector of the ray shouldn't be null
        Z_ASSERT_WARNING( !this->Direction.IsZero() && !ray.Direction.IsZero(), "The direction vector of the ray shouldn't be null" );

        const VectorT &vP(ray.Origin - this->Origin); // Difference of positions
        Vector3 vCross = this->Direction.CrossProduct(ray.Direction); // Cross product of directions

        const float_z &DENOMINATOR = vCross.GetSquaredLength(); // That is always positive

        if ( SFloat::IsZero(DENOMINATOR) ) // Both directions are parallel
        {
            if (this->Origin == ray.Origin)
            {
                if ( (this->Direction + ray.Direction) == Vector3::GetNullVector() ) // Directions are opposite (are supossed normalized)
                {
                    vIntersection.x = this->Origin.x;
                    vIntersection.y = this->Origin.y;
                    vIntersection.z = this->Origin.z;
                    return EIntersections::E_One;
                }
                else
                    return EIntersections::E_Infinite; // Both rays are the same
            }
            else if ( this->Contains(ray.Origin) )
            {
                if(ray.Contains(this->Origin))
                {
                    vIntersection.x = this->Origin.x;
                    vIntersection.y = this->Origin.y;
                    vIntersection.z = this->Origin.z;
                    return EIntersections::E_Two;
                }
                else
                {
                    vIntersection.x = ray.Origin.x;
                    vIntersection.y = ray.Origin.y;
                    vIntersection.z = ray.Origin.z;
                    return EIntersections::E_One;
                }
            }
            else if(ray.Contains(this->Origin) )
            {
                vIntersection.x = this->Origin.x;
                vIntersection.y = this->Origin.y;
                vIntersection.z = this->Origin.z;
                return EIntersections::E_One;
            }
            else
                return EIntersections::E_None;
        }
        else // Directions are not parallel
        {
            const float_z NUMERATOR1 = vP.x * ray.Direction.y * vCross.z +   vP.y * ray.Direction.z * vCross.x +
                                       vP.z * ray.Direction.x * vCross.y - ( vP.z * ray.Direction.y * vCross.x +
                                       vP.y * ray.Direction.x * vCross.z +   vP.x * ray.Direction.z * vCross.y );

            if ( SFloat::IsGreaterOrEquals(NUMERATOR1, SFloat::_0) ) // Remember that fDenominator is always positive
            {
                const float_z &NUMERATOR2 = vP.x * this->Direction.y * vCross.z +   vP.y * this->Direction.z * vCross.x +
                                            vP.z * this->Direction.x * vCross.y - ( vP.z * this->Direction.y * vCross.x +
                                            vP.y * this->Direction.x * vCross.z +   vP.x * this->Direction.z * vCross.y );

                if ( SFloat::IsGreaterOrEquals(NUMERATOR2, SFloat::_0) ) // Remember that fDenominator is always positive
                {
                    const Vector3 &P_INT1 = Vector3(this->Origin) + (NUMERATOR1 / DENOMINATOR) * this->Direction;
                    const Vector3 &P_INT2 = Vector3(ray.Origin) + (NUMERATOR2 / DENOMINATOR) * ray.Direction;

                    if (P_INT1 == P_INT2)
                    {
                        vIntersection.x = P_INT1.x;
                        vIntersection.y = P_INT1.y;
                        vIntersection.z = P_INT1.z;
                        return EIntersections::E_One;
                    }
                    else
                        return EIntersections::E_None;
                }
                else
                    return EIntersections::E_None;
            }
            else
                return EIntersections::E_None;
        }
    }
    
    /// <summary>
    /// Computes the intersection point between the ray and provided line segment, if it exists.
    /// </summary>
    /// <remarks>
    /// If the direction of the ray is null, the result is undefined.<br/>
    /// If there's no intersection point, the output parameters won't be modified.<br/>
    /// To calculate the intersections, a ray with direction from A to B with origin in A is constructed.<br/>
    /// If both rays intersects, the intersection point must verify both vectorial ecuations:<br/>
    /// <br/>
    /// \f$ P \equiv P_1 + t_1 \cdot D_1 \f$<br/>
    /// <br/>
    /// \f$ P \equiv P_2 + t_2 \cdot D_2 \f$<br/>
    /// <br/>
    /// This ecuation is solved via vectorial products as follovs:<br/>
    /// <br/>
    /// \f$ t_1 = \frac{\begin{vmatrix} (P_2 - P_1)_x & (P_2 - P_1)_y & (P_2 - P_1)_z \\ D_{2x} & D_{2y} & D_{2z}
    /// \\ (D_1 \times D_2)_x & (D_1 \times D_2)_y & (D_1 \times D_2)_z \end{vmatrix}}{\left | D_1 \times D_2 \right |^2} \f$<br/>
    /// <br/>
    /// \f$ t_2 = \frac{\begin{vmatrix} (P_2 - P_1)_x & (P_2 - P_1)_y & (P_2 - P_1)_z \\ D_{1x} & D_{1y} & D_{1z}
    /// \\ (D_1 \times D_2)_x & (D_1 \times D_2)_y & (D_1 \times D_2)_z \end{vmatrix}}{\left | D_1 \times D_2 \right |^2} \f$<br/>
    /// <br/>
    /// Both \f$ t_1 \f$ and \f$ t_2 \f$ are forced to be greater or equal to 0, to ensure ray direction is being followed,
    /// and \f$ t_2 \f$ is forced to be in [0, 1] interval, to ensure the point is inside segment.<br/>
    /// Finally it's verified that:<br/>
    /// <br/>
    /// \f$ P_1 + t_1 \cdot D_1 = P_2 + t_2 \cdot D_2 \f$<br/>
    /// <br/>
    /// When rays direction vector are parallel, one ray containing the other ray origin point is checked.
    /// </remarks>
    /// <param name="segment">[IN] The line segment whose intersection with resident ray will be checked.</param>
    /// <param name="vIntersection">[OUT] The closest intersection point to the ray's origin.</param>
    /// <returns>
    /// An enumerated value that indicates how many intersections were found:<br/>
    /// <br/>
    /// <b>None</b><br/>
    /// There are no intersections.<br/>
    ///
    /// <b>One</b><br/>
    /// There is one intersection.<br/>
    /// - The ray intersects with the line segment between endpoints A and B.
    /// - The origin of the ray coincides with an endpoint of the segment and the other endpoint is not contained in the ray.
    /// - The origin of the ray is contained in the line segment and thre is no intersection with the endpoints.
    /// - The ray intersects with an endpoint of the segment.
    ///
    /// <b>Two</b><br/>
    /// There are two intersections.<br/>
    /// - The origin of the ray coincides with an endpoint of the segment and the other endpoint is contained in the ray.
    /// - The ray intersects with the teo endpoints of the line, containing it.
    /// </returns>
    EIntersections IntersectionPoint(const BaseLineSegment<VectorT> &segment, VectorT &vIntersection) const
    {
        // The direction vector of the ray shouldn't be null
        Z_ASSERT_WARNING( !this->Direction.IsZero(), "The direction vector of the ray shouldn't be null" );

        // The length of the segment shouldn't equal zero
        Z_ASSERT_WARNING( segment.A != segment.B, "The length of the segment shouldn't equal zero" );

        // Same method that intersection with other ray. A ray with Position in A and direction B-A is created.
        // After intersection method, the ray parameter is forced to be in [0, 1] interval.
        BaseRay<VectorT, Vector3> ray( segment.A, Vector3(segment.B - segment.A) );

        const VectorT &vP(segment.A - this->Origin); // Difference of positions

        Vector3 vCross = this->Direction.CrossProduct(ray.Direction); // Cross product of directions

        const float_z &DENOMINATOR = vCross.GetSquaredLength(); // That is always positive

        if ( SFloat::IsZero(DENOMINATOR) ) // Both directions are parallels
        {
            const bool &A_IS_IN_RAY = this->Contains(segment.A);
            const bool &B_IS_IN_RAY = this->Contains(segment.B);

            if ( A_IS_IN_RAY && B_IS_IN_RAY )
            {
                if(this->Origin == segment.A)
                {
                    vIntersection.x = segment.A.x;
                    vIntersection.y = segment.A.y;
                    vIntersection.z = segment.A.z;
                }
                else if(this->Origin == segment.B)
                {
                    vIntersection.x = segment.B.x;
                    vIntersection.y = segment.B.y;
                    vIntersection.z = segment.B.z;
                }
                else if(SFloat::IsNegative( (segment.B - segment.A).DotProduct(segment.B - this->Origin) ))// To know which endpoint is closer to the origin of the ray...
                {
                    vIntersection.x = segment.A.x;
                    vIntersection.y = segment.A.y;
                    vIntersection.z = segment.A.z;
                }
                else
                {
                    vIntersection.x = segment.B.x;
                    vIntersection.y = segment.B.y;
                    vIntersection.z = segment.B.z;
                }

                return EIntersections::E_Two;
            }
            else if ( A_IS_IN_RAY )
            {
                vIntersection.x = this->Origin.x;
                vIntersection.y = this->Origin.y;
                vIntersection.z = this->Origin.z;

                if (segment.A == this->Origin)
                {
                    return EIntersections::E_One;
                }
                else
                {
                    return EIntersections::E_Two;
                }
            }
            else if ( B_IS_IN_RAY )
            {
                vIntersection.x = this->Origin.x;
                vIntersection.y = this->Origin.y;
                vIntersection.z = this->Origin.z;

                if (segment.B == this->Origin)
                {
                    return EIntersections::E_One;
                }
                else
                {
                    return EIntersections::E_Two;
                }
            }
            else
                return EIntersections::E_None;
        }
        else // Directions are not parallel
        {
            const float_z NUMERATOR1 = vP.x * ray.Direction.y * vCross.z +   vP.y * ray.Direction.z * vCross.x +
                                       vP.z * ray.Direction.x * vCross.y - ( vP.z * ray.Direction.y * vCross.x +
                                       vP.y * ray.Direction.x * vCross.z +   vP.x * ray.Direction.z * vCross.y );

            if ( SFloat::IsGreaterOrEquals(NUMERATOR1, SFloat::_0) ) // Remember that fDenominator is always positive
            {
                const float_z &NUMERATOR2 = vP.x * this->Direction.y * vCross.z +   vP.y * this->Direction.z * vCross.x +
                                            vP.z * this->Direction.x * vCross.y - ( vP.z * this->Direction.y * vCross.x +
                                            vP.y * this->Direction.x * vCross.z +   vP.x * this->Direction.z * vCross.y );

                const float_z PARAM2 = NUMERATOR2 / DENOMINATOR;
                if ( SFloat::IsGreaterOrEquals(NUMERATOR2, SFloat::_0) && SFloat::IsLessOrEquals(PARAM2, SFloat::_1) ) // Remember that fDenominator is always positive
                {
                    const Vector3 &P_INT1 = Vector3(this->Origin) + (NUMERATOR1 / DENOMINATOR) * this->Direction;
                    const Vector3 &P_INT2 = Vector3(ray.Origin) + PARAM2 * ray.Direction;

                    if (P_INT1 == P_INT2)
                    {
                        vIntersection.x = P_INT1.x;
                        vIntersection.y = P_INT1.y;
                        vIntersection.z = P_INT1.z;
                        return EIntersections::E_One;
                    }
                    else
                        return EIntersections::E_None;
                }
                else
                    return EIntersections::E_None;
            }
            else
                return EIntersections::E_None;
        }
    }
    
    /// <summary>
    /// Computes the intersection point between resident ray and provided line segment, if it exists.
    /// </summary>
    /// <remarks>
    /// If the direction of the ray is null, the result is undefined.<br/>
    /// If there's no intersection point, the output parameters won't be modified.<br/>
    /// To calculate the intersections, a ray with direction from A to B with origin in A is constructed.<br/>
    /// If both rays intersects, the intersection point must verify both vectorial ecuations:<br/>
    /// <br/>
    /// \f$ P \equiv P_1 + t_1 \cdot D_1 \f$<br/>
    /// <br/>
    /// \f$ P \equiv P_2 + t_2 \cdot D_2 \f$<br/>
    /// <br/>
    /// This ecuation is solved via vectorial products as follovs:<br/>
    /// <br/>
    /// \f$ t_1 = \frac{\begin{vmatrix} (P_2 - P_1)_x & (P_2 - P_1)_y & (P_2 - P_1)_z \\ D_{2x} & D_{2y} & D_{2z}
    /// \\ (D_1 \times D_2)_x & (D_1 \times D_2)_y & (D_1 \times D_2)_z \end{vmatrix}}{\left | D_1 \times D_2 \right |^2} \f$<br/>
    /// <br/>
    /// \f$ t_2 = \frac{\begin{vmatrix} (P_2 - P_1)_x & (P_2 - P_1)_y & (P_2 - P_1)_z \\ D_{1x} & D_{1y} & D_{1z}
    /// \\ (D_1 \times D_2)_x & (D_1 \times D_2)_y & (D_1 \times D_2)_z \end{vmatrix}}{\left | D_1 \times D_2 \right |^2} \f$<br/>
    /// <br/>
    /// Both \f$ t_1 \f$ and \f$ t_2 \f$ are forced to be greater or equal to 0, to ensure ray direction is being followed,
    /// and \f$ t_2 \f$ is forced to be in [0, 1] interval, to ensure the point is inside segment.<br/>
    /// Finally it's verified that:<br/>
    /// <br/>
    /// \f$ P_1 + t_1 \cdot D_1 = P_2 + t_2 \cdot D_2 \f$<br/>
    /// <br/>
    /// When rays direction vector are parallel, one ray containing the other ray origin point is checked.
    /// </remarks>
    /// <param name="segment">[IN] The line segment whose intersection with the ray will be checked.</param>
    /// <param name="vIntersection1">[OUT] The closest intersection point to the ray's origin.</param>
    /// <param name="vIntersection2">[OUT] The furthest intersection point to the ray's origin.</param>
    /// <returns>
    /// An enumerated value that indicates how many intersections were found:<br/>
    /// <br/>
    /// <b>None</b><br/>
    /// There are no intersections.<br/>
    ///
    /// <b>One</b><br/>
    /// There is one intersection.<br/>
    /// - The ray intersects with the line segment between endpoints A and B.
    /// - The origin of the ray coincides with an endpoint of the segment and the other endpoint is not contained in the ray.
    /// - The origin of the ray is contained in the line segment and thre is no intersection with the endpoints.
    /// - The ray intersects with an endpoint of the segment.
    ///
    /// <b>Two</b><br/>
    /// There are two intersections.<br/>
    /// - The origin of the ray coincides with an endpoint of the segment and the other endpoint is contained in the ray.
    /// - The ray intersects with the teo endpoints of the line, containing it.
    /// </returns>
    EIntersections IntersectionPoint(const BaseLineSegment<VectorT> &segment, VectorT &vIntersection1, VectorT &vIntersection2) const
    {
        // The direction vector of the ray shouldn't be null
        Z_ASSERT_WARNING( !this->Direction.IsZero(), "The direction vector of the ray shouldn't be null" );

        // The length of the line shouldn't equal zero
        Z_ASSERT_WARNING( segment.A != segment.B, "The length of the line shouldn't equal zero" );

        // Same method that intersection with other ray. A ray with Position in A and direction B-A is created.
        // After intersection method, the ray parameter is forced to be in [0, 1] interval.
        BaseRay<VectorT, Vector3> ray( segment.A, Vector3(segment.B - segment.A) );

        const VectorT &vP(segment.A - this->Origin); // Difference of positions

        Vector3 vCross = this->Direction.CrossProduct(ray.Direction); // Cross product of directions

        const float_z &DENOMINATOR = vCross.GetSquaredLength(); // That is always positive

        if ( SFloat::IsZero(DENOMINATOR) ) // Both directions are parallels
        {
            const bool &A_IS_IN_RAY = this->Contains(segment.A);
            const bool &B_IS_IN_RAY = this->Contains(segment.B);

            if ( A_IS_IN_RAY && B_IS_IN_RAY )
            {
                if(this->Origin == segment.A)
                {
                    vIntersection1.x = segment.A.x;
                    vIntersection1.y = segment.A.y;
                    vIntersection1.z = segment.A.z;
                    vIntersection2.x = segment.B.x;
                    vIntersection2.y = segment.B.y;
                    vIntersection2.z = segment.B.z;
                }
                else if(this->Origin == segment.B)
                {
                    vIntersection1.x = segment.B.x;
                    vIntersection1.y = segment.B.y;
                    vIntersection1.z = segment.B.z;
                    vIntersection2.x = segment.A.x;
                    vIntersection2.y = segment.A.y;
                    vIntersection2.z = segment.A.z;
                }
                else if(SFloat::IsNegative( (segment.B - segment.A).DotProduct(segment.B - this->Origin) ))// To know which endpoint is closer to the origin of the ray...
                {
                    vIntersection1.x = segment.A.x;
                    vIntersection1.y = segment.A.y;
                    vIntersection1.z = segment.A.z;
                    vIntersection2.x = segment.B.x;
                    vIntersection2.y = segment.B.y;
                    vIntersection2.z = segment.B.z;
                }
                else
                {
                    vIntersection1.x = segment.B.x;
                    vIntersection1.y = segment.B.y;
                    vIntersection1.z = segment.B.z;
                    vIntersection2.x = segment.A.x;
                    vIntersection2.y = segment.A.y;
                    vIntersection2.z = segment.A.z;
                }

                return EIntersections::E_Two;
            }
            else if ( A_IS_IN_RAY )
            {
                if (segment.A == this->Origin)
                {
                    vIntersection1.x = segment.A.x;
                    vIntersection1.y = segment.A.y;
                    vIntersection1.z = segment.A.z;
                    return EIntersections::E_One;
                }
                else
                {
                    vIntersection1.x = this->Origin.x;
                    vIntersection1.y = this->Origin.y;
                    vIntersection1.z = this->Origin.z;
                    vIntersection2.x = segment.A.x;
                    vIntersection2.y = segment.A.y;
                    vIntersection2.z = segment.A.z;
                    return EIntersections::E_Two;
                }
            }
            else if ( B_IS_IN_RAY )
            {
                if (segment.B == this->Origin)
                {
                    vIntersection1.x = segment.B.x;
                    vIntersection1.y = segment.B.y;
                    vIntersection1.z = segment.B.z;
                    return EIntersections::E_One;
                }
                else
                {
                    vIntersection1.x = this->Origin.x;
                    vIntersection1.y = this->Origin.y;
                    vIntersection1.z = this->Origin.z;
                    vIntersection2.x = segment.B.x;
                    vIntersection2.y = segment.B.y;
                    vIntersection2.z = segment.B.z;
                    return EIntersections::E_Two;
                }
            }
            else
                return EIntersections::E_None;
        }
        else // Directions are not parallel
        {
            const float_z NUMERATOR1 = vP.x * ray.Direction.y * vCross.z +   vP.y * ray.Direction.z * vCross.x +
                                       vP.z * ray.Direction.x * vCross.y - ( vP.z * ray.Direction.y * vCross.x +
                                       vP.y * ray.Direction.x * vCross.z +   vP.x * ray.Direction.z * vCross.y );

            if ( SFloat::IsGreaterOrEquals(NUMERATOR1, SFloat::_0) ) // Remember that fDenominator is always positive
            {
                const float_z &NUMERATOR2 = vP.x * this->Direction.y * vCross.z +   vP.y * this->Direction.z * vCross.x +
                                            vP.z * this->Direction.x * vCross.y - ( vP.z * this->Direction.y * vCross.x +
                                            vP.y * this->Direction.x * vCross.z +   vP.x * this->Direction.z * vCross.y );

                const float_z PARAM2 = NUMERATOR2 / DENOMINATOR;
                if ( SFloat::IsGreaterOrEquals(NUMERATOR2, SFloat::_0) && SFloat::IsLessOrEquals(PARAM2, SFloat::_1) ) // Remember that fDenominator is always positive
                {
                    const Vector3 &P_INT1 = Vector3(this->Origin) + (NUMERATOR1 / DENOMINATOR) * this->Direction;
                    const Vector3 &P_INT2 = Vector3(ray.Origin) + PARAM2 * ray.Direction;

                    if (P_INT1 == P_INT2)
                    {
                        vIntersection1.x = P_INT1.x;
                        vIntersection1.y = P_INT1.y;
                        vIntersection1.z = P_INT1.z;
                        return EIntersections::E_One;
                    }
                    else
                        return EIntersections::E_None;
                }
                else
                    return EIntersections::E_None;
            }
            else
                return EIntersections::E_None;
        }
    }

    /// <summary>
    /// Checks if the ray intersects with the provided plane, calculating the intersection point.
    /// </summary>
    /// <remarks>
    /// If the direction of the ray is null, the result is undefined.<br/>
    /// If there is no intersection point or if there are infinite, the output parameter is not modified.<br/>
    /// Intersection point \f$ P_0 \f$ must verify both ecuations:<br/>
    /// <br/>
    /// Ray equation: \f$ P_0 = P + t \cdot V \f$<br/>
    /// <br/>
    /// Plane equation: \f$ aP_{0x} + bP_{0y} + cP_{0z} + d = N \cdot P_0 + D = 0 \f$<br/>
    /// <br/>
    /// That is:<br/>
    /// <br/>
    /// \f$ t = \frac{-(d + N \cdot P)}{N \cdot V} \f$<br/>
    /// <br/>
    /// - If \f$ N \cdot V = 0 \f$ ray and plane are parallels.<br/>
    ///  - Then, if \f$ d + N \cdot P = 0 \f$ ray lies on plane, otherwise there are no intersection.<br/>
    /// - If t < 0, there are no intersection (the ray straight line intersects the plane backwards the ray position).
    /// </remarks>
    /// <param name="plane">[IN] The plane we want check if intersects with resident ray. If it is null, the result is undefined.</param>
    /// <param name="vIntersection">[OUT] The intersection point.</param>
    /// <returns>
    /// An enumerated value that indicates how many intersections were found:<br/>
    /// <br/>
    /// <b>None</b><br/>
    /// There are no intersections.<br/>
    ///
    /// <b>One</b><br/>
    /// There is one intersection.<br/>
    /// - The origin of the ray is in one side of the space divided by the plane, pionting to the other side.
    /// - Only the origin of the ray belongs to the plane.
    ///
    /// <b>Infinite</b><br/>
    /// There are infinite intersections.<br/>
    /// - The ray is completely contained in the plane.
    /// </returns>
    EIntersections IntersectionPoint(const BasePlane &plane, VectorT &vIntersection) const
    {
        // The direction vector of the ray shouldn't be null
        Z_ASSERT_WARNING( !this->Direction.IsZero(), "The direction vector of the ray shouldn't be null" );

        // The plane shouldn't be null
        Z_ASSERT_WARNING( !(SFloat::IsZero(plane.a) && SFloat::IsZero(plane.b) && SFloat::IsZero(plane.c)), "The input plane shouldn't be null" );

        const VectorT vN( Vector3(plane.a, plane.b, plane.c) );

        const float_z &NUMERATOR = -(plane.d + this->Origin.DotProduct(vN));
        const float_z &DENOMINATOR = VectorT(this->Direction).DotProduct(vN);

        if ( SFloat::IsZero(DENOMINATOR) ) // Ray is parallel to plane
            if ( SFloat::IsZero(NUMERATOR) ) // Ray lies on plane
                return EIntersections::E_Infinite;
            else // Ray is parallel but don't lies on plane.
                return EIntersections::E_None;
        else if ( SFloat::IsZero(NUMERATOR) ) // Ray origin lies on plane
        {
            vIntersection.x = this->Origin.x;
            vIntersection.y = this->Origin.y;
            vIntersection.z = this->Origin.z;
            return EIntersections::E_One;
        }
        else
        {
            const float_z &PARAM = NUMERATOR / DENOMINATOR;
            if ( SFloat::IsGreaterOrEquals(PARAM, SFloat::_0) ) // Intersection in one point.
            {
                vIntersection.x = this->Origin.x + PARAM * this->Direction.x;
                vIntersection.y = this->Origin.y + PARAM * this->Direction.y;
                vIntersection.z = this->Origin.z + PARAM * this->Direction.z;
                
                return EIntersections::E_One;
            }
            else // No intersection
                return EIntersections::E_None;
        }
    }

    /// <summary>
    /// Computes the intersection points between the ray and provided triangle.
    /// </summary>
    /// <remarks>
    /// If the direction of the ray is null, the result is undefined.<br/>
    /// If there's no intersection point, the output parameter won't be modified.
    /// </remarks>
    /// <param name="triangle">[IN] The triangle whose intersection with resident ray will be checked. If any of its vertices coincide, 
    /// the result is undefined.</param>
    /// <param name="vIntersection">[OUT] Closest intersection point to the ray's origin.</param>
    /// <returns>
    /// An enumerated value that indicates how many intersections were found:<br/>
    /// <br/>
    /// <b>None</b><br/>
    /// There are no intersections.<br/>
    ///
    /// <b>One</b><br/>
    /// There is one intersection.<br/>
    /// - The ray intersects with the interior (face) of the triangle in one point.
    /// - The ray intersects with a vertex of the triangle.
    /// - The origin of the ray is inside the triangle and the ray does not intersect with any edge.
    /// - The origin of the ray is inside the triangle and the ray intersect with an edge.
    /// - The origin of the ray belongs to an edge of the triangle.
    /// - The ray intersects with an edge of the triangle.
    /// - The origin of the ray coincides with a vertex of the triangle.
    ///
    /// <b>Two</b><br/>
    /// There are two intersections.<br/>
    /// - The origin of the ray belongs to an edge and the ray intersects with another edge.
    /// - The origin of the ray belongs to an edge and the ray intersects with a vertex of the edge.
    /// - The ray intersects with two edges of the triangle.
    /// </returns>
    EIntersections IntersectionPoint(const BaseTriangle<VectorT> &triangle, VectorT &vIntersection) const
    {
        VectorT vAux;
        return this->IntersectionPoint(triangle, vIntersection, vAux);
    }

    /// <summary>
    /// Computes the intersection point between the ray and provided triangle.
    /// </summary>
    /// <remarks>
    /// If the direction of the ray is null, the result is undefined.<br/>
    /// If there's no intersection point, the output parameters won't be modified.
    /// </remarks>
    /// <param name="triangle">[IN] The triangle whose intersection with the ray will be checked. If any of its vertices coincide, 
    /// the result is undefined.</param>
    /// <param name="vIntersection1">[OUT] Closest intersection point to the ray's origin.</param>
    /// <param name="vIntersection2">[OUT] Furthest intersection point to the ray's origin.</param>
    /// <returns>
    /// An enumerated value that indicates how many intersections were found:<br/>
    /// <br/>
    /// <b>None</b><br/>
    /// There are no intersections.<br/>
    ///
    /// <b>One</b><br/>
    /// There is one intersection.<br/>
    /// - The ray intersects with the interior (face) of the triangle in one point.
    /// - The ray intersects with a vertex of the triangle.
    /// - The origin of the ray is inside the triangle and the ray does not intersect with any edge.
    /// - The origin of the ray is inside the triangle and the ray intersect with an edge.
    /// - The origin of the ray belongs to an edge of the triangle.
    /// - The ray intersects with an edge of the triangle.
    /// - The origin of the ray coincides with a vertex of the triangle.
    ///
    /// <b>Two</b><br/>
    /// There are two intersections.<br/>
    /// - The origin of the ray belongs to an edge and the ray intersects with another edge.
    /// - The origin of the ray belongs to an edge and the ray intersects with a vertex of the edge.
    /// - The ray intersects with two edges of the triangle.
    /// </returns>
    EIntersections IntersectionPoint(const BaseTriangle<VectorT> &triangle, VectorT &vIntersection1, VectorT &vIntersection2) const
    {
        // Plane that contains triangle
        Plane auxP(triangle.A, triangle.B, triangle.C);

        VectorT vAux;

        const EIntersections &NUM_INTERSECT = this->IntersectionPoint(auxP, vAux);
        if (NUM_INTERSECT == EIntersections::E_Infinite) // Ray and plane are coplanar.
        {
            if ( PointInsideTriangle(triangle, this->Origin) ) // Ray origin is inside triangle
            {
                if (this->Origin == triangle.A) // Ray origin is A triangle vertex
                {
                    vIntersection1.x = this->Origin.x;
                    vIntersection1.y = this->Origin.y;
                    vIntersection1.z = this->Origin.z;

                    // Checks intersection with opposite edge
                    if (this->IntersectionPoint(BaseLineSegment<VectorT>(triangle.B, triangle.C), vAux) == EIntersections::E_None) // No intersection found
                        return EIntersections::E_One;
                    else // Intersection found
                    {
                        vIntersection2.x = vAux.x;
                        vIntersection2.y = vAux.y;
                        vIntersection2.z = vAux.z;
                        return EIntersections::E_Two;
                    }
                }
                else if (this->Origin == triangle.B) // Ray origin is B triangle vertex
                {
                    vIntersection1.x = this->Origin.x;
                    vIntersection1.y = this->Origin.y;
                    vIntersection1.z = this->Origin.z;

                   // Checks intersection with opposite edge
                    if (this->IntersectionPoint(BaseLineSegment<VectorT>(triangle.C, triangle.A), vAux) == EIntersections::E_None) // No intersection found
                        return EIntersections::E_One;
                    else // Intersection found
                    {
                        vIntersection2.x = vAux.x;
                        vIntersection2.y = vAux.y;
                        vIntersection2.z = vAux.z;
                        return EIntersections::E_Two;
                    }
                }
                else if (this->Origin == triangle.C) // Ray origin is C triangle vertex
                {
                    vIntersection1 = this->Origin;

                    // Checks intersection with opposite edge
                    if (this->IntersectionPoint(BaseLineSegment<VectorT>(triangle.A, triangle.B), vAux) == EIntersections::E_None) // No intersection found
                        return EIntersections::E_One;
                    else // Intersection found
                    {
                        vIntersection2.x = vAux.x;
                        vIntersection2.y = vAux.y;
                        vIntersection2.z = vAux.z;
                        return EIntersections::E_Two;
                    }
                }
                else if (SFloat::IsZero(LineSegment<VectorT>(triangle.A, triangle.B).MinDistance(this->Origin))) // Ray origin is in AB triangle edge
                {
                    vIntersection1.x = this->Origin.x;
                    vIntersection1.y = this->Origin.y;
                    vIntersection1.z = this->Origin.z;

                    if (this->IntersectionPoint(BaseLineSegment<VectorT>(triangle.B, triangle.C), vAux) == EIntersections::E_One ||
                        this->IntersectionPoint(BaseLineSegment<VectorT>(triangle.C, triangle.A), vAux) == EIntersections::E_One) // Ray intersects edge BC or CA
                    {
                        vIntersection2.x = vAux.x;
                        vIntersection2.y = vAux.y;
                        vIntersection2.z = vAux.z;
                        return EIntersections::E_Two;
                    }
                    else // Ray doesn't intersect with other edge
                    {
                        return EIntersections::E_One;
                    }
                }
                else if (SFloat::IsZero(LineSegment<VectorT>(triangle.B, triangle.C).MinDistance(this->Origin))) // Ray origin is in BC triangle edge
                {
                    vIntersection1.x = this->Origin.x;
                    vIntersection1.y = this->Origin.y;
                    vIntersection1.z = this->Origin.z;

                    if (this->IntersectionPoint(BaseLineSegment<VectorT>(triangle.C, triangle.A), vAux) == EIntersections::E_One ||
                        this->IntersectionPoint(BaseLineSegment<VectorT>(triangle.A, triangle.B), vAux) == EIntersections::E_One) // Ray intersects edge BC or CA
                    {
                        vIntersection2.x = vAux.x;
                        vIntersection2.y = vAux.y;
                        vIntersection2.z = vAux.z;
                        return EIntersections::E_Two;
                    }
                    else // Ray doesn't intersect with other edge
                    {
                        return EIntersections::E_One;
                    }
                }
                else if (SFloat::IsZero(LineSegment<VectorT>(triangle.C, triangle.A).MinDistance(this->Origin))) // Ray origin is in CA triangle edge
                {
                    vIntersection1.x = this->Origin.x;
                    vIntersection1.y = this->Origin.y;
                    vIntersection1.z = this->Origin.z;

                    if (this->IntersectionPoint(BaseLineSegment<VectorT>(triangle.A, triangle.B), vAux) == EIntersections::E_One ||
                        this->IntersectionPoint(BaseLineSegment<VectorT>(triangle.B, triangle.C), vAux) == EIntersections::E_One) // Ray intersects edge BC or CA
                    {
                        vIntersection2.x = vAux.x;
                        vIntersection2.y = vAux.y;
                        vIntersection2.z = vAux.z;
                        return EIntersections::E_Two;
                    }
                    else // Ray doesn't intersect with other edge
                    {
                        return EIntersections::E_One;
                    }
                }
                else // Ray origin is strictly inside triangle (is not in a vertex or an edge
                {
                    if (this->IntersectionPoint(BaseLineSegment<VectorT>(triangle.A, triangle.B), vAux) == EIntersections::E_One ||
                        this->IntersectionPoint(BaseLineSegment<VectorT>(triangle.B, triangle.C), vAux) == EIntersections::E_One ||
                        this->IntersectionPoint(BaseLineSegment<VectorT>(triangle.C, triangle.A), vAux) == EIntersections::E_One )
                    {
                        vIntersection1.x = vAux.x;
                        vIntersection1.y = vAux.y;
                        vIntersection1.z = vAux.z;
                    }
                    else
                        Z_ASSERT_WARNING(false, "Something went really wrong, this code branch must never be reached");  // Something is wrong, if ray point is interior, it must be ONE intersection with a edge.

                    return EIntersections::E_One;
                }
            }
            else // Ray origin is outside triangle
            {
                VectorT vPrevInt;
                bool bPrevInt = false;

                VectorT vAuxAB;
                EIntersections numIntersectAB = this->IntersectionPoint(BaseLineSegment<VectorT>(triangle.A, triangle.B), vAuxAB); // Checks intersection with AB edge
                if (numIntersectAB == EIntersections::E_Two) // Ray contains AB edge
                {
                    // Looks for closest point to ray origin
                    if  ( (triangle.A - this->Origin).GetSquaredLength() < (triangle.B - this->Origin).GetSquaredLength() )
                    {
                        vIntersection1.x = triangle.A.x;
                        vIntersection1.y = triangle.A.y;
                        vIntersection1.z = triangle.A.z;
                        vIntersection2.x = triangle.B.x;
                        vIntersection2.y = triangle.B.y;
                        vIntersection2.z = triangle.B.z;
                    }
                    else
                    {
                        vIntersection1.x = triangle.B.x;
                        vIntersection1.y = triangle.B.y;
                        vIntersection1.z = triangle.B.z;
                        vIntersection2.x = triangle.A.x;
                        vIntersection2.y = triangle.A.y;
                        vIntersection2.z = triangle.A.z;
                    }
                    return EIntersections::E_Two;
                }

                VectorT vAuxBC;
                EIntersections numIntersectBC = this->IntersectionPoint(BaseLineSegment<VectorT>(triangle.B, triangle.C), vAuxBC); // Checks intersection with BC edge
                if (numIntersectBC == EIntersections::E_Two) // Ray contains BC edge
                {
                    // Looks for closest point to ray origin
                    if  ( (triangle.B - this->Origin).GetSquaredLength() < (triangle.C - this->Origin).GetSquaredLength() )
                    {
                        vIntersection1.x = triangle.B.x;
                        vIntersection1.y = triangle.B.y;
                        vIntersection1.z = triangle.B.z;
                        vIntersection2.x = triangle.C.x;
                        vIntersection2.y = triangle.C.y;
                        vIntersection2.z = triangle.C.z;
                    }
                    else
                    {
                        vIntersection1.x = triangle.C.x;
                        vIntersection1.y = triangle.C.y;
                        vIntersection1.z = triangle.C.z;
                        vIntersection2.x = triangle.B.x;
                        vIntersection2.y = triangle.B.y;
                        vIntersection2.z = triangle.B.z;
                    }
                    return EIntersections::E_Two;
                }

                VectorT vAuxCA;
                EIntersections numIntersectCA = this->IntersectionPoint(BaseLineSegment<VectorT>(triangle.C, triangle.A), vAuxCA); // Checks intersection with BC edge
                if (numIntersectCA == EIntersections::E_Two) // Ray contains CA edge
                {
                    // Looks for closest point to ray origin
                    if  ( (triangle.C - this->Origin).GetSquaredLength() < (triangle.A - this->Origin).GetSquaredLength() )
                    {
                        vIntersection1.x = triangle.C.x;
                        vIntersection1.y = triangle.C.y;
                        vIntersection1.z = triangle.C.z;
                        vIntersection2.x = triangle.A.x;
                        vIntersection2.y = triangle.A.y;
                        vIntersection2.z = triangle.A.z;
                    }
                    else
                    {
                        vIntersection1.x = triangle.A.x;
                        vIntersection1.y = triangle.A.y;
                        vIntersection1.z = triangle.A.z;
                        vIntersection2.x = triangle.C.x;
                        vIntersection2.y = triangle.C.y;
                        vIntersection2.z = triangle.C.z;
                    }
                    return EIntersections::E_Two;
                }

                if (numIntersectAB == EIntersections::E_One) // Ray has ONE intersection with AB edge
                {
                    bPrevInt = true;
                    vPrevInt.x = vAuxAB.x;
                    vPrevInt.y = vAuxAB.y;
                    vPrevInt.z = vAuxAB.z;
                }

                if (numIntersectBC == EIntersections::E_One) // Ray has ONE intersection with BC edge
                {
                    if (bPrevInt) // There is a previous intersection with an edge
                    {
                        if (vAuxBC != vPrevInt)
                        {
                            // Looks for closest point to ray origin
                            if  ( (vAuxBC - this->Origin).GetSquaredLength() < (vPrevInt - this->Origin).GetSquaredLength() )
                            {
                                vIntersection1.x = vAuxBC.x;
                                vIntersection1.y = vAuxBC.y;
                                vIntersection1.z = vAuxBC.z;
                                vIntersection2.x = vPrevInt.x;
                                vIntersection2.y = vPrevInt.y;
                                vIntersection2.z = vPrevInt.z;
                            }
                            else
                            {
                                vIntersection1.x = vPrevInt.x;
                                vIntersection1.y = vPrevInt.y;
                                vIntersection1.z = vPrevInt.z;
                                vIntersection2.x = vAuxBC.x;
                                vIntersection2.y = vAuxBC.y;
                                vIntersection2.z = vAuxBC.z;
                            }
                            return EIntersections::E_Two;
                        }
                    }
                    else // Its the first intersection found
                    {
                        bPrevInt = true;
                        vPrevInt = vAuxBC;
                    }
                }

                if (numIntersectCA == EIntersections::E_One)
                {
                    if (bPrevInt) // There is a previous intersection with an edge
                    {
                        if (vAuxCA != vPrevInt)
                        {
                            // Looks for closest point to ray origin
                            if  ( (vAuxCA - this->Origin).GetSquaredLength() < (vPrevInt - this->Origin).GetSquaredLength() )
                            {
                                vIntersection1.x = vAuxCA.x;
                                vIntersection1.y = vAuxCA.y;
                                vIntersection1.z = vAuxCA.z;
                                vIntersection2.x = vPrevInt.x;
                                vIntersection2.y = vPrevInt.y;
                                vIntersection2.z = vPrevInt.z;
                            }
                            else
                            {
                                vIntersection1.x = vPrevInt.x;
                                vIntersection1.y = vPrevInt.y;
                                vIntersection1.z = vPrevInt.z;
                                vIntersection2.x = vAuxCA.x;
                                vIntersection2.y = vAuxCA.y;
                                vIntersection2.z = vAuxCA.z;
                            }
                            return EIntersections::E_Two;
                        }
                    }
                    else
                        Z_ASSERT_WARNING(false, "Something went really wrong, this code branch must never be reached");  // Something is wrong, there is ONE intersection and is not a vertex
                }

                if (bPrevInt)
                {
                    vIntersection1.x = vPrevInt.x;
                    vIntersection1.y = vPrevInt.y;
                    vIntersection1.z = vPrevInt.z;
                    return EIntersections::E_One;
                }
                else
                    return EIntersections::E_None;
            }
        }
        else if (NUM_INTERSECT == EIntersections::E_One) // Ray and plane intersects in one point, are not coplanar
        {
            if (this->PointInsideTriangle(triangle, vAux) )
            {
                vIntersection1.x = vAux.x;
                vIntersection1.y = vAux.y;
                vIntersection1.z = vAux.z;
                return EIntersections::E_One;
            }
            else
                return EIntersections::E_None;
        }
        else
            return EIntersections::E_None;;
    }

    /// <summary>
    /// Computes the intersection point between the ray and provided hexahedron.
    /// </summary>
    /// <remarks>
    /// If the direction of the ray is null, the result is undefined.<br/>
    /// The hexahedron must be convex for the operation to return correct results.<br/>
    /// If there's no intersection point, the output parameter used for storing the intersection point won't be modified.
    /// </remarks>
    /// <param name="hexahedron">[IN] The hexahedron whose intersections with the ray are wanted. It must be convex for the operation to return correct 
    /// results. If any of its vertices coincide, the result is undefined.</param>
    /// <param name="vIntersection">[OUT] Closest intersection point to the ray's origin.</param>
    /// <returns>
    /// An enumerated value that indicates how many intersections were found:<br/>
    /// <br/>
    /// <b>None</b><br/>
    /// There are no intersections.<br/>
    ///
    /// <b>One</b><br/>
    /// There is one intersection.<br/>
    /// - The ray intersects with a vertex of the hexahedron.
    /// - The origin of the ray is contained in the hexahedron.
    /// - The origin of the ray belongs to an edge of the hexahedron.
    /// - The ray intersects with an edge of the hexahedron in only one point.
    /// - The origin of the ray coincides with a vertex of the hexahedron and the ray does not point to the hexahedron.
    ///
    /// <b>Two</b><br/>
    /// There are two intersections.<br/>
    /// - The ray intersects with two faces of the hexahedron.
    /// - The origin of the ray belongs to a face of the hexahedron and the ray intersects an edge of the face.
    /// - The origin of the ray belongs to an edge of the hexahedron and the ray points to the hexahedron.
    /// - The origin of the ray coincides with a vertex of the hexahedron and the ray points to the hexahedron.
    /// </returns>
    EIntersections IntersectionPoint(const BaseHexahedron<VectorT> &hexahedron, VectorT &vIntersection) const
    {
        VectorT vAux;
        return this->IntersectionPoint(hexahedron, vIntersection, vAux);
    }

    /// <summary>
    /// Computes the intersection points between the ray and provided hexahedron.
    /// </summary>
    /// <remarks>
    /// If the direction of the ray is null, the result is undefined.<br/>
    /// The hexahedron must be convex for the operation to return correct results.<br/>
    /// If there are no intersection point, the output parameters used for storing the intersection points will not be modified.
    /// </remarks>
    /// <param name="hexahedron">[IN] The hexahedron whose intersections with the ray are wanted. It must be convex for the operation to return correct 
    /// results. If any of its vertices coincide, the result is undefined.</param>
    /// <param name="vIntersection1">[OUT] Closest intersection point to the ray's origin.</param>
    /// <param name="vIntersection2">[OUT] Furthest intersection point to the ray's origin.</param>
    /// <returns>
    /// An enumerated value that indicates how many intersections were found:<br/>
    /// <br/>
    /// <b>None</b><br/>
    /// There are no intersections.<br/>
    ///
    /// <b>One</b><br/>
    /// There is one intersection.<br/>
    /// - The ray intersects with a vertex of the hexahedron.
    /// - The origin of the ray is contained in the hexahedron.
    /// - The origin of the ray belongs to an edge of the hexahedron.
    /// - The ray intersects with an edge of the hexahedron in only one point.
    /// - The origin of the ray coincides with a vertex of the hexahedron and the ray does not point to the hexahedron.
    ///
    /// <b>Two</b><br/>
    /// There are two intersections.<br/>
    /// - The ray intersects with two faces of the hexahedron.
    /// - The origin of the ray belongs to a face of the hexahedron and the ray intersects an edge of the face.
    /// - The origin of the ray belongs to an edge of the hexahedron and the ray points to the hexahedron.
    /// - The origin of the ray coincides with a vertex of the hexahedron and the ray points to the hexahedron.
    /// </returns>
    EIntersections IntersectionPoint(const BaseHexahedron<VectorT> &hexahedron, VectorT &vIntersection1, VectorT &vIntersection2) const
    {
        VectorT vAuxPoint, vAux1, vAux2;
        bool bPreviousInt = false;

        // Check if resident ray intersects ABCD face
        EIntersections value1 = this->IntersectionPoint(hexahedron.A, hexahedron.B, hexahedron.C, hexahedron.D, vAux1, vAux2);

        if ( value1 == EIntersections::E_Two ) // There are 2 intersections
        {
            vIntersection1.x = vAux1.x;
            vIntersection1.y = vAux1.y;
            vIntersection1.z = vAux1.z;
            vIntersection2.x = vAux2.x;
            vIntersection2.y = vAux2.y;
            vIntersection2.z = vAux2.z;
            return EIntersections::E_Two;
        }
        else if (value1 == EIntersections::E_One) // There is only one intersection
        {
            vAuxPoint = vAux1;
            bPreviousInt = true;
        }

        // Check if resident ray intersects EFGH face
        EIntersections value2 = this->IntersectionPoint(hexahedron.E, hexahedron.F, hexahedron.G, hexahedron.H, vAux1, vAux2);

        if ( value2 == EIntersections::E_Two ) // There are 2 intersections
        {
            vIntersection1.x = vAux1.x;
            vIntersection1.y = vAux1.y;
            vIntersection1.z = vAux1.z;
            vIntersection2.x = vAux2.x;
            vIntersection2.y = vAux2.y;
            vIntersection2.z = vAux2.z;
            return EIntersections::E_Two;
        }
        else if (value2 == EIntersections::E_One) // There is only one intersection
        {
            if (bPreviousInt && (vAuxPoint != vAux1)) // There is one intersection with other face and both points are not the same
            {
                if  ( (vAuxPoint - this->Origin).GetSquaredLength() < (vAux1 - this->Origin).GetSquaredLength() ) // Computes the closest intersection to ray origin
                {
                    vIntersection1.x = vAuxPoint.x;
                    vIntersection1.y = vAuxPoint.y;
                    vIntersection1.z = vAuxPoint.z;
                    vIntersection2.x = vAux1.x;
                    vIntersection2.y = vAux1.y;
                    vIntersection2.z = vAux1.z;
                }
                else
                {
                    vIntersection1.x = vAux1.x;
                    vIntersection1.y = vAux1.y;
                    vIntersection1.z = vAux1.z;
                    vIntersection2.x = vAuxPoint.x;
                    vIntersection2.y = vAuxPoint.y;
                    vIntersection2.z = vAuxPoint.z;
                }
                return EIntersections::E_Two;
            }
            else
            {
                vAuxPoint = vAux1;
                bPreviousInt = true;
            }
        }

        // Check if resident ray intersects ABHE face
        EIntersections value3 = this->IntersectionPoint(hexahedron.A, hexahedron.B, hexahedron.H, hexahedron.E, vAux1, vAux2);

        if ( value3 == EIntersections::E_Two ) // There are 2 intersections
        {
            vIntersection1.x = vAux1.x;
            vIntersection1.y = vAux1.y;
            vIntersection1.z = vAux1.z;
            vIntersection2.x = vAux2.x;
            vIntersection2.y = vAux2.y;
            vIntersection2.z = vAux2.z;
            return EIntersections::E_Two;
        }
        else if (value3 == EIntersections::E_One) // There is only one intersection
        {
            if (bPreviousInt && (vAuxPoint != vAux1)) // There is one intersection with other face and both points are not the same
            {
                if  ( (vAuxPoint - this->Origin).GetSquaredLength() < (vAux1 - this->Origin).GetSquaredLength() ) // Computes the closest intersection to ray origin
                {
                    vIntersection1.x = vAuxPoint.x;
                    vIntersection1.y = vAuxPoint.y;
                    vIntersection1.z = vAuxPoint.z;
                    vIntersection2.x = vAux1.x;
                    vIntersection2.y = vAux1.y;
                    vIntersection2.z = vAux1.z;
                }
                else
                {
                    vIntersection1.x = vAux1.x;
                    vIntersection1.y = vAux1.y;
                    vIntersection1.z = vAux1.z;
                    vIntersection2.x = vAuxPoint.x;
                    vIntersection2.y = vAuxPoint.y;
                    vIntersection2.z = vAuxPoint.z;
                }
                return EIntersections::E_Two;
            }
            else
            {
                vAuxPoint = vAux1;
                bPreviousInt = true;
            }
        }

        // Check if resident ray intersects BCGH face
        EIntersections value4 = this->IntersectionPoint(hexahedron.B, hexahedron.C, hexahedron.G, hexahedron.H, vAux1,vAux2);

        if ( value4 == EIntersections::E_Two ) // There are 2 intersections
        {
            vIntersection1.x = vAux1.x;
            vIntersection1.y = vAux1.y;
            vIntersection1.z = vAux1.z;
            vIntersection2.x = vAux2.x;
            vIntersection2.y = vAux2.y;
            vIntersection2.z = vAux2.z;
            return EIntersections::E_Two;
        }
        else if (value4 == EIntersections::E_One) // There is only one intersection
        {
            if (bPreviousInt && (vAuxPoint != vAux1)) // There is one intersection with other face and both points are not the same
            {
                if  ( (vAuxPoint - this->Origin).GetSquaredLength() < (vAux1 - this->Origin).GetSquaredLength() ) // Computes the closest intersection to ray origin
                {
                    vIntersection1.x = vAuxPoint.x;
                    vIntersection1.y = vAuxPoint.y;
                    vIntersection1.z = vAuxPoint.z;
                    vIntersection2.x = vAux1.x;
                    vIntersection2.y = vAux1.y;
                    vIntersection2.z = vAux1.z;
                }
                else
                {
                    vIntersection1.x = vAux1.x;
                    vIntersection1.y = vAux1.y;
                    vIntersection1.z = vAux1.z;
                    vIntersection2.x = vAuxPoint.x;
                    vIntersection2.y = vAuxPoint.y;
                    vIntersection2.z = vAuxPoint.z;
                }
                return EIntersections::E_Two;
            }
            else
            {
                vAuxPoint = vAux1;
                bPreviousInt = true;
            }
        }

        // Check if resident ray intersects ADFE face
        EIntersections value5 = this->IntersectionPoint(hexahedron.A, hexahedron.D, hexahedron.F, hexahedron.E, vAux1, vAux2);

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
                if  ( (vAuxPoint - this->Origin).GetSquaredLength() < (vAux1 - this->Origin).GetSquaredLength() ) // Computes the closest intersection ray origin
                {
                    vIntersection1.x = vAuxPoint.x;
                    vIntersection1.y = vAuxPoint.y;
                    vIntersection1.z = vAuxPoint.z;
                    vIntersection2.x = vAux1.x;
                    vIntersection2.y = vAux1.y;
                    vIntersection2.z = vAux1.z;
                }
                else
                {
                    vIntersection1.x = vAux1.x;
                    vIntersection1.y = vAux1.y;
                    vIntersection1.z = vAux1.z;
                    vIntersection2.x = vAuxPoint.x;
                    vIntersection2.y = vAuxPoint.y;
                    vIntersection2.z = vAuxPoint.z;
                }
                return EIntersections::E_Two;
            }
            else
            {
                vAuxPoint = vAux1;
                bPreviousInt = true;
            }
        }

        // Check if resident ray intersects CDFG face
        EIntersections value6 = this->IntersectionPoint(hexahedron.C, hexahedron.D, hexahedron.F, hexahedron.G, vAux1, vAux2);

        if ( value6 == EIntersections::E_Two ) // There are 2 intersections
        {
            vIntersection1.x = vAux1.x;
            vIntersection1.y = vAux1.y;
            vIntersection1.z = vAux1.z;
            vIntersection2.x = vAux2.x;
            vIntersection2.y = vAux2.y;
            vIntersection2.z = vAux2.z;
            return EIntersections::E_Two;
        }
        else if (value6 == EIntersections::E_One) // There is only one intersection
        {
            if (bPreviousInt && (vAuxPoint != vAux1)) // There is one intersection with other face and both points are not the same
            {
                if  ( (vAuxPoint - this->Origin).GetSquaredLength() < (vAux1 - this->Origin).GetSquaredLength() ) // Computes the closest intersection to ray origin
                {
                    vIntersection1.x = vAuxPoint.x;
                    vIntersection1.y = vAuxPoint.y;
                    vIntersection1.z = vAuxPoint.z;
                    vIntersection2.x = vAux1.x;
                    vIntersection2.y = vAux1.y;
                    vIntersection2.z = vAux1.z;
                }
                else
                {
                    vIntersection1.x = vAux1.x;
                    vIntersection1.y = vAux1.y;
                    vIntersection1.z = vAux1.z;
                    vIntersection2.x = vAuxPoint.x;
                    vIntersection2.y = vAuxPoint.y;
                    vIntersection2.z = vAuxPoint.z;
                }
                return EIntersections::E_Two;
            }
            else
            {
                vAuxPoint = vAux1;
                bPreviousInt = true;
            }
        }

        if (bPreviousInt) // There is only one intersection with hexahedron
        {
            vIntersection1.x = vAuxPoint.x;
            vIntersection1.y = vAuxPoint.y;
            vIntersection1.z = vAuxPoint.z;
            return EIntersections::E_One;
        }
        else // There are no intersections with hexahedron
            return EIntersections::E_None;
    }

    /// <summary>
    /// Checks the relation between resident ray and the provided plane.
    /// </summary>
    /// <remarks>
    /// If the direction of the ray is null, the result is undefined.<br/>
    /// Note that if the origin of resident ray lies on the plane, we don't consider that the ray is crossing the plane.
    /// </remarks>
    /// <param name="plane">[IN] The plane we want check the relation with resident ray. If it is null, the result is undefined.</param>
    /// <returns>
    /// An enumerated value like follows:<br/>
    /// - 0 (E_Contained): The ray lies on plane.
    /// - 1 (E_PositiveSide): The ray is fully contained in the positive side of the space defined by the plane.<br/>
    /// - 2 (E_NegativeSide): The ray is fully contained in the negative side of the space defined by the plane.<br/>
    /// - 3 (E_BothSides): The ray cross the plane.<br/>
    /// We consider "positive part of the space" the locus of points which verifies \f$ Ax + By + Cz + D > 0 \f$.
    /// </returns>
    ESpaceRelation SpaceRelation(const BasePlane &plane) const
    {
        // The plane shouldn't be null
        Z_ASSERT_WARNING( !(SFloat::IsZero(plane.a) && SFloat::IsZero(plane.b) && SFloat::IsZero(plane.c)), "The input plane shouldn't be null" );

        // The direction vector of the ray mustn't be null
        Z_ASSERT_WARNING( !this->Direction.IsZero(), "The direction vector of the ray mustn't be null" );

        // We take as auxiliar point the head of the direction vector, as if it was positioned in the origin point of the ray
        Vector3 vAux(Vector3(this->Origin) + this->Direction);

        // Distances to the plane from both auxiliar point and origin of ray
        // To compare the two distances is not necessary to divide by de normal length (it is invariant)
        const float_z& DIST_ORIGIN = plane.a * this->Origin.x + plane.b * this->Origin.y + plane.c * this->Origin.z + plane.d;
        const float_z& DIST_AUX = plane.a * vAux.x + plane.b * vAux.y + plane.c * vAux.z + plane.d;

        if ( SFloat::IsZero(DIST_ORIGIN) ) // Origin point of ray lies on plane
        {
            if ( SFloat::IsZero(DIST_AUX) ) // Ray lies on plane
                return ESpaceRelation::E_Contained;
            else if ( SFloat::IsNegative(DIST_AUX) ) // Direction vector goes to positive side
                return ESpaceRelation::E_NegativeSide;
            else // Direction vector goes to negative side
                return ESpaceRelation::E_PositiveSide;
        }
        else if ( SFloat::IsNegative(DIST_ORIGIN) )// Origin point of ray is in negative side
        {
            if ( SFloat::IsLessOrEquals(DIST_AUX, DIST_ORIGIN) ) // Direction vector moves away from plane or is parallel to it.
                return ESpaceRelation::E_NegativeSide;
            else // Direction vector is approaching to plane
                return ESpaceRelation::E_BothSides;
        }
        else // Origin point of ray is in positive side
        {
            if ( SFloat::IsGreaterOrEquals(DIST_AUX, DIST_ORIGIN) ) // Direction vector moves away from plane or is parallel to it.
                return ESpaceRelation::E_PositiveSide;
            else // Direction vector is approaching to plane
                return ESpaceRelation::E_BothSides;
        }
    }

    /// <summary>
    /// This method rotates the resident ray applying the rotation contained in the provided quaternion
    /// around the coordinate axis centre.
    /// </summary>
    /// <param name="qRotation">[IN] Quaternion which contains the rotation to be applied.</param>
    /// <returns>
    /// The rotated ray.
    /// </returns>
    Ray3D<VectorT> Rotate(const Quaternion &qRotation) const
    {
        Ray3D<VectorT> auxRay = *this;
        SPoint::Rotate(qRotation, &auxRay.Origin, 1);
        SPoint::Rotate(qRotation, &auxRay.Direction, 1);
        return auxRay;
    }

    /// <summary>
    /// This method rotates the resident ray applying the rotation contained in the provided quaternion
    /// around the point provided as pivot.
    /// </summary>
    /// <param name="qRotation">[IN] Quaternion which contains the rotation to be applied.</param>
    /// <param name="vPivot">[IN] Point which acts as pivot.</param>
    /// <returns>
    /// The rotated ray.
    /// </returns>
    Ray3D<VectorT> RotateWithPivot(const Quaternion &qRotation, const VectorT &vPivot) const
    {
        Ray3D<VectorT> auxRay = *this;
        SPoint::RotateWithPivot(qRotation, vPivot, &auxRay.Origin, 1);
        SPoint::Rotate(qRotation, &auxRay.Direction, 1);
        return auxRay;
    }

    /// <summary>
    /// This method translates the resident ray by the translation contained in the provided vector.
    /// </summary>
    /// <param name="vTranslation">[IN] Vector which contains the translation to be applied.</param>
    /// <returns>
    /// The translated ray.
    /// </returns>
    Ray3D<VectorT> Translate(const BaseVector3 &vTranslation) const
    {
        Ray3D<VectorT> auxRay = *this;
        SPoint::Translate(vTranslation, &auxRay.Origin, 1);
        return auxRay;
    }

    /// <summary>
    /// This method translates the resident ray by the provided amounts for every axis.
    /// </summary>
    /// <param name="fTranslationX">[IN] Amount of translation in X direction.</param>
    /// <param name="fTranslationY">[IN] Amount of translation in Y direction.</param>
    /// <param name="fTranslationZ">[IN] Amount of translation in Z direction.</param>
    /// <returns>
    /// The translated ray.
    /// </returns>
    Ray3D<VectorT> Translate(const float_z fTranslationX, const float_z fTranslationY, const float_z fTranslationZ) const
    {
        Ray3D<VectorT> auxRay = *this;
        SPoint::Translate(fTranslationX, fTranslationY, fTranslationZ, &auxRay.Origin, 1);
        return auxRay;
    }

    /// <summary>
    /// This method scales the resident ray by the scale contained in the provided vector.
    /// </summary>
    /// <remarks>
    /// Resultant ray is normalized after this operation.<br/>
    /// If the direction of the ray is null, the result is undefined.
    /// </remarks>
    /// <param name="vScale">[IN] Vector which contains the scale to be applied in every axis. If it is null, the result is undefined.</param>
    /// <returns>
    /// The scaled ray.
    /// </returns>
    Ray3D<VectorT> Scale(const BaseVector3 &vScale) const
    {
        Ray3D<VectorT> auxRay = *this;
        SPoint::Scale(vScale, &auxRay.Origin, 1);
        SPoint::Scale(vScale, &auxRay.Direction, 1);
        return Ray3D<VectorT>(auxRay.Origin, auxRay.Direction.Normalize());
    }

    /// <summary>
    /// This method scales the resident ray by the amounts provided for every axis.
    /// </summary>
    /// <remarks>
    /// Resultant ray is normalized after this operation.<br/>
    /// If the direction of the ray is null, the result is undefined.
    /// </remarks>
    /// <param name="fScaleX">[IN] Scale to be applied in X direction. If it equals zero, the result is undefined.</param>
    /// <param name="fScaleY">[IN] Scale to be applied in Y direction. If it equals zero, the result is undefined.</param>
    /// <param name="fScaleZ">[IN] Scale to be applied in Z direction. If it equals zero, the result is undefined.</param>
    /// <returns>
    /// The scaled ray.
    /// </returns>
    Ray3D<VectorT> Scale(const float_z fScaleX, const float_z fScaleY, const float_z fScaleZ) const
    {
        Ray3D<VectorT> auxRay = *this;
        SPoint::Scale(fScaleX, fScaleY, fScaleZ, &auxRay.Origin, 1);
        SPoint::Scale(fScaleX, fScaleY, fScaleZ, &auxRay.Direction, 1);
        return Ray3D<VectorT>(auxRay.Origin, auxRay.Direction.Normalize());
    }

    /// <summary>
    /// This method scales the resident ray by the scale contained in the provided vector from
    /// the provided point that acts as pivot.
    /// </summary>
    /// <remarks>
    /// Resultant ray is normalized after this operation.<br/>
    /// If the direction of the ray is null, the result is undefined.
    /// </remarks>
    /// <param name="vScale">[IN] Vector which contains the scale to be applied in every axis. If it is null, the result is undefined.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot of the scale.</param>
    /// <returns>
    /// The scaled ray.
    /// </returns>
    Ray3D<VectorT> ScaleWithPivot(const BaseVector3 &vScale, const VectorT &vPivot) const
    {
        Ray3D<VectorT> auxRay = *this;
        SPoint::ScaleWithPivot(vScale, vPivot, &auxRay.Origin, 1);
        SPoint::Scale(vScale, &auxRay.Direction, 1);
        return Ray3D<VectorT>(auxRay.Origin, auxRay.Direction.Normalize());
    }

    /// <summary>
    /// This method scales the resident ray by the amounts provided for every axis from
    /// the provided point that acts as pivot.
    /// </summary>
    /// <remarks>
    /// Resultant ray is normalized after this operation.<br/>
    /// If the direction of the ray is null, the result is undefined.
    /// </remarks>
    /// <param name="fScaleX">[IN] Scale to be applied in X direction. If it equals zero, the result is undefined.</param>
    /// <param name="fScaleY">[IN] Scale to be applied in Y direction. If it equals zero, the result is undefined.</param>
    /// <param name="fScaleZ">[IN] Scale to be applied in Z direction. If it equals zero, the result is undefined.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot of the scale.</param>
    /// <returns>
    /// The scaled ray.
    /// </returns>
    Ray3D<VectorT> ScaleWithPivot(const float_z fScaleX, const float_z fScaleY, const float_z fScaleZ, const VectorT &vPivot) const
    {
        Ray3D<VectorT> auxRay = *this;
        SPoint::ScaleWithPivot(fScaleX, fScaleY, fScaleZ, vPivot, &auxRay.Origin, 1);
        SPoint::Scale(fScaleX, fScaleY, fScaleZ, &auxRay.Direction, 1);
        return Ray3D<VectorT>(auxRay.Origin, auxRay.Direction.Normalize());
    }

    /// <summary>
    /// This method rotates the resident ray applying the rotation contained in the provided matrix
    /// around the coordinate axis centre.
    /// </summary>
    /// <param name="rotation">[IN] Rotation matrix which contains the rotation to be applied.</param>
    /// <returns>
    /// The rotated ray.
    /// </returns>
    Ray3D<VectorT> Rotate(const RotationMatrix3x3 &rotation) const
    {
        Ray3D<VectorT> auxRay = *this;
        SPoint::Rotate(rotation, &auxRay.Origin, 1);
        SPoint::Rotate(rotation, &auxRay.Direction, 1);
        return auxRay;
    }

    /// <summary>
    /// This method translates the resident ray by the translation contained in the provided matrix.
    /// </summary>
    /// <param name="translation">[IN] Matrix which contains the translation to be applied.</param>
    /// <returns>
    /// The translated ray.
    /// </returns>
    Ray3D<VectorT> Translate(const TranslationMatrix<Matrix4x3> &translation) const
    {
        Ray3D<VectorT> auxRay = *this;
        SPoint::Translate(translation, &auxRay.Origin, 1);
        return auxRay;
    }

    /// <summary>
    /// This method translates the resident ray by the translation contained in the provided matrix.
    /// </summary>
    /// <param name="translation">[IN] Matrix which contains the translation to be applied.</param>
    /// <returns>
    /// The translated ray.
    /// </returns>
    Ray3D<VectorT> Translate(const TranslationMatrix<Matrix4x4> &translation) const
    {
        Ray3D<VectorT> auxRay = *this;
        SPoint::Translate(translation, &auxRay.Origin, 1);
        return auxRay;
    }

    /// <summary>
    /// This method scales the resident ray by the scale contained in the provided matrix.
    /// </summary>
    /// <remarks>
    /// Resultant ray is normalized after this operation.<br/>
    /// If the direction of the ray is null, the result is undefined.
    /// </remarks>
    /// <param name="scale">[IN] Matrix which contains the scale to be applied in every axis. If it is null, the result is undefined.</param>
    /// <returns>
    /// The scaled ray.
    /// </returns>
    Ray3D<VectorT> Scale(const ScalingMatrix3x3 &scale) const
    {
        Ray3D<VectorT> auxRay = *this;
        SPoint::Scale(scale, &auxRay.Origin, 1);
        SPoint::Scale(scale, &auxRay.Direction, 1);
        return Ray3D<VectorT>(auxRay.Origin, auxRay.Direction.Normalize());
    }

    /// <summary>
    /// This method applies to the resident ray the transformation contained in the provided matrix.
    /// </summary>
    /// <remarks>
    /// Resultant ray is normalized after this operation.<br/>
    /// If the direction of the ray is null, the result is undefined.
    /// </remarks>
    /// <param name="transformation">[IN] Matrix which contains the transformation to be applied. If it is null, the result is undefined.</param>
    /// <returns>
    /// The transformed ray.
    /// </returns>
    Ray3D<VectorT> Transform(const TransformationMatrix<Matrix4x3> &transformation) const
    {
        return this->TransformImp(transformation);
    }

    /// <summary>
    /// This method applies to the resident ray the transformation contained in the provided matrix.
    /// </summary>
    /// <remarks>
    /// Resultant ray is normalized after this operation.<br/>
    /// If the direction of the ray is null, the result is undefined.
    /// </remarks>
    /// <param name="transformation">[IN] Matrix which contains the transformation to be applied. If it is null, the result is undefined.</param>
    /// <returns>
    /// The transformed ray.
    /// </returns>
    Ray3D<VectorT> Transform(const TransformationMatrix<Matrix4x4> &transformation) const
    {
        return this->TransformImp(transformation);
    }

    /// <summary>
    /// This method applies to the resident ray the transformation contained in the provided matrix.
    /// </summary>
    /// <remarks>
    /// Resultant ray is normalized after this operation.
    /// </remarks>
    /// <param name="spaceConversion">[IN] Matrix which contains the transformation to be applied.</param>
    /// <returns>
    /// The transformed ray.
    /// </returns>
    Ray3D<VectorT> Transform(const SpaceConversionMatrix &spaceConversion) const
    {
        return Ray3D<VectorT>(this->Origin.Transform(spaceConversion), 
                                  this->Direction.Transform(spaceConversion));
    }

    /// <summary>
    /// This method rotates the resident ray applying the rotation contained in the provided matrix
    /// around a given point that acts as pivot of rotation.
    /// </summary>
    /// <param name="rotation">[IN] Rotation matrix which contains the rotation to be applied.</param>
    /// <param name="vPivot">[IN] Point which acts as pivot.</param>
    /// <returns>
    /// The rotated ray.
    /// </returns>
    Ray3D<VectorT> RotateWithPivot(const RotationMatrix3x3 &rotation, const VectorT &vPivot) const
    {
        Ray3D<VectorT> auxRay = *this;
        SPoint::RotateWithPivot(rotation, vPivot, &auxRay.Origin, 1);
        SPoint::Rotate(rotation, &auxRay.Direction, 1);
        return auxRay;
    }

    /// <summary>
    /// This method scales the resident ray by the scale contained in the provided matrix from
    /// a given point that acts as pivot.
    /// </summary>
    /// <remarks>
    /// Resultant ray is normalized after this operation.<br/>
    /// If the direction of the ray is null, the result is undefined.
    /// </remarks>
    /// <param name="scale">[IN] Matrix which contains the scale to be applied. If it is null, the result is undefined.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot of the scale.</param>
    /// <returns>
    /// The rotated ray.
    /// </returns>
    Ray3D<VectorT> ScaleWithPivot(const ScalingMatrix3x3 &scale, const VectorT &vPivot) const
    {
        Ray3D<VectorT> auxRay = *this;
        SPoint::ScaleWithPivot(scale, vPivot, &auxRay.Origin, 1);
        SPoint::Scale(scale, &auxRay.Direction, 1);
        return Ray3D<VectorT>(auxRay.Origin, auxRay.Direction.Normalize());
    }

    /// <summary>
    /// This method applies the transformation contained in the provided matrix using
    /// a given point as pivot of transformation.
    /// </summary>
    /// <remarks>
    /// Resultant ray is normalized after this operation.<br/>
    /// If the direction of the ray is null, the result is undefined.<br/>
    /// When using 4D vectors, the W component of the pivot point doesn't affect the result.
    /// </remarks>
    /// <param name="transformation">[IN] Tranformation matrix to be applied. If it is null, the result is undefined.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot of the transformation.</param>
    /// <returns>
    /// The transformed ray.
    /// </returns>
    Ray3D<VectorT> TransformWithPivot(const TransformationMatrix<Matrix4x3> &transformation, const VectorT &vPivot) const
    {
        return this->TransformWithPivotImp(transformation, vPivot);
    }

    /// <summary>
    /// This method applies the transformation contained in the provided matrix using
    /// a given point as pivot of transformation.
    /// </summary>
    /// <remarks>
    /// Resultant ray is normalized after this operation.<br/>
    /// If the direction of the ray is null, the result is undefined.<br/>
    /// When using 4D vectors, the W component of the pivot point doesn't affect the result.
    /// </remarks>
    /// <param name="transformation">[IN] Tranformation matrix to be applied. If it is null, the result is undefined.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot of the transformation.</param>
    /// <returns>
    /// The transformed ray.
    /// </returns>
    Ray3D<VectorT> TransformWithPivot(const TransformationMatrix<Matrix4x4> &transformation, const VectorT &vPivot) const
    {
        return this->TransformWithPivotImp(transformation, vPivot);
    }

protected:

    /// <summary>
    /// Checks if the ray contains a given point.
    /// </summary>
    /// <remarks>
    /// Ray must be normalized for the operation to return a correct result.
    /// </remarks>
    /// <param name="vPoint">[IN] The point to be checked.</param>
    /// <returns>
    /// True if the point belongs to the ray; False otherwise.
    /// </returns>
    bool Contains(const VectorT &vPoint) const
    {
        if (vPoint == this->Origin) // The point is the ray position.
            return true;

        Vector3 vAux(vPoint - this->Origin); // Calculates a vector from ray origin to point.

        Vector3 vCross = vAux.CrossProduct(this->Direction); // Calculates cross product to check if both vectors are parallel

        if (vCross != Vector3::GetNullVector()) // Vectors are not parallel
            return false;
        else // Vectors are parallel. It checks if they are opposite or not.
            return ( SFloat::IsNegative(vAux.x) == SFloat::IsNegative(this->Direction.x) ) &&
                   ( SFloat::IsNegative(vAux.y) == SFloat::IsNegative(this->Direction.y) ) &&
                   ( SFloat::IsNegative(vAux.z) == SFloat::IsNegative(this->Direction.z) );

    }

    /// <summary>
    /// Checks if a triangle contains a given point.
    /// </summary>
    /// <typeparam name="VectorParamT">Allowed types: Vector3, Vector4.</typeparam>
    /// <param name="triangle">[IN] The triangle inside which the point may be.</param>
    /// <param name="vPoint">[IN] The point to be checked.</param>
    /// <returns>
    /// True if the point belongs to the triangle; False otherwise.
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

        Z_ASSERT_WARNING(DENOM != SFloat::_0, "The constant value DENOM must not be zero, this will cause a division by zero");

        const float_z &INV_DENOM = SFloat::_1 / DENOM;

        const float_z &fU = (DOT_11 * DOT_02 - DOT_01 * DOT_12) * INV_DENOM;
        const float_z &fV = (DOT_00 * DOT_12 - DOT_01 * DOT_02) * INV_DENOM;

        // Check if point is in triangle
        return SFloat::IsGreaterOrEquals(fU, SFloat::_0) && 
               SFloat::IsGreaterOrEquals(fV, SFloat::_0) && 
               SFloat::IsLessOrEquals(fU + fV, SFloat::_1);
    }

    /// <summary>
    /// Calculates if a point is inside the quadrilateral provided by four vertices.
    /// </summary>
    /// <remarks>
    /// The quadrilateral is suppossed to be convex and not complex.
    /// </remarks>
    /// <typeparam name="VectorParamT">Allowed types: Vector3, Vector4.</typeparam>
    /// <param name="vVertexA">[IN] The vertex A of the quadrilateral.</param>
    /// <param name="vVertexB">[IN] The vertex B of the quadrilateral.</param>
    /// <param name="vVertexC">[IN] The vertex C of the quadrilateral.</param>
    /// <param name="vVertexD">[IN] The vertex D of the quadrilateral.</param>
    /// <param name="vPoint">[IN] The point to be checked.</param>
    /// <returns>
    /// True if the point belongs to the quadrilateral; False otherwise.
    /// </returns>
    template <class VectorParamT>
    bool PointInsideQuadrilateral(const VectorParamT &vVertexA, const VectorParamT &vVertexB,
                                  const VectorParamT &vVertexC,const VectorParamT &vVertexD,
                                  const VectorParamT &vPoint) const
    {
        // Compute vectors
        const VectorParamT &V0(vVertexC - vVertexA);
        const VectorParamT &V1(vVertexB - vVertexA);
        const VectorParamT &V2(vPoint - vVertexA);

        // Compute dot products
        const float_z &DOT_00 = V0.DotProduct(V0);
        const float_z &DOT_01 = V0.DotProduct(V1);
        const float_z &DOT_02 = V0.DotProduct(V2);
        const float_z &DOT_11 = V1.DotProduct(V1);
        const float_z &DOT_12 = V1.DotProduct(V2);

        // Compute barycentric coordinates
        const float_z &DENOM = DOT_00 * DOT_11 - DOT_01 * DOT_01;

        Z_ASSERT_WARNING(DENOM != SFloat::_0, "The constant value DENOM must not be zero, this will cause a division by zero");

        const float_z &INV_DENOM = SFloat::_1 / DENOM;

        const float_z &fU = (DOT_11 * DOT_02 - DOT_01 * DOT_12) * INV_DENOM;
        const float_z &fV = (DOT_00 * DOT_12 - DOT_01 * DOT_02) * INV_DENOM;

        // Check if point is in triangle
        if ( SFloat::IsGreaterOrEquals(fU, SFloat::_0) && 
             SFloat::IsGreaterOrEquals(fV, SFloat::_0) && 
             SFloat::IsLessOrEquals(fU + fV, SFloat::_1) )
            return true;

        // Compute new vector
        const VectorParamT &V3(vVertexD - vVertexA);

        // Compute new dot products
        const float_z &DOT_03 = V0.DotProduct(V3);
        const float_z &DOT_33 = V3.DotProduct(V3);
        const float_z &DOT_32 = V3.DotProduct(V2);

        // Compute new barycentric coordinates
        const float_z &DENOM2 = DOT_00 * DOT_33 - DOT_03 * DOT_03;

        Z_ASSERT_WARNING(DENOM2 != SFloat::_0, "The constant value DENOM must not be zero, this will cause a division by zero");

        const float_z &INV_DENOM2 = SFloat::_1 / DENOM2;

        const float_z &fU2 = (DOT_33 * DOT_02 - DOT_03 * DOT_32) * INV_DENOM2;
        const float_z &fV2 = (DOT_00 * DOT_32 - DOT_03 * DOT_02) * INV_DENOM2;

        // Check if point is in triangle
        return  SFloat::IsGreaterOrEquals(fU2, SFloat::_0) && 
                SFloat::IsGreaterOrEquals(fV2, SFloat::_0) && 
                SFloat::IsLessOrEquals(fU2 + fV2, SFloat::_1);
    }

    /// <summary>
    /// Checks if the ray intersects with a quadrilateral given by its four vertices.
    /// </summary>
    /// <param name="vVertexA">[IN] The vertex A of the quadrilateral.</param>
    /// <param name="vVertexB">[IN] The vertex B of the quadrilateral.</param>
    /// <param name="vVertexC">[IN] The vertex C of the quadrilateral.</param>
    /// <param name="vVertexD">[IN] The vertex D of the quadrilateral.</param>
    /// <returns>
    /// True if the ray intersects with the quadrilateral; False otherwise.
    /// </returns>
    bool Intersection(const VectorT &vVertexA, const VectorT &vVertexB, const VectorT &vVertexC, const VectorT &vVertexD) const
    {
        // Plane that contains quadrilateral
        Plane auxP(vVertexA, vVertexB, vVertexC);

        VectorT vAux;

        const EIntersections &NUM_INTERSECT = this->IntersectionPoint(auxP, vAux);
        if (NUM_INTERSECT == EIntersections::E_Infinite) // Ray and plane are coplanar.
            return ( this->Intersection(BaseLineSegment<VectorT>(vVertexA, vVertexB)) || this->Intersection(BaseLineSegment<VectorT>(vVertexB, vVertexC)) ||
                     this->Intersection(BaseLineSegment<VectorT>(vVertexC, vVertexD)) || this->Intersection(BaseLineSegment<VectorT>(vVertexD, vVertexA)) );
        else if (NUM_INTERSECT == EIntersections::E_One) // Ray and plane intersects in one point
            return this->PointInsideQuadrilateral(vVertexA, vVertexB, vVertexC, vVertexD, vAux);
        else
            return false;
    }

    /// <summary>
    /// Calculates the intersection point between a quadrilateral given by its four vertices and the resident ray.
    /// </summary>
    /// <param name="vVertexA">[IN] The vertex A of the quadrilateral.</param>
    /// <param name="vVertexB">[IN] The vertex B of the quadrilateral.</param>
    /// <param name="vVertexC">[IN] The vertex C of the quadrilateral.</param>
    /// <param name="vVertexD">[IN] The vertex D of the quadrilateral.</param>
    /// <param name="vIntersection1">[OUT] The vertex D of the quadrilateral.</param>
    /// <param name="vIntersection2">[OUT] The vertex D of the quadrilateral.</param>
    /// <returns>
    /// An enumerated value that indicates how many intersections were found:<br/>
    /// <br/>
    /// <b>None</b><br/>
    /// There are no intersections.<br/>
    ///
    /// <b>One</b><br/>
    /// There is one intersection.<br/>
    /// - The origin of the ray belongs to an edge of the quadrilateral and the ray does not point to the quadrilateral.
    /// - The origin of the ray coincide with a vertex of the quadrilateral and the ray does not point to the quadrilateral.
    /// - The ray intersects with only one vertex of the quadrilateral.
    /// - The origin of the ray is contained in the quadrilateral.
    /// - The origin of the ray is contained in the quadrilateral but the ray does not intersect with any edge.
    ///
    /// <b>Two</b><br/>
    /// There are two intersections.<br/>
    /// - The ray intersects with two edges of the quadrilateral.
    /// - The origin of the ray belongs to an edge of the quadrilateral and the ray intersects with another edge.
    /// - The origin of the ray coincides with a vertex of the quadrilateral and the ray intersects with another edge.
    /// - The origin of the ray belongs to an edge of the quadrilateral and the ray intersects with a vertex of the edge.
    /// - The ray intersects with two vertices of the quadrilateral.
    /// </returns>
    EIntersections IntersectionPoint (const VectorT &vVertexA, const VectorT &vVertexB, const VectorT &vVertexC, const VectorT &vVertexD,
                                       VectorT &vIntersection1, VectorT &vIntersection2) const
    {
        // Plane that contains quadrilateral
        Plane auxP(vVertexA, vVertexB, vVertexC);

        VectorT vAux;

        const EIntersections &NUM_INTERSECT = this->IntersectionPoint(auxP, vAux);
        if (NUM_INTERSECT == EIntersections::E_Infinite) // Ray and quadrilateral are coplanar.
        {
            if ( PointInsideQuadrilateral(vVertexA, vVertexB, vVertexC, vVertexD, this->Origin) ) // Ray origin is inside quadrilateral
            {
                if (this->Origin == vVertexA) // Ray origin is A quadrilateral vertex
                {
                    vIntersection1 = this->Origin;

                    // Checks intersection with opposite edges
                    if (this->IntersectionPoint(BaseLineSegment<VectorT>(vVertexB, vVertexC), vAux) == EIntersections::E_One) // Intersection found
                    {
                        vIntersection2 = vAux;
                        return EIntersections::E_Two;
                    }
                    else if (this->IntersectionPoint(BaseLineSegment<VectorT>(vVertexC, vVertexD), vAux) == EIntersections::E_One) // Intersection found
                    {
                        vIntersection2 = vAux;
                        return EIntersections::E_Two;
                    }
                    else // No intersection found
                        return EIntersections::E_One;
                }
                else if (this->Origin == vVertexB) // Ray origin is B quadrilateral vertex
                {
                    vIntersection1 = this->Origin;

                   // Checks intersection with opposite edges
                    if (this->IntersectionPoint(BaseLineSegment<VectorT>(vVertexC, vVertexD), vAux) == EIntersections::E_One) // Intersection found
                    {
                        vIntersection2 = vAux;
                        return EIntersections::E_Two;
                    }
                    else if (this->IntersectionPoint(BaseLineSegment<VectorT>(vVertexD, vVertexA), vAux) == EIntersections::E_One) // Intersection found
                    {
                        vIntersection2 = vAux;
                        return EIntersections::E_Two;
                    }
                    else // No intersection found
                        return EIntersections::E_One;
                }
                else if (this->Origin == vVertexC) // Ray origin is C quadrilateral vertex
                {
                    vIntersection1 = this->Origin;

                    // Checks intersection with opposite edges
                    if (this->IntersectionPoint(BaseLineSegment<VectorT>(vVertexD, vVertexA), vAux) == EIntersections::E_One) // Intersection found
                    {
                        vIntersection2 = vAux;
                        return EIntersections::E_Two;
                    }
                    else if (this->IntersectionPoint(BaseLineSegment<VectorT>(vVertexA, vVertexB), vAux) == EIntersections::E_One) // Intersection found
                    {
                        vIntersection2 = vAux;
                        return EIntersections::E_Two;
                    }
                    else // No intersection found
                        return EIntersections::E_One;
                }
                else if (this->Origin == vVertexD) // Ray origin is D quadrilateral vertex
                {
                    vIntersection1 = this->Origin;

                    // Checks intersection with opposite edges
                    if (this->IntersectionPoint(BaseLineSegment<VectorT>(vVertexA, vVertexB), vAux) == EIntersections::E_One) // Intersection found
                    {
                        vIntersection2 = vAux;
                        return EIntersections::E_Two;
                    }
                    else if (this->IntersectionPoint(BaseLineSegment<VectorT>(vVertexB, vVertexC), vAux) == EIntersections::E_One) // Intersection found
                    {
                        vIntersection2 = vAux;
                        return EIntersections::E_Two;
                    }
                    else // No intersection found
                        return EIntersections::E_One;
                }
                else if (SFloat::IsZero(LineSegment<VectorT>(vVertexA, vVertexB).MinDistance(this->Origin))) // Ray origin is in AB quadrilateral edge
                {
                    vIntersection1 = this->Origin;

                    if (this->IntersectionPoint(BaseLineSegment<VectorT>(vVertexB, vVertexC), vAux) == EIntersections::E_One) // Ray intersects other edge
                    {
                        vIntersection2 = vAux;
                        return EIntersections::E_Two;
                    }
                    else if (this->IntersectionPoint(BaseLineSegment<VectorT>(vVertexC, vVertexD), vAux) == EIntersections::E_One) // Ray intersects other edge
                    {
                        vIntersection2 = vAux;
                        return EIntersections::E_Two;
                    }
                    else if (this->IntersectionPoint(BaseLineSegment<VectorT>(vVertexD, vVertexA), vAux) == EIntersections::E_One) // Ray intersects other edge
                    {
                        vIntersection2 = vAux;
                        return EIntersections::E_Two;
                    }
                    else // Ray doesn't intersect with other edge
                    {
                        return EIntersections::E_One;
                    }
                }
                else if (SFloat::IsZero(LineSegment<VectorT>(vVertexB, vVertexC).MinDistance(this->Origin))) // Ray origin is in BC quadrilateral edge
                {
                    vIntersection1 = this->Origin;

                    if (this->IntersectionPoint(BaseLineSegment<VectorT>(vVertexC, vVertexD), vAux) == EIntersections::E_One) // Ray intersects other edge
                    {
                        vIntersection2 = vAux;
                        return EIntersections::E_Two;
                    }
                    else if (this->IntersectionPoint(BaseLineSegment<VectorT>(vVertexD, vVertexA), vAux) == EIntersections::E_One) // Ray intersects other edge
                    {
                        vIntersection2 = vAux;
                        return EIntersections::E_Two;
                    }
                    else if (this->IntersectionPoint(BaseLineSegment<VectorT>(vVertexA, vVertexB), vAux) == EIntersections::E_One) // Ray intersects other edge
                    {
                        vIntersection2 = vAux;
                        return EIntersections::E_Two;
                    }
                    else // Ray doesn't intersect with other edge
                    {
                        return EIntersections::E_One;
                    }
                }
                else if (SFloat::IsZero(LineSegment<VectorT>(vVertexC, vVertexD).MinDistance(this->Origin))) // Ray origin is in CD quadrilateral edge
                {
                    vIntersection1 = this->Origin;

                    if (this->IntersectionPoint(BaseLineSegment<VectorT>(vVertexD, vVertexA), vAux) == EIntersections::E_One) // Ray intersects other edge
                    {
                        vIntersection2 = vAux;
                        return EIntersections::E_Two;
                    }
                    else if (this->IntersectionPoint(BaseLineSegment<VectorT>(vVertexA, vVertexB), vAux) == EIntersections::E_One) // Ray intersects other edge
                    {
                        vIntersection2 = vAux;
                        return EIntersections::E_Two;
                    }
                    else if (this->IntersectionPoint(BaseLineSegment<VectorT>(vVertexB, vVertexC), vAux) == EIntersections::E_One) // Ray intersects other edge
                    {
                        vIntersection2 = vAux;
                        return EIntersections::E_Two;
                    }
                    else // Ray doesn't intersect with other edge
                    {
                        return EIntersections::E_One;
                    }
                }
                else if (SFloat::IsZero(LineSegment<VectorT>(vVertexD, vVertexA).MinDistance(this->Origin))) // Ray origin is in DA quadrilateral edge
                {
                    vIntersection1 = this->Origin;

                    if (this->IntersectionPoint(BaseLineSegment<VectorT>(vVertexA, vVertexB), vAux) == EIntersections::E_One) // Ray intersects other edge
                    {
                        vIntersection2 = vAux;
                        return EIntersections::E_Two;
                    }
                    else if (this->IntersectionPoint(BaseLineSegment<VectorT>(vVertexB, vVertexC), vAux) == EIntersections::E_One) // Ray intersects other edge
                    {
                        vIntersection2 = vAux;
                        return EIntersections::E_Two;
                    }
                    else if (this->IntersectionPoint(BaseLineSegment<VectorT>(vVertexC, vVertexD), vAux) == EIntersections::E_One) // Ray intersects other edge
                    {
                        vIntersection2 = vAux;
                        return EIntersections::E_Two;
                    }
                    else // Ray doesn't intersect with other edge
                    {
                        return EIntersections::E_One;
                    }
                }
                else // Ray origin is strictly inside quadrilateral (is not in a vertex or an edge)
                {
                    vIntersection1 = this->Origin;

                    if (this->IntersectionPoint(BaseLineSegment<VectorT>(vVertexA, vVertexB), vAux) == EIntersections::E_One)
                        vIntersection2 = vAux;
                    else if (this->IntersectionPoint(BaseLineSegment<VectorT>(vVertexB, vVertexC), vAux) == EIntersections::E_One)
                        vIntersection2 = vAux;
                    else if (this->IntersectionPoint(BaseLineSegment<VectorT>(vVertexC, vVertexD), vAux) == EIntersections::E_One)
                        vIntersection2 = vAux;
                    else if (this->IntersectionPoint(BaseLineSegment<VectorT>(vVertexD, vVertexA), vAux) == EIntersections::E_One)
                        vIntersection2 = vAux;
                    else
                        Z_ASSERT_WARNING(false, "Something went really wrong, this code branch must never be reached");  // Something is wrong, if ray point is interior, it must be ONE intersection with a edge.

                    return EIntersections::E_Two;
                }
            }
            else // Ray origin is outside quadrilateral
            {
                VectorT vPrevInt;
                bool bPrevInt = false;

                VectorT vAuxAB;
                EIntersections numIntersectAB = this->IntersectionPoint(BaseLineSegment<VectorT>(vVertexA, vVertexB), vAuxAB); // Checks intersection with AB edge
                if (numIntersectAB == EIntersections::E_Two) // Ray contains AB edge
                {
                    // Looks for closest point to ray origin
                    if  ( (vVertexA - this->Origin).GetSquaredLength() < (vVertexB - this->Origin).GetSquaredLength() )
                    {
                        vIntersection1 = vVertexA;
                        vIntersection2 = vVertexB;
                    }
                    else
                    {
                        vIntersection1 = vVertexB;
                        vIntersection2 = vVertexA;
                    }
                    return EIntersections::E_Two;
                }

                VectorT vAuxBC;
                EIntersections numIntersectBC = this->IntersectionPoint(BaseLineSegment<VectorT>(vVertexB, vVertexC), vAuxBC); // Checks intersection with BC edge
                if (numIntersectBC == EIntersections::E_Two) // Ray contains BC edge
                {
                    // Looks for closest point to ray origin
                    if  ( (vVertexB - this->Origin).GetSquaredLength() < (vVertexC - this->Origin).GetSquaredLength() )
                    {
                        vIntersection1 = vVertexB;
                        vIntersection2 = vVertexC;
                    }
                    else
                    {
                        vIntersection1 = vVertexC;
                        vIntersection2 = vVertexB;
                    }
                    return EIntersections::E_Two;
                }

                VectorT vAuxCD;
                EIntersections numIntersectCD = this->IntersectionPoint(BaseLineSegment<VectorT>(vVertexC, vVertexD), vAuxCD); // Checks intersection with CD edge
                if (numIntersectCD == EIntersections::E_Two) // Ray contains CD edge
                {
                    // Looks for closest point to ray origin
                    if  ( (vVertexC - this->Origin).GetSquaredLength() < (vVertexD - this->Origin).GetSquaredLength() )
                    {
                        vIntersection1 = vVertexC;
                        vIntersection2 = vVertexD;
                    }
                    else
                    {
                        vIntersection1 = vVertexD;
                        vIntersection2 = vVertexC;
                    }
                    return EIntersections::E_Two;
                }

                VectorT vAuxDA;
                EIntersections numIntersectDA = this->IntersectionPoint(BaseLineSegment<VectorT>(vVertexD, vVertexA), vAuxDA); // Checks intersection with DA edge
                if (numIntersectDA == EIntersections::E_Two) // Ray contains DA edge
                {
                    // Looks for closest point to ray origin
                    if  ( (vVertexD - this->Origin).GetSquaredLength() < (vVertexA - this->Origin).GetSquaredLength() )
                    {
                        vIntersection1 = vVertexD;
                        vIntersection2 = vVertexA;
                    }
                    else
                    {
                        vIntersection1 = vVertexA;
                        vIntersection2 = vVertexD;
                    }
                    return EIntersections::E_Two;
                }

                if (numIntersectAB == EIntersections::E_One) // Ray has ONE intersection with AB edge
                {
                    bPrevInt = true;
                    vPrevInt = vAuxAB;
                }

                if (numIntersectBC == EIntersections::E_One) // Ray has ONE intersection with BC edge
                {
                    if (bPrevInt) // There is a previous intersection with an edge
                    {
                        if (vPrevInt != vAuxBC) // They are not the same point (a common vertex)
                        {
                            // Looks for closest point to ray origin
                            if  ( (vAuxBC - this->Origin).GetSquaredLength() < (vPrevInt - this->Origin).GetSquaredLength() )
                            {
                                vIntersection1 = vAuxBC;
                                vIntersection2 = vPrevInt;
                            }
                            else
                            {
                                vIntersection1 = vPrevInt;
                                vIntersection2 = vAuxBC;
                            }
                            return EIntersections::E_Two;
                        }
                    }
                    else // It's the first intersection found
                    {
                        bPrevInt = true;
                        vPrevInt = vAuxBC;
                    }
                }

                if (numIntersectCD == EIntersections::E_One)
                {
                    if (bPrevInt) // There is a previous intersection with an edge
                    {
                        if (vPrevInt != vAuxCD) // They are not the same point (a common vertex)
                        {
                            // Looks for closest point to ray origin
                            if  ( (vAuxCD - this->Origin).GetSquaredLength() < (vPrevInt - this->Origin).GetSquaredLength() )
                            {
                                vIntersection1 = vAuxCD;
                                vIntersection2 = vPrevInt;
                            }
                            else
                            {
                                vIntersection1 = vPrevInt;
                                vIntersection2 = vAuxCD;
                            }
                            return EIntersections::E_Two;
                        }
                    }
                    else // It's the first intersection found
                    {
                        bPrevInt = true;
                        vPrevInt = vAuxCD;
                    }
                }

                if (numIntersectDA == EIntersections::E_One)
                {
                    if (bPrevInt) // There is a previous intersection with an edge
                    {
                        if (vPrevInt != vAuxDA) // They are not the same point (a common vertex)
                        {
                            // Looks for closest point to ray origin
                            if  ( (vAuxDA - this->Origin).GetSquaredLength() < (vPrevInt - this->Origin).GetSquaredLength() )
                            {
                                vIntersection1 = vAuxDA;
                                vIntersection2 = vPrevInt;
                            }
                            else
                            {
                                vIntersection1 = vPrevInt;
                                vIntersection2 = vAuxDA;
                            }
                            return EIntersections::E_Two;
                        }
                    }
                    else // It's the first intersection found
                        Z_ASSERT_WARNING(false, "Something went really wrong, this code branch must never be reached");  // Something is wrong
                }

                if (bPrevInt)
                {
                    vIntersection1 = vPrevInt;
                    return EIntersections::E_One;
                }
                else
                    return EIntersections::E_None;
            }
        }
        else if (NUM_INTERSECT == EIntersections::E_One) // Ray and plane intersects only in one point
        {
            if ( this->PointInsideQuadrilateral(vVertexA, vVertexB, vVertexC, vVertexD, vAux) )
            {
                vIntersection1 = vAux;
                return EIntersections::E_One;
            }
            else
                return EIntersections::E_None;
        }
        else
            return EIntersections::E_None;
    }

private:

    /// <summary>
    /// This method applies to the resident ray the transformation contained in the provided matrix.
    /// </summary>
    /// <remarks>
    /// Resultant ray is normalized after this operation.
    /// </remarks>
    /// <typeparam name="MatrixT">Allowed types: TransformationMatrix<Matrix4x3>, TransformationMatrix<Matrix4x4>.</typeparam>
    /// <param name="transformation">[IN] Matrix which contains the transformation to be applied.</param>
    /// <returns>
    /// The transformed ray.
    /// </returns>
    template <class MatrixT>
    Ray3D<VectorT> TransformImp(const MatrixT &transformation) const
    {
        Ray3D<VectorT> auxRay = *this;
        SPoint::Transform(transformation, &auxRay.Origin, 1);

        // Only rotation and scale part of the matrix is applyed to direction vector
        // These operations must be the same those used in Vector3::Transform, except for the translation operations.
        auxRay.Direction = Vector3(this->Direction.x * transformation.ij[0][0] + this->Direction.y * transformation.ij[1][0] + this->Direction.z * transformation.ij[2][0],
                                    this->Direction.x * transformation.ij[0][1] + this->Direction.y * transformation.ij[1][1] + this->Direction.z * transformation.ij[2][1],
                                    this->Direction.x * transformation.ij[0][2] + this->Direction.y * transformation.ij[1][2] + this->Direction.z * transformation.ij[2][2])
                                    .Normalize();
        return auxRay;
    }

    /// <summary>
    /// This method applies to the resident ray the transformation contained in the provided matrix using
    /// a given point as pivot of transformation.
    /// </summary>
    /// <remarks>
    /// Resultant ray is normalized after this operation.
    /// </remarks>
    /// <typeparam name="MatrixT">Allowed types: TransformationMatrix<Matrix4x3>, TransformationMatrix<Matrix4x4>.</typeparam>
    /// <param name="transformation">[IN] Tranformation matrix to be applied.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot of the transformation.</param>
    /// <returns>
    /// The transformed ray.
    /// </returns>
    template <class MatrixT>
    Ray3D<VectorT> TransformWithPivotImp(const MatrixT &transformation, const VectorT &vPivot) const
    {
        Ray3D<VectorT> auxRay = *this;
        SPoint::TransformWithPivot(transformation, vPivot, &auxRay.Origin, 1);

        // Only rotation and scale part of the matrix is applyed to direction vector
        // These operations must be the same those used in Vector3::Transform, except for the translation operations.
        auxRay.Direction = Vector3(this->Direction.x * transformation.ij[0][0] + this->Direction.y * transformation.ij[1][0] + this->Direction.z * transformation.ij[2][0],
                                    this->Direction.x * transformation.ij[0][1] + this->Direction.y * transformation.ij[1][1] + this->Direction.z * transformation.ij[2][1],
                                    this->Direction.x * transformation.ij[0][2] + this->Direction.y * transformation.ij[1][2] + this->Direction.z * transformation.ij[2][2])
                                    .Normalize();
        return auxRay;
    }
};


// SPECIALIZATION EXPORTATIONS
// -----------------------------
#ifdef Z_MATH_TEMPLATE_SPECIALIZATION_SYMBOLS

template class Z_LAYER_MATH_SYMBOLS Ray3D<Vector3>;
template class Z_LAYER_MATH_SYMBOLS Ray3D<Vector4>;

#endif // Z_MATH_TEMPLATE_SPECIALIZATION_SYMBOLS

} // namespace z


#endif // __RAY3D__
