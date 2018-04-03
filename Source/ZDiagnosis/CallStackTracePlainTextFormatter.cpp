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

#include "Zdiagnosis/CallStackTracePlainTextFormatter.h"

#include "ZCommon/DataTypes/SInteger.h"


namespace z
{

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |  ATTRIBUTES INITIALIZATION |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

Z_RTTI_SUPPORT_TYPE_DEFINITION(CallStackTracePlainTextFormatter);
    

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |          DESTRUCTOR        |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

CallStackTracePlainTextFormatter::~CallStackTracePlainTextFormatter()
{
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

void CallStackTracePlainTextFormatter::FormatCallStackTraceFooter(const CallStackTrace &trace, string_z &strFormattedTrace) const
{
    static const string_z FOOTER("End of call stack trace information.\n");
    strFormattedTrace.Append(FOOTER);
}

void CallStackTracePlainTextFormatter::FormatCallStackTraceHeader(const CallStackTrace &trace, string_z &strFormattedTrace) const
{
    static const string_z HEADER("Call stack trace for ");
    static const string_z NEW_LINE("\n");

    strFormattedTrace.Append(HEADER);
    strFormattedTrace.Append(trace.GetThreadId());
    strFormattedTrace.Append(NEW_LINE);
}

void CallStackTracePlainTextFormatter::FormatCallTrace(const CallTrace &trace, const unsigned int uDepthLevel, string_z &strFormattedTrace) const
{
    static const string_z ONE_LEVEL("  ");
    string_z strIndentation;
    for(unsigned int i = 0; i < uDepthLevel; ++i)
        strIndentation.Append(ONE_LEVEL);

    static const string_z NEW_LINE("\n");
    strFormattedTrace.Append(trace.GetFunctionSignature());
    strFormattedTrace.Append(NEW_LINE);

    static const string_z ARGUMENT_PREFIX1("  | -{");
    static const string_z ARGUMENT_PREFIX2("}");
    static const string_z EUAL_SIGN("=");
    const ArgumentTrace* arArguments = trace.GetArguments();

    for(unsigned int i = 0; i < trace.GetArgumentsCount(); ++i)
    {
        strFormattedTrace.Append(strIndentation);
        strFormattedTrace.Append(ARGUMENT_PREFIX1);
        strFormattedTrace.Append(string_z::FromInteger(i));
        strFormattedTrace.Append(ARGUMENT_PREFIX2);
        strFormattedTrace.Append(arArguments[i].GetTypeName());
        strFormattedTrace.Append(EUAL_SIGN);
        strFormattedTrace.Append(arArguments[i].GetValue());
        strFormattedTrace.Append(NEW_LINE);
    }
}

void CallStackTracePlainTextFormatter::FormatCallTraceFooter(const CallTrace &trace, const unsigned int uDepthLevel, string_z &strFormattedTrace) const
{
    // Nothing
}

void CallStackTracePlainTextFormatter::FormatCallTraceHeader(const CallTrace &trace, const unsigned int uDepthLevel, string_z &strFormattedTrace) const
{
    static const string_z HEADER("-->");
    static const string_z ONE_LEVEL("  ");

    for(unsigned int i = 0; i < uDepthLevel; ++i)
        strFormattedTrace.Append(ONE_LEVEL);

    strFormattedTrace.Append(HEADER);
}

string_z CallStackTracePlainTextFormatter::ToString() const
{
    static const string_z CLASS_NAME("CallStackTracePlainTextFormatter");
    return CLASS_NAME;
}

} // namespace z
