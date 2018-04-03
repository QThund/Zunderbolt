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

#ifndef __BASEMATRIX2X2__
#define __BASEMATRIX2X2__

#include "ZCommon/DataTypes/DataTypesDefinitions.h"
#include "ZMath/MathModuleDefinitions.h"



namespace z
{

/// <summary>
/// Base class to represent a matrix of floating point values of 2 rows and 2 columns.
/// </summary>
class Z_LAYER_MATH_SYMBOLS BaseMatrix2x2
{
    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor. Initializes each element in the matrix to 0.
    /// </summary>
    BaseMatrix2x2();

    /// <summary>
    /// Copy constructor. Copies attributes from given matrix.
    /// </summary>
    /// <param name="matrix">[IN] The 2x2 matrix from which we want to create a copy in the resident matrix.</param>
    BaseMatrix2x2(const BaseMatrix2x2 &matrix);

    /// <summary>
    /// Constructor that receives a floating point value for all elements of the matrix.
    /// </summary>
    /// <param name="fValueAll">[IN] Floating point value which to fill the matrix with.</param>
    explicit BaseMatrix2x2(const float_z fValueAll);

    /// <summary>
    /// Constructor from a floating point value for each element of the matrix.
    /// </summary>
    /// <param name="f00">[IN] Floating point value for element of row 0, column 0.</param>
    /// <param name="f01">[IN] Floating point value for element of row 0, column 1.</param>
    /// <param name="f10">[IN] Floating point value for element of row 1, column 0.</param>
    /// <param name="f11">[IN] Floating point value for element of row 1, column 1.</param>
    BaseMatrix2x2(const float_z f00, const float_z f01, const float_z f10, const float_z f11);

    /// <summary>
    /// Constructor that receives a pointer to 4 floating point values.
    /// </summary>
    /// <remarks>
    /// Keeps the convention rows x columns, so each chunck of 2 consecutive elements
    /// corresponds to a row, where each element in the chunck is the column in the row.
    /// </remarks>
    /// <param name="arValues">[IN] A 4 length array of floating point values. If the pointer is null, the behavior  
    /// is undefined.</param>
    BaseMatrix2x2(const float_z* arValues);

    /// <summary>
    /// Constructor from one 4x32 floating point packed values. Each value contains an element of the matrix.<br/>
    /// Each pack element is unpacked following the row x column convention.
    /// </summary>
    /// <param name="value">[IN] 4x32 values for the matrix.</param>
    BaseMatrix2x2(const vf32_z value);


    // METHODS
    // ---------------
public:

    /// <summary>
    /// Equality operator. Compares two [2x2] matrices.
    /// </summary>
    /// <param name="matrix">[IN] The matrix to compare to.</param>
    /// <returns>
    /// If matrices are equals, then it returns true. Otherwise, it returns false.
    /// </returns>
    bool operator==(const BaseMatrix2x2 &matrix) const;

    /// <summary>
    /// Inequality operator. Compares two [2x2] matrices.
    /// </summary>
    /// <param name="matrix">[IN] The matrix to compare to.</param>
    /// <returns>
    /// If matrices are not equals, then it returns true. Otherwise, it returns false.
    /// </returns>
    bool operator!=(const BaseMatrix2x2 &matrix) const;


    // ATTRIBUTES
    // ---------------
public:

    /// <summary>
    /// Array that holds the matrix.
    /// </summary>
    float_z ij[2][2];
};

} // namespace z


#endif // __BASEMATRIX2X2__
