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

#ifndef __TYPEWITHTOSTRING__
#define __TYPEWITHTOSTRING__

#include "ZDiagnosis/DiagnosisModuleDefinitions.h"


namespace z
{

/// <summary>
/// Constructor overload selector used to call a constructor that expects an argument to provide a method called ToString, 
/// which receives no parameters and returns a string.<br/>
/// Overload selectors are intended to be instanced in the function call and passed as argument so the compiler calls the desired
/// overload based on the type of the parameters.
/// </summary>
class Z_LAYER_DIAGNOSIS_SYMBOLS TypeWithToString
{
};

} // namespace z


#endif // __TYPEWITHTOSTRING__
