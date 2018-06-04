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

#ifndef __RAY2D__
#define __RAY2D__

#include "Ray.h"

#include "ZMath/Vector2.h"
#include "EIntersections.h"



namespace z
{


// FORWARD DECLARATIONS
// ---------------------
class TransformationMatrix3x3;


namespace Internals
{


// FORWARD DECLARATIONS
// ---------------------
template<class VectorT> class Triangle;


/// <summary>
/// Represents a ray in 2D space, which consists of a origin point or position, and a direction.
/// </summary>
/// <remarks>
/// The direction symbolizes a line with only one end (which coincides with the point) and that extends to the infinite.
/// </remarks>
class Z_MATH_MODULE_SYMBOLS Ray2D : public Ray<Vector2, Vector2>
{
    // BASE CLASS USINGS
    // ------------------
public:

    using Ray<Vector2, Vector2>::Intersection;
    using Ray<Vector2, Vector2>::IntersectionPoint;


    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor. It is an empty constructor, it does not assign any value.
    /// </summary>
    Ray2D();

    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="ray">[IN] The 2D ray from which we want to create a copy in the resident 2D ray.</param>
    Ray2D(const Ray2D &ray);

    /// <summary>
    /// Base type constructor.
    /// </summary>
    /// <param name="ray">[IN] The 2D ray in which we want resident 2D ray to be based.</param>
    Ray2D(const Ray<Vector2, Vector2> &ray);

    /// <summary>
    /// Constructor that receives the ray's position and direction.
    /// </summary>
    /// <remarks>
    /// The direction vector must be normalized to construct the ray properly.
    /// </remarks>
    /// <param name="vOrigin">[IN] Ray's position.</param>
    /// <param name="vDirection">[IN] Ray's direction.</param>
    Ray2D(const Vector2 &vOrigin, const Vector2 &vDirection);


    // PROPERTIES
    // ---------------
public:

    /// <summary>
    /// Gets a ray placed at the coordinate origin and whose direction vector is null.
    /// </summary>
    /// <returns>
    /// The null ray.
    /// </returns>
    static const Ray2D& GetNullRay();

    /// <summary>
    /// Gets a ray placed at the coordinate origin and whose direction vector is in X growing direction.
    /// </summary>
    /// <returns>
    /// A ray that points to X direction.
    /// </returns>
    static const Ray2D& GetRayX();

    /// <summary>
    /// Gets a ray placed at the coordinate origin and whose direction vector is in Y growing direction.
    /// </summary>
    /// <returns>
    /// A ray that points to Y direction.
    /// </returns>
    static const Ray2D& GetRayY();


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
    Ray2D& operator=(const Ray<Vector2, Vector2> &ray);
    
    /// <summary>
    /// Checks if the ray intersects with the provided triangle.
    /// </summary>
    /// <remarks>
    /// If the direction of the ray is null the result is undefined.
    /// </remarks>
    /// <param name="triangle">[IN] The triangle whose intersection with the ray will be checked. If any of its vertices coincide, 
    /// the result is undefined.</param>
    /// <returns>
    /// A boolean value that indicates whether the ray and the triangle intersect or not.<br/>
    /// <br/>
    /// <b>True</b><br/>
    /// The ray and the triangle intersect, including the following cases:
    /// - The ray intersects the triangle in two points.
    /// - The ray intersects with a vertex of the triangle.
    /// - The the origin of the ray is contained in the triangle.
    /// - The origin of the ray belongs to an edge of the triangle.
    /// - The origin of the ray coincides with a vertex of the triangle.
    ///
    /// <b>False</b><br/>
    /// The ray and the triangle do not intersect.
    /// </returns>
    bool Intersection(const Triangle<Vector2> &triangle) const;

    /*
    /// <summary>
    /// Computes the intersection point between the ray and provided triangle.
    /// </summary>
    /// <remarks>
    /// If the direction of the ray is null the result is undefined.<br/>
    /// If there's no intersection point, the output parameter won't be modified.
    /// </remarks>
    /// <param name="triangle">[IN] The triangle whose intersection with resident ray will be checked. If any of its vertices coincide, 
    /// the result is undefined.</param>
    /// <param name="vIntersection">[OUT] Closest intersection point to ray's origin point, if it exists.</param>
    /// <returns>
    /// An enumerated value that indicates how many intersections were found:<br/>
    /// <br/>
    /// <b>None</b><br/>
    /// There are no intersections.<br/>
    ///
    /// <b>One</b><br/>
    /// There is one intersection.<br/>
    /// - The ray intersects with a vertex of the triangle.
    /// - The origin of the ray is inside of the triangle.
    /// - The origin of the ray belongs to an edge of the triangle and the ray does not point to the triangle.
    /// - The origin of the ray coincides with a vertex of the triangle and the ray does not point to the triangle.
    ///
    /// <b>Two</b><br/>
    /// There are two intersections.<br/>
    /// - The ray intersects with two edges of the triangle.
    /// - The origin of the ray belongs to an edge and the ray intersects with another edge.
    /// - The origin of the ray coincides with a vertex of the triangle and the ray intersects with the opposite edge.
    /// - The origin of the ray belongs to an edge and the ray intersects with a vertex of the same edge.
    /// - The ray intersects with two vertices of the triangle.
    /// </returns>
    EIntersections IntersectionPoint(const Triangle<Vector2> &triangle, Vector2 &vIntersection) const;

    /// <summary>
    /// Computes the intersection point between the ray and provided triangle.
    /// </summary>
    /// <remarks>
    /// If the direction of the ray is null the result is undefined.<br/>
    /// If there's no intersection point, the output parameters won't be modified.
    /// </remarks>
    /// <param name="triangle">[IN] The triangle whose intersection with resident ray will be checked. If any of its vertices coincide, 
    /// the result is undefined.</param>
    /// <param name="vIntersection1">[OUT] Closest intersection point to ray's origin point, if it exists.</param>
    /// <param name="vIntersection2">[OUT] Furthest intersection point to ray's origin point, if it exists.</param>
    /// <returns>
    /// An enumerated value that indicates how many intersections were found:<br/>
    /// <br/>
    /// <b>None</b><br/>
    /// There are no intersections.<br/>
    ///
    /// <b>One</b><br/>
    /// There is one intersection.<br/>
    /// - The ray intersects with a vertex of the triangle.
    /// - The origin of the ray is inside of the triangle.
    /// - The origin of the ray belongs to an edge of the triangle and the ray does not point to the triangle.
    /// - The origin of the ray coincides with a vertex of the triangle and the ray does not point to the triangle.
    ///
    /// <b>Two</b><br/>
    /// There are two intersections.<br/>
    /// - The ray intersects with two edges of the triangle.
    /// - The origin of the ray belongs to an edge and the ray intersects with another edge.
    /// - The origin of the ray coincides with a vertex of the triangle and the ray intersects with the opposite edge.
    /// - The origin of the ray belongs to an edge and the ray intersects with a vertex of the same edge.
    /// - The ray intersects with two vertices of the triangle.
    /// </returns>
    EIntersections IntersectionPoint(const Triangle<Vector2> &triangle, Vector2 &vIntersection1, Vector2 &vIntersection2) const;
    
    /// <summary>
    /// Computes a ray that is the result of resident ray reflection on the line segment provided.
    /// </summary>
    /// <remarks>
    /// Ray direction must be normalized to obtain a correct result.<br/>
    /// If there's no intersection point between ray and line segment, or are both coincident or parallel,
    /// reflected ray is the resident ray itself.<br/>
    /// If there's one intersection point between them, then the reflected ray has its origin point at the intersection point
    /// and its direction verifies that the incident angle and the reflected angle are equals.
    /// </remarks>
    /// <param name="segment">[IN] The line segment which acts as mirror. If the length of the segment equals zero, the result is undefined.</param>
    /// <param name="ray">[OUT] The reflected ray.</param>
    void Reflection(const BaseLineSegment<Vector2> &segment, Ray<Vector2, Vector2> &ray) const;

    /// <summary>
    /// Computes a vector that is the resultant direction of resident ray reflection on the line segment provided.
    /// </summary>
    /// <remarks>
    /// Ray direction must be normalized to obtain a correct result.<br/>
    /// If there's no intersection point between ray and line segment, or are both coincident or parallel,
    /// reflected ray is the resident ray itself.<br/>
    /// If there's one intersection point between them, then the reflected ray direction verifies
    /// that the incident angle and the reflected angle are equals.
    /// </remarks>
    /// <param name="segment">[IN] The line segment which acts as mirror. If the length of the segment equals zero, the result is undefined.</param>
    /// <param name="vDirection">[OUT] The direction of the reflected ray.</param>
    void Reflection(const BaseLineSegment<Vector2> &segment, Vector2 &vDirection) const;
    */
    /// <summary>
    /// Applies the transformation given by the matrix provided to resident ray.
    /// </summary>
    /// <remarks>
    /// Resultant ray is normalized after this operation.<br/>
    /// If the direction of the ray is null, the result is undefined.<br/>
    /// All transformations affect both the origin and the direction of the ray except translations,
    /// that only affect the origin point.
    /// </remarks>
    /// <param name="transformation">[IN] The transformation matrix to be applied. If it is null, the result is undefined.</param>
    /// <returns>
    /// The transformed ray.
    /// </returns>
    Ray2D Transform(const z::TransformationMatrix3x3 &transformation) const;

    /// <summary>
    /// This method rotates the resident ray the provided angle around the coordinate axis centre.
    /// </summary>
    /// <param name="fRotationAngle">[IN] Angle of rotation.</param>
    /// <returns>
    /// The rotated ray.
    /// </returns>
    Ray2D Rotate(const float_z fRotationAngle) const;

    /// <summary>
    /// This method rotates the resident ray the provided angle around the point provided as pivot.
    /// </summary>
    /// <param name="fRotationAngle">[IN] Angle of rotation.</param>
    /// <param name="vPivot">[IN] Point which acts as pivot.</param>
    /// <returns>
    /// The rotated ray.
    /// </returns>
    Ray2D RotateWithPivot(const float_z fRotationAngle, const Vector2 &vPivot) const;

    /// <summary>
    /// This method translates the resident ray by the translation contained in the provided vector.
    /// </summary>
    /// <param name="vTranslation">[IN] Vector which contains the translation to be applied.</param>
    /// <returns>
    /// The translated ray.
    /// </returns>
    Ray2D Translate(const Vector2 &vTranslation) const;

    /// <summary>
    /// This method translates the resident ray by the provided amounts for every axis.
    /// </summary>
    /// <param name="fTranslationX">[IN] Amount of translation in X direction.</param>
    /// <param name="fTranslationY">[IN] Amount of translation in Y direction.</param>
    /// <returns>
    /// The translated ray.
    /// </returns>
    Ray2D Translate(const float_z fTranslationX, const float_z fTranslationY) const;

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
    Ray2D Scale(const Vector2 &vScale) const;

    /// <summary>
    /// This method scales the resident ray by the amounts provided for every axis.
    /// </summary>
    /// <remarks>
    /// Resultant ray is normalized after this operation.<br/>
    /// If the direction of the ray is null, the result is undefined.
    /// </remarks>
    /// <param name="fScaleX">[IN] Scale to be applied in X direction. If it equals zero, the result is undefined.</param>
    /// <param name="fScaleY">[IN] Scale to be applied in Y direction. If it equals zero, the result is undefined.</param>
    /// <returns>
    /// The scaled ray.
    /// </returns>
    Ray2D Scale(const float_z fScaleX, const float_z fScaleY) const;

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
    Ray2D ScaleWithPivot(const Vector2 &vScale, const Vector2 &vPivot) const;

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
    /// <param name="vPivot">[IN] Point that acts as pivot of the scale.</param>
    /// <returns>
    /// The scaled ray.
    /// </returns>
    Ray2D ScaleWithPivot(const float_z fScaleX, const float_z fScaleY, const Vector2 &vPivot) const;

    /// <summary>
    /// This method applies the transformation contained in the provided transformation matrix from
    /// the provided point that acts as pivot.
    /// </summary>
    /// <remarks>
    /// Resultant ray is normalized after this operation.<br/>
    /// If the direction of the ray is null, the result is undefined.
    /// </remarks>
    /// <param name="transformation">[IN] Tranformation matrix to be applied. If it is null, the result is undefined.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot of the transformation.</param>
    /// <returns>
    /// The transformed ray.
    /// </returns>
    Ray2D TransformWithPivot(const z::TransformationMatrix3x3 &transformation, const Vector2 &vPivot) const;

protected:
    
    /// <summary>
    /// Checks if the resident ray contains a given point.
    /// </summary>
    /// <param name="vPoint">[IN] The point to be checked.</param>
    /// <returns>
    /// True if the point belongs to the ray; False otherwise.
    /// </returns>
    bool Contains(const Vector2 &vPoint) const;

    // [TODO] jwladi: Replace by the Triangle2D or Triangle Contains method, when it exists.

    /// <summary>
    /// Checks if a point is inside a triangle.
    /// </summary>
    /// <param name="triangle">[IN] The triangle that may contain or not the point.</param>
    /// <param name="vPoint">[IN] The point that may be inside or not of the triangle.</param>
    /// <returns>
    /// True if the point belongs to the triangle; False otherwise.
    /// </returns>
    bool PointInsideTriangle(const Triangle<Vector2>& triangle, const Vector2& vPoint) const;

    /// <summary>
    /// Check if two points are in the same side of a line.
    /// </summary>
    /// <param name="vP1">[IN] One of the points to be checked.</param>
    /// <param name="vP2">[IN] One of the points to be checked.</param>
    /// <param name="vLine1">[IN] A point that belongs to the line that divides the two-dimensional space in to two parts.</param>
    /// <param name="vLine2">[IN] Another point that belongs to the line that divides the two-dimensional space in to two parts.</param>
    /// <returns>
    /// True if the two points belong to the same side of the space divided by the line; False otherwise.
    /// </returns>
    bool PointsInSameSideOfLine(const Vector2 &vP1, const Vector2 &vP2, const Vector2 &vLine1, const Vector2 &vLine2) const;

};

} // namespace Internals


// TYPEDEFS
// ----------
typedef Internals::Ray2D Ray2;

} // namespace z


#endif // __RAY2D__
