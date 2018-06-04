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

#ifndef __PLANE__
#define __PLANE__

#include "ZMath/MathModuleDefinitions.h"
#include "ZCommon/DataTypes/StringsDefinitions.h"

#include "EIntersections.h"
#include "ESpaceRelation.h"



namespace z
{

// Forward declarations
class Vector3;
class Vector4;
class Vector3;
class Vector4;
class Matrix3x4;
class RotationMatrix3x3;
class ScalingMatrix3x3;
class SpaceConversionMatrix;
class Quaternion;
class Matrix4x3;
class Matrix4x4;

namespace Internals
{
    template<class MatrixT> class TransformationMatrix;
    template<class MatrixT> class TranslationMatrix;
}

typedef Internals::TranslationMatrix<Matrix4x3> TranslationMatrix4x3;
typedef Internals::TranslationMatrix<Matrix4x4> TranslationMatrix4x4;
typedef Internals::TransformationMatrix<Matrix4x3> TransformationMatrix4x3;
typedef Internals::TransformationMatrix<Matrix4x4> TransformationMatrix4x4;


/// <summary>
/// It represents the basic form of a 3D plane.
/// </remarks>
/// <remarks>
/// A plane is defined by the equation:<br/>
/// <br/>
/// \f$ ax + by + cz + d = 0\f$.<br/>
/// <br/>
/// We can see that the vector (a, b, c) is normal to the plane, and d represents the sorthest distance from
/// plane to the origin, when the normal is normalized.
/// </remarks>
class Z_MATH_MODULE_SYMBOLS Plane
{
    // FRIENDS
    // ---------------
public:

    /// <summary>
    /// Product by a scalar: all coefficients are multiplied by the floating point value provided.
    /// </summary>
    /// <remarks>
    /// Note that it may be necessary re-normalize the plane after this operation!!
    /// </remarks>
    /// <param name="fScalar">[IN] Multiplying floating point value.</param>
    /// <param name="plane">[IN] Plane to be multiplied.</param>
    /// <returns>
    /// A plane that is the result of the product.
    /// </returns>
    friend Plane Z_MATH_MODULE_SYMBOLS operator*(const float_z fScalar, const Plane &plane);


    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor. It is an empty constructor, it does not assign any value.
    /// </summary>
    Plane();

    /// <summary>
    /// Constructor from a floating point value for each coefficient.
    /// </summary>
    /// <param name="fValueA">[IN] Floating point value for a coefficient.</param>
    /// <param name="fValueB">[IN] Floating point value for b coefficient.</param>
    /// <param name="fValueC">[IN] Floating point value for c coefficient.</param>
    /// <param name="fValueD">[IN] Floating point value for independent term d.</param>
    Plane(const float_z fValueA, const float_z fValueB, const float_z fValueC, const float_z fValueD);

    /// <summary>
    /// Constructor from a floating point value for all coefficients.
    /// </summary>
    /// <param name="fValueAll">[IN] Floating point value for all the coefficients.</param>
    explicit Plane(const float_z fValueAll);

    /// <summary>
    /// Constructor from a pointer to an array of floating point values.
    /// </summary>
    /// <param name="arValues">[IN] Pointer to array of floating point values. It must have at least four elements. If the pointer is null, the behavior  
    /// is undefined.</param>
    explicit Plane(float_z* arValues);

    /// <summary>
    /// Constructor from a 4x32 packed float value.
    /// </summary>
    /// <param name="value">[IN] 4x32 packed float containing the four components.</param>
    /// <remarks>
    /// The parse order: 1st value (a coefficient), 2nd value (b coefficient),
    /// 3rd value (c coefficient), 4th value (d independent term).
    /// </remarks>
    explicit Plane(const vf32_z value);

    /// <summary>
    /// Constructor from three points.
    /// </summary>
    /// <remarks>
    /// This method produces a normalized plane. The normal of the plane depends on the order the points are passed as parameters.<br/>
    /// The three points shouldn't be collinear and shouldn't coincide; otherwise, the result is undefined.
    /// </remarks>
    /// <param name="vPoint1">[IN] A 3D vector which represents the first point.</param>
    /// <param name="vPoint2">[IN] A 3D vector which represents the second point.</param>
    /// <param name="vPoint3">[IN] A 3D vector which represents the third point.</param>
    Plane(const Vector3 &vPoint1, const Vector3 &vPoint2, const Vector3 &vPoint3);

    /// <summary>
    /// Constructor from three points.
    /// </summary>
    /// <remarks>
    /// This method produces a normalized plane. The normal of the plane depends on the order the points are passed as parameters.<br/>
    /// The three points shouldn't be collinear and shouldn't coincide; otherwise, the result is undefined.
    /// </remarks>
    /// <param name="vPoint1">[IN] A 3D vector which represents the first point.</param>
    /// <param name="vPoint2">[IN] A 3D vector which represents the second point.</param>
    /// <param name="vPoint3">[IN] A 3D vector which represents the third point.</param>
    Plane(const Vector4 &vPoint1, const Vector4 &vPoint2, const Vector4 &vPoint3);

private:

    /// <summary>
    /// Constructor from three points.
    /// </summary>
    /// <remarks>
    /// This method produces a normalized plane. The normal of the plane depends on the order the points are passed as parameters.
    /// </remarks>
    /// <typeparam name="VectorT">Allowed types: Vector3, Vector4.</typeparam>
    /// <param name="vPoint1">[IN] A 3D vector which represents the first point.</param>
    /// <param name="vPoint2">[IN] A 3D vector which represents the second point.</param>
    /// <param name="vPoint3">[IN] A 3D vector which represents the third point.</param>
    template <class VectorT>
    void PlaneImp(const VectorT &vPoint1, const VectorT &vPoint2, const VectorT &vPoint3);


    // PROPERTIES
    // ---------------
public:

    /// <summary>
    /// Gets a plane with all components set to 0.
    /// </summary>
    /// <returns>
    /// A plane with all components set to 0.
    /// </returns>
    static const Plane& GetNullPlane();

    /// <summary>
    /// Gets the plane that contains the Z and X axis, and its normal is in the Y axis.
    /// </summary>
    /// <returns>
    /// The plane ZX.
    /// </returns>
    static const Plane& GetPlaneZX();

    /// <summary>
    /// Gets the plane that contains the X and Y axis, and its normal is in the Z axis.
    /// </summary>
    /// <returns>
    /// The plane XY.
    /// </returns>
    static const Plane& GetPlaneXY();

    /// <summary>
    /// Gets the plane that contains the Y and Z axis, and its normal is in the X axis.
    /// </summary>
    /// <returns>
    /// The plane YZ.
    /// </returns>
    static const Plane& GetPlaneYZ();


    // METHODS
    // ---------------
public:
    
    /// <summary>
    /// Equality operator. Compares two planes.
    /// </summary>
    /// <remarks>
    /// Note that if any of the planes are not normalized, the result may be false, even if they are the same plane:
    /// <br/>
    /// \f$ x + y + z + 1 = 0\f$ and \f$ 2x + 2y + 2z + 2 = 0\f$ are the same plane but their components are different.
    /// </remarks>
    /// <param name="plane">[IN] Plane with which to compare.</param>
    /// <returns>
    /// True if planes are the same, false otherwise.
    /// </returns>
    bool operator==(const Plane &plane) const;

    /// <summary>
    /// Inequality operator. Compares two planes.
    /// </summary>
    /// <remarks>
    /// Note that if any of the planes are not normalized, the result may be true, even if they are the same plane.
    /// <br/>
    /// \f$ x + y + z + 1 = 0\f$ and \f$ 2x + 2y + 2z + 2 = 0\f$ are the same plane but their components are different.
    /// </remarks>
    /// <param name="plane">[IN] Plane with which to compare.</param>
    /// <returns>
    /// True if planes are not the same, false otherwise.
    /// </returns>
    bool operator!=(const Plane &plane) const;

    /// <summary>
    /// Product by a scalar: all coefficients are multiplied by the floating point value provided.
    /// </summary>
    /// <remarks>
    /// Note that it may be necessary re-normalize the plane after this operation!!
    /// </remarks>
    /// <param name="fScalar">[IN] Multiplying floating point value.</param>
    /// <returns>
    /// A plane that is the result of the product.
    /// </returns>
    Plane operator*(const float_z fScalar) const;

    /// <summary>
    /// Division by a scalar: all coefficients are divided by the floating point value provided.
    /// </summary>
    /// <remarks>
    /// Note that it may be necessary re-normalize the plane after this operation!!
    /// </remarks>
    /// <param name="fScalar">[IN] Dividing floating point value.</param>
    /// <returns>
    /// A plane that is the result of the division.
    /// </returns>
    Plane operator/(const float_z fScalar) const;

    /// <summary>
    /// Multiplies resident plane coefficients by a floating point value provided.
    /// </summary>
    /// <remarks>
    /// Note that it may be necessary re-normalize the plane after this operation!!
    /// </remarks>
    /// <param name="fScalar">[IN] Multiplying floating point value.</param>
    /// <returns>
    /// A reference to plane result of the product.
    /// </returns>
    Plane& operator*=(const float_z fScalar);

    /// <summary>
    /// Divides resident plane coefficients by a floating point value provided.
    /// </summary>
    /// <remarks>
    /// Note that it may be necessary re-normalize the plane after this operation!!
    /// <param name="fScalar">[IN] Dividing floating point value.</param>
    /// <returns>
    /// A reference to plane result of the division.
    /// </returns>
    Plane& operator/=(const float_z fScalar);

    /// <summary>
    /// Opposite plane: multiplies each coefficient by -1, maintaining its distance to the origin.
    /// </summary>
    /// <remarks>
    /// Note that this operation does not flips the normal of the plane but also moves the plane to the opposite place 
    /// regarding the coordinate origin.
    /// </remarks>
    /// <returns>
    /// A plane that is the opposite of the resident plane.
    /// </returns>
    Plane operator-() const;

    /// <summary>
    /// Normalizes the plane.
    /// </summary>
    /// <remarks>
    /// If the plane is null, the result is undefined.
    /// </remarks>
    /// <returns>
    /// The normalized plane.
    /// </returns>
    Plane Normalize() const;

    /// <summary>
    /// Calculates the dot product between the direction vector of the resident plane and the provided vector.
    /// </summary>
    /// <param name="vVector">[IN] The vector which we want to calculate the dot product with.</param>
    /// <returns>
    /// The result of the dot product.
    /// </returns>
    float_z DotProduct(const Vector3 &vVector) const;

    /// <summary>
    /// Calculates the dot product between the direction vector of the resident plane and the provided vector.
    /// </summary>
    /// <param name="vVector">[IN] The vector which we want to calculate the dot product with.</param>
    /// <returns>
    /// The result of the dot product.
    /// </returns>
    float_z DotProduct(const Vector4 &vVector) const;

    /// <summary>
    /// Calculates the dot product between the direction vectors of the resident plane and the provided one.
    /// </summary>
    /// <param name="plane">[IN] The plane which we want to calculate the dot product with.</param>
    /// <returns>
    /// The result of the dot product.
    /// </returns>
    float_z DotProduct(const Plane &plane) const;

    /// <summary>
    /// Calculates the angle between the direction vector of the resident plane and the provided vector via dot product.
    /// </summary>
    /// <remarks>
    /// The plane must be normalized to obtain a correct result and shouldn't be null (zero).
    /// </remarks>
    /// <param name="vVector">[IN] The vector whose angle with the resident plane we want to calculate. If it is null, the result
    /// is undefined.</param>
    /// <returns>
    /// The result of the dot product.
    /// </returns>
    float_z AngleBetween(const Vector3 &vVector) const;

    /// <summary>
    /// Calculates the angle between the direction vector of the resident plane and the provided vector via dot product.
    /// </summary>
    /// <remarks>
    /// The plane must be normalized to obtain a correct result and shouldn't be null (zero).
    /// </remarks>
    /// <param name="vVector">[IN] The vector whose angle with the resident plane we want to calculate.. If it is null, the result
    /// is undefined.</param>
    /// <returns>
    /// The result of the dot product.
    /// </returns>
    float_z AngleBetween(const Vector4 &vVector) const;

    /// <summary>
    /// Calculates the angle between resident and provided planes via dot product between their direction vectors.
    /// </summary>
    /// <remarks>
    /// Both planes must be normalized to obtain a correct result and shouldn't be null (zero).
    /// </remarks>
    /// <param name="plane">[IN] The plane whose angle with the resident plane we want to calculate. If it is null, the result
    /// is undefined.</param>
    /// <returns>
    /// The result of the dot product.
    /// </returns>
    float_z AngleBetween(const Plane &plane) const;

    /// <summary>
    /// Calculates the orthogonal projection of a given point over the resident plane.
    /// </summary>
    /// <remarks>
    /// The plane must be normalized to obtain a correct result and shouldn't be null (zero).
    /// </remarks>
    /// <param name="vPoint">[IN] A 3D vector which represents the point to be projected.</param>
    /// <returns>
    /// The projected point.
    /// </returns>
    Vector3 PointProjection(const Vector3 &vPoint) const;

    /// <summary>
    /// Calculates the orthogonal projection of a given point over the resident plane.
    /// </summary>
    /// <remarks>
    /// The plane must be normalized to obtain a correct result and shouldn't be null (zero). The W component of the
    /// returned point equals the input point one's value.
    /// </remarks>
    /// <param name="vPoint">[IN] A 4D vector which represents the point to be projected.</param>
    /// <returns>
    /// The projected point.
    /// </returns>
    Vector4 PointProjection(const Vector4 &vPoint) const;

    /// <summary>
    /// Calculates if a point is contained in the resident plane.
    /// </summary>
    /// <remarks>
    /// If the plane is null, the result is undefined.
    /// </remarks>
    /// <param name="vPoint">[IN] The point we want know if it is contained on the resident plane.</param>
    /// <returns>
    /// True if the point is contained, false otherwise.
    /// </returns>
    bool Contains(const Vector3 &vPoint) const;

    /// <summary>
    /// Calculates if a point is contained in the resident plane.
    /// </summary>
    /// <remarks>
    /// If the plane is null, the result is undefined.
    /// </remarks>
    /// <param name="vPoint">[IN] The point we want know if it is contained on the resident plane.</param>
    /// <returns>
    /// True if the point is contained, false otherwise.
    /// </returns>
    bool Contains(const Vector4 &vPoint) const;

    /// <summary>
    /// Calculates the length of the direction vector of the resident plane.
    /// </summary>
    /// <returns>
    /// A floating point value representing the value of the calculated length.
    /// </returns>
    float_z GetLength() const;

    /// <summary>
    /// Calculates the squared length of the direction vector of the resident plane.
    /// </summary>
    /// <returns>
    /// A floating point value representing the value of the calculated squared length.
    /// </returns>
    float_z GetSquaredLength() const;

    /// <summary>
    /// Calculates the direction vector of the resident plane.
    /// </summary>
    /// <remarks>
    /// The returned vector will not be normalized unless the plane is.
    /// </remarks>
    /// <returns>
    /// The direction vector of the plane.
    /// </returns>
    Vector3 GetNormal() const;

    /// <summary>
    /// Calculates the minimum distance from the given point to the resident plane, which is the length
    /// of the normal to the plane which passes through the point.
    /// </summary>
    /// <remarks>
    /// If the plane is null, the result is undefined.
    /// </remarks>
    /// <param name="vPoint">[IN] The point we want know it distance from resident plane.</param>
    /// <returns>
    /// A floating point value which represents the minimum distance between the plane and the point.
    /// </returns>
    float_z PointDistance(const Vector3 &vPoint) const;

    /// <summary>
    /// Calculates the minimum distance from the given point to the resident plane, which is the length
    /// of the normal to the plane which passes through the point.
    /// </summary>
    /// <remarks>
    /// If the plane is null, the result is undefined.
    /// </remarks>
    /// <param name="vPoint">[IN] The point we want know it distance from resident plane.</param>
    /// <returns>
    /// A floating point value which represents the minimum distance between the plane and the point.
    /// </returns>
    float_z PointDistance(const Vector4 &vPoint) const;

    /// <summary>
    /// Calculates the number of intersections between the resident plane and two planes provided,
    /// and also calculates the intersection point if there is only one.
    /// </summary>
    /// <remarks>
    /// If there are no intersections or if there are infinite, the output parameter is not modified.
    /// </remarks>
    /// <param name="plane1">[IN] The first plane we want to calculate the intersection with.</param>
    /// <param name="plane2">[IN] The second plane we want to calculate the intersection with.</param>
    /// <param name="vIntersection">[OUT] The intersection point of the three planes, if it exists.</param>
    /// <returns>
    /// An enumerated value that indicates how many intersections were found:<br/>
    /// <br/>
    /// <b>None</b><br/>
    /// There are no intersections.<br/>
    /// - All planes are parallel and not coincident.
    /// - Not all planes intersect with the resident plane.
    /// - All planes intersect but they do not share any common point or line.
    ///
    /// <b>One</b><br/>
    /// There is one intersection.<br/>
    /// - The planes share one point. There are more intersections, but there is only one point that belongs to all the planes.
    ///
    /// <b>Infinite</b><br/>
    /// There are infinite intersections.<br/>
    /// - All planes intersect, defining a single line instead of a point.
    /// - All planes are the same.
    /// </returns>
    EIntersections IntersectionPoint(const Plane &plane1, const Plane &plane2, Vector3 &vIntersection) const;

    /// <summary>
    /// Calculates the number of intersections between the resident plane and two planes provided,
    /// and also calculates the intersection point if there is only one.
    /// </summary>
    /// <remarks>
    /// If there are no intersections or if there are infinite, the output parameter is not modified.
    /// </remarks>
    /// <param name="plane1">[IN] The first plane we want to calculate the intersection with.</param>
    /// <param name="plane2">[IN] The second plane we want to calculate the intersection with.</param>
    /// <param name="vIntersection">[OUT] The intersection point of the three planes, if it exists. The W component is not
    /// changed during the process.</param>
    /// <returns>
    /// An enumerated value that indicates how many intersections were found:<br/>
    /// <br/>
    /// <b>None</b><br/>
    /// There are no intersections.<br/>
    /// - All planes are parallel and not coincident.
    /// - Not all planes intersect with the resident plane.
    /// - All planes intersect but they do not share any common point or line.
    ///
    /// <b>One</b><br/>
    /// There is one intersection.<br/>
    /// - The planes share one point. There are more intersections, but there is only one point that belongs to all the planes.
    ///
    /// <b>Infinite</b><br/>
    /// There are infinite intersections.<br/>
    /// - All planes intersect, defining a single line instead of a point.
    /// - All planes are the same.
    /// </returns>
    EIntersections IntersectionPoint(const Plane &plane1, const Plane &plane2, Vector4 &vIntersection) const;

    /// <summary>
    /// Checks the spacial relation between resident plane and the provided plane.
    /// </summary>
    /// <remarks>
    /// Both planes must be normalized to obtain a correct result.
    /// </remarks>
    /// <param name="plane">[IN] The plane we want check the relation with resident plane.</param>
    /// <returns>
    /// The space relation of the input plane regarding the resident one.
    /// </returns>
    ESpaceRelation SpaceRelation(const Plane &plane) const;

    /// <summary>
    /// Applies a rotation to the resident plane. The normal vector to the plane is rotated,
    /// remaining unchanged the distance from the plane to the origin.
    /// </summary>
    /// <param name="rotation">[IN] A [3x3] matrix containing the rotation to be applied.</param>
    /// <returns>
    /// The rotated plane.
    /// </returns>
    Plane Rotate(const RotationMatrix3x3 &rotation) const;

    /// <summary>
    /// Applies a rotation to the resident plane. The normal vector to the plane is rotated,
    /// remaining unchanged the distance from the plane to the origin.
    /// </summary>
    /// <param name="qRotation">[IN] A quaternion containing the rotation to be applied.</param>
    /// <returns>
    /// The rotated plane.
    /// </returns>
    Plane Rotate(const Quaternion &qRotation) const;

    /// <summary>
    /// Applies a scale to the resident plane.
    /// </summary>
    /// <remarks>
    /// Resultant plane is normalized after this operation.<br/>
    /// The scale must not equal zero and the plane must not be null to obtain a correct result.
    /// </remarks>
    /// <param name="scale">[IN] A [3x3] matrix containing the scale to be applied.</param>
    /// <returns>
    /// The scaled plane.
    /// </returns>
    Plane Scale(const ScalingMatrix3x3 &scale) const;

    /// <summary>
    /// Applies a scale to the resident plane given by the provided vector.
    /// </summary>
    /// <remarks>
    /// Resultant plane is normalized after this operation.<br/>
    /// The scale must not equal zero and the plane must not be null to obtain a correct result.
    /// </remarks>
    /// <param name="vScale">[IN] A vector containing the scale to be applied.</param>
    /// <returns>
    /// The scaled plane.
    /// </returns>
    Plane Scale(const Vector3 &vScale) const;

    /// <summary>
    /// Applies a scale to the resident plane given by the provided amounts for every axis.
    /// </summary>
    /// <remarks>
    /// Resultant plane is normalized after this operation.<br/>
    /// The scale must not equal zero and the plane must not be null to obtain a correct result.
    /// </remarks>
    /// <param name="fScaleX">[IN] The scale amount to be applied in X direction.</param>
    /// <param name="fScaleY">[IN] The scale amount to be applied in Y direction.</param>
    /// <param name="fScaleZ">[IN] The scale amount to be applied in Z direction.</param>
    /// <returns>
    /// The scaled plane.
    /// </returns>
    Plane Scale(const float_z fScaleX, const float_z fScaleY, const float_z fScaleZ) const;

    /// <summary>
    /// Applies a translation to the resident plane.
    /// </summary>
    /// <remarks>
    /// The normal vector to the plane remains unchanged,
    /// but the distance from the plane to the origin is modified according to the translation applied.
    /// </remarks>
    /// <param name="translation">[IN] A [4x3] matrix containing the translation to be applied.</param>
    /// <returns>
    /// The translated plane.
    /// </returns>
    Plane Translate(const TranslationMatrix4x3 &translation) const;

    /// <summary>
    /// Applies a translation to the resident plane.
    /// </summary>
    /// <remarks>
    /// The normal vector to the plane remains unchanged,
    /// but the distance from the plane to the origin is modified according to the translation applied.
    /// </remarks>
    /// <param name="translation">[IN] A [4x4] matrix containing the translation to be applied.</param>
    /// <returns>
    /// The translated plane.
    /// </returns>
    Plane Translate(const TranslationMatrix4x4 &translation) const;

    /// <summary>
    /// Applies a translation to the resident plane given by the provided vector.
    /// </summary>
    /// <remarks>
    /// The normal vector to the plane remains unchanged,
    /// but the distance from the plane to the origin is modified according with the applied translation.
    /// </remarks>
    /// <param name="vTranslation">[IN] A 3d vector containing the translation to be applied.</param>
    /// <returns>
    /// The translated plane.
    /// </returns>
    Plane Translate(const Vector3 &vTranslation) const;

    /// <summary>
    /// Applies a translation to the resident plane given by the provided vector.
    /// </summary>
    /// <remarks>
    /// The normal vector to the plane remains unchanged,
    /// but the distance from the plane to the origin is modified according to the applied translation.
    /// </remarks>
    /// <param name="vTranslation">[IN] A 3d vector containing the translation to be applied.</param>
    /// <returns>
    /// The translated plane.
    /// </returns>
    Plane Translate(const Vector4 &vTranslation) const;

    /// <summary>
    /// Applies a translation to the resident plane given by the provided amounts for every axis.
    /// </summary>
    /// <remarks>
    /// The normal vector to the plane remains unchanged,
    /// but the distance from the plane to the origin is modified according to the applied translation.
    /// </remarks>
    /// <param name="fTranslationX">[IN] Translation amount to be applied in X direction.</param>
    /// <param name="fTranslationY">[IN] Translation amount to be applied in Y direction.</param>
    /// <param name="fTranslationZ">[IN] Translation amount to be applied in Z direction.</param>
    /// <returns>
    /// The translated plane.
    /// </returns>
    Plane Translate(const float_z fTranslationX, const float_z fTranslationY, const float_z fTranslationZ) const;

    /// <summary>
    /// Applies a transformation to the resident plane.
    /// </summary>
    /// <remarks>
    /// The transformation matrix must not equal zero and the plane must not be null to obtain a correct result.<br/>
    /// Resultant plane is normalized after this operation.
    /// </remarks>
    /// <param name="transformation">[IN] A [4x3] matrix containing the transformation to be applied.</param>
    /// <returns>
    /// The transformed plane.
    /// </returns>
    Plane Transform(const TransformationMatrix4x3 &transformation) const;

    /// <summary>
    /// Applies a transformation to the resident plane.
    /// </summary>
    /// <remarks>
    /// The transformation matrix must not equal zero and the plane must not be null to obtain a correct result.<br/>
    /// Resultant plane is normalized after this operation.
    /// </remarks>
    /// <param name="transformation">[IN] A [4x4] matrix containing the transformation to be applied.</param>
    /// <returns>
    /// The transformed plane.
    /// </returns>
    Plane Transform(const TransformationMatrix4x4 &transformation) const;

    /// <summary>
    /// Applies the transformation contained in a space conversion matrix to the resident plane.
    /// </summary>
    /// <param name="spaceConversion">[IN] A [4x4] space conversion matrix containing the transformation to be applied.</param>
    /// <remarks>
    /// Resultant plane is normalized after this operation.
    /// </remarks>
    /// <returns>
    /// The converted plane.
    /// </returns>
    Plane Transform(const SpaceConversionMatrix &spaceConversion) const;

    /// <summary>
    /// Applies the rotation contained in the provided quaternion to the resident plane
    /// around the given point, that acts as pivot of rotation.
    /// </summary>
    /// <param name="qRotation">[IN] A quaternion containing the rotation to be applied.</param>
    /// <param name="vPivot">[IN] The point that acts as pivot of rotation.</param>
    /// <returns>
    /// The rotated plane.
    /// </returns>
    Plane RotateWithPivot(const Quaternion &qRotation, const Vector3 &vPivot) const;

    /// <summary>
    /// Applies the rotation contained in the provided quaternion to the resident plane
    /// around the given point, that acts as pivot of rotation.
    /// </summary>
    /// <param name="qRotation">[IN] A quaternion containing the rotation to be applied.</param>
    /// <param name="vPivot">[IN] The point that acts as pivot of rotation.</param>
    /// <returns>
    /// The rotated plane.
    /// </returns>
    Plane RotateWithPivot(const Quaternion &qRotation, const Vector4 &vPivot) const;

    /// <summary>
    /// Applies the rotation contained in the provided matrix to the resident plane
    /// around the given point, that acts as pivot of rotation.
    /// </summary>
    /// <param name="rotation">[IN] A [3x3] matrix containing the rotation to be applied.</param>
    /// <param name="vPivot">[IN] The point that acts as pivot of rotation.</param>
    /// <returns>
    /// The rotated plane.
    /// </returns>
    Plane RotateWithPivot(const RotationMatrix3x3 &rotation, const Vector3 &vPivot) const;

    /// <summary>
    /// Applies the rotation contained in the provided matrix to the resident plane
    /// around the given point, that acts as pivot of rotation.
    /// </summary>
    /// <param name="rotation">[IN] A [3x3] matrix containing the rotation to be applied.</param>
    /// <param name="vPivot">[IN] The point that acts as pivot of rotation.</param>
    /// <returns>
    /// The rotated plane.
    /// </returns>
    Plane RotateWithPivot(const RotationMatrix3x3 &rotation, const Vector4 &vPivot) const;

    /// <summary>
    /// Applies the scale contained in the provided vector to the resident plane,
    /// acting the given point as pivot of scale.
    /// </summary>
    /// <remarks>
    /// Resultant plane is normalized after this operation.<br/>
    /// The scale must not equal zero and the plane must not be null to obtain a correct result.
    /// </remarks>
    /// <param name="vScale">[IN] A vector containing the scale to be applied in every axis.</param>
    /// <param name="vPivot">[IN] The point that acts as pivot of scale.</param>
    /// <returns>
    /// The scaled plane.
    /// </returns>
    Plane ScaleWithPivot(const Vector3 &vScale, const Vector3 &vPivot) const;

    /// <summary>
    /// Applies the scale contained in the provided vector to the resident plane,
    /// acting the given point as pivot of scale.
    /// </summary>
    /// <remarks>
    /// Resultant plane is normalized after this operation.<br/>
    /// The scale must not equal zero and the plane must not be null to obtain a correct result.
    /// </remarks>
    /// <param name="vScale">[IN] A vector containing the scale to be applied in every axis.</param>
    /// <param name="vPivot">[IN] The point that acts as pivot of scale.</param>
    /// <returns>
    /// The scaled plane.
    /// </returns>
    Plane ScaleWithPivot(const Vector3 &vScale, const Vector4 &vPivot) const;

    /// <summary>
    /// Scales the resident plane by the provided amounts for every axis,
    /// acting the given point as pivot of scale.
    /// </summary>
    /// <remarks>
    /// Resultant plane is normalized after this operation.<br/>
    /// The scale must not equal zero and the plane must not be null to obtain a correct result.
    /// </remarks>
    /// <param name="fScaleX">[IN] Amount of scale to be applied in X direction.</param>
    /// <param name="fScaleY">[IN] Amount of scale to be applied in Y direction.</param>
    /// <param name="fScaleZ">[IN] Amount of scale to be applied in Z direction.</param>
    /// <param name="vPivot">[IN] The point that acts as pivot of scale.</param>
    /// <returns>
    /// The scaled plane.
    /// </returns>
    Plane ScaleWithPivot(const float_z fScaleX, const float_z fScaleY, const float_z fScaleZ, const Vector3 &vPivot) const;

    /// <summary>
    /// Scales the resident plane by the provided amounts for every axis,
    /// acting the given point as pivot of scale.
    /// </summary>
    /// <remarks>
    /// Resultant plane is normalized after this operation.<br/>
    /// The scale must not equal zero and the plane must not be null to obtain a correct result.
    /// </remarks>
    /// <param name="fScaleX">[IN] Amount of scale to be applied in X direction.</param>
    /// <param name="fScaleY">[IN] Amount of scale to be applied in Y direction.</param>
    /// <param name="fScaleZ">[IN] Amount of scale to be applied in Z direction.</param>
    /// <param name="vPivot">[IN] The point that acts as pivot of scale.</param>
    /// <returns>
    /// The scaled plane.
    /// </returns>
    Plane ScaleWithPivot(const float_z fScaleX, const float_z fScaleY, const float_z fScaleZ, const Vector4 &vPivot) const;

    /// <summary>
    /// Applies the scale contained in the provided matrix to the resident plane,
    /// acting the given point as pivot of scale.
    /// </summary>
    /// <remarks>
    /// Resultant plane is normalized after this operation.<br/>
    /// The scale must not equal zero and the plane must not be null to obtain a correct result.
    /// </remarks>
    /// <param name="scale">[IN] A [3x3] matrix containing the scale to be applied in every axis.</param>
    /// <param name="vPivot">[IN] The point that acts as pivot of scale.</param>
    /// <returns>
    /// The scaled plane.
    /// </returns>
    Plane ScaleWithPivot(const ScalingMatrix3x3 &scale, const Vector3 &vPivot) const;

    /// <summary>
    /// Applies the scale contained in the provided matrix to the resident plane,
    /// acting the given point as pivot of scale.
    /// </summary>
    /// <remarks>
    /// Resultant plane is normalized after this operation.
    /// </remarks>
    /// <param name="scale">[IN] A [3x3] matrix containing the scale to be applied in every axis.</param>
    /// <param name="vPivot">[IN] The point that acts as pivot of scale.</param>
    /// <returns>
    /// The scaled plane.
    /// </returns>
    Plane ScaleWithPivot(const ScalingMatrix3x3 &scale, const Vector4 &vPivot) const;

    /// <summary>
    /// Applies the transformation contained in the provided matrix to the resident plane
    /// around the given point, that acts as pivot of transformation.
    /// </summary>
    /// <remarks>
    /// The transformation matrix must not equal zero and the plane must not be null to obtain a correct result.<br/>
    /// Resultant plane is normalized after this operation.
    /// </remarks>
    /// <param name="transformation">[IN] A [4x3] matrix containing the transformation to be applied.</param>
    /// <param name="vPivot">[IN] The point that acts as pivot of transformation.</param>
    /// <returns>
    /// The transformed plane.
    /// </returns>
    Plane TransformWithPivot(const TransformationMatrix4x3 &transformation, const Vector3 &vPivot) const;

    /// <summary>
    /// Applies the transformation contained in the provided matrix to the resident plane
    /// around the given point, that acts as pivot of transformation.
    /// </summary>
    /// <remarks>
    /// The transformation matrix must not equal zero and the plane must not be null to obtain a correct result.<br/>
    /// Resultant plane is normalized after this operation.<br/>
    /// The W component of the pivot point doesn't affect the result.
    /// </remarks>
    /// <param name="transformation">[IN] A [4x3] matrix containing the transformation to be applied.</param>
    /// <param name="vPivot">[IN] The point that acts as pivot of transformation.</param>
    /// <returns>
    /// The transformed plane.
    /// </returns>
    Plane TransformWithPivot(const TransformationMatrix4x3 &transformation, const Vector4 &vPivot) const;

    /// <summary>
    /// Applies the transformation contained in the provided matrix to the resident plane
    /// around the given point, that acts as pivot of transformation.
    /// </summary>
    /// <remarks>
    /// The transformation matrix must not equal zero and the plane must not be null to obtain a correct result.<br/>
    /// Resultant plane is normalized after this operation.
    /// </remarks>
    /// <param name="transformation">[IN] A [4x4] matrix containing the transformation to be applied.</param>
    /// <param name="vPivot">[IN] The point that acts as pivot of transformation.</param>
    /// <returns>
    /// The transformed plane.
    /// </returns>
    Plane TransformWithPivot(const TransformationMatrix4x4 &transformation, const Vector3 &vPivot) const;

    /// <summary>
    /// Applies the transformation contained in the provided matrix to the resident plane
    /// around the given point, that acts as pivot of transformation.
    /// </summary>
    /// <remarks>
    /// The transformation matrix must not equal zero and the plane must not be null to obtain a correct result.<br/>
    /// Resultant plane is normalized after this operation.<br/>
    /// The W component of the pivot point doesn't affect the result.
    /// </remarks>
    /// <param name="transformation">[IN] A [4x4] matrix containing the transformation to be applied.</param>
    /// <param name="vPivot">[IN] The point that acts as pivot of transformation.</param>
    /// <returns>
    /// The transformed plane.
    /// </returns>
    Plane TransformWithPivot(const TransformationMatrix4x4 &transformation, const Vector4 &vPivot) const;

    /// <summary>
    /// Converts plane into a string.
    /// </summary>
    /// <remarks>
    /// The format of the string is:<br/>
    /// "PL($a,$b,$c,$d)".<br/>
    /// Where "$" means "string representation of attribute".
    /// </remarks>
    /// <returns>
    /// The string with the format specified.
    /// </returns>
    string_z ToString() const;

private:

    /// <summary>
    /// Calculates the dot product between the direction vector of the resident plane and the provided vector.
    /// </summary>
    /// <typeparam name="VectorT">Allowed types: Vector3, Vector4, Vector3, Vector4.</typeparam>
    /// <param name="vVector">[IN] The vector which we want to calculate the dot product with.</param>
    template <class VectorT>
    float_z DotProductImp(const VectorT &vVector) const;

    /// <summary>
    /// Calculates the angle between the direction vector of the resident plane and the provided vector via dot product.
    /// </summary>
    /// <typeparam name="VectorT">Allowed types: Vector3, Vector4, Vector3, Vector4.</typeparam>
    /// <param name="vVector">[IN] The vector whose angle with the resident plane we want to calculate.</param>
    template <class VectorT>
    float_z AngleBetweenImp(const VectorT &vVector) const;

    /// <summary>
    /// Applies the rotation contained in the provided quaternion to the resident plane
    /// around the given point, that acts as pivot of rotation.
    /// </summary>
    /// <typeparam name="VectorT">Allowed types: Vector3, Vector4.</typeparam>
    /// <param name="qRotation">[IN] A quaternion containing the rotation to be applied.</param>
    /// <param name="vPivot">[IN] The point that acts as pivot of rotation.</param>
    /// <returns>
    /// The rotated plane.
    /// </returns>
    template <class VectorT>
    Plane RotateWithPivotImp(const Quaternion &qRotation, const VectorT &vPivot) const;

    /// <summary>
    /// Applies the rotation contained in the provided matrix to the resident plane
    /// around the given point, that acts as pivot of rotation.
    /// </summary>
    /// <typeparam name="VectorT">Allowed types: Vector3, Vector4.</typeparam>
    /// <param name="rotation">[IN] A [3x3] matrix containing the rotation to be applied.</param>
    /// <param name="vPivot">[IN] The point that acts as pivot of rotation.</param>
    /// <returns>
    /// The rotated plane.
    /// </returns>
    template <class VectorT>
    Plane RotateWithPivotImp(const RotationMatrix3x3 &rotation, const VectorT &vPivot) const;

    /// <summary>
    /// Applies the scale contained in the provided vector to the resident plane,
    /// acting the given point as pivot of scale.
    /// </summary>
    /// <typeparam name="VectorT">Allowed types: Vector3, Vector4.</typeparam>
    /// <param name="vScale">[IN] A vector containing the scale to be applied in every axis.</param>
    /// <param name="vPivot">[IN] The point that acts as pivot of scale.</param>
    /// <returns>
    /// The scaled plane.
    /// </returns>
    template <class VectorT>
    Plane ScaleWithPivotImp(const Vector3 &vScale, const VectorT &vPivot) const;

    /// <summary>
    /// Scales the resident plane by the provided amounts for every axis,
    /// acting the given point as pivot of scale.
    /// </summary>
    /// <typeparam name="VectorT">Allowed types: Vector3, Vector4.</typeparam>
    /// <param name="fScaleX">[IN] Amount of scale to be applied in X direction.</param>
    /// <param name="fScaleY">[IN] Amount of scale to be applied in Y direction.</param>
    /// <param name="fScaleZ">[IN] Amount of scale to be applied in Z direction.</param>
    /// <param name="vPivot">[IN] The point that acts as pivot of scale.</param>
    /// <returns>
    /// The scaled plane.
    /// </returns>
    template <class VectorT>
    Plane ScaleWithPivotImp(const float_z fScaleX, const float_z fScaleY, const float_z fScaleZ, const VectorT &vPivot) const;

    /// <summary>
    /// Applies the scale contained in the provided matrix to the resident plane,
    /// acting the given point as pivot of scale.
    /// </summary>
    /// <typeparam name="VectorT">Allowed types: Vector3, Vector4.</typeparam>
    /// <param name="scale">[IN] A [3x3] matrix containing the scale to be applied in every axis.</param>
    /// <param name="vPivot">[IN] The point that acts as pivot of scale.</param>
    /// <returns>
    /// The scaled plane.
    /// </returns>
    template <class VectorT>
    Plane ScaleWithPivotImp(const ScalingMatrix3x3 &scale, const VectorT &vPivot) const;

    /// <summary>
    /// Applies the transformation contained in the provided matrix to the resident plane
    /// around the given point, that acts as pivot of transformation.
    /// </summary>
    /// <typeparam name="VectorT">Allowed types: Vector3, Vector4.</typeparam>
    /// <param name="transformation">[IN] A [4x3] or [4x4] matrix containing the transformation to be applied.</param>
    /// <param name="vPivot">[IN] The point that acts as pivot of transformation.</param>
    /// <returns>
    /// The transformed plane.
    /// </returns>
    template <class MatrixT, class VectorT>
    Plane TransformWithPivotImp(const MatrixT &transformation, const VectorT &vPivot) const;


    /// <summary>
    /// Calculates the orthogonal projection of a given point over the resident plane.
    /// </summary>
    /// <typeparam name="VectorT">Allowed types: Vector3, Vector4.</typeparam>
    /// <param name="vPoint">[IN] A 3D vector which represents the point we want project.</param>
    /// <returns>
    /// The projected point.
    /// </returns>
    template <class VectorT>
    VectorT PointProjectionImp(const VectorT &vPoint) const;

    /// <summary>
    /// Calculates if a point is contained on the resident plane.
    /// </summary>
    /// <typeparam name="VectorT">Allowed types: Vector3, Vector4.</typeparam>
    /// <param name="vPoint">[IN] The point we want know if it is contained on the resident plane.</param>
    /// <returns>
    /// True if the point is contained, false otherwise.
    /// </returns>
    template <class VectorT>
    bool ContainsImp(const VectorT &vPoint) const;

    /// <summary>
    /// Calculates the minimum distance from the given point to the resident plane, which is the length
    /// of the normal to the plane which passes through the point.
    /// </summary>
    /// <typeparam name="VectorT">Allowed types: Vector3, Vector4.</typeparam>
    /// <param name="vPoint">[IN] The point we want know it distance from resident plane.</param>
    /// <returns>
    /// A floating point value which represents the minimum distance between the plane and the point.
    /// </returns>
    template <class VectorT>
    float_z PointDistanceImp(const VectorT &vPoint) const;

    /// <summary>
    /// Calculates the number of intersections between the resident plane and two planes provided,
    /// and also calculates the intersection point if there is only one.
    /// </summary>
    /// <typeparam name="VectorT">Allowed types: Vector3, Vector4.</typeparam>
    /// <param name="plane1">[IN] The first plane we want to calculate the intersection with.</param>
    /// <param name="plane2">[IN] The second plane we want to calculate the intersection with.</param>
    /// <param name="vIntersection">[OUT] The intersection point of the three planes, if it exists.</param>
    /// <returns>
    /// An enumerated value which represents the number of intersections between the three planes, and can take
    /// the following values: E_None, E_One and E_Infinite.
    /// </returns>
    template <class VectorT>
    EIntersections IntersectionPointImp(const Plane &plane1, const Plane &plane2, VectorT &vIntersection) const;
    

    // ATTRIBUTES
    // ---------------
public:

    /// <summary>
    /// X coefficient of the plane equation.
    /// </summary>
    float_z a;

    /// <summary>
    /// Y coefficient of the plane equation.
    /// </summary>
    float_z b;

    /// <summary>
    /// Z coefficient of the plane equation.
    /// </summary>
    float_z c;

    /// <summary>
    /// Independent term of the plane equation.
    /// </summary>
    float_z d;
};


} // namespace z


#endif // __PLANE__
