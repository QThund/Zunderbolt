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

#ifndef __CALLTRACE__
#define __CALLTRACE__

#include "ZDiagnosis/DiagnosisModuleDefinitions.h"
#include "ArgumentTrace.h"


namespace z
{

/// <summary>
/// Represents a data structure that stores some information about the context of a function call.
/// </summary>
class Z_DIAGNOSIS_MODULE_SYMBOLS CallTrace
{

    // CONSTRUCTORS
    // ---------------
public:
    
    /// <summary>
    /// Constructor that receives the function signature and some information about its arguments.
    /// </summary>
    /// <param name="szFunctionSignature">[IN] The function signature.</param>
    /// <param name="arArgumentTraces">[IN] An array of argument traces. It can be null if the function does not have arguments.</param>
    /// <param name="uNumberOfArguments">[IN] The amount of argument traces.</param>
    CallTrace(const char* szFunctionSignature, const ArgumentTrace* arArgumentTraces, const unsigned int uNumberOfArguments);

    /// <summary>
    /// Constructor that receives the class name, the function signature and some information about its arguments.
    /// </summary>
    /// <param name="szFunctionSignature">[IN] The function signature.</param>
    /// <param name="arArgumentTraces">[IN] An array of argument traces. It can be null if the function does not have arguments.</param>
    /// <param name="uNumberOfArguments">[IN] The amount of argument traces.</param>
    /// <param name="szClassName">[IN] The name of the class. It should not be null.</param>
    CallTrace(const char* szFunctionSignature, const ArgumentTrace* arArgumentTraces, const unsigned int uNumberOfArguments, const char* szClassName);

    /// <summary>
    /// Constructor that receives the class name, the object state, the function signature and some information about its arguments.
    /// </summary>
    /// <param name="szFunctionSignature">[IN] The function signature.</param>
    /// <param name="arArgumentTraces">[IN] An array of argument traces. It can be null if the function does not have arguments.</param>
    /// <param name="uNumberOfArguments">[IN] The amount of argument traces.</param>
    /// <param name="szClassName">[IN] The name of the class. It should not be null.</param>
    /// <param name="strObjectState">[IN] The string representation of the object's state.</param>
    CallTrace(const char* szFunctionSignature, const ArgumentTrace* arArgumentTraces, const unsigned int uNumberOfArguments, const char* szClassName, const string_z& strObjectState);


    // PROPERTIES
    // ---------------
public:
    
    /// <summary>
    /// Gets the function signature.
    /// </summary>
    /// <returns>
    /// The function signature.
    /// </returns>
    const char* GetFunctionSignature() const;
    
    /// <summary>
    /// Gets the array of arguments.
    /// </summary>
    /// <returns>
    /// The array of arguments. It can be null.
    /// </returns>
    const ArgumentTrace* GetArguments() const;
    
    /// <summary>
    /// Gets the amount of arguments.
    /// </summary>
    /// <returns>
    /// The amount of arguments. It can be zero.
    /// </returns>
    unsigned int GetArgumentsCount() const;
    
    /// <summary>
    /// Gets the name of the class.
    /// </summary>
    /// <returns>
    /// The name of the class, if any. It can be null.
    /// </returns>
    const char* GetClassName() const;
    
    /// <summary>
    /// Gets the state of the object.
    /// </summary>
    /// <returns>
    /// The string representation of the object.
    /// </returns>
    const string_z& GetObjectState() const;


    // ATTRIBUTES
    // ---------------
protected:

    /// <summary>
    /// The function signature.
    /// </summary>
    const char* m_szFunctionSignature;

    /// <summary>
    /// The array of arguments. It can be null.
    /// </summary>
    const ArgumentTrace* m_arArgumentTraces;

    /// <summary>
    /// The amount of arguments. It can be zero.
    /// </summary>
    const unsigned int m_uNumberOfArguments;

    /// <summary>
    /// The name of the class, if any. It can be null.
    /// </summary>
    const char* m_szClassName;

    /// <summary>
    /// The string representation of the object.
    /// </summary>
    const string_z m_strObjectState;

};

} // namespace z


#endif // __CALLTRACE__
