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

#ifndef __BASICARRAY__
#define __BASICARRAY__

#include "ZCommon/CommonModuleDefinitions.h"
#include "ZCommon/DataTypes/CrossPlatformBasicTypes.h"


namespace z
{
   
/// <summary>
/// A wrapper for C-style arrays that stores both, the array and the number of elements in it.
/// </summary>
/// <remarks>
/// Note that copying instances of this class does not imply making a copy of the array, only the pointer is copied.
/// </remarks>
/// <typeparam name="T">The type of the elements in the array.</typeparam>
template<class T>
class ArrayBasic
{

    // CONSTRUCTORS
    // ---------------
public:
    
    /// <summary>
    /// Constructor that receives the array and the number of elements in it.
    /// </summary>
    /// <param name="pArray">[IN] The array to be wrapped.</param>
    /// <param name="uCount">[IN] The number of elements in the array.</param>
    ArrayBasic(T* pArray, const puint_z uCount) : m_pArray(pArray),
                                                          m_uCount(uCount)
    {
    }


    // METHODS
    // ---------------
public:
    
    /// <summary>
    /// Array subscript operator that returns an element of the array from a given position.
    /// </summary>
    /// <remarks>
    /// It is just a wrapper method for the operator of the wrapped array. It has been included just to make potential refactoring tasks easier.
    /// </remarks>
    /// <param name="uIndex">[IN] The position index of the element, starting at zero. It must be lower than the number of elements in the array.</param>
    /// <returns>
    /// A reference to the retrieved element.
    /// </returns>
    T& operator[](const puint_z uIndex) const
    {
        return m_pArray[uIndex];
    }


    // PROPERTIES
    // ---------------
public:
    
    /// <summary>
    /// Gets the wrapped array.
    /// </summary>
    /// <returns>
    /// The C-style array contained in the wrapper.
    /// </returns>
    T* Get() const
    {
        return m_pArray;
    }
    
    /// <summary>
    /// Gets the number of elements in the array.
    /// </summary>
    /// <returns>
    /// The number of elements in the array.
    /// </returns>
    puint_z GetCount() const
    {
        return m_uCount;
    }
    
    /// <summary>
    /// Gets the size of the wrapped array, in bytes.
    /// </summary>
    /// <returns>
    /// The size of the array.
    /// </returns>
    puint_z GetSize() const
    {
        return m_uCount * sizeof(T);
    }

    
    // ATTRIBUTES
    // ---------------
protected:
    
    /// <summary>
    /// The wrapped array.
    /// </summary>
    T* m_pArray;
    
    /// <summary>
    /// The number of elements in the array.
    /// </summary>
    puint_z m_uCount;

};

} // namespace z

#endif // __BASICARRAY__
