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

#ifndef __MATRIX3X4__
#define __MATRIX3X4__

#include "ZMath/MathModuleDefinitions.h"
#include "Matrix4x4.h"
#include "ZCommon/DataTypes/StringsDefinitions.h"
#include "Matrix3x3.h"
#include "Matrix4x3.h"


namespace z
{

// FORWARD DECLARATIONS
// ---------------------
class Matrix3x3;
class Matrix4x3;
class Matrix4x4;


/// <summary>
/// This class implements the functionality of a matrix with 3 rows and 4 columns.
/// </summary>
/// <remarks>
/// A matrix is a rectangular arrangement of numbers.<br/>
/// The horizontal and vertical lines in a matrix
/// are called rows and columns, respectively. The numbers in the matrix are called its entries or its elements.<br/>
/// To specify the size of a matrix, a matrix with m rows and n columns is called an m-by-n matrix or m x n matrix,
/// while m and n are called its dimensions.<br/>
/// Every element is referenced by its position in the matrix.<br/>
/// Due to we use a row by column convention, we will always write first the row of the element and then its
/// column: the element in the i row and the j column is denoted \f$ A_{ij} \f$.<br/>
/// In this case, we will work with 4x3 matrices, therefore our matrix will be:<br/>
/// <br/>
/// \f$ A = \begin{bmatrix} a_{00} & a_{01} & a_{02} & a_{03}\\ a_{10} & a_{11} & a_{12} & a_{13}\\ a_{20} & a_{21} & a_{22} & a_{23}\end{bmatrix}\f$
/// </remarks>
class Z_MATH_MODULE_SYMBOLS Matrix3x4
{
    // FRIENDS
    // ---------------
public:
    /// <summary>
    /// Multiply by scalar operator. All matrix components are multiplied by the scalar.
    /// </summary>
    /// <param name="fScalar">[IN] The scalar term of product.</param>
    /// <param name="matrix">[IN] The matrix term of product.</param>
    /// <returns>
    /// The resultant matrix.
    /// </returns>
    friend Matrix3x4 Z_MATH_MODULE_SYMBOLS operator*(const float_z fScalar, const Matrix3x4 &matrix);


     // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor. It is an empty constructor, it does not assign any value.
    /// </summary>
    Matrix3x4();

    /// <summary>
    /// Constructor from a floating point value which with fill all matrix's elements.
    /// </summary>
    /// <param name="fValueAll">[IN] The floating point value used to fill the matrix.</param>
    explicit Matrix3x4(const float_z fValueAll);

    /// <summary>
    /// Constructor from a floating point value for each element of the matrix.
    /// </summary>
    /// <param name="f00">[IN] Floating point value for element of row 0, column 0.</param>
    /// <param name="f01">[IN] Floating point value for element of row 0, column 1.</param>
    /// <param name="f02">[IN] Floating point value for element of row 0, column 2.</param>
    /// <param name="f03">[IN] Floating point value for element of row 0, column 3.</param>
    /// <param name="f10">[IN] Floating point value for element of row 1, column 0.</param>
    /// <param name="f11">[IN] Floating point value for element of row 1, column 1.</param>
    /// <param name="f12">[IN] Floating point value for element of row 1, column 2.</param>
    /// <param name="f13">[IN] Floating point value for element of row 1, column 3.</param>
    /// <param name="f20">[IN] Floating point value for element of row 2, column 0.</param>
    /// <param name="f21">[IN] Floating point value for element of row 2, column 1.</param>
    /// <param name="f22">[IN] Floating point value for element of row 2, column 2.</param>
    /// <param name="f23">[IN] Floating point value for element of row 2, column 3.</param>
    Matrix3x4(const float_z f00, const float_z f01, const float_z f02, const float_z f03,
              const float_z f10, const float_z f11, const float_z f12, const float_z f13,
              const float_z f20, const float_z f21, const float_z f22, const float_z f23);

    /// <summary>
    /// Constructor that receives a pointer to 12 floating point values.
    /// </summary>
    /// <remarks>
    /// Keeps the convention rows x columns, so each chunck of 3 consecutive elements
    /// corresponds to a row, where each element in the chunck is the column in the row.
    /// </remarks>
    /// <param name="arValues">[IN] A 12-length array of floating point values. If the pointer is null, the behavior  
    /// is undefined.</param>
    explicit Matrix3x4(const float_z *arValues);

    /// <summary>
    /// Constructor from three 4x32 floating point packed values. Each param contains a row of the matrix.
    /// </summary>
    /// <param name="row0">[IN] 4x32 values for row 0, columns 0 to 3 unpacked in this order.</param>
    /// <param name="row1">[IN] 4x32 values for row 1, columns 0 to 3 unpacked in this order.</param>
    /// <param name="row2">[IN] 4x32 values for row 2, columns 0 to 3 unpacked in this order.</param>
    Matrix3x4(const vf32_z row0, const vf32_z row1, const vf32_z row2);


    // PROPERTIES
    // ---------------
public:

    /// <summary>
    /// Gets a null matrix.
    /// </summary>
    /// <returns>
    /// A matrix with all components set to 0.
    /// </returns>
    static const Matrix3x4& GetNullMatrix();

    /// <summary>
    /// Stores an identity matrix.<br/>
    /// The identity matrix is a matrix whose elements are zero except the main diagonal that is composed by ones:
    ///
    /// \f$ I = \begin{bmatrix} 1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 0 \end{bmatrix}\f$
    ///
    /// </summary>
    /// <returns>
    /// An identity matrix
    /// </returns>
    static const Matrix3x4& GetIdentity();


    // METHODS
    // ---------------
public:
    
    /// <summary>
    /// Equality operator. Compares two [3x4] matrices.
    /// </summary>
    /// <param name="matrix">[IN] The matrix to compare to.</param>
    /// <returns>
    /// If matrices are equals, then it returns true. Otherwise, it returns false.
    /// </returns>
    bool operator==(const Matrix3x4 &matrix) const;

    /// <summary>
    /// Inequality operator. Compares two [3x4] matrices.
    /// </summary>
    /// <param name="matrix">[IN] The matrix to compare to.</param>
    /// <returns>
    /// If matrices are not equals, then it returns true. Otherwise, it returns false.
    /// </returns>
    bool operator!=(const Matrix3x4 &matrix) const;

    /// <summary>
    /// Multiply by scalar operator. All matrix components are multiplied by the scalar.
    /// </summary>
    /// <param name="fScalar">[IN] The scalar to multiply by.</param>
    /// <returns>
    /// The resultant matrix.
    /// </returns>
    Matrix3x4 operator*(const float_z fScalar) const;

    /// <summary>
    /// Multiply the resident matrix by a 4x3 matrix.
    /// </summary>
    /// <param name="matrix">[IN] A 4x3 matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant 3x3 matrix.
    /// </returns>
    Matrix3x3 operator*(const Matrix4x3& matrix) const;

    /// <summary>
    /// Multiply the resident matrix by a 4x4 matrix.
    /// </summary>
    /// <param name="matrix">[IN] A 4x4 matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant 3x4 matrix.
    /// </returns>
    Matrix3x4 operator*(const Matrix4x4& matrix) const;

    /// <summary>
    /// Divides resident matrix by a floating point value.
    /// </summary>
    /// <param name="fScalar">[IN] Floating point value to be divided by. If the number equals zero, the result 
    /// is undefined.</param>
    /// <returns>
    /// The resultant matrix.
    /// </returns>
    Matrix3x4 operator/(const float_z fScalar) const;

    /// <summary>
    /// Adds a 3x4 matrix to the resident matrix.
    /// </summary>
    /// <param name="matrix">[IN] The matrix to be added to.</param>
    /// <returns>
    /// The resultant matrix.
    /// </returns>
    Matrix3x4 operator+(const Matrix3x4 &matrix) const;

    /// <summary>
    /// Subtracts a Matrix3x4 to the resident matrix.
    /// </summary>
    /// <param name="matrix">[IN] The matrix to be subtracted to.</param>
    /// <returns>
    /// The resultant matrix.
    /// </returns>
    Matrix3x4 operator-(const Matrix3x4 &matrix) const;

    /// <summary>
    /// Division and assign operator. Resident matrix stores the result of the division.
    /// </summary>
    /// <param name="fScalar">[IN] The floating point value by which to divide. If the number equals zero, the result 
    /// is undefined.</param>
    /// <returns>
    /// The modified matrix.
    /// </returns>
    Matrix3x4& operator/=(const float_z fScalar);

    /// <summary>
    /// Addition and assign operator. Resident matrix stores the result of the addition.
    /// </summary>
    /// <param name="matrix">[IN] The matrix to be added to.</param>
    /// <returns>
    /// The modified matrix.
    /// </returns>
    Matrix3x4& operator+=(const Matrix3x4 &matrix);

    /// <summary>
    /// Subtraction and assign operator. Resident matrix stores the result of the subtraction.
    /// </summary>
    /// <param name="matrix">[IN] The matrix to be subtracted to.</param>
    /// <returns>
    /// The modified matrix.
    /// </returns>
    Matrix3x4& operator-=(const Matrix3x4 &matrix);

    /// <summary>
    /// Product and assign operator. Current matrix stores the result of the multiplication.
    /// </summary>
    /// <param name="fScalar">[IN] The floating point value to be multiplied by.</param>
    /// <returns>
    /// The modified matrix.
    /// </returns>
    Matrix3x4& operator*=(const float_z fScalar);

    /// <summary>
    /// Product and assign operator. Current matrix stores the result of the multiplication.
    /// </summary>
    /// <param name="matrix">[IN] A 4x4 matrix to be multiplied by.</param>
    /// <returns>
    /// The modified matrix.
    /// </returns>
    Matrix3x4& operator*=(const Matrix4x4 &matrix);

    /// <summary>
    /// Resets all matrix elements to 0.
    /// </summary>
    void ResetToZero();

    /// <summary>
    /// The transpose of a matrix m x n is a matrix n x m where each row becomes a column
    /// and each column becomes a row. Every element Aij becomes Aji. It's noted A^T.
     /// </summary>
    /// <remarks>
    /// If the matrix is a rotation matrix, then the transpose is guaranteed to be the inverse of the matrix.
    /// </remarks>
    /// <returns>
    /// The transposed matrix, which is a 4x3 matrix.
    /// </returns>
    Matrix4x3 Transpose() const;

    /// <summary>
    /// Checks if all elements of the matrix are 0 or under tolerance (absolute value).
    /// </summary>
    /// <returns>
    /// True if all elements are 0, false otherwise.
    /// </returns>
    bool IsZero() const;


    /// <summary>
    /// Resets the matrix to a identity matrix.<br/>
    /// The element \f$ A_{ij} \f$ is set to 0 if \f$ i\neq j \f$, and it's set to 1 if \f$ i=j\f$.
    /// </summary>
    void ResetToIdentity();

    /// <summary>
    /// Converts the matrix into a string.
    /// </summary>
    /// <remarks>
    /// The format of the string is:<br/>
    /// "M3x4($ij[0][0],$ij[0][1],$ij[0][2],$ij[0][3],$ij[1][0],$ij[1][1],$ij[1][2],$ij[1][3],$ij[2][0],$ij[2][1],$ij[2][2],$ij[2][3])".<br/>
    /// Where "$" means "string representation of attribute".
    /// </remarks>
    /// <returns>
    /// The string with the format specified.
    /// </returns>
    string_z ToString() const;
    

    // ATTRIBUTES
    // ---------------
public:

    /// <summary>
    /// Array that holds the matrix.
    /// </summary>
    float_z ij[3][4];
};

} // namespace z


#endif // __MATRIX3X4__

