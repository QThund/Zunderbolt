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

#include "ZCommon/DataTypes/ETextEncoding.h"

namespace z
{

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |  ATTRIBUTES INITIALIZATION |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

const char* ETextEncoding::sm_arStrings[] = { "ASCII", 
                                               "ISO-8859-1", 
                                               "UTF-8", 
                                               "UTF-16", 
                                               "UTF-32", 
                                               "UTF-16 BE", 
                                               "UTF-16 LE", 
                                               "UTF-32 BE", 
                                               "UTF-32 LE"};

const ETextEncoding::EnumType ETextEncoding::sm_arValues[] = { ETextEncoding::E_ASCII,
                                                                 ETextEncoding::E_ISO88591,
                                                                 ETextEncoding::E_UTF8,
                                                                 ETextEncoding::E_UTF16,
                                                                 ETextEncoding::E_UTF32,
                                                                 ETextEncoding::E_UTF16BE,
                                                                 ETextEncoding::E_UTF16LE,
                                                                 ETextEncoding::E_UTF32BE,
                                                                 ETextEncoding::E_UTF32LE};


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

unsigned int ETextEncoding::_GetNumberOfValues()
{
    return sizeof(sm_arValues) / sizeof(ETextEncoding::EnumType);
}


} // namespace z