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

#ifndef __SINTERNALLOGGER__
#define __SINTERNALLOGGER__

#include "ZCommon/DataTypes/DataTypesDefinitions.h"

#ifdef Z_COMPILER_MSVC
    #pragma warning( push )
    #pragma warning( disable: 4251 ) // This warning occurs when using a template specialization as attribute
#endif

#include "ZCommon/Delegate.h"

namespace z
{

/// <summary>
/// Logger used internally by the engine's libraries to write text to a given output channel.
/// </summary>
/// <remarks>
/// This class is not intended to be used by final users but only by the engine.<br/>
/// Since the lowest layers of the engine do not have any logging utility (loggers are implemented in the System layer) and
/// it is not possible to access a class of an upper layer, it was necessary to provide a way to send all the log entries 
/// produced by lower layer libraries to external loggers. Using a delegate, upper layers can set it to call any function,
/// for example a logger instance's method. Lower layers will call that delegate, whatever function it points to.
/// </remarks>
class Z_COMMON_MODULE_SYMBOLS SInternalLogger
{
	// CONSTRUCTORS
	// ---------------
private:

	/// <summary>
	/// Default constructor (hidden).
	/// </summary>
	SInternalLogger();
    

	// METHODS
	// ---------------
public:

    /// <summary>
	/// Sends text to the active console, if any. When using Visual Studio, the text will be sent to the output debug window.
	/// </summary>
    /// <remarks>
	/// No end-of-line characters are added.
	/// </remarks>
    /// <param name="strMessage">[IN] The text to be sent to the console.</param>
    static void DefaultLogFunction(const string_z &strMessage);


	// PROPERTIES
	// ---------------
public:

    /// <summary>
	/// Sets the log function to which the delegate will point.
	/// </summary>
    /// <param name="loggingFunction">[IN] The new logging function.</param>
    static void SetLogFunction(Delegate<void (const string_z&)> loggingFunction);


	// ATTRIBUTES
	// ---------------
public:

    /// <summary>
	/// Call the logging function directly.
	/// </summary>
    static Delegate<void (const string_z&)> Log;
};



#ifdef Z_COMPILER_MSVC
    #pragma warning( pop )
#endif

} // namespace z

#endif // __SINTERNALLOGGER__
