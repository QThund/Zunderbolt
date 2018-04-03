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

#include "ZDiagnosis/CallStackTracer.h"

#include "ZThreading/SThisThread.h"
#include "ZThreading/ScopedExclusiveLock.h"
#include "ZThreading/ScopedSharedLock.h"

#ifdef GetPrinter // On Windows, the API maps the GetPrinter definition to either GetPrinterA or GetPrinterW function names, which prevents the GetPrinter method from being declared
    #undef GetPrinter
#endif
#ifdef SetPrinter // On Windows, the API maps the SetPrinter definition to either SetPrinterA or SetPrinterW function names, which prevents the SetPrinter method from being declared
    #undef SetPrinter
#endif

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

CallStackTracer::CallStackTracer() : m_pPrinter((AbstractCallStackTracePrinter*)null_z)
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

CallStackTracer* CallStackTracer::Get()
{
    static CallStackTracer callStackTracerInstance;

    return &callStackTracerInstance;
}

void CallStackTracer::AddTrace(const CallTrace &trace)
{
    Thread::Id threadId = SThisThread::GetId();

    // ---------- Critical section -----------
    {
        ScopedExclusiveLock<SharedMutex> exclusiveLock(m_callStackTracesMutex);

        CallStackTraceContainer::ConstIterator itCallStackTrace = m_callStackTraces.PositionOfKey(threadId);

        const bool CALLSTACKTRACE_DOES_NOT_EXIST = itCallStackTrace.IsEnd();

        if(CALLSTACKTRACE_DOES_NOT_EXIST)
        {
            // Creates a new call stack trace
            CallStackTrace* pNewCallStackTrace = new CallStackTrace(SThisThread::ToString());
            itCallStackTrace = m_callStackTraces.Add(threadId, pNewCallStackTrace);
        }

        itCallStackTrace->GetValue()->Push(trace);

    } // --------- Critical section ----------
}

void CallStackTracer::RemoveLastTrace()
{
    Thread::Id threadId = SThisThread::GetId();

    // ---------- Critical section -----------
    {
        ScopedExclusiveLock<SharedMutex> exclusiveLock(m_callStackTracesMutex);
        CallStackTraceContainer::ConstIterator itCallStackTrace = m_callStackTraces.PositionOfKey(threadId);
        itCallStackTrace->GetValue()->Pop();

        // If there are no more traces in the call stack of the current thread, the stack is completely removed
        if(itCallStackTrace->GetValue()->GetCount() == 0)
            m_callStackTraces.Remove(itCallStackTrace);

    } // --------- Critical section ----------
}

void CallStackTracer::Dump()
{
    if(m_pPrinter != null_z)
    {
        Thread::Id threadId = SThisThread::GetId();

        // ---------- Critical section -----------
        {
            ScopedSharedLock<SharedMutex> sharedLock(m_callStackTracesMutex);

            CallStackTraceContainer::ConstIterator itCallStackTrace = m_callStackTraces.PositionOfKey(threadId);
            const bool CALLSTACKTRACE_EXISTS = !itCallStackTrace.IsEnd();

            if(CALLSTACKTRACE_EXISTS)
                m_pPrinter->PrintCallStackTrace(*itCallStackTrace->GetValue());

        } // --------- Critical section ----------
    }
    else
    {
        static const string_z NO_TRACES_MESSAGE1("There are no call stack traces for the current thread (");
        static const string_z NO_TRACES_MESSAGE2(").");
        m_pPrinter->PrintString(NO_TRACES_MESSAGE1 + SThisThread::ToString() + NO_TRACES_MESSAGE2);
    }
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |         PROPERTIES         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

boost::shared_ptr<AbstractCallStackTracePrinter> CallStackTracer::GetPrinter() const
{
    boost::shared_ptr<AbstractCallStackTracePrinter> pPrinter;

    // ---------- Critical section -----------
    {
        ScopedSharedLock<SharedMutex> sharedLock(m_printerMutex);

        pPrinter = m_pPrinter;

    } // ---------- Critical section -----------

    return pPrinter;
}

void CallStackTracer::SetPrinter(const boost::shared_ptr<AbstractCallStackTracePrinter> &pPrinter)
{
    // ---------- Critical section -----------
    {
        ScopedExclusiveLock<SharedMutex> exclusiveLock(m_printerMutex);
        m_pPrinter = pPrinter;

    } // ---------- Critical section -----------
}

void CallStackTracer::SetPrinter(AbstractCallStackTracePrinter* pPrinter)
{
    this->SetPrinter(boost::shared_ptr<AbstractCallStackTracePrinter>(pPrinter));
}

} // namespace z
