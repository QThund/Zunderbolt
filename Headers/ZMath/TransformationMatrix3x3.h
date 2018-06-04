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

#ifndef __TRANSFORMATIONMATRIX3X3__
#define __TRANSFORMATIONMATRIX3X3__

#include "ZMath/Matrix3x3.h"



namespace z
{

// FORWARD DELCARATIONS
// -----------------------
class Vector2;


/// <summary>
/// It represents a 3x3 matrix containing spatial transformations relating to translation, rotation and scaling,
/// applying them to 2D space points.
/// </summary>
class Z_MATH_MODULE_SYMBOLS TransformationMatrix3x3 : public Matrix3x3
{

    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor. It is an empty constructor, it does not assign any value.
    /// </summary>
    TransformationMatrix3x3();

    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="transformation">[IN] The 3x3 transformation matrix from which we want to create a copy in the resident 3x3 transformation matrix.</param>
    TransformationMatrix3x3(const TransformationMatrix3x3 &transformation);

    /// <summary>
    /// Base type constructor.
    /// </summary>
    /// <remarks>
    /// If you use this constructor, be sure that you are constructing a transformation matrix,
    /// otherwise unpredictable behavior could happen.
    /// </remarks>
    /// <param name="transformation">[IN] The 3x3 matrix in which we want the resident 3x3 transformation matrix to be based.</param>
    TransformationMatrix3x3(const Matrix3x3 &transformation);

    /// <summary>
    /// Constructor from a 2D vector which stores a scale, a floating point value which stores a rotation
    /// and a 2D vector which stores a translation.
    /// </summary>
    /// <param name="vTranslation">[IN] Vector with the displacement values.</param>
    /// <param name="fRotationAngle">[IN] Angle of rotation.</param>
    /// <param name="vScale">[IN] Vector with the scale values.</param>
    TransformationMatrix3x3(const Vector2 &vTranslation, const float_z fRotationAngle, const Vector2 &vScale);


    // PROPERTIES
    // ---------------
public:

    /// <summary>
    /// Gets an identity matrix.
    /// </summary>
    /// <remarks>
    /// The identity matrix is a matrix whose elements are zero except the main diagonal that is composed by ones:<br/>
    /// <br/>
    /// \f$ I = \begin{bmatrix} 1 & 0 & 0 \\ 0 & 1 & 0 \\ 0 & 0 & 1 \end{bmatrix}\f$<br/>
    /// </remarks>
    /// <returns>
    /// The identity matrix.
    /// </returns>
    static const TransformationMatrix3x3& GetIdentity();


    // METHODS
    // ---------------
public:

    /// <summary>
    /// Assignation operator. Assigns the provided matrix to the resident matrix.
    /// </summary>
    /// <param name="matrix">[IN] The matrix to be assigned.</param>
    /// <returns>
    /// A reference to the modified matrix.
    /// </returns>
    TransformationMatrix3x3& operator=(const Matrix3x3 &matrix);

    /// <summary>
    /// Extracts the scale, the rotation and the translation into separated variables.
    /// </summary>
    /// <remarks>
    /// If the matrix was built using a null scale, the results are undefined.
    /// </remarks>
    /// <param name="vTranslation">[OUT] A 2D vector to store the translation.</param>
    /// <param name="fRotationAngle">[OUT] Floating point variable to store the angle of rotation.</param>
    /// <param name="vScale">[OUT] A 2D vector to store the scale.</param>
    void Decompose(Vector2 &vTranslation, float_z &fRotationAngle, Vector2 &vScale) const;

    /// <summary>
    /// Extracts the displacement components from the matrix.
    /// </summary>
    /// <param name="vTranslation">[OUT] A 2D vector where to store the displacement.</param>
    void GetTranslation(Vector2 &vTranslation) const;

    /// <summary>
    /// Extracts the rotation angle from the transformation matrix.
    /// </summary>
    /// <remarks>
    /// If the matrix was built using a null scale, the result is undefined.
    /// </remarks>
    /// <param name="fRotationAngle">[OUT] Floating point variable to store the angle of rotation.</param>
    void GetRotation(float_z &fRotationAngle) const;

    /// <summary>
    /// Extracts the scale factors from the matrix.
    /// </summary>
    /// <param name="vScale">[OUT] A 2D vector where to store the scale factors.</param>
    void GetScale(Vector2 &vScale) const;

    /// <summary>
    /// Turns the hand convention into opposite rules.
    /// </summary>
    /// <remarks>
    /// Remember that Zunderbolt works with left-hand convention by default.<br/>
    /// To do that, we simply invert rotation (by trasposing its submatrix).
    /// </remarks>
    /// <returns>
    /// The switched matrix.
    /// </returns>
    TransformationMatrix3x3 SwitchHandConvention() const;

private:

    // Preventing the operators from base class to be used.
    Matrix3x3 operator*(const float_z fScalar) const;
    Matrix3x3 operator*(const Matrix3x3 &matrix) const;
    Matrix3x4 operator*(const Matrix3x4& matrix) const;
    Matrix3x3 operator/(const float_z fScalar) const;
    Matrix3x3 operator+(const Matrix3x3 &matrix) const;
    Matrix3x3 operator-(const Matrix3x3 &matrix) const;
    Matrix3x3& operator*=(const Matrix3x3 &matrix);
    Matrix3x3& operator*=(const float_z Scalar);
    Matrix3x3& operator/=(const float_z fScalar);
    Matrix3x3& operator+=(const Matrix3x3 &matrix);
    Matrix3x3& operator-=(const Matrix3x3 &matrix);

    // Hidden method to prevent it could be used.
    void ResetToZero();

};


// Preventing friend global operator to be called.
TransformationMatrix3x3 operator*(const float_z fScalar, const TransformationMatrix3x3 &matrix);


} // namespace z


#endif // __TRANSFORMATIONMATRIX3x3__
