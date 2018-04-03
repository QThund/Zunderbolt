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
#include <boost/mpl/list.hpp>
using namespace boost::unit_test;

#include "../../testsystem/TestingExternalDefinitions.h"

#include "ZCommon/Delegate.h"

#include "ZCommon/Exceptions/AssertException.h"
#include "FunctionsForDelegateTests.h"

using namespace z::Test;

typedef boost::mpl::list<void(), 
                         void(int), 
                         void(int, int), 
                         void(int, int, int), 
                         void(int, int, int, int), 
                         void(int, int, int, int, int), 
                         void(int, int, int, int, int, int), 
                         void(int, int, int, int, int, int, int), 
                         void(int, int, int, int, int, int, int, int)> TFreeFunctions;


ZTEST_SUITE_BEGIN( Delegate_TestSuite )

/// <summary>
/// Checks that the delegate is null by default.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor1_DelegateIsNullByDefault_Test, TFreeFunctions )
{
    // [Preparation]
    const bool IS_NULL = true;

	// [Execution]
    Delegate<T> delegate;
    
    // [Verification]
    bool bIsNull = delegate.IsNull();
    BOOST_CHECK_EQUAL(bIsNull, IS_NULL);
}

/// <summary>
/// Checks that a method with 0 parameters is correctly stored.
/// </summary>
ZTEST_CASE ( Constructor2_MethodWith0ParametersIsCorrectlyStored_Test )
{
    // [Preparation]
    typedef int(TFunctionType)();
    const int EXPECTED_RESULT = Delegate<TFunctionType>::GetNumberOfParameters();
    const Methods object;

	// [Execution]
    Delegate<TFunctionType> delegate(&object, &Methods::ConstMethod);
    
    // [Verification]
    int nResult = delegate();
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that a method with 1 parameter is correctly stored.
/// </summary>
ZTEST_CASE ( Constructor2_MethodWith1ParametersIsCorrectlyStored_Test )
{
    // [Preparation]
    typedef int(TFunctionType)(int);
    const int EXPECTED_RESULT = Delegate<TFunctionType>::GetNumberOfParameters();
    int ARGUMENT = 1;
    const Methods object;

	// [Execution]
    Delegate<TFunctionType> delegate(&object, &Methods::ConstMethod);
    
    // [Verification]
    int nResult = delegate(ARGUMENT);
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that a method with 2 parameter is correctly stored.
/// </summary>
ZTEST_CASE ( Constructor2_MethodWith2ParametersIsCorrectlyStored_Test )
{
    // [Preparation]
    typedef int(TFunctionType)(int, int);
    const int EXPECTED_RESULT = Delegate<TFunctionType>::GetNumberOfParameters();
    int ARGUMENT = 1;
    const Methods object;

	// [Execution]
    Delegate<TFunctionType> delegate(&object, &Methods::ConstMethod);
    
    // [Verification]
    int nResult = delegate(ARGUMENT, ARGUMENT);
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that a method with 3 parameter is correctly stored.
/// </summary>
ZTEST_CASE ( Constructor2_MethodWith3ParametersIsCorrectlyStored_Test )
{
    // [Preparation]
    typedef int(TFunctionType)(int, int, int);
    const int EXPECTED_RESULT = Delegate<TFunctionType>::GetNumberOfParameters();
    int ARGUMENT = 1;
    const Methods object;

	// [Execution]
    Delegate<TFunctionType> delegate(&object, &Methods::ConstMethod);
    
    // [Verification]
    int nResult = delegate(ARGUMENT, ARGUMENT, ARGUMENT);
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that a method with 4 parameter is correctly stored.
/// </summary>
ZTEST_CASE ( Constructor2_MethodWith4ParametersIsCorrectlyStored_Test )
{
    // [Preparation]
    typedef int(TFunctionType)(int, int, int, int);
    const int EXPECTED_RESULT = Delegate<TFunctionType>::GetNumberOfParameters();
    int ARGUMENT = 1;
    const Methods object;

	// [Execution]
    Delegate<TFunctionType> delegate(&object, &Methods::ConstMethod);
    
    // [Verification]
    int nResult = delegate(ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT);
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that a method with 5 parameter is correctly stored.
/// </summary>
ZTEST_CASE ( Constructor2_MethodWith5ParametersIsCorrectlyStored_Test )
{
    // [Preparation]
    typedef int(TFunctionType)(int, int, int, int, int);
    const int EXPECTED_RESULT = Delegate<TFunctionType>::GetNumberOfParameters();
    int ARGUMENT = 1;
    const Methods object;

	// [Execution]
    Delegate<TFunctionType> delegate(&object, &Methods::ConstMethod);
    
    // [Verification]
    int nResult = delegate(ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT);
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that a method with 6 parameter is correctly stored.
/// </summary>
ZTEST_CASE ( Constructor2_MethodWith6ParametersIsCorrectlyStored_Test )
{
    // [Preparation]
    typedef int(TFunctionType)(int, int, int, int, int, int);
    const int EXPECTED_RESULT = Delegate<TFunctionType>::GetNumberOfParameters();
    int ARGUMENT = 1;
    const Methods object;

	// [Execution]
    Delegate<TFunctionType> delegate(&object, &Methods::ConstMethod);
    
    // [Verification]
    int nResult = delegate(ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT);
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that a method with 7 parameter is correctly stored.
/// </summary>
ZTEST_CASE ( Constructor2_MethodWith7ParametersIsCorrectlyStored_Test )
{
    // [Preparation]
    typedef int(TFunctionType)(int, int, int, int, int, int, int);
    const int EXPECTED_RESULT = Delegate<TFunctionType>::GetNumberOfParameters();
    int ARGUMENT = 1;
    const Methods object;

	// [Execution]
    Delegate<TFunctionType> delegate(&object, &Methods::ConstMethod);
    
    // [Verification]
    int nResult = delegate(ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT);
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that a method with 8 parameter is correctly stored.
/// </summary>
ZTEST_CASE ( Constructor2_MethodWith8ParametersIsCorrectlyStored_Test )
{
    // [Preparation]
    typedef int(TFunctionType)(int, int, int, int, int, int, int, int);
    const int EXPECTED_RESULT = Delegate<TFunctionType>::GetNumberOfParameters();
    int ARGUMENT = 1;
    const Methods object;

	// [Execution]
    Delegate<TFunctionType> delegate(&object, &Methods::ConstMethod);
    
    // [Verification]
    int nResult = delegate(ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT);
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that a virtual method is correctly stored.
/// </summary>
ZTEST_CASE ( Constructor2_VirtualMethodIsCorrectlyStored_Test )
{
    // [Preparation]
    typedef int(TFunctionType)(int);
    const int EXPECTED_RESULT = Delegate<TFunctionType>::GetNumberOfParameters();
    int ARGUMENT = 1;
    Methods object;

	// [Execution]
    Delegate<TFunctionType> delegate(&object, &Methods::VMethod);
    
    // [Verification]
    int nResult = delegate(ARGUMENT);
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that a constant method that receives 0 parameters is correctly stored.
/// </summary>
ZTEST_CASE ( Constructor3_ConstantMethodWith0ParametersIsCorrectlyStored_Test )
{
    // [Preparation]
    typedef int (TFunctionType)( );
    const int EXPECTED_RESULT = Delegate<TFunctionType>::GetNumberOfParameters();
    const Methods object;

	// [Execution]
    Delegate<TFunctionType> delegate(&object, &Methods::ConstMethod);
    
    // [Verification]
    int nResult = delegate();
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that a constant method that receives 1 parameters is correctly stored.
/// </summary>
ZTEST_CASE ( Constructor3_ConstantMethodWith1ParametersIsCorrectlyStored_Test )
{
    // [Preparation]
    typedef int (TFunctionType)( int );
    const int EXPECTED_RESULT = Delegate<TFunctionType>::GetNumberOfParameters();
    int ARGUMENT = 1;
    const Methods object;

	// [Execution]
    Delegate<TFunctionType> delegate(&object, &Methods::ConstMethod);
    
    // [Verification]
    int nResult = delegate(ARGUMENT);
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that a constant method that receives 2 parameters is correctly stored.
/// </summary>
ZTEST_CASE ( Constructor3_ConstantMethodWith2ParametersIsCorrectlyStored_Test )
{
    // [Preparation]
    typedef int (TFunctionType)( int, int );
    const int EXPECTED_RESULT = Delegate<TFunctionType>::GetNumberOfParameters();
    int ARGUMENT = 1;
    const Methods object;

	// [Execution]
    Delegate<TFunctionType> delegate(&object, &Methods::ConstMethod);
    
    // [Verification]
    int nResult = delegate(ARGUMENT, ARGUMENT);
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that a constant method that receives 3 parameters is correctly stored.
/// </summary>
ZTEST_CASE ( Constructor3_ConstantMethodWith3ParametersIsCorrectlyStored_Test )
{
    // [Preparation]
    typedef int (TFunctionType)( int, int, int );
    const int EXPECTED_RESULT = Delegate<TFunctionType>::GetNumberOfParameters();
    int ARGUMENT = 1;
    const Methods object;

	// [Execution]
    Delegate<TFunctionType> delegate(&object, &Methods::ConstMethod);
    
    // [Verification]
    int nResult = delegate(ARGUMENT, ARGUMENT, ARGUMENT);
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that a constant method that receives 4 parameters is correctly stored.
/// </summary>
ZTEST_CASE ( Constructor3_ConstantMethodWith4ParametersIsCorrectlyStored_Test )
{
    // [Preparation]
    typedef int (TFunctionType)( int, int, int, int );
    const int EXPECTED_RESULT = Delegate<TFunctionType>::GetNumberOfParameters();
    int ARGUMENT = 1;
    const Methods object;

	// [Execution]
    Delegate<TFunctionType> delegate(&object, &Methods::ConstMethod);
    
    // [Verification]
    int nResult = delegate(ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT);
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that a constant method that receives 5 parameters is correctly stored.
/// </summary>
ZTEST_CASE ( Constructor3_ConstantMethodWith5ParametersIsCorrectlyStored_Test )
{
    // [Preparation]
    typedef int (TFunctionType)( int, int, int, int, int );
    const int EXPECTED_RESULT = Delegate<TFunctionType>::GetNumberOfParameters();
    int ARGUMENT = 1;
    const Methods object;

	// [Execution]
    Delegate<TFunctionType> delegate(&object, &Methods::ConstMethod);
    
    // [Verification]
    int nResult = delegate(ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT);
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that a constant method that receives 6 parameters is correctly stored.
/// </summary>
ZTEST_CASE ( Constructor3_ConstantMethodWith6ParametersIsCorrectlyStored_Test )
{
    // [Preparation]
    typedef int (TFunctionType)( int, int, int, int, int, int );
    const int EXPECTED_RESULT = Delegate<TFunctionType>::GetNumberOfParameters();
    int ARGUMENT = 1;
    const Methods object;

	// [Execution]
    Delegate<TFunctionType> delegate(&object, &Methods::ConstMethod);
    
    // [Verification]
    int nResult = delegate(ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT);
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that a constant method that receives 7 parameters is correctly stored.
/// </summary>
ZTEST_CASE ( Constructor3_ConstantMethodWith7ParametersIsCorrectlyStored_Test )
{
    // [Preparation]
    typedef int (TFunctionType)( int, int, int, int, int, int, int );
    const int EXPECTED_RESULT = Delegate<TFunctionType>::GetNumberOfParameters();
    int ARGUMENT = 1;
    const Methods object;

	// [Execution]
    Delegate<TFunctionType> delegate(&object, &Methods::ConstMethod);
    
    // [Verification]
    int nResult = delegate(ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT);
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that a constant method that receives 8 parameters is correctly stored.
/// </summary>
ZTEST_CASE ( Constructor3_ConstantMethodWith8ParametersIsCorrectlyStored_Test )
{
    // [Preparation]
    typedef int (TFunctionType)( int, int, int, int, int, int, int, int );
    const int EXPECTED_RESULT = Delegate<TFunctionType>::GetNumberOfParameters();
    int ARGUMENT = 1;
    const Methods object;

	// [Execution]
    Delegate<TFunctionType> delegate(&object, &Methods::ConstMethod);
    
    // [Verification]
    int nResult = delegate(ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT);
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that a free function that receives 0 parameters is correctly stored.
/// </summary>
ZTEST_CASE ( Constructor4_FreeFunctionWith0ParametersIsCorrectlyStored_Test )
{
    // [Preparation]
    typedef void (TFunctionType)( );
    const int EXPECTED_RESULT = Delegate<TFunctionType>::GetNumberOfParameters();

	// [Execution]
    Delegate<TFunctionType> delegate(&FreeFunction);
    
    // [Verification]
    delegate();
    int nResult = LAST_FREEFUNCTION_RESULT;
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that a free function that receives 1 parameters is correctly stored.
/// </summary>
ZTEST_CASE ( Constructor4_FreeFunctionWith1ParametersIsCorrectlyStored_Test )
{
    // [Preparation]
    typedef void (TFunctionType)( int );
    const int EXPECTED_RESULT = Delegate<TFunctionType>::GetNumberOfParameters();
    int ARGUMENT = 1;

	// [Execution]
    Delegate<TFunctionType> delegate(&FreeFunction);
    
    // [Verification]
    delegate(ARGUMENT);
    int nResult = LAST_FREEFUNCTION_RESULT;
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that a free function that receives 2 parameters is correctly stored.
/// </summary>
ZTEST_CASE ( Constructor4_FreeFunctionWith2ParametersIsCorrectlyStored_Test )
{
    // [Preparation]
    typedef void (TFunctionType)( int, int );
    const int EXPECTED_RESULT = Delegate<TFunctionType>::GetNumberOfParameters();
    int ARGUMENT = 1;

	// [Execution]
    Delegate<TFunctionType> delegate(&FreeFunction);
    
    // [Verification]
    delegate(ARGUMENT, ARGUMENT);
    int nResult = LAST_FREEFUNCTION_RESULT;
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that a free function that receives 3 parameters is correctly stored.
/// </summary>
ZTEST_CASE ( Constructor4_FreeFunctionWith3ParametersIsCorrectlyStored_Test )
{
    // [Preparation]
    typedef void (TFunctionType)( int, int, int );
    const int EXPECTED_RESULT = Delegate<TFunctionType>::GetNumberOfParameters();
    int ARGUMENT = 1;

	// [Execution]
    Delegate<TFunctionType> delegate(&FreeFunction);
    
    // [Verification]
    delegate(ARGUMENT, ARGUMENT, ARGUMENT);
    int nResult = LAST_FREEFUNCTION_RESULT;
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that a free function that receives 4 parameters is correctly stored.
/// </summary>
ZTEST_CASE ( Constructor4_FreeFunctionWith4ParametersIsCorrectlyStored_Test )
{
    // [Preparation]
    typedef void (TFunctionType)( int, int, int, int );
    const int EXPECTED_RESULT = Delegate<TFunctionType>::GetNumberOfParameters();
    int ARGUMENT = 1;

	// [Execution]
    Delegate<TFunctionType> delegate(&FreeFunction);
    
    // [Verification]
    delegate(ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT);
    int nResult = LAST_FREEFUNCTION_RESULT;
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that a free function that receives 5 parameters is correctly stored.
/// </summary>
ZTEST_CASE ( Constructor4_FreeFunctionWith5ParametersIsCorrectlyStored_Test )
{
    // [Preparation]
    typedef void (TFunctionType)( int, int, int, int, int );
    const int EXPECTED_RESULT = Delegate<TFunctionType>::GetNumberOfParameters();
    int ARGUMENT = 1;

	// [Execution]
    Delegate<TFunctionType> delegate(&FreeFunction);
    
    // [Verification]
    delegate(ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT);
    int nResult = LAST_FREEFUNCTION_RESULT;
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that a free function that receives 6 parameters is correctly stored.
/// </summary>
ZTEST_CASE ( Constructor4_FreeFunctionWith6ParametersIsCorrectlyStored_Test )
{
    // [Preparation]
    typedef void (TFunctionType)( int, int, int, int, int, int );
    const int EXPECTED_RESULT = Delegate<TFunctionType>::GetNumberOfParameters();
    int ARGUMENT = 1;

	// [Execution]
    Delegate<TFunctionType> delegate(&FreeFunction);
    
    // [Verification]
    delegate(ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT);
    int nResult = LAST_FREEFUNCTION_RESULT;
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that a free function that receives 7 parameters is correctly stored.
/// </summary>
ZTEST_CASE ( Constructor4_FreeFunctionWith7ParametersIsCorrectlyStored_Test )
{
    // [Preparation]
    typedef void (TFunctionType)( int, int, int, int, int, int, int );
    const int EXPECTED_RESULT = Delegate<TFunctionType>::GetNumberOfParameters();
    int ARGUMENT = 1;

	// [Execution]
    Delegate<TFunctionType> delegate(&FreeFunction);
    
    // [Verification]
    delegate(ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT);
    int nResult = LAST_FREEFUNCTION_RESULT;
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that a free function that receives 8 parameters is correctly stored.
/// </summary>
ZTEST_CASE ( Constructor4_FreeFunctionWith8ParametersIsCorrectlyStored_Test )
{
    // [Preparation]
    typedef void (TFunctionType)( int, int, int, int, int, int, int, int );
    const int EXPECTED_RESULT = Delegate<TFunctionType>::GetNumberOfParameters();
    int ARGUMENT = 1;

	// [Execution]
    Delegate<TFunctionType> delegate(&FreeFunction);
    
    // [Verification]
    delegate(ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT);
    int nResult = LAST_FREEFUNCTION_RESULT;
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that a free function that receives constant parameters is correctly stored.
/// </summary>
ZTEST_CASE ( Constructor4_FreeFunctionWithConstantParameterIsCorrectlyStored_Test )
{
    // [Preparation]
    typedef void (TFunctionType)( const int& );
    const int EXPECTED_RESULT = Delegate<TFunctionType>::GetNumberOfParameters();
    int ARGUMENT = 1;

	// [Execution]
    Delegate<TFunctionType> delegate(&FreeFunctionWithConstant);
    
    // [Verification]
    delegate(ARGUMENT);
    int nResult = LAST_FREEFUNCTION_RESULT;
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that a static method is correctly stored.
/// </summary>
ZTEST_CASE ( Constructor4_StaticMethodIsCorrectlyStored_Test )
{
    // [Preparation]
    typedef int (TFunctionType)( int, int );
    const int EXPECTED_RESULT = Delegate<TFunctionType>::GetNumberOfParameters();
    int ARGUMENT = 1;

	// [Execution]
    Delegate<TFunctionType> delegate(&Methods::SMethod);
    
    // [Verification]
    int nResult = delegate(ARGUMENT, ARGUMENT);
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that delegates are properly assigned.
/// </summary>
ZTEST_CASE ( OperatorAssignment_DelegateIsCorrectlyAssigned_Test )
{
    // [Preparation]
    typedef int (TFunctionType)( int, int );
    const int EXPECTED_RESULT = Delegate<TFunctionType>::GetNumberOfParameters();
    int ARGUMENT = 1;
    Delegate<TFunctionType> delegate;

	// [Execution]
    delegate = Delegate<TFunctionType>(&Methods::SMethod);
    
    // [Verification]
    int nResult = delegate(ARGUMENT, ARGUMENT);
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that delegates can be assigned more than once.
/// </summary>
ZTEST_CASE ( OperatorAssignment_DelegateCanBeAssignedMoreThanOnce_Test )
{
    // [Preparation]
    typedef int (TFunctionType)( int, int );
    const int EXPECTED_RESULT = Delegate<TFunctionType>::GetNumberOfParameters();
    int ARGUMENT = 1;
    Delegate<TFunctionType> delegate;

	// [Execution]
    delegate = Delegate<TFunctionType>(&Methods::SMethod2);
    delegate = Delegate<TFunctionType>(&Methods::SMethod);
    
    // [Verification]
    int nResult = delegate(ARGUMENT, ARGUMENT);
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that delegates can be assigned to a free function after it has been assigned to a method.
/// </summary>
ZTEST_CASE ( OperatorAssignment_DelegateCanBeAssignedToFunctionAfterBeingAssignedToMethod_Test )
{
    // [Preparation]
    typedef int (TFunctionType)( int, int );
    const int EXPECTED_RESULT = Delegate<TFunctionType>::GetNumberOfParameters();
    int ARGUMENT = 1;
    const Methods object;
    Delegate<TFunctionType> delegate;

	// [Execution]
    delegate = Delegate<TFunctionType>(&object, &Methods::ConstMethod);
    delegate = Delegate<TFunctionType>(&FreeFunctionWithReturn);
    
    // [Verification]
    int nResult = delegate(ARGUMENT, ARGUMENT);
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that delegates can be assigned to null.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorAssignment_DelegatesCanBeAssignedToNull_Test, TFreeFunctions )
{
    // [Preparation]
    typedef T TFunctionType;
    const bool EXPECTED_RESULT = true;
    Delegate<TFunctionType> delegate(&FreeFunction);

	// [Execution]
    delegate = null_z;
    
    // [Verification]
    bool bResult = false;
    bResult = delegate.IsNull();
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the delegate is null.
/// </summary>
ZTEST_CASE ( IsNull_ReturnsTrueWhenDelegateIsNull_Test )
{
    // [Preparation]
    typedef int (TFunctionType)( int, int );
    const bool EXPECTED_RESULT = true;
    Delegate<TFunctionType> delegate = null_z;

	// [Execution]
    bool bResult = delegate.IsNull();
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the delegate is not null.
/// </summary>
ZTEST_CASE ( IsNull_ReturnsFalseWhenDelegateIsNotNull_Test )
{
    // [Preparation]
    typedef int (TFunctionType)( int, int );
    const bool EXPECTED_RESULT = false;
    Delegate<TFunctionType> delegate = Delegate<TFunctionType>(&FreeFunctionWithReturn);;

	// [Execution]
    bool bResult = delegate.IsNull();
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that free functions that receive 0 parameters are correctly called.
/// </summary>
ZTEST_CASE ( OperatorParenthesis_FreeFunctionWith0ParametersIsCorrectlyCalled_Test )
{
    // [Preparation]
    typedef int (TFunctionType)( );
    const int EXPECTED_RESULT = Delegate<TFunctionType>::GetNumberOfParameters();
    Delegate<TFunctionType> delegate(&FreeFunctionWithReturn);

	// [Execution]
    int nResult = delegate();
    
    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that free functions that receive 1 parameters are correctly called.
/// </summary>
ZTEST_CASE ( OperatorParenthesis_FreeFunctionWith1ParametersIsCorrectlyCalled_Test )
{
    // [Preparation]
    typedef int (TFunctionType)( int );
    const int EXPECTED_RESULT = Delegate<TFunctionType>::GetNumberOfParameters();
    int ARGUMENT = 1;
    Delegate<TFunctionType> delegate(&FreeFunctionWithReturn);

	// [Execution]
    int nResult = delegate(ARGUMENT);
    
    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that free functions that receive 2 parameters are correctly called.
/// </summary>
ZTEST_CASE ( OperatorParenthesis_FreeFunctionWith2ParametersIsCorrectlyCalled_Test )
{
    // [Preparation]
    typedef int (TFunctionType)( int, int );
    const int EXPECTED_RESULT = Delegate<TFunctionType>::GetNumberOfParameters();
    int ARGUMENT = 1;
    Delegate<TFunctionType> delegate(&FreeFunctionWithReturn);

	// [Execution]
    int nResult = delegate(ARGUMENT, ARGUMENT);
    
    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that free functions that receive 3 parameters are correctly called.
/// </summary>
ZTEST_CASE ( OperatorParenthesis_FreeFunctionWith3ParametersIsCorrectlyCalled_Test )
{
    // [Preparation]
    typedef int (TFunctionType)( int, int, int );
    const int EXPECTED_RESULT = Delegate<TFunctionType>::GetNumberOfParameters();
    int ARGUMENT = 1;
    Delegate<TFunctionType> delegate(&FreeFunctionWithReturn);

	// [Execution]
    int nResult = delegate(ARGUMENT, ARGUMENT, ARGUMENT);
    
    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that free functions that receive 4 parameters are correctly called.
/// </summary>
ZTEST_CASE ( OperatorParenthesis_FreeFunctionWith4ParametersIsCorrectlyCalled_Test )
{
    // [Preparation]
    typedef int (TFunctionType)( int, int, int, int );
    const int EXPECTED_RESULT = Delegate<TFunctionType>::GetNumberOfParameters();
    int ARGUMENT = 1;
    Delegate<TFunctionType> delegate(&FreeFunctionWithReturn);

	// [Execution]
    int nResult = delegate(ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT);
    
    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that free functions that receive 5 parameters are correctly called.
/// </summary>
ZTEST_CASE ( OperatorParenthesis_FreeFunctionWith5ParametersIsCorrectlyCalled_Test )
{
    // [Preparation]
    typedef int (TFunctionType)( int, int, int, int, int );
    const int EXPECTED_RESULT = Delegate<TFunctionType>::GetNumberOfParameters();
    int ARGUMENT = 1;
    Delegate<TFunctionType> delegate(&FreeFunctionWithReturn);

	// [Execution]
    int nResult = delegate(ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT);
    
    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that free functions that receive 6 parameters are correctly called.
/// </summary>
ZTEST_CASE ( OperatorParenthesis_FreeFunctionWith6ParametersIsCorrectlyCalled_Test )
{
    // [Preparation]
    typedef int (TFunctionType)( int, int, int, int, int, int );
    const int EXPECTED_RESULT = Delegate<TFunctionType>::GetNumberOfParameters();
    int ARGUMENT = 1;
    Delegate<TFunctionType> delegate(&FreeFunctionWithReturn);

	// [Execution]
    int nResult = delegate(ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT);
    
    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that free functions that receive 7 parameters are correctly called.
/// </summary>
ZTEST_CASE ( OperatorParenthesis_FreeFunctionWith7ParametersIsCorrectlyCalled_Test )
{
    // [Preparation]
    typedef int (TFunctionType)( int, int, int, int, int, int, int );
    const int EXPECTED_RESULT = Delegate<TFunctionType>::GetNumberOfParameters();
    int ARGUMENT = 1;
    Delegate<TFunctionType> delegate(&FreeFunctionWithReturn);

	// [Execution]
    int nResult = delegate(ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT);
    
    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that free functions that receive 8 parameters are correctly called.
/// </summary>
ZTEST_CASE ( OperatorParenthesis_FreeFunctionWith8ParametersIsCorrectlyCalled_Test )
{
    // [Preparation]
    typedef int (TFunctionType)( int, int, int, int, int, int, int, int );
    const int EXPECTED_RESULT = Delegate<TFunctionType>::GetNumberOfParameters();
    int ARGUMENT = 1;
    Delegate<TFunctionType> delegate(&FreeFunctionWithReturn);

	// [Execution]
    int nResult = delegate(ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT);
    
    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that methods that receive 0 parameters are correctly called.
/// </summary>
ZTEST_CASE ( OperatorParenthesis_MethodWith0ParametersIsCorrectlyCalled_Test )
{
    // [Preparation]
    typedef int (TFunctionType)( );
    const int EXPECTED_RESULT = Delegate<TFunctionType>::GetNumberOfParameters();
    const Methods object;
    Delegate<TFunctionType> delegate(&object, &Methods::ConstMethod);

	// [Execution]
    int nResult = delegate();
    
    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that methods that receive 1 parameters are correctly called.
/// </summary>
ZTEST_CASE ( OperatorParenthesis_MethodWith1ParametersIsCorrectlyCalled_Test )
{
    // [Preparation]
    typedef int (TFunctionType)( int );
    const int EXPECTED_RESULT = Delegate<TFunctionType>::GetNumberOfParameters();
    int ARGUMENT = 1;
    const Methods object;
    Delegate<TFunctionType> delegate(&object, &Methods::ConstMethod);

	// [Execution]
    int nResult = delegate(ARGUMENT);
    
    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that methods that receive 2 parameters are correctly called.
/// </summary>
ZTEST_CASE ( OperatorParenthesis_MethodWith2ParametersIsCorrectlyCalled_Test )
{
    // [Preparation]
    typedef int (TFunctionType)( int, int );
    const int EXPECTED_RESULT = Delegate<TFunctionType>::GetNumberOfParameters();
    int ARGUMENT = 1;
    const Methods object;
    Delegate<TFunctionType> delegate(&object, &Methods::ConstMethod);

	// [Execution]
    int nResult = delegate(ARGUMENT, ARGUMENT);
    
    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that methods that receive 3 parameters are correctly called.
/// </summary>
ZTEST_CASE ( OperatorParenthesis_MethodWith3ParametersIsCorrectlyCalled_Test )
{
    // [Preparation]
    typedef int (TFunctionType)( int, int, int );
    const int EXPECTED_RESULT = Delegate<TFunctionType>::GetNumberOfParameters();
    int ARGUMENT = 1;
    const Methods object;
    Delegate<TFunctionType> delegate(&object, &Methods::ConstMethod);

	// [Execution]
    int nResult = delegate(ARGUMENT, ARGUMENT, ARGUMENT);
    
    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that methods that receive 4 parameters are correctly called.
/// </summary>
ZTEST_CASE ( OperatorParenthesis_MethodWith4ParametersIsCorrectlyCalled_Test )
{
    // [Preparation]
    typedef int (TFunctionType)( int, int, int, int );
    const int EXPECTED_RESULT = Delegate<TFunctionType>::GetNumberOfParameters();
    int ARGUMENT = 1;
    const Methods object;
    Delegate<TFunctionType> delegate(&object, &Methods::ConstMethod);

	// [Execution]
    int nResult = delegate(ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT);
    
    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that methods that receive 5 parameters are correctly called.
/// </summary>
ZTEST_CASE ( OperatorParenthesis_MethodWith5ParametersIsCorrectlyCalled_Test )
{
    // [Preparation]
    typedef int (TFunctionType)( int, int, int, int, int );
    const int EXPECTED_RESULT = Delegate<TFunctionType>::GetNumberOfParameters();
    int ARGUMENT = 1;
    const Methods object;
    Delegate<TFunctionType> delegate(&object, &Methods::ConstMethod);

	// [Execution]
    int nResult = delegate(ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT);
    
    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that methods that receive 6 parameters are correctly called.
/// </summary>
ZTEST_CASE ( OperatorParenthesis_MethodWith6ParametersIsCorrectlyCalled_Test )
{
    // [Preparation]
    typedef int (TFunctionType)( int, int, int, int, int, int );
    const int EXPECTED_RESULT = Delegate<TFunctionType>::GetNumberOfParameters();
    int ARGUMENT = 1;
    const Methods object;
    Delegate<TFunctionType> delegate(&object, &Methods::ConstMethod);

	// [Execution]
    int nResult = delegate(ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT);
    
    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that methods that receive 7 parameters are correctly called.
/// </summary>
ZTEST_CASE ( OperatorParenthesis_MethodWith7ParametersIsCorrectlyCalled_Test )
{
    // [Preparation]
    typedef int (TFunctionType)( int, int, int, int, int, int, int );
    const int EXPECTED_RESULT = Delegate<TFunctionType>::GetNumberOfParameters();
    int ARGUMENT = 1;
    const Methods object;
    Delegate<TFunctionType> delegate(&object, &Methods::ConstMethod);

	// [Execution]
    int nResult = delegate(ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT);
    
    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that methods that receive 8 parameters are correctly called.
/// </summary>
ZTEST_CASE ( OperatorParenthesis_MethodWith8ParametersIsCorrectlyCalled_Test )
{
    // [Preparation]
    typedef int (TFunctionType)( int, int, int, int, int, int, int, int );
    const int EXPECTED_RESULT = Delegate<TFunctionType>::GetNumberOfParameters();
    int ARGUMENT = 1;
    const Methods object;
    Delegate<TFunctionType> delegate(&object, &Methods::ConstMethod);

	// [Execution]
    int nResult = delegate(ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT);
    
    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that methods that receive 0 parameters are correctly called.
/// </summary>
ZTEST_CASE ( OperatorParenthesis_ConstantMethodWith0ParametersIsCorrectlyCalled_Test )
{
    // [Preparation]
    typedef int (TFunctionType)( );
    const int EXPECTED_RESULT = Delegate<TFunctionType>::GetNumberOfParameters();
    const Methods object;
    Delegate<TFunctionType> delegate(&object, &Methods::ConstMethod);

	// [Execution]
    int nResult = delegate();
    
    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that methods that receive 1 parameters are correctly called.
/// </summary>
ZTEST_CASE ( OperatorParenthesis_ConstantMethodWith1ParametersIsCorrectlyCalled_Test )
{
    // [Preparation]
    typedef int (TFunctionType)( int );
    const int EXPECTED_RESULT = Delegate<TFunctionType>::GetNumberOfParameters();
    int ARGUMENT = 1;
    const Methods object;
    Delegate<TFunctionType> delegate(&object, &Methods::ConstMethod);

	// [Execution]
    int nResult = delegate(ARGUMENT);
    
    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that methods that receive 2 parameters are correctly called.
/// </summary>
ZTEST_CASE ( OperatorParenthesis_ConstantMethodWith2ParametersIsCorrectlyCalled_Test )
{
    // [Preparation]
    typedef int (TFunctionType)( int, int );
    const int EXPECTED_RESULT = Delegate<TFunctionType>::GetNumberOfParameters();
    int ARGUMENT = 1;
    const Methods object;
    Delegate<TFunctionType> delegate(&object, &Methods::ConstMethod);

	// [Execution]
    int nResult = delegate(ARGUMENT, ARGUMENT);
    
    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that methods that receive 3 parameters are correctly called.
/// </summary>
ZTEST_CASE ( OperatorParenthesis_ConstantMethodWith3ParametersIsCorrectlyCalled_Test )
{
    // [Preparation]
    typedef int (TFunctionType)( int, int, int );
    const int EXPECTED_RESULT = Delegate<TFunctionType>::GetNumberOfParameters();
    int ARGUMENT = 1;
    const Methods object;
    Delegate<TFunctionType> delegate(&object, &Methods::ConstMethod);

	// [Execution]
    int nResult = delegate(ARGUMENT, ARGUMENT, ARGUMENT);
    
    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that methods that receive 4 parameters are correctly called.
/// </summary>
ZTEST_CASE ( OperatorParenthesis_ConstantMethodWith4ParametersIsCorrectlyCalled_Test )
{
    // [Preparation]
    typedef int (TFunctionType)( int, int, int, int );
    const int EXPECTED_RESULT = Delegate<TFunctionType>::GetNumberOfParameters();
    int ARGUMENT = 1;
    const Methods object;
    Delegate<TFunctionType> delegate(&object, &Methods::ConstMethod);

	// [Execution]
    int nResult = delegate(ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT);
    
    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that methods that receive 5 parameters are correctly called.
/// </summary>
ZTEST_CASE ( OperatorParenthesis_ConstantMethodWith5ParametersIsCorrectlyCalled_Test )
{
    // [Preparation]
    typedef int (TFunctionType)( int, int, int, int, int );
    const int EXPECTED_RESULT = Delegate<TFunctionType>::GetNumberOfParameters();
    int ARGUMENT = 1;
    const Methods object;
    Delegate<TFunctionType> delegate(&object, &Methods::ConstMethod);

	// [Execution]
    int nResult = delegate(ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT);
    
    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that methods that receive 6 parameters are correctly called.
/// </summary>
ZTEST_CASE ( OperatorParenthesis_ConstantMethodWith6ParametersIsCorrectlyCalled_Test )
{
    // [Preparation]
    typedef int (TFunctionType)( int, int, int, int, int, int );
    const int EXPECTED_RESULT = Delegate<TFunctionType>::GetNumberOfParameters();
    int ARGUMENT = 1;
    const Methods object;
    Delegate<TFunctionType> delegate(&object, &Methods::ConstMethod);

	// [Execution]
    int nResult = delegate(ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT);
    
    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that methods that receive 7 parameters are correctly called.
/// </summary>
ZTEST_CASE ( OperatorParenthesis_ConstantMethodWith7ParametersIsCorrectlyCalled_Test )
{
    // [Preparation]
    typedef int (TFunctionType)( int, int, int, int, int, int, int );
    const int EXPECTED_RESULT = Delegate<TFunctionType>::GetNumberOfParameters();
    int ARGUMENT = 1;
    const Methods object;
    Delegate<TFunctionType> delegate(&object, &Methods::ConstMethod);

	// [Execution]
    int nResult = delegate(ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT);
    
    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that methods that receive 8 parameters are correctly called.
/// </summary>
ZTEST_CASE ( OperatorParenthesis_ConstantMethodWith8ParametersIsCorrectlyCalled_Test )
{
    // [Preparation]
    typedef int (TFunctionType)( int, int, int, int, int, int, int, int );
    const int EXPECTED_RESULT = Delegate<TFunctionType>::GetNumberOfParameters();
    int ARGUMENT = 1;
    const Methods object;
    Delegate<TFunctionType> delegate(&object, &Methods::ConstMethod);

	// [Execution]
    int nResult = delegate(ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT, ARGUMENT);
    
    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that static methods are correctly called.
/// </summary>
ZTEST_CASE ( OperatorParenthesis_StaticMethodIsCorrectlyCalled_Test )
{
    // [Preparation]
    typedef int (TFunctionType)( int, int );
    const int EXPECTED_RESULT = Delegate<TFunctionType>::GetNumberOfParameters();
    int ARGUMENT = 1;
    Delegate<TFunctionType> delegate(&Methods::SMethod);

	// [Execution]
    int nResult = delegate(ARGUMENT, ARGUMENT);
    
    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the functions is called when it is assigned after the delegate was nulled.
/// </summary>
ZTEST_CASE ( OperatorParenthesis_FunctionIsCalledWhenAssignedAfterNulled_Test )
{
    // [Preparation]
    typedef int (TFunctionType)( int, int );
    const int EXPECTED_RESULT = Delegate<TFunctionType>::GetNumberOfParameters();
    int ARGUMENT = 1;
    Delegate<TFunctionType> delegate = null_z;

	// [Execution]
    delegate = Delegate<TFunctionType>(&Methods::SMethod);
    int nResult = delegate(ARGUMENT, ARGUMENT);
    
    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the delegate is null.
/// </summary>
ZTEST_CASE ( OperatorParenthesis_AssertionFailsWhenDelegateIsNull_Test )
{
    // [Preparation]
    typedef int (TFunctionType)( int, int );
    const bool ASSERTION_FAILED = true;
    int ARGUMENT = 1;
    Delegate<TFunctionType> delegate = null_z;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        delegate(ARGUMENT, ARGUMENT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }
        
    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif

/// <summary>
/// Checks that virtual methods are correctly called.
/// </summary>
ZTEST_CASE ( OperatorParenthesis_VirtualMethodIsCalledForProperObject_Test )
{
    // [Preparation]
    typedef int (TFunctionType)( int );
    const int EXPECTED_RESULT = 4;
    int ARGUMENT = 1;
    Methods* pObject = new MethodsDerived3();
    Delegate<TFunctionType> delegate(pObject, &Methods::VMethod);

	// [Execution]
    int nResult = delegate(ARGUMENT);
    
    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when two delegates contain the same free function.
/// </summary>
ZTEST_CASE ( OperatorEquality_ReturnsTrueWhenTwoDelegatesContainTheSameFreeFunction_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = true;
    typedef void (TFunctionType)();
    Delegate<TFunctionType> delegate1(&FreeFunction);
    Delegate<TFunctionType> delegate2(&FreeFunction);

	// [Execution]
    bool bResult = delegate1 == delegate2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when two delegates contain the same static function.
/// </summary>
ZTEST_CASE ( OperatorEquality_ReturnsTrueWhenTwoDelegatesContainTheSameStaticFunction_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = true;
    typedef int (TFunctionType)(int, int);
    Delegate<TFunctionType> delegate1(&Methods::SMethod);
    Delegate<TFunctionType> delegate2(&Methods::SMethod);

	// [Execution]
    bool bResult = delegate1 == delegate2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when two delegates contain the same method of the same object.
/// </summary>
ZTEST_CASE ( OperatorEquality_ReturnsTrueWhenTwoDelegatesContainTheSameMethodOfTheSameObject_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = true;
    typedef int (TFunctionType)(int, int);
    Methods object;
    Delegate<TFunctionType> delegate1(&object, &Methods::Method);
    Delegate<TFunctionType> delegate2(&object, &Methods::Method);

	// [Execution]
    bool bResult = delegate1 == delegate2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when two delegates contain different free functions.
/// </summary>
ZTEST_CASE ( OperatorEquality_ReturnsFalseWhenTwoDelegatesContainDifferentFreeFunctions_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = false;
    typedef void (TFunctionType)();
    Delegate<TFunctionType> delegate1(&FreeFunction);
    Delegate<TFunctionType> delegate2(&FreeFunction2);

	// [Execution]
    bool bResult = delegate1 == delegate2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when two delegates contain different static functions.
/// </summary>
ZTEST_CASE ( OperatorEquality_ReturnsFalseWhenTwoDelegatesContainDifferentStaticFunctions_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = false;
    typedef int (TFunctionType)(int, int);
    Delegate<TFunctionType> delegate1(&Methods::SMethod);
    Delegate<TFunctionType> delegate2(&Methods::SMethod2);

	// [Execution]
    bool bResult = delegate1 == delegate2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when two delegates contain different methods of the same object.
/// </summary>
ZTEST_CASE ( OperatorEquality_ReturnsFalseWhenTwoDelegatesContainDifferentMethodsOfTheSameObject_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = false;
    typedef int (TFunctionType)(int, int);
    Methods object;
    Delegate<TFunctionType> delegate1(&object, &Methods::Method);
    Delegate<TFunctionType> delegate2(&object, &Methods::Method2);

	// [Execution]
    bool bResult = delegate1 == delegate2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when two delegates contain the same method of different objects.
/// </summary>
ZTEST_CASE ( OperatorEquality_ReturnsFalseWhenTwoDelegatesContainTheSameMethodOfDifferentObject_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = false;
    typedef int (TFunctionType)(int, int);
    Methods object1;
    Methods object2;
    Delegate<TFunctionType> delegate1(&object1, &Methods::Method);
    Delegate<TFunctionType> delegate2(&object2, &Methods::Method);

	// [Execution]
    bool bResult = delegate1 == delegate2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when two delegates contain the same free function.
/// </summary>
ZTEST_CASE ( OperatorInequality_ReturnsFalseWhenTwoDelegatesContainTheSameFreeFunction_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = false;
    typedef void (TFunctionType)();
    Delegate<TFunctionType> delegate1(&FreeFunction);
    Delegate<TFunctionType> delegate2(&FreeFunction);

	// [Execution]
    bool bResult = delegate1 != delegate2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when two delegates contain the same static function.
/// </summary>
ZTEST_CASE ( OperatorInequality_ReturnsFalseWhenTwoDelegatesContainTheSameStaticFunction_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = false;
    typedef int (TFunctionType)(int, int);
    Delegate<TFunctionType> delegate1(&Methods::SMethod);
    Delegate<TFunctionType> delegate2(&Methods::SMethod);

	// [Execution]
    bool bResult = delegate1 != delegate2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when two delegates contain the same method of the same object.
/// </summary>
ZTEST_CASE ( OperatorInequality_ReturnsFalseWhenTwoDelegatesContainTheSameMethodOfTheSameObject_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = false;
    typedef int (TFunctionType)(int, int);
    Methods object;
    Delegate<TFunctionType> delegate1(&object, &Methods::Method);
    Delegate<TFunctionType> delegate2(&object, &Methods::Method);

	// [Execution]
    bool bResult = delegate1 != delegate2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when two delegates contain different free functions.
/// </summary>
ZTEST_CASE ( OperatorInequality_ReturnsTrueWhenTwoDelegatesContainDifferentFreeFunctions_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = true;
    typedef void (TFunctionType)();
    Delegate<TFunctionType> delegate1(&FreeFunction);
    Delegate<TFunctionType> delegate2(&FreeFunction2);

	// [Execution]
    bool bResult = delegate1 != delegate2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when two delegates contain different static functions.
/// </summary>
ZTEST_CASE ( OperatorInequality_ReturnsTrueWhenTwoDelegatesContainDifferentStaticFunctions_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = true;
    typedef int (TFunctionType)(int, int);
    Delegate<TFunctionType> delegate1(&Methods::SMethod);
    Delegate<TFunctionType> delegate2(&Methods::SMethod2);

	// [Execution]
    bool bResult = delegate1 != delegate2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when two delegates contain a different method of the same object.
/// </summary>
ZTEST_CASE ( OperatorInequality_ReturnsTrueWhenTwoDelegatesContainDifferentMethodOfTheSameObject_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = true;
    typedef int (TFunctionType)(int, int);
    Methods object;
    Delegate<TFunctionType> delegate1(&object, &Methods::Method);
    Delegate<TFunctionType> delegate2(&object, &Methods::Method2);

	// [Execution]
    bool bResult = delegate1 != delegate2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when two delegates contain the same method of different objects.
/// </summary>
ZTEST_CASE ( OperatorInequality_ReturnsTrueWhenTwoDelegatesContainTheSameMethodOfDifferentObject_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = true;
    typedef int (TFunctionType)(int, int);
    Methods object1;
    Methods object2;
    Delegate<TFunctionType> delegate1(&object1, &Methods::Method);
    Delegate<TFunctionType> delegate2(&object2, &Methods::Method);

	// [Execution]
    bool bResult = delegate1 != delegate2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

// End - Test Suite: Delegate
ZTEST_SUITE_END()
