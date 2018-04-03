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

#ifndef __ALIGNMENTMOCKED__
#define __ALIGNMENTMOCKED__


#include "ZMemory/Alignment.h"
#include "ZCommon/CommonModuleDefinitions.h"
#include "ZMemory/MemoryModuleDefinitions.h"


namespace z
{
namespace Test
{


/// <summary>
/// [DOC]
/// </summary>
class AlignmentMocked : public Alignment
{
	// CONSTRUCTORS
	// ---------------
public:

	explicit AlignmentMocked(const puint_z &uAlignment) : Alignment (uAlignment) {}


	// METHODS
	// ---------------
public:
    // TO-DO: [DOC]
    void SabotageAlignmentValue()
    {
        do
        {
            ++m_uAlignment;
        } while ( !(0 == m_uAlignment) && !(m_uAlignment & (m_uAlignment - 1)) );
    }
};


} // namespace Test
} // namespace z

#endif // __ALIGNMENTMOCKED__
