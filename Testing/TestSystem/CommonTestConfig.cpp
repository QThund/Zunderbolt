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

#include "CommonTestConfig.h"
#include "CommonConfigDefinitions.h"

#include <boost/date_time.hpp>

namespace z
{
namespace Test
{

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |  ATTRIBUTES INITIALIZATION |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

const std::string CommonTestConfig::TestConfigFileName("TestConfig.txt");
std::string CommonTestConfig::s_strLogFilePath;
std::ofstream CommonTestConfig::s_resultsFileStream;


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |       CONSTRUCTORS		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

CommonTestConfig::CommonTestConfig()
{
}

CommonTestConfig::CommonTestConfig(const std::string &strTestModuleName, const ETestType &testType)
{
    // Loads configuration values from disk
    // -------------------------------------
    Test::SimpleConfigLoader config(CommonTestConfig::TestConfigFileName);
    if(config.LoadEntries())
    {
        // Entries order in the configuration file
        const int FILE_UNITTEST_RESULTSPATH_ENTRY_POSITION = 0;
        const int FILE_PERFORMANCETEST_RESULTSPATH_ENTRY_POSITION = 1;
        
        // Depending on the test type, a path is selected to store the results file
        int nEntryToReadResultsPathFrom = 0;

        switch(testType)
        {
        case ETestType::E_UnitTest:
            {
                nEntryToReadResultsPathFrom = FILE_UNITTEST_RESULTSPATH_ENTRY_POSITION;
                break;
            }
        case ETestType::E_PerformanceTest:
            {
                nEntryToReadResultsPathFrom = FILE_PERFORMANCETEST_RESULTSPATH_ENTRY_POSITION;
                break;
            }
        default:
            break;
        }

        CommonTestConfig::s_strLogFilePath = (config[nEntryToReadResultsPathFrom] + strTestModuleName + "_" + Z_TEST_CONFIG_NAME + "_" + this->GetCurrentTime() + ".xml");
        CommonTestConfig::s_resultsFileStream.open(CommonTestConfig::s_strLogFilePath.c_str(), std::ofstream::out);

        // Log configuration
        // -------------------
        // Output file format
        unit_test_log.set_format(boost::unit_test::output_format::OF_XML);
        // Output stream
        unit_test_log.set_stream(CommonTestConfig::s_resultsFileStream);
        // Threshold level
        unit_test_log.set_threshold_level(log_successful_tests);
    }
    else
    {
        std::cout << "An error occured when loading the test configuration file (" << CommonTestConfig::TestConfigFileName << ").";
    }
}

	
//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		  DESTRUCTOR		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

CommonTestConfig::~CommonTestConfig()
{
}


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		    METHODS	    	 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

std::string CommonTestConfig::GetCurrentTime()
{
    // Read from http://stackoverflow.com/questions/2612938/simplest-way-to-get-current-time-in-current-timezone-using-boostdate-time

    std::string strResult;

    std::ostringstream stringStream;
    const boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();
    boost::posix_time::time_facet *const facet = new boost::posix_time::time_facet("%Y-%m-%d-%H-%M-%S");
    stringStream.imbue(std::locale(stringStream.getloc(), facet));
    stringStream << now;

    strResult = stringStream.str();

    return strResult;
}

} // namespace Test
} // namespace z
