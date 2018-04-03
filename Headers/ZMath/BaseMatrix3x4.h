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

#ifndef __BASEMATRIX3X4__
#define __BASEMATRIX3X4__

#include "ZCommon/DataTypes/DataTypesDefinitions.h"
#include "ZMath/MathModuleDefinitions.h"



namespace z
{

/// <summary>
/// Base class to represent a matrix of floating point values with 3 rows and 4 columns.
/// </summary>
class Z_LAYER_MATH_SYMBOLS BaseMatrix3x4
{
    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor. Initializes each element in the matrix to 0.
    /// </summary>
    BaseMatrix3x4();

    /// <summary>
    /// Copy constructor. Copies attributes from given matrix.
    /// </summary>
    /// <param name="matrix">[IN] The 3x4 matrix from which we want to create a copy in the resident matrix.</param>
    BaseMatrix3x4(const BaseMatrix3x4 &matrix);

    /// <summary>
    /// Constructor that receives a floating point value for all elements of the matrix.
    /// </summary>
    /// <param name="fValueAll">[IN] Floating point value which to fill the matrix with.</param>
    explicit BaseMatrix3x4(const float_z fValueAll);

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
    explicit BaseMatrix3x4(const float_z f00, const float_z f01, const float_z f02, const float_z f03,
                            const float_z f10, const float_z f11, const float_z f12, const float_z f13,
                            const float_z f20, const float_z f21, const float_z f22, const float_z f23);

    /// <summary>
    /// Constructor that receives a pointer to 12 floating point values.
    /// </summary>
    /// <remarks>
    /// Keeps the convention rows x columns, so each chunck of 4 consecutive elements
    /// corresponds to a row, where each element in the chunck is the column in the row.
    /// </remarks>
    /// <param name="arValues">[IN] A 12 length array of floating point values. If the pointer is null, the behavior  
    /// is undefined.</param>
    BaseMatrix3x4(const float_z* arValues);

    /// <summary>
    /// Constructor from four 4x32 floating point packed values. Each param contains a row of the matrix.
    /// </summary>
    /// <param name="row0">[IN] 4x32 values for row 0, columns 0 to 3, parsed in this order.</param>
    /// <param name="row1">[IN] 4x32 values for row 1, columns 0 to 3, parsed in this order.</param>
    /// <param name="row2">[IN] 4x32 values for row 2, columns 0 to 3, parsed in this order.</param>
    BaseMatrix3x4(const vf32_z row0, const vf32_z row1, const vf32_z row2);
    

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
    bool operator==(const BaseMatrix3x4 &matrix) const;

    /// <summary>
    /// Inequality operator. Compares two [3x4] matrices.
    /// </summary>
    /// <param name="matrix">[IN] The matrix to compare to.</param>
    /// <returns>
    /// If matrices are not equals, then it returns true. Otherwise, it returns false.
    /// </returns>
    bool operator!=(const BaseMatrix3x4 &matrix) const;


    // ATTRIBUTES
    // ---------------
public:

    /// <summary>
    /// Array that holds the matrix.
    /// </summary>
    float_z ij[3][4];
};

} // namespace z


#endif // __BASEMATRIX3X4__
