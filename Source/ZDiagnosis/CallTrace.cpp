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

#include "ZDiagnosis/CallTrace.h"


namespace z
{

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |       CONSTRUCTORS         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

CallTrace::CallTrace(const char* szFunctionSignature, const ArgumentTrace* arArgumentTraces, const unsigned int uNumberOfArguments) : 
                                                                                                                        m_szFunctionSignature(szFunctionSignature),
                                                                                                                        m_arArgumentTraces(arArgumentTraces),
                                                                                                                        m_uNumberOfArguments(uNumberOfArguments),
                                                                                                                        m_szClassName(null_z),
                                                                                                                        m_strObjectState(string_z::GetEmpty())
{
    Z_ASSERT_WARNING(!(arArgumentTraces == null_z && uNumberOfArguments > 0), "The number of arguments cannot be greater than zero if the argument array is null.");
    Z_ASSERT_WARNING(!(arArgumentTraces != null_z && uNumberOfArguments == 0), "The number of arguments cannot be zero if the argument array is not null.");
    Z_ASSERT_WARNING(szFunctionSignature != null_z, "The function signature cannot be empty.");
}

CallTrace::CallTrace(const char* szFunctionSignature, const ArgumentTrace* arArgumentTraces, const unsigned int uNumberOfArguments, const char* szClassName) : 
                                                                                                                        m_szFunctionSignature(szFunctionSignature),
                                                                                                                        m_arArgumentTraces(arArgumentTraces),
                                                                                                                        m_uNumberOfArguments(uNumberOfArguments),
                                                                                                                        m_szClassName(szClassName),
                                                                                                                        m_strObjectState(string_z::GetEmpty())
{
    Z_ASSERT_WARNING(!(arArgumentTraces == null_z && uNumberOfArguments > 0), "The number of arguments cannot be greater than zero if the argument array is null.");
    Z_ASSERT_WARNING(!(arArgumentTraces != null_z && uNumberOfArguments == 0), "The number of arguments cannot be zero if the argument array is not null.");
    Z_ASSERT_WARNING(szFunctionSignature != null_z, "The function signature cannot be empty.");
    Z_ASSERT_WARNING(szClassName != null_z, "The class name cannot be empty.");
}

CallTrace::CallTrace(const char* szFunctionSignature, const ArgumentTrace* arArgumentTraces, const unsigned int uNumberOfArguments, const char* szClassName, const string_z& strObjectState) : 
                                                                                                                        m_szFunctionSignature(szFunctionSignature),
                                                                                                                        m_arArgumentTraces(arArgumentTraces),
                                                                                                                        m_uNumberOfArguments(uNumberOfArguments),
                                                                                                                        m_szClassName(szClassName),
                                                                                                                        m_strObjectState(strObjectState)
{
    Z_ASSERT_WARNING(!(arArgumentTraces == null_z && uNumberOfArguments > 0), "The number of arguments cannot be greater than zero if the argument array is null.");
    Z_ASSERT_WARNING(!(arArgumentTraces != null_z && uNumberOfArguments == 0), "The number of arguments cannot be zero if the argument array is not null.");
    Z_ASSERT_WARNING(szFunctionSignature != null_z, "The function signature cannot be empty.");
    Z_ASSERT_WARNING(szClassName != null_z, "The class name cannot be empty.");
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |         PROPERTIES         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################
 
const char* CallTrace::GetFunctionSignature() const
{
    return m_szFunctionSignature;
}

const ArgumentTrace* CallTrace::GetArguments() const
{
    return m_arArgumentTraces;
}

unsigned int CallTrace::GetArgumentsCount() const
{
    return m_uNumberOfArguments;
}

const char* CallTrace::GetClassName() const
{
    return m_szClassName;
}

const string_z& CallTrace::GetObjectState() const
{
    return m_strObjectState;
}


} // namespace z
