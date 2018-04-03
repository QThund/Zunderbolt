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

#ifndef __DELEGATE__
#define __DELEGATE__

#include "ZCommon/CommonModuleDefinitions.h"

#include "ZCommon/Internals/DelegateInternals.h"
#include "ZCommon/Assertions.h"
#include "ZCommon/DataTypes/StringsDefinitions.h"

namespace z
{

/// <summary>
/// Represents a delegate. Delegates are a kind of sophisticated pointers-to-function; they can store
/// a reference to any kind of function: "free" functions, static methods and non-static methods, both
/// virtual and non-virtual. In the case of non-static methods, a reference to the class instance to which
/// the method refers to is stored too.
/// </summary>
/// <remarks>
/// Delegates may be null if they have never been assigned to any function. They can be assigned as
/// many times as necessary.<br/>
/// Delegates are used as if they were normal functions, passing arguments between
/// the brackets.<br/>
/// <b>Known limitations</b><br/>
/// At the moment, it is not possible to create a delegate that stored a constant method of a class when
/// there is an non-constant overload of such method. The non-const overload will be used always instead.
/// </remarks>
/// <typeparam name="FunctionSignatureT">The signature of the function.</typeparam>
template <typename FunctionSignatureT>
class Delegate;

/// <summary>
/// Represents a delegate. Delegates are a kind of sophisticated pointers-to-function; they can store
/// a reference to any kind of function: "free" functions, static methods and non-static methods, both
/// virtual and non-virtual. In the case of non-static methods, a reference to the class instance to which
/// the method refers to is stored too.
/// </summary>
/// <remarks>
/// Delegates may be null if they have never been assigned to any function. They can be assigned as
/// many times as necessary.<br/>
/// Delegates are used as if they were normal functions, passing arguments between
/// the brackets.<br/>
/// <b>Known limitations</b><br/>
/// At the moment, it is not possible to create a delegate that stored a constant method of a class when
/// there is an non-constant overload of such method. The non-const overload will be used always instead.
/// </remarks>
/// <typeparam name="ReturnValueT">The type of the return value.</typeparam>
template<typename ReturnValueT>
class Delegate< ReturnValueT (  ) > : protected Internals::FastDelegate0 < ReturnValueT >
{

    /// <summary>
    /// Pseudonym for the base class.
    /// </summary>
    typedef FastDelegate0 < ReturnValueT > BaseType;

    using BaseType::m_closure;

public:

    /// <summary>
    /// Pseudonym for the return type of the function.
    /// </summary>
    typedef ReturnValueT ReturnType;


    // CONSTRUCTORS
    // ---------------

    /// <summary>
    /// Default constructor. Delgates are considered as null when they have not been assigned to a function.
    /// </summary>
    Delegate()
    {
    }

    /// <summary>
    /// Constructor that receives an object and one of its methods.
    /// </summary>
    /// <typeparam name="ClassT">The class where the method is defined. It can be an ancestor of the object's class.</typeparam>
    /// <typeparam name="ObjectT">The type of the object whose method is to be called.</typeparam>
    /// <param name="pThis">[IN] The object whose method is to be called.</param>
    /// <param name="pFunction">[IN] The method to be called.</param>
    template < class ClassT, class ObjectT >
    Delegate(ObjectT* pThis, ReturnValueT (ClassT::* pFunction)(  )) : BaseType(pThis, pFunction)
    {
    }

    /// <summary>
    /// Constructor that receives a constant object and one of its methods (which must be constant too).
    /// </summary>
    /// <typeparam name="ClassT">The class where the method is defined. It can be an ancestor of the object's class.</typeparam>
    /// <typeparam name="ObjectT">The type of the object whose method is to be called.</typeparam>
    /// <param name="pThis">[IN] The constant object whose method is to be called.</param>
    /// <param name="pFunction">[IN] The constant method to be called.</param>
    template < class ClassT, class ObjectT >
    Delegate(const ObjectT* pThis, ReturnValueT (ClassT::* pFunction)(  ) const) : BaseType(pThis, pFunction)
    {
    }

    /// <summary>
    /// Constructor that receives a function.
    /// </summary>
    /// <param name="pFunction">[IN] The function to be called.</param>
    Delegate(ReturnValueT (*pFunction)(  )) : BaseType(pFunction)
    {
    }


    // METHODS
    // ---------------

    /// <summary>
    /// Assignment operator that copies a delegate.
    /// </summary>
    /// <param name="delegate">[IN] The delegate to copy.</param>
    /// <returns>
    /// A reference to the resident object.
    /// </returns>
    Delegate& operator=(const Delegate &delegate)
    {
        m_closure.CopyFrom(this, delegate.m_closure);
        return *this;
    }

    /// <summary>
    /// Calls the stored function for the stored object, if any.
    /// </summary>
    /// <returns>
    /// The value returned by the function, if any.
    /// </returns>
    ReturnValueT operator() () const
    {
        Z_ASSERT_ERROR(!this->IsNull(), "The delegate is null, calling to the function will fail");
        return (m_closure.GetClosureThis()->*(m_closure.GetClosureMemPtr()))();
    }
    
    /// <summary>
    /// Equality operator that checks whether two delegates contain the same function or not. If they contain the same method, 
    /// it checks whether they belong to the same object.
    /// </summary>
    /// <param name="delegate">[IN] The delegate to compare to.</param>
    /// <returns>
    /// True if both delegates contain the same function or, in case they are methods, if they contain the same method of the same object; False otherwise.
    /// </returns>
    bool operator==(const Delegate &delegate) const
    {
        return m_closure.IsEqual(delegate.m_closure);
    }
    
    /// <summary>
    /// Inequality operator that checks whether two delegates do not contain the same function. If they contain the same method, 
    /// it checks whether they belong to the same object.
    /// </summary>
    /// <param name="delegate">[IN] The delegate to compare to.</param>
    /// <returns>
    /// True if delegates contain different functions or, in case they are methods, if they contain the same method of different objects; False otherwise.
    /// </returns>
    bool operator!=(const Delegate &delegate) const
    {
        return !m_closure.IsEqual(delegate.m_closure);
    }


    // PROPERTIES
    // ---------------

    /// <summary>
    /// Gets the number of parameters of the function.
    /// </summary>
    /// <returns>
    /// The number of parameters of the function.
    /// </returns>
    static const unsigned int& GetNumberOfParameters()
    {
        return Delegate::NUMBER_OF_PARAMETERS;
    }

    /// <summary>
    /// Indicates whether the delegate is null or not. Delegates are null when they are not assigned to any function.
    /// </summary>
    /// <returns>
    /// True if the delegate is True; False otherwise.
    /// </returns>
    bool IsNull() const
    {
        return !m_closure;
    }


    // ATTRIBUTES
    // ---------------
private:

    /// <summary>
    /// The number of parameters of the function.
    /// </summary>
    static const unsigned int NUMBER_OF_PARAMETERS;
};

// STATIC MEMBERS INITIALIZATION
// --------------------------------
template<typename ReturnValueT>
const unsigned int Delegate< ReturnValueT (  ) >::NUMBER_OF_PARAMETERS = 0;


/// <summary>
/// Represents a delegate. Delegates are a kind of sophisticated pointers-to-function; they can store
/// a reference to any kind of function: "free" functions, static methods and non-static methods, both
/// virtual and non-virtual. In the case of non-static methods, a reference to the class instance to which
/// the method refers to is stored too.
/// </summary>
/// <remarks>
/// Delegates may be null if they have never been assigned to any function. They can be assigned as
/// many times as necessary.<br/>
/// Delegates are used as if they were normal functions, passing arguments between
/// the brackets.<br/>
/// <b>Known limitations</b><br/>
/// At the moment, it is not possible to create a delegate that stored a constant method of a class when
/// there is an non-constant overload of such method. The non-const overload will be used always instead.
/// </remarks>
/// <typeparam name="ReturnValueT">The type of the return value.</typeparam>
/// <typeparam name="Param1T">The type of the first parameter.</typeparam>
template<typename ReturnValueT, class Param1T>
class Delegate< ReturnValueT ( Param1T ) > : protected Internals::FastDelegate1 < Param1T, ReturnValueT >
{

    /// <summary>
    /// Pseudonym for the base class.
    /// </summary>
    typedef FastDelegate1 < Param1T, ReturnValueT > BaseType;

    using BaseType::m_closure;

    /// <summary>
    /// Pseudonym for this class.
    /// </summary>
    typedef Delegate SelfType;

public:

    /// <summary>
    /// Pseudonym for the type of the first parameter of the function.
    /// </summary>
    typedef Param1T Parameter1Type;

    /// <summary>
    /// Pseudonym for the return type of the function.
    /// </summary>
    typedef ReturnValueT ReturnType;


    // CONSTRUCTORS
    // ---------------

    /// <summary>
    /// Default constructor. Delgates are considered as null when they have not been assigned to a function.
    /// </summary>
    Delegate()
    {
    }

    /// <summary>
    /// Constructor that receives an object and one of its methods.
    /// </summary>
    /// <typeparam name="ClassT">The class where the method is defined. It can be an ancestor of the object's class.</typeparam>
    /// <typeparam name="ObjectT">The type of the object whose method is to be called.</typeparam>
    /// <param name="pThis">[IN] The object whose method is to be called.</param>
    /// <param name="pFunction">[IN] The method to be called.</param>
    template < class ClassT, class ObjectT >
    Delegate(ObjectT* pThis, ReturnValueT (ClassT::* pFunction)( Param1T p1 )) : BaseType(pThis, pFunction)
    {
    }

    /// <summary>
    /// Constructor that receives a constant object and one of its methods (which must be constant too).
    /// </summary>
    /// <typeparam name="ClassT">The class where the method is defined. It can be an ancestor of the object's class.</typeparam>
    /// <typeparam name="ObjectT">The type of the object whose method is to be called.</typeparam>
    /// <param name="pThis">[IN] The constant object whose method is to be called.</param>
    /// <param name="pFunction">[IN] The constant method to be called.</param>
    template < class ClassT, class ObjectT >
    Delegate(const ObjectT* pThis, ReturnValueT (ClassT::* pFunction)( Param1T p1 ) const) : BaseType(pThis, pFunction)
    {
    }

    /// <summary>
    /// Constructor that receives a function.
    /// </summary>
    /// <param name="pFunction">[IN] The function to be called.</param>
    Delegate(ReturnValueT (*pFunction)( Param1T p1 )) : BaseType(pFunction)
    {
    }


    // METHODS
    // ---------------

    /// <summary>
    /// Assignment operator that copies a delegate.
    /// </summary>
    /// <param name="delegate">[IN] The delegate to copy.</param>
    /// <returns>
    /// A reference to the resident object.
    /// </returns>
    Delegate& operator=(const Delegate &delegate)
    {
        m_closure.CopyFrom(this, delegate.m_closure);
        return *this;
    }

    /// <summary>
    /// Calls the stored function for the stored object, if any.
    /// </summary>
    /// <param name="p1">[IN] The first parameter of the function.</param>
    /// <returns>
    /// The value returned by the function, if any.
    /// </returns>
    ReturnValueT operator() (Param1T p1) const
    {
        Z_ASSERT_ERROR(!this->IsNull(), "The delegate is null, calling to the function will fail");
        return (m_closure.GetClosureThis()->*(m_closure.GetClosureMemPtr()))(p1);
    }
    
    /// <summary>
    /// Equality operator that checks whether two delegates contain the same function or not. If they contain the same method, 
    /// it checks whether they belong to the same object.
    /// </summary>
    /// <param name="delegate">[IN] The delegate to compare to.</param>
    /// <returns>
    /// True if both delegates contain the same function or, in case they are methods, if they contain the same method of the same object; False otherwise.
    /// </returns>
    bool operator==(const Delegate &delegate) const
    {
        return m_closure.IsEqual(delegate.m_closure);
    }
    
    /// <summary>
    /// Inequality operator that checks whether two delegates do not contain the same function. If they contain the same method, 
    /// it checks whether they belong to the same object.
    /// </summary>
    /// <param name="delegate">[IN] The delegate to compare to.</param>
    /// <returns>
    /// True if delegates contain different functions or, in case they are methods, if they contain the same method of different objects; False otherwise.
    /// </returns>
    bool operator!=(const Delegate &delegate) const
    {
        return !m_closure.IsEqual(delegate.m_closure);
    }


    // PROPERTIES
    // ---------------

    /// <summary>
    /// Gets the number of parameters of the function.
    /// </summary>
    /// <returns>
    /// The number of parameters of the function.
    /// </returns>
    static const unsigned int& GetNumberOfParameters()
    {
        return Delegate::NUMBER_OF_PARAMETERS;
    }

    /// <summary>
    /// Indicates whether the delegate is null or not. Delegates are null when they are not assigned to any function.
    /// </summary>
    /// <returns>
    /// True if the delegate is True; False otherwise.
    /// </returns>
    bool IsNull() const
    {
        return !m_closure;
    }

    // ATTRIBUTES
    // ---------------
private:

    /// <summary>
    /// The number of parameters of the function.
    /// </summary>
    static const unsigned int NUMBER_OF_PARAMETERS;
};

// STATIC MEMBERS INITIALIZATION
// --------------------------------
template<typename ReturnValueT, class Param1T>
const unsigned int Delegate< ReturnValueT ( Param1T ) >::NUMBER_OF_PARAMETERS = 1;


/// <summary>
/// Represents a delegate. Delegates are a kind of sophisticated pointers-to-function; they can store
/// a reference to any kind of function: "free" functions, static methods and non-static methods, both
/// virtual and non-virtual. In the case of non-static methods, a reference to the class instance to which
/// the method refers to is stored too.
/// </summary>
/// <remarks>
/// Delegates may be null if they have never been assigned to any function. They can be assigned as
/// many times as necessary.<br/>
/// Delegates are used as if they were normal functions, passing arguments between
/// the brackets.<br/>
/// <b>Known limitations</b><br/>
/// At the moment, it is not possible to create a delegate that stored a constant method of a class when
/// there is an non-constant overload of such method. The non-const overload will be used always instead.
/// </remarks>
/// <typeparam name="ReturnValueT">The type of the return value.</typeparam>
/// <typeparam name="Param1T">The type of the first parameter.</typeparam>
/// <typeparam name="Param2T">The type of the second parameter.</typeparam>
template<typename ReturnValueT, class Param1T, class Param2T>
class Delegate< ReturnValueT ( Param1T, Param2T ) > : protected Internals::FastDelegate2 < Param1T, Param2T, ReturnValueT >
{

    /// <summary>
    /// Pseudonym for the base class.
    /// </summary>
    typedef FastDelegate2 < Param1T, Param2T, ReturnValueT > BaseType;

    using BaseType::m_closure;

    /// <summary>
    /// Pseudonym for this class.
    /// </summary>
    typedef Delegate SelfType;

public:

    /// <summary>
    /// Pseudonym for the type of the first parameter of the function.
    /// </summary>
    typedef Param1T Parameter1Type;

    /// <summary>
    /// Pseudonym for the type of the second parameter of the function.
    /// </summary>
    typedef Param2T Parameter2Type;

    /// <summary>
    /// Pseudonym for the return type of the function.
    /// </summary>
    typedef ReturnValueT ReturnType;


    // CONSTRUCTORS
    // ---------------

    /// <summary>
    /// Default constructor. Delgates are considered as null when they have not been assigned to a function.
    /// </summary>
    Delegate()
    {
    }

    /// <summary>
    /// Constructor that receives an object and one of its methods.
    /// </summary>
    /// <typeparam name="ClassT">The class where the method is defined. It can be an ancestor of the object's class.</typeparam>
    /// <typeparam name="ObjectT">The type of the object whose method is to be called.</typeparam>
    /// <param name="pThis">[IN] The object whose method is to be called.</param>
    /// <param name="pFunction">[IN] The method to be called.</param>
    template < class ClassT, class ObjectT >
    Delegate(ObjectT* pThis, ReturnValueT (ClassT::* pFunction)( Param1T p1, Param2T p2 )) : BaseType(pThis, pFunction)
    {
    }

    /// <summary>
    /// Constructor that receives a constant object and one of its methods (which must be constant too).
    /// </summary>
    /// <typeparam name="ClassT">The class where the method is defined. It can be an ancestor of the object's class.</typeparam>
    /// <typeparam name="ObjectT">The type of the object whose method is to be called.</typeparam>
    /// <param name="pThis">[IN] The constant object whose method is to be called.</param>
    /// <param name="pFunction">[IN] The constant method to be called.</param>
    template < class ClassT, class ObjectT >
    Delegate(const ObjectT* pThis, ReturnValueT (ClassT::* pFunction)( Param1T p1, Param2T p2 ) const) : BaseType(pThis, pFunction)
    {
    }

    /// <summary>
    /// Constructor that receives a function.
    /// </summary>
    /// <param name="pFunction">[IN] The function to be called.</param>
    Delegate(ReturnValueT (*pFunction)( Param1T p1, Param2T p2 )) : BaseType(pFunction)
    {
    }

    // METHODS
    // ---------------

    /// <summary>
    /// Assignment operator that copies a delegate.
    /// </summary>
    /// <param name="delegate">[IN] The delegate to copy.</param>
    /// <returns>
    /// A reference to the resident object.
    /// </returns>
    Delegate& operator=(const Delegate &delegate)
    {
        m_closure.CopyFrom(this, delegate.m_closure);
        return *this;
    }

    /// <summary>
    /// Calls the stored function for the stored object, if any.
    /// </summary>
    /// <param name="p1">[IN] The first parameter of the function.</param>
    /// <param name="p2">[IN] The second parameter of the function.</param>
    /// <returns>
    /// The value returned by the function, if any.
    /// </returns>
    ReturnValueT operator() (Param1T p1, Param2T p2) const
    {
        Z_ASSERT_ERROR(!this->IsNull(), "The delegate is null, calling to the function will fail");
        return (m_closure.GetClosureThis()->*(m_closure.GetClosureMemPtr()))(p1, p2);
    }
    
    /// <summary>
    /// Equality operator that checks whether two delegates contain the same function or not. If they contain the same method, 
    /// it checks whether they belong to the same object.
    /// </summary>
    /// <param name="delegate">[IN] The delegate to compare to.</param>
    /// <returns>
    /// True if both delegates contain the same function or, in case they are methods, if they contain the same method of the same object; False otherwise.
    /// </returns>
    bool operator==(const Delegate &delegate) const
    {
        return m_closure.IsEqual(delegate.m_closure);
    }
    
    /// <summary>
    /// Inequality operator that checks whether two delegates do not contain the same function. If they contain the same method, 
    /// it checks whether they belong to the same object.
    /// </summary>
    /// <param name="delegate">[IN] The delegate to compare to.</param>
    /// <returns>
    /// True if delegates contain different functions or, in case they are methods, if they contain the same method of different objects; False otherwise.
    /// </returns>
    bool operator!=(const Delegate &delegate) const
    {
        return !m_closure.IsEqual(delegate.m_closure);
    }


    // PROPERTIES
    // ---------------

    /// <summary>
    /// Gets the number of parameters of the function.
    /// </summary>
    /// <returns>
    /// The number of parameters of the function.
    /// </returns>
    static const unsigned int& GetNumberOfParameters()
    {
        return Delegate::NUMBER_OF_PARAMETERS;
    }

    /// <summary>
    /// Indicates whether the delegate is null or not. Delegates are null when they are not assigned to any function.
    /// </summary>
    /// <returns>
    /// True if the delegate is True; False otherwise.
    /// </returns>
    bool IsNull() const
    {
        return !m_closure;
    }

    // ATTRIBUTES
    // ---------------
private:

    /// <summary>
    /// The number of parameters of the function.
    /// </summary>
    static const unsigned int NUMBER_OF_PARAMETERS;
};

// STATIC MEMBERS INITIALIZATION
// --------------------------------
template<typename ReturnValueT, class Param1T, class Param2T>
const unsigned int Delegate< ReturnValueT ( Param1T, Param2T ) >::NUMBER_OF_PARAMETERS = 2;


/// <summary>
/// Represents a delegate. Delegates are a kind of sophisticated pointers-to-function; they can store
/// a reference to any kind of function: "free" functions, static methods and non-static methods, both
/// virtual and non-virtual. In the case of non-static methods, a reference to the class instance to which
/// the method refers to is stored too.
/// </summary>
/// <remarks>
/// Delegates may be null if they have never been assigned to any function. They can be assigned as
/// many times as necessary.<br/>
/// Delegates are used as if they were normal functions, passing arguments between
/// the brackets.<br/>
/// <b>Known limitations</b><br/>
/// At the moment, it is not possible to create a delegate that stored a constant method of a class when
/// there is an non-constant overload of such method. The non-const overload will be used always instead.
/// </remarks>
/// <typeparam name="ReturnValueT">The type of the return value.</typeparam>
/// <typeparam name="Param1T">The type of the first parameter.</typeparam>
/// <typeparam name="Param2T">The type of the second parameter.</typeparam>
/// <typeparam name="Param3T">The type of the third parameter.</typeparam>
template<typename ReturnValueT, class Param1T, class Param2T, class Param3T>
class Delegate< ReturnValueT ( Param1T, Param2T, Param3T ) > : protected Internals::FastDelegate3 < Param1T, Param2T, Param3T, ReturnValueT >
{

    /// <summary>
    /// Pseudonym for the base class.
    /// </summary>
    typedef FastDelegate3 < Param1T, Param2T, Param3T, ReturnValueT > BaseType;

    using BaseType::m_closure;

    /// <summary>
    /// Pseudonym for this class.
    /// </summary>
    typedef Delegate SelfType;

public:

    /// <summary>
    /// Pseudonym for the type of the first parameter of the function.
    /// </summary>
    typedef Param1T Parameter1Type;

    /// <summary>
    /// Pseudonym for the type of the second parameter of the function.
    /// </summary>
    typedef Param2T Parameter2Type;

    /// <summary>
    /// Pseudonym for the type of the third parameter of the function.
    /// </summary>
    typedef Param3T Parameter3Type;

    /// <summary>
    /// Pseudonym for the return type of the function.
    /// </summary>
    typedef ReturnValueT ReturnType;


    // CONSTRUCTORS
    // ---------------

    /// <summary>
    /// Default constructor. Delgates are considered as null when they have not been assigned to a function.
    /// </summary>
    Delegate()
    {
    }

    /// <summary>
    /// Constructor that receives an object and one of its methods.
    /// </summary>
    /// <typeparam name="ClassT">The class where the method is defined. It can be an ancestor of the object's class.</typeparam>
    /// <typeparam name="ObjectT">The type of the object whose method is to be called.</typeparam>
    /// <param name="pThis">[IN] The object whose method is to be called.</param>
    /// <param name="pFunction">[IN] The method to be called.</param>
    template < class ClassT, class ObjectT >
    Delegate(ObjectT* pThis, ReturnValueT (ClassT::* pFunction)( Param1T p1, Param2T p2, Param3T p3 )) : BaseType(pThis, pFunction)
    {
    }

    /// <summary>
    /// Constructor that receives a constant object and one of its methods (which must be constant too).
    /// </summary>
    /// <typeparam name="ClassT">The class where the method is defined. It can be an ancestor of the object's class.</typeparam>
    /// <typeparam name="ObjectT">The type of the object whose method is to be called.</typeparam>
    /// <param name="pThis">[IN] The constant object whose method is to be called.</param>
    /// <param name="pFunction">[IN] The constant method to be called.</param>
    template < class ClassT, class ObjectT >
    Delegate(const ObjectT* pThis, ReturnValueT (ClassT::* pFunction)( Param1T p1, Param2T p2, Param3T p3 ) const) : BaseType(pThis, pFunction)
    {
    }

    /// <summary>
    /// Constructor that receives a function.
    /// </summary>
    /// <param name="pFunction">[IN] The function to be called.</param>
    Delegate(ReturnValueT (*pFunction)( Param1T p1, Param2T p2, Param3T p3 )) : BaseType(pFunction)
    {
    }

    // METHODS
    // ---------------

    /// <summary>
    /// Assignment operator that copies a delegate.
    /// </summary>
    /// <param name="delegate">[IN] The delegate to copy.</param>
    /// <returns>
    /// A reference to the resident object.
    /// </returns>
    Delegate& operator=(const Delegate &delegate)
    {
        m_closure.CopyFrom(this, delegate.m_closure);
        return *this;
    }

    /// <summary>
    /// Calls the stored function for the stored object, if any.
    /// </summary>
    /// <param name="p1">[IN] The first parameter of the function.</param>
    /// <param name="p2">[IN] The second parameter of the function.</param>
    /// <param name="p3">[IN] The third parameter of the function.</param>
    /// <returns>
    /// The value returned by the function, if any.
    /// </returns>
    ReturnValueT operator() (Param1T p1, Param2T p2, Param3T p3) const
    {
        Z_ASSERT_ERROR(!this->IsNull(), "The delegate is null, calling to the function will fail");
        return (m_closure.GetClosureThis()->*(m_closure.GetClosureMemPtr()))(p1, p2, p3);
    }
    
    /// <summary>
    /// Equality operator that checks whether two delegates contain the same function or not. If they contain the same method, 
    /// it checks whether they belong to the same object.
    /// </summary>
    /// <param name="delegate">[IN] The delegate to compare to.</param>
    /// <returns>
    /// True if both delegates contain the same function or, in case they are methods, if they contain the same method of the same object; False otherwise.
    /// </returns>
    bool operator==(const Delegate &delegate) const
    {
        return m_closure.IsEqual(delegate.m_closure);
    }
    
    /// <summary>
    /// Inequality operator that checks whether two delegates do not contain the same function. If they contain the same method, 
    /// it checks whether they belong to the same object.
    /// </summary>
    /// <param name="delegate">[IN] The delegate to compare to.</param>
    /// <returns>
    /// True if delegates contain different functions or, in case they are methods, if they contain the same method of different objects; False otherwise.
    /// </returns>
    bool operator!=(const Delegate &delegate) const
    {
        return !m_closure.IsEqual(delegate.m_closure);
    }


    // PROPERTIES
    // ---------------

    /// <summary>
    /// Gets the number of parameters of the function.
    /// </summary>
    /// <returns>
    /// The number of parameters of the function.
    /// </returns>
    static const unsigned int& GetNumberOfParameters()
    {
        return Delegate::NUMBER_OF_PARAMETERS;
    }

    /// <summary>
    /// Indicates whether the delegate is null or not. Delegates are null when they are not assigned to any function.
    /// </summary>
    /// <returns>
    /// True if the delegate is True; False otherwise.
    /// </returns>
    bool IsNull() const
    {
        return !m_closure;
    }


    // ATTRIBUTES
    // ---------------
private:

    /// <summary>
    /// The number of parameters of the function.
    /// </summary>
    static const unsigned int NUMBER_OF_PARAMETERS;
};

// STATIC MEMBERS INITIALIZATION
// --------------------------------
template<typename ReturnValueT, class Param1T, class Param2T, class Param3T>
const unsigned int Delegate< ReturnValueT ( Param1T, Param2T, Param3T ) >::NUMBER_OF_PARAMETERS = 3;


/// <summary>
/// Represents a delegate. Delegates are a kind of sophisticated pointers-to-function; they can store
/// a reference to any kind of function: "free" functions, static methods and non-static methods, both
/// virtual and non-virtual. In the case of non-static methods, a reference to the class instance to which
/// the method refers to is stored too.
/// </summary>
/// <remarks>
/// Delegates may be null if they have never been assigned to any function. They can be assigned as
/// many times as necessary.<br/>
/// Delegates are used as if they were normal functions, passing arguments between
/// the brackets.<br/>
/// <b>Known limitations</b><br/>
/// At the moment, it is not possible to create a delegate that stored a constant method of a class when
/// there is an non-constant overload of such method. The non-const overload will be used always instead.
/// </remarks>
/// <typeparam name="ReturnValueT">The type of the return value.</typeparam>
/// <typeparam name="Param1T">The type of the first parameter.</typeparam>
/// <typeparam name="Param2T">The type of the second parameter.</typeparam>
/// <typeparam name="Param3T">The type of the third parameter.</typeparam>
/// <typeparam name="Param4T">The type of the forth parameter.</typeparam>
template<typename ReturnValueT, class Param1T, class Param2T, class Param3T, class Param4T>
class Delegate< ReturnValueT ( Param1T, Param2T, Param3T, Param4T ) > : protected Internals::FastDelegate4 < Param1T, Param2T, Param3T, Param4T, ReturnValueT >
{

    /// <summary>
    /// Pseudonym for the base class.
    /// </summary>
    typedef FastDelegate4 < Param1T, Param2T, Param3T, Param4T, ReturnValueT > BaseType;

    using BaseType::m_closure;

    /// <summary>
    /// Pseudonym for this class.
    /// </summary>
    typedef Delegate SelfType;

public:

    /// <summary>
    /// Pseudonym for the type of the first parameter of the function.
    /// </summary>
    typedef Param1T Parameter1Type;

    /// <summary>
    /// Pseudonym for the type of the second parameter of the function.
    /// </summary>
    typedef Param2T Parameter2Type;

    /// <summary>
    /// Pseudonym for the type of the third parameter of the function.
    /// </summary>
    typedef Param3T Parameter3Type;

    /// <summary>
    /// Pseudonym for the type of the forth parameter of the function.
    /// </summary>
    typedef Param4T Parameter4Type;

    /// <summary>
    /// Pseudonym for the return type of the function.
    /// </summary>
    typedef ReturnValueT ReturnType;


    // CONSTRUCTORS
    // ---------------

    /// <summary>
    /// Default constructor. Delgates are considered as null when they have not been assigned to a function.
    /// </summary>
    Delegate()
    {
    }

    /// <summary>
    /// Constructor that receives an object and one of its methods.
    /// </summary>
    /// <typeparam name="ClassT">The class where the method is defined. It can be an ancestor of the object's class.</typeparam>
    /// <typeparam name="ObjectT">The type of the object whose method is to be called.</typeparam>
    /// <param name="pThis">[IN] The object whose method is to be called.</param>
    /// <param name="pFunction">[IN] The method to be called.</param>
    template < class ClassT, class ObjectT >
    Delegate(ObjectT* pThis, ReturnValueT (ClassT::* pFunction)( Param1T p1, Param2T p2, Param3T p3, Param4T p4 )) : BaseType(pThis, pFunction)
    {
    }

    /// <summary>
    /// Constructor that receives a constant object and one of its methods (which must be constant too).
    /// </summary>
    /// <typeparam name="ClassT">The class where the method is defined. It can be an ancestor of the object's class.</typeparam>
    /// <typeparam name="ObjectT">The type of the object whose method is to be called.</typeparam>
    /// <param name="pThis">[IN] The constant object whose method is to be called.</param>
    /// <param name="pFunction">[IN] The constant method to be called.</param>
    template < class ClassT, class ObjectT >
    Delegate(const ObjectT* pThis, ReturnValueT (ClassT::* pFunction)( Param1T p1, Param2T p2, Param3T p3, Param4T p4 ) const) : BaseType(pThis, pFunction)
    {
    }

    /// <summary>
    /// Constructor that receives a function.
    /// </summary>
    /// <param name="pFunction">[IN] The function to be called.</param>
    Delegate(ReturnValueT (*pFunction)( Param1T p1, Param2T p2, Param3T p3, Param4T p4 )) : BaseType(pFunction)
    {
    }

    // METHODS
    // ---------------

    /// <summary>
    /// Assignment operator that copies a delegate.
    /// </summary>
    /// <param name="delegate">[IN] The delegate to copy.</param>
    /// <returns>
    /// A reference to the resident object.
    /// </returns>
    Delegate& operator=(const Delegate &delegate)
    {
        m_closure.CopyFrom(this, delegate.m_closure);
        return *this;
    }

    /// <summary>
    /// Calls the stored function for the stored object, if any.
    /// </summary>
    /// <param name="p1">[IN] The first parameter of the function.</param>
    /// <param name="p2">[IN] The second parameter of the function.</param>
    /// <param name="p3">[IN] The third parameter of the function.</param>
    /// <param name="p4">[IN] The forth parameter of the function.</param>
    /// <returns>
    /// The value returned by the function, if any.
    /// </returns>
    ReturnValueT operator() (Param1T p1, Param2T p2, Param3T p3, Param4T p4) const
    {
        Z_ASSERT_ERROR(!this->IsNull(), "The delegate is null, calling to the function will fail");
        return (m_closure.GetClosureThis()->*(m_closure.GetClosureMemPtr()))(p1, p2, p3, p4);
    }
    
    /// <summary>
    /// Equality operator that checks whether two delegates contain the same function or not. If they contain the same method, 
    /// it checks whether they belong to the same object.
    /// </summary>
    /// <param name="delegate">[IN] The delegate to compare to.</param>
    /// <returns>
    /// True if both delegates contain the same function or, in case they are methods, if they contain the same method of the same object; False otherwise.
    /// </returns>
    bool operator==(const Delegate &delegate) const
    {
        return m_closure.IsEqual(delegate.m_closure);
    }
    
    /// <summary>
    /// Inequality operator that checks whether two delegates do not contain the same function. If they contain the same method, 
    /// it checks whether they belong to the same object.
    /// </summary>
    /// <param name="delegate">[IN] The delegate to compare to.</param>
    /// <returns>
    /// True if delegates contain different functions or, in case they are methods, if they contain the same method of different objects; False otherwise.
    /// </returns>
    bool operator!=(const Delegate &delegate) const
    {
        return !m_closure.IsEqual(delegate.m_closure);
    }


    // PROPERTIES
    // ---------------

    /// <summary>
    /// Gets the number of parameters of the function.
    /// </summary>
    /// <returns>
    /// The number of parameters of the function.
    /// </returns>
    static const unsigned int& GetNumberOfParameters()
    {
        return Delegate::NUMBER_OF_PARAMETERS;
    }

    /// <summary>
    /// Indicates whether the delegate is null or not. Delegates are null when they are not assigned to any function.
    /// </summary>
    /// <returns>
    /// True if the delegate is True; False otherwise.
    /// </returns>
    bool IsNull() const
    {
        return !m_closure;
    }


    // ATTRIBUTES
    // ---------------
private:

    /// <summary>
    /// The number of parameters of the function.
    /// </summary>
    static const unsigned int NUMBER_OF_PARAMETERS;
};

// STATIC MEMBERS INITIALIZATION
// --------------------------------
template<typename ReturnValueT, class Param1T, class Param2T, class Param3T, class Param4T>
const unsigned int Delegate< ReturnValueT ( Param1T, Param2T, Param3T, Param4T ) >::NUMBER_OF_PARAMETERS = 4;


/// <summary>
/// Represents a delegate. Delegates are a kind of sophisticated pointers-to-function; they can store
/// a reference to any kind of function: "free" functions, static methods and non-static methods, both
/// virtual and non-virtual. In the case of non-static methods, a reference to the class instance to which
/// the method refers to is stored too.
/// </summary>
/// <remarks>
/// Delegates may be null if they have never been assigned to any function. They can be assigned as
/// many times as necessary.<br/>
/// Delegates are used as if they were normal functions, passing arguments between
/// the brackets.<br/>
/// <b>Known limitations</b><br/>
/// At the moment, it is not possible to create a delegate that stored a constant method of a class when
/// there is an non-constant overload of such method. The non-const overload will be used always instead.
/// </remarks>
/// <typeparam name="ReturnValueT">The type of the return value.</typeparam>
/// <typeparam name="Param1T">The type of the first parameter.</typeparam>
/// <typeparam name="Param2T">The type of the second parameter.</typeparam>
/// <typeparam name="Param3T">The type of the third parameter.</typeparam>
/// <typeparam name="Param4T">The type of the forth parameter.</typeparam>
/// <typeparam name="Param5T">The type of the fifth parameter.</typeparam>
template<typename ReturnValueT, class Param1T, class Param2T, class Param3T, class Param4T, class Param5T>
class Delegate< ReturnValueT ( Param1T, Param2T, Param3T, Param4T, Param5T ) > : protected Internals::FastDelegate5 < Param1T, Param2T, Param3T, Param4T, Param5T, ReturnValueT >
{

    /// <summary>
    /// Pseudonym for the base class.
    /// </summary>
    typedef FastDelegate5 < Param1T, Param2T, Param3T, Param4T, Param5T, ReturnValueT > BaseType;

    using BaseType::m_closure;

    /// <summary>
    /// Pseudonym for this class.
    /// </summary>
    typedef Delegate SelfType;

public:

    /// <summary>
    /// Pseudonym for the type of the first parameter of the function.
    /// </summary>
    typedef Param1T Parameter1Type;

    /// <summary>
    /// Pseudonym for the type of the second parameter of the function.
    /// </summary>
    typedef Param2T Parameter2Type;

    /// <summary>
    /// Pseudonym for the type of the third parameter of the function.
    /// </summary>
    typedef Param3T Parameter3Type;

    /// <summary>
    /// Pseudonym for the type of the forth parameter of the function.
    /// </summary>
    typedef Param4T Parameter4Type;

    /// <summary>
    /// Pseudonym for the type of the fifth parameter of the function.
    /// </summary>
    typedef Param5T Parameter5Type;

    /// <summary>
    /// Pseudonym for the return type of the function.
    /// </summary>
    typedef ReturnValueT ReturnType;


    // CONSTRUCTORS
    // ---------------

    /// <summary>
    /// Default constructor. Delgates are considered as null when they have not been assigned to a function.
    /// </summary>
    Delegate()
    {
    }

    /// <summary>
    /// Constructor that receives an object and one of its methods.
    /// </summary>
    /// <typeparam name="ClassT">The class where the method is defined. It can be an ancestor of the object's class.</typeparam>
    /// <typeparam name="ObjectT">The type of the object whose method is to be called.</typeparam>
    /// <param name="pThis">[IN] The object whose method is to be called.</param>
    /// <param name="pFunction">[IN] The method to be called.</param>
    template < class ClassT, class ObjectT >
    Delegate(ObjectT* pThis, ReturnValueT (ClassT::* pFunction)( Param1T p1, Param2T p2, Param3T p3, Param4T p4, Param5T p5 ))
                                                            : BaseType(pThis, pFunction)
    {
    }

    /// <summary>
    /// Constructor that receives a constant object and one of its methods (which must be constant too).
    /// </summary>
    /// <typeparam name="ClassT">The class where the method is defined. It can be an ancestor of the object's class.</typeparam>
    /// <typeparam name="ObjectT">The type of the object whose method is to be called.</typeparam>
    /// <param name="pThis">[IN] The constant object whose method is to be called.</param>
    /// <param name="pFunction">[IN] The constant method to be called.</param>
    template < class ClassT, class ObjectT >
    Delegate(const ObjectT* pThis, ReturnValueT (ClassT::* pFunction)( Param1T p1, Param2T p2, Param3T p3, Param4T p4, Param5T p5 ) const)
                                                            : BaseType(pThis, pFunction)
    {
    }

    /// <summary>
    /// Constructor that receives a function.
    /// </summary>
    /// <param name="pFunction">[IN] The function to be called.</param>
    Delegate(ReturnValueT (*pFunction)( Param1T p1, Param2T p2, Param3T p3, Param4T p4, Param5T p5 )) : BaseType(pFunction)
    {
    }

    // METHODS
    // ---------------

    /// <summary>
    /// Assignment operator that copies a delegate.
    /// </summary>
    /// <param name="delegate">[IN] The delegate to copy.</param>
    /// <returns>
    /// A reference to the resident object.
    /// </returns>
    Delegate& operator=(const Delegate &delegate)
    {
        m_closure.CopyFrom(this, delegate.m_closure);
        return *this;
    }

    /// <summary>
    /// Calls the stored function for the stored object, if any.
    /// </summary>
    /// <param name="p1">[IN] The first parameter of the function.</param>
    /// <param name="p2">[IN] The second parameter of the function.</param>
    /// <param name="p3">[IN] The third parameter of the function.</param>
    /// <param name="p4">[IN] The forth parameter of the function.</param>
    /// <param name="p5">[IN] The fifth parameter of the function.</param>
    /// <returns>
    /// The value returned by the function, if any.
    /// </returns>
    ReturnValueT operator() (Param1T p1, Param2T p2, Param3T p3, Param4T p4, Param5T p5) const
    {
        Z_ASSERT_ERROR(!this->IsNull(), "The delegate is null, calling to the function will fail");
        return (m_closure.GetClosureThis()->*(m_closure.GetClosureMemPtr()))(p1, p2, p3, p4, p5);
    }
    
    /// <summary>
    /// Equality operator that checks whether two delegates contain the same function or not. If they contain the same method, 
    /// it checks whether they belong to the same object.
    /// </summary>
    /// <param name="delegate">[IN] The delegate to compare to.</param>
    /// <returns>
    /// True if both delegates contain the same function or, in case they are methods, if they contain the same method of the same object; False otherwise.
    /// </returns>
    bool operator==(const Delegate &delegate) const
    {
        return m_closure.IsEqual(delegate.m_closure);
    }
    
    /// <summary>
    /// Inequality operator that checks whether two delegates do not contain the same function. If they contain the same method, 
    /// it checks whether they belong to the same object.
    /// </summary>
    /// <param name="delegate">[IN] The delegate to compare to.</param>
    /// <returns>
    /// True if delegates contain different functions or, in case they are methods, if they contain the same method of different objects; False otherwise.
    /// </returns>
    bool operator!=(const Delegate &delegate) const
    {
        return !m_closure.IsEqual(delegate.m_closure);
    }


    // PROPERTIES
    // ---------------

    /// <summary>
    /// Gets the number of parameters of the function.
    /// </summary>
    /// <returns>
    /// The number of parameters of the function.
    /// </returns>
    static const unsigned int& GetNumberOfParameters()
    {
        return Delegate::NUMBER_OF_PARAMETERS;
    }

    /// <summary>
    /// Indicates whether the delegate is null or not. Delegates are null when they are not assigned to any function.
    /// </summary>
    /// <returns>
    /// True if the delegate is True; False otherwise.
    /// </returns>
    bool IsNull() const
    {
        return !m_closure;
    }

    // ATTRIBUTES
    // ---------------
private:

    /// <summary>
    /// The number of parameters of the function.
    /// </summary>
    static const unsigned int NUMBER_OF_PARAMETERS;
};

// STATIC MEMBERS INITIALIZATION
// --------------------------------
template<typename ReturnValueT, class Param1T, class Param2T, class Param3T, class Param4T, class Param5T>
const unsigned int Delegate< ReturnValueT ( Param1T, Param2T, Param3T, Param4T, Param5T ) > ::NUMBER_OF_PARAMETERS = 5;


/// <summary>
/// Represents a delegate. Delegates are a kind of sophisticated pointers-to-function; they can store
/// a reference to any kind of function: "free" functions, static methods and non-static methods, both
/// virtual and non-virtual. In the case of non-static methods, a reference to the class instance to which
/// the method refers to is stored too.
/// </summary>
/// <remarks>
/// Delegates may be null if they have never been assigned to any function. They can be assigned as
/// many times as necessary.<br/>
/// Delegates are used as if they were normal functions, passing arguments between
/// the brackets.<br/>
/// <b>Known limitations</b><br/>
/// At the moment, it is not possible to create a delegate that stored a constant method of a class when
/// there is an non-constant overload of such method. The non-const overload will be used always instead.
/// </remarks>
/// <typeparam name="ReturnValueT">The type of the return value.</typeparam>
/// <typeparam name="Param1T">The type of the first parameter.</typeparam>
/// <typeparam name="Param2T">The type of the second parameter.</typeparam>
/// <typeparam name="Param3T">The type of the third parameter.</typeparam>
/// <typeparam name="Param4T">The type of the forth parameter.</typeparam>
/// <typeparam name="Param5T">The type of the fifth parameter.</typeparam>
/// <typeparam name="Param6T">The type of the sixth parameter.</typeparam>
template<typename ReturnValueT, class Param1T, class Param2T, class Param3T, class Param4T, class Param5T, class Param6T>
class Delegate< ReturnValueT ( Param1T, Param2T, Param3T, Param4T, Param5T, Param6T ) > : protected Internals::FastDelegate6 < Param1T, Param2T, Param3T, Param4T, Param5T, Param6T, ReturnValueT >
{

    /// <summary>
    /// Pseudonym for the base class.
    /// </summary>
    typedef FastDelegate6 < Param1T, Param2T, Param3T, Param4T, Param5T, Param6T, ReturnValueT > BaseType;

    using BaseType::m_closure;

    /// <summary>
    /// Pseudonym for this class.
    /// </summary>
    typedef Delegate SelfType;

public:

    /// <summary>
    /// Pseudonym for the type of the first parameter of the function.
    /// </summary>
    typedef Param1T Parameter1Type;

    /// <summary>
    /// Pseudonym for the type of the second parameter of the function.
    /// </summary>
    typedef Param2T Parameter2Type;

    /// <summary>
    /// Pseudonym for the type of the third parameter of the function.
    /// </summary>
    typedef Param3T Parameter3Type;

    /// <summary>
    /// Pseudonym for the type of the forth parameter of the function.
    /// </summary>
    typedef Param4T Parameter4Type;

    /// <summary>
    /// Pseudonym for the type of the fifth parameter of the function.
    /// </summary>
    typedef Param5T Parameter5Type;

    /// <summary>
    /// Pseudonym for the type of the sixth parameter of the function.
    /// </summary>
    typedef Param6T Parameter6Type;

    /// <summary>
    /// Pseudonym for the return type of the function.
    /// </summary>
    typedef ReturnValueT ReturnType;


    // CONSTRUCTORS
    // ---------------

    /// <summary>
    /// Default constructor. Delgates are considered as null when they have not been assigned to a function.
    /// </summary>
    Delegate()
    {
    }

    /// <summary>
    /// Constructor that receives an object and one of its methods.
    /// </summary>
    /// <typeparam name="ClassT">The class where the method is defined. It can be an ancestor of the object's class.</typeparam>
    /// <typeparam name="ObjectT">The type of the object whose method is to be called.</typeparam>
    /// <param name="pThis">[IN] The object whose method is to be called.</param>
    /// <param name="pFunction">[IN] The method to be called.</param>
    template < class ClassT, class ObjectT >
    Delegate(ObjectT* pThis, ReturnValueT (ClassT::* pFunction)( Param1T p1, Param2T p2, Param3T p3, Param4T p4, Param5T p5, Param6T p6 ))
                                                    : BaseType(pThis, pFunction)
    {
    }

    /// <summary>
    /// Constructor that receives a constant object and one of its methods (which must be constant too).
    /// </summary>
    /// <typeparam name="ClassT">The class where the method is defined. It can be an ancestor of the object's class.</typeparam>
    /// <typeparam name="ObjectT">The type of the object whose method is to be called.</typeparam>
    /// <param name="pThis">[IN] The constant object whose method is to be called.</param>
    /// <param name="pFunction">[IN] The constant method to be called.</param>
    template < class ClassT, class ObjectT >
    Delegate(const ObjectT* pThis, ReturnValueT (ClassT::* pFunction)( Param1T p1, Param2T p2, Param3T p3, Param4T p4, Param5T p5, Param6T p6 ) const)
                                                    : BaseType(pThis, pFunction)
    {
    }

    /// <summary>
    /// Constructor that receives a function.
    /// </summary>
    /// <param name="pFunction">[IN] The function to be called.</param>
    Delegate(ReturnValueT (*pFunction)( Param1T p1, Param2T p2, Param3T p3, Param4T p4, Param5T p5, Param6T p6 ))
                                                    : BaseType(pFunction)
    {
    }

    // METHODS
    // ---------------

    /// <summary>
    /// Assignment operator that copies a delegate.
    /// </summary>
    /// <param name="delegate">[IN] The delegate to copy.</param>
    /// <returns>
    /// A reference to the resident object.
    /// </returns>
    Delegate& operator=(const Delegate &delegate)
    {
        m_closure.CopyFrom(this, delegate.m_closure);
        return *this;
    }

    /// <summary>
    /// Calls the stored function for the stored object, if any.
    /// </summary>
    /// <param name="p1">[IN] The first parameter of the function.</param>
    /// <param name="p2">[IN] The second parameter of the function.</param>
    /// <param name="p3">[IN] The third parameter of the function.</param>
    /// <param name="p4">[IN] The forth parameter of the function.</param>
    /// <param name="p5">[IN] The fifth parameter of the function.</param>
    /// <param name="p6">[IN] The sixth parameter of the function.</param>
    /// <returns>
    /// The value returned by the function, if any.
    /// </returns>
    ReturnValueT operator() (Param1T p1, Param2T p2, Param3T p3, Param4T p4, Param5T p5, Param6T p6) const
    {
        Z_ASSERT_ERROR(!this->IsNull(), "The delegate is null, calling to the function will fail");
        return (m_closure.GetClosureThis()->*(m_closure.GetClosureMemPtr()))(p1, p2, p3, p4, p5, p6);
    }
    
    /// <summary>
    /// Equality operator that checks whether two delegates contain the same function or not. If they contain the same method, 
    /// it checks whether they belong to the same object.
    /// </summary>
    /// <param name="delegate">[IN] The delegate to compare to.</param>
    /// <returns>
    /// True if both delegates contain the same function or, in case they are methods, if they contain the same method of the same object; False otherwise.
    /// </returns>
    bool operator==(const Delegate &delegate) const
    {
        return m_closure.IsEqual(delegate.m_closure);
    }
    
    /// <summary>
    /// Inequality operator that checks whether two delegates do not contain the same function. If they contain the same method, 
    /// it checks whether they belong to the same object.
    /// </summary>
    /// <param name="delegate">[IN] The delegate to compare to.</param>
    /// <returns>
    /// True if delegates contain different functions or, in case they are methods, if they contain the same method of different objects; False otherwise.
    /// </returns>
    bool operator!=(const Delegate &delegate) const
    {
        return !m_closure.IsEqual(delegate.m_closure);
    }


    // PROPERTIES
    // ---------------

    /// <summary>
    /// Gets the number of parameters of the function.
    /// </summary>
    /// <returns>
    /// The number of parameters of the function.
    /// </returns>
    static const unsigned int& GetNumberOfParameters()
    {
        return Delegate::NUMBER_OF_PARAMETERS;
    }

    /// <summary>
    /// Indicates whether the delegate is null or not. Delegates are null when they are not assigned to any function.
    /// </summary>
    /// <returns>
    /// True if the delegate is True; False otherwise.
    /// </returns>
    bool IsNull() const
    {
        return !m_closure;
    }

    // ATTRIBUTES
    // ---------------
private:

    /// <summary>
    /// The number of parameters of the function.
    /// </summary>
    static const unsigned int NUMBER_OF_PARAMETERS;
};

// STATIC MEMBERS INITIALIZATION
// --------------------------------
template<typename ReturnValueT, class Param1T, class Param2T, class Param3T, class Param4T, class Param5T, class Param6T>
const unsigned int Delegate< ReturnValueT ( Param1T, Param2T, Param3T, Param4T, Param5T, Param6T ) > ::NUMBER_OF_PARAMETERS = 6;


/// <summary>
/// Represents a delegate. Delegates are a kind of sophisticated pointers-to-function; they can store
/// a reference to any kind of function: "free" functions, static methods and non-static methods, both
/// virtual and non-virtual. In the case of non-static methods, a reference to the class instance to which
/// the method refers to is stored too.
/// </summary>
/// <remarks>
/// Delegates may be null if they have never been assigned to any function. They can be assigned as
/// many times as necessary.<br/>
/// Delegates are used as if they were normal functions, passing arguments between
/// the brackets.<br/>
/// <b>Known limitations</b><br/>
/// At the moment, it is not possible to create a delegate that stored a constant method of a class when
/// there is an non-constant overload of such method. The non-const overload will be used always instead.
/// </remarks>
/// <typeparam name="ReturnValueT">The type of the return value.</typeparam>
/// <typeparam name="Param1T">The type of the first parameter.</typeparam>
/// <typeparam name="Param2T">The type of the second parameter.</typeparam>
/// <typeparam name="Param3T">The type of the third parameter.</typeparam>
/// <typeparam name="Param4T">The type of the forth parameter.</typeparam>
/// <typeparam name="Param5T">The type of the fifth parameter.</typeparam>
/// <typeparam name="Param6T">The type of the sixth parameter.</typeparam>
/// <typeparam name="Param7T">The type of the seventh parameter.</typeparam>
template<typename ReturnValueT, class Param1T, class Param2T, class Param3T, class Param4T, class Param5T, class Param6T, class Param7T>
class Delegate< ReturnValueT ( Param1T, Param2T, Param3T, Param4T, Param5T, Param6T, Param7T ) > : protected Internals::FastDelegate7 < Param1T, Param2T, Param3T, Param4T, Param5T, Param6T, Param7T, ReturnValueT >
{

    /// <summary>
    /// Pseudonym for the base class.
    /// </summary>
    typedef FastDelegate7 < Param1T, Param2T, Param3T, Param4T, Param5T, Param6T, Param7T, ReturnValueT > BaseType;

    using BaseType::m_closure;

    /// <summary>
    /// Pseudonym for this class.
    /// </summary>
    typedef Delegate SelfType;

public:

    /// <summary>
    /// Pseudonym for the type of the first parameter of the function.
    /// </summary>
    typedef Param1T Parameter1Type;

    /// <summary>
    /// Pseudonym for the type of the second parameter of the function.
    /// </summary>
    typedef Param2T Parameter2Type;

    /// <summary>
    /// Pseudonym for the type of the third parameter of the function.
    /// </summary>
    typedef Param3T Parameter3Type;

    /// <summary>
    /// Pseudonym for the type of the forth parameter of the function.
    /// </summary>
    typedef Param4T Parameter4Type;

    /// <summary>
    /// Pseudonym for the type of the fifth parameter of the function.
    /// </summary>
    typedef Param5T Parameter5Type;

    /// <summary>
    /// Pseudonym for the type of the sixth parameter of the function.
    /// </summary>
    typedef Param6T Parameter6Type;

    /// <summary>
    /// Pseudonym for the type of the seventh parameter of the function.
    /// </summary>
    typedef Param7T Parameter7Type;

    /// <summary>
    /// Pseudonym for the return type of the function.
    /// </summary>
    typedef ReturnValueT ReturnType;


    // CONSTRUCTORS
    // ---------------

    /// <summary>
    /// Default constructor. Delgates are considered as null when they have not been assigned to a function.
    /// </summary>
    Delegate()
    {
    }

    /// <summary>
    /// Constructor that receives an object and one of its methods.
    /// </summary>
    /// <typeparam name="ClassT">The class where the method is defined. It can be an ancestor of the object's class.</typeparam>
    /// <typeparam name="ObjectT">The type of the object whose method is to be called.</typeparam>
    /// <param name="pThis">[IN] The object whose method is to be called.</param>
    /// <param name="pFunction">[IN] The method to be called.</param>
    template < class ClassT, class ObjectT >
    Delegate(ObjectT* pThis, ReturnValueT (ClassT::* pFunction)( Param1T p1, Param2T p2, Param3T p3, Param4T p4, Param5T p5, Param6T p6, Param7T p7 ))
                                                    : BaseType(pThis, pFunction)
    {
    }

    /// <summary>
    /// Constructor that receives a constant object and one of its methods (which must be constant too).
    /// </summary>
    /// <typeparam name="ClassT">The class where the method is defined. It can be an ancestor of the object's class.</typeparam>
    /// <typeparam name="ObjectT">The type of the object whose method is to be called.</typeparam>
    /// <param name="pThis">[IN] The constant object whose method is to be called.</param>
    /// <param name="pFunction">[IN] The constant method to be called.</param>
    template < class ClassT, class ObjectT >
    Delegate(const ObjectT* pThis, ReturnValueT (ClassT::* pFunction)( Param1T p1, Param2T p2, Param3T p3, Param4T p4, Param5T p5, Param6T p6, Param7T p7 ) const)
                                                    : BaseType(pThis, pFunction)
    {
    }

    /// <summary>
    /// Constructor that receives a function.
    /// </summary>
    /// <param name="pFunction">[IN] The function to be called.</param>
    Delegate(ReturnValueT (*pFunction)( Param1T p1, Param2T p2, Param3T p3, Param4T p4, Param5T p5, Param6T p6, Param7T p7 ))
                                                    : BaseType(pFunction)
    {
    }

    // METHODS
    // ---------------

    /// <summary>
    /// Assignment operator that copies a delegate.
    /// </summary>
    /// <param name="delegate">[IN] The delegate to copy.</param>
    /// <returns>
    /// A reference to the resident object.
    /// </returns>
    Delegate& operator=(const Delegate &delegate)
    {
        m_closure.CopyFrom(this, delegate.m_closure);
        return *this;
    }

    /// <summary>
    /// Calls the stored function for the stored object, if any.
    /// </summary>
    /// <param name="p1">[IN] The first parameter of the function.</param>
    /// <param name="p2">[IN] The second parameter of the function.</param>
    /// <param name="p3">[IN] The third parameter of the function.</param>
    /// <param name="p4">[IN] The forth parameter of the function.</param>
    /// <param name="p5">[IN] The fifth parameter of the function.</param>
    /// <param name="p6">[IN] The sixth parameter of the function.</param>
    /// <param name="p7">[IN] The seventh parameter of the function.</param>
    /// <returns>
    /// The value returned by the function, if any.
    /// </returns>
    ReturnValueT operator() (Param1T p1, Param2T p2, Param3T p3, Param4T p4, Param5T p5, Param6T p6, Param7T p7) const
    {
        Z_ASSERT_ERROR(!this->IsNull(), "The delegate is null, calling to the function will fail");
        return (m_closure.GetClosureThis()->*(m_closure.GetClosureMemPtr()))(p1, p2, p3, p4, p5, p6, p7);
    }
    
    /// <summary>
    /// Equality operator that checks whether two delegates contain the same function or not. If they contain the same method, 
    /// it checks whether they belong to the same object.
    /// </summary>
    /// <param name="delegate">[IN] The delegate to compare to.</param>
    /// <returns>
    /// True if both delegates contain the same function or, in case they are methods, if they contain the same method of the same object; False otherwise.
    /// </returns>
    bool operator==(const Delegate &delegate) const
    {
        return m_closure.IsEqual(delegate.m_closure);
    }
    
    /// <summary>
    /// Inequality operator that checks whether two delegates do not contain the same function. If they contain the same method, 
    /// it checks whether they belong to the same object.
    /// </summary>
    /// <param name="delegate">[IN] The delegate to compare to.</param>
    /// <returns>
    /// True if delegates contain different functions or, in case they are methods, if they contain the same method of different objects; False otherwise.
    /// </returns>
    bool operator!=(const Delegate &delegate) const
    {
        return !m_closure.IsEqual(delegate.m_closure);
    }


    // PROPERTIES
    // ---------------

    /// <summary>
    /// Gets the number of parameters of the function.
    /// </summary>
    /// <returns>
    /// The number of parameters of the function.
    /// </returns>
    static const unsigned int& GetNumberOfParameters()
    {
        return Delegate::NUMBER_OF_PARAMETERS;
    }

    /// <summary>
    /// Indicates whether the delegate is null or not. Delegates are null when they are not assigned to any function.
    /// </summary>
    /// <returns>
    /// True if the delegate is True; False otherwise.
    /// </returns>
    bool IsNull() const
    {
        return !m_closure;
    }

    // ATTRIBUTES
    // ---------------
private:

    /// <summary>
    /// The number of parameters of the function.
    /// </summary>
    static const unsigned int NUMBER_OF_PARAMETERS;
};

// STATIC MEMBERS INITIALIZATION
// --------------------------------
template<typename ReturnValueT, class Param1T, class Param2T, class Param3T, class Param4T, class Param5T, class Param6T, class Param7T>
const unsigned int Delegate< ReturnValueT ( Param1T, Param2T, Param3T, Param4T, Param5T, Param6T, Param7T ) >::NUMBER_OF_PARAMETERS = 7;


/// <summary>
/// Represents a delegate. Delegates are a kind of sophisticated pointers-to-function; they can store
/// a reference to any kind of function: "free" functions, static methods and non-static methods, both
/// virtual and non-virtual. In the case of non-static methods, a reference to the class instance to which
/// the method refers to is stored too.
/// </summary>
/// <remarks>
/// Delegates may be null if they have never been assigned to any function. They can be assigned as
/// many times as necessary.<br/>
/// Delegates are used as if they were normal functions, passing arguments between
/// the brackets.<br/>
/// <b>Known limitations</b><br/>
/// At the moment, it is not possible to create a delegate that stored a constant method of a class when
/// there is an non-constant overload of such method. The non-const overload will be used always instead.
/// </remarks>
/// <typeparam name="ReturnValueT">The type of the return value.</typeparam>
/// <typeparam name="Param1T">The type of the first parameter.</typeparam>
/// <typeparam name="Param2T">The type of the second parameter.</typeparam>
/// <typeparam name="Param3T">The type of the third parameter.</typeparam>
/// <typeparam name="Param4T">The type of the forth parameter.</typeparam>
/// <typeparam name="Param5T">The type of the fifth parameter.</typeparam>
/// <typeparam name="Param6T">The type of the sixth parameter.</typeparam>
/// <typeparam name="Param7T">The type of the seventh parameter.</typeparam>
/// <typeparam name="Param8T">The type of the eighth parameter.</typeparam>
template<typename ReturnValueT, class Param1T, class Param2T, class Param3T, class Param4T, class Param5T, class Param6T, class Param7T, class Param8T>
class Delegate< ReturnValueT ( Param1T, Param2T, Param3T, Param4T, Param5T, Param6T, Param7T, Param8T ) > : protected Internals::FastDelegate8 < Param1T, Param2T, Param3T, Param4T, Param5T, Param6T, Param7T, Param8T, ReturnValueT >
{

    /// <summary>
    /// Pseudonym for the base class.
    /// </summary>
    typedef FastDelegate8 < Param1T, Param2T, Param3T, Param4T, Param5T, Param6T, Param7T, Param8T, ReturnValueT > BaseType;

    using BaseType::m_closure;

    /// <summary>
    /// Pseudonym for this class.
    /// </summary>
    typedef Delegate SelfType;

public:

    /// <summary>
    /// Pseudonym for the type of the first parameter of the function.
    /// </summary>
    typedef Param1T Parameter1Type;

    /// <summary>
    /// Pseudonym for the type of the second parameter of the function.
    /// </summary>
    typedef Param2T Parameter2Type;

    /// <summary>
    /// Pseudonym for the type of the third parameter of the function.
    /// </summary>
    typedef Param3T Parameter3Type;

    /// <summary>
    /// Pseudonym for the type of the forth parameter of the function.
    /// </summary>
    typedef Param4T Parameter4Type;

    /// <summary>
    /// Pseudonym for the type of the fifth parameter of the function.
    /// </summary>
    typedef Param5T Parameter5Type;

    /// <summary>
    /// Pseudonym for the type of the sixth parameter of the function.
    /// </summary>
    typedef Param6T Parameter6Type;

    /// <summary>
    /// Pseudonym for the type of the seventh parameter of the function.
    /// </summary>
    typedef Param7T Parameter7Type;

    /// <summary>
    /// Pseudonym for the type of the eighth parameter of the function.
    /// </summary>
    typedef Param8T Parameter8Type;

    /// <summary>
    /// Pseudonym for the return type of the function.
    /// </summary>
    typedef ReturnValueT ReturnType;


    // CONSTRUCTORS
    // ---------------

    /// <summary>
    /// Default constructor. Delgates are considered as null when they have not been assigned to a function.
    /// </summary>
    Delegate()
    {
    }

    /// <summary>
    /// Constructor that receives an object and one of its methods.
    /// </summary>
    /// <typeparam name="ClassT">The class where the method is defined. It can be an ancestor of the object's class.</typeparam>
    /// <typeparam name="ObjectT">The type of the object whose method is to be called.</typeparam>
    /// <param name="pThis">[IN] The object whose method is to be called.</param>
    /// <param name="pFunction">[IN] The method to be called.</param>
    template < class ClassT, class ObjectT >
    Delegate(ObjectT* pThis, ReturnValueT (ClassT::* pFunction)( Param1T p1, Param2T p2, Param3T p3, Param4T p4, Param5T p5, Param6T p6, Param7T p7, Param8T p8 ))
                                                    : BaseType(pThis, pFunction)
    {
    }

    /// <summary>
    /// Constructor that receives a constant object and one of its methods (which must be constant too).
    /// </summary>
    /// <typeparam name="ClassT">The class where the method is defined. It can be an ancestor of the object's class.</typeparam>
    /// <typeparam name="ObjectT">The type of the object whose method is to be called.</typeparam>
    /// <param name="pThis">[IN] The constant object whose method is to be called.</param>
    /// <param name="pFunction">[IN] The constant method to be called.</param>
    template < class ClassT, class ObjectT >
    Delegate(const ObjectT* pThis, ReturnValueT (ClassT::* pFunction)( Param1T p1, Param2T p2, Param3T p3, Param4T p4, Param5T p5, Param6T p6, Param7T p7, Param8T p8 ) const)
                                                    : BaseType(pThis, pFunction)
    {
    }

    /// <summary>
    /// Constructor that receives a function.
    /// </summary>
    /// <param name="pFunction">[IN] The function to be called.</param>
    Delegate(ReturnValueT (*pFunction)( Param1T p1, Param2T p2, Param3T p3, Param4T p4, Param5T p5, Param6T p6, Param7T p7, Param8T p8 ))
                                                    : BaseType(pFunction)
    {
    }

    // METHODS
    // ---------------

    /// <summary>
    /// Assignment operator that copies a delegate.
    /// </summary>
    /// <param name="delegate">[IN] The delegate to copy.</param>
    /// <returns>
    /// A reference to the resident object.
    /// </returns>
    Delegate& operator=(const Delegate &delegate)
    {
        m_closure.CopyFrom(this, delegate.m_closure);
        return *this;
    }

    /// <summary>
    /// Calls the stored function for the stored object, if any.
    /// </summary>
    /// <param name="p1">[IN] The first parameter of the function.</param>
    /// <param name="p2">[IN] The second parameter of the function.</param>
    /// <param name="p3">[IN] The third parameter of the function.</param>
    /// <param name="p4">[IN] The forth parameter of the function.</param>
    /// <param name="p5">[IN] The fifth parameter of the function.</param>
    /// <param name="p6">[IN] The sixth parameter of the function.</param>
    /// <param name="p7">[IN] The seventh parameter of the function.</param>
    /// <param name="p8">[IN] The eighth parameter of the function.</param>
    /// <returns>
    /// The value returned by the function, if any.
    /// </returns>
    ReturnValueT operator() (Param1T p1, Param2T p2, Param3T p3, Param4T p4, Param5T p5, Param6T p6, Param7T p7, Param8T p8) const
    {
        Z_ASSERT_ERROR(!this->IsNull(), "The delegate is null, calling to the function will fail");
        return (m_closure.GetClosureThis()->*(m_closure.GetClosureMemPtr()))(p1, p2, p3, p4, p5, p6, p7, p8);
    }
    
    /// <summary>
    /// Equality operator that checks whether two delegates contain the same function or not. If they contain the same method, 
    /// it checks whether they belong to the same object.
    /// </summary>
    /// <param name="delegate">[IN] The delegate to compare to.</param>
    /// <returns>
    /// True if both delegates contain the same function or, in case they are methods, if they contain the same method of the same object; False otherwise.
    /// </returns>
    bool operator==(const Delegate &delegate) const
    {
        return m_closure.IsEqual(delegate.m_closure);
    }
    
    /// <summary>
    /// Inequality operator that checks whether two delegates do not contain the same function. If they contain the same method, 
    /// it checks whether they belong to the same object.
    /// </summary>
    /// <param name="delegate">[IN] The delegate to compare to.</param>
    /// <returns>
    /// True if delegates contain different functions or, in case they are methods, if they contain the same method of different objects; False otherwise.
    /// </returns>
    bool operator!=(const Delegate &delegate) const
    {
        return !m_closure.IsEqual(delegate.m_closure);
    }


    // PROPERTIES
    // ---------------

    /// <summary>
    /// Gets the number of parameters of the function.
    /// </summary>
    /// <returns>
    /// The number of parameters of the function.
    /// </returns>
    static const unsigned int& GetNumberOfParameters()
    {
        return Delegate::NUMBER_OF_PARAMETERS;
    }

    /// <summary>
    /// Indicates whether the delegate is null or not. Delegates are null when they are not assigned to any function.
    /// </summary>
    /// <returns>
    /// True if the delegate is True; False otherwise.
    /// </returns>
    bool IsNull() const
    {
        return !m_closure;
    }


    // ATTRIBUTES
    // ---------------
private:

    /// <summary>
    /// The number of parameters of the function.
    /// </summary>
    static const unsigned int NUMBER_OF_PARAMETERS;
};

// STATIC MEMBERS INITIALIZATION
// --------------------------------
template<typename ReturnValueT, class Param1T, class Param2T, class Param3T, class Param4T, class Param5T, class Param6T, class Param7T, class Param8T>
const unsigned int Delegate< ReturnValueT ( Param1T, Param2T, Param3T, Param4T, Param5T, Param6T, Param7T, Param8T ) >::NUMBER_OF_PARAMETERS = 8;


} // namespace z

#endif // __DELEGATE__
