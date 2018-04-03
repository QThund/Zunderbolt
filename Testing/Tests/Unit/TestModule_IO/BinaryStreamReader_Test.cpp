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

#include "ZIO/BinaryStreamReader.h"

// The MemoryStream type is used in all the tests
#include "ZIO/MemoryStream.h"
#include "ZCommon/Exceptions/AssertException.h"


ZTEST_SUITE_BEGIN( BinaryStreamReader_TestSuite )

/// <summary>
/// Checks that the stream is correctly stored.
/// </summary>
ZTEST_CASE ( Constructor_StreamIsCorrectlyStored_Test )
{
    // [Preparation]
    MemoryStream<> stream(1);
    const MemoryStream<>* EXPECTED_STREAM = &stream;

    // [Execution]
    BinaryStreamReader< MemoryStream<> > reader(stream);

    // [Verification]
    MemoryStream<>* pStoredStream = &reader.GetStream();
    BOOST_CHECK_EQUAL(pStoredStream, EXPECTED_STREAM);
}

/// <summary>
/// Checks that the value is read correctly.
/// </summary>
ZTEST_CASE ( OperatorRightShift_ValueIsReadCorrectly_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_VALUE = 0xFEDCBA98;
    MemoryStream<> stream(&EXPECTED_VALUE, sizeof(EXPECTED_VALUE));
    BinaryStreamReader< MemoryStream<> > reader(stream);

    // [Execution]
    unsigned int uValue = 0;
    reader >> uValue;

    // [Verification]
    BOOST_CHECK_EQUAL(uValue, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the stream pointer is moved forward.
/// </summary>
ZTEST_CASE ( OperatorRightShift_StreamPointerIsMovedForward_Test )
{
    // [Preparation]
    const unsigned int STREAM_VALUE = 0xFEDCBA98;
    MemoryStream<> stream(&STREAM_VALUE, sizeof(STREAM_VALUE));
    BinaryStreamReader< MemoryStream<> > reader(stream);
    const puint_z ORIGINAL_POINTER_POSITION = stream.GetPosition();

    // [Execution]
    unsigned int uValue = 0;
    reader >> uValue;

    // [Verification]
    puint_z uPointerPosition = reader.GetStream().GetPosition();
    BOOST_CHECK(uPointerPosition > ORIGINAL_POINTER_POSITION);
}

/// <summary>
/// Checks that the method returns a reference to the resident instance.
/// </summary>
ZTEST_CASE ( OperatorRightShift_ReturnsResidentInstance_Test )
{
    // [Preparation]
    const unsigned int STREAM_VALUE = 0xFEDCBA98;
    MemoryStream<> stream(&STREAM_VALUE, sizeof(STREAM_VALUE));
    BinaryStreamReader< MemoryStream<> > reader(stream);
    BinaryStreamReader< MemoryStream<> >* EXPECTED_INSTANCE = &reader;

    // [Execution]
    unsigned int uValue = 0;
    BinaryStreamReader< MemoryStream<> >* pReader = &(reader >> uValue);

    // [Verification]
    BOOST_CHECK_EQUAL(pReader, EXPECTED_INSTANCE);
}

/// <summary>
/// Checks that the value is read correctly.
/// </summary>
ZTEST_CASE ( ReadBytes_ValueIsReadCorrectly_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_VALUE = 0xFEDCBA98;
    MemoryStream<> stream(&EXPECTED_VALUE, sizeof(EXPECTED_VALUE));
    BinaryStreamReader< MemoryStream<> > reader(stream);

    // [Execution]
    unsigned int uValue = 0;
    reader.ReadBytes(&uValue, sizeof(EXPECTED_VALUE));

    // [Verification]
    BOOST_CHECK_EQUAL(uValue, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the stream pointer is moved forward.
/// </summary>
ZTEST_CASE ( ReadBytes_StreamPointerIsMovedForward_Test )
{
    // [Preparation]
    const unsigned int STREAM_VALUE = 0xFEDCBA98;
    MemoryStream<> stream(&STREAM_VALUE, sizeof(STREAM_VALUE));
    BinaryStreamReader< MemoryStream<> > reader(stream);
    const puint_z ORIGINAL_POINTER_POSITION = stream.GetPosition();

    // [Execution]
    unsigned int uValue = 0;
    reader.ReadBytes(&uValue, sizeof(unsigned int));

    // [Verification]
    puint_z uPointerPosition = reader.GetStream().GetPosition();
    BOOST_CHECK(uPointerPosition > ORIGINAL_POINTER_POSITION);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input buffer is null.
/// </summary>
ZTEST_CASE ( ReadBytes_AssertionFailsWhenInputBufferIsNull_Test )
{
    // [Preparation]
    const unsigned int STREAM_VALUE = 0xFEDCBA98;
    MemoryStream<> stream(&STREAM_VALUE, sizeof(STREAM_VALUE));
    BinaryStreamReader< MemoryStream<> > reader(stream);
    
    const bool ASSERTION_FAILED = true;
    void* pNullPointer = null_z;

    // [Execution]
    bool bAssertionFailed = false;
    
    try
    {
        reader.ReadBytes(pNullPointer, sizeof(unsigned int));
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the input buffer size equals zero.
/// </summary>
ZTEST_CASE ( ReadBytes_AssertionFailsWhenSizeEqualsZero_Test )
{
    // [Preparation]
    const unsigned int STREAM_VALUE = 0xFEDCBA98;
    MemoryStream<> stream(&STREAM_VALUE, sizeof(STREAM_VALUE));
    BinaryStreamReader< MemoryStream<> > reader(stream);
    
    const bool ASSERTION_FAILED = true;
    const puint_z ZERO_SIZE = 0;

    // [Execution]
    bool bAssertionFailed = false;
    
    try
    {
        unsigned int uValue;
        reader.ReadBytes(&uValue, ZERO_SIZE);
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
/// Checks that the value is read correctly.
/// </summary>
ZTEST_CASE ( Read_ValueIsReadCorrectly_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_VALUE = 0xFEDCBA98;
    MemoryStream<> stream(&EXPECTED_VALUE, sizeof(EXPECTED_VALUE));
    BinaryStreamReader< MemoryStream<> > reader(stream);

    // [Execution]
    unsigned int uValue = reader.Read<unsigned int>();

    // [Verification]
    BOOST_CHECK_EQUAL(uValue, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the stream pointer is moved forward.
/// </summary>
ZTEST_CASE ( Read_StreamPointerIsMovedForward_Test )
{
    // [Preparation]
    const unsigned int STREAM_VALUE = 0xFEDCBA98;
    MemoryStream<> stream(&STREAM_VALUE, sizeof(STREAM_VALUE));
    BinaryStreamReader< MemoryStream<> > reader(stream);
    const puint_z ORIGINAL_POINTER_POSITION = stream.GetPosition();

    // [Execution]
    reader.Read<unsigned int>();

    // [Verification]
    puint_z uPointerPosition = reader.GetStream().GetPosition();
    BOOST_CHECK(uPointerPosition > ORIGINAL_POINTER_POSITION);
}

/// <summary>
/// It is not necessary to test this method since it is just a getter.
/// </summary>
ZTEST_CASE ( GetStream_NotNecessaryToTest_Test )
{
    BOOST_TEST_MESSAGE("It is not necessary to test this method since it is just a getter");
}

// End - Test Suite: BinaryStreamReader
ZTEST_SUITE_END()
