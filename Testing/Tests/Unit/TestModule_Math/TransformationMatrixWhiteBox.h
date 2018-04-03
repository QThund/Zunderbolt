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

#ifndef __ZTRANSFORMATIONMATRIXWHITEBOX__
#define __ZTRANSFORMATIONMATRIXWHITEBOX__

#include "ZMath/TransformationMatrix.h"
#include "ZMath/TranslationMatrix.h"
#include "ZMath/RotationMatrix3x3.h"
#include "ZMath/ScalingMatrix3x3.h"

namespace z
{
namespace Test
{

/// <summary>
/// Class intented to be used to expose protected methods of TransformationMatrix for testing purposes.
/// </summary>
template<class MatrixType>
class TransformationMatrixWhiteBox : public TransformationMatrix<MatrixType>
{
	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
	TransformationMatrixWhiteBox() : TransformationMatrix<MatrixType>()
    {
    }

    // Necessary for testing
    TransformationMatrixWhiteBox(const TransformationMatrix<MatrixType>& matrix) : TransformationMatrix<MatrixType>(matrix)
    {
    }


	// METHODS
	// ---------------
public:

    // Necessary for testing
    MatrixType& operator=(const TransformationMatrix<MatrixType> &matrix)
    {
        return TransformationMatrix<MatrixType>::operator=(matrix);
    }

    // Exposed methods
	RotationMatrix3x3 ToRotationMatrix3x3() const
    {
        return TransformationMatrix<MatrixType>::ToRotationMatrix3x3();
    }

    void Initialize(const float_z &fTranslationX, const float_z &fTranslationY, const float_z &fTranslationZ,
                    const float_z &fRotationX, const float_z &fRotationY, const float_z &fRotationZ, const float_z &fRotationW,
                    const float_z &fScaleX, const float_z &fScaleY, const float_z &fScaleZ)
    {
        TransformationMatrix<MatrixType>::Initialize(fTranslationX, fTranslationY, fTranslationZ,
                                                      fRotationX, fRotationY, fRotationZ, fRotationW,
                                                      fScaleX, fScaleY, fScaleZ);
    }

};

} // namespace Test
} // namespace z

#endif // __ZTRANSFORMATIONMATRIXWHITEBOX__
