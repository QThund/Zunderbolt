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

#ifndef __EXTERNALDEFINITIONS__
#define __EXTERNALDEFINITIONS__

#include "ZCommon/Configuration.h"

// --------------------------------------------------------------------------------------------------------
// Compilation configuration: Defines if the current compilation configuration is set for debugging or
// releasing.
// --------------------------------------------------------------------------------------------------------
#ifndef NDEBUG
    #define Z_DEBUG    // Debug compilation
#else
    #define Z_RELEASE  // Release compilation
#endif

// --------------------------------------------------------------------------------------------------------
// Operative system: Defines on which ooperative system is running the compiler.
// --------------------------------------------------------------------------------------------------------
#if defined(_WIN32) && !defined(_WIN64)
    #define Z_OS_WINDOWS 32    // Windows 32 bits
    #define Z_ARCH_32BITS 32
#elif defined(_WIN64)
    #define Z_OS_WINDOWS 64    // Windows 64 bits
    #define Z_ARCH_64BITS 64
#elif defined(__i386) && defined(__linux__)
    #define Z_OS_LINUX 32      // Linux 32 bits
    #define Z_ARCH_32BITS 32
#elif defined(LINUX64) && defined(__linux__)
    #define Z_OS_LINUX 64      // Linux 64 bits
    #define Z_ARCH_64BITS 64
#elif defined(__APPLE__) && !defined(__LP64__)
    #define Z_OS_MAC 32        // Mac 32 bits
    #define Z_ARCH_32BITS 32
#elif defined(__APPLE__) && defined(__LP64__)
    #define Z_OS_MAC 64        // Mac 64 bits
    #define Z_ARCH_64BITS 64
#else
    #error Unknown operative system.
#endif

// --------------------------------------------------------------------------------------------------------
// Compiler: Defines which compiler is compiling the code.
// --------------------------------------------------------------------------------------------------------
#ifdef _MSC_VER
    #if _MSC_VER >= 1700
        #define Z_COMPILER_MSVC 12 // Microsoft Visual C++ 2013
    #elif _MSC_VER == 1600
        #define Z_COMPILER_MSVC 10 // Microsoft Visual C++ 2010
    #else
        #define Z_COMPILER_MSVC 0  // Microsoft Visual C++ < 2010
    #endif
#elif __GNUC__
    #define Z_COMPILER_GCC __GNUC__ // GCC
#else
    #error Unknown compiler.
#endif

// --------------------------------------------------------------------------------------------------------
// Compiler specifics: Assures that specific compiler macros are defined always.
// --------------------------------------------------------------------------------------------------------
#ifndef __LINE__
    #define __LINE__    // Microsoft Visual C++ macro
#endif
#ifndef __FILE__
    #define __FILE__    // Microsoft Visual C++ macro
#endif
#ifndef __DATE__
    #define __DATE__    // Microsoft Visual C++ macro
#endif
#ifndef __TIME__
    #define __TIME__    // Microsoft Visual C++ macro
#endif

#endif // __EXTERNALDEFINITIONS__
