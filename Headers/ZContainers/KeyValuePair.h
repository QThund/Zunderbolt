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

#ifndef __KEYVALUEPAIR__
#define __KEYVALUEPAIR__

#include "ZContainers/ContainersModuleDefinitions.h"


namespace z
{

/// <summary>
/// A data structure that stores a value and a key associated to that value.
/// </summary>
/// <typeparam name="KeyT">The type of the key.</typeparam>
/// <typeparam name="ValueT">The type of the value.</typeparam>
template<class KeyT, class ValueT>
class KeyValuePair
{

    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Constructor that receives both the key and the value and stores a copy of them.
    /// </summary>
    /// <param name="key">[IN] The key.</param>
    /// <param name="value">[IN] The value.</param>
    KeyValuePair(const KeyT& key, const ValueT& value) : m_key(key), 
                                                         m_value(value)
    {
    }


    // PROPERTIES
    // ---------------
public:

    /// <summary>
    /// Gets the key.
    /// </summary>
    /// <returns>
    /// A reference to the stored key.
    /// </returns>
    KeyT& GetKey()
    {
        return m_key;
    }
    
    /// <summary>
    /// Gets the key.
    /// </summary>
    /// <returns>
    /// A constant reference to the stored key.
    /// </returns>
    const KeyT& GetKey() const
    {
        return m_key;
    }

    /// <summary>
    /// Sets the key.
    /// </summary>
    /// <param name="key">[IN] The new key.</param>
    void SetKey(const KeyT& key)
    {
        m_key = key;
    }

    /// <summary>
    /// Gets the value.
    /// </summary>
    /// <returns>
    /// A reference to the stored value.
    /// </returns>
    ValueT& GetValue()
    {
        return m_value;
    }
    
    /// <summary>
    /// Gets the value.
    /// </summary>
    /// <returns>
    /// A constant reference to the stored value.
    /// </returns>
    const ValueT& GetValue() const
    {
        return m_value;
    }

    /// <summary>
    /// Sets the value.
    /// </summary>
    /// <param name="value">[IN] The new value.</param>
    void SetValue(const ValueT& value)
    {
        m_value = value;
    }


    // ATTRIBUTES
    // ---------------
private:

    /// <summary>
    /// An object that acts as a key.
    /// </summary>
    KeyT m_key;

    /// <summary>
    /// An object that acts as a value.
    /// </summary>
    ValueT m_value;

};

} // namespace z


#endif // __KEYVALUEPAIR__
