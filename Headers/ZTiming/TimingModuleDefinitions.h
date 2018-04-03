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

#ifndef __ZTIMINGMODULEDEFINITIONS__
#define __ZTIMINGMODULEDEFINITIONS__

#include "ZCommon/InternalDefinitions.h"

// --------------------------------------------------------------------------------------------------------
// Library importation / exportation switches: These definitions indicate whether the library is being compiled
// as a dynamic link library or a static library and if its symbols are being imported or exported.
// The switch is set as a preprocessor definition in the compiler options.
// --------------------------------------------------------------------------------------------------------
// Technical explanation (only on Windows, when compiling as DLLs):
// -----------------------------------------------------------------
// Why do we use a different "switch" (macro) for every library instead of using only one to export or import the symbols
// of all of them?
// The problem is that some libraries depend on others. For example, library A depends on B, so when compiling B, the symbols
// of B must be exported but, when compiling A, those symbols must be imported and A's symbols must be exported. If we use the 
// same macro for A and B, how do we import B's symbols and export A's at the same time?
// This way, A uses a preprocessor definition to tell the compiler that the symbols of B are needed to be imported, and another
// preprocessor definition to tell it that the symbols of A are to be exported; maybe, a third library, C, needs to import A's symbols.
// This could seem complex but it is not at all. Just add the macros for all the Zunderbolt libraries to be imported and then
// add a macro for exporting the symbols of the library being compiled.
// In order to simplify the process for final users, a client application or library has only to use one macro, Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT,
// to import the symbols of all the Zunderbolt libraries linked.
#ifdef Z_PREPROCESSOR_EXPORTLIB_TIMING // Specified as a preprocessor definition when compiling as a dynamic link library
    #define Z_LAYER_TIMING_SYMBOLS Z_EXPORT_SYMBOLS
    #define Z_LAYER_TIMING_EXTERN Z_EXPORT_SYMBOLS_EXTERN
    #define Z_TIMING_TEMPLATE_SPECIALIZATION_SYMBOLS
#elif defined(Z_PREPROCESSOR_IMPORTLIB_TIMING) || defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT) // Specified as a preprocessor definition when compiling the client system
    #define Z_LAYER_TIMING_SYMBOLS Z_IMPORT_SYMBOLS
    #define Z_LAYER_TIMING_EXTERN Z_IMPORT_SYMBOLS_EXTERN
    #define Z_TIMING_TEMPLATE_SPECIALIZATION_SYMBOLS
#else // Static library
    #define Z_LAYER_TIMING_SYMBOLS
    #define Z_LAYER_TIMING_EXTERN
#endif


#endif // __ZTIMINGMODULEDEFINITIONS__
