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

#ifndef __EVENT__
#define __EVENT__

#include "ZContainers/ContainersModuleDefinitions.h"
#include "ZContainers/ArrayDynamic.h"
#include "ZCommon/Delegate.h"
#include "ZContainers/SEqualityComparator.h"


namespace z
{

/// <summary>
/// Represents an event to which other components can subscribe. When an event is raised, all the 
/// functions subscribed to it will be called using the arguments passed by the caller.
/// </summary>
/// <remarks>
/// Recommended function signatures for event subscribers are:<br/>
/// void f(arguments in an structure)<br/>
/// void f(publisher object, arguments in an structure)
/// </remarks>
/// <typeparam name="FunctionSignatureT">The signature of the functions that subscribe to the event.</typeparam>
template<typename FunctionSignatureT>
class Event;


/// <summary>
/// Represents an event to which other components can subscribe. When an event is raised, all the 
/// functions subscribed to it will be called using the arguments passed by the caller.
/// </summary>
/// <remarks>
/// Recommended function signatures for event subscribers are:<br/>
/// void f(arguments in an structure)<br/>
/// void f(publisher object, arguments in an structure)
/// </remarks>
/// <typeparam name="ReturnValueT">The return type of the functions that subscribe to the event.</typeparam>
template<class ReturnValueT>
class Event< ReturnValueT(void) >
{
    // TYPEDEFS
    // ---------------
public:

    typedef ReturnValueT(FunctionSignatureT)();
    typedef Delegate<FunctionSignatureT> Subscriber;
    typedef ArrayDynamic<Subscriber, 
                                                                     PoolAllocator, 
                                                                     SEqualityComparator<Subscriber> > 
                                                                        SubscriberArray;

    // [TODO] Thund: It may be useful to print a trace when the instance is destroyed while one or more functions are still subscribed.

    // METHODS
    // ---------------
public:

    /// <summary>
    /// Calls every subscribed function in FIFO order, passing them the same instance of the provided arguments if any.
    /// </summary>
    void Raise() const
    {
        const puint_z COUNT = m_arSubscribers.GetCount();

        for(puint_z i = 0; i < COUNT; ++i)
            m_arSubscribers[i]();
    }
    
    /// <summary>
    /// Subscribes a function to the event.
    /// </summary>
    /// <param name="subscriber">[IN] A function to subscribe. It should not be already subscribed. It must not be null.</param>
    void operator+=(const Subscriber &subscriber)
    {
        Z_ASSERT_WARNING(!m_arSubscribers.Contains(subscriber), "The input function is already subscribed to the event.");
        Z_ASSERT_ERROR(!subscriber.IsNull(), "The input function must not be null.");

        m_arSubscribers.Add(subscriber);
    }
    
    /// <summary>
    /// Unsubscribes a function from the event.
    /// </summary>
    /// <param name="subscriber">[IN] A function to unsubscribe. It must be already subscribed. It must not be null.</param>
    void operator-=(const Subscriber &subscriber)
    {
        Z_ASSERT_ERROR(!subscriber.IsNull(), "The input function must not be null.");

        puint_z uIndex = m_arSubscribers.IndexOf(subscriber);

        Z_ASSERT_WARNING(uIndex != SubscriberArray::ELEMENT_NOT_FOUND, "The input function cannot be removed, it is not subscribed to the event.");

        if(uIndex != SubscriberArray::ELEMENT_NOT_FOUND)
            m_arSubscribers.Remove(uIndex);
    }

    /// <summary>
    /// Unsubscribes all the subscribed functions.
    /// </summary>
    void UnsubscribeAll()
    {
        m_arSubscribers.Clear();
    }


    // PROPERTIES
    // ---------------
public:
    
    /// <summary>
    /// Gets the entire list of subscribed functions.
    /// </summary>
    /// <returns>
    /// A list of subscribed functions.
    /// </returns>
    SubscriberArray GetSubscribers() const
    {
        return m_arSubscribers;
    }


    // ATTRIBUTES
    // ---------------
protected:

    /// <summary>
    /// The list of subscribed functions.
    /// </summary>
    SubscriberArray m_arSubscribers;
};


/// <summary>
/// Represents an event to which other components can subscribe. When an event is raised, all the 
/// functions subscribed to it will be called using the arguments passed by the caller.
/// </summary>
/// <remarks>
/// Recommended function signatures for event subscribers are:<br/>
/// void f(arguments in an structure)<br/>
/// void f(publisher object, arguments in an structure)
/// </remarks>
/// <typeparam name="ReturnValueT">The return type of the functions that subscribe to the event.</typeparam>
/// <typeparam name="Param1T">The type of the first parameter of the functions that subscribe to the event.</typeparam>
template<class ReturnValueT, class Param1T>
class Event< ReturnValueT(Param1T) >
{
    // TYPEDEFS
    // ---------------
public:

    typedef ReturnValueT(FunctionSignatureT)(Param1T);
    typedef Delegate<FunctionSignatureT> Subscriber;
    typedef ArrayDynamic<Subscriber, 
                                                                     PoolAllocator, 
                                                                     SEqualityComparator<Subscriber> > 
                                                                        SubscriberArray;

    // [TODO] Thund: It may be useful to print a trace when the instance is destroyed while one or more functions are still subscribed.

    // METHODS
    // ---------------
public:
    
    /// <summary>
    /// Calls every subscribed function in FIFO order, passing them the same instance of the provided arguments if any.
    /// </summary>
    /// <param name="p1">An instance to be passed as parameter to every function.</param>
    void Raise(Param1T p1) const
    {
        const puint_z COUNT = m_arSubscribers.GetCount();

        for(puint_z i = 0; i < COUNT; ++i)
            m_arSubscribers[i](p1);
    }
    
    /// <summary>
    /// Subscribes a function to the event.
    /// </summary>
    /// <param name="subscriber">[IN] A function to subscribe. It should not be already subscribed.</param>
    void operator+=(const Subscriber &subscriber)
    {
        Z_ASSERT_WARNING(!m_arSubscribers.Contains(subscriber), "The input function is already subscribed to the event.");

        m_arSubscribers.Add(subscriber);
    }
    
    /// <summary>
    /// Unsubscribes a function from the event.
    /// </summary>
    /// <param name="subscriber">[IN] A function to unsubscribe. It must be already subscribed.</param>
    void operator-=(const Subscriber &subscriber)
    {
        puint_z uIndex = m_arSubscribers.IndexOf(subscriber);

        Z_ASSERT_WARNING(uIndex != SubscriberArray::ELEMENT_NOT_FOUND, "The input function cannot be removed, it is not subscribed to the event.");

        if(uIndex != SubscriberArray::ELEMENT_NOT_FOUND)
            m_arSubscribers.Remove(uIndex);
    }

    /// <summary>
    /// Unsubscribes all the subscribed functions.
    /// </summary>
    void UnsubscribeAll()
    {
        m_arSubscribers.Clear();
    }


    // PROPERTIES
    // ---------------
public:
    
    /// <summary>
    /// Gets the entire list of subscribed functions.
    /// </summary>
    /// <returns>
    /// A list of subscribed functions.
    /// </returns>
    SubscriberArray GetSubscribers() const
    {
        return m_arSubscribers;
    }


    // ATTRIBUTES
    // ---------------
protected:

    /// <summary>
    /// The list of subscribed functions.
    /// </summary>
    SubscriberArray m_arSubscribers;

};


/// <summary>
/// Represents an event to which other components can subscribe. When an event is raised, all the 
/// functions subscribed to it will be called using the arguments passed by the caller.
/// </summary>
/// <remarks>
/// Recommended function signatures for event subscribers are:<br/>
/// void f(arguments in an structure)<br/>
/// void f(publisher object, arguments in an structure)
/// </remarks>
/// <typeparam name="ReturnValueT">The return type of the functions that subscribe to the event.</typeparam>
/// <typeparam name="Param1T">The type of the first parameter of the functions that subscribe to the event.</typeparam>
/// <typeparam name="Param2T">The type of the second parameter of the functions that subscribe to the event.</typeparam>
template<class ReturnValueT, class Param1T, class Param2T>
class Event< ReturnValueT(Param1T, Param2T) >
{
    // TYPEDEFS
    // ---------------
public:

    typedef ReturnValueT(FunctionSignatureT)(Param1T, Param2T);
    typedef Delegate<FunctionSignatureT> Subscriber;
    typedef ArrayDynamic<Subscriber, 
                                                                     PoolAllocator, 
                                                                     SEqualityComparator<Subscriber> > 
                                                                        SubscriberArray;

    // [TODO] Thund: It may be useful to print a trace when the instance is destroyed while one or more functions are still subscribed.

    // METHODS
    // ---------------
public:
    
    /// <summary>
    /// Calls every subscribed function in FIFO order, passing them the same instance of the provided arguments if any.
    /// </summary>
    /// <param name="p1">An instance to be passed as first parameter to every function.</param>
    /// <param name="p2">An instance to be passed as second parameter to every function.</param>
    void Raise(Param1T p1, Param2T p2) const
    {
        const puint_z COUNT = m_arSubscribers.GetCount();

        for(puint_z i = 0; i < COUNT; ++i)
            m_arSubscribers[i](p1, p2);
    }
    
    /// <summary>
    /// Subscribes a function to the event.
    /// </summary>
    /// <param name="subscriber">[IN] A function to subscribe. It should not be already subscribed.</param>
    void operator+=(const Subscriber &subscriber)
    {
        Z_ASSERT_WARNING(!m_arSubscribers.Contains(subscriber), "The input function is already subscribed to the event.");

        m_arSubscribers.Add(subscriber);
    }
    
    /// <summary>
    /// Unsubscribes a function from the event.
    /// </summary>
    /// <param name="subscriber">[IN] A function to unsubscribe. It must be already subscribed.</param>
    void operator-=(const Subscriber &subscriber)
    {
        puint_z uIndex = m_arSubscribers.IndexOf(subscriber);

        Z_ASSERT_WARNING(uIndex != SubscriberArray::ELEMENT_NOT_FOUND, "The input function cannot be removed, it is not subscribed to the event.");

        if(uIndex != SubscriberArray::ELEMENT_NOT_FOUND)
            m_arSubscribers.Remove(uIndex);
    }

    /// <summary>
    /// Unsubscribes all the subscribed functions.
    /// </summary>
    void UnsubscribeAll()
    {
        m_arSubscribers.Clear();
    }


    // PROPERTIES
    // ---------------
public:
    
    /// <summary>
    /// Gets the entire list of subscribed functions.
    /// </summary>
    /// <returns>
    /// A list of subscribed functions.
    /// </returns>
    SubscriberArray GetSubscribers() const
    {
        return m_arSubscribers;
    }


    // ATTRIBUTES
    // ---------------
protected:

    /// <summary>
    /// The list of subscribed functions.
    /// </summary>
    SubscriberArray m_arSubscribers;

};


/// <summary>
/// Represents an event to which other components can subscribe. When an event is raised, all the 
/// functions subscribed to it will be called using the arguments passed by the caller.
/// </summary>
/// <remarks>
/// Recommended function signatures for event subscribers are:<br/>
/// void f(arguments in an structure)<br/>
/// void f(publisher object, arguments in an structure)
/// </remarks>
/// <typeparam name="ReturnValueT">The return type of the functions that subscribe to the event.</typeparam>
/// <typeparam name="Param1T">The type of the first parameter of the functions that subscribe to the event.</typeparam>
/// <typeparam name="Param2T">The type of the second parameter of the functions that subscribe to the event.</typeparam>
/// <typeparam name="Param3T">The type of the third parameter of the functions that subscribe to the event.</typeparam>
template<class ReturnValueT, class Param1T, class Param2T, class Param3T>
class Event< ReturnValueT(Param1T, Param2T, Param3T) >
{
    // TYPEDEFS
    // ---------------
public:

    typedef ReturnValueT(FunctionSignatureT)(Param1T, Param2T, Param3T);
    typedef Delegate<FunctionSignatureT> Subscriber;
    typedef ArrayDynamic<Subscriber, 
                                                                     PoolAllocator, 
                                                                     SEqualityComparator<Subscriber> > 
                                                                        SubscriberArray;

    // [TODO] Thund: It may be useful to print a trace when the instance is destroyed while one or more functions are still subscribed.

    // METHODS
    // ---------------
public:
    
    /// <summary>
    /// Calls every subscribed function in FIFO order, passing them the same instance of the provided arguments if any.
    /// </summary>
    /// <param name="p1">An instance to be passed as first parameter to every function.</param>
    /// <param name="p2">An instance to be passed as second parameter to every function.</param>
    /// <param name="p3">An instance to be passed as third parameter to every function.</param>
    void Raise(Param1T p1, Param2T p2, Param3T p3) const
    {
        const puint_z COUNT = m_arSubscribers.GetCount();

        for(puint_z i = 0; i < COUNT; ++i)
            m_arSubscribers[i](p1, p2, p3);
    }
    
    /// <summary>
    /// Subscribes a function to the event.
    /// </summary>
    /// <param name="subscriber">[IN] A function to subscribe. It should not be already subscribed.</param>
    void operator+=(const Subscriber &subscriber)
    {
        Z_ASSERT_WARNING(!m_arSubscribers.Contains(subscriber), "The input function is already subscribed to the event.");

        m_arSubscribers.Add(subscriber);
    }
    
    /// <summary>
    /// Unsubscribes a function from the event.
    /// </summary>
    /// <param name="subscriber">[IN] A function to unsubscribe. It must be already subscribed.</param>
    void operator-=(const Subscriber &subscriber)
    {
        puint_z uIndex = m_arSubscribers.IndexOf(subscriber);

        Z_ASSERT_WARNING(uIndex != SubscriberArray::ELEMENT_NOT_FOUND, "The input function cannot be removed, it is not subscribed to the event.");

        if(uIndex != SubscriberArray::ELEMENT_NOT_FOUND)
            m_arSubscribers.Remove(uIndex);
    }

    /// <summary>
    /// Unsubscribes all the subscribed functions.
    /// </summary>
    void UnsubscribeAll()
    {
        m_arSubscribers.Clear();
    }


    // PROPERTIES
    // ---------------
public:
    
    /// <summary>
    /// Gets the entire list of subscribed functions.
    /// </summary>
    /// <returns>
    /// A list of subscribed functions.
    /// </returns>
    SubscriberArray GetSubscribers() const
    {
        return m_arSubscribers;
    }


    // ATTRIBUTES
    // ---------------
protected:

    /// <summary>
    /// The list of subscribed functions.
    /// </summary>
    SubscriberArray m_arSubscribers;

};


/// <summary>
/// Represents an event to which other components can subscribe. When an event is raised, all the 
/// functions subscribed to it will be called using the arguments passed by the caller.
/// </summary>
/// <remarks>
/// Recommended function signatures for event subscribers are:<br/>
/// void f(arguments in an structure)<br/>
/// void f(publisher object, arguments in an structure)
/// </remarks>
/// <typeparam name="ReturnValueT">The return type of the functions that subscribe to the event.</typeparam>
/// <typeparam name="Param1T">The type of the first parameter of the functions that subscribe to the event.</typeparam>
/// <typeparam name="Param2T">The type of the second parameter of the functions that subscribe to the event.</typeparam>
/// <typeparam name="Param3T">The type of the third parameter of the functions that subscribe to the event.</typeparam>
/// <typeparam name="Param4T">The type of the fourth parameter of the functions that subscribe to the event.</typeparam>
template<class ReturnValueT, class Param1T, class Param2T, class Param3T, class Param4T>
class Event< ReturnValueT(Param1T, Param2T, Param3T, Param4T) >
{
    // TYPEDEFS
    // ---------------
public:

    typedef ReturnValueT(FunctionSignatureT)(Param1T, Param2T, Param3T, Param4T);
    typedef Delegate<FunctionSignatureT> Subscriber;
    typedef ArrayDynamic<Subscriber, 
                                                                     PoolAllocator, 
                                                                     SEqualityComparator<Subscriber> > 
                                                                        SubscriberArray;

    // [TODO] Thund: It may be useful to print a trace when the instance is destroyed while one or more functions are still subscribed.

    // METHODS
    // ---------------
public:
    
    /// <summary>
    /// Calls every subscribed function in FIFO order, passing them the same instance of the provided arguments if any.
    /// </summary>
    /// <param name="p1">An instance to be passed as first parameter to every function.</param>
    /// <param name="p2">An instance to be passed as second parameter to every function.</param>
    /// <param name="p3">An instance to be passed as third parameter to every function.</param>
    /// <param name="p4">An instance to be passed as fourth parameter to every function.</param>
    void Raise(Param1T p1, Param2T p2, Param3T p3, Param4T p4) const
    {
        const puint_z COUNT = m_arSubscribers.GetCount();

        for(puint_z i = 0; i < COUNT; ++i)
            m_arSubscribers[i](p1, p2, p3, p4);
    }
    
    /// <summary>
    /// Subscribes a function to the event.
    /// </summary>
    /// <param name="subscriber">[IN] A function to subscribe. It should not be already subscribed.</param>
    void operator+=(const Subscriber &subscriber)
    {
        Z_ASSERT_WARNING(!m_arSubscribers.Contains(subscriber), "The input function is already subscribed to the event.");

        m_arSubscribers.Add(subscriber);
    }
    
    /// <summary>
    /// Unsubscribes a function from the event.
    /// </summary>
    /// <param name="subscriber">[IN] A function to unsubscribe. It must be already subscribed.</param>
    void operator-=(const Subscriber &subscriber)
    {
        puint_z uIndex = m_arSubscribers.IndexOf(subscriber);

        Z_ASSERT_WARNING(uIndex != SubscriberArray::ELEMENT_NOT_FOUND, "The input function cannot be removed, it is not subscribed to the event.");

        if(uIndex != SubscriberArray::ELEMENT_NOT_FOUND)
            m_arSubscribers.Remove(uIndex);
    }

    /// <summary>
    /// Unsubscribes all the subscribed functions.
    /// </summary>
    void UnsubscribeAll()
    {
        m_arSubscribers.Clear();
    }


    // PROPERTIES
    // ---------------
public:
    
    /// <summary>
    /// Gets the entire list of subscribed functions.
    /// </summary>
    /// <returns>
    /// A list of subscribed functions.
    /// </returns>
    SubscriberArray GetSubscribers() const
    {
        return m_arSubscribers;
    }


    // ATTRIBUTES
    // ---------------
protected:

    /// <summary>
    /// The list of subscribed functions.
    /// </summary>
    SubscriberArray m_arSubscribers;

};


/// <summary>
/// Represents an event to which other components can subscribe. When an event is raised, all the 
/// functions subscribed to it will be called using the arguments passed by the caller.
/// </summary>
/// <remarks>
/// Recommended function signatures for event subscribers are:<br/>
/// void f(arguments in an structure)<br/>
/// void f(publisher object, arguments in an structure)
/// </remarks>
/// <typeparam name="ReturnValueT">The return type of the functions that subscribe to the event.</typeparam>
/// <typeparam name="Param1T">The type of the first parameter of the functions that subscribe to the event.</typeparam>
/// <typeparam name="Param2T">The type of the second parameter of the functions that subscribe to the event.</typeparam>
/// <typeparam name="Param3T">The type of the third parameter of the functions that subscribe to the event.</typeparam>
/// <typeparam name="Param4T">The type of the fourth parameter of the functions that subscribe to the event.</typeparam>
/// <typeparam name="Param5T">The type of the fifth parameter of the functions that subscribe to the event.</typeparam>
template<class ReturnValueT, class Param1T, class Param2T, class Param3T, class Param4T, class Param5T>
class Event< ReturnValueT(Param1T, Param2T, Param3T, Param4T, Param5T) >
{
    // TYPEDEFS
    // ---------------
public:

    typedef ReturnValueT(FunctionSignatureT)(Param1T, Param2T, Param3T, Param4T, Param5T);
    typedef Delegate<FunctionSignatureT> Subscriber;
    typedef ArrayDynamic<Subscriber, 
                                                                     PoolAllocator, 
                                                                     SEqualityComparator<Subscriber> > 
                                                                        SubscriberArray;

    // [TODO] Thund: It may be useful to print a trace when the instance is destroyed while one or more functions are still subscribed.

    // METHODS
    // ---------------
public:
    
    /// <summary>
    /// Calls every subscribed function in FIFO order, passing them the same instance of the provided arguments if any.
    /// </summary>
    /// <param name="p1">An instance to be passed as first parameter to every function.</param>
    /// <param name="p2">An instance to be passed as second parameter to every function.</param>
    /// <param name="p3">An instance to be passed as third parameter to every function.</param>
    /// <param name="p4">An instance to be passed as fourth parameter to every function.</param>
    /// <param name="p5">An instance to be passed as fifth parameter to every function.</param>
    void Raise(Param1T p1, Param2T p2, Param3T p3, Param4T p4, Param5T p5) const
    {
        const puint_z COUNT = m_arSubscribers.GetCount();

        for(puint_z i = 0; i < COUNT; ++i)
            m_arSubscribers[i](p1, p2, p3, p4, p5);
    }
    
    /// <summary>
    /// Subscribes a function to the event.
    /// </summary>
    /// <param name="subscriber">[IN] A function to subscribe. It should not be already subscribed.</param>
    void operator+=(const Subscriber &subscriber)
    {
        Z_ASSERT_WARNING(!m_arSubscribers.Contains(subscriber), "The input function is already subscribed to the event.");

        m_arSubscribers.Add(subscriber);
    }
    
    /// <summary>
    /// Unsubscribes a function from the event.
    /// </summary>
    /// <param name="subscriber">[IN] A function to unsubscribe. It must be already subscribed.</param>
    void operator-=(const Subscriber &subscriber)
    {
        puint_z uIndex = m_arSubscribers.IndexOf(subscriber);

        Z_ASSERT_WARNING(uIndex != SubscriberArray::ELEMENT_NOT_FOUND, "The input function cannot be removed, it is not subscribed to the event.");

        if(uIndex != SubscriberArray::ELEMENT_NOT_FOUND)
            m_arSubscribers.Remove(uIndex);
    }

    /// <summary>
    /// Unsubscribes all the subscribed functions.
    /// </summary>
    void UnsubscribeAll()
    {
        m_arSubscribers.Clear();
    }


    // PROPERTIES
    // ---------------
public:
    
    /// <summary>
    /// Gets the entire list of subscribed functions.
    /// </summary>
    /// <returns>
    /// A list of subscribed functions.
    /// </returns>
    SubscriberArray GetSubscribers() const
    {
        return m_arSubscribers;
    }


    // ATTRIBUTES
    // ---------------
protected:

    /// <summary>
    /// The list of subscribed functions.
    /// </summary>
    SubscriberArray m_arSubscribers;

};


/// <summary>
/// Represents an event to which other components can subscribe. When an event is raised, all the 
/// functions subscribed to it will be called using the arguments passed by the caller.
/// </summary>
/// <remarks>
/// Recommended function signatures for event subscribers are:<br/>
/// void f(arguments in an structure)<br/>
/// void f(publisher object, arguments in an structure)
/// </remarks>
/// <typeparam name="ReturnValueT">The return type of the functions that subscribe to the event.</typeparam>
/// <typeparam name="Param1T">The type of the first parameter of the functions that subscribe to the event.</typeparam>
/// <typeparam name="Param2T">The type of the second parameter of the functions that subscribe to the event.</typeparam>
/// <typeparam name="Param3T">The type of the third parameter of the functions that subscribe to the event.</typeparam>
/// <typeparam name="Param4T">The type of the fourth parameter of the functions that subscribe to the event.</typeparam>
/// <typeparam name="Param5T">The type of the fifth parameter of the functions that subscribe to the event.</typeparam>
/// <typeparam name="Param6T">The type of the sixth parameter of the functions that subscribe to the event.</typeparam>
template<class ReturnValueT, class Param1T, class Param2T, class Param3T, class Param4T, class Param5T, class Param6T>
class Event< ReturnValueT(Param1T, Param2T, Param3T, Param4T, Param5T, Param6T) >
{
    // TYPEDEFS
    // ---------------
public:

    typedef ReturnValueT(FunctionSignatureT)(Param1T, Param2T, Param3T, Param4T, Param5T, Param6T);
    typedef Delegate<FunctionSignatureT> Subscriber;
    typedef ArrayDynamic<Subscriber, 
                                                                     PoolAllocator, 
                                                                     SEqualityComparator<Subscriber> > 
                                                                        SubscriberArray;

    // [TODO] Thund: It may be useful to print a trace when the instance is destroyed while one or more functions are still subscribed.

    // METHODS
    // ---------------
public:
    
    /// <summary>
    /// Calls every subscribed function in FIFO order, passing them the same instance of the provided arguments if any.
    /// </summary>
    /// <param name="p1">An instance to be passed as first parameter to every function.</param>
    /// <param name="p2">An instance to be passed as second parameter to every function.</param>
    /// <param name="p3">An instance to be passed as third parameter to every function.</param>
    /// <param name="p4">An instance to be passed as fourth parameter to every function.</param>
    /// <param name="p5">An instance to be passed as fifth parameter to every function.</param>
    /// <param name="p6">An instance to be passed as sixth parameter to every function.</param>
    void Raise(Param1T p1, Param2T p2, Param3T p3, Param4T p4, Param5T p5, Param6T p6) const
    {
        const puint_z COUNT = m_arSubscribers.GetCount();

        for(puint_z i = 0; i < COUNT; ++i)
            m_arSubscribers[i](p1, p2, p3, p4, p5, p6);
    }
    
    /// <summary>
    /// Subscribes a function to the event.
    /// </summary>
    /// <param name="subscriber">[IN] A function to subscribe. It should not be already subscribed.</param>
    void operator+=(const Subscriber &subscriber)
    {
        Z_ASSERT_WARNING(!m_arSubscribers.Contains(subscriber), "The input function is already subscribed to the event.");

        m_arSubscribers.Add(subscriber);
    }
    
    /// <summary>
    /// Unsubscribes a function from the event.
    /// </summary>
    /// <param name="subscriber">[IN] A function to unsubscribe. It must be already subscribed.</param>
    void operator-=(const Subscriber &subscriber)
    {
        puint_z uIndex = m_arSubscribers.IndexOf(subscriber);

        Z_ASSERT_WARNING(uIndex != SubscriberArray::ELEMENT_NOT_FOUND, "The input function cannot be removed, it is not subscribed to the event.");

        if(uIndex != SubscriberArray::ELEMENT_NOT_FOUND)
            m_arSubscribers.Remove(uIndex);
    }

    /// <summary>
    /// Unsubscribes all the subscribed functions.
    /// </summary>
    void UnsubscribeAll()
    {
        m_arSubscribers.Clear();
    }


    // PROPERTIES
    // ---------------
public:
    
    /// <summary>
    /// Gets the entire list of subscribed functions.
    /// </summary>
    /// <returns>
    /// A list of subscribed functions.
    /// </returns>
    SubscriberArray GetSubscribers() const
    {
        return m_arSubscribers;
    }


    // ATTRIBUTES
    // ---------------
protected:

    /// <summary>
    /// The list of subscribed functions.
    /// </summary>
    SubscriberArray m_arSubscribers;

};


/// <summary>
/// Represents an event to which other components can subscribe. When an event is raised, all the 
/// functions subscribed to it will be called using the arguments passed by the caller.
/// </summary>
/// <remarks>
/// Recommended function signatures for event subscribers are:<br/>
/// void f(arguments in an structure)<br/>
/// void f(publisher object, arguments in an structure)
/// </remarks>
/// <typeparam name="ReturnValueT">The return type of the functions that subscribe to the event.</typeparam>
/// <typeparam name="Param1T">The type of the first parameter of the functions that subscribe to the event.</typeparam>
/// <typeparam name="Param2T">The type of the second parameter of the functions that subscribe to the event.</typeparam>
/// <typeparam name="Param3T">The type of the third parameter of the functions that subscribe to the event.</typeparam>
/// <typeparam name="Param4T">The type of the fourth parameter of the functions that subscribe to the event.</typeparam>
/// <typeparam name="Param5T">The type of the fifth parameter of the functions that subscribe to the event.</typeparam>
/// <typeparam name="Param6T">The type of the sixth parameter of the functions that subscribe to the event.</typeparam>
/// <typeparam name="Param7T">The type of the seventh parameter of the functions that subscribe to the event.</typeparam>
template<class ReturnValueT, class Param1T, class Param2T, class Param3T, class Param4T, class Param5T, class Param6T, class Param7T>
class Event< ReturnValueT(Param1T, Param2T, Param3T, Param4T, Param5T, Param6T, Param7T) >
{
    // TYPEDEFS
    // ---------------
public:

    typedef ReturnValueT(FunctionSignatureT)(Param1T, Param2T, Param3T, Param4T, Param5T, Param6T, Param7T);
    typedef Delegate<FunctionSignatureT> Subscriber;
    typedef ArrayDynamic<Subscriber, 
                                                                     PoolAllocator, 
                                                                     SEqualityComparator<Subscriber> > 
                                                                        SubscriberArray;

    // [TODO] Thund: It may be useful to print a trace when the instance is destroyed while one or more functions are still subscribed.

    // METHODS
    // ---------------
public:
    
    /// <summary>
    /// Calls every subscribed function in FIFO order, passing them the same instance of the provided arguments if any.
    /// </summary>
    /// <param name="p1">An instance to be passed as first parameter to every function.</param>
    /// <param name="p2">An instance to be passed as second parameter to every function.</param>
    /// <param name="p3">An instance to be passed as third parameter to every function.</param>
    /// <param name="p4">An instance to be passed as fourth parameter to every function.</param>
    /// <param name="p5">An instance to be passed as fifth parameter to every function.</param>
    /// <param name="p6">An instance to be passed as sixth parameter to every function.</param>
    /// <param name="p7">An instance to be passed as seventh parameter to every function.</param>
    void Raise(Param1T p1, Param2T p2, Param3T p3, Param4T p4, Param5T p5, Param6T p6, Param7T p7) const
    {
        const puint_z COUNT = m_arSubscribers.GetCount();

        for(puint_z i = 0; i < COUNT; ++i)
            m_arSubscribers[i](p1, p2, p3, p4, p5, p6, p7);
    }
    
    /// <summary>
    /// Subscribes a function to the event.
    /// </summary>
    /// <param name="subscriber">[IN] A function to subscribe. It should not be already subscribed.</param>
    void operator+=(const Subscriber &subscriber)
    {
        Z_ASSERT_WARNING(!m_arSubscribers.Contains(subscriber), "The input function is already subscribed to the event.");

        m_arSubscribers.Add(subscriber);
    }
    
    /// <summary>
    /// Unsubscribes a function from the event.
    /// </summary>
    /// <param name="subscriber">[IN] A function to unsubscribe. It must be already subscribed.</param>
    void operator-=(const Subscriber &subscriber)
    {
        puint_z uIndex = m_arSubscribers.IndexOf(subscriber);

        Z_ASSERT_WARNING(uIndex != SubscriberArray::ELEMENT_NOT_FOUND, "The input function cannot be removed, it is not subscribed to the event.");

        if(uIndex != SubscriberArray::ELEMENT_NOT_FOUND)
            m_arSubscribers.Remove(uIndex);
    }

    /// <summary>
    /// Unsubscribes all the subscribed functions.
    /// </summary>
    void UnsubscribeAll()
    {
        m_arSubscribers.Clear();
    }


    // PROPERTIES
    // ---------------
public:
    
    /// <summary>
    /// Gets the entire list of subscribed functions.
    /// </summary>
    /// <returns>
    /// A list of subscribed functions.
    /// </returns>
    SubscriberArray GetSubscribers() const
    {
        return m_arSubscribers;
    }


    // ATTRIBUTES
    // ---------------
protected:

    /// <summary>
    /// The list of subscribed functions.
    /// </summary>
    SubscriberArray m_arSubscribers;

};


/// <summary>
/// Represents an event to which other components can subscribe. When an event is raised, all the 
/// functions subscribed to it will be called using the arguments passed by the caller.
/// </summary>
/// <remarks>
/// Recommended function signatures for event subscribers are:<br/>
/// void f(arguments in an structure)<br/>
/// void f(publisher object, arguments in an structure)
/// </remarks>
/// <typeparam name="ReturnValueT">The return type of the functions that subscribe to the event.</typeparam>
/// <typeparam name="Param1T">The type of the first parameter of the functions that subscribe to the event.</typeparam>
/// <typeparam name="Param2T">The type of the second parameter of the functions that subscribe to the event.</typeparam>
/// <typeparam name="Param3T">The type of the third parameter of the functions that subscribe to the event.</typeparam>
/// <typeparam name="Param4T">The type of the fourth parameter of the functions that subscribe to the event.</typeparam>
/// <typeparam name="Param5T">The type of the fifth parameter of the functions that subscribe to the event.</typeparam>
/// <typeparam name="Param6T">The type of the sixth parameter of the functions that subscribe to the event.</typeparam>
/// <typeparam name="Param7T">The type of the seventh parameter of the functions that subscribe to the event.</typeparam>
/// <typeparam name="Param8T">The type of the eighth parameter of the functions that subscribe to the event.</typeparam>
template<class ReturnValueT, class Param1T, class Param2T, class Param3T, class Param4T, class Param5T, class Param6T, class Param7T, class Param8T>
class Event< ReturnValueT(Param1T, Param2T, Param3T, Param4T, Param5T, Param6T, Param7T, Param8T) >
{
    // TYPEDEFS
    // ---------------
public:

    typedef ReturnValueT(FunctionSignatureT)(Param1T, Param2T, Param3T, Param4T, Param5T, Param6T, Param7T, Param8T);
    typedef Delegate<FunctionSignatureT> Subscriber;
    typedef ArrayDynamic<Subscriber, 
                                                                     PoolAllocator, 
                                                                     SEqualityComparator<Subscriber> > 
                                                                        SubscriberArray;

    // [TODO] Thund: It may be useful to print a trace when the instance is destroyed while one or more functions are still subscribed.

    // METHODS
    // ---------------
public:
    
    /// <summary>
    /// Calls every subscribed function in FIFO order, passing them the same instance of the provided arguments if any.
    /// </summary>
    /// <param name="p1">An instance to be passed as first parameter to every function.</param>
    /// <param name="p2">An instance to be passed as second parameter to every function.</param>
    /// <param name="p3">An instance to be passed as third parameter to every function.</param>
    /// <param name="p4">An instance to be passed as fourth parameter to every function.</param>
    /// <param name="p5">An instance to be passed as fifth parameter to every function.</param>
    /// <param name="p6">An instance to be passed as sixth parameter to every function.</param>
    /// <param name="p7">An instance to be passed as seventh parameter to every function.</param>
    /// <param name="p8">An instance to be passed as eighth parameter to every function.</param>
    void Raise(Param1T p1, Param2T p2, Param3T p3, Param4T p4, Param5T p5, Param6T p6, Param7T p7, Param8T p8) const
    {
        const puint_z COUNT = m_arSubscribers.GetCount();

        for(puint_z i = 0; i < COUNT; ++i)
            m_arSubscribers[i](p1, p2, p3, p4, p5, p6, p7, p8);
    }
    
    /// <summary>
    /// Subscribes a function to the event.
    /// </summary>
    /// <param name="subscriber">[IN] A function to subscribe. It should not be already subscribed.</param>
    void operator+=(const Subscriber &subscriber)
    {
        Z_ASSERT_WARNING(!m_arSubscribers.Contains(subscriber), "The input function is already subscribed to the event.");

        m_arSubscribers.Add(subscriber);
    }
    
    /// <summary>
    /// Unsubscribes a function from the event.
    /// </summary>
    /// <param name="subscriber">[IN] A function to unsubscribe. It must be already subscribed.</param>
    void operator-=(const Subscriber &subscriber)
    {
        puint_z uIndex = m_arSubscribers.IndexOf(subscriber);

        Z_ASSERT_WARNING(uIndex != SubscriberArray::ELEMENT_NOT_FOUND, "The input function cannot be removed, it is not subscribed to the event.");

        if(uIndex != SubscriberArray::ELEMENT_NOT_FOUND)
            m_arSubscribers.Remove(uIndex);
    }

    /// <summary>
    /// Unsubscribes all the subscribed functions.
    /// </summary>
    void UnsubscribeAll()
    {
        m_arSubscribers.Clear();
    }


    // PROPERTIES
    // ---------------
public:
    
    /// <summary>
    /// Gets the entire list of subscribed functions.
    /// </summary>
    /// <returns>
    /// A list of subscribed functions.
    /// </returns>
    SubscriberArray GetSubscribers() const
    {
        return m_arSubscribers;
    }


    // ATTRIBUTES
    // ---------------
protected:

    /// <summary>
    /// The list of subscribed functions.
    /// </summary>
    SubscriberArray m_arSubscribers;

};

} // namespace z

#endif // __EVENT__
