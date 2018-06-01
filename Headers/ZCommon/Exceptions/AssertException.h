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

#ifndef __ASSERTEXCEPTION__
#define __ASSERTEXCEPTION__

#include "ZCommon/CommonModuleDefinitions.h"
#include "ZCommon/DataTypes/StringsDefinitions.h"



namespace z
{

/// <summary>
/// Exception used for testing purposes only. It stores information about a failed assertion.
/// </summary>
class Z_COMMON_MODULE_SYMBOLS AssertException
{
    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Constructor that receives all the information about a failed assertion.
    /// </summary>
    /// <param name="strCondition">[IN] The condition that failed.</param>
    /// <param name="strMessage">[IN] The error message.</param>
    /// <param name="nLineNumber">[IN] The number of the line where the assertion failed.</param>
    /// <param name="strFileName">[IN] The source code file where the assertion failed.</param>
    AssertException(const string_z &strCondition, const string_z &strMessage, const int nLineNumber, const string_z &strFileName);


    // PROPERTIES
    // ---------------
public:

    /// <summary>
    /// Gets the condition that failed.
    /// </summary>
    /// <returns>
    /// A string that contains the condition that failed.
    /// </returns>
    string_z GetCondition() const;

    /// <summary>
    /// Gets the error message.
    /// </summary>
    /// <returns>
    /// The error message.
    /// </returns>
    string_z GetMessage() const;

    /// <summary>
    /// Gets the number of the line where the assertion failed.
    /// </summary>
    /// <returns>
    /// The number of the line where the assertion failed.
    /// </returns>
    int GetLineNumber() const;

    /// <summary>
    /// Gets the source code file where the assertion failed.
    /// </summary>
    /// <returns>
    /// The source code file where the assertion failed.
    /// </returns>
    string_z GetFileName() const;


    // ATTRIBUTES
    // ---------------
protected:

    /// <summary>
    /// A string that contains the condition that failed.
    /// </summary>
    string_z m_strCondition;

    /// <summary>
    /// The error message.
    /// </summary>
    string_z m_strMessage;

    /// <summary>
    /// The number of the line where the assertion failed.
    /// </summary>
    int m_nLineNumber;

    /// <summary>
    /// The source code file where the assertion failed.
    /// </summary>
    string_z m_strFileName;

};

} // namespace z


#endif // __ASSERTEXCEPTION__
