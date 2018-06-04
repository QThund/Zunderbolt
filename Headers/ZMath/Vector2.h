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

#ifndef __VECTOR2__
#define __VECTOR2__

#include "ZMath/MathModuleDefinitions.h"
#include "ZCommon/DataTypes/StringsDefinitions.h"


namespace z
{

// Forward declarations
// ---------------------
class TransformationMatrix3x3;
class Matrix2x2;


/// <summary>
/// A vector with two components: X and Y.
/// </summary>
/// <remarks>
///    A vector is a geometric object that has both a magnitude (or length) and a direction.
/// </remarks>
class Z_MATH_MODULE_SYMBOLS Vector2
{
    // FRIENDS
    // ---------------
public:

    /// <summary>
    /// Product of a scalar by a vector. All the components are multiplied by the scalar provided.
    /// </summary>
    /// <param name="fScalar">[IN] Scalar to multiply.</param>
    /// <param name="vVector">[IN] Vector to be multiplied by.</param>
    /// <returns>
    /// A vector that is the result of the product.
    /// </returns>
    friend Vector2 Z_MATH_MODULE_SYMBOLS operator*(const float_z fScalar, const Vector2 &vVector);


    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor. It is an empty constructor, it does not assign any value.
    /// </summary>
    Vector2();

    /// <summary>
    /// Constructor that receives the value of every vector's component.
    /// </summary>
    /// <param name="fValueX">[IN] The value for X component.</param>
    /// <param name="fValueY">[IN] The value for Y component.</param>
    Vector2(const float_z fValueX, const float_z fValueY);

    /// <summary>
    /// Constructor from a single value for all the vector's components.
    /// </summary>
    /// <param name="fValueAll">[IN] The value for all components.</param>
    explicit Vector2(const float_z fValueAll);

    /// <summary>
    /// Constructor that receives an array of scalars.
    /// </summary>
    /// <remarks>
    /// The array must contain, at least, two elements. Only the first two elements will be considered; the rest will be ignored.
    /// </remarks>
    /// <param name="arValues">[IN] An array of scalars. It must contain, at least, two elements. If it is null, the behavior is undefined.</param>
    explicit Vector2(const float_z* arValues);

    /// <summary>
    /// Constructor that receives a pack of four scalars.
    /// </summary>
    /// <remarks>
    /// Only the two first elements in the pack (most significant bits) are considered.
    /// </remarks>
    /// <param name="value">[IN] 4x32 packed floating point value containing the two components.</param>
    explicit Vector2(const vf32_z value);


    // PROPERTIES
    // ---------------
public:

    /// <summary>
    /// Gets a vector whose components equal zero.
    /// </summary>
    /// <returns>
    /// A null vector.
    /// </returns>
    static const Vector2& GetNullVector();

    /// <summary>
    /// Gets a vector whose components equal one.
    /// </summary>
    /// <returns>
    /// A vector of ones.
    /// </returns>
    static const Vector2& GetVectorOfOnes();

    /// <summary>
    /// Gets a unit vector that points to the positive direction of the X axis.
    /// </summary>
    /// <returns>
    /// A unit vector that points to the positive direction of the X axis.
    /// </returns>
    static const Vector2& GetUnitVectorX();

    /// <summary>
    /// Gets a unit vector that points to the positive direction of the Y axis.
    /// </summary>
    /// <returns>
    /// A unit vector that points to the positive direction of the Y axis.
    /// </returns>
    static const Vector2& GetUnitVectorY();

    /// <summary>
    /// Gets a unit vector that points to the negative direction of the X axis.
    /// </summary>
    /// <returns>
    /// A unit vector that points to the negative direction of the X axis.
    /// </returns>
    static const Vector2& GetUnitVectorInvX();

    /// <summary>
    /// Gets a unit vector that points to the negative direction of the Y axis.
    /// </summary>
    /// <returns>
    /// A unit vector that points to the negative direction of the Y axis.
    /// </returns>
    static const Vector2& GetUnitVectorInvY();


    // METHODS
    // ---------------
public:

    /// <summary>
    /// Checks if two vectors are equal.
    /// </summary>
    /// <param name="vVector">[IN] The vector to which to compare.</param>
    /// <returns>
    /// True if vectors are the same; False otherwise.
    /// </returns>
    bool operator==(const Vector2 &vVector) const;

    /// <summary>
    /// Checks if two vectors are not equal.
    /// </summary>
    /// <param name="vVector">[IN] The vector to which to compare.</param>
    /// <returns>
    /// True if vectors are not the same; False otherwise.
    /// </returns>
    bool operator!=(const Vector2 &vVector) const;

    /// <summary>
    /// Adds two vectors by adding each component.
    /// </summary>
    /// <param name="vVector">[IN] Vector to be added.</param>
    /// <returns>
    /// A vector that is the result of the addition.
    /// </returns>
    Vector2 operator+(const Vector2 &vVector) const;

    /// <summary>
    /// Substracts two vectors by substracting each component.
    /// </summary>
    /// <param name="vVector">[IN] Vector to be substracted.</param>
    /// <returns>
    /// A vector that is the result of the subtraction.
    /// </returns>
    Vector2 operator-(const Vector2 &vVector) const;

    /// <summary>
    /// Multiplies the vector by a scalar.
    /// </summary>
    /// <param name="fScalar">[IN] The scalar to multiply by.</param>
    /// <returns>
    /// A vector that is the result of the product.
    /// </returns>
    Vector2 operator*(const float_z fScalar) const;

    /// <summary>
    /// Multiplies two vectors by multiplying each component.
    /// </summary>
    /// <param name="vVector">[IN] Vector to multiply by.</param>
    /// <returns>
    /// A vector that is the result of the product.
    /// </returns>
    Vector2 operator*(const Vector2 &vVector) const;

    /// <summary>
    /// Multiplies the vector by a 2x2 matrix.
    /// </summary>
    /// <remarks>
    /// The vector is treated as if it was a one-dimensional matrix with one row.
    /// </remarks>
    /// <param name="matrix">[IN] The matrix to multiply by.</param>
    /// <returns>
    /// A vector that is the result of the product.
    /// </returns>
    Vector2 operator*(const Matrix2x2 &matrix) const;

    /// <summary>
    /// Divides the vector by a scalar.
    /// </summary>
    /// <param name="fScalar">[IN] The scalar to divide by. If it equals zero, the result is undefined.</param>
    /// <returns>
    /// A vector that is the result of the division.
    /// </returns>
    Vector2 operator/(const float_z fScalar) const;

    /// <summary>
    /// Divides two vectors by dividing each component.
    /// </summary>
    /// <param name="vVector">[IN] The vector to divide by. If any of its components equals zero, the result is undefined.</param>
    /// <returns>
    /// A vector that is the result of the division.
    /// </returns>
    Vector2 operator/(const Vector2 &vVector) const;

    /// <summary>
    /// Adds a vector to the resident vector. The resident vector is set to the result.
    /// </summary>
    /// <param name="vVector">[IN] The vector to be added.</param>
    /// <returns>
    /// A reference to the resident vector, result of the addition.
    /// </returns>
    Vector2& operator+=(const Vector2 &vVector);

    /// <summary>
    /// Subtracts a vector to the resident vector. The resident vector is set to the result.
    /// </summary>
    /// <param name="vVector">[IN] The vector to be substracted.</param>
    /// <returns>
    /// A reference to the resident vector, result of the subtraction.
    /// </returns>
    Vector2& operator-=(const Vector2 &vVector);

    /// <summary>
    /// Multiplies the resident vector by a scalar. The resident vector is set to the result.
    /// </summary>
    /// <param name="fScalar">[IN] The scalar to multiply by.</param>
    /// <returns>
    /// A reference to the resident vector, result of the product.
    /// </returns>
    Vector2& operator*=(const float_z fScalar);

    /// <summary>
    /// Multiplies the resident vector by a 2x2 matrix. The resident vector is set to the result.
    /// </summary>
    /// <remarks>
    /// The vector is treated as if it was a one-dimensional matrix with one row.
    /// </remarks>
    /// <param name="matrix">[IN] The matrix to multiply by.</param>
    /// <returns>
    /// A reference to the resident vector, result of the product.
    /// </returns>
    Vector2& operator*=(const Matrix2x2 &matrix);

    /// <summary>
    /// Multiplies two vectors by multiplying each component. The resident vector is set to the result.
    /// </summary>
    /// <param name="vVector">[IN] The vector to multiply by.</param>
    /// <returns>
    /// A reference to the resident vector, result of the product.
    /// </returns>
    Vector2& operator*=(const Vector2 &vVector);

    /// <summary>
    /// Divides the vector by a scalar. The resident vector is set to the result.
    /// </summary>
    /// <param name="fScalar">[IN] The scalar to divide by. If it equals zero, the result is undefined.</param>
    /// <returns>
    /// A reference to the resident vector, result of the division.
    /// </returns>
    Vector2& operator/=(const float_z fScalar);

    /// <summary>
    /// Divides two vectors by dividing each component. The resident vector is set to the result.
    /// </summary>
    /// <param name="vVector">[IN] The vector to divide by. If any of its components equal zero, the result is undefined.</param>
    /// <returns>
    /// A reference to the resident vector, result of the division.
    /// </returns>
    Vector2& operator/=(const Vector2 &vVector);

    /// <summary>
    /// Negates the vector by negating each component.
    /// </summary>
    /// <returns>
    /// A vector that is the result of the negation.
    /// </returns>
    Vector2 operator-() const;

    /// <summary>
    /// Calculates the length (magnitude) of the vector.
    /// </summary>
    /// <returns>
    /// A scalar whose value equals the length of the vector.
    /// </returns>
    float_z GetLength() const;

    /// <summary>
    /// Calculates the squared length of the vector.
    /// </summary>
    /// <remarks>
    /// The squared length is calculated faster than the length and is commonly used to compare two vectors.
    /// </remarks>
    /// <returns>
    /// A scalar whose value equals the squared length of the vector.
    /// </returns>
    float_z GetSquaredLength() const;

    /// <summary>
    /// Calculates the vector that is perpendicular to the resident vector.
    /// </summary>
    /// <remarks>
    /// It's like rotating the vector by a quarter of circunference, clockwise.
    /// </remarks>
    /// <returns>
    /// A vector that is perpendicular to the resident vector.
    /// </returns>
    Vector2 GetPerpendicular() const;

    /// <summary>
    /// Normalizes the vector. The vector keeps its direction but its length equals one.
    /// </summary>
    /// <remarks>
    /// If the vector is null, the result is undefined.
    /// </remarks>
    /// <returns>
    /// The normalized vector.
    /// </returns>
    Vector2 Normalize() const;

    /// <summary>
    /// Sets all the components of the vector to one.
    /// </summary>
    void ResetToOne();

    /// <summary>
    /// Sets all the components of the vector to zero.
    /// </summary>
    void ResetToZero();

    /// <summary>
    /// Applies a transformation to the resident vector, multiplying it by a transformation matrix.
    /// </summary>
    /// <remarks>
    /// The transformation can be a rotation, scale, translation or a combination of them.
    /// </remarks>
    /// <param name="matrix">[IN] The transformation matrix.</param>
    /// <returns>
    /// The transformed vector.
    /// </returns>
    Vector2 Transform(const TransformationMatrix3x3 &matrix) const;

    /// <summary>
    /// Rotates the vector by a concrete angle.
    /// </summary>
    /// <param name="fRotationAngle">[IN] The rotation angle.</param>
    /// <returns>
    /// The rotated vector.
    /// </returns>
    Vector2 Transform(const float_z fRotationAngle) const;

    /// <summary>
    /// Checks if all components equal zero.
    /// </summary>
    /// <returns>
    /// True if all components equal zero; False otherwise.
    /// </returns>
    bool IsZero() const;

    /// <summary>
    /// Checks if all components equal one.
    /// </summary>
    /// <returns>
    /// True if all components equal one; False otherwise.
    /// </returns>
    bool IsVectorOfOnes() const;

    /// <summary>
    /// Calculates the dot product of two vectors.
    /// </summary>
    /// <remarks>
    /// Remember that the dot product is commutative.
    /// </remarks>
    /// <param name="vVector">[IN] The second operand of the product.</param>
    /// <returns>
    /// A scalar whose value equals the result of dot product.
    /// </returns>
    float_z DotProduct(const Vector2 &vVector) const;

    /// <summary>
    /// Calculates the smaller angle between two vectors.
    /// </summary>
    /// <remarks>
    /// The angle will be always lower than or equal to \f$\pi\f$ radians (\f$ 180^0\f$). The order of the operands doesn't affect the result.
    /// </remarks>
    /// <param name="vVector">[IN] The second operand.</param>
    /// <returns>
    /// A scalar whose value equals the angle between the vectors.
    /// </returns>
    float_z AngleBetween(const Vector2 &vVector) const;

    /// <summary>
    /// Calculates the linear interpolation between two vectors.
    /// </summary>
    /// <param name="fProportion">[IN] A value that represents how close is the resultant vector to the provided 
    /// vector. A value of 0 will produce a vector that equals the resident vector; a value of 1 will produce a vector that
    /// equals the input vector. Note tha values lower than 0 and higher than 1 are also valid.</param>
    /// <param name="vVector">[IN] Vector with which to interpolate.</param>
    /// <returns>
    /// A vector that is the result of the interpolation.
    /// </returns>
    Vector2 Lerp(const float_z fProportion, const Vector2 &vVector) const;

    /// <summary>
    /// Calculates the distance between two vectors (two points).
    /// </summary>
    /// <param name="vVector">[IN] Vector to calculate the distance to.</param>
    /// <returns>
    /// A positive value that equals the distance between both vectors.
    /// </returns>
    float_z Distance(const Vector2 &vVector) const;

    /// <summary>
    /// Converts vector into a string.
    /// </summary>
    /// <remarks>
    /// The format of the string is:<br/>
    /// "V2($x,$y)".<br/>
    /// Where "$" means "string representation of attribute".
    /// </summary>
    /// <returns>
    /// The string with the format specified.
    /// </returns>
    string_z ToString() const;
    

    // ATTRIBUTES
    // ---------------
public:

    /// <summary>
    /// Vector's X coordinate.
    /// </summary>
    float_z x;

    /// <summary>
    /// Vector's Y coordinate.
    /// </summary>
    float_z y;
};

} // namespace z


#endif // __VECTOR2__
