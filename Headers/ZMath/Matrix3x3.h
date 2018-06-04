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

#ifndef __MATRIX3X3__
#define __MATRIX3X3__

#include "ZMath/MathModuleDefinitions.h"
#include "Matrix3x4.h"
#include "ZCommon/DataTypes/StringsDefinitions.h"



namespace z
{

// FORWARD DECLARATIONS
// ---------------------
class Matrix3x4;


/// <summary>
/// This class implements the functionality of a matrix with 3 rows and 3 columns.
/// </summary>
/// <remarks>
/// A matrix is a rectangular arrangement of numbers.<br/>
/// The horizontal and vertical lines in a matrix
/// are called rows and columns, respectively. The numbers in the matrix are called its entries or its elements.<br/>
/// To specify the size of a matrix, a matrix with m rows and n columns is called an m-by-n matrix or m × n matrix,
/// while m and n are called its dimensions.<br/>
/// Every element is referenced by its position in the matrix.<br/>
/// Due to we use a row by column convention, we will always write first the row of the element and then its
/// column: the element in the i row and the j column is denoted A_ij.<br/>
/// In this case, we will work with 3x3 matrices, therefore our matrix will be:<br/>
/// <br/>
/// \f$ A = \begin{bmatrix} a_{00} & a_{01} & a_{02}\\ a_{10} & a_{11} & a_{12}\\ a_{20} & a_{21} & a_{22}\end{bmatrix}\f$
/// </remarks>
class Z_MATH_MODULE_SYMBOLS Matrix3x3
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
    friend Matrix3x3 Z_MATH_MODULE_SYMBOLS operator*(const float_z fScalar, const Matrix3x3 &matrix);


    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor. It is an empty constructor, it does not assign any value.
    /// </summary>
    Matrix3x3();

    /// <summary>
    /// Constructor from a floating point value which with fill all matrix's elements.
    /// </summary>
    /// <param name="fValueAll">[IN] The floating point value used to fill the matrix.</param>
    explicit Matrix3x3(const float_z fValueAll);

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
    Matrix3x3(const float_z f00, const float_z f01, const float_z f02,
              const float_z f10, const float_z f11, const float_z f12,
              const float_z f20, const float_z f21, const float_z f22);

    /// <summary>
    /// Constructor that receives a pointer to 9 floating point values.
    /// </summary>
    /// <remarks>
    /// Keeps the convention rows x columns, so each chunck of 3 consecutive elements
    /// corresponds to a row, where each element in the chunck is the column in the row.
    /// </remarks>
    /// <param name="arValues">[IN] A 9-length array of floating point values. If the pointer is null, the behavior  
    /// is undefined.</param>
    explicit Matrix3x3(const float_z *arValues);

    /// <summary>
    /// Constructor from three 4x32 floating point packed values. Each param contains a row of the matrix.
    /// </summary>
    /// <remarks>
    /// Last component of each pack will be ignored.
    /// </remarks>
    /// <param name="row0">[IN] 4x32 values for row 0, columns 0 to 3 unpacked in this order.</param>
    /// <param name="row1">[IN] 4x32 values for row 1, columns 0 to 3 unpacked in this order.</param>
    /// <param name="row2">[IN] 4x32 values for row 2, columns 0 to 3 unpacked in this order.</param>
    Matrix3x3(const vf32_z row0, const vf32_z row1, const vf32_z row2);


    // PROPERTIES
    // ---------------
public:

    /// <summary>
    /// Gets a null matrix.
    /// </summary>
    /// <returns>
    /// A matrix with all components set to 0.
    /// </returns>
    static const Matrix3x3& GetNullMatrix();

    /// <summary>
    /// Gets an identity matrix.
    /// </summary>
    /// <remarks>
    /// The identity matrix is a matrix whose elements are zero except the main diagonal that is composed by ones:
    ///
    /// \f$ I = \begin{bmatrix} 1 & 0 & 0 \\ 0 & 1 & 0 \\ 0 & 0 & 1 \end{bmatrix}\f$
    ///
    /// </remarks>
    /// <returns>
    /// An identity matrix
    /// </returns>
    static const Matrix3x3& GetIdentity();


    // METHODS
    // ---------------
public:
    
    /// <summary>
    /// Equality operator. Compares two [3x3] matrices.
    /// </summary>
    /// <param name="matrix">[IN] The matrix to compare to.</param>
    /// <returns>
    /// If matrices are equals, then it returns true. Otherwise, it returns false.
    /// </returns>
    bool operator==(const Matrix3x3 &matrix) const;

    /// <summary>
    /// Inequality operator. Compares two [3x3] matrices.
    /// </summary>
    /// <param name="matrix">[IN] The matrix to compare to.</param>
    /// <returns>
    /// If matrices are not equals, then it returns true. Otherwise, it returns false.
    /// </returns>
    bool operator!=(const Matrix3x3 &matrix) const;

    /// <summary>
    /// Multiply by scalar operator. All matrix components are multiplied by the scalar.
    /// </summary>
    /// <param name="fScalar">[IN] The scalar to multiply by.</param>
    /// <returns>
    /// The resultant matrix.
    /// </returns>
    Matrix3x3 operator*(const float_z fScalar) const;

    /// <summary>
    /// Multiplies a 3x3 matrix by the resident matrix.
    /// </summary>
    /// <remarks>
    /// A matrix [m x n] can only be multiplied by a matrix [n x p], being the resultant matrix m x p.<br/>
    /// So, left matrix must have same number of columns than rows have right matrix.<br/>
    /// The product is not conmutative.<br/>
    /// To perform a product of matrices, each element is calculated as
    /// ( being A(m x n), B(n x p), C (m x p) ):<br/>
    /// <br/>
    /// \f$ A \times B = C \f$<br/>
    /// <br/>
    /// \f$ C_{ij} = \sum_{r=1}^{n} A_{ir}B_{rj} \f$<br/>
    /// <br/>
    /// This product is not conmmutative.
    /// </remarks>
    /// <param name="matrix">[IN] Matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant matrix.
    /// </returns>
    Matrix3x3 operator*(const Matrix3x3 &matrix) const;

    /// <summary>
    /// Multiplies a 3x4 matrix by the current matrix.
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
    /// <param name="matrix">[IN] Matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant matrix.
    /// </returns>
    Matrix3x4 operator*(const Matrix3x4& matrix) const;

    /// <summary>
    /// Divides current matrix by a floating point value.
    /// </summary>
    /// <param name="fScalar">[IN] Floating point value to be divided by. If the number equals zero, the result 
    /// is undefined.</param>
    /// <returns>
    /// The resultant matrix.
    /// </returns>
    Matrix3x3 operator/(const float_z fScalar) const;

    /// <summary>
    /// Adds a 3x3 matrix to the current matrix.
    /// </summary>
    /// <param name="matrix">[IN] The matrix to be added to.</param>
    /// <returns>
    /// The resultant matrix.
    /// </returns>
    Matrix3x3 operator+(const Matrix3x3 &matrix) const;

    /// <summary>
    /// Subtracts a 3x3 matrix to the current matrix.
    /// </summary>
    /// <param name="matrix">[IN] The matrix to be subtracted to.</param>
    /// <returns>
    /// The resultant matrix.
    /// </returns>
    Matrix3x3 operator-(const Matrix3x3 &matrix) const;

    /// <summary>
    /// Product and assign operator. Current matrix stores the result of the multiplication.
    /// </summary>
    /// <param name="matrix">[IN] The matrix to be multiplied by.</param>
    /// <returns>
    /// The modified matrix.
    /// </returns>
    Matrix3x3& operator*=(const Matrix3x3 &matrix);

    /// <summary>
    /// Multiply by scalar operator. All matrix components are multiplied by the scalar.
    /// </summary>
    /// <param name="fScalar">[IN] The scalar to multiply by.</param>
    /// <returns>
    /// The resultant matrix.
    /// </returns>
    Matrix3x3& operator*=(const float_z fScalar);

    /// <summary>
    /// Division and assign operator. Current matrix stores the result of the division.
    /// </summary>
    /// <param name="fScalar">[IN] The floating point value by which to divide. If the number equals zero, the result 
    /// is undefined.</param>
    /// <returns>
    /// The modified matrix.
    /// </returns>
    Matrix3x3& operator/=(const float_z fScalar);

    /// <summary>
    /// Addition and assign operator. Current matrix stores the result of the addition.
    /// </summary>
    /// <param name="matrix">[IN] The matrix to be added to.</param>
    /// <returns>
    /// The modified matrix.
    /// </returns>
    Matrix3x3& operator+=(const Matrix3x3 &matrix);

    /// <summary>
    /// Subtraction and assign operator. Current matrix stores the result of the subtraction.
    /// </summary>
    /// <param name="matrix">[IN] The matrix to be subtracted to.</param>
    /// <returns>
    /// The modified matrix.
    /// </returns>
    Matrix3x3& operator-=(const Matrix3x3 &matrix);

    /// <summary>
    /// Resets all matrix elements to 0.
    /// </summary>
    void ResetToZero();

    /// <summary>
    /// Resets the matrix to a identity matrix.
    /// </summary>
    /// <remarks>
    /// The element \f$ A_{ij} \f$ is set to 0 if \f$ i\neq j \f$, and it's set to 1 if \f$ i=j\f$.
    /// </remarks>
    void ResetToIdentity();

    /// <summary>
    /// The transpose of a matrix m x n is a matrix n x m where each row becomes a column and each column becomes a row.
    /// </summary>
    /// <remarks>
    /// Every element \f$ A_{ij} \f$  becomes \f$ A_{ji}\f$.<br/>
    /// It's noted \f$ A^T \f$.<br/>
    /// If the matrix is a rotation matrix, then the transpose is guaranteed to be the inverse of the matrix.
    /// </remarks>
    /// <returns>
    /// The transposed matrix.
    /// </returns>
    Matrix3x3 Transpose() const;

    /// <summary>
    /// Checks if all elements of the matrix are 0 or under tolerance (absolute value).
    /// </summary>
    /// <returns>
    /// True if all elements are 0, false otherwise.
    /// </returns>
    bool IsZero() const;

    /// <summary>
    /// Checks if all elements of the matrix are 0 or under tolerance (absolute value) except
    /// elements where i=j, which must be 1.
    /// </summary>
    /// <returns>
    /// True if all elements are 0 except i=j which are 1, false otherwise.
    /// </returns>
    bool IsIdentity() const;

    /// <summary>
    /// Calculates the determinant of the matrix.
    /// </summary>
    /// <remarks>
    /// It's only applicable to square matrices.<br/>
    /// A determinant is a real number obtained
    /// through the addition of all possible products between elements of different
    /// row and column, where the sign of a product derives from the parity of the permutation involved.<br/>
    /// In practice, we can calculate any determinant this way:<br/>
    /// <br/>
    /// Order 1: \f$\left|A\right| = a_{00}\f$<br/>
    /// <br/>
    /// Order 2: \f$\left|A\right| = a_{00}\cdot a_{11} - a_{01}\cdot a_{10}\f$<br/>
    /// <br/>
    /// Order 3: \f$\left|A\right| = a_{00}\cdot a_{11}\cdot a_{22} + a_{01}\cdot a_{12}\cdot a_{20} + a_{02}\cdot a_{21} - (a_{02}\cdot a_{11}\cdot a_{20} + a_{00}\cdot a_{12}\cdot a_{21} + a_{01}\cdot a_{10}\cdot a_{22})\f$<br/>
    /// <br/>
    /// Any other order can be solved developing determinant by a row or a column, reducing
    /// the problem to other of one order less.<br/>
    /// To do that, we multiply each element of the row or column selected by his cofactor, defined as:<br/>
    /// <br/>
    /// \f$ C_{ij} = -1^{i+j} \cdot \left|M_{ij}\right|\f$,<br/>
    /// v
    /// where \f$ M_{ij}\f$ is the submatrix obtained by deleting from the original matrix the i row and the j column.<br/>
    /// After that, we add all products to obtain the final value of the determinant.
    /// </remarks>
    /// <returns>
    /// Floating point value which is the result of the determinant.
    /// </returns>
    float_z GetDeterminant() const;

    /// <summary>
    /// Inverts the matrix.
    /// </summary>
    /// <remarks>
    /// The inverse of a square matrix with non zero determinant is another matrix which verifies that:<br/>
    /// <br/>
    /// \f$ A\cdot A^{-1} = A^{-1}\cdot A = I\f$<br/>
    /// <br/>
    /// We can calculate the inverse of any matrix by:<br/>
    /// <br/>
    /// \f$ A^{-1} = \frac{1}{\left|A\right|}\cdot C^{T}_{ij}\f$,<br/>
    /// <br/>
    /// where \f$ C^{T}_{ij}\f$ is the matrix formed by each cofactor of each element of A, trasposed.
    /// </remarks>
    /// <returns>
    /// The inverse of the matrix.
    /// </returns>
    Matrix3x3 Invert() const;

    /// <summary>
    /// Calculates whether the matrix has inverse or not.
    /// </summary>
    /// <remarks>
    /// A matrix has inverse when its determinant doesn't equal zero.
    /// </remarks>
    /// <returns>
    /// True if the matrix has inverse, false otherwise.
    /// </returns>
    bool HasInverse() const;

    /// <summary>
    /// Converts the matrix into a string.
    /// </summary>
    /// <remarks>
    /// The format of the string is:<br/>
    /// "M3x3($ij[0][0],$ij[0][1],$ij[0][2],$ij[1][0],$ij[1][1],$ij[1][2],$ij[2][0],$ij[2][1],$ij[2][2])".<br/>
    /// Where "$" means "string representation of attribute".
    /// </remarks>
    /// <returns>The string with the format specified.</returns>
    string_z ToString() const;
    

    // ATTRIBUTES
    // ---------------
public:

    /// <summary>
    /// Array that holds the matrix.
    /// </summary>
    float_z ij[3][3];
};

} // namespace z


#endif // __MATRIX3X3__
