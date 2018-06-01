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

#ifndef __ASSERTIONS__
#define __ASSERTIONS__

#ifdef Z_COMPILER_MSVC
    #pragma warning(disable: 4297) // This prevents the compiler from complaining about functions that are supposed not 
                                   // to throw exceptions but do throw exceptions due to the assertion behavior compilation flag
#endif

#include "ZCommon/EAssertionType.h"


namespace z 
{ 
    // This forward declaration is necessary to avoid mutual inclusion with string types
    class StringUnicode; 

#if Z_CONFIG_CHARACTERSET_DEFAULT == Z_CONFIG_CHARACTERSET_ASCII
    typedef std::string string_z;
#elif Z_CONFIG_CHARACTERSET_DEFAULT == Z_CONFIG_CHARACTERSET_UNICODE
    typedef StringUnicode string_z;
#endif

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT != Z_CONFIG_ASSERTSBEHAVIOR_DISABLED

    /// <summary>
	/// Traces a failed assertion, providing some useful debugging information.
	/// </summary>
    /// <remarks>
	/// It uses the internal logger to send the information to the configured output channel.
	/// </remarks>
    /// <param name="strExpression">[IN] The expression which evaluates to false.</param>
    /// <param name="strErrorMessage">[IN] The error message provided by the user in the assertion.</param>
    /// <param name="nLineNumber">[IN] The number of the line of code where the failed assertion is.</param>
    /// <param name="strFileName">[IN] The file name of the source code file where the assertion failed.</param>
    /// <param name="uAssertionType">[IN] The type of assertion, depending its purpose.</param>
    Z_COMMON_MODULE_SYMBOLS void Z_TRACE_FAILED_ASSERT(const string_z &strExpression, 
                                                      const string_z &strErrorMessage,
                                                      const int nLineNumber, 
                                                      const string_z &strFileName,
                                                      const EAssertionType &eAssertionType);
        
    /// <summary>
	/// Throws an exception filled with some useful debugging information.
	/// </summary>
    /// <param name="strExpression">[IN] The expression which evaluates to false.</param>
    /// <param name="strErrorMessage">[IN] The error message provided by the user in the assertion.</param>
    /// <param name="nLineNumber">[IN] The number of the line of code where the failed assertion is.</param>
    /// <param name="strFileName">[IN] The file name of the source code file where the assertion failed.</param>
    Z_COMMON_MODULE_SYMBOLS void Z_THROW_FAILED_ASSERT(const string_z &strExpression, 
                                                      const string_z &strErrorMessage,
                                                      const int nLineNumber, 
                                                      const string_z &strFileName);

    #if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS // This is used for testing purposes
    
        #ifdef Z_COMPILER_MSVC
            #define Z_ASSERT(expression, strErrorMessage, eAssertionType)                                                                           \
                    {                                                                                                                               \
                        if(!(expression))                                                                                                           \
                        {                                                                                                                           \
                            if(Z_CONFIG_ASSERTSTRACING_DEFAULT == Z_CONFIG_ASSERTSTRACING_ENABLED)													\
                            {                                                                                                                       \
                                Z_TRACE_FAILED_ASSERT(#expression, strErrorMessage, __LINE__, __FILE__, eAssertionType);                            \
                            }                                                                                                                       \
                            Z_THROW_FAILED_ASSERT(#expression, strErrorMessage, __LINE__, __FILE__);                                                \
                        }                                                                                                                           \
                    }
        #else
            // It is not possible to use throw when compiling with GCC
            #define Z_ASSERT(expression, strErrorMessage, eAssertionType)                                                                           \
                    {                                                                                                                               \
                        if(!(expression))                                                                                                           \
                        {                                                                                                                           \
                            if(Z_CONFIG_ASSERTSTRACING_DEFAULT == Z_CONFIG_ASSERTSTRACING_ENABLED)                                                  \
                            {                                                                                                                       \
                                Z_TRACE_FAILED_ASSERT(#expression, strErrorMessage, __LINE__, __FILE__, eAssertionType);                            \
                            }                                                                                                                       \
                        }                                                                                                                           \
                    }
        #endif
    #else

        #ifdef Z_COMPILER_GCC

            #define Z_ASSERT(expression, strErrorMessage, eAssertionType)															\
                             {                                                                                                      \
                                 if(!(expression))                                                                                  \
                                 {                                                                                                  \
                                     asm("int $3");                                                                                 \
                                                                                                                                    \
                                     if(Z_CONFIG_ASSERTSTRACING_DEFAULT == Z_CONFIG_ASSERTSTRACING_ENABLED)							\
                                     {                                                                                              \
                                         Z_TRACE_FAILED_ASSERT(#expression, strErrorMessage, __LINE__, __FILE__, eAssertionType);	\
                                     }                                                                                              \
                                 }                                                                                                  \
                             }
                             // Note: asm("int $3") makes GDB to stop at the failing line and continue the execution later
        #else

            #define Z_ASSERT(expression, strErrorMessage, eAssertionType)													\
                    {																										\
                        if(!(expression))																					\
                        {																									\
                            if(Z_CONFIG_ASSERTSTRACING_DEFAULT == Z_CONFIG_ASSERTSTRACING_ENABLED)							\
                            {																								\
                                Z_TRACE_FAILED_ASSERT(#expression, strErrorMessage, __LINE__, __FILE__, eAssertionType);	\
                            }																								\
                            __debugbreak();																					\
                        }																									\
                    }
        #endif
    #endif

#else

    #define Z_ASSERT(expression, strErrorMessage, eAssertionType) ;

#endif

// A macro definition for every type of assertion

// Assertion to notify the use of deprecated functions or classes
#define Z_ASSERT_DEPRECATED(expression, strErrorMessage) Z_ASSERT(expression, strErrorMessage, z::EAssertionType::E_Deprecation)
// Assertion to notify an abnormal situation, something that may be not intended, although the program will continue normally
#define Z_ASSERT_WARNING(expression, strErrorMessage)    Z_ASSERT(expression, strErrorMessage, z::EAssertionType::E_Warning)
// Assertion to notify an abnormal situation, something that is not allowed and will make the program crash either immediately or in a while
#define Z_ASSERT_ERROR(expression, strErrorMessage)      Z_ASSERT(expression, strErrorMessage, z::EAssertionType::E_Error)

} // namespace z

#endif // __ASSERTIONS__
