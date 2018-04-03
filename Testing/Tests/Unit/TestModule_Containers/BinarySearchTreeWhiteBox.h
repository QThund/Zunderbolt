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

#ifndef __BINARYSEARCHTREEWHITEBOX__
#define __BINARYSEARCHTREEWHITEBOX__

#include "ZContainers/BinarySearchTree.h"
#include "ZMemory/PoolAllocator.h"


namespace z
{
namespace Test
{

/// <summary>
/// Class intended to be used to expose protected methods of BinarySearchTree for testing purposes.
/// </summary>
template <class T, class AllocatorT = PoolAllocator, class ComparatorT = SComparatorDefault<T> >
class BinarySearchTreeWhiteBox : public BinarySearchTree<T, AllocatorT, ComparatorT>
{
public:

    using typename BinarySearchTree<T, AllocatorT, ComparatorT>::BinaryNode;


	// CONSTRUCTORS
	// ---------------
public:

    BinarySearchTreeWhiteBox()
    {
    }

    BinarySearchTreeWhiteBox(const puint_z uInitialCapacity) : BinarySearchTree<T, AllocatorT, ComparatorT>(uInitialCapacity)
    {
    }



	// PROPERTIES
	// ---------------
public:

    puint_z GetRootPosition() const
    {
        return BinarySearchTree<T, AllocatorT>::m_uRoot;
    }

    const AllocatorT& GetNodeAllocator() const
    {
        return BinarySearchTree<T, AllocatorT>::m_nodeAllocator;
    }

    static puint_z GetEndPositionForward()
    {
        return BinarySearchTree<T, AllocatorT>::END_POSITION_FORWARD;
    }

};

} // namespace Test
} // namespace z

#endif // __BINARYSEARCHTREEWHITEBOX__
