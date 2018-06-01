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

#ifndef __MATRIX4X3__
#define __MATRIX4X3__

#include "BaseMatrix4x3.h"
#include "BaseMatrix3x3.h"
#include "BaseMatrix3x4.h"
#include "BaseMatrix4x4.h"
#include "ZCommon/DataTypes/StringsDefinitions.h"



namespace z
{

/// <summary>
/// This class implements the functionality of a matrix with 4 rows and 3 columns.
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
/// \f$ A = \begin{bmatrix} a_{00} & a_{01} & a_{02}\\ a_{10} & a_{11} & a_{12}\\ a_{20} & a_{21} & a_{22}\\ a_{30} & a_{31} & a_{32}\end{bmatrix}\f$<br/>
/// <br/>
/// This allows us to compute the special case of transformatios, where 4th column has the values (0, 0, 0, 1), and
/// we can ignore it in some cases.
/// </remarks>
class Z_MATH_MODULE_SYMBOLS Matrix4x3 : public BaseMatrix4x3
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
    friend Matrix4x3 Z_MATH_MODULE_SYMBOLS operator*(const float_z fScalar, const Matrix4x3 &matrix);


     // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor.
    /// </summary>
    Matrix4x3();

    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="matrix">[IN] The 4x3 matrix from which we want to create a copy in the resident matrix.</param>
    Matrix4x3(const Matrix4x3 &matrix);

    /// <summary>
    /// Base type constructor.
    /// </summary>
    /// <param name="matrix">[IN] The 4x3 matrix in which we want the resident matrix to be based.</param>
    Matrix4x3(const BaseMatrix4x3 &matrix);

    /// <summary>
    /// Constructor from a floating point value which with fill all matrix's elements.
    /// </summary>
    /// <param name="fValueAll">[IN] The floating point value used to fill the matrix.</param>
    explicit Matrix4x3(const float_z fValueAll);

    /// <summary>
    /// Constructor from a floating point value for each element of the matrix.
    /// </summary>
    /// <param name="f00">[IN] Floating point value for element of row 0, column 0.</param>
    /// <param name="f01">[IN] Floating point value for element of row 0, column 1.</param>
    /// <param name="f02">[IN] Floating point value for element of row 0, column 2.</param>
    /// <param name="f10">[IN] Floating point value for element of row 1, column 0.</param>
    /// <param name="f11">[IN] Floating point value for element of row 1, column 1.</param>
    /// <param name="f12">[IN] Floating point value for element of row 1, column 2.</param>
    /// <param name="f20">[IN] Floating point value for element of row 2, column 0.</param>
    /// <param name="f21">[IN] Floating point value for element of row 2, column 1.</param>
    /// <param name="f22">[IN] Floating point value for element of row 2, column 2.</param>
    /// <param name="f30">[IN] Floating point value for element of row 3, column 0.</param>
    /// <param name="f31">[IN] Floating point value for element of row 3, column 1.</param>
    /// <param name="f32">[IN] Floating point value for element of row 3, column 2.</param>
    Matrix4x3(const float_z f00, const float_z f01, const float_z f02,
               const float_z f10, const float_z f11, const float_z f12,
               const float_z f20, const float_z f21, const float_z f22,
               const float_z f30, const float_z f31, const float_z f32);

    /// <summary>
    /// Constructor that receives a pointer to 12 floating point values.
    /// </summary>
    /// <remarks>
    /// Keeps the convention rows x columns, so each chunck of 3 consecutive elements
    /// corresponds to a row, where each element in the chunck is the column in the row.
    /// </remarks>
    /// <param name="arValues">[IN] A 12-length array of floating point values. If the pointer is null, the behavior  
    /// is undefined.</param>
    explicit Matrix4x3(const float_z* arValues);

    /// <summary>
    /// Constructor from four 4x32 floating point packed values. Each param contains a row of the matrix.
    /// Last value of each 4x32 pack is ignored.
    /// </summary>
    /// <param name="row0">[IN] 4x32 values for row 0, columns 0 to 2 unpacked in this order.</param>
    /// <param name="row1">[IN] 4x32 values for row 1, columns 0 to 2 unpacked in this order.</param>
    /// <param name="row2">[IN] 4x32 values for row 2, columns 0 to 2 unpacked in this order.</param>
    /// <param name="row3">[IN] 4x32 values for row 3, columns 0 to 2 unpacked in this order.</param>
    Matrix4x3(const vf32_z row0, const vf32_z row1, const vf32_z row2, const vf32_z &row3);


    // PROPERTIES
    // ---------------
public:

    /// <summary>
    /// Gets a null matrix.
    /// </summary>
    /// <returns>
    /// A matrix with all components set to 0.
    /// </returns>
    static const Matrix4x3& GetNullMatrix();

    /// <summary>
    /// Gets a pseudo-identity matrix.
    /// </summary>
    /// <remarks>
    /// The identity matrix is a matrix whose elements are zero except the main diagonal that is composed by ones:<br/>
    /// <br/>
    /// \f$ I = \begin{bmatrix} 1 & 0 & 0 \\ 0 & 1 & 0 \\ 0 & 0 & 1 \\ 0 & 0 & 0 \end{bmatrix}\f$<br/>
    /// <br/>
    /// In this case, as it's not a square matrix, it's not a real identity matrix.<br/>
    /// This constant exists due to compatibility reasons only, as an exception.
    /// </remarks>
    /// <returns>
    /// An identity matrix
    /// </returns>
    static const Matrix4x3& GetIdentity();


    // METHODS
    // ---------------
public:

    /// <summary>
    /// Multiply by scalar operator. All matrix components are multiplied by the scalar.
    /// </summary>
    /// <param name="fScalar">[IN] The scalar to multiply by.</param>
    /// <returns>
    /// The resultant matrix.
    /// </returns>
    Matrix4x3 operator*(const float_z fScalar) const;

    /// <summary>
    /// Multiply resident matrix by a square 3x3 matrix.
    /// </summary>
    /// <remarks>
    /// A matrix [m x n] can only be multiplied by a matrix [n x p], being the resultant matrix m x p.<br/>
    /// So, left matrix must have same number of columns than rows have right matrix.<br/>
    /// The product is not conmutative.<br/>
    /// To perform a product of matrices, each element is calculated as ( being A(m x n), B(n x p), C (m x p) ):<br/>
    /// <br/>
    /// \f$ A\times B = C \f$<br/>
    /// <br/>
    /// \f$ C_{ij} = \sum_{r=1}^{n} A_{ir}B_{rj} \f$<br/>
    /// <br/>
    /// This product is not conmmutative.
    /// </remarks>
    /// <param name="matrix">[IN] The square 3x3 matrix to multiply by.</param>
    /// <returns>
    /// The resultant 4x3 matrix.
    /// </returns>
    Matrix4x3 operator*(const BaseMatrix3x3 &matrix) const;

    /// <summary>
    /// Multiply resident matrix by a non-square 3x4 matrix.
    /// </summary>
    /// <remarks>
    /// A matrix [m x n] can only be multiplied by a matrix [n x p], being the resultant matrix m x p.<br/>
    /// So, left matrix must have same number of columns than rows have right matrix.<br/>
    /// The product is not conmutative.<br/>
    /// To perform a product of matrices, each element is calculated as ( being A(m x n), B(n x p), C (m x p) ):<br/>
    /// <br/>
    /// \f$ A x B = C \f$<br/>
    /// <br/>
    /// \f$ C_{ij} = \sum_{r=1}^{n} A_{ir}B_{rj} \f$<br/>
    /// <br/>
    /// This product is not conmmutative.
    /// </remarks>
    /// <param name="matrix">[IN] The 3x4 matrix to multiply by.</param>
    /// <returns>
    /// The resultant square 4x4 matrix.
    /// </returns>
    BaseMatrix4x4 operator*(const BaseMatrix3x4 &matrix) const;

    /// <summary>
    /// Multiply by scalar operator. All matrix components are multiplied by the scalar.
    /// </summary>
    /// <param name="fScalar">[IN] The scalar to multiply by.</param>
    /// <returns>
    /// The resultant matrix.
    /// </returns>
    Matrix4x3& operator*=(const float_z fScalar);

    /// <summary>
    /// Multiply resident matrix by a square 3x3 matrix, being the resultant
    /// matrix stored as well in the whole resident one.
    /// </summary>
    /// <remarks>
    /// A matrix [m x n] can only be multiplied by a matrix [n x p], being the resultant matrix m x p.<br/>
    /// So, left matrix must have same number of columns than rows have right matrix.<br/>
    /// The product is not conmutative.<br/>
    /// To perform a product of matrices, each element is calculated as ( being A(m x n), B(n x p), C (m x p) ):<br/>
    /// <br/>
    /// \f$ A x B = C \f$<br/>
    /// <br/>
    /// \f$ C_{ij} = \sum_{r=1}^{n} A_{ir}B_{rj} \f$<br/>
    /// <br/>
    /// This product is not conmmutative.
    /// </remarks>
    /// <param name="matrix">[IN] The square 3x3 matrix to multiply by.</param>
    /// <returns>
    /// The modified matrix.
    /// </returns>
    Matrix4x3& operator*=(const BaseMatrix3x3 &matrix);

    /// <summary>
    /// Divides resident matrix by a floating point value.
    /// </summary>
    /// <param name="fScalar">[IN] Floating point value to be divided by. If the number equals zero, the result 
    /// is undefined.</param>
    /// <returns>
    /// The resultant matrix.
    /// </returns>
    Matrix4x3 operator/(const float_z fScalar) const;

    /// <summary>
    /// Adds a 4x3 matrix to the resident matrix.
    /// </summary>
    /// <param name="matrix">[IN] The matrix to be added to.</param>
    /// <returns>
    /// The resultant matrix.
    /// </returns>
    Matrix4x3 operator+(const BaseMatrix4x3 &matrix) const;

    /// <summary>
    /// Subtracts a 4x3 matrix to the resident matrix.
    /// </summary>
    /// <param name="matrix">[IN] The matrix to be subtracted to.</param>
    /// <returns>
    /// The resultant matrix.
    /// </returns>
    Matrix4x3 operator-(const BaseMatrix4x3 &matrix) const;

    /// <summary>
    /// Division and assign operator. Resident matrix stores the result of the division.
    /// </summary>
    /// <param name="fScalar">[IN] The floating point value by which to divide. If the number equals zero, the result 
    /// is undefined.</param>
    /// <returns>
    /// The modified matrix.
    /// </returns>
    Matrix4x3& operator/=(const float_z fScalar);

    /// <summary>
    /// Addition and assign operator. Resident matrix stores the result of the addition.
    /// </summary>
    /// <param name="matrix">[IN] The matrix to be added to.</param>
    /// <returns>
    /// The modified matrix.
    /// </returns>
    Matrix4x3& operator+=(const BaseMatrix4x3 &matrix);

    /// <summary>
    /// Subtraction and assign operator. Resident matrix stores the result of the subtraction.
    /// </summary>
    /// <param name="matrix">[IN] The matrix to be subtracted to.</param>
    /// <returns>
    /// The modified matrix.
    /// </returns>
    Matrix4x3& operator-=(const BaseMatrix4x3 &matrix);

    /// <summary>
    /// Assignation operator. Assigns the provided matrix to the resident matrix.
    /// </summary>
    /// <param name="matrix">[IN] The matrix to be assigned.</param>
    /// <returns>
    /// A reference to the modified matrix.
    /// </returns>
    Matrix4x3& operator=(const BaseMatrix4x3 &matrix);

    /// <summary>
    /// Resets all matrix elements to 0.
    /// </summary>
    void ResetToZero();

    /// <summary>
    /// Resets main diagonal elements to 1 and any other element to 0.<br/>
    /// Since element [3][3] doesn't exists, it can not be initialized.
    /// </summary>
    void ResetToIdentity();

    /// <summary>
    /// The transpose of a matrix m x n is a matrix n x m where each row becomes a column
    /// and each column becomes a row.<br/>
    /// </summary>
    /// <remarks>
    /// Every element Aij becomes Aji. It's noted A^T.<br/>
    /// If the matrix is a rotation matrix, then the transpose is guaranteed to be the inverse of the matrix.
    /// </remarks>
    /// <returns>
    /// The transposed matrix, which is a 3x4 matrix.
    /// </returns>
    BaseMatrix3x4 Transpose() const;

    /// <summary>
    /// Checks if all elements of the matrix are 0 or under tolerance (absolute value).
    /// </summary>
    /// <returns>
    /// True if all elements are 0, false otherwise.
    /// </returns>
    bool IsZero() const;

    /// <summary>
    /// Converts matrix into a string.
    /// </summary>
    /// <remarks>
    /// The format of the string is:<br/>
    /// "M4x3($ij[0][0],$ij[0][1],$ij[0][2],$ij[1][0],$ij[1][1],$ij[1][2],$ij[2][0],$ij[2][1],$ij[2][2],$ij[3][0],$ij[3][1],$ij[3][2])".<br/>
    /// Where "$" means "string representation of attribute".
    /// </remarks>
    /// <returns>
    /// The string with the format specified.
    /// </returns>
    string_z ToString() const;
};

} // namespace z


#endif // __MATRIX4X3__

