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

#include "ZIO/BinaryStreamWriter.h"
#include "ZIO/MemoryStream.h"
#include "ZCommon/Exceptions/AssertException.h"


ZTEST_SUITE_BEGIN( BinaryStreamWriter_TestSuite )

/// <summary>
/// Checks that the stream is correctly stored.
/// </summary>
ZTEST_CASE ( Constructor_StreamIsCorrectlyStored_Test )
{
    // [Preparation]
    MemoryStream<> memoryStream(1U);

    // [Execution]
    BinaryStreamWriter<MemoryStream<> > writer(memoryStream);
    
    // [Verification]
    bool bStreamIsStoredCorrectly = &memoryStream == &writer.GetStream();
    BOOST_CHECK(bStreamIsStoredCorrectly);
}

/// <summary>
/// Checks that the buffer is correctly written.
/// </summary>
ZTEST_CASE ( WriteBytes_BufferIsCorrectlyWritten_Test )
{
    // [Preparation]
    const int EXPECTED_VALUE = 123456;
    MemoryStream<> memoryStream(4U);
    BinaryStreamWriter<MemoryStream<> > writer(memoryStream);

    // [Execution]
    writer.WriteBytes(&EXPECTED_VALUE, sizeof(EXPECTED_VALUE));
    
    // [Verification]
    int nValue = 0;
    memoryStream.SetPosition(0);
    memoryStream.Read(&nValue, 0, sizeof(nValue));
    BOOST_CHECK_EQUAL(nValue, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the internal pointer of the stream is moved forward.
/// </summary>
ZTEST_CASE ( WriteBytes_StreamInternalPointerIsMovedForward_Test )
{
    // [Preparation]
    const int EXPECTED_VALUE = 123456;
    MemoryStream<> memoryStream(4U);
    BinaryStreamWriter<MemoryStream<> > writer(memoryStream);
    const puint_z ORIGINAL_POSITION = memoryStream.GetPosition();

    // [Execution]
    writer.WriteBytes(&EXPECTED_VALUE, sizeof(EXPECTED_VALUE));
    
    // [Verification]
    puint_z uPosition = memoryStream.GetPosition();
    BOOST_CHECK(uPosition > ORIGINAL_POSITION);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input buffer is null.
/// </summary>
ZTEST_CASE ( WriteBytes_AssertionFailsWhenInputBufferIsNull_Test )
{
    // [Preparation]
    const unsigned int STREAM_VALUE = 0xFEDCBA98;
    MemoryStream<> stream(&STREAM_VALUE, sizeof(STREAM_VALUE));
    BinaryStreamWriter< MemoryStream<> > writer(stream);
    
    const bool ASSERTION_FAILED = true;
    void* pNullPointer = null_z;

    // [Execution]
    bool bAssertionFailed = false;
    
    try
    {
        writer.WriteBytes(pNullPointer, sizeof(unsigned int));
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
ZTEST_CASE ( WriteBytes_AssertionFailsWhenSizeEqualsZero_Test )
{
    // [Preparation]
    const unsigned int STREAM_VALUE = 0xFEDCBA98;
    MemoryStream<> stream(&STREAM_VALUE, sizeof(STREAM_VALUE));
    BinaryStreamWriter< MemoryStream<> > writer(stream);
    
    const bool ASSERTION_FAILED = true;
    const puint_z ZERO_SIZE = 0;

    // [Execution]
    bool bAssertionFailed = false;
    
    try
    {
        unsigned int uValue;
        writer.WriteBytes(&uValue, ZERO_SIZE);
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
/// Checks that the instance is correctly written.
/// </summary>
ZTEST_CASE ( Write_BufferIsCorrectlyWritten_Test )
{
    // [Preparation]
    const int EXPECTED_VALUE = 123456;
    MemoryStream<> memoryStream(4U);
    BinaryStreamWriter<MemoryStream<> > writer(memoryStream);

    // [Execution]
    writer.Write(EXPECTED_VALUE);
    
    // [Verification]
    int nValue = 0;
    memoryStream.SetPosition(0);
    memoryStream.Read(&nValue, 0, sizeof(nValue));
    BOOST_CHECK_EQUAL(nValue, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the internal pointer of the stream is moved forward.
/// </summary>
ZTEST_CASE ( Write_StreamInternalPointerIsMovedForward_Test )
{
    // [Preparation]
    const int EXPECTED_VALUE = 123456;
    MemoryStream<> memoryStream(4U);
    BinaryStreamWriter<MemoryStream<> > writer(memoryStream);
    const puint_z ORIGINAL_POSITION = memoryStream.GetPosition();

    // [Execution]
    writer.Write(EXPECTED_VALUE);
    
    // [Verification]
    puint_z uPosition = memoryStream.GetPosition();
    BOOST_CHECK(uPosition > ORIGINAL_POSITION);
}

/// <summary>
/// Checks that the instance is correctly written.
/// </summary>
ZTEST_CASE ( OperatorLeftShift_BufferIsCorrectlyWritten_Test )
{
    // [Preparation]
    const int EXPECTED_VALUE = 123456;
    MemoryStream<> memoryStream(4U);
    BinaryStreamWriter<MemoryStream<> > writer(memoryStream);

    // [Execution]
    writer << EXPECTED_VALUE;
    
    // [Verification]
    int nValue = 0;
    memoryStream.SetPosition(0);
    memoryStream.Read(&nValue, 0, sizeof(nValue));
    BOOST_CHECK_EQUAL(nValue, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the internal pointer of the stream is moved forward.
/// </summary>
ZTEST_CASE ( OperatorLeftShift_StreamInternalPointerIsMovedForward_Test )
{
    // [Preparation]
    const int EXPECTED_VALUE = 123456;
    MemoryStream<> memoryStream(4U);
    BinaryStreamWriter<MemoryStream<> > writer(memoryStream);
    const puint_z ORIGINAL_POSITION = memoryStream.GetPosition();

    // [Execution]
    writer << EXPECTED_VALUE;
    
    // [Verification]
    puint_z uPosition = memoryStream.GetPosition();
    BOOST_CHECK(uPosition > ORIGINAL_POSITION);
}

/// <summary>
/// Checks that it returns a reference to the same instance of the writer.
/// </summary>
ZTEST_CASE ( OperatorLeftShift_ReturnsReferenceToSameInstance_Test )
{
    // [Preparation]
    const int INPUT_VALUE = 123456;
    MemoryStream<> memoryStream(4U);
    BinaryStreamWriter<MemoryStream<> > writer(memoryStream);
    BinaryStreamWriter<MemoryStream<> >* EXPECTED_POINTER = &writer;

    // [Execution]
    BinaryStreamWriter<MemoryStream<> >* pWriter = &(writer << INPUT_VALUE);
    
    // [Verification]
    BOOST_CHECK_EQUAL(pWriter, EXPECTED_POINTER);
}

/// <summary>
/// It is not necessary to test this method since it is just calls another method and there are no inputs nor outputs.
/// </summary>
ZTEST_CASE ( Flush_NotNecessaryToTest_Test )
{
    BOOST_TEST_MESSAGE("It is not necessary to test this method since it is just calls another method and there are no inputs nor outputs");
}

/// <summary>
/// It is not necessary to test this method since it is just a getter.
/// </summary>
ZTEST_CASE ( GetStream_NotNecessaryToTest_Test )
{
    BOOST_TEST_MESSAGE("It is not necessary to test this method since it is just a getter");
}

// End - Test Suite: BinaryStreamWriter
ZTEST_SUITE_END()
