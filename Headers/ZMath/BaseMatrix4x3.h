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

#ifndef __BASEMATRIX4X3__
#define __BASEMATRIX4X3__

#include "ZCommon/DataTypes/DataTypesDefinitions.h"
#include "ZMath/MathModuleDefinitions.h"



namespace z
{

/// <summary>
/// Base class to represent a matrix of floating point values with 4 rows and 3 columns.
/// </summary>
class Z_LAYER_MATH_SYMBOLS BaseMatrix4x3
{
    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor. Initializes each element in the matrix to 0.
    /// </summary>
    BaseMatrix4x3();

    /// <summary>
    /// Copy constructor. Copies attributes from given matrix.
    /// </summary>
    /// <param name="matrix">[IN] The 4x3 matrix from which we want to create a copy in the resident matrix.</param>
    BaseMatrix4x3(const BaseMatrix4x3 &matrix);

    /// <summary>
    /// Constructor that receives a floating point value for all elements of the matrix.
    /// </summary>
    /// <param name="fValueAll">[IN] Floating point value which to fill the matrix with.</param>
    explicit BaseMatrix4x3(const float_z fValueAll);

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
    BaseMatrix4x3(const float_z f00, const float_z f01, const float_z f02,
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
    /// <param name="arValues">[IN] A 12 length array of floating point values. If the pointer is null, the behavior  
    /// is undefined.</param>
    BaseMatrix4x3(const float_z* arValues);

    /// <summary>
    /// Constructor from four 4x32 floating point packed values. Each param contains a row of the matrix.
    /// </summary>
    /// <remarks>
    /// Last component for each 4x32 value will be ignored.
    /// </remarks>
    /// <param name="row0">[IN] 4x32 values for row 0, columns 0 to 2, parsed in this order.</param>
    /// <param name="row1">[IN] 4x32 values for row 1, columns 0 to 2, parsed in this order.</param>
    /// <param name="row2">[IN] 4x32 values for row 2, columns 0 to 2, parsed in this order.</param>
    /// <param name="row3">[IN] 4x32 values for row 3, columns 0 to 2, parsed in this order.</param>
    BaseMatrix4x3(const vf32_z row0, const vf32_z row1, const vf32_z row2, const vf32_z &row3);


    // METHODS
    // ---------------
public:

    /// <summary>
    /// Equality operator. Compares two [4x3] matrices.
    /// </summary>
    /// <param name="matrix">[IN] The matrix to compare to.</param>
    /// <returns>
    /// If matrices are equals, then it returns true. Otherwise, it returns false.
    /// </returns>
    bool operator==(const BaseMatrix4x3 &matrix) const;
    
    /// <summary>
    /// Inequality operator. Compares two [4x3] matrices.
    /// </summary>
    /// <param name="matrix">[IN] The matrix to compare to.</param>
    /// <returns>
    /// If matrices are not equals, then it returns true. Otherwise, it returns false.
    /// </returns>
    bool operator!=(const BaseMatrix4x3 &matrix) const;


    // ATTRIBUTES
    // ---------------
public:

    /// <summary>
    /// Array that holds the matrix.
    /// </summary>
    float_z ij[4][3];
};

} // namespace z


#endif // __BASEMATRIX4X3__
