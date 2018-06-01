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

#include "ZCommon/AllocationOperators.h"
#include "ZCommon/Alignment.h"
#include "ZCommon/Exceptions/AssertException.h"


// --------------------------------------------------------------------------------------------------------
// Eight bytes size supporting struct for allocation and deallocation of memory blocks.
// --------------------------------------------------------------------------------------------------------
struct TFooEightBytesSize
{
    char m_field01;
    char m_field02;
    char m_field03;
    char m_field04;
    char m_field05;
    char m_field06;
    char m_field07;
    char m_field08;

    TFooEightBytesSize() : m_field01('a'), m_field02('b'), m_field03('c'), m_field04('d'), m_field05('e'), m_field06('f'), m_field07('g'), m_field08('h') {}
};


ZTEST_SUITE_BEGIN( AllocationOperators_TestSuite )

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when a non-aligned memory block is passed to the overloaded delete operator.
/// </summary>
ZTEST_CASE ( OperatorDelete_AssertionFailsWhenReceivedANonAlignedMemoryBlock_Test )
{
    // [Preparation]

    const bool           ASSERTION_FAILED             = true;
    bool                 bAssertionFailed01           = false;

    const puint_z ALIGNMENT_VALUE_POWER_OF_TWO = 8;
    Alignment           align_001(ALIGNMENT_VALUE_POWER_OF_TWO);

    TFooEightBytesSize* pFoo001                       = null_z;


	// [Execution]

    try
    {
        // Memory block probably not aligned in memory. However, note that the size
        // of the memory block is 1 byte bigger, that's because maybe it's necessary
        // to provide manually a non-aligned addrees (se below).
        char  arMemoryBuffer[sizeof(TFooEightBytesSize) + 1];
        arMemoryBuffer[sizeof(TFooEightBytesSize)] = '\0';
        char* p                                  = arMemoryBuffer;

        // If true, the pointer is pointing to an aligned address, so it's necessary
        // to modify the pointer manually in order to provide a non-aligned address.
        if ( 0 == ((rcast_z(p, puint_z)) & (align_001 - 1)) )
        {
            // Now it's pointing to a definitively not aligned memory address.
            ++p;
        }

        // Finally, the struct is created in the NON-aligned memory block.
        void*   q = p;
        pFoo001   = new (q) TFooEightBytesSize();

        if (null_z != pFoo001)
        {
            // Assert will fail due to the allocated memory block is not aligned.
            operator delete(pFoo001, align_001);
            pFoo001 = null_z;
        }
    }
    catch(const AssertException&)
    {
        bAssertionFailed01 = true;
    }


    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed01, ASSERTION_FAILED);

}

/// <summary>
/// Checks that an assertion fails when a non-aligned memory block is passed to the overloaded delete[] operator.
/// </summary>
ZTEST_CASE ( OperatorDeleteArray_AssertionFailsWhenReceivedANonAlignedMemoryBlock_Test )
{
    // [Preparation]

    const bool           ASSERTION_FAILED             = true;
    bool                 bAssertionFailed02           = false;

    const puint_z ALIGNMENT_VALUE_POWER_OF_TWO = 8;
    Alignment           align_002(ALIGNMENT_VALUE_POWER_OF_TWO);

    TFooEightBytesSize*  pFoo002                      = null_z;


	// [Execution]

    try
    {
        // Memory block probably not aligned in memory. However, note that the size
        // of the memory block is 1 byte bigger, that's because maybe it's necessary
        // to provide manually a non-aligned addrees (se below).
        char  arMemoryBuffer[sizeof(TFooEightBytesSize) + 1];
        arMemoryBuffer[sizeof(TFooEightBytesSize)] = '\0';
        char* p                                  = arMemoryBuffer;

        // If true, the pointer is pointing to an aligned address, so it's necessary
        // to modify the pointer manually in order to provide a non-aligned address.
        if ( 0 == ((rcast_z(p, puint_z)) & (align_002 - 1)) )
        {
            // Now it's pointing to a definitively not aligned memory address.
            ++p;
        }

        // Finally, the struct is created in the NON-aligned memory block.
        void*   q = p;
        pFoo002   = new (q) TFooEightBytesSize();

        if (null_z != pFoo002)
        {
            // Assert will fail due to the allocated memory block is not aligned.
            operator delete[](pFoo002, align_002);
            pFoo002 = null_z;
        }
    }
    catch(const AssertException&)
    {
        bAssertionFailed02 = true;
    }


    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed02, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

// End - Test Suite: AllocationAndDeallocationOperators
ZTEST_SUITE_END()
