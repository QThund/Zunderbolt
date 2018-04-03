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

#ifndef __ABSTRACTCALLSTACKTRACEPRINTERMOCK__
#define __ABSTRACTCALLSTACKTRACEPRINTERMOCK__

#include "ZDiagnosis/AbstractCallStackTracePrinter.h"


namespace z
{
namespace Test
{

/// <summary>
/// Sends the printed text to a string so it can be compared in unit tests.
/// </summary>
class AbstractCallStackTracePrinterMock : public AbstractCallStackTracePrinter
{

    Z_RTTI_SUPPORT_DERIVED_FROM_1_CLASS(AbstractCallStackTracePrinterMock, AbstractCallStackTracePrinter);
    

    // CONSTRUCTORS
	// ---------------
public:

    AbstractCallStackTracePrinterMock()
    {
    }

    AbstractCallStackTracePrinterMock(ICallStackTraceFormatter* pFormatter)
    {
        m_pFormatter = boost::shared_ptr<ICallStackTraceFormatter>(pFormatter);
    }


    // METHODS
	// ---------------
public:

    // Implementation that prints the text to a string
    void PrintString(const string_z &strText)
    {
        m_strPrintedText.Append(strText);
    }

    string_z GetPrintedText() const
    {
        return m_strPrintedText;
    }
    
    void ClearPrintedText()
    {
        m_strPrintedText = string_z::GetEmpty();
    }

    string_z ToString() const
    {
        return "";
    }


    // ATTRIBUTES
	// ---------------
private:

    string_z m_strPrintedText;
};


} // namespace Test
} // namespace z


#endif // __ABSTRACTCALLSTACKTRACEPRINTERMOCK__
