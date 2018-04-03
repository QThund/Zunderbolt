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

// This file was created to provide a definition for Boost's throw_exception function, which is necessary
// when exceptions are disabled.
// 
// See http://www.boost.org/doc/libs/1_38_0/libs/exception/doc/throw_exception.html

// IMPORTANT: This file is shared among several projects.

#include <exception>
#include "ZCommon/Assertions.h"
#include "ZCommon/DataTypes/StringsDefinitions.h"

namespace boost
{

    void throw_exception( std::exception const & e )
    {
        Z_ASSERT_ERROR(false, "An unexpected error occurred inside Boost libraries.");
        std::terminate();
    }

}