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

#ifndef __REFERENCEWRAPPER__
#define __REFERENCEWRAPPER__

#include "ZCommon/CommonModuleDefinitions.h"


namespace z
{

/// <summary>
/// A wrapper for storing a reference.
/// </summary>
/// <typeparam name="T">The type of the reference.</typeparam>
template<class T>
class ReferenceWrapper
{

    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Constructor that receives the instance whose reference will be stored.
    /// </summary>
    /// <param name="value">[IN] The instance whose reference will be stored.</param>
    explicit ReferenceWrapper(T& value) : m_value(value)
    {
    }

    
    // METHODS
    // ---------------
public:

    /// <summary>
    /// Casting operator that gets the stored reference.
    /// </summary>
    /// <returns>
    /// The stored reference.
    /// </returns>
    operator T&() const
    {
        return m_value;
    }
    
    /// <summary>
    /// Gets the stored reference.
    /// </summary>
    /// <returns>
    /// The stored reference.
    /// </returns>
    T& Get() const
    {
        return m_value;
    }
    

    // ATTRIBUTES
    // ---------------
private:

    /// <returns>
    /// The wrapped reference.
    /// </returns>
    T& m_value;

};

} // namespace z

#endif // __REFERENCEWRAPPER__
