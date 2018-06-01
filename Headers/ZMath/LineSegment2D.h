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

#ifndef __LINESEGMENT2D__
#define __LINESEGMENT2D__

#include "ZMath/LineSegment.h"
#include "ZMath/Vector2.h"


namespace z
{

template<class VectorT> class BaseTriangle;
class BaseQuadrilateral;

/// <summary>
/// This class represents a chunk (segment) of straight line into 2D space, defined by two
/// endpoints, A and B.
/// </summary>
/// <remarks>
/// These points will always be expressed as 2D points or vectors.<br/>
/// Please note there's really no "source" and "end" points implicit, that is, it's not an oriented segment
/// except for the unit line (see below). However, some transforming methods will rotate the segment using A
/// by default as the pivot point.
/// </remarks>
class Z_MATH_MODULE_SYMBOLS LineSegment2D : public LineSegment<Vector2>
{
    // BASE CLASS USINGS
    // ------------------
public:

    using LineSegment<Vector2>::Intersection;
    using LineSegment<Vector2>::IntersectionPoint;


    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor.
    /// </summary>
    LineSegment2D();

    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="segment">[IN] 2D line segment containing the two endpoints from which we want to create a copy in the resident segment.</param>
    LineSegment2D(const LineSegment2D &segment);

    /// <summary>
    /// Base type constructor.
    /// </summary>
    /// <param name="segment">[IN] The 2D line segment containing the two endpoints in which we want resident segment to be based.</param>
    LineSegment2D(const BaseLineSegment<Vector2> &segment);

    /// <summary>
    /// Constructor from two vectors.
    /// </summary>
    /// <param name="vA">[IN] 2D vector to define endpoint A.</param>
    /// <param name="vB">[IN] 2D vector to define endpoint B.</param>
    LineSegment2D(const Vector2& vA, const Vector2& vB);


    // PROPERTIES
    // ---------------
public:

    /// <summary>
    /// Unit segment lying on positive X axis (it's length equals 1).
    /// </summary>
    /// <returns>
    /// A 1-length line segment.
    /// </returns>
    static const LineSegment2D& GetUnitLine();

    /// <summary>
    /// Zero segment lying in the coordinates center whose endpoints both equals (0, 0) and it's length equals 0.
    /// </summary>
    /// <returns>
    /// A 0-length line segment.
    /// </returns>
    static const LineSegment2D& GetLineZero();


    // METHODS
    // ---------------

public:

    /// <summary>
    /// Assigning operator.
    /// </summary>
    /// <param name="segment">[IN] The 2D segment to be copied from.</param>
    /// <returns>
    /// A reference to the modified line segment.
    /// </returns>
    LineSegment2D& operator=(const BaseLineSegment<Vector2> &segment);

    /// <summary>
    /// This method receives a 2D triangle, and computes whether they intersect each other or not.
    /// </summary>
    /// <param name="triangle">[IN] The 2D triangle to be compared to. If any of the vertices of the triangle coincide,
    /// the result is undefined.</param>
    /// <returns>
    /// A boolean value that indicates whether the segment and the triangle intersect or not.<br/>
    /// <br/>
    /// <b>True</b><br/>
    /// The segment and the triangle intersect, including the following cases:
    /// - The segment intersects with one vertex of the triangle.
    /// - The segment intersects with two edges of the triangle.
    /// - The segment is completely contained in the triangle.
    /// - Only one endpoint is inside the triangle.
    /// - The line segment intersects with two vertices of the triangle (containing the edge).
    /// - The line segment is contained in an edge of the triangle.
    /// - An endpoint coincides with a vertex of the triangle.
    /// - An endpoint is tangent to an edge of the triangle, even if the other endpoint is inside the triangle.
    ///
    /// <b>False</b><br/>
    /// The line segment does not intersect with the triangle.
    /// </returns>
    bool Intersection(const BaseTriangle<Vector2>& triangle) const;

    /// <summary>
    /// This method receives a 2D quadrilateral, and computes whether they intersect each other or not.
    /// </summary>
    /// <remarks>
    /// If the quadrilateral is complex or concave, the result is undefined.
    /// </remarks>
    /// <param name="quad">[IN] The 2D quadrilateral to be compared to. If any of the vertices of the quadrilateral coincide,
    /// the result is undefined.</param>
    /// <returns>
    /// A boolean value that indicates whether the segment and the quadrilateral intersect or not.<br/>
    /// <br/>
    /// <b>True</b><br/>
    /// The segment and the quadrilateral intersect, including the following cases:
    /// - The segment intersects with one vertex of the quadrilateral.
    /// - The segment intersects with two edges of the quadrilateral.
    /// - The segment is completely contained in the quadrilateral.
    /// - Only one endpoint is inside the quadrilateral.
    /// - The line segment intersects with two vertices of the quadrilateral.
    /// - The line segment is contained in an edge of the quadrilateral.
    /// - An endpoint coincides with a vertex of the quadrilateral.
    /// - An endpoint is tangent to an edge of the quadrilateral, even if the other endpoint is inside the quadrilateral.
    ///
    /// <b>False</b><br/>
    /// The line segment does not intersect with the quadrilateral.
    /// </returns>
    bool Intersection(const BaseQuadrilateral& quad) const;

    /// <summary>
    /// This method applies to the resident line segment the rotation defined by the provided angle
    /// around the coordinate axis centre.
    /// </summary>
    /// <param name="fRotationAngle">[IN] The angle of rotation.</param>
    /// <returns>
    /// The rotated segment.
    /// </returns>
    LineSegment2D Rotate(const float_z fRotationAngle) const;

    /// <summary>
    /// This method performs a translation of the resident line segment given by the provided vector.
    /// </summary>
    /// <param name="vTranslation">[IN] The 2D vector which contains the translation to be applied.</param>
    /// <returns>
    /// The translated segment.
    /// </returns>
    LineSegment2D Translate(const BaseVector2 &vTranslation) const;

    /// <summary>
    /// This method performs a translation of the resident line segment given by the provided amounts for every axis.
    /// </summary>
    /// <param name="fTranslationX">[IN] The amount of translation to be applied in X direction.</param>
    /// <param name="fTranslationY">[IN] The amount of translation to be applied in Y direction.</param>
    /// <returns>
    /// The translated segment.
    /// </returns>
    LineSegment2D Translate(const float_z fTranslationX, const float_z fTranslationY) const;

    /// <summary>
    /// This method scales the resident line segment by the scale contained in the provided vector.
    /// </summary>
    /// <param name="vScale">[IN] The 2D vector which contains the scale to be applied in every axis.</param>
    /// <returns>
    /// The scaled segment.
    /// </returns>
    LineSegment2D Scale(const BaseVector2 &vScale) const;

    /// <summary>
    /// This method scales the resident line segment by the provided amounts for every axis.
    /// </summary>
    /// <param name="fScaleX">[IN] The scale to be applied in X direction.</param>
    /// <param name="fScaleY">[IN] The scale to be applied in Y direction.</param>
    /// <returns>
    /// The scaled segment.
    /// </returns>
    LineSegment2D Scale(const float_z fScaleX, const float_z fScaleY) const;

    /// <summary>
    /// Receives a transformation matrix and applies the transformations to the resident
    /// line segment. The transformation pivot is the origin of coordinates.
    /// </summary>
    /// <param name="transformation">[IN] Matrix that contains the transformation to apply.</param>
    /// <returns>
    /// The transformed segment.
    /// </returns>
    LineSegment2D Transform(const TransformationMatrix3x3 &transformation) const;

    /// <summary>
    /// This method transforms the 2D segment by rotating an amount defined by a rotation angle
    /// around a pivot point (as center of rotation).
    /// </summary>
    /// <param name="fRotationAngle">[IN] The angle of rotation.</param>
    /// <param name="vPivot">[IN] The pivot point which the rotation will be accomplished around.</param>
    /// <returns>
    /// The rotated segment.
    /// </returns>
    LineSegment2D RotateWithPivot(const float_z fRotationAngle, const Vector2 &vPivot) const;

    /// <summary>
    /// This method scales the resident line segment by the scale contained in the provided vector,
    /// acting the provided vector as pivot of scale.
    /// </summary>
    /// <param name="vScale">[IN] The 2D vector which contains the scale to be applied in every axis.</param>
    /// <param name="vPivot">[IN] The point which acts as pivot of the scale.</param>
    /// <returns>
    /// The scaled segment.
    /// </returns>
    LineSegment2D ScaleWithPivot(const BaseVector2 &vScale, const BaseVector2 &vPivot) const;

    /// <summary>
    /// This method scales the resident line segment by the provided amounts for every axis,
    /// acting the provided vector as pivot of scale.
    /// </summary>
    /// <param name="fScaleX">[IN] The scale to be applied in X direction.</param>
    /// <param name="fScaleY">[IN] The scale to be applied in Y direction.</param>
    /// <param name="vPivot">[IN] The point which acts as pivot of the scale.</param>
    /// <returns>
    /// The scaled segment.
    /// </returns>
    LineSegment2D ScaleWithPivot(const float_z fScaleX, const float_z fScaleY, const BaseVector2 &vPivot) const;

    /// <summary>
    /// Receives a transformation matrix and a vector (transformation pivot) and applies the transformations
    /// to the resident line segment.
    /// </summary>
    /// <param name="transformation">[IN] Matrix that contains the transformation to apply.</param>
    /// <param name="vPivot">[IN] Pivot point used for the transformation.</param>
    /// <returns>
    /// The transformed segment.
    /// </returns>
    LineSegment2D TransformWithPivot(const TransformationMatrix3x3 &transformation, const BaseVector2 &vPivot) const;

    /// <summary>
    /// This method receives a 2D triangle, and computes the intersection point between it and the segment,
    /// if it exists.
    /// </summary>
    /// <remarks>
    /// If there is no intersection point or if there are infinite, the output parameter used for storing that point won't be modified.
    /// </remarks>
    /// <param name="triangle">[IN] The triangle to be compared to. If any of the vertices of the triangle coincide,
    /// the result is undefined.</param>
    /// <param name="vIntersection">[OUT] The point where they intersect that is closest to A (segment).</param>
    /// <returns>
    /// An enumerated value that indicates how many intersections were found:<br/>
    /// <br/>
    /// <b>None</b><br/>
    /// There are no intersections.<br/>
    ///
    /// <b>One</b><br/>
    /// There is one intersection.<br/>
    /// - The segment intersects with a vertex of the triangle.
    /// - Only one endpoint is inside the triangle.
    /// - Only one endpoint coincides with a vertex of the triangle, even if the other is inside of the triangle.
    /// - Only one endpoint belongs to an edge of the triangle, even if the other is inside of the triangle.
    ///
    /// <b>Two</b><br/>
    /// There are two intersections.<br/>
    /// - The segment intersects with two edges of the triangle.
    /// - The segment intersects with two vertices of the triangle.
    /// - The segment belongs to an edge of the triangle.
    /// - Both endpoints are contained in different edges of the triangle.
    ///
    /// <b>Infinite</b><br/>
    /// There are infinite intersections.<br/>
    /// - The segment is contained in the triangle (the endpoints are not tangent to the edges).
    /// </returns>
    EIntersections IntersectionPoint(const BaseTriangle<Vector2> &triangle, BaseVector2 &vIntersection) const;
    
    /// <summary>
    /// This method receives a 2D triangle, and computes the intersection points between it and the segment,
    /// if they exist.
    /// </summary>
    /// <remarks>
    /// If there are no intersection points, the output parameters used for storing that points won't be modified.
    /// </remarks>
    /// <param name="triangle">[IN] The triangle to be compared to. If any of the vertices of the triangle coincide,
    /// the result is undefined.</param>
    /// <param name="vIntersection1">[OUT] The point where they intersect that is closest to A (segment).</param>
    /// <param name="vIntersection2">[OUT] The point where they intersect that is furthest to A (segment).</param>
    /// <returns>
    /// An enumerated value that indicates how many intersections were found:<br/>
    /// <br/>
    /// <b>None</b><br/>
    /// There are no intersections.<br/>
    ///
    /// <b>One</b><br/>
    /// There is one intersection.<br/>
    /// - The segment intersects with a vertex of the triangle.
    /// - Only one endpoint is inside the triangle.
    /// - Only one endpoint coincides with a vertex of the triangle, even if the other is inside of the triangle.
    /// - Only one endpoint belongs to an edge of the triangle, even if the other is inside of the triangle.
    ///
    /// <b>Two</b><br/>
    /// There are two intersections.<br/>
    /// - The segment intersects with two edges of the triangle.
    /// - The segment intersects with two vertices of the triangle.
    /// - The segment belongs to an edge of the triangle.
    /// - Both endpoints are contained in different edges of the triangle.
    ///
    /// <b>Infinite</b><br/>
    /// There are infinite intersections.<br/>
    /// - The segment is contained in the triangle (the endpoints are not tangent to the edges).
    /// </returns>
    EIntersections IntersectionPoint(const BaseTriangle<Vector2> &triangle, BaseVector2 &vIntersection1, BaseVector2 &vIntersection2) const;
        
    /// <summary>
    /// This method receives a quadrilateral, and computes the intersection point between it and the segment,
    /// if it exists.
    /// </summary>
    /// <remarks>
    /// The provided quadrilateral must be convex. Otherwise, the results obtained by the method will be incorrect.<br/>
    /// If there are no intersection point or if there are infinite, the output parameter used for storing that point won't be modified.
    /// </remarks>
    /// <param name="quad">[IN] The quadrilateral to be compared to. If any of the vertices of the quadrilateral coincide,
    /// the result is undefined.</param>
    /// <param name="vIntersection">[OUT] The point where they intersect that is closest to A (segment).</param>
    /// <returns>
    /// An enumerated value that indicates how many intersections were found:<br/>
    /// <br/>
    /// <b>None</b><br/>
    /// There are no intersections.<br/>
    ///
    /// <b>One</b><br/>
    /// There is one intersection.<br/>
    /// - The segment intersects with a vertex of the quadrilateral.
    /// - Only one endpoint is inside the quadrilateral.
    /// - Only one endpoint coincides with a vertex of the quadrilateral, even if the other is inside of the quadrilateral.
    /// - Only one endpoint belongs to an edge of the quadrilateral, even if the other is inside of the quadrilateral.
    ///
    /// <b>Two</b><br/>
    /// There are two intersections.<br/>
    /// - The segment intersects with two edges of the quadrilateral.
    /// - The segment intersects with two vertices of the quadrilateral.
    /// - The segment belongs to an edge of the quadrilateral.
    /// - Both endpoints are contained in different edges of the quadrilateral.
    ///
    /// <b>Infinite</b><br/>
    /// There are infinite intersections.<br/>
    /// - The segment is contained in the quadrilateral (the endpoints are not tangent to the edges).
    /// </returns>
    EIntersections IntersectionPoint(const BaseQuadrilateral &quad, BaseVector2 &vIntersection) const;

    /// <summary>
    /// This method receives a quadrilateral, and computes the intersection points between it and the segment,
    /// if they exist.
    /// </summary>
    /// <remarks>
    /// The provided quadrilateral MUST be convex. Otherwise, the results obtained by the method will be incorrect.<br/>
    /// If there are no intersection points or it there are infinite, the output parameters used for storing that points won't be modified.<br/>
    /// </remarks>
    /// <param name="quad">[IN] The quadrilateral to be compared to. If any of the vertices of the quadrilateral coincide,
    /// the result is undefined.</param>
    /// <param name="vIntersection1">[OUT] The point where they intersect that is closest to A (segment).</param>
    /// <param name="vIntersection2">[OUT] The point where they intersect that is furthest to A (segment).</param>
    /// <returns>
    /// An enumerated value that indicates how many intersections were found:<br/>
    /// <br/>
    /// <b>None</b><br/>
    /// There are no intersections.<br/>
    ///
    /// <b>One</b><br/>
    /// There is one intersection.<br/>
    /// - The segment intersects with a vertex of the quadrilateral.
    /// - Only one endpoint is inside the quadrilateral.
    /// - Only one endpoint coincides with a vertex of the quadrilateral, even if the other is inside of the quadrilateral.
    /// - Only one endpoint belongs to an edge of the quadrilateral, even if the other is inside of the quadrilateral.
    ///
    /// <b>Two</b><br/>
    /// There are two intersections.<br/>
    /// - The segment intersects with two edges of the quadrilateral.
    /// - The segment intersects with two vertices of the quadrilateral.
    /// - The segment belongs to an edge of the quadrilateral.
    /// - Both endpoints are contained in different edges of the quadrilateral.
    ///
    /// <b>Infinite</b><br/>
    /// There are infinite intersections.<br/>
    /// - The segment is contained in the quadrilateral (the endpoints are not tangent to the edges).
    /// </returns>
    EIntersections IntersectionPoint(const BaseQuadrilateral &quad, BaseVector2 &vIntersection1, BaseVector2 &vIntersection2) const;
    
protected:

    /// <summary>
    /// Checks if a point is inside a triangle.
    /// </summary>
    /// <param name="triangle">[IN] The triangle that may contain or not the point.</param>
    /// <param name="vPoint">[IN] The point to be checked.</param>
    /// <returns>
    /// True if the point is inside the quadrilateral; False otherwise.
    /// </returns>
    bool PointInsideTriangle(const BaseTriangle<Vector2>& triangle, const Vector2& vPoint) const; // [TODO] jwladi: Replace by the Triangle2D or Triangle Contains method, when it exists.

    /// <summary>
    /// Check if two points are in the same side of a line.
    /// </summary>
    /// <param name="vP1">[IN] The first point to be checked.</param>
    /// <param name="vP2">[IN] The second point to be checked.</param>
    /// <param name="vLine1">[IN] A point that belongs to the line that divides the two-dimensional space in two parts.</param>
    /// <param name="vLine2">[IN] A second point that belongs to the line that divides the two-dimensional space in two parts.</param>
    /// <returns>
    /// True if the point is inside the quadrilateral; False otherwise.
    /// </returns>
    bool PointsInSameSideOfLine(const Vector2 &vP1, const Vector2 &vP2, const Vector2 &vLine1, const Vector2 &vLine2) const;

    /// <summary>
    /// Checks if a point is inside a quadrilateral.
    /// </summary>
    /// <param name="quad">[IN] The quadrilateral that may contain or not the point.</param>
    /// <param name="vPoint">[IN] The point to be checked.</param>
    /// <returns>
    /// True if the point is inside the quadrilateral; False otherwise.
    /// </returns>
    bool PointInsideQuadrilateral(const BaseQuadrilateral& quad, const Vector2& vPoint) const; // [TODO] jwladi: Replace by the Quadrilateral Contains method, when it exists.
};

} // namespace z


#endif // __LINESEGMENT2D__
