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

#include "ZCommon/SInternalLogger.h"

#include "ZCommon/DataTypes/ArrayResult.h"
#include "ZCommon/DataTypes/StringsDefinitions.h"

#if defined(Z_COMPILER_MSVC)
    #define NOMINMAX // This definition is necessary to bypass the min and max macros defined in Windows headers
    #include "windows.h"
#elif defined(Z_COMPILER_GCC)
    #include <iostream>
#endif



namespace z
{

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |  ATTRIBUTES INITIALIZATION |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

Delegate<void (const string_z&)> SInternalLogger::Log = SInternalLogger::DefaultLogFunction;


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		    METHODS			 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

void SInternalLogger::DefaultLogFunction(const string_z &strMessage)
{
    // [TODO] Thund: In order to optimize this method, a configurable buffer could be used to avoid reserving and freeing memory on every
    //               string conversion. This may require to add an overload to StringUncode::ToBytes that receives that buffer.

    static const ETextEncoding OS_WCHAR_ENCODING = sizeof(wchar_t) == 2U ? string_z::GetLocalEncodingUTF16() : 
                                                                           string_z::GetLocalEncodingUTF32();
    
    // Depending on the compiler, a different function is used to print the error message to the console
    
    #if defined(Z_COMPILER_MSVC)
        #if Z_CONFIG_CHARACTERSET_DEFAULT == Z_CONFIG_CHARACTERSET_UNICODE
            
            ArrayResult<i8_z> arBytes = strMessage.ToBytes(OS_WCHAR_ENCODING);
            ::OutputDebugStringW(rcast_z(arBytes.Get(), wchar_t*));
                
        #elif Z_CONFIG_CHARACTERSET_DEFAULT == Z_CONFIG_CHARACTERSET_ASCII
            ::OutputDebugStringA(strMessage);
        #endif

    #elif defined(Z_COMPILER_GCC)
        #if Z_CONFIG_CHARACTERSET_DEFAULT == Z_CONFIG_CHARACTERSET_UNICODE

            ArrayResult<i8_z> arBytes = strMessage.ToBytes(OS_WCHAR_ENCODING);
            std::wcout << rcast_z(arBytes.Get(), wchar_t*);
            std::wcout.flush();
                
        #elif Z_CONFIG_CHARACTERSET_DEFAULT == Z_CONFIG_CHARACTERSET_ASCII
            std::cout << strMessage;
            std::cout.flush();
        #endif
        
    #endif
}


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |         PROPERTIES		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

void SInternalLogger::SetLogFunction(Delegate<void (const string_z&)> loggingFunction)
{
    SInternalLogger::Log = loggingFunction;
}


} // namespace z
