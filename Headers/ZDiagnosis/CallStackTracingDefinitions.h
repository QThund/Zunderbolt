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

#ifndef __CALLSTACKTRACINGDEFINITIONS__
#define __CALLSTACKTRACINGDEFINITIONS__

#include "ZDiagnosis/DiagnosisModuleDefinitions.h"

#include "ScopedCallTraceNotifier.h"

namespace z
{
    
// --------------------------------------------------------------------------------------------------------
// Zunderbolt's Call Stack Tracing utility: It must be placed at the very beginning of the body of 
// a free function.
// --------------------------------------------------------------------------------------------------------
#define Z_TRACE_CALLSTACK_FUNCTION_WITHOUT_PARAMS() \
    const ScopedCallTraceNotifier SCOPED_TRACE(     \
            CallTrace(Z_PRINT_FUNCTION,             \
                      null_z,                       \
                      0));

// --------------------------------------------------------------------------------------------------------
// Zunderbolt's Call Stack Tracing utility: It must be placed at the very beginning of the body of a method. 
// The class name, which is a null-terminated array of chars, is passed as parameter to this macro.
// --------------------------------------------------------------------------------------------------------
#define Z_TRACE_CALLSTACK_METHOD_WITHOUT_PARAMS(szClassName)    \
    const ScopedCallTraceNotifier SCOPED_TRACE(                 \
            CallTrace(Z_PRINT_FUNCTION,                         \
                      null_z,                                   \
                      0,                                        \
                      szClassName));

// --------------------------------------------------------------------------------------------------------
// Zunderbolt's Call Stack Tracing utility: It must be placed at the very beginning of the body of a 
// The class name, which is a null-terminated array of chars, is passed as parameter to this macro.
// It assumes that the class implements the ToString method, which is called to get the state of the object.
// --------------------------------------------------------------------------------------------------------
#define Z_TRACE_CALLSTACK_METHOD_WITHOUT_PARAMS_WITH_TOSTRING(szClassName)  \
    const ScopedCallTraceNotifier SCOPED_TRACE(                             \
            CallTrace(Z_PRINT_FUNCTION,                                     \
                      null_z,                                               \
                      0,                                                    \
                      szClassName,                                          \
                      this->ToString()));

// --------------------------------------------------------------------------------------------------------
// Zunderbolt's Call Stack Tracing utility: It must be placed at the very beginning of the body of 
// a free function. Every function parameter has to be passed to this macro.
// --------------------------------------------------------------------------------------------------------
#define Z_TRACE_CALLSTACK_FUNCTION_WITH_PARAMS(...)                       \
    const ArgumentTrace ARGUMENT_TRACES[] = { __VA_ARGS__ };              \
    const ScopedCallTraceNotifier SCOPED_TRACE(                           \
            CallTrace(Z_PRINT_FUNCTION,                                   \
                      ARGUMENT_TRACES,                                    \
                      sizeof(ARGUMENT_TRACES) / sizeof(ArgumentTrace)));

// --------------------------------------------------------------------------------------------------------
// Zunderbolt's Call Stack Tracing utility: It must be placed at the very beginning of the body of a method. 
// Every function parameter has to be passed to this macro after the class name, which is a null-terminated array of chars.
// --------------------------------------------------------------------------------------------------------
#define Z_TRACE_CALLSTACK_METHOD_WITH_PARAMS(szClassName, ...)          \
    const ArgumentTrace ARGUMENT_TRACES[] = { __VA_ARGS__ };            \
    const ScopedCallTraceNotifier SCOPED_TRACE(                         \
            CallTrace(Z_PRINT_FUNCTION,                                 \
                      ARGUMENT_TRACES,                                  \
                      sizeof(ARGUMENT_TRACES) / sizeof(ArgumentTrace),  \
                      szClassName));

// --------------------------------------------------------------------------------------------------------
// Zunderbolt's Call Stack Tracing utility: It must be placed at the very beginning of the body of a 
// non-static method. Every function parameter has to be passed to this macro after the class 
// name, which is a null-terminated array of chars. It assumes that the class implements the ToString method, 
// which is called to get the state of the object.
// --------------------------------------------------------------------------------------------------------
#define Z_TRACE_CALLSTACK_METHOD_WITH_PARAMS_WITH_TOSTRING(szClassName, ...)   \
    const ArgumentTrace ARGUMENT_TRACES[] = { __VA_ARGS__ };                   \
    const ScopedCallTraceNotifier SCOPED_TRACE(                                \
            CallTrace(Z_PRINT_FUNCTION,                                        \
                      ARGUMENT_TRACES,                                         \
                      sizeof(ARGUMENT_TRACES) / sizeof(ArgumentTrace),         \
                      szClassName,                                             \
                      this->ToString()));

// --------------------------------------------------------------------------------------------------------
// Zunderbolt's Call Stack Tracing utility: Encloses an argument that is known to provide an implementation
// of the ToString method, which returns a string representation of the object's state. This macro is intended to 
// be used in the list of parameters passed to Z_TRACE_CALLSTACK_* macros.
// --------------------------------------------------------------------------------------------------------
#define Z_TRACE_PARAM_HAS_TOSTRING(param) ArgumentTrace(param, TypeWithToString())

// --------------------------------------------------------------------------------------------------------
// Zunderbolt's Call Stack Tracing utility: Encloses an argument that is known to provide an implementation
// of the GetTypeObjcet method, which returns a pointer to a Type instance that contains the name of the type. 
// This macro is intended to be used in the list of parameters passed to Z_TRACE_CALLSTACK_* macros.
// --------------------------------------------------------------------------------------------------------
#define Z_TRACE_PARAM_HAS_GETTYPE(param) ArgumentTrace(param, TypeWithGetType())

// --------------------------------------------------------------------------------------------------------
// Zunderbolt's Call Stack Tracing utility: Encloses an argument that is known to provide an implementation
// of the ToString method, which returns a string representation of the object's state, and an implementation of 
// the GetTypeObjcet method, which returns a pointer to a Type instance that contains the name of the type. 
// This macro is intended to be used in the list of parameters passed to Z_TRACE_CALLSTACK_* macros.
// --------------------------------------------------------------------------------------------------------
#define Z_TRACE_PARAM_HAS_GETTYPE_TOSTRING(param) ArgumentTrace(param, TypeWithGetType(), \
                                                                TypeWithToString())


} // namespace z


#endif // __CALLSTACKTRACINGDEFINITIONS__
