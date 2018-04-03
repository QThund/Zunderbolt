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

#include "ZMemory/StackAllocator.h"
#include "StackAllocatorWhiteBox.h"
#include "ZCommon/Exceptions/AssertException.h"

using z::Test::StackAllocatorWhiteBox;


ZTEST_SUITE_BEGIN( BlockHeader_TestSuite )

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the passed block size is zero.
/// </summary>
ZTEST_CASE ( Constructor1_AssertionFailsWhenBlockSizeIsZero_Test )
{
    // [Preparation]

    const bool             ASSERTION_FAILED                 = true;
    bool                   bAssertionFailed                 = false;


	// [Execution]

    try
    {
        StackAllocatorWhiteBox::BlockHeader blockHeader(0, 0, 0);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

 
    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS


/// <summary>
/// Checks that everything is correctly set inside the block header.
/// </summary>
ZTEST_CASE ( Constructor1_ChecksThatEverythingIsCorrectlySet_Test )
{
    // [Preparation]

    const bool           EVERYTHING_CORRECTLY_SET                  = true;
    const puint_z TEST_SIZE_128B                            = 128;
    const puint_z TEST_ALIGNMENT_OFFSET_2B                  = 2;
    const puint_z TEST_PREVIOUS_BLOCKHEADER_BACK_OFFSET_55B = 55;

    bool                 bCorrectSize                              = false;
    bool                 bCorrectAlignmentOffset                   = false;
    bool                 bCorrectPreviousBlockHeaderBackOffset     = false;


    // [Execution]
    StackAllocatorWhiteBox::BlockHeader blockHeaderWhiteBox(TEST_SIZE_128B,
                                                            TEST_ALIGNMENT_OFFSET_2B,
                                                            TEST_PREVIOUS_BLOCKHEADER_BACK_OFFSET_55B);

    // [Verification]

    if ( TEST_SIZE_128B == blockHeaderWhiteBox.GetAllocatedBlockSize() )
        bCorrectSize                          = true;

    if ( TEST_ALIGNMENT_OFFSET_2B == blockHeaderWhiteBox.GetAlignmentOffset() )
        bCorrectAlignmentOffset               = true;

    if ( TEST_PREVIOUS_BLOCKHEADER_BACK_OFFSET_55B == blockHeaderWhiteBox.GetPreviousHeaderBackOffset() )
        bCorrectPreviousBlockHeaderBackOffset = true;

    BOOST_CHECK_EQUAL(bCorrectSize,                          EVERYTHING_CORRECTLY_SET);
    BOOST_CHECK_EQUAL(bCorrectAlignmentOffset,               EVERYTHING_CORRECTLY_SET);
    BOOST_CHECK_EQUAL(bCorrectPreviousBlockHeaderBackOffset, EVERYTHING_CORRECTLY_SET);
}

// End - Test Suite: BlockHeader_TestSuite
ZTEST_SUITE_END()
