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

#ifndef __STRINGSDEFINITIONS__
#define __STRINGSDEFINITIONS__

#include "ZCommon/DataTypes/DataTypesDefinitions.h"

#if Z_CONFIG_CHARACTERSET_DEFAULT == Z_CONFIG_CHARACTERSET_ASCII
    #include <string>
#elif Z_CONFIG_CHARACTERSET_DEFAULT == Z_CONFIG_CHARACTERSET_UNICODE
    #include "CharUnicode.h"
    #include "StringUnicode.h"
#endif

namespace z
{

// --------------------------------------------------------------------------------------------------------
// Char type: Defines the char width used throughout the engine, depending on the selected character set.
// --------------------------------------------------------------------------------------------------------
#if Z_CONFIG_CHARACTERSET_DEFAULT == Z_CONFIG_CHARACTERSET_ASCII
    typedef char char_z;
#elif Z_CONFIG_CHARACTERSET_DEFAULT == Z_CONFIG_CHARACTERSET_UNICODE
    typedef CharUnicode char_z;
#else
    typedef char char_z;
#endif


// --------------------------------------------------------------------------------------------------------
// String type: Defines the string class used throughout the engine, depending on the selected character set.
// --------------------------------------------------------------------------------------------------------
#if Z_CONFIG_CHARACTERSET_DEFAULT == Z_CONFIG_CHARACTERSET_ASCII
    typedef std::string string_z;
#elif Z_CONFIG_CHARACTERSET_DEFAULT == Z_CONFIG_CHARACTERSET_UNICODE
    typedef StringUnicode string_z;
#endif


// --------------------------------------------------------------------------------------------------------
// Literals prefix: Specifies if character string literals must be prefixed with the wide-char token, depending
// on the selected character set.
// --------------------------------------------------------------------------------------------------------
#if Z_CONFIG_CHARACTERSET_DEFAULT == Z_CONFIG_CHARACTERSET_ASCII
    #define Z_L(str) str
#elif Z_CONFIG_CHARACTERSET_DEFAULT == Z_CONFIG_CHARACTERSET_UNICODE
    #define Z_L(str) str
#endif


} // namespace z


#endif // __STRINGSDEFINITIONS__
