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

#ifndef __COMMONTESTCONFIG__
#define __COMMONTESTCONFIG__

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>

#include <fstream>
#include <string>

#include "SimpleConfigLoader.h"
#include "ETestType.h"

using namespace boost::unit_test;


namespace z
{
namespace Test
{

/// <summary>
/// Configures the testing system and initializes it. It must be instantiated only once per module.
/// When instantiated, it reads the test configuration file and sets up, for example, the test 
/// logging objects.
/// </summary>
class CommonTestConfig
{

    // CONSTANTS
    // ---------------
public:

    /// <summary>
    /// Predefined file name of the test configuration file.
    /// </summary>
    static const std::string TestConfigFileName;


	// CONSTRUCTORS
	// ---------------
public:

    /// <summary>
    /// Default constructor.
    /// </summary>
    CommonTestConfig();

    /// <summary>
    /// Constructor that receives the name of the test module and the type of test.
    /// </summary>
    /// <param name="strTestModuleName">The name of the module.</param>
    /// <param name="testType">The type of test.</param>
    CommonTestConfig(const std::string &strTestModuleName, const ETestType& testType);


	// DESTRUCTOR
	// ---------------
public:

	/// <summary>
	/// Destructor.
	/// </summary>		
	virtual ~CommonTestConfig();

    // METHODS
    // ---------------
protected:

    /// <summary>
    /// Gets the current date and time.
    /// </summary>
    /// <returns>
    /// The date and the time following this format: "YYYY-MM-DD-hh-mm-ss".
    /// </returns>
    std::string GetCurrentTime();


	// ATTRIBUTES
	// ---------------
protected:

    /// <summary>
    /// The path of the file where the tests results are to be written.
    /// </summary>
    /// <remarks>
    /// It has to be static because, internally, it's used by the logger of Boost library, that needs it 
    /// alive until the application exits.
    /// </remarks>
    static std::string s_strLogFilePath;

    /// <summary>
    /// The output file stream where the logger will write.
    /// </summary>
    /// <remarks>
    /// It has to be static because, internally, it's used by the logger of Boost library, that needs it 
    /// alive until the application exits.
    /// </remarks>
    static std::ofstream s_resultsFileStream;

};

} // namespace Test
} // namespace z

#endif // __COMMONTESTCONFIG__

