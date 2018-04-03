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

#ifndef __ZUADRILATERAL__
#define __ZUADRILATERAL__

#include "BaseQuadrilateral.h"

#include "ZMath/Vector2.h"



namespace z
{

// Forward declarations
class LineSegment2D;

/// <summary>
/// Class which represents a quadrilateral in 2D space.
/// </summary>
/// <remarks>
/// The quadrilateral is defined by four consecutive vertices A, B, C, D, being the edges AB, BC, CD and DA segments.
/// </remarks>
class Z_LAYER_MATH_SYMBOLS Quadrilateral : public BaseQuadrilateral
{

    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor.
    /// </summary>
    Quadrilateral();

    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="quad">[IN] The quadrilateral from which we want to create a copy in the resident quadrilateral.</param>
    Quadrilateral(const Quadrilateral &quad);

    /// <summary>
    /// Base type constructor.
    /// </summary>
    /// <param name="quad">[IN] The quadrilateral in which we want resident quadrilateral to be based.</param>
    Quadrilateral(const BaseQuadrilateral &quad);

    /// <summary>
    /// Constructor from four 2D vectors.
    /// </summary>
    /// <remarks>
    /// Note that the four vertices must be consecutive, so that the egdes of the quadrilateral must be AB, BC, CD and DA.
    /// </remarks>
    /// <param name="vA">[IN] The 2D vector which defines A vertex.</param>
    /// <param name="vB">[IN] The 2D vector which defines B vertex.</param>
    /// <param name="vC">[IN] The 2D vector which defines C vertex.</param>
    /// <param name="vD">[IN] The 2D vector which defines D vertex.</param>
    Quadrilateral(const Vector2 &vA, const Vector2 &vB, const Vector2 &vC, const Vector2 &vD);


    // PROPERTIES
    // ---------------
public:

    /// <summary>
    /// Gets a square with center in coordinate origin and 1-length edges which are parallels to coordinate axis.
    /// </summary>
    /// <returns>
    /// The "unit square".
    /// </returns>
    static const Quadrilateral& GetUnitSquare();


    // METHODS
    // ---------------
public:

    /// <summary>
    /// Assignation operator. Assigns the provided quadrilateral to the resident quadrilateral.
    /// </summary>
    /// <param name="quad">[IN] The quadrilateral to be assigned.</param>
    /// <returns>
    /// A reference to the modified quadrilateral.
    /// </returns>
    Quadrilateral& operator=(const BaseQuadrilateral &quad);

    /// <summary>
    /// Checks if a given point is inside quadrilateral or not.
    /// </summary>
    /// <remarks>
    /// If the quadrilateral is a complex figure (two opposite edges intersect), the result will be still correct.<br/>
    /// If any of the vertices of the quadrilateral coincide, the result is undefined.
    /// </remarks>
    /// <param name="vPoint">[IN] The point we want to check.</param>
    /// <returns>
    /// True if the given point is inside quadrilateral, false otherwise.
    /// The quadrilateral perimeter is considered inside.
    /// </returns>
    bool Contains(const BaseVector2 &vPoint) const;

    /// <summary>
    /// Checks if the resident quadrilateral intersects with the provided one.
    /// </summary>
    /// <remarks>
    /// If any vertex of a quadilateral coincide, the result is undefined.
    /// </remarks>
    /// <param name="quad">[IN] The quadrilateral we want to check the intersection with resident one.</param>
    /// <returns>
    /// A boolean value that indicates whether the quadrilaterals intersect or not.<br/>
    /// <br/>
    /// <b>True</b><br/>
    /// The quadrilaterals intersect, including the following cases:
    /// - The quadrilaterals are overlapped but not coincident.
    /// - The quadrilaterals share only one vertex.
    /// - A vertex of one quadrilateral is contained in the edge of the other.
    /// - The quadrilaterals are coincident.
    /// - One quadrilateral is contained in the other.
    ///
    /// <b>False</b><br/>
    /// The quadrilaterals do not intersect.
    /// </returns>
    bool Intersection(const BaseQuadrilateral &quad) const;

    /// <summary>
    /// Checks if the resident quadrilateral is complex.
    /// </summary>
    /// <returns>
    /// True if the resident quadrilateral is complex, false otherwise.
    /// </returns>
    bool IsComplex() const;

    /// <summary>
    /// Checks if the resident quadrilateral is convex.
    /// </summary>
    /// <remarks>
    /// Crossed quadrilaterals are considered as convex.<br/>
    /// Quadrilaterals with a \f$ 180^0\f$ angle are considered convex too.
    /// </remarks>
    /// <returns>
    /// True if the resident quadrilateral is convex, false otherwise.
    /// </returns>
    bool IsConvex() const;

    /// <summary>
    /// Checks if the resident quadrilateral is concave.
    /// </summary>
    /// <returns>
    /// True if the resident quadrilateral is concave, false otherwise.
    /// </returns>
    bool IsConcave() const;

    /// <summary>
    /// Computes the interior angle between AB and AD edges of resident quadrilateral.
    /// </summary>
    /// <remarks>
    /// The result is always a positive angle, which is less than or equals a straight angle.<br/>
    /// If any of the three vertices that compound the corner of the quadrilateral coincide, the result is undefined.
    /// </remarks>
    /// <returns>
    /// A floating point value which is the angle computed.
    /// </returns>
    float_z GetAngleA() const;

    /// <summary>
    /// Computes the interior angle between BC and BA edges of resident quadrilateral.
    /// </summary>
    /// <remarks>
    /// The result is always a positive angle, which is less than or equals a straight angle.<br/>
    /// If any of the three vertices that compound the corner of the quadrilateral coincide, the result is undefined.
    /// </remarks>
    /// <returns>
    /// A floating point value which is the angle computed.
    /// </returns>
    float_z GetAngleB() const;

    /// <summary>
    /// Computes the angle between CD and CB edges of resident quadrilateral.
    /// </summary>
    /// <remarks>
    /// The result is always a positive angle, which is less than or equals a straight angle.<br/>
    /// If any of the three vertices that compound the corner of the quadrilateral coincide, the result is undefined.
    /// </remarks>
    /// <returns>
    /// A floating point value which is the angle computed.
    /// </returns>
    float_z GetAngleC() const;

    /// <summary>
    /// Computes the angle between DA and DC edges of resident quadrilateral.
    /// </summary>
    /// <remarks>
    /// The result is always a positive angle, which is less than or equals a straight angle.<br/>
    /// If any of the three vertices that compound the corner of the quadrilateral coincide, the result is undefined.
    /// </remarks>
    /// <returns>
    /// A floating point value which is the angle computed.
    /// </returns>
    float_z GetAngleD() const;

    /// <summary>
    /// This method applies to the resident quadrilateral the rotation defined by the provided angle
    /// around the coordinate axis centre.
    /// </summary>
    /// <param name="fRotationAngle">[IN] The angle of rotation.</param>
    /// <returns>
    /// The rotated quadrilateral.
    /// </returns>
    Quadrilateral Rotate(const float_z fRotationAngle) const;

    /// <summary>
    /// This method performs a translation of the resident quadrilateral given by the provided vector.
    /// </summary>
    /// <param name="vTranslation">[IN] The 2D vector which contains the translation to be applied.</param>
    /// <returns>
    /// The translated quadrilateral.
    /// </returns>
    Quadrilateral Translate(const BaseVector2 &vTranslation) const;

    /// <summary>
    /// This method performs a translation of the resident quadrilateral given by the provided amounts for every axis.
    /// </summary>
    /// <param name="fTranslationX">[IN] The amount of translation to be applied in X direction.</param>
    /// <param name="fTranslationY">[IN] The amount of translation to be applied in Y direction.</param>
    /// <returns>
    /// The translated quadrilateral.
    /// </returns>
    Quadrilateral Translate(const float_z fTranslationX, const float_z fTranslationY) const;

    /// <summary>
    /// This method scales the resident quadrilateral by the scale contained in the provided vector.
    /// </summary>
    /// <param name="vScale">[IN] The 2D vector which contains the scale to be applied in every axis.</param>
    /// <returns>
    /// The scaled quadrilateral.
    /// </returns>
    Quadrilateral Scale(const BaseVector2 &vScale) const;

    /// <summary>
    /// This method scales the resident quadrilateral by the provided amounts for every axis.
    /// </summary>
    /// <param name="fScaleX">[IN] The scale to be applied in X direction.</param>
    /// <param name="fScaleY">[IN] The scale to be applied in Y direction.</param>
    /// <returns>
    /// The scaled quadrilateral.
    /// </returns>
    Quadrilateral Scale(const float_z fScaleX, const float_z fScaleY) const;

    /// <summary>
    /// Receives a transformation matrix and applies the transformations to the resident quadrilateral.
    /// </summary>
    /// <remarks>
    /// The transformation pivot is the origin of coordinates.
    /// </remarks>
    /// <param name="transformation">[IN] Matrix that contains the transformation to apply.</param>
    /// <returns>
    /// The transformed quadrilateral.
    /// </returns>
    Quadrilateral Transform(const TransformationMatrix3x3 &transformation) const;

    /// <summary>
    /// This method transforms the 2D quadrilateral by rotating an amount defined by a rotation angle
    /// around a pivot point (as center of rotation).
    /// </summary>
    /// <param name="fRotationAngle">[IN] The angle of rotation.</param>
    /// <param name="vPivot">[IN] The pivot point which the rotation will be accomplished around.</param>
    /// <returns>
    /// The rotated quadrilateral.
    /// </returns>
    Quadrilateral RotateWithPivot(const float_z fRotationAngle, const Vector2 &vPivot) const;

    /// <summary>
    /// This method scales the resident quadrilateral by the scale contained in the provided vector,
    /// acting the provided vector as pivot of scale.
    /// </summary>
    /// <param name="vScale">[IN] The 2D vector which contains the scale to be applied in every axis.</param>
    /// <param name="vPivot">[IN] The point which acts as pivot of the scale.</param>
    /// <returns>
    /// The scaled quadrilateral.
    /// </returns>
    Quadrilateral ScaleWithPivot(const BaseVector2 &vScale, const BaseVector2 &vPivot) const;

    /// <summary>
    /// This method scales the resident quadrilateral by the provided amounts for every axis,
    /// acting the provided vector as pivot of scale.
    /// </summary>
    /// <param name="fScaleX">[IN] The scale to be applied in X direction.</param>
    /// <param name="fScaleY">[IN] The scale to be applied in Y direction.</param>
    /// <param name="vPivot">[IN] The point which acts as pivot of the scale.</param>
    /// <returns>
    /// The scaled quadrilateral.
    /// </returns>
    Quadrilateral ScaleWithPivot(const float_z fScaleX, const float_z fScaleY, const BaseVector2 &vPivot) const;

    /// <summary>
    /// Receives a transformation matrix and a vector (transformation pivot) and applies the transformations
    /// to the resident quadrilateral.
    /// </summary>
    /// <remarks>
    /// The transformation pivot is the vector received as parameter.
    /// </remarks>
    /// <param name="transformation">[IN] Matrix that contains the transformation to apply.</param>
    /// <param name="vPivot">[IN] Pivot point used for the transformation.</param>
    /// <returns>
    /// The transformed quadrilateral.
    /// </returns>
    Quadrilateral TransformWithPivot(const TransformationMatrix3x3 &transformation, const BaseVector2 &vPivot) const;

    /// <summary>
    /// Converts quadrilateral into a string.
    /// </summary>
    /// <remarks>
    /// The format of the string is:<br/>
    /// "L(a($A),b($B),c($C),d($D))".<br/>
    /// Where "$" means "string representation of attribute".
    /// </summary>
    /// <returns>
    /// The string with the specified format.
    /// </returns>
    string_z ToString() const;

protected:

    /// <summary>
    /// Calculates if two points are in the same side of a line segment.
    /// </summary>
    /// <remarks>
    /// Used to know if a quadrilateral is complex, and to check if a point is inside a triangle.
    /// In 2D case, it may be more efficient than the baricentric method.
    /// It is bassed on the orientation of the two tringles compossed by
    /// each point of the two we want to check and the end points of the line. If both triangles have
    /// the same orientation, both points are in the same side of the line.
    /// </remarks>
    /// <param name="vPoint1">[IN] One of the points to be checked.</param>
    /// <param name="vPoint2">[IN] One of the points to be checked..</param>
    /// <param name="vLine1">[IN] A point that belongs to the line that divides de two-dimensional space in two parts.</param>
    /// <param name="vLine2">[IN] Another point that belongs to the line that divides de two-dimensional space in two parts.</param>
    /// <returns>
    /// True if both points belong to the same side of the space divided by the line; False otherwise.
    /// </returns>
    bool PointsInSameSideOfLine(const BaseVector2 &vPoint1, const BaseVector2 &vPoint2,
                                const BaseVector2 &vLine1, const BaseVector2 &vLine2) const;

    /// <summary>
    /// Checks if the angle formed by three contiguous vertices is a reflex angle (> 180º or Pi radians).
    /// </summary>
    /// <param name="vAngleVertex">[IN] The angle's peak.</param>
    /// <param name="vContiguousVertex1">[IN] An adjacent vertex that forms one side of the angle.</param>
    /// <param name="vContiguousVertex2">[IN] The other adjacent vertex that forms the other side of the angle.</param>
    /// <param name="vOppositeVertex">[IN] The peak of the opposite angle in the quadrilateral.</param>
    /// <returns>
    /// True if the angle formed by the three vertices is a reflex angle; False otherwise.
    /// </returns>
    bool IsReflexAngle(const Vector2 &vAngleVertex, const Vector2 &vContiguousVertex1,
                       const Vector2 &vContiguousVertex2, const Vector2 &vOppositeVertex) const;
};

} // namespace z


#endif // __ZUADRILATERAL__
