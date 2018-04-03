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

#include "ZIO/MemoryStream.h"
#include "ZCommon/Exceptions/AssertException.h"


ZTEST_SUITE_BEGIN( MemoryStream_TestSuite )

/// <summary>
/// Checks that the stream is correctly constructed when using a common buffer size.
/// </summary>
ZTEST_CASE ( Constructor1_ItIsCorrectlyConstructedWhenUsingCommonSize_Test )
{
    // [Preparation]
    const puint_z BUFFER_SIZE = 4U;
    const puint_z EXPECTED_LENGTH = 0;

    // [Execution]
    MemoryStream<> stream(BUFFER_SIZE);
    
    // [Verification]
    puint_z uLength = stream.GetLength();
    BOOST_CHECK_EQUAL(uLength, EXPECTED_LENGTH);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input size equals zero.
/// </summary>
ZTEST_CASE ( Constructor1_AssertionFailsWhenInputSizeIsZero_Test )
{
    // [Preparation]
    const puint_z INPUT_SIZE = 0;
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        MemoryStream<> stream(INPUT_SIZE);
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
/// Checks that the stream is correctly constructed when using a common buffer size and a valid buffer.
/// </summary>
ZTEST_CASE ( Constructor2_ItIsCorrectlyConstructedWhenUsingCommonSizeAndValidBuffer_Test )
{
    // [Preparation]
    const puint_z BUFFER_SIZE = sizeof(u32_z);
    const u32_z CONTENT = 0x01020304;
    const puint_z EXPECTED_LENGTH = BUFFER_SIZE;

    // [Execution]
    MemoryStream<> stream(&CONTENT, BUFFER_SIZE);
    
    // [Verification]
    puint_z uLength = stream.GetLength();
    BOOST_CHECK_EQUAL(uLength, EXPECTED_LENGTH);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input size equals zero.
/// </summary>
ZTEST_CASE ( Constructor2_AssertionFailsWhenInputSizeIsZero_Test )
{
    // [Preparation]
    const puint_z INPUT_SIZE = 0;
    const u32_z CONTENT = 0x01020304;
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        MemoryStream<> stream(&CONTENT, INPUT_SIZE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the buffer is null.
/// </summary>
ZTEST_CASE ( Constructor2_AssertionFailsWhenBufferIsNull_Test )
{
    // [Preparation]
    const puint_z INPUT_SIZE = 4U;
    void* pBuffer = null_z;
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        MemoryStream<> stream(pBuffer, INPUT_SIZE);
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
/// Checks that the stream is correctly copied.
/// </summary>
ZTEST_CASE ( Constructor3_ItIsCorrectlyCopied_Test )
{
    // [Preparation]
    const puint_z BUFFER_SIZE = 8U;
    const u32_z CONTENT = 1234;
    MemoryStream<> originalStream(BUFFER_SIZE);
    originalStream.Write(&CONTENT, 0, sizeof(CONTENT));

    // [Execution]
    MemoryStream<> stream(originalStream);
    
    // [Verification]
    puint_z uLength = stream.GetLength();
    u32_z nContent = 0;
    stream.Read(&nContent, 0, sizeof(CONTENT));

    BOOST_CHECK_EQUAL(uLength, sizeof(CONTENT));
    BOOST_CHECK_EQUAL(nContent, CONTENT);
}

/// <summary>
/// Checks that the stream is correctly copied when it is empty.
/// </summary>
ZTEST_CASE ( Constructor3_ItIsCorrectlyCopiedWhenInputIsEmpty_Test )
{
    // [Preparation]
    const puint_z BUFFER_SIZE = 8U;
    const puint_z EXPECTED_LENGTH = 0;
    MemoryStream<> originalStream(BUFFER_SIZE);

    // [Execution]
    MemoryStream<> stream(originalStream);
    
    // [Verification]
    puint_z uLength = stream.GetLength();

    BOOST_CHECK_EQUAL(uLength, EXPECTED_LENGTH);
}

/// <summary>
/// Checks that output offset affects the result.
/// </summary>
ZTEST_CASE ( Read_OutputOffsetAffectsTheResult_Test )
{
    // [Preparation]
    const u32_z CONTENT = 0x01020304;
    const puint_z OFFSET1 = 1U;
    const puint_z OFFSET2 = 2U;
    const u32_z EXPECTED_CONTENT_OFFSET1 = 0x00030400;
    const u32_z EXPECTED_CONTENT_OFFSET2 = 0x03040000;
    const puint_z READ_BLOCK_SIZE = 2U;
    const puint_z BUFFER_SIZE = 4U;
    MemoryStream<> stream(&CONTENT, BUFFER_SIZE);

    // [Execution]
    u32_z nContentOffset1 = 0;
    stream.Read(&nContentOffset1, OFFSET1, READ_BLOCK_SIZE);

    u32_z nContentOffset2 = 0;
    stream.SetPosition(0); // To read from the beginning again
    stream.Read(&nContentOffset2, OFFSET2, READ_BLOCK_SIZE);
    
    // [Verification]
    BOOST_CHECK_EQUAL(nContentOffset1, EXPECTED_CONTENT_OFFSET1);
    BOOST_CHECK_EQUAL(nContentOffset2, EXPECTED_CONTENT_OFFSET2);
}

/// <summary>
/// Checks that the complete stream can be read.
/// </summary>
ZTEST_CASE ( Read_TheCompleteStreamCanBeRead_Test )
{
    // [Preparation]
    const u32_z CONTENT = 0x01020304;
    const puint_z OFFSET = 0;
    const puint_z BUFFER_SIZE = 4U;
    const puint_z READ_BLOCK_SIZE = BUFFER_SIZE;
    MemoryStream<> stream(&CONTENT, BUFFER_SIZE);

    // [Execution]
    u32_z nContent = 0;
    stream.Read(&nContent, OFFSET, READ_BLOCK_SIZE);

    // [Verification]
    BOOST_CHECK_EQUAL(nContent, CONTENT);
}

/// <summary>
/// Checks that the read pointer is moved forward after every read operation.
/// </summary>
ZTEST_CASE ( Read_InternalReadPointerIsMovedForwardAutomatically_Test )
{
    // [Preparation]
    const u32_z CONTENT = 0x01020304;
    const puint_z OFFSET = 0;
    const puint_z BUFFER_SIZE = 4U;
    const puint_z READ_BLOCK_SIZE = 2U;
    MemoryStream<> stream(&CONTENT, BUFFER_SIZE);

    // [Execution]
    u32_z nContent = 0;
    stream.Read(&nContent, OFFSET, READ_BLOCK_SIZE);
    stream.Read(&nContent, OFFSET + READ_BLOCK_SIZE, READ_BLOCK_SIZE);

    // [Verification]
    BOOST_CHECK_EQUAL(nContent, CONTENT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the output buffer is null.
/// </summary>
ZTEST_CASE ( Read_AssertionFailsWhenOutputBufferIsNull_Test )
{
    // [Preparation]
    const puint_z INPUT_SIZE = 4U;
    void* pBuffer = null_z;
    MemoryStream<> stream(INPUT_SIZE);
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        stream.Read(pBuffer, 0, INPUT_SIZE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the output size equals zero.
/// </summary>
ZTEST_CASE ( Read_AssertionFailsWhenOutputSizeIsZero_Test )
{
    // [Preparation]
    const puint_z INPUT_SIZE = 0;
    u32_z nBuffer;
    MemoryStream<> stream(4U);
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        stream.Read(&nBuffer, 0, INPUT_SIZE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when trying to read out of the buffer.
/// </summary>
ZTEST_CASE ( Read_AssertionFailsWhenTryingToReadOutOfBounds_Test )
{
    // [Preparation]
    const puint_z INPUT_SIZE = 4U;
    const puint_z OFFSET = 2U;
    u64_z uBuffer;
    u32_z* pBuffer = rcast_z(&uBuffer, u32_z*);
    MemoryStream<> stream(INPUT_SIZE);
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        stream.Read(pBuffer, OFFSET, INPUT_SIZE);
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
/// Checks that input offset affects the result.
/// </summary>
ZTEST_CASE ( Write_InputOffsetAffectsTheResult_Test )
{
    // [Preparation]
    const u32_z NEW_CONTENT = 0x01020304;
    const u32_z ORIGINAL_CONTENT = 0;
    const puint_z OFFSET1 = 1U;
    const puint_z OFFSET2 = 2U;
    const u32_z EXPECTED_CONTENT_OFFSET1 = 0x00000203;
    const u32_z EXPECTED_CONTENT_OFFSET2 = 0x00000102;
    const puint_z WRITE_BLOCK_SIZE = 2U;
    const puint_z BUFFER_SIZE = 4U;
    MemoryStream<> stream1(&ORIGINAL_CONTENT, BUFFER_SIZE);
    MemoryStream<> stream2(&ORIGINAL_CONTENT, BUFFER_SIZE);

    // [Execution]
    stream1.Write(&NEW_CONTENT, OFFSET1, WRITE_BLOCK_SIZE);
    stream2.Write(&NEW_CONTENT, OFFSET2, WRITE_BLOCK_SIZE);
    
    // [Verification]
    u32_z nContentOffset1 = 0;
    u32_z nContentOffset2 = 0;
    stream1.SetPosition(0);
    stream2.SetPosition(0);
    stream1.Read(&nContentOffset1, 0, BUFFER_SIZE);
    stream2.Read(&nContentOffset2, 0, BUFFER_SIZE);
    BOOST_CHECK_EQUAL(nContentOffset1, EXPECTED_CONTENT_OFFSET1);
    BOOST_CHECK_EQUAL(nContentOffset2, EXPECTED_CONTENT_OFFSET2);
}

/// <summary>
/// Checks that it is possible to write blocks that are bigger than the buffer's size.
/// </summary>
ZTEST_CASE ( Write_ItIsPossibleToWriteABlockBiggerThanBufferSize_Test )
{
    // [Preparation]
    const u64_z EXPECTED_CONTENT = 0x0102030405060708;
    const u32_z ORIGINAL_CONTENT = 0;
    const puint_z OFFSET = 0;
    const puint_z BUFFER_SIZE = 4U;
    const puint_z WRITE_BLOCK_SIZE = sizeof(u64_z);
    MemoryStream<> stream(&ORIGINAL_CONTENT, BUFFER_SIZE);

    // [Execution]
    stream.Write(&EXPECTED_CONTENT, OFFSET, WRITE_BLOCK_SIZE);

    // [Verification]
    u64_z nContent = 0;
    stream.SetPosition(0);
    stream.Read(&nContent, 0, sizeof(u64_z));
    BOOST_CHECK_EQUAL(nContent, EXPECTED_CONTENT);
}

/// <summary>
/// Checks that the buffer grows as more memory is necessary.
/// </summary>
ZTEST_CASE ( Write_TheBufferGrowsAsMoreMemoryIsNecessary_Test )
{
    // [Preparation]
    const u32_z CONTENT_TO_WRITE1 = 0x05060708;
    const u32_z CONTENT_TO_WRITE2 = 0x01020304;
    const u32_z ORIGINAL_CONTENT = 0;
    const puint_z OFFSET = 0;
    const puint_z ORIGINAL_BUFFER_SIZE = sizeof(u32_z);
    const puint_z WRITE_BLOCK_SIZE = sizeof(u32_z);
    MemoryStream<> stream(&ORIGINAL_CONTENT, ORIGINAL_BUFFER_SIZE);

    // [Execution]
    stream.Write(&CONTENT_TO_WRITE1, OFFSET, WRITE_BLOCK_SIZE);
    stream.Write(&CONTENT_TO_WRITE2, OFFSET, WRITE_BLOCK_SIZE);

    // [Verification]
    puint_z uBufferLength = stream.GetLength();
    BOOST_CHECK(uBufferLength > ORIGINAL_BUFFER_SIZE);
}

/// <summary>
/// Checks that the internal write pointer is automatically moved forward on every write operation.
/// </summary>
ZTEST_CASE ( Write_TheInternalPointerIsMovedAutomatically_Test )
{
    // [Preparation]
    const u64_z EXPECTED_CONTENT = 0x0102030405060708;
    const u32_z CONTENT_TO_WRITE1 = 0x05060708;
    const u32_z CONTENT_TO_WRITE2 = 0x01020304;
    const u32_z ORIGINAL_CONTENT = 0;
    const puint_z OFFSET = 0;
    const puint_z BUFFER_SIZE = sizeof(u32_z);
    const puint_z WRITE_BLOCK_SIZE = sizeof(u32_z);
    MemoryStream<> stream(&ORIGINAL_CONTENT, BUFFER_SIZE);

    // [Execution]
    stream.Write(&CONTENT_TO_WRITE1, OFFSET, WRITE_BLOCK_SIZE);
    stream.Write(&CONTENT_TO_WRITE2, OFFSET, WRITE_BLOCK_SIZE);

    // [Verification]
    u64_z nContent = 0;
    stream.SetPosition(0);
    stream.Read(&nContent, 0, sizeof(u64_z));
    BOOST_CHECK_EQUAL(nContent, EXPECTED_CONTENT);
}

/// <summary>
/// Checks that blocks are correctly written when they occupy both allocated and non-allocated memory.
/// </summary>
ZTEST_CASE ( Write_ItWorksWhenWrittenBlockOccupiesBothAllocatedAndNonAllocatedMemory_Test )
{
    // [Preparation]
    const u32_z CONTENT_TO_WRITE1 = 0x05060708;
    const u32_z CONTENT_TO_WRITE2 = 0x01020304;
    const u32_z ORIGINAL_CONTENT = 0;
    const puint_z OFFSET = 0;
    const puint_z BUFFER_SIZE = sizeof(u32_z);
    const puint_z WRITE_BLOCK_SIZE = sizeof(u32_z);
    MemoryStream<> stream(&ORIGINAL_CONTENT, BUFFER_SIZE);

    // [Execution]
    stream.Write(&CONTENT_TO_WRITE1, OFFSET, WRITE_BLOCK_SIZE);
    stream.SetPosition(2U);
    stream.Write(&CONTENT_TO_WRITE2, OFFSET, WRITE_BLOCK_SIZE);

    // [Verification]
    puint_z uBufferLength = stream.GetLength();
    BOOST_CHECK(uBufferLength > BUFFER_SIZE);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input buffer is null.
/// </summary>
ZTEST_CASE ( Write_AssertionFailsWhenInputBufferIsNull_Test )
{
    // [Preparation]
    const puint_z INPUT_SIZE = 4U;
    void* pBuffer = null_z;
    MemoryStream<> stream(INPUT_SIZE);
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        stream.Write(pBuffer, 0, INPUT_SIZE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the input size equals zero.
/// </summary>
ZTEST_CASE ( Write_AssertionFailsWhenInputSizeIsZero_Test )
{
    // [Preparation]
    const puint_z INPUT_SIZE = 0;
    u32_z nBuffer;
    MemoryStream<> stream(4U);
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        stream.Write(&nBuffer, 0, INPUT_SIZE);
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
/// Checks that the source stream's offset affects the result.
/// </summary>
ZTEST_CASE ( CopyTo_SourceOffsetAffectsTheResult_Test )
{
    // [Preparation]
    const u32_z NEW_CONTENT = 0x01020304;
    const u32_z ORIGINAL_CONTENT = 0;
    const puint_z DESTINATION_OFFSET = 0;
    const puint_z OFFSET1 = 1U;
    const puint_z OFFSET2 = 2U;
    const u32_z EXPECTED_CONTENT_OFFSET1 = 0x00020304;
    const u32_z EXPECTED_CONTENT_OFFSET2 = 0x00000304;
    const puint_z BUFFER_SIZE = 4U;
    MemoryStream<> sourceStream(&NEW_CONTENT, BUFFER_SIZE);
    MemoryStream<> stream1(&ORIGINAL_CONTENT, BUFFER_SIZE);
    MemoryStream<> stream2(&ORIGINAL_CONTENT, BUFFER_SIZE);

    // [Execution]
    sourceStream.CopyTo(stream1, OFFSET1, DESTINATION_OFFSET, BUFFER_SIZE - OFFSET1);
    sourceStream.CopyTo(stream2, OFFSET2, DESTINATION_OFFSET, BUFFER_SIZE - OFFSET2);
    
    // [Verification]
    u32_z nContentOffset1 = 0;
    u32_z nContentOffset2 = 0;
    stream1.SetPosition(0);
    stream2.SetPosition(0);
    stream1.Read(&nContentOffset1, 0, sizeof(u32_z));
    stream2.Read(&nContentOffset2, 0, sizeof(u32_z));
    BOOST_CHECK_EQUAL(nContentOffset1, EXPECTED_CONTENT_OFFSET1);
    BOOST_CHECK_EQUAL(nContentOffset2, EXPECTED_CONTENT_OFFSET2);
}

/// <summary>
/// Checks that the destination stream's offset affects the result.
/// </summary>
ZTEST_CASE ( CopyTo_DestinationOffsetAffectsTheResult_Test )
{
    // [Preparation]
    const u32_z NEW_CONTENT = 0x01020304;
    const u32_z ORIGINAL_CONTENT = 0;
    const puint_z SOURCE_OFFSET = 0;
    const puint_z OFFSET1 = 1U;
    const puint_z OFFSET2 = 2U;
    const u32_z EXPECTED_CONTENT_OFFSET1 = 0x02030400;
    const u32_z EXPECTED_CONTENT_OFFSET2 = 0x03040000;
    const puint_z BUFFER_SIZE = 4U;
    MemoryStream<> sourceStream(&NEW_CONTENT, BUFFER_SIZE);
    MemoryStream<> stream1(&ORIGINAL_CONTENT, BUFFER_SIZE);
    MemoryStream<> stream2(&ORIGINAL_CONTENT, BUFFER_SIZE);

    // [Execution]
    sourceStream.CopyTo(stream1, SOURCE_OFFSET, OFFSET1, BUFFER_SIZE);
    sourceStream.CopyTo(stream2, SOURCE_OFFSET, OFFSET2, BUFFER_SIZE);
    
    // [Verification]
    u32_z nContentOffset1 = 0;
    u32_z nContentOffset2 = 0;
    stream1.SetPosition(0);
    stream2.SetPosition(0);
    stream1.Read(&nContentOffset1, 0, sizeof(u32_z));
    stream2.Read(&nContentOffset2, 0, sizeof(u32_z));
    BOOST_CHECK_EQUAL(nContentOffset1, EXPECTED_CONTENT_OFFSET1);
    BOOST_CHECK_EQUAL(nContentOffset2, EXPECTED_CONTENT_OFFSET2);
}

/// <summary>
/// Checks that streams can be completely copied.
/// </summary>
ZTEST_CASE ( CopyTo_StreamCanBeCompletelyCopied_Test )
{
    // [Preparation]
    u8_z NEW_CONTENT[10000];
    memset(NEW_CONTENT, 0x01, sizeof(NEW_CONTENT));

    const bool ARE_EQUAL = true;
    const puint_z DESTINATION_OFFSET = 0;
    const puint_z SOURCE_OFFSET = 0;
    const puint_z BUFFER_SIZE = sizeof(NEW_CONTENT);

    MemoryStream<> sourceStream(&NEW_CONTENT, BUFFER_SIZE);
    MemoryStream<> stream(4U);

    // [Execution]
    sourceStream.CopyTo(stream, SOURCE_OFFSET, DESTINATION_OFFSET, BUFFER_SIZE);
    
    // [Verification]
    u8_z arContent[10000];
    stream.SetPosition(0);
    stream.Read(arContent, 0, sizeof(NEW_CONTENT));
    bool bAreEqual = memcmp(arContent, NEW_CONTENT, sizeof(NEW_CONTENT)) == 0;

    BOOST_CHECK_EQUAL(bAreEqual, ARE_EQUAL);
}

/// <summary>
/// Checks that the destination stream grows when it is necessary.
/// </summary>
ZTEST_CASE ( CopyTo_DestinationStreamGrowsWhenNecessary_Test )
{
    // [Preparation]
    const u64_z NEW_CONTENT = 0x0102030405060708;
    const puint_z DESTINATION_OFFSET = 0;
    const puint_z SOURCE_OFFSET = 0;
    const puint_z SOURCE_BUFFER_SIZE = sizeof(NEW_CONTENT);
    const puint_z DESTINATION_BUFFER_SIZE = 4U;

    MemoryStream<> sourceStream(&NEW_CONTENT, SOURCE_BUFFER_SIZE);
    MemoryStream<> stream(DESTINATION_BUFFER_SIZE);

    // [Execution]
    sourceStream.CopyTo(stream, SOURCE_OFFSET, DESTINATION_OFFSET, SOURCE_BUFFER_SIZE);
    
    // [Verification]
    puint_z uDestinationLength = stream.GetLength();
    BOOST_CHECK(uDestinationLength > DESTINATION_BUFFER_SIZE);
}

/// <summary>
/// Checks that the internal pointer of the source stream is moved forward.
/// </summary>
ZTEST_CASE ( CopyTo_SourceStreamInternalPointerIsMovedForward_Test )
{
    // [Preparation]
    const u64_z NEW_CONTENT = 0x0102030405060708;
    const puint_z DESTINATION_OFFSET = 0;
    const puint_z SOURCE_OFFSET = 0;
    const puint_z BUFFER_SIZE = sizeof(NEW_CONTENT);
    const puint_z EXPECTED_POSITION = BUFFER_SIZE;

    MemoryStream<> sourceStream(&NEW_CONTENT, BUFFER_SIZE);
    sourceStream.GetCurrentPointer();

    MemoryStream<> stream(BUFFER_SIZE);

    // [Execution]
    sourceStream.CopyTo(stream, SOURCE_OFFSET, DESTINATION_OFFSET, BUFFER_SIZE);
    
    // [Verification]
    puint_z uPosition = sourceStream.GetPosition();
    BOOST_CHECK_EQUAL(uPosition, EXPECTED_POSITION);
}

/// <summary>
/// Checks that the internal pointer of the destination stream is moved forward.
/// </summary>
ZTEST_CASE ( CopyTo_DestinationStreamInternalPointerIsMovedForward_Test )
{
    // [Preparation]
    const u64_z NEW_CONTENT = 0x0102030405060708;
    const puint_z DESTINATION_OFFSET = 0;
    const puint_z SOURCE_OFFSET = 0;
    const puint_z BUFFER_SIZE = sizeof(NEW_CONTENT);

    MemoryStream<> sourceStream(&NEW_CONTENT, BUFFER_SIZE);
    MemoryStream<> stream(BUFFER_SIZE);
    void* pOriginalPointer = stream.GetCurrentPointer();

    // [Execution]
    sourceStream.CopyTo(stream, SOURCE_OFFSET, DESTINATION_OFFSET, BUFFER_SIZE);
    
    // [Verification]
    void* pCurrentPointer = stream.GetCurrentPointer();
    BOOST_CHECK_NE(pOriginalPointer, pCurrentPointer);
}

/// <summary>
/// Checks that the internal pointer of the source stream is moved to the source offset when the number of bytes to copy is zero.
/// </summary>
ZTEST_CASE ( CopyTo_SourceStreamInternalPointerIsMovedToOffsetWhenNumberOfBytesToCopyEqualsZero_Test )
{
    // [Preparation]
    const u64_z NEW_CONTENT = 0x0102030405060708;
    const puint_z DESTINATION_OFFSET = 0;
    const puint_z SOURCE_OFFSET = 1U;
    const puint_z BUFFER_SIZE = sizeof(NEW_CONTENT);
    const puint_z EXPECTED_POSITION = SOURCE_OFFSET;
    const puint_z NUMBER_OF_BYTES = 0;

    MemoryStream<> sourceStream(&NEW_CONTENT, BUFFER_SIZE);
    sourceStream.GetCurrentPointer();

    MemoryStream<> stream(BUFFER_SIZE);

    // [Execution]
    sourceStream.CopyTo(stream, SOURCE_OFFSET, DESTINATION_OFFSET, NUMBER_OF_BYTES);
    
    // [Verification]
    puint_z uPosition = sourceStream.GetPosition();
    BOOST_CHECK_EQUAL(uPosition, EXPECTED_POSITION);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the source stream's offset is out of bounds.
/// </summary>
ZTEST_CASE ( CopyTo_AssertionFailsWhenSourceOffsetIsOutOfBounds_Test )
{
    // [Preparation]
    const puint_z SOURCE_OFFSET = 5U;
    u32_z nBuffer;
    MemoryStream<> sourceStream(&nBuffer, 4U);
    MemoryStream<> destinationStream(&nBuffer, 4U);
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        sourceStream.CopyTo(destinationStream, SOURCE_OFFSET, 0, 4U);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the destination stream's offset is out of bounds.
/// </summary>
ZTEST_CASE ( CopyTo_AssertionFailsWhenDestinationOffsetIsOutOfBounds_Test )
{
    // [Preparation]
    const puint_z DESTINATION_OFFSET = 5U;
    u32_z nBuffer;
    MemoryStream<> sourceStream(&nBuffer, 4U);
    MemoryStream<> destinationStream(&nBuffer, 4U);
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        sourceStream.CopyTo(destinationStream, 0, DESTINATION_OFFSET, 4U);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the number of bytes to copy exceeds the limits of the source stream.
/// </summary>
ZTEST_CASE ( CopyTo_AssertionFailsWhenNumberOfBytesExceedsSourceStreamBounds_Test )
{
    // [Preparation]
    const puint_z SOURCE_OFFSET = 2U;
    u32_z nBuffer;
    MemoryStream<> sourceStream(&nBuffer, 4U);
    MemoryStream<> destinationStream(&nBuffer, 4U);
    const puint_z NUMBER_OF_BYTES = 3U;
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        sourceStream.CopyTo(destinationStream, SOURCE_OFFSET, 0, NUMBER_OF_BYTES);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the batch size equals zero.
/// </summary>
ZTEST_CASE ( CopyTo_AssertionFailsWhenBatchSizeIsZero_Test )
{
    // [Preparation]
    const puint_z SOURCE_OFFSET = 2U;
    u32_z nBuffer;
    MemoryStream<> sourceStream(&nBuffer, 4U);
    MemoryStream<> destinationStream(&nBuffer, 4U);
    const puint_z NUMBER_OF_BYTES = 2U;
    const puint_z BATCH_SIZE = 0;
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        sourceStream.CopyTo(destinationStream, SOURCE_OFFSET, 0, NUMBER_OF_BYTES, BATCH_SIZE);
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
/// It is not necessary to test this method since it does nothing.
/// </summary>
ZTEST_CASE ( Flush_NotNecessaryToTest_Test )
{
    BOOST_TEST_MESSAGE("It is not necessary to test this method since it does nothing");
}

/// <summary>
/// Checks that the internal pointer is correctly moved.
/// </summary>
ZTEST_CASE ( MoveBackward_PointerIsCorrectlyMoved_Test )
{
    // [Preparation]
    const u64_z NEW_CONTENT = 0x0102030405060708;
    const puint_z MOVEMENT = 1U;
    const puint_z BUFFER_SIZE = sizeof(NEW_CONTENT);

    MemoryStream<> stream(&NEW_CONTENT, BUFFER_SIZE);
    stream.SetPosition(1);
    puint_z uOriginalPointer = stream.GetPosition();

    // [Execution]
    stream.MoveBackward(MOVEMENT);
    
    // [Verification]
    puint_z uCurrentPointer = stream.GetPosition();
    BOOST_CHECK(uCurrentPointer < uOriginalPointer);
}

/// <summary>
/// Checks that the internal pointer is not moved when the amount of movement is zero.
/// </summary>
ZTEST_CASE ( MoveBackward_PointerIsNotMovedWhenMovementIsZero_Test )
{
    // [Preparation]
    const u64_z NEW_CONTENT = 0x0102030405060708;
    const puint_z MOVEMENT = 0;
    const puint_z BUFFER_SIZE = sizeof(NEW_CONTENT);

    MemoryStream<> stream(&NEW_CONTENT, BUFFER_SIZE);
    stream.SetPosition(1);
    puint_z uOriginalPointer = stream.GetPosition();

    // [Execution]
    stream.MoveBackward(MOVEMENT);
    
    // [Verification]
    puint_z uCurrentPointer = stream.GetPosition();
    BOOST_CHECK_EQUAL(uCurrentPointer, uOriginalPointer);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the internal pointer points to the first position of the buffer.
/// </summary>
ZTEST_CASE ( MoveBackward_AssertionFailsWhenPointerPointsToFirstPosition_Test )
{
    // [Preparation]
    const u64_z NEW_CONTENT = 0x0102030405060708;
    const puint_z MOVEMENT = 1U;
    const puint_z BUFFER_SIZE = sizeof(NEW_CONTENT);
    const bool ASSERTION_FAILED = true;

    MemoryStream<> stream(&NEW_CONTENT, BUFFER_SIZE);

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        stream.MoveBackward(MOVEMENT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that the pointer does not moves when it points to the first position of the buffer.
/// </summary>
ZTEST_CASE ( MoveBackward_PointerIsNotMovedWhenPointerPointsToFirstPosition_Test )
{
    // [Preparation]
    const u64_z NEW_CONTENT = 0x0102030405060708;
    const puint_z MOVEMENT = 1U;
    const puint_z BUFFER_SIZE = sizeof(NEW_CONTENT);

    MemoryStream<> stream(&NEW_CONTENT, BUFFER_SIZE);
    puint_z uOriginalPointer = stream.GetPosition();

    // [Execution]
    stream.MoveBackward(MOVEMENT);
    
    // [Verification]
    puint_z uCurrentPointer = stream.GetPosition();
    BOOST_CHECK_EQUAL(uCurrentPointer, uOriginalPointer);
}

#endif

/// <summary>
/// Checks that the internal pointer is correctly moved.
/// </summary>
ZTEST_CASE ( MoveForward_PointerIsCorrectlyMoved_Test )
{
    // [Preparation]
    const u64_z NEW_CONTENT = 0x0102030405060708;
    const puint_z MOVEMENT = 1U;
    const puint_z BUFFER_SIZE = sizeof(NEW_CONTENT);

    MemoryStream<> stream(&NEW_CONTENT, BUFFER_SIZE);
    puint_z uOriginalPointer = stream.GetPosition();

    // [Execution]
    stream.MoveForward(MOVEMENT);
    
    // [Verification]
    puint_z uCurrentPointer = stream.GetPosition();
    BOOST_CHECK(uCurrentPointer > uOriginalPointer);
}

/// <summary>
/// Checks that the internal pointer is not moved when the amount of movement is zero.
/// </summary>
ZTEST_CASE ( MoveForward_PointerIsNotMovedWhenMovementIsZero_Test )
{
    // [Preparation]
    const u64_z NEW_CONTENT = 0x0102030405060708;
    const puint_z MOVEMENT = 0;
    const puint_z BUFFER_SIZE = sizeof(NEW_CONTENT);

    MemoryStream<> stream(&NEW_CONTENT, BUFFER_SIZE);
    puint_z uOriginalPointer = stream.GetPosition();

    // [Execution]
    stream.MoveForward(MOVEMENT);
    
    // [Verification]
    puint_z uCurrentPointer = stream.GetPosition();
    BOOST_CHECK_EQUAL(uCurrentPointer, uOriginalPointer);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the internal pointer points outside of the buffer.
/// </summary>
ZTEST_CASE ( MoveForward_AssertionFailsWhenPointerPointsOutsideOfTheBuffer_Test )
{
    // [Preparation]
    const u64_z NEW_CONTENT = 0x0102030405060708;
    const puint_z MOVEMENT = 1U;
    const puint_z BUFFER_SIZE = sizeof(NEW_CONTENT);
    const bool ASSERTION_FAILED = true;

    MemoryStream<> stream(&NEW_CONTENT, BUFFER_SIZE);
    stream.SetPosition(sizeof(NEW_CONTENT));

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        stream.MoveForward(MOVEMENT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that the pointer does not moves when the internal pointer points outside of the buffer.
/// </summary>
ZTEST_CASE ( MoveForward_PointerIsNotMovedWhenPointerPointsOutsideOfTheBuffer_Test )
{
    // [Preparation]
    const u64_z NEW_CONTENT = 0x0102030405060708;
    const puint_z MOVEMENT = 1U;
    const puint_z BUFFER_SIZE = sizeof(NEW_CONTENT);

    MemoryStream<> stream(&NEW_CONTENT, BUFFER_SIZE);
    stream.SetPosition(sizeof(NEW_CONTENT));
    puint_z uOriginalPointer = stream.GetPosition();

    // [Execution]
    stream.MoveForward(MOVEMENT);
    
    // [Verification]
    puint_z uCurrentPointer = stream.GetPosition();
    BOOST_CHECK_EQUAL(uCurrentPointer, uOriginalPointer);
}

#endif

/// <summary>
/// Checks that it returns zero when the stream is empty.
/// </summary>
ZTEST_CASE ( GetLength_ReturnsZeroWhenStreamIsEmpty_Test )
{
    // [Preparation]
    const puint_z EXPECTED_LENGTH = 0;
    MemoryStream<> stream(4U);

    // [Execution]
    puint_z uLength = stream.GetLength();
    
    // [Verification]
    BOOST_CHECK_EQUAL(uLength, EXPECTED_LENGTH);
}

/// <summary>
/// Checks that it returns expected length when the stream is not empty.
/// </summary>
ZTEST_CASE ( GetLength_ReturnsExpectedLengthWhenStreamIsNotEmpty_Test )
{
    // [Preparation]
    const puint_z EXPECTED_LENGTH = 4U;
    const u32_z CONTENT = 0;
    MemoryStream<> stream(&CONTENT, EXPECTED_LENGTH);

    // [Execution]
    puint_z uLength = stream.GetLength();
    
    // [Verification]
    BOOST_CHECK_EQUAL(uLength, EXPECTED_LENGTH);
}

/// <summary>
/// It is not necessary to test this method since it is just a getter.
/// </summary>
ZTEST_CASE ( GetPosition_NotNecessaryToTest_Test )
{
    BOOST_TEST_MESSAGE("It is not necessary to test this method since it is just a getter");
}

/// <summary>
/// Checks that the internal pointer is correctly moved to the given position.
/// </summary>
ZTEST_CASE ( SetPosition_ThePointerIsCorrectlyMovedToTheGivenPosition_Test )
{
    // [Preparation]
    const puint_z EXPECTED_POSITION = 4U;
    const u32_z CONTENT = 0;
    MemoryStream<> stream(&CONTENT, sizeof(CONTENT));

    // [Execution]
    stream.SetPosition(EXPECTED_POSITION);
    
    // [Verification]
    puint_z uPosition = stream.GetPosition();
    BOOST_CHECK_EQUAL(uPosition, EXPECTED_POSITION);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the internal pointer is not moved when the input position is out of bounds.
/// </summary>
ZTEST_CASE ( SetPosition_AssertionFailsWhenTheInputPositionIsOutOfBounds_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const puint_z NEW_POSITION = 5U;
    const u32_z CONTENT = 0;
    MemoryStream<> stream(&CONTENT, sizeof(CONTENT));

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        stream.SetPosition(NEW_POSITION);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }
    
    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that the internal pointer is not moved when the input position is out of bounds.
/// </summary>
ZTEST_CASE ( SetPosition_ThePointerIsNotMovedWhenTheInputPositionIsOutOfBounds_Test )
{
    // [Preparation]
    const puint_z ORIGINAL_POSITION = 0;
    const puint_z NEW_POSITION = 5U;
    const u32_z CONTENT = 0;
    MemoryStream<> stream(&CONTENT, sizeof(CONTENT));

    // [Execution]
    stream.SetPosition(NEW_POSITION);
    
    // [Verification]
    puint_z uPosition = stream.GetPosition();
    BOOST_CHECK_EQUAL(uPosition, ORIGINAL_POSITION);
}

#endif

/// <summary>
/// Checks that the returned address depends on the position of the internal pointer.
/// </summary>
ZTEST_CASE ( GetCurrentPointer_ReturnedAddressDespendsOnInternalPointerPosition_Test )
{
    // [Preparation]
    const puint_z POSITION = 4U;
    const u32_z CONTENT = 0;
    MemoryStream<> stream(&CONTENT, sizeof(CONTENT));
    void* pOriginalPointer = stream.GetCurrentPointer();
    stream.SetPosition(POSITION);

    // [Execution]
    void* pCurrentPointer = stream.GetCurrentPointer();
    
    // [Verification]
    puint_z uOriginalPosition = rcast_z(pOriginalPointer, puint_z);
    puint_z uCurrentPosition = rcast_z(pCurrentPointer, puint_z);
    puint_z uActualPosition = uCurrentPosition - uOriginalPosition;
    BOOST_CHECK_EQUAL(uActualPosition, POSITION);
}

// End - Test Suite: MemoryStream
ZTEST_SUITE_END()
