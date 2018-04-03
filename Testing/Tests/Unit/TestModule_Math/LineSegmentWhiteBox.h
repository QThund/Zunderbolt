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

#ifndef __LINESEGMENTWHITEBOX__
#define __LINESEGMENTWHITEBOX__

#include "ZMath/LineSegment.h"

namespace z
{
namespace Test
{

/// <summary>
/// Class intented to be used to expose protected methods of LineSegment for testing purposes.
/// </summary>
template<class VectorType>
class LineSegmentWhiteBox : public LineSegment<VectorType>
{
	// CONSTRUCTORS
	// ---------------
public:

	// Necessary for testing
	LineSegmentWhiteBox()
    {
    }

    // Necessary for testing
    LineSegmentWhiteBox(const LineSegment<VectorType>& lineSegment) : LineSegment<VectorType>(lineSegment)
    {
    }


	// METHODS
	// ---------------
public:

    // Necessary for testing
    LineSegment<VectorType>& operator=(const LineSegment<VectorType> &lineSegment)
    {
        return LineSegment<VectorType>::operator=(lineSegment);
    }

    // Exposed method
	void GetClosestPoints(const BaseLineSegment<VectorType> &segment,
						  VectorType& vClosestPtInS1ToS2, VectorType& vClosestPtInS2ToS1) const
    {
        LineSegment<VectorType>::GetClosestPoints(segment, vClosestPtInS1ToS2, vClosestPtInS2ToS1);
    }
};

} // namespace Test
} // namespace z

#endif // __LINESEGMENTWHITEBOX__
