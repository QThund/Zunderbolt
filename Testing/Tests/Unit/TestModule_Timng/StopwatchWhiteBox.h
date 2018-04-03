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

#ifndef __STOPWATCHWHITEBOX__
#define __STOPWATCHWHITEBOX__

#include "ZTiming/Stopwatch.h"


namespace z
{
namespace Test
{

/// <summary>
/// Exposes the protected methods of the Stopwatch to perform white-box tests.
/// </summary>
class StopwatchWhiteBox : public Stopwatch
{

    // METHODS
	// ---------------
public:

    // Method to obtain the reference instant
    u64_z GetReferenceInstantForTest()
    {
        return m_uReferenceTime;
    }

};

} // namespace Test
} // namespace z


#endif // __STOPWATCHWHITEBOX__
