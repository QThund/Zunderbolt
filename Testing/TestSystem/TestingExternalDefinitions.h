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

#ifndef __TESTINGEXTERNALDEFINITIONS__
#define __TESTINGEXTERNALDEFINITIONS__

#include "CommonConfigDefinitions.h"

using namespace z;

// --------------------------------------------------------------------------------------------------------
// ZTEST_SUITE_BEGIN: Use this macro to start defining a test suite.
// TestSuiteName: The name of the test suite (without quotation marks).
//
// EXZTEST_SUITE_BEGIN: Use this macro insted of the one above to mark a unit test as an exception
//                      when the configuration of the execution of tests is set to IGNORE.
// --------------------------------------------------------------------------------------------------------
#if Z_TEST_CONFIG_TEST_EXECUTION == Z_TEST_CONFIG_TEST_EXECUTION_NORMAL
    #define ZTEST_SUITE_BEGIN( TestSuiteName ) BOOST_AUTO_TEST_SUITE( TestSuiteName )
#elif Z_TEST_CONFIG_TEST_EXECUTION == Z_TEST_CONFIG_TEST_EXECUTION_IGNORE
    #define ZTEST_SUITE_BEGIN( TestSuiteName ) class Ignored_TestSuiteName {
    #define EXZTEST_SUITE_BEGIN( TestSuiteName ) BOOST_AUTO_TEST_SUITE( TestSuiteName )
#endif

// --------------------------------------------------------------------------------------------------------
// ZTEST_CASE: Use this macro to define the header of a new test case, for testing a function or method.
//             It must be enclosed between ZTEST_SUITE_BEGIN and ZTEST_SUITE_END macros.
// TestCaseName: The name of the test case, as descriptive as possible (without quotation marks).
//
// EXZTEST_CASE: Use this macro insted of the one above to mark a unit test as an exception
//               when the configuration of the execution of tests is set to IGNORE.
// --------------------------------------------------------------------------------------------------------
#if Z_TEST_CONFIG_TEST_EXECUTION == Z_TEST_CONFIG_TEST_EXECUTION_NORMAL
    #define ZTEST_CASE( TestCaseName ) BOOST_AUTO_TEST_CASE( TestCaseName )
#elif Z_TEST_CONFIG_TEST_EXECUTION == Z_TEST_CONFIG_TEST_EXECUTION_IGNORE
    #define ZTEST_CASE( TestCaseName ) void TestCaseName()
    #define EXZTEST_CASE( TestCaseName ) BOOST_AUTO_TEST_CASE( TestCaseName )
#endif

// --------------------------------------------------------------------------------------------------------
// ZTEST_CASE_TEMPLATE: Use this macro to define the header of a new test case, for testing a template
//                      function or method.
//                      It must be enclosed between ZTEST_SUITE_BEGIN and ZTEST_SUITE_END macros.
// TestCaseName: The name of the test case, as descriptive as possible (without quotation marks).
// TemplateTypes: A list of types to be used as template parameter T.
//
// EXZTEST_CASE_TEMPLATE: Use this macro insted of the one above to mark a unit test as an exception
//                        when the configuration of the execution of tests is set to IGNORE.
// --------------------------------------------------------------------------------------------------------
#if Z_TEST_CONFIG_TEST_EXECUTION == Z_TEST_CONFIG_TEST_EXECUTION_NORMAL
    #define ZTEST_CASE_TEMPLATE( TestCaseName, TemplateTypes ) BOOST_AUTO_TEST_CASE_TEMPLATE( TestCaseName, T, TemplateTypes )
#elif Z_TEST_CONFIG_TEST_EXECUTION == Z_TEST_CONFIG_TEST_EXECUTION_IGNORE
    #define ZTEST_CASE_TEMPLATE( TestCaseName, TemplateTypes ) template<class T> void TestCaseName()
    #define EXZTEST_CASE_TEMPLATE( TestCaseName, TemplateTypes ) BOOST_AUTO_TEST_CASE_TEMPLATE( TestCaseName, T, TemplateTypes )
#endif

// --------------------------------------------------------------------------------------------------------
// ZTEST_SUITE_END: Use this macro to finish defining a test suite.
//
// EXZTEST_SUITE_END: Use this macro insted of the one above to mark a unit test as an exception
//                    when the configuration of the execution of tests is set to IGNORE.
// --------------------------------------------------------------------------------------------------------
#if Z_TEST_CONFIG_TEST_EXECUTION == Z_TEST_CONFIG_TEST_EXECUTION_NORMAL
    #define ZTEST_SUITE_END( ) BOOST_AUTO_TEST_SUITE_END( )
#elif Z_TEST_CONFIG_TEST_EXECUTION == Z_TEST_CONFIG_TEST_EXECUTION_IGNORE
    #define ZTEST_SUITE_END( ) };
    #define EXZTEST_SUITE_END( ) BOOST_AUTO_TEST_SUITE_END( )
#endif


#endif // __TESTINGEXTERNALDEFINITIONS__
