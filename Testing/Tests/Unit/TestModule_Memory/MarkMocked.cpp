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

#include "StackAllocatorWhiteBox.h"


namespace z
{
namespace Test
{


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |  ATTRIBUTES INITIALIZATION |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

const puint_z StackAllocatorWhiteBox::MarkMocked::MARKMOCKED_OFFSET_VALUE = 0X100;


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		    METHODS			 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

void StackAllocatorWhiteBox::MarkMocked::SabotageMarkToNull()
{
   this->m_pMemoryAddress = null_z;
}

void StackAllocatorWhiteBox::MarkMocked::SabotageMarkToLesserMemoryAddress()
{
    puint_z uAux  = rcast_z(m_pMemoryAddress, puint_z);
    uAux                -= MARKMOCKED_OFFSET_VALUE;
    m_pMemoryAddress     = rcast_z(uAux, void*);
}

void StackAllocatorWhiteBox::MarkMocked::SabotageMarkToGreaterMemoryAddress()
{
    puint_z uAux  = rcast_z(m_pMemoryAddress, puint_z);
    uAux                += MARKMOCKED_OFFSET_VALUE;
    m_pMemoryAddress     = rcast_z(uAux, void*);
}


} // namespace Test
} // namespace z
