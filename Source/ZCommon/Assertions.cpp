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

#include "ZCommon/Assertions.h"

#include "ZCommon/DataTypes/StringsDefinitions.h"
#include "ZCommon/LoggingUtilities.h"
#include "ZCommon/Exceptions/AssertException.h"

namespace z
{

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           FUNCTIONS        |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

void Z_TRACE_FAILED_ASSERT(const string_z &strExpression, 
                           const string_z &strErrorMessage, 
                           const int nLineNumber, 
                           const string_z &strFileName,
                           const EAssertionType &eAssertionType)
{
    string_z strLogText("!! ");
    
    switch(eAssertionType)
    {
        case EAssertionType::E_Deprecation:
            strLogText.Append("[Deprecated]");
            break;
        case EAssertionType::E_Warning:
            strLogText.Append("[Warning]");
            break;
        case EAssertionType::E_Error:
            strLogText.Append("[Error]");
            break;
        default:
            break;
    }

    strLogText.Append(" Z ASSERTION FAILED !! : \"");
    strLogText.Append(strErrorMessage);
    strLogText.Append(string_z("\" at "));
    strLogText.Append(strFileName);
    strLogText.Append(" (");
    strLogText.Append(nLineNumber);
    strLogText.Append(") [");
    strLogText.Append(strExpression);
    strLogText.Append("]");
    strLogText.Append(string_z("\n"));
    Z_LOG(strLogText);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS 

void Z_THROW_FAILED_ASSERT(const string_z &strExpression, 
                            const string_z &strErrorMessage,
                            const int nLineNumber, 
                            const string_z &strFileName)
{
    throw AssertException(strExpression, strErrorMessage, nLineNumber, strFileName);
}

#endif

} // namespace z