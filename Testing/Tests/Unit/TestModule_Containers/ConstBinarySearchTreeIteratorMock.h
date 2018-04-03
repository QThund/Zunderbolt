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

#ifndef __CONSTBINARYSEARCHTREEITERATORMOCK__
#define __CONSTBINARYSEARCHTREEITERATORMOCK__

#include "ZContainers/BinarySearchTree.h"

namespace z
{
namespace Test
{

/// <summary>
/// Fake iterator used for testing purposes (to create invalid iterators, for example).
/// </summary>
/// <typeparam name="T">The type of the tree elements.</typeparam>
template <class T>
class ConstBinarySearchTreeIteratorMock : public BinarySearchTree<T>::ConstBinarySearchTreeIterator
{
    using BinarySearchTree<T>::ConstBinarySearchTreeIterator::m_uPosition;

public:

    // Constructor bypass
    ConstBinarySearchTreeIteratorMock(const BinarySearchTree<T>* pTree, const puint_z uPosition, const ETreeTraversalOrder &eTraversalOrder) : BinarySearchTree<T>::ConstBinarySearchTreeIterator(pTree, uPosition, eTraversalOrder)
    {
    }

    /// <summary>
    /// Sets the position to which the iterator points.
    /// </summary>
    /// <param name="uPosition">[IN] The new position. It can be invalid.</param>
    void SetPosition(const puint_z uPosition)
    {
        m_uPosition = uPosition;
    }
};

} // namespace Test
} // namespace z

#endif // __CONSTBINARYSEARCHTREEITERATORMOCK__
