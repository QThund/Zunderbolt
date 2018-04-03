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

#ifndef __COMMONCONFIGDEFINITIONS__
#define __COMMONCONFIGDEFINITIONS__

#include "ZCommon/ExternalDefinitions.h"

// --------------------------------------------------------------------------------------------------------
// Test execution configuration: This flag defines how the tests are executed, whether they are ignored or
// executed in the normal order. The main purpose of including this flag is to let a developer to check the
// results of the tests he/she is developing at the moment, not having to wait for the execution of all
// the other tests of the module previously implemented. So, when creating the tests for class C, this flag
// would nullify all the tests but those that are marked as exceptions. See definitions EXZTEST_-.
// --------------------------------------------------------------------------------------------------------
#define Z_TEST_CONFIG_TEST_EXECUTION_NORMAL 0x0
#define Z_TEST_CONFIG_TEST_EXECUTION_IGNORE 0x1

#define Z_TEST_CONFIG_TEST_EXECUTION Z_TEST_CONFIG_TEST_EXECUTION_NORMAL

// --------------------------------------------------------------------------------------------------------
// Current compilation configuration: This group of definitions identifies the compilation configuration
// that is currently selected for the operative system where it is running on.
// --------------------------------------------------------------------------------------------------------
#if defined(Z_OS_WINDOWS)

    #if defined(Z_ARCH_32BITS)
        #ifdef Z_COMPILER_MSVC // Microsoft Visual C++
            #if Z_COMPILER_MSVC >= 10 // Microsoft Visual C++ 2010
                #if defined(Z_DEBUG) && (defined(_MT) && defined(_DLL)) && !defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                    // Windows 32 bits OS, Debug, Shared runtime linking, Static library output
                    #define Z_TEST_CONFIG_WIN32_DEBUG_SHAREDRUNTIME_STATICOUT
                #elif defined(Z_DEBUG) && (defined(_MT) && defined(_DLL)) && defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                    // Windows 32 bits OS, Debug, Shared runtime linking, Dynamic library output
                    #define Z_TEST_CONFIG_WIN32_DEBUG_SHAREDRUNTIME_DYNAMICOUT
                #elif !defined(Z_DEBUG) && (defined(_MT) && defined(_DLL)) && !defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                    // Windows 32 bits OS, Release, Shared runtime linking, Static library output
                    #define Z_TEST_CONFIG_WIN32_RELEASE_SHAREDRUNTIME_STATICOUT
                #elif !defined(Z_DEBUG) && (defined(_MT) && defined(_DLL)) && defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                    // Windows 32 bits OS, Release, Shared runtime linking, Dynamic library output
                    #define Z_TEST_CONFIG_WIN32_RELEASE_SHAREDRUNTIME_DYNAMICOUT
                #elif defined(Z_DEBUG) && defined(_MT) && !defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                    // Windows 32 bits OS, Debug, Static runtime linking, Static library output
                    #define Z_TEST_CONFIG_WIN32_DEBUG_STATICRUNTIME_STATICOUT
                #elif defined(Z_DEBUG) && defined(_MT) && defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                    // Windows 32 bits OS, Debug, Static runtime linking, Dynamic library output
                    #define Z_TEST_CONFIG_WIN32_DEBUG_STATICRUNTIME_DYNAMICOUT
                #elif !defined(Z_DEBUG) && defined(_MT) && !defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                    // Windows 32 bits OS, Release, Static runtime linking, Static library output
                    #define Z_TEST_CONFIG_WIN32_RELEASE_STATICRUNTIME_STATICOUT
                #elif !defined(Z_DEBUG) && defined(_MT) && defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                    // Windows 32 bits OS, Release, Static runtime linking, Dynamic library output
                    #define Z_TEST_CONFIG_WIN32_RELEASE_STATICRUNTIME_DYNAMICOUT
                #else
                    #error "Unknown configuration"
                #endif
            #else// Microsoft Visual C++ < 2010
            #endif
        #elif defined(Z_COMPILER_GCC) // GCC (MinGW)
            #define UsingSharedRuntime // TODO [Thund]: How to know if the compiler is linking shared or static libstdc++?
            #if defined(Z_DEBUG) && defined(UsingSharedRuntime) && !defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                // Windows 32 bits OS, Debug, Shared runtime linking, Static library output
                #define Z_TEST_CONFIG_WIN32_DEBUG_SHAREDRUNTIME_STATICOUT
            #elif defined(Z_DEBUG) && defined(UsingSharedRuntime) && defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                // Windows 32 bits OS, Debug, Shared runtime linking, Dynamic library output
                #define Z_TEST_CONFIG_WIN32_DEBUG_SHAREDRUNTIME_DYNAMICOUT
            #elif !defined(Z_DEBUG) && defined(UsingSharedRuntime) && !defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                // Windows 32 bits OS, Release, Shared runtime linking, Static library output
                #define Z_TEST_CONFIG_WIN32_RELEASE_SHAREDRUNTIME_STATICOUT
            #elif !defined(Z_DEBUG) && defined(UsingSharedRuntime) && defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                // Windows 32 bits OS, Release, Shared runtime linking, Dynamic library output
                #define Z_TEST_CONFIG_WIN32_RELEASE_SHAREDRUNTIME_DYNAMICOUT
            #elif defined(Z_DEBUG) && !defined(UsingSharedRuntime) && !defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                // Windows 32 bits OS, Debug, Static runtime linking, Static library output
                #define Z_TEST_CONFIG_WIN32_DEBUG_STATICRUNTIME_STATICOUT
            #elif defined(Z_DEBUG) && !defined(UsingSharedRuntime) && defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                // Windows 32 bits OS, Debug, Static runtime linking, Dynamic library output
                #define Z_TEST_CONFIG_WIN32_DEBUG_STATICRUNTIME_DYNAMICOUT
            #elif !defined(Z_DEBUG) && !defined(UsingSharedRuntime) && !defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                // Windows 32 bits OS, Release, Static runtime linking, Static library output
                #define Z_TEST_CONFIG_WIN32_RELEASE_STATICRUNTIME_STATICOUT
            #elif !defined(Z_DEBUG) && !defined(UsingSharedRuntime) && defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                // Windows 32 bits OS, Release, Static runtime linking, Dynamic library output
                #define Z_TEST_CONFIG_WIN32_RELEASE_STATICRUNTIME_DYNAMICOUT
            #else
                #error "Unknown configuration"
            #endif
        #endif
    #elif defined(Z_ARCH_64BITS)
        #ifdef Z_COMPILER_MSVC // Microsoft Visual C++
            #if Z_COMPILER_MSVC >= 10 // Microsoft Visual C++ 2010
                #if defined(Z_DEBUG) && (defined(_MT) && defined(_DLL)) && !defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                    // Windows 64 bits OS, Debug, Shared runtime linking, Static library output
                    #define Z_TEST_CONFIG_WIN64_DEBUG_SHAREDRUNTIME_STATICOUT
                #elif defined(Z_DEBUG) && (defined(_MT) && defined(_DLL)) && defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                    // Windows 64 bits OS, Debug, Shared runtime linking, Dynamic library output
                    #define Z_TEST_CONFIG_WIN64_DEBUG_SHAREDRUNTIME_DYNAMICOUT
                #elif !defined(Z_DEBUG) && (defined(_MT) && defined(_DLL)) && !defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                    // Windows 64 bits OS, Release, Shared runtime linking, Static library output
                    #define Z_TEST_CONFIG_WIN64_RELEASE_SHAREDRUNTIME_STATICOUT
                #elif !defined(Z_DEBUG) && (defined(_MT) && defined(_DLL)) && defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                    // Windows 64 bits OS, Release, Shared runtime linking, Dynamic library output
                    #define Z_TEST_CONFIG_WIN64_RELEASE_SHAREDRUNTIME_DYNAMICOUT
                #elif defined(Z_DEBUG) && defined(_MT) && !defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                    // Windows 64 bits OS, Debug, Static runtime linking, Static library output
                    #define Z_TEST_CONFIG_WIN64_DEBUG_STATICRUNTIME_STATICOUT
                #elif defined(Z_DEBUG) && defined(_MT) && defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                    // Windows 64 bits OS, Debug, Static runtime linking, Dynamic library output
                    #define Z_TEST_CONFIG_WIN64_DEBUG_STATICRUNTIME_DYNAMICOUT
                #elif !defined(Z_DEBUG) && defined(_MT) && !defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                    // Windows 64 bits OS, Release, Static runtime linking, Static library output
                    #define Z_TEST_CONFIG_WIN64_RELEASE_STATICRUNTIME_STATICOUT
                #elif !defined(Z_DEBUG) && defined(_MT) && defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                    // Windows 64 bits OS, Release, Static runtime linking, Dynamic library output
                    #define Z_TEST_CONFIG_WIN64_RELEASE_STATICRUNTIME_DYNAMICOUT
                #else
                    #error "Unknown configuration"
                #endif
            #else// Microsoft Visual C++ < 2010
            #endif
        #elif defined(Z_COMPILER_GCC) // GCC (MinGW)
            #define UsingSharedRuntime // TODO [Thund]: How to know if the compiler is linking shared or static libstdc++?
            #if defined(Z_DEBUG) && defined(UsingSharedRuntime) && !defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                // Windows 64 bits OS, Debug, Shared runtime linking, Static library output
                #define Z_TEST_CONFIG_WIN64_DEBUG_SHAREDRUNTIME_STATICOUT
            #elif defined(Z_DEBUG) && defined(UsingSharedRuntime) && defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                // Windows 64 bits OS, Debug, Shared runtime linking, Dynamic library output
                #define Z_TEST_CONFIG_WIN64_DEBUG_SHAREDRUNTIME_DYNAMICOUT
            #elif !defined(Z_DEBUG) && defined(UsingSharedRuntime) && !defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                // Windows 64 bits OS, Release, Shared runtime linking, Static library output
                #define Z_TEST_CONFIG_WIN64_RELEASE_SHAREDRUNTIME_STATICOUT
            #elif !defined(Z_DEBUG) && defined(UsingSharedRuntime) && defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                // Windows 64 bits OS, Release, Shared runtime linking, Dynamic library output
                #define Z_TEST_CONFIG_WIN64_RELEASE_SHAREDRUNTIME_DYNAMICOUT
            #elif defined(Z_DEBUG) && !defined(UsingSharedRuntime) && !defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                // Windows 64 bits OS, Debug, Static runtime linking, Static library output
                #define Z_TEST_CONFIG_WIN64_DEBUG_STATICRUNTIME_STATICOUT
            #elif defined(Z_DEBUG) && !defined(UsingSharedRuntime) && defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                // Windows 64 bits OS, Debug, Static runtime linking, Dynamic library output
                #define Z_TEST_CONFIG_WIN64_DEBUG_STATICRUNTIME_DYNAMICOUT
            #elif !defined(Z_DEBUG) && !defined(UsingSharedRuntime) && !defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                // Windows 64 bits OS, Release, Static runtime linking, Static library output
                #define Z_TEST_CONFIG_WIN64_RELEASE_STATICRUNTIME_STATICOUT
            #elif !defined(Z_DEBUG) && !defined(UsingSharedRuntime) && defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                // Windows 64 bits OS, Release, Static runtime linking, Dynamic library output
                #define Z_TEST_CONFIG_WIN64_RELEASE_STATICRUNTIME_DYNAMICOUT
            #else
                #error "Unknown configuration"
            #endif
        #endif
    #endif
// [TODO] Thund: Completar con resto de compiladores.
#elif defined(Z_OS_LINUX)
    #if defined(Z_ARCH_32BITS)
        #if defined(Z_COMPILER_GCC) // GCC
            #define UsingSharedRuntime // TODO [Thund]: How to know if the compiler is linking shared or static libstdc++?
            #if defined(Z_DEBUG) && defined(UsingSharedRuntime) && !defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                // Linux 32 bits OS, Debug, Shared runtime linking, Static library output
                #define Z_TEST_CONFIG_LINUX32_DEBUG_SHAREDRUNTIME_STATICOUT
            #elif defined(Z_DEBUG) && defined(UsingSharedRuntime) && defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                // Linux 32 bits OS, Debug, Shared runtime linking, Dynamic library output
                #define Z_TEST_CONFIG_LINUX32_DEBUG_SHAREDRUNTIME_DYNAMICOUT
            #elif !defined(Z_DEBUG) && defined(UsingSharedRuntime) && !defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                // Linux 32 bits OS, Release, Shared runtime linking, Static library output
                #define Z_TEST_CONFIG_LINUX32_RELEASE_SHAREDRUNTIME_STATICOUT
            #elif !defined(Z_DEBUG) && defined(UsingSharedRuntime) && defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                // Linux 32 bits OS, Release, Shared runtime linking, Dynamic library output
                #define Z_TEST_CONFIG_LINUX32_RELEASE_SHAREDRUNTIME_DYNAMICOUT
            #elif defined(Z_DEBUG) && !defined(UsingSharedRuntime) && !defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                // Linux 32 bits OS, Debug, Static runtime linking, Static library output
                #define Z_TEST_CONFIG_LINUX32_DEBUG_STATICRUNTIME_STATICOUT
            #elif defined(Z_DEBUG) && !defined(UsingSharedRuntime) && defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                // Linux 32 bits OS, Debug, Static runtime linking, Dynamic library output
                #define Z_TEST_CONFIG_LINUX32_DEBUG_STATICRUNTIME_DYNAMICOUT
            #elif !defined(Z_DEBUG) && !defined(UsingSharedRuntime) && !defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                // Linux 32 bits OS, Release, Static runtime linking, Static library output
                #define Z_TEST_CONFIG_LINUX32_RELEASE_STATICRUNTIME_STATICOUT
            #elif !defined(Z_DEBUG) && !defined(UsingSharedRuntime) && defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                // Linux 32 bits OS, Release, Static runtime linking, Dynamic library output
                #define Z_TEST_CONFIG_LINUX32_RELEASE_STATICRUNTIME_DYNAMICOUT
            #else
                #error "Unknown configuration"
            #endif
        #endif
    #elif defined(Z_ARCH_64BITS)
        #if defined(Z_COMPILER_GCC) // GCC
            #define UsingSharedRuntime // TODO [Thund]: How to know if the compiler is linking shared or static libstdc++?
            #if defined(Z_DEBUG) && defined(UsingSharedRuntime) && !defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                // Linux 64 bits OS, Debug, Shared runtime linking, Static library output
                #define Z_TEST_CONFIG_LINUX64_DEBUG_SHAREDRUNTIME_STATICOUT
            #elif defined(Z_DEBUG) && defined(UsingSharedRuntime) && defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                // Linux 64 bits OS, Debug, Shared runtime linking, Dynamic library output
                #define Z_TEST_CONFIG_LINUX64_DEBUG_SHAREDRUNTIME_DYNAMICOUT
            #elif !defined(Z_DEBUG) && defined(UsingSharedRuntime) && !defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                // Linux 64 bits OS, Release, Shared runtime linking, Static library output
                #define Z_TEST_CONFIG_LINUX64_RELEASE_SHAREDRUNTIME_STATICOUT
            #elif !defined(Z_DEBUG) && defined(UsingSharedRuntime) && defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                // Linux 64 bits OS, Release, Shared runtime linking, Dynamic library output
                #define Z_TEST_CONFIG_LINUX64_RELEASE_SHAREDRUNTIME_DYNAMICOUT
            #elif defined(Z_DEBUG) && !defined(UsingSharedRuntime) && !defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                // Linux 64 bits OS, Debug, Static runtime linking, Static library output
                #define Z_TEST_CONFIG_LINUX64_DEBUG_STATICRUNTIME_STATICOUT
            #elif defined(Z_DEBUG) && !defined(UsingSharedRuntime) && defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                // Linux 64 bits OS, Debug, Static runtime linking, Dynamic library output
                #define Z_TEST_CONFIG_LINUX64_DEBUG_STATICRUNTIME_DYNAMICOUT
            #elif !defined(Z_DEBUG) && !defined(UsingSharedRuntime) && !defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                // Linux 64 bits OS, Release, Static runtime linking, Static library output
                #define Z_TEST_CONFIG_LINUX64_RELEASE_STATICRUNTIME_STATICOUT
            #elif !defined(Z_DEBUG) && !defined(UsingSharedRuntime) && defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                // Linux 64 bits OS, Release, Static runtime linking, Dynamic library output
                #define Z_TEST_CONFIG_LINUX64_RELEASE_STATICRUNTIME_DYNAMICOUT
            #else
                #error "Unknown configuration"
            #endif
        #endif
    #endif

#elif defined(Z_OS_MAC)
    #if defined(Z_ARCH_32BITS)
        #if defined(Z_COMPILER_GCC) // GCC
            #define UsingSharedRuntime // TODO [Thund]: How to know if the compiler is linking shared or static libstdc++?
            #if defined(Z_DEBUG) && defined(UsingSharedRuntime) && !defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                // Mac OS X 32 bits OS, Debug, Shared runtime linking, Static library output
                #define Z_TEST_CONFIG_MAC32_DEBUG_SHAREDRUNTIME_STATICOUT
            #elif defined(Z_DEBUG) && defined(UsingSharedRuntime) && defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                // Mac OS X 32 bits OS, Debug, Shared runtime linking, Dynamic library output
                #define Z_TEST_CONFIG_MAC32_DEBUG_SHAREDRUNTIME_DYNAMICOUT
            #elif !defined(Z_DEBUG) && defined(UsingSharedRuntime) && !defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                // Mac OS X 32 bits OS, Release, Shared runtime linking, Static library output
                #define Z_TEST_CONFIG_MAC32_RELEASE_SHAREDRUNTIME_STATICOUT
            #elif !defined(Z_DEBUG) && defined(UsingSharedRuntime) && defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                // Mac OS X 32 bits OS, Release, Shared runtime linking, Dynamic library output
                #define Z_TEST_CONFIG_MAC32_RELEASE_SHAREDRUNTIME_DYNAMICOUT
            #elif defined(Z_DEBUG) && !defined(UsingSharedRuntime) && !defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                // Mac OS X 32 bits OS, Debug, Static runtime linking, Static library output
                #define Z_TEST_CONFIG_MAC32_DEBUG_STATICRUNTIME_STATICOUT
            #elif defined(Z_DEBUG) && !defined(UsingSharedRuntime) && defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                // Mac OS X 32 bits OS, Debug, Static runtime linking, Dynamic library output
                #define Z_TEST_CONFIG_MAC32_DEBUG_STATICRUNTIME_DYNAMICOUT
            #elif !defined(Z_DEBUG) && !defined(UsingSharedRuntime) && !defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                // Mac OS X 32 bits OS, Release, Static runtime linking, Static library output
                #define Z_TEST_CONFIG_MAC32_RELEASE_STATICRUNTIME_STATICOUT
            #elif !defined(Z_DEBUG) && !defined(UsingSharedRuntime) && defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                // Mac OS X 32 bits OS, Release, Static runtime linking, Dynamic library output
                #define Z_TEST_CONFIG_MAC32_RELEASE_STATICRUNTIME_DYNAMICOUT
            #else
                #error "Unknown configuration"
            #endif
        #endif
    #elif defined(Z_ARCH_64BITS)
        #if defined(Z_COMPILER_GCC) // GCC
            #define UsingSharedRuntime // TODO [Thund]: How to know if the compiler is linking shared or static libstdc++?
            #if defined(Z_DEBUG) && defined(UsingSharedRuntime) && !defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                // Mac OS X 64 bits OS, Debug, Shared runtime linking, Static library output
                #define Z_TEST_CONFIG_MAC64_DEBUG_SHAREDRUNTIME_STATICOUT
            #elif defined(Z_DEBUG) && defined(UsingSharedRuntime) && defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                // Mac OS X 64 bits OS, Debug, Shared runtime linking, Dynamic library output
                #define Z_TEST_CONFIG_MAC64_DEBUG_SHAREDRUNTIME_DYNAMICOUT
            #elif !defined(Z_DEBUG) && defined(UsingSharedRuntime) && !defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                // Mac OS X 64 bits OS, Release, Shared runtime linking, Static library output
                #define Z_TEST_CONFIG_MAC64_RELEASE_SHAREDRUNTIME_STATICOUT
            #elif !defined(Z_DEBUG) && defined(UsingSharedRuntime) && defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                // Mac OS X 64 bits OS, Release, Shared runtime linking, Dynamic library output
                #define Z_TEST_CONFIG_MAC64_RELEASE_SHAREDRUNTIME_DYNAMICOUT
            #elif defined(Z_DEBUG) && !defined(UsingSharedRuntime) && !defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                // Mac OS X 64 bits OS, Debug, Static runtime linking, Static library output
                #define Z_TEST_CONFIG_MAC64_DEBUG_STATICRUNTIME_STATICOUT
            #elif defined(Z_DEBUG) && !defined(UsingSharedRuntime) && defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                // Mac OS X 64 bits OS, Debug, Static runtime linking, Dynamic library output
                #define Z_TEST_CONFIG_MAC64_DEBUG_STATICRUNTIME_DYNAMICOUT
            #elif !defined(Z_DEBUG) && !defined(UsingSharedRuntime) && !defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                // Mac OS X 64 bits OS, Release, Static runtime linking, Static library output
                #define Z_TEST_CONFIG_MAC64_RELEASE_STATICRUNTIME_STATICOUT
            #elif !defined(Z_DEBUG) && !defined(UsingSharedRuntime) && defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)
                // Mac OS X 64 bits OS, Release, Static runtime linking, Dynamic library output
                #define Z_TEST_CONFIG_MAC64_RELEASE_STATICRUNTIME_DYNAMICOUT
            #else
                #error "Unknown configuration"
            #endif
        #endif
    #endif
#else
    #error "Zunderbolt Error Message: Operative system not supported."
#endif


// --------------------------------------------------------------------------------------------------------
// Compilation configuration names: Depending on the operative system and the compilation configuration
// currently selected, a name is assigned. This name is going to be used, for example, to generate the
// test result file.
// --------------------------------------------------------------------------------------------------------
#if   defined(Z_TEST_CONFIG_WIN32_DEBUG_SHAREDRUNTIME_STATICOUT)
    #define Z_TEST_CONFIG_NAME "Win32DebugSharedrtStatic"
#elif defined(Z_TEST_CONFIG_WIN32_DEBUG_SHAREDRUNTIME_DYNAMICOUT)
    #define Z_TEST_CONFIG_NAME "Win32DebugSharedrtDynamic"
#elif defined(Z_TEST_CONFIG_WIN32_RELEASE_SHAREDRUNTIME_STATICOUT)
    #define Z_TEST_CONFIG_NAME "Win32ReleaseSharedrtStatic"
#elif defined(Z_TEST_CONFIG_WIN32_RELEASE_SHAREDRUNTIME_DYNAMICOUT)
    #define Z_TEST_CONFIG_NAME "Win32ReleaseSharedrtDynamic"
#elif defined(Z_TEST_CONFIG_WIN32_DEBUG_STATICRUNTIME_STATICOUT)
    #define Z_TEST_CONFIG_NAME "Win32DebugStaticrtStatic"
#elif defined(Z_TEST_CONFIG_WIN32_DEBUG_STATICRUNTIME_DYNAMICOUT)
    #define Z_TEST_CONFIG_NAME "Win32DebugStaticrtDynamic"
#elif defined(Z_TEST_CONFIG_WIN32_RELEASE_STATICRUNTIME_STATICOUT)
    #define Z_TEST_CONFIG_NAME "Win32ReleaseStaticrtStatic"
#elif defined(Z_TEST_CONFIG_WIN32_RELEASE_STATICRUNTIME_DYNAMICOUT)
    #define Z_TEST_CONFIG_NAME "Win32ReleaseStaticrtDynamic"

#elif defined(Z_TEST_CONFIG_LINUX32_DEBUG_SHAREDRUNTIME_STATICOUT)
    #define Z_TEST_CONFIG_NAME "Linux32DebugSharedrtStatic"
#elif defined(Z_TEST_CONFIG_LINUX32_DEBUG_SHAREDRUNTIME_DYNAMICOUT)
    #define Z_TEST_CONFIG_NAME "Linux32DebugSharedrtDynamic"
#elif defined(Z_TEST_CONFIG_LINUX32_RELEASE_SHAREDRUNTIME_STATICOUT)
    #define Z_TEST_CONFIG_NAME "Linux32ReleaseSharedrtStatic"
#elif defined(Z_TEST_CONFIG_LINUX32_RELEASE_SHAREDRUNTIME_DYNAMICOUT)
    #define Z_TEST_CONFIG_NAME "Linux32ReleaseSharedrtDynamic"
#elif defined(Z_TEST_CONFIG_LINUX32_DEBUG_STATICRUNTIME_STATICOUT)
    #define Z_TEST_CONFIG_NAME "Linux32DebugStaticrtStatic"
#elif defined(Z_TEST_CONFIG_LINUX32_DEBUG_STATICRUNTIME_DYNAMICOUT)
    #define Z_TEST_CONFIG_NAME "Linux32DebugStaticrtDynamic"
#elif defined(Z_TEST_CONFIG_LINUX32_RELEASE_STATICRUNTIME_STATICOUT)
    #define Z_TEST_CONFIG_NAME "Linux32ReleaseStaticrtStatic"
#elif defined(Z_TEST_CONFIG_LINUX32_RELEASE_STATICRUNTIME_DYNAMICOUT)
    #define Z_TEST_CONFIG_NAME "Linux32ReleaseStaticrtDynamic"

#elif defined(Z_TEST_CONFIG_MAC32_DEBUG_SHAREDRUNTIME_STATICOUT)
    #define Z_TEST_CONFIG_NAME "Mac32DebugSharedrtStatic"
#elif defined(Z_TEST_CONFIG_MAC32_DEBUG_SHAREDRUNTIME_DYNAMICOUT)
    #define Z_TEST_CONFIG_NAME "Mac32DebugSharedrtDynamic"
#elif defined(Z_TEST_CONFIG_MAC32_RELEASE_SHAREDRUNTIME_STATICOUT)
    #define Z_TEST_CONFIG_NAME "Mac32ReleaseSharedrtStatic"
#elif defined(Z_TEST_CONFIG_MAC32_RELEASE_SHAREDRUNTIME_DYNAMICOUT)
    #define Z_TEST_CONFIG_NAME "Mac32ReleaseSharedrtDynamic"
#elif defined(Z_TEST_CONFIG_MAC32_DEBUG_STATICRUNTIME_STATICOUT)
    #define Z_TEST_CONFIG_NAME "Mac32DebugStaticrtStatic"
#elif defined(Z_TEST_CONFIG_MAC32_DEBUG_STATICRUNTIME_DYNAMICOUT)
    #define Z_TEST_CONFIG_NAME "Mac32DebugStaticrtDynamic"
#elif defined(Z_TEST_CONFIG_MAC32_RELEASE_STATICRUNTIME_STATICOUT)
    #define Z_TEST_CONFIG_NAME "Mac32ReleaseStaticrtStatic"
#elif defined(Z_TEST_CONFIG_MAC32_RELEASE_STATICRUNTIME_DYNAMICOUT)
    #define Z_TEST_CONFIG_NAME "Mac32ReleaseStaticrtDynamic"

#elif   defined(Z_TEST_CONFIG_WIN64_DEBUG_SHAREDRUNTIME_STATICOUT)
    #define Z_TEST_CONFIG_NAME "Win64DebugSharedrtStatic"
#elif defined(Z_TEST_CONFIG_WIN64_DEBUG_SHAREDRUNTIME_DYNAMICOUT)
    #define Z_TEST_CONFIG_NAME "Win64DebugSharedrtDynamic"
#elif defined(Z_TEST_CONFIG_WIN64_RELEASE_SHAREDRUNTIME_STATICOUT)
    #define Z_TEST_CONFIG_NAME "Win64ReleaseSharedrtStatic"
#elif defined(Z_TEST_CONFIG_WIN64_RELEASE_SHAREDRUNTIME_DYNAMICOUT)
    #define Z_TEST_CONFIG_NAME "Win64ReleaseSharedrtDynamic"
#elif defined(Z_TEST_CONFIG_WIN64_DEBUG_STATICRUNTIME_STATICOUT)
    #define Z_TEST_CONFIG_NAME "Win64DebugStaticrtStatic"
#elif defined(Z_TEST_CONFIG_WIN64_DEBUG_STATICRUNTIME_DYNAMICOUT)
    #define Z_TEST_CONFIG_NAME "Win64DebugStaticrtDynamic"
#elif defined(Z_TEST_CONFIG_WIN64_RELEASE_STATICRUNTIME_STATICOUT)
    #define Z_TEST_CONFIG_NAME "Win64ReleaseStaticrtStatic"
#elif defined(Z_TEST_CONFIG_WIN64_RELEASE_STATICRUNTIME_DYNAMICOUT)
    #define Z_TEST_CONFIG_NAME "Win64ReleaseStaticrtDynamic"

#elif defined(Z_TEST_CONFIG_LINUX64_DEBUG_SHAREDRUNTIME_STATICOUT)
    #define Z_TEST_CONFIG_NAME "Linux64DebugSharedrtStatic"
#elif defined(Z_TEST_CONFIG_LINUX64_DEBUG_SHAREDRUNTIME_DYNAMICOUT)
    #define Z_TEST_CONFIG_NAME "Linux64DebugSharedrtDynamic"
#elif defined(Z_TEST_CONFIG_LINUX64_RELEASE_SHAREDRUNTIME_STATICOUT)
    #define Z_TEST_CONFIG_NAME "Linux64ReleaseSharedrtStatic"
#elif defined(Z_TEST_CONFIG_LINUX64_RELEASE_SHAREDRUNTIME_DYNAMICOUT)
    #define Z_TEST_CONFIG_NAME "Linux64ReleaseSharedrtDynamic"
#elif defined(Z_TEST_CONFIG_LINUX64_DEBUG_STATICRUNTIME_STATICOUT)
    #define Z_TEST_CONFIG_NAME "Linux64DebugStaticrtStatic"
#elif defined(Z_TEST_CONFIG_LINUX64_DEBUG_STATICRUNTIME_DYNAMICOUT)
    #define Z_TEST_CONFIG_NAME "Linux64DebugStaticrtDynamic"
#elif defined(Z_TEST_CONFIG_LINUX64_RELEASE_STATICRUNTIME_STATICOUT)
    #define Z_TEST_CONFIG_NAME "Linux64ReleaseStaticrtStatic"
#elif defined(Z_TEST_CONFIG_LINUX64_RELEASE_STATICRUNTIME_DYNAMICOUT)
    #define Z_TEST_CONFIG_NAME "Linux64ReleaseStaticrtDynamic"

#elif defined(Z_TEST_CONFIG_MAC64_DEBUG_SHAREDRUNTIME_STATICOUT)
    #define Z_TEST_CONFIG_NAME "Mac64DebugSharedrtStatic"
#elif defined(Z_TEST_CONFIG_MAC64_DEBUG_SHAREDRUNTIME_DYNAMICOUT)
    #define Z_TEST_CONFIG_NAME "Mac64DebugSharedrtDynamic"
#elif defined(Z_TEST_CONFIG_MAC64_RELEASE_SHAREDRUNTIME_STATICOUT)
    #define Z_TEST_CONFIG_NAME "Mac64ReleaseSharedrtStatic"
#elif defined(Z_TEST_CONFIG_MAC64_RELEASE_SHAREDRUNTIME_DYNAMICOUT)
    #define Z_TEST_CONFIG_NAME "Mac64ReleaseSharedrtDynamic"
#elif defined(Z_TEST_CONFIG_MAC64_DEBUG_STATICRUNTIME_STATICOUT)
    #define Z_TEST_CONFIG_NAME "Mac64DebugStaticrtStatic"
#elif defined(Z_TEST_CONFIG_MAC64_DEBUG_STATICRUNTIME_DYNAMICOUT)
    #define Z_TEST_CONFIG_NAME "Mac64DebugStaticrtDynamic"
#elif defined(Z_TEST_CONFIG_MAC64_RELEASE_STATICRUNTIME_STATICOUT)
    #define Z_TEST_CONFIG_NAME "Mac64ReleaseStaticrtStatic"
#elif defined(Z_TEST_CONFIG_MAC64_RELEASE_STATICRUNTIME_DYNAMICOUT)
    #define Z_TEST_CONFIG_NAME "Mac64ReleaseStaticrtDynamic"

#endif

#endif // __COMMONCONFIGDEFINITIONS__
