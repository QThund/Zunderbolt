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

#include "ZDiagnosis/AbstractCallStackTracePrinter.h"


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

Z_RTTI_SUPPORT_TYPE_DEFINITION(AbstractCallStackTracePrinter);


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |       CONSTRUCTORS         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

AbstractCallStackTracePrinter::AbstractCallStackTracePrinter() : m_pFormatter((ICallStackTraceFormatter*)null_z)
{
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |          DESTRUCTOR        |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

AbstractCallStackTracePrinter::~AbstractCallStackTracePrinter()
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

void AbstractCallStackTracePrinter::PrintCallStackTrace(const CallStackTrace &callStackTrace)
{
    static const string_z NEW_LINE("\n");

    string_z strTextToPrint;
    m_pFormatter->FormatCallStackTraceHeader(callStackTrace, strTextToPrint);
    
    for(puint_z i = 0; i < callStackTrace.GetCount(); ++i)
    {
        m_pFormatter->FormatCallTraceHeader(callStackTrace.GetTrace(i), scast_z(i, unsigned int), strTextToPrint);
        m_pFormatter->FormatCallTrace(callStackTrace.GetTrace(i), scast_z(i, unsigned int), strTextToPrint);
        m_pFormatter->FormatCallTraceFooter(callStackTrace.GetTrace(i), scast_z(i, unsigned int), strTextToPrint);
    }

    m_pFormatter->FormatCallStackTraceFooter(callStackTrace, strTextToPrint);
    this->PrintString(strTextToPrint);
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |         PROPERTIES         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

void AbstractCallStackTracePrinter::SetFormatter(ICallStackTraceFormatter* pFormatter)
{
    m_pFormatter = boost::shared_ptr<ICallStackTraceFormatter>(pFormatter);
}

void AbstractCallStackTracePrinter::SetFormatter(boost::shared_ptr<ICallStackTraceFormatter> &pFormatter)
{
    m_pFormatter = pFormatter;
}

boost::shared_ptr<ICallStackTraceFormatter> AbstractCallStackTracePrinter::GetFormatter() const
{
    return m_pFormatter;
}


} // namespace z
