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

#include <boost/test/auto_unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
using namespace boost::unit_test;

#include "../../testsystem/TestingExternalDefinitions.h"

#include "ZContainers/Event.h"

#include "ZCommon/Exceptions/AssertException.h"


class Event_TestClass
{
public:

    Event_TestClass() : m_bMethodCalled(false)
    {
    }

    static void Reset()
    {
        sm_bFunction0Called = false;
        sm_bFunction1Called = false;
        sm_bFunction2Called = false;
        sm_bFunction3Called = false;
        sm_bFunction4Called = false;
        sm_bFunction5Called = false;
        sm_bFunction6Called = false;
        sm_bFunction7Called = false;
        sm_bFunction8Called = false;
        sm_bFunction1ArgumentsAreCorrect = false;
        sm_bFunction2ArgumentsAreCorrect = false;
        sm_bFunction3ArgumentsAreCorrect = false;
        sm_bFunction4ArgumentsAreCorrect = false;
        sm_bFunction5ArgumentsAreCorrect = false;
        sm_bFunction6ArgumentsAreCorrect = false;
        sm_bFunction7ArgumentsAreCorrect = false;
        sm_bFunction8ArgumentsAreCorrect = false;
        sm_bSubscriberAreCalledInFIFOOrder = false;
        sm_uCallCounter = 0;
        sm_bSameInstancePassedToAllSubscribers = false;
    }

    int Method0()
    {
        m_bMethodCalled = true;
        return 0;
    }

    static int FunctionA(int &p1)
    {
        sm_bSameInstancePassedToAllSubscribers = p1 == 1;
        ++p1;
        return 1;
    }

    static int FunctionB(int &p1)
    {
        sm_bSameInstancePassedToAllSubscribers = sm_bSameInstancePassedToAllSubscribers && p1 == 2;
        ++p1;
        return 1;
    }
    
    static int FunctionC(int &p1)
    {
        sm_bSameInstancePassedToAllSubscribers = sm_bSameInstancePassedToAllSubscribers && p1 == 3;
        ++p1;
        return 1;
    }
    
    static int FunctionD(int p1)
    {
        sm_bSubscriberAreCalledInFIFOOrder = sm_uCallCounter == 0;
        ++sm_uCallCounter;
        return 1;
    }

    static int FunctionE(int p1)
    {
        sm_bSubscriberAreCalledInFIFOOrder = sm_bSubscriberAreCalledInFIFOOrder && sm_uCallCounter == 1;
        ++sm_uCallCounter;
        return 1;
    }
    
    static int FunctionF(int p1)
    {
        sm_bSubscriberAreCalledInFIFOOrder = sm_bSubscriberAreCalledInFIFOOrder && sm_uCallCounter == 2;
        ++sm_uCallCounter;
        return 1;
    }

    static int Function0()
    {
        sm_bFunction0Called = true;
        return 0;
    }
    
    static int Function1(int p1)
    {
        sm_bFunction1Called = true;
        sm_bFunction1ArgumentsAreCorrect = p1 == 1;
        return 1;
    }
    
    static int Function2(int p1, int p2)
    {
        sm_bFunction2Called = true;
        sm_bFunction2ArgumentsAreCorrect = p1 == 1 && p2 == 2;
        return 2;
    }
    
    static int Function3(int p1, int p2, int p3)
    {
        sm_bFunction3Called = true;
        sm_bFunction3ArgumentsAreCorrect = p1 == 1 && p2 == 2 && p3 == 3;
        return 3;
    }
    
    static int Function4(int p1, int p2, int p3, int p4)
    {
        sm_bFunction4Called = true;
        sm_bFunction4ArgumentsAreCorrect = p1 == 1 && p2 == 2 && p3 == 3 && p4 == 4;
        return 4;
    }
    
    static int Function5(int p1, int p2, int p3, int p4, int p5)
    {
        sm_bFunction5Called = true;
        sm_bFunction5ArgumentsAreCorrect = p1 == 1 && p2 == 2 && p3 == 3 && p4 == 4 && p5 == 5;
        return 5;
    }
    
    static int Function6(int p1, int p2, int p3, int p4, int p5, int p6)
    {
        sm_bFunction6Called = true;
        sm_bFunction6ArgumentsAreCorrect = p1 == 1 && p2 == 2 && p3 == 3 && p4 == 4 && p5 == 5 && p6 == 6;
        return 6;
    }
    
    static int Function7(int p1, int p2, int p3, int p4, int p5, int p6, int p7)
    {
        sm_bFunction7Called = true;
        sm_bFunction7ArgumentsAreCorrect = p1 == 1 && p2 == 2 && p3 == 3 && p4 == 4 && p5 == 5 && p6 == 6 && p7 == 7;
        return 7;
    }
    
    static int Function8(int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8)
    {
        sm_bFunction8Called = true;
        sm_bFunction8ArgumentsAreCorrect = p1 == 1 && p2 == 2 && p3 == 3 && p4 == 4 && p5 == 5 && p6 == 6 && p7 == 7 && p8 == 8;
        return 8;
    }

    static bool sm_bFunction0Called;
    static bool sm_bFunction1Called;
    static bool sm_bFunction2Called;
    static bool sm_bFunction3Called;
    static bool sm_bFunction4Called;
    static bool sm_bFunction5Called;
    static bool sm_bFunction6Called;
    static bool sm_bFunction7Called;
    static bool sm_bFunction8Called;
    static bool sm_bFunction1ArgumentsAreCorrect;
    static bool sm_bFunction2ArgumentsAreCorrect;
    static bool sm_bFunction3ArgumentsAreCorrect;
    static bool sm_bFunction4ArgumentsAreCorrect;
    static bool sm_bFunction5ArgumentsAreCorrect;
    static bool sm_bFunction6ArgumentsAreCorrect;
    static bool sm_bFunction7ArgumentsAreCorrect;
    static bool sm_bFunction8ArgumentsAreCorrect;
    static bool sm_bSubscriberAreCalledInFIFOOrder;
    static bool sm_bSameInstancePassedToAllSubscribers;
    static unsigned int sm_uCallCounter;
    bool m_bMethodCalled;

};

bool Event_TestClass::sm_bFunction0Called = false;
bool Event_TestClass::sm_bFunction1Called = false;
bool Event_TestClass::sm_bFunction2Called = false;
bool Event_TestClass::sm_bFunction3Called = false;
bool Event_TestClass::sm_bFunction4Called = false;
bool Event_TestClass::sm_bFunction5Called = false;
bool Event_TestClass::sm_bFunction6Called = false;
bool Event_TestClass::sm_bFunction7Called = false;
bool Event_TestClass::sm_bFunction8Called = false;
bool Event_TestClass::sm_bFunction1ArgumentsAreCorrect = false;
bool Event_TestClass::sm_bFunction2ArgumentsAreCorrect = false;
bool Event_TestClass::sm_bFunction3ArgumentsAreCorrect = false;
bool Event_TestClass::sm_bFunction4ArgumentsAreCorrect = false;
bool Event_TestClass::sm_bFunction5ArgumentsAreCorrect = false;
bool Event_TestClass::sm_bFunction6ArgumentsAreCorrect = false;
bool Event_TestClass::sm_bFunction7ArgumentsAreCorrect = false;
bool Event_TestClass::sm_bFunction8ArgumentsAreCorrect = false;
bool Event_TestClass::sm_bSubscriberAreCalledInFIFOOrder = false;
bool Event_TestClass::sm_bSameInstancePassedToAllSubscribers = false;
unsigned int Event_TestClass::sm_uCallCounter = 0;



ZTEST_SUITE_BEGIN( Event_TestSuite )

/// <summary>
/// Checks that a single subscriber without parameters is called.
/// </summary>
ZTEST_CASE ( Raise_SingleSubscriberWithoutParametersIsCalled_Test )
{
    // [Preparation]
    Event<int()> event;
    event += Event_TestClass::Function0;
    Event_TestClass::Reset();

    // [Execution]
    event.Raise();

    // [Verification]
    BOOST_CHECK(Event_TestClass::sm_bFunction0Called);
}

/// <summary>
/// Checks that a single subscriber with 1 parameter is called.
/// </summary>
ZTEST_CASE ( Raise_SingleSubscriberWith1ParameterIsCalled_Test )
{
    // [Preparation]
    Event<int(int)> event;
    event += Event_TestClass::Function1;
    Event_TestClass::Reset();

    // [Execution]
    event.Raise(1);

    // [Verification]
    BOOST_CHECK(Event_TestClass::sm_bFunction1Called);
}

/// <summary>
/// Checks that a single subscriber with 2 parameters is called.
/// </summary>
ZTEST_CASE ( Raise_SingleSubscriberWith2ParametersIsCalled_Test )
{
    // [Preparation]
    Event<int(int, int)> event;
    event += Event_TestClass::Function2;
    Event_TestClass::Reset();

    // [Execution]
    event.Raise(1, 2);

    // [Verification]
    BOOST_CHECK(Event_TestClass::sm_bFunction2Called);
}

/// <summary>
/// Checks that a single subscriber with 3 parameters is called.
/// </summary>
ZTEST_CASE ( Raise_SingleSubscriberWith3ParametersIsCalled_Test )
{
    // [Preparation]
    Event<int(int, int, int)> event;
    event += Event_TestClass::Function3;
    Event_TestClass::Reset();

    // [Execution]
    event.Raise(1, 2, 3);

    // [Verification]
    BOOST_CHECK(Event_TestClass::sm_bFunction3Called);
}

/// <summary>
/// Checks that a single subscriber with 4 parameters is called.
/// </summary>
ZTEST_CASE ( Raise_SingleSubscriberWith4ParametersIsCalled_Test )
{
    // [Preparation]
    Event<int(int, int, int, int)> event;
    event += Event_TestClass::Function4;
    Event_TestClass::Reset();

    // [Execution]
    event.Raise(1, 2, 3, 4);

    // [Verification]
    BOOST_CHECK(Event_TestClass::sm_bFunction4Called);
}

/// <summary>
/// Checks that a single subscriber with 5 parameters is called.
/// </summary>
ZTEST_CASE ( Raise_SingleSubscriberWith5ParametersIsCalled_Test )
{
    // [Preparation]
    Event<int(int, int, int, int, int)> event;
    event += Event_TestClass::Function5;
    Event_TestClass::Reset();

    // [Execution]
    event.Raise(1, 2, 3, 4, 5);

    // [Verification]
    BOOST_CHECK(Event_TestClass::sm_bFunction5Called);
}

/// <summary>
/// Checks that a single subscriber with 6 parameters is called.
/// </summary>
ZTEST_CASE ( Raise_SingleSubscriberWith6ParametersIsCalled_Test )
{
    // [Preparation]
    Event<int(int, int, int, int, int, int)> event;
    event += Event_TestClass::Function6;
    Event_TestClass::Reset();

    // [Execution]
    event.Raise(1, 2, 3, 4, 5, 6);

    // [Verification]
    BOOST_CHECK(Event_TestClass::sm_bFunction6Called);
}

/// <summary>
/// Checks that a single subscriber with 7 parameters is called.
/// </summary>
ZTEST_CASE ( Raise_SingleSubscriberWith7ParametersIsCalled_Test )
{
    // [Preparation]
    Event<int(int, int, int, int, int, int, int)> event;
    event += Event_TestClass::Function7;
    Event_TestClass::Reset();

    // [Execution]
    event.Raise(1, 2, 3, 4, 5, 6, 7);

    // [Verification]
    BOOST_CHECK(Event_TestClass::sm_bFunction7Called);
}

/// <summary>
/// Checks that a single subscriber with 8 parameters is called.
/// </summary>
ZTEST_CASE ( Raise_SingleSubscriberWith8ParametersIsCalled_Test )
{
    // [Preparation]
    Event<int(int, int, int, int, int, int, int, int)> event;
    event += Event_TestClass::Function8;
    Event_TestClass::Reset();

    // [Execution]
    event.Raise(1, 2, 3, 4, 5, 6, 7, 8);

    // [Verification]
    BOOST_CHECK(Event_TestClass::sm_bFunction8Called);
}

/// <summary>
/// Checks that all the arguments are correctly passed to a subscriber that receives 1 parameter.
/// </summary>
ZTEST_CASE ( Raise_ArgumentsAreCorrectlyPassedWhenFunctionHas1Parameter_Test )
{
    // [Preparation]
    Event<int(int)> event;
    event += Event_TestClass::Function1;
    Event_TestClass::Reset();

    // [Execution]
    event.Raise(1);

    // [Verification]
    BOOST_CHECK(Event_TestClass::sm_bFunction1ArgumentsAreCorrect);
}

/// <summary>
/// Checks that all the arguments are correctly passed to a subscriber that receives 2 parameters.
/// </summary>
ZTEST_CASE ( Raise_ArgumentsAreCorrectlyPassedWhenFunctionHas2Parameters_Test )
{
    // [Preparation]
    Event<int(int, int)> event;
    event += Event_TestClass::Function2;
    Event_TestClass::Reset();

    // [Execution]
    event.Raise(1, 2);

    // [Verification]
    BOOST_CHECK(Event_TestClass::sm_bFunction2ArgumentsAreCorrect);
}

/// <summary>
/// Checks that all the arguments are correctly passed to a subscriber that receives 3 parameters.
/// </summary>
ZTEST_CASE ( Raise_ArgumentsAreCorrectlyPassedWhenFunctionHas3Parameters_Test )
{
    // [Preparation]
    Event<int(int, int, int)> event;
    event += Event_TestClass::Function3;
    Event_TestClass::Reset();

    // [Execution]
    event.Raise(1, 2, 3);

    // [Verification]
    BOOST_CHECK(Event_TestClass::sm_bFunction3ArgumentsAreCorrect);
}

/// <summary>
/// Checks that all the arguments are correctly passed to a subscriber that receives 4 parameters.
/// </summary>
ZTEST_CASE ( Raise_ArgumentsAreCorrectlyPassedWhenFunctionHas4Parameters_Test )
{
    // [Preparation]
    Event<int(int, int, int, int)> event;
    event += Event_TestClass::Function4;
    Event_TestClass::Reset();

    // [Execution]
    event.Raise(1, 2, 3, 4);

    // [Verification]
    BOOST_CHECK(Event_TestClass::sm_bFunction4ArgumentsAreCorrect);
}

/// <summary>
/// Checks that all the arguments are correctly passed to a subscriber that receives 5 parameters.
/// </summary>
ZTEST_CASE ( Raise_ArgumentsAreCorrectlyPassedWhenFunctionHas5Parameters_Test )
{
    // [Preparation]
    Event<int(int, int, int, int, int)> event;
    event += Event_TestClass::Function5;
    Event_TestClass::Reset();

    // [Execution]
    event.Raise(1, 2, 3, 4, 5);

    // [Verification]
    BOOST_CHECK(Event_TestClass::sm_bFunction5ArgumentsAreCorrect);
}

/// <summary>
/// Checks that all the arguments are correctly passed to a subscriber that receives 6 parameters.
/// </summary>
ZTEST_CASE ( Raise_ArgumentsAreCorrectlyPassedWhenFunctionHas6Parameters_Test )
{
    // [Preparation]
    Event<int(int, int, int, int, int, int)> event;
    event += Event_TestClass::Function6;
    Event_TestClass::Reset();

    // [Execution]
    event.Raise(1, 2, 3, 4, 5, 6);

    // [Verification]
    BOOST_CHECK(Event_TestClass::sm_bFunction6ArgumentsAreCorrect);
}

/// <summary>
/// Checks that all the arguments are correctly passed to a subscriber that receives 7 parameters.
/// </summary>
ZTEST_CASE ( Raise_ArgumentsAreCorrectlyPassedWhenFunctionHas7Parameters_Test )
{
    // [Preparation]
    Event<int(int, int, int, int, int, int, int)> event;
    event += Event_TestClass::Function7;
    Event_TestClass::Reset();

    // [Execution]
    event.Raise(1, 2, 3, 4, 5, 6, 7);

    // [Verification]
    BOOST_CHECK(Event_TestClass::sm_bFunction7ArgumentsAreCorrect);
}

/// <summary>
/// Checks that all the arguments are correctly passed to a subscriber that receives 8 parameters.
/// </summary>
ZTEST_CASE ( Raise_ArgumentsAreCorrectlyPassedWhenFunctionHas8Parameters_Test )
{
    // [Preparation]
    Event<int(int, int, int, int, int, int, int, int)> event;
    event += Event_TestClass::Function8;
    Event_TestClass::Reset();

    // [Execution]
    event.Raise(1, 2, 3, 4, 5, 6, 7, 8);

    // [Verification]
    BOOST_CHECK(Event_TestClass::sm_bFunction8ArgumentsAreCorrect);
}

/// <summary>
/// Checks that the same instance is passed to every subscriber.
/// </summary>
ZTEST_CASE ( Raise_SameInstanceOfArgumentIsPassedToEverySubscriber_Test )
{
    // [Preparation]
    Event<int(int&)> event;
    event += Event_TestClass::FunctionA;
    event += Event_TestClass::FunctionB;
    event += Event_TestClass::FunctionC;
    Event_TestClass::Reset();
    int nArgument = 1;

    // [Execution]
    event.Raise(nArgument);

    // [Verification]
    BOOST_CHECK(Event_TestClass::sm_bSameInstancePassedToAllSubscribers);
}

/// <summary>
/// Checks that all the subscribers are called in FIFO order.
/// </summary>
ZTEST_CASE ( Raise_SubscribersAreCalledInFifoOrder_Test )
{
    // [Preparation]
    Event<int(int)> event;
    event += Event_TestClass::FunctionD;
    event += Event_TestClass::FunctionE;
    event += Event_TestClass::FunctionF;
    Event_TestClass::Reset();
    int nArgument = 1;

    // [Execution]
    event.Raise(nArgument);

    // [Verification]
    BOOST_CHECK(Event_TestClass::sm_bSubscriberAreCalledInFIFOOrder);
}

/// <summary>
/// Checks that the method of the correct object is called.
/// </summary>
ZTEST_CASE ( Raise_MethodOfCorrectObjectIsCalled_Test )
{
    // [Preparation]
    Event_TestClass testClass;
    Event<int()> event;
    event += Event<int()>::Subscriber(&testClass, &Event_TestClass::Method0);
    Event_TestClass::Reset();

    // [Execution]
    event.Raise();

    // [Verification]
    BOOST_CHECK(testClass.m_bMethodCalled);
}

/// <summary>
/// Checks that the method of every object is called.
/// </summary>
ZTEST_CASE ( Raise_MethodOfAllObjectsIsCalled_Test )
{
    // [Preparation]
    Event_TestClass testClass1;
    Event_TestClass testClass2;
    Event_TestClass testClass3;
    Event<int()> event;
    event += Event<int()>::Subscriber(&testClass1, &Event_TestClass::Method0);
    event += Event<int()>::Subscriber(&testClass2, &Event_TestClass::Method0);
    event += Event<int()>::Subscriber(&testClass3, &Event_TestClass::Method0);
    Event_TestClass::Reset();

    // [Execution]
    event.Raise();

    // [Verification]
    BOOST_CHECK(testClass1.m_bMethodCalled);
    BOOST_CHECK(testClass2.m_bMethodCalled);
    BOOST_CHECK(testClass3.m_bMethodCalled);
}

/// <summary>
/// Checks that subscribers are added.
/// </summary>
ZTEST_CASE ( OperatorAdditionAssignment_SubscriberIsAdded_Test )
{
    // [Preparation]
    Event<int()> event;
    Event_TestClass::Reset();

    // [Execution]
    event += &Event_TestClass::Function0;

    // [Verification]
    bool bSubscriberIsAdded = event.GetSubscribers().GetCount() > 0;
    BOOST_CHECK(bSubscriberIsAdded);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input is null.
/// </summary>
ZTEST_CASE ( OperatorAdditionAssignment_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    Event<int()> event;
    Event_TestClass::Reset();

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        event += null_z;
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that an assertion fails when subscriber was already there.
/// </summary>
ZTEST_CASE ( OperatorAdditionAssignment_AssertionFailsWhenSubscriberWasAlreadySubscribed_Test )
{
    // [Preparation]
    Event<int()> event;
    Event_TestClass::Reset();
    event += &Event_TestClass::Function0;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        event += &Event_TestClass::Function0;
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif

/// <summary>
/// Checks that subscribers are removed.
/// </summary>
ZTEST_CASE ( OperatorSubstractionAssignment_SubscriberIsRemoved_Test )
{
    // [Preparation]
    Event<int()> event;
    Event_TestClass::Reset();
    event += &Event_TestClass::Function0;

    // [Execution]
    event -= &Event_TestClass::Function0;

    // [Verification]
    bool bSubscriberIsRemoved = event.GetSubscribers().GetCount() == 0;
    BOOST_CHECK(bSubscriberIsRemoved);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input is null.
/// </summary>
ZTEST_CASE ( OperatorSubstractionAssignment_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    Event<int()> event;
    Event_TestClass::Reset();

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        event -= null_z;
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that an assertion fails when subscriber was not subscribed.
/// </summary>
ZTEST_CASE ( OperatorSubstractionAssignment_AssertionFailsWhenSubscriberWasNotSubscribed_Test )
{
    // [Preparation]
    Event<int()> event;
    Event_TestClass::Reset();

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        event -= &Event_TestClass::Function0;
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif

/// <summary>
/// Checks that subscribers are removed.
/// </summary>
ZTEST_CASE ( UnsubscribeAll_AllSubscribersAreUnsubscribed_Test )
{
    // [Preparation]
    Event<int(int&)> event;
    Event_TestClass::Reset();
    event += &Event_TestClass::FunctionA;
    event += &Event_TestClass::FunctionB;
    event += &Event_TestClass::FunctionC;

    // [Execution]
    event.UnsubscribeAll();

    // [Verification]
    bool bSubscriberIsRemoved = event.GetSubscribers().GetCount() == 0;
    BOOST_CHECK(bSubscriberIsRemoved);
}


// End - Test Suite: Event
ZTEST_SUITE_END()
