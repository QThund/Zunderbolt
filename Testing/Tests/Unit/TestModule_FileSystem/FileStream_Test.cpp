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

// Note: In these unit tests we are no fulfilling the principle of reproducibility. We are running out of time at the moment.
// Note2: These unit tests make use of some artifacts located at /testing/bin/artifacts/artifacts/FileStream/ (copied to the cwd before execution).

#include <boost/test/auto_unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
using namespace boost::unit_test;

#include "../../testsystem/TestingExternalDefinitions.h"

#include "ZFileSystem/FileStream.h"

#include "ZFileSystem/Path.h"
#include "ZCommon/DataTypes/ArrayResult.h"
#include "ZCommon/DataTypes/ETextEncoding.h"
#include "ZFileSystem/SFile.h"
#include "FileStreamWhiteBox.h"
#include "ZCommon/Exceptions/AssertException.h"

// The base path to all the artifacts used by these tests
static const string_z PATH_TO_ARTIFACTS("./artifacts/FileStream/");

// Compares 2 sequence of bytes, one by one and returns the result, True if they are exactly equal
bool CompareByteSequence_TestHelper(const char* arBytes1, const char* arBytes2, const puint_z uBytesToCompare)
{
    bool bResult = true;

    for(puint_z i = 0; i < uBytesToCompare && bResult; ++i)
        bResult = bResult && arBytes1[i] == arBytes2[i];

    return bResult;
}

using z::Test::FileStreamWhiteBox;


ZTEST_SUITE_BEGIN( FileStream_TestSuite )

/// <summary>
/// Checks that the instance is initialized as expected.
/// </summary>
ZTEST_CASE ( Constructor1_InstanceIsInitializedAsExpected_Test )
{
    // [Preparation]
    const puint_z INITIAL_CAPACITY = 4U;
    const Path EXPECTED_PATH(string_z::GetEmpty());
    const puint_z EXPECTED_POSITION = 0;
    const bool EXPECTED_OPEN_STATUS = false;

    // [Execution]
    FileStream stream(INITIAL_CAPACITY);

    // [Verification]
    BOOST_CHECK_EQUAL(stream.GetPosition(), EXPECTED_POSITION);
    BOOST_CHECK_EQUAL(stream.IsOpen(), EXPECTED_OPEN_STATUS);
    BOOST_CHECK(stream.GetPath() == EXPECTED_PATH);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the initial capacity is zero.
/// </summary>
ZTEST_CASE ( Constructor1_AssertionFailsWhenInitialCapacityIsZero_Test )
{
    // [Preparation]
    const puint_z INITIAL_CAPACITY = 0;
    bool bAssertionFailed = false;

    // [Execution]
    try
    {
        FileStream stream(INITIAL_CAPACITY);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#elif Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that the length of the stream is initialized as expected.
/// </summary>
ZTEST_CASE ( Constructor1_LengthIsInitializedAsExpected_Test )
{
    // Note: This test is placed here to avoid a failing assertion of GetLength

    // [Preparation]
    const puint_z INITIAL_CAPACITY = 4U;
    const puint_z EXPECTED_LENGTH = 0;;

    // [Execution]
    FileStream stream(INITIAL_CAPACITY);

    // [Verification]
    BOOST_CHECK_EQUAL(stream.GetLength(), EXPECTED_LENGTH);
}

#endif

/// <summary>
/// Checks that it returns Success when the file exists and the open mode is Append.
/// </summary>
ZTEST_CASE ( Constructor2_ReturnsSuccessWhenFileExistsAndOpenModeIsAppend_Test )
{
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const puint_z INITIAL_CAPACITY = 4U;
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Append;
    const EFileSystemError EXPECTED_RESULT = EFileSystemError::E_Success;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;

    // [Execution]
    FileStream stream(INPUT_PATH, OPEN_MODE, INITIAL_CAPACITY, errorInfo);

    // [Verification]
    BOOST_CHECK(errorInfo == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns Success when the file exists and the open mode is Open.
/// </summary>
ZTEST_CASE ( Constructor2_ReturnsSuccessWhenFileExistsAndOpenModeIsOpen_Test )
{
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const puint_z INITIAL_CAPACITY = 4U;
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Open;
    const EFileSystemError EXPECTED_RESULT = EFileSystemError::E_Success;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;

    // [Execution]
    FileStream stream(INPUT_PATH, OPEN_MODE, INITIAL_CAPACITY, errorInfo);

    // [Verification]
    BOOST_CHECK(errorInfo == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns Success when the file exists and the open mode is CreateOrOverwrite.
/// </summary>
ZTEST_CASE ( Constructor2_ReturnsSuccessWhenFileExistsAndOpenModeIsCreateOrOverwrite_Test )
{
    // Assuming the existence of:
    // -./FileToReplace.txt

    // [Preparation]
    const puint_z INITIAL_CAPACITY = 4U;
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./FileToReplace.txt");
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_CreateOrOverwrite;
    const EFileSystemError EXPECTED_RESULT = EFileSystemError::E_Success;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;

    // [Execution]
    FileStream stream(INPUT_PATH, OPEN_MODE, INITIAL_CAPACITY, errorInfo);

    // [Verification]
    BOOST_CHECK(errorInfo == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns Success when the file exists and the open mode is OpenOrCreate.
/// </summary>
ZTEST_CASE ( Constructor2_ReturnsSuccessWhenFileExistsAndOpenModeIsOpenOrCreate_Test )
{
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const puint_z INITIAL_CAPACITY = 4U;
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_OpenOrCreate;
    const EFileSystemError EXPECTED_RESULT = EFileSystemError::E_Success;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;

    // [Execution]
    FileStream stream(INPUT_PATH, OPEN_MODE, INITIAL_CAPACITY, errorInfo);

    // [Verification]
    BOOST_CHECK(errorInfo == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns DoesNotExist when the file does not exist and the open mode is Append.
/// </summary>
ZTEST_CASE ( Constructor2_ReturnsDoesNotExistWhenFileDoesNotExistAndOpenModeIsAppend_Test )
{
    // [Preparation]
    const puint_z INITIAL_CAPACITY = 4U;
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./NonexistentFile.txt");
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Append;
    const EFileSystemError EXPECTED_RESULT = EFileSystemError::E_DoesNotExist;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;

    // [Execution]
    FileStream stream(INPUT_PATH, OPEN_MODE, INITIAL_CAPACITY, errorInfo);

    // [Verification]
    BOOST_CHECK(errorInfo == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns DoesNotExist when the file does not exist and the open mode is Open.
/// </summary>
ZTEST_CASE ( Constructor2_ReturnsDoesNotExistWhenFileDoesNotExistAndOpenModeIsOpen_Test )
{
    // [Preparation]
    const puint_z INITIAL_CAPACITY = 4U;
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./NonexistentFile.txt");
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Open;
    const EFileSystemError EXPECTED_RESULT = EFileSystemError::E_DoesNotExist;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;

    // [Execution]
    FileStream stream(INPUT_PATH, OPEN_MODE, INITIAL_CAPACITY, errorInfo);

    // [Verification]
    BOOST_CHECK(errorInfo == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns Success when the file does not exist and the open mode is Create.
/// </summary>
ZTEST_CASE ( Constructor2_ReturnsSuccessWhenFileDoesNotExistAndOpenModeIsCreate_Test )
{
    // [Preparation]
    const puint_z INITIAL_CAPACITY = 4U;
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./NewFile.txt");
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Create;
    const EFileSystemError EXPECTED_RESULT = EFileSystemError::E_Success;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;

    // [Execution]
    FileStream stream(INPUT_PATH, OPEN_MODE, INITIAL_CAPACITY, errorInfo);

    // [Verification]
    BOOST_CHECK(errorInfo == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns AlreadyExists when the file exists and the open mode is Create.
/// </summary>
ZTEST_CASE ( Constructor2_ReturnsAlreadyExistsWhenFileExistsAndOpenModeIsCreate_Test )
{
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const puint_z INITIAL_CAPACITY = 4U;
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Create;
    const EFileSystemError EXPECTED_RESULT = EFileSystemError::E_AlreadyExists;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;

    // [Execution]
    FileStream stream(INPUT_PATH, OPEN_MODE, INITIAL_CAPACITY, errorInfo);

    // [Verification]
    BOOST_CHECK(errorInfo == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns Success when the file does not exist and the open mode is CreateOrOverwrite.
/// </summary>
ZTEST_CASE ( Constructor2_ReturnsSuccessWhenFileDoesNotExistAndOpenModeIsCreateOrOverwrite_Test )
{
    // [Preparation]
    const puint_z INITIAL_CAPACITY = 4U;
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./NewFile2.txt");
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_CreateOrOverwrite;
    const EFileSystemError EXPECTED_RESULT = EFileSystemError::E_Success;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;

    // [Execution]
    FileStream stream(INPUT_PATH, OPEN_MODE, INITIAL_CAPACITY, errorInfo);

    // [Verification]
    BOOST_CHECK(errorInfo == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns Success when the file does not exist and the open mode is OpenOrCreate.
/// </summary>
ZTEST_CASE ( Constructor2_ReturnsSuccessWhenFileDoesNotExistAndOpenModeIsOpenOrCreate_Test )
{
    // [Preparation]
    const puint_z INITIAL_CAPACITY = 4U;
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./NewFile3.txt");
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_OpenOrCreate;
    const EFileSystemError EXPECTED_RESULT = EFileSystemError::E_Success;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;

    // [Execution]
    FileStream stream(INPUT_PATH, OPEN_MODE, INITIAL_CAPACITY, errorInfo);

    // [Verification]
    BOOST_CHECK(errorInfo == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the position is set to the end when the open mode is Append.
/// </summary>
ZTEST_CASE ( Constructor2_PositionIsSetAtTheEndWhenOpenModeIsAppend_Test )
{
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const puint_z INITIAL_CAPACITY = 4U;
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Append;
    const puint_z EXPECTED_POSITION = 4U;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;

    // [Execution]
    FileStream stream(INPUT_PATH, OPEN_MODE, INITIAL_CAPACITY, errorInfo);

    // [Verification]
    BOOST_CHECK_EQUAL(stream.GetPosition(), EXPECTED_POSITION);
}

/// <summary>
/// Checks that the position is set to zero when the open mode is Open.
/// </summary>
ZTEST_CASE ( Constructor2_PositionIsSetAtZeroWhenOpenModeIsOpen_Test )
{
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const puint_z INITIAL_CAPACITY = 4U;
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Open;
    const puint_z EXPECTED_POSITION = 0;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;

    // [Execution]
    FileStream stream(INPUT_PATH, OPEN_MODE, INITIAL_CAPACITY, errorInfo);

    // [Verification]
    BOOST_CHECK_EQUAL(stream.GetPosition(), EXPECTED_POSITION);
}

/// <summary>
/// Checks that the position is set to zero when the open mode is CreateOrOverwrite.
/// </summary>
ZTEST_CASE ( Constructor2_PositionIsSetAtZeroWhenOpenModeIsCreateOrOverwrite_Test )
{
    // Assuming the existence of:
    // -./FileToReplace.txt
    
    // [Preparation]
    const puint_z INITIAL_CAPACITY = 4U;
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./FileToReplace.txt");
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_CreateOrOverwrite;
    const puint_z EXPECTED_POSITION = 0;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;

    // [Execution]
    FileStream stream(INPUT_PATH, OPEN_MODE, INITIAL_CAPACITY, errorInfo);

    // [Verification]
    BOOST_CHECK_EQUAL(stream.GetPosition(), EXPECTED_POSITION);
}

/// <summary>
/// Checks that the position is set to zero when the open mode is OpenOrCreate.
/// </summary>
ZTEST_CASE ( Constructor2_PositionIsSetAtZeroWhenOpenModeIsOpenOrCreate_Test )
{
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const puint_z INITIAL_CAPACITY = 4U;
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_OpenOrCreate;
    const puint_z EXPECTED_POSITION = 0;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;

    // [Execution]
    FileStream stream(INPUT_PATH, OPEN_MODE, INITIAL_CAPACITY, errorInfo);

    // [Verification]
    BOOST_CHECK_EQUAL(stream.GetPosition(), EXPECTED_POSITION);
}

/// <summary>
/// Checks that the position is set to zero when the open mode is Create.
/// </summary>
ZTEST_CASE ( Constructor2_PositionIsSetAtZeroWhenOpenModeIsCreate_Test )
{
    // [Preparation]
    const puint_z INITIAL_CAPACITY = 4U;
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./NewFile4.txt");
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Create;
    const puint_z EXPECTED_POSITION = 0;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;

    // [Execution]
    FileStream stream(INPUT_PATH, OPEN_MODE, INITIAL_CAPACITY, errorInfo);

    // [Verification]
    BOOST_CHECK_EQUAL(stream.GetPosition(), EXPECTED_POSITION);
}

/// <summary>
/// Checks that the file is overwritten when the open mode is CreateOrOverwrite.
/// </summary>
ZTEST_CASE ( Constructor2_FileIsOverwrittenWhenOpenModeIsCreateOrOverwrite_Test )
{
    // Assuming the existence of:
    // -./FileToReplace2.txt (with a size > 0)
    
    // [Preparation]
    const puint_z INITIAL_CAPACITY = 4U;
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./FileToReplace2.txt");
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_CreateOrOverwrite;
    const puint_z EXPECTED_SIZE = 0;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;

    // [Execution]
    FileStream stream(INPUT_PATH, OPEN_MODE, INITIAL_CAPACITY, errorInfo);

    // [Verification]
    FileInfo fileInfo = SFile::GetFileInfo(Path(INPUT_PATH), errorInfo);
    BOOST_CHECK_EQUAL(fileInfo.GetSize(), EXPECTED_SIZE);
}

/// <summary>
/// Checks that the length of the steam is the size of the opened file.
/// </summary>
ZTEST_CASE ( Constructor2_LengthOfStreamIsFileSize_Test )
{
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const puint_z INITIAL_CAPACITY = 1U;
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Open;
    const puint_z EXPECTED_LENGTH = 4U;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;

    // [Execution]
    FileStream stream(INPUT_PATH, OPEN_MODE, INITIAL_CAPACITY, errorInfo);

    // [Verification]
    BOOST_CHECK_EQUAL(stream.GetLength(), EXPECTED_LENGTH);
}

/// <summary>
/// Checks that the path of the file is stored.
/// </summary>
ZTEST_CASE ( Constructor2_PathIsStored_Test )
{
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const puint_z INITIAL_CAPACITY = 1U;
    const Path EXPECTED_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Open;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;

    // [Execution]
    FileStream stream(EXPECTED_PATH, OPEN_MODE, INITIAL_CAPACITY, errorInfo);

    // [Verification]
    BOOST_CHECK(stream.GetPath() == EXPECTED_PATH);
}

/// <summary>
/// Checks that the IsOpen property returns True when the file is open.
/// </summary>
ZTEST_CASE ( Constructor2_IsOpenReturnsTrueWhenFileIsOpen_Test )
{
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const puint_z INITIAL_CAPACITY = 1U;
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Open;
    const bool EXPECTED_OPEN_STATUS = true;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;

    // [Execution]
    FileStream stream(INPUT_PATH, OPEN_MODE, INITIAL_CAPACITY, errorInfo);

    // [Verification]
    BOOST_CHECK_EQUAL(stream.IsOpen(), EXPECTED_OPEN_STATUS);
}

/// <summary>
/// Checks that the IsOpen property returns False when the file is not open.
/// </summary>
ZTEST_CASE ( Constructor2_IsOpenReturnsFalseWhenFileIsNotOpen_Test )
{
    // [Preparation]
    const puint_z INITIAL_CAPACITY = 1U;
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./NonexistingFile.txt");
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Open;
    const bool EXPECTED_OPEN_STATUS = false;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;

    // [Execution]
    FileStream stream(INPUT_PATH, OPEN_MODE, INITIAL_CAPACITY, errorInfo);

    // [Verification]
    BOOST_CHECK_EQUAL(stream.IsOpen(), EXPECTED_OPEN_STATUS);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the initial capacity is zero.
/// </summary>
ZTEST_CASE ( Constructor2_AssertionFailsWhenInitialCapacityIsZero_Test )
{
    // [Preparation]
    const puint_z INITIAL_CAPACITY = 0;
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Open;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;

    bool bAssertionFailed = false;

    // [Execution]
    try
    {
        FileStream stream(INPUT_PATH, OPEN_MODE, INITIAL_CAPACITY, errorInfo);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif

/// <summary>
/// Checks that the stream is flushed before it is destroyed.
/// </summary>
ZTEST_CASE ( Destructor_StreamIsFlushedBeforeDestroyed_Test )
{
    // [Preparation]
    const puint_z INITIAL_CAPACITY = 4U;
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./FlushedStream.txt");
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_CreateOrOverwrite;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;

    {
        FileStream stream(INPUT_PATH, OPEN_MODE, INITIAL_CAPACITY, errorInfo);
        stream.Write("ABCD", 0, 4U);

    // [Execution]
    } // Destructor called

    // [Verification]
    FileInfo fileInfo = SFile::GetFileInfo(Path(INPUT_PATH), errorInfo);
    bool bStreamWasFlushed = fileInfo.GetSize() > 0;
    BOOST_CHECK(bStreamWasFlushed);
}

/// <summary>
/// Checks that no error occurs when the stream is destroyed after it has been closed.
/// </summary>
ZTEST_CASE ( Destructor_StreamIsDestroyedWithoutErrorsWhenItWasAlreadyClosed_Test )
{
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const puint_z INITIAL_CAPACITY = 4U;
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Open;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;

    {
        FileStream stream(INPUT_PATH, OPEN_MODE, INITIAL_CAPACITY, errorInfo);
        stream.Close();

    // [Execution]
    } // Destructor called

    // [Verification]
    BOOST_CHECK(true);
}

/// <summary>
/// Checks that output offset affects the result.
/// </summary>
ZTEST_CASE ( Read_OutputOffsetAffectsTheResult_Test )
{
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const puint_z OFFSET1 = 1U;
    const puint_z OFFSET2 = 2U;
    const char EXPECTED_CONTENT_OFFSET1[] = {0, 'A', 'B', 0};
    const char EXPECTED_CONTENT_OFFSET2[] = {0, 0, 'A', 'B'};
    const puint_z READ_BLOCK_SIZE = 2U;
    const puint_z BUFFER_SIZE = 4U;
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Open;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream stream(INPUT_PATH, OPEN_MODE, BUFFER_SIZE, errorInfo);

    // [Execution]
    char szContentOffset1[] = {0, 0, 0, 0};
    stream.Read(szContentOffset1, OFFSET1, READ_BLOCK_SIZE);

    char szContentOffset2[] = {0, 0, 0, 0};
    stream.SetPosition(0); // To read from the beginning again
    stream.Read(szContentOffset2, OFFSET2, READ_BLOCK_SIZE);
    
    // [Verification]
    bool bResultOffset1 = CompareByteSequence_TestHelper(szContentOffset1, EXPECTED_CONTENT_OFFSET1, 4U);
    bool bResultOffset2 = CompareByteSequence_TestHelper(szContentOffset2, EXPECTED_CONTENT_OFFSET2, 4U);
    BOOST_CHECK(bResultOffset1);
    BOOST_CHECK(bResultOffset2);
}

/// <summary>
/// Checks that the complete stream can be read.
/// </summary>
ZTEST_CASE ( Read_TheCompleteStreamCanBeRead_Test )
{
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const char EXPECTED_CONTENT[] = {'A', 'B', 'C', 'D'};
    const puint_z OFFSET = 0;
    const puint_z BUFFER_SIZE = 4U;
    const puint_z READ_BLOCK_SIZE = BUFFER_SIZE;
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Open;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream stream(INPUT_PATH, OPEN_MODE, BUFFER_SIZE, errorInfo);

    // [Execution]
    char szContent[4];
    stream.Read(szContent, OFFSET, READ_BLOCK_SIZE);

    // [Verification]
    bool bFullContentIsCorrectlyObtained = CompareByteSequence_TestHelper(szContent, EXPECTED_CONTENT, 4U);
    BOOST_CHECK(bFullContentIsCorrectlyObtained);
}

/// <summary>
/// Checks that the read pointer is moved forward after every read operation.
/// </summary>
ZTEST_CASE ( Read_InternalReadPointerIsMovedForwardAutomatically_Test )
{
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const char EXPECTED_CONTENT[] = {'A', 'B', 'C', 'D'};
    const puint_z OFFSET = 0;
    const puint_z BUFFER_SIZE = 4U;
    const puint_z READ_BLOCK_SIZE = 2U;
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Open;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream stream(INPUT_PATH, OPEN_MODE, BUFFER_SIZE, errorInfo);

    // [Execution]
    char szContent[] = {0, 0, 0, 0};
    stream.Read(szContent, OFFSET, READ_BLOCK_SIZE);
    stream.Read(szContent, OFFSET + READ_BLOCK_SIZE, READ_BLOCK_SIZE);

    // [Verification]
    bool bContentIsWhatExpected = CompareByteSequence_TestHelper(szContent, EXPECTED_CONTENT, 4U);
    BOOST_CHECK(bContentIsWhatExpected);
}

/// <summary>
/// Checks that the content of the stream is flushed when the new position is not contiguous.
/// </summary>
ZTEST_CASE ( Read_ContentIsFlushedWhenNewPositionIsNotContiguous_Test )
{
    // Assuming the existence of:
    // -./FileToRead.txt

    // [Preparation]
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./FileToRead.txt");
    char CONTENT_TO_READ[] = {0, 0, 0, 0};
    const char EXPECTED_CONTENT[] = {'1', '2', '3', '4'};
    const puint_z OFFSET = 0;
    const puint_z BUFFER_SIZE = 4U;
    const puint_z WRITE_BLOCK_SIZE = 4U;
    const puint_z READ_BLOCK_SIZE = 2U;
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Open;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream stream(INPUT_PATH, OPEN_MODE, BUFFER_SIZE, errorInfo);

    // [Execution]
    stream.Write(EXPECTED_CONTENT, OFFSET, WRITE_BLOCK_SIZE);
    stream.SetPosition(6U);
    stream.Read(CONTENT_TO_READ, OFFSET, READ_BLOCK_SIZE); // Calls Flush
    
    // [Verification]
    stream.SetPosition(0);
    stream.Read(CONTENT_TO_READ, OFFSET, WRITE_BLOCK_SIZE);
    bool bContentIsWhatExpected = CompareByteSequence_TestHelper(CONTENT_TO_READ, EXPECTED_CONTENT, WRITE_BLOCK_SIZE);
    BOOST_CHECK(bContentIsWhatExpected);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the output buffer is null.
/// </summary>
ZTEST_CASE ( Read_AssertionFailsWhenOutputBufferIsNull_Test )
{
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const puint_z BUFFER_SIZE = 4U;
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Open;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream stream(INPUT_PATH, OPEN_MODE, BUFFER_SIZE, errorInfo);

    const puint_z INPUT_SIZE = 4U;
    void* pBuffer = null_z;
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
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const puint_z BUFFER_SIZE = 4U;
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Open;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream stream(INPUT_PATH, OPEN_MODE, BUFFER_SIZE, errorInfo);

    const puint_z INPUT_SIZE = 0;
    char pBuffer[4];
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
/// Checks that an assertion fails when trying to read out of the buffer.
/// </summary>
ZTEST_CASE ( Read_AssertionFailsWhenTryingToReadOutOfBounds_Test )
{
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const puint_z BUFFER_SIZE = 4U;
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Open;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream stream(INPUT_PATH, OPEN_MODE, BUFFER_SIZE, errorInfo);
    stream.MoveForward(2U);

    const puint_z INPUT_SIZE = 4U;
    const puint_z OFFSET = 0;
    char pBuffer[4];
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

/// <summary>
/// Checks that an assertion fails when the file is closed.
/// </summary>
ZTEST_CASE ( Read_AssertionFailsWhenFileIsClosed_Test )
{
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const puint_z BUFFER_SIZE = 4U;
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Open;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream stream(INPUT_PATH, OPEN_MODE, BUFFER_SIZE, errorInfo);
    stream.Close();

    const puint_z INPUT_SIZE = 4U;
    const puint_z OFFSET = 0;
    char pBuffer[4];
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
    const Path INPUT_PATH1(PATH_TO_ARTIFACTS + "./WrittenFile1.txt");
    const Path INPUT_PATH2(PATH_TO_ARTIFACTS + "./WrittenFile2.txt");
    const char NEW_CONTENT[] = {'A', 'B', 'C', 'D'};
    const puint_z OFFSET1 = 1U;
    const puint_z OFFSET2 = 2U;
    const char EXPECTED_CONTENT_OFFSET1[] = {'B', 'C', 0, 0};
    const char EXPECTED_CONTENT_OFFSET2[] = {'C', 'D', 0, 0};
    const puint_z WRITE_BLOCK_SIZE = 2U;
    const puint_z BUFFER_SIZE = 4U;
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_CreateOrOverwrite;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream stream1(INPUT_PATH1, OPEN_MODE, BUFFER_SIZE, errorInfo);
    FileStream stream2(INPUT_PATH2, OPEN_MODE, BUFFER_SIZE, errorInfo);
    char szOriginalContent[] = {0, 0, 0, 0};
    stream1.Write(szOriginalContent, 0, BUFFER_SIZE);
    stream2.Write(szOriginalContent, 0, BUFFER_SIZE);
    stream1.SetPosition(0);
    stream2.SetPosition(0);

    // [Execution]
    stream1.Write(NEW_CONTENT, OFFSET1, WRITE_BLOCK_SIZE);
    stream2.Write(NEW_CONTENT, OFFSET2, WRITE_BLOCK_SIZE);
    
    // [Verification]
    char szContentOffset1[] = {0, 0, 0, 0};
    char szContentOffset2[] = {0, 0, 0, 0};
    stream1.SetPosition(0);
    stream2.SetPosition(0);
    stream1.Read(szContentOffset1, 0, BUFFER_SIZE);
    stream2.Read(szContentOffset2, 0, BUFFER_SIZE);
    bool bResultOffset1 = CompareByteSequence_TestHelper(szContentOffset1, EXPECTED_CONTENT_OFFSET1, 4U);
    bool bResultOffset2 = CompareByteSequence_TestHelper(szContentOffset2, EXPECTED_CONTENT_OFFSET2, 4U);
    BOOST_CHECK(bResultOffset1);
    BOOST_CHECK(bResultOffset2);
}

/// <summary>
/// Checks that it is possible to write blocks that are bigger than the buffer's size.
/// </summary>
ZTEST_CASE ( Write_ItIsPossibleToWriteABlockBiggerThanBufferSize_Test )
{
    // [Preparation]
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./WrittenFile.txt");
    const char NEW_CONTENT[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
    const puint_z OFFSET = 0;
    const puint_z BUFFER_SIZE = 4U;
    const puint_z WRITE_BLOCK_SIZE = sizeof(NEW_CONTENT);
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_CreateOrOverwrite;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream stream(INPUT_PATH, OPEN_MODE, BUFFER_SIZE, errorInfo);

    // [Execution]
    stream.Write(NEW_CONTENT, OFFSET, WRITE_BLOCK_SIZE);

    // [Verification]
    char szContent[] = {0, 0, 0, 0, 0, 0, 0, 0};
    stream.SetPosition(0);
    stream.Read(szContent, 0, sizeof(szContent));
    bool bFullContentIsCorrectlyObtained = CompareByteSequence_TestHelper(szContent, NEW_CONTENT, sizeof(NEW_CONTENT));
    BOOST_CHECK(bFullContentIsCorrectlyObtained);
}

/// <summary>
/// Checks that the buffer grows as more memory is necessary.
/// </summary>
ZTEST_CASE ( Write_TheBufferGrowsAsMoreMemoryIsNecessary_Test )
{
    // [Preparation]
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./WrittenFile.txt");
    const char CONTENT_TO_WRITE1[] = {'E', 'F', 'G', 'H'};
    const char CONTENT_TO_WRITE2[] = {'A', 'B', 'C', 'D'};
    const puint_z OFFSET = 0;
    const puint_z ORIGINAL_BUFFER_SIZE = sizeof(CONTENT_TO_WRITE1);
    const puint_z WRITE_BLOCK_SIZE = sizeof(CONTENT_TO_WRITE1);
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_CreateOrOverwrite;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream stream(INPUT_PATH, OPEN_MODE, ORIGINAL_BUFFER_SIZE, errorInfo);

    // [Execution]
    stream.Write(CONTENT_TO_WRITE1, OFFSET, WRITE_BLOCK_SIZE);
    stream.Write(CONTENT_TO_WRITE2, OFFSET, WRITE_BLOCK_SIZE);

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
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./WrittenFile.txt");
    const char CONTENT_TO_WRITE1[] = {'A', 'B', 'C', 'D'};
    const char CONTENT_TO_WRITE2[] = {'E', 'F', 'G', 'H'};
    const char EXPECTED_CONTENT[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
    const puint_z OFFSET = 0;
    const puint_z BUFFER_SIZE = sizeof(CONTENT_TO_WRITE1);
    const puint_z WRITE_BLOCK_SIZE = sizeof(CONTENT_TO_WRITE1);
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_CreateOrOverwrite;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream stream(INPUT_PATH, OPEN_MODE, BUFFER_SIZE, errorInfo);

    // [Execution]
    stream.Write(CONTENT_TO_WRITE1, OFFSET, WRITE_BLOCK_SIZE);
    stream.Write(CONTENT_TO_WRITE2, OFFSET, WRITE_BLOCK_SIZE);

    // [Verification]
    char szContent[] = {0, 0, 0, 0, 0, 0, 0, 0};
    stream.SetPosition(0);
    stream.Read(szContent, 0, sizeof(szContent));
    bool bFullContentIsCorrectlyObtained = CompareByteSequence_TestHelper(szContent, EXPECTED_CONTENT, sizeof(EXPECTED_CONTENT));
    BOOST_CHECK(bFullContentIsCorrectlyObtained);
}

/// <summary>
/// Checks that it works when writing twice the same part of the stream.
/// </summary>
ZTEST_CASE ( Write_ItWorksWhenWritingTwiceTheSamePartOfTheStream_Test )
{
    // [Preparation]
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./WrittenFile.txt");
    const char CONTENT_TO_WRITE1[] = {'A', 'B', 'C', 'D'};
    const char CONTENT_TO_WRITE2[] = {'E', 'F', 'G', 'H'};
    const char EXPECTED_CONTENT[] = {'A', 'B', 'E', 'F', 'G', 'H'};
    const puint_z OFFSET = 0;
    const puint_z BUFFER_SIZE = sizeof(CONTENT_TO_WRITE1);
    const puint_z WRITE_BLOCK_SIZE = sizeof(CONTENT_TO_WRITE1);
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_CreateOrOverwrite;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream stream(INPUT_PATH, OPEN_MODE, BUFFER_SIZE, errorInfo);

    // [Execution]
    stream.Write(CONTENT_TO_WRITE1, OFFSET, WRITE_BLOCK_SIZE);
    stream.SetPosition(2U);
    stream.Write(CONTENT_TO_WRITE2, OFFSET, WRITE_BLOCK_SIZE);

    // [Verification]
    char szContent[] = {0, 0, 0, 0, 0, 0};
    stream.SetPosition(0);
    stream.Read(szContent, 0, sizeof(szContent));
    bool bFullContentIsCorrectlyObtained = CompareByteSequence_TestHelper(szContent, EXPECTED_CONTENT, sizeof(EXPECTED_CONTENT));
    BOOST_CHECK(bFullContentIsCorrectlyObtained);

    puint_z uBufferLength = stream.GetLength();
    BOOST_CHECK(uBufferLength > BUFFER_SIZE);
}

/// <summary>
/// Checks that the content of the stream is flushed when the new position is not contiguous.
/// </summary>
ZTEST_CASE ( Write_ContentIsFlushedWhenNewPositionIsNotContiguous_Test )
{
    // Assuming the existence of:
    // -./FileToWrite.txt

    // [Preparation]
    const puint_z ORIGINAL_FILE_SIZE = 8U;
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./FileToWrite.txt");
    const char CONTENT_TO_WRITE[] = {'W', 'X', 'Y', 'Z'};
    const puint_z OFFSET = 0;
    const puint_z BUFFER_SIZE = 4U;
    const puint_z WRITE_BLOCK_SIZE = sizeof(CONTENT_TO_WRITE);
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Open;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream stream(INPUT_PATH, OPEN_MODE, BUFFER_SIZE, errorInfo);

    // [Execution]
    stream.SetPosition(6U);
    stream.Write(CONTENT_TO_WRITE, OFFSET, WRITE_BLOCK_SIZE);
    stream.SetPosition(0);
    stream.Write(CONTENT_TO_WRITE, OFFSET, WRITE_BLOCK_SIZE); // Calls Flush

    // [Verification]
    FileInfo fileInfo = SFile::GetFileInfo(Path(INPUT_PATH), errorInfo);
    bool bStreamWasFlushed = fileInfo.GetSize() > ORIGINAL_FILE_SIZE;
    BOOST_CHECK(bStreamWasFlushed);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input buffer is null.
/// </summary>
ZTEST_CASE ( Write_AssertionFailsWhenInputBufferIsNull_Test )
{
    // [Preparation]
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./WrittenFile.txt");
    const puint_z INPUT_SIZE = 4U;
    void* pBuffer = null_z;
    const puint_z BUFFER_SIZE = 4U;
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_CreateOrOverwrite;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream stream(INPUT_PATH, OPEN_MODE, BUFFER_SIZE, errorInfo);
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
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./WrittenFile.txt");
    const puint_z INPUT_SIZE = 0;
    u32_z nBuffer;
    const puint_z BUFFER_SIZE = 4U;
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_CreateOrOverwrite;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream stream(INPUT_PATH, OPEN_MODE, BUFFER_SIZE, errorInfo);
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

/// <summary>
/// Checks that an assertion fails when the file is closed.
/// </summary>
ZTEST_CASE ( Write_AssertionFailsWhenFileIsClosed_Test )
{
    // [Preparation]
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./WrittenFile.txt");
    const puint_z INPUT_SIZE = 4U;
    u32_z nBuffer;
    const puint_z BUFFER_SIZE = 4U;
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_CreateOrOverwrite;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream stream(INPUT_PATH, OPEN_MODE, BUFFER_SIZE, errorInfo);
    stream.Close();
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
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const puint_z BUFFER_SIZE = 4U;
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Open;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream sourceStream(INPUT_PATH, OPEN_MODE, BUFFER_SIZE, errorInfo);

    const Path INPUT_PATH2(PATH_TO_ARTIFACTS + "./WrittenFile1.txt");
    const Path INPUT_PATH3(PATH_TO_ARTIFACTS + "./WrittenFile2.txt");
    const EFileOpenMode OPEN_MODE2 = EFileOpenMode::E_CreateOrOverwrite;
    FileStream stream1(INPUT_PATH2, OPEN_MODE2, BUFFER_SIZE, errorInfo);
    FileStream stream2(INPUT_PATH3, OPEN_MODE2, BUFFER_SIZE, errorInfo);
    const char ORIGINAL_CONTENT[] = {0, 0, 0, 0};
    stream1.Write(ORIGINAL_CONTENT, 0, sizeof(ORIGINAL_CONTENT));
    stream2.Write(ORIGINAL_CONTENT, 0, sizeof(ORIGINAL_CONTENT));

    const puint_z DESTINATION_OFFSET = 0;
    const puint_z OFFSET1 = 1U;
    const puint_z OFFSET2 = 2U;
    const char EXPECTED_CONTENT_OFFSET1[] = {'B', 'C', 'D', 0};
    const char EXPECTED_CONTENT_OFFSET2[] = {'C', 'D', 0, 0};

    // [Execution]
    sourceStream.CopyTo(stream1, OFFSET1, DESTINATION_OFFSET, BUFFER_SIZE - OFFSET1);
    sourceStream.CopyTo(stream2, OFFSET2, DESTINATION_OFFSET, BUFFER_SIZE - OFFSET2);
    
    // [Verification]
    char szContentOffset1[] = {0, 0, 0, 0};
    char szContentOffset2[] = {0, 0, 0, 0};
    stream1.SetPosition(0);
    stream2.SetPosition(0);
    stream1.Read(szContentOffset1, 0, sizeof(szContentOffset1));
    stream2.Read(szContentOffset2, 0, sizeof(szContentOffset2));
    bool bResultOffset1 = CompareByteSequence_TestHelper(szContentOffset1, EXPECTED_CONTENT_OFFSET1, 4U);
    bool bResultOffset2 = CompareByteSequence_TestHelper(szContentOffset2, EXPECTED_CONTENT_OFFSET2, 4U);
    BOOST_CHECK(bResultOffset1);
    BOOST_CHECK(bResultOffset2);
}

/// <summary>
/// Checks that the destination stream's offset affects the result.
/// </summary>
ZTEST_CASE ( CopyTo_DestinationOffsetAffectsTheResult_Test )
{
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const puint_z BUFFER_SIZE = 4U;
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Open;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream sourceStream(INPUT_PATH, OPEN_MODE, BUFFER_SIZE, errorInfo);
    
    const Path INPUT_PATH2(PATH_TO_ARTIFACTS + "./WrittenFile1.txt");
    const Path INPUT_PATH3(PATH_TO_ARTIFACTS + "./WrittenFile2.txt");
    const EFileOpenMode OPEN_MODE2 = EFileOpenMode::E_CreateOrOverwrite;
    FileStream stream1(INPUT_PATH2, OPEN_MODE2, BUFFER_SIZE, errorInfo);
    FileStream stream2(INPUT_PATH3, OPEN_MODE2, BUFFER_SIZE, errorInfo);
    const char ORIGINAL_CONTENT[] = {0, 0, 0, 0};
    stream1.Write(ORIGINAL_CONTENT, 0, sizeof(ORIGINAL_CONTENT));
    stream2.Write(ORIGINAL_CONTENT, 0, sizeof(ORIGINAL_CONTENT));
    
    const puint_z SOURCE_OFFSET = 0;
    const puint_z OFFSET1 = 1U;
    const puint_z OFFSET2 = 2U;
    const char EXPECTED_CONTENT_OFFSET1[] = {0, 'A', 'B', 'C'};
    const char EXPECTED_CONTENT_OFFSET2[] = {0, 0, 'A', 'B'};

    // [Execution]
    sourceStream.CopyTo(stream1, SOURCE_OFFSET, OFFSET1, BUFFER_SIZE);
    sourceStream.CopyTo(stream2, SOURCE_OFFSET, OFFSET2, BUFFER_SIZE);
    
    // [Verification]
    char szContentOffset1[] = {0, 0, 0, 0};
    char szContentOffset2[] = {0, 0, 0, 0};
    stream1.SetPosition(0);
    stream2.SetPosition(0);
    stream1.Read(szContentOffset1, 0, sizeof(szContentOffset1));
    stream2.Read(szContentOffset2, 0, sizeof(szContentOffset2));
    bool bResultOffset1 = CompareByteSequence_TestHelper(szContentOffset1, EXPECTED_CONTENT_OFFSET1, 4U);
    bool bResultOffset2 = CompareByteSequence_TestHelper(szContentOffset2, EXPECTED_CONTENT_OFFSET2, 4U);
    BOOST_CHECK(bResultOffset1);
    BOOST_CHECK(bResultOffset2);
}

/// <summary>
/// Checks that streams can be completely copied.
/// </summary>
ZTEST_CASE ( CopyTo_StreamCanBeCompletelyCopied_Test )
{
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const puint_z BUFFER_SIZE = 4U;
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Open;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream sourceStream(INPUT_PATH, OPEN_MODE, BUFFER_SIZE, errorInfo);

    const Path INPUT_PATH2(PATH_TO_ARTIFACTS + "./WrittenFile.txt");
    const EFileOpenMode OPEN_MODE2 = EFileOpenMode::E_CreateOrOverwrite;
    FileStream stream(INPUT_PATH2, OPEN_MODE2, BUFFER_SIZE, errorInfo);
    const char ORIGINAL_CONTENT[] = {0, 0, 0, 0};
    stream.Write(ORIGINAL_CONTENT, 0, sizeof(ORIGINAL_CONTENT));

    const puint_z SOURCE_OFFSET = 0;
    const puint_z OFFSET = 0;
    const char EXPECTED_CONTENT_OFFSET[] = {'A', 'B', 'C', 'D'};

    // [Execution]
    sourceStream.CopyTo(stream, SOURCE_OFFSET, OFFSET, BUFFER_SIZE);
    
    // [Verification]
    char szContentOffset[] = {0, 0, 0, 0};
    stream.SetPosition(0);
    stream.Read(szContentOffset, 0, sizeof(szContentOffset));
    bool bResultOffset = CompareByteSequence_TestHelper(szContentOffset, EXPECTED_CONTENT_OFFSET, 4U);
    BOOST_CHECK(bResultOffset);
}

/// <summary>
/// Checks that streams can be completely copied when the batch size is smaller than the number of bytes to be copied.
/// </summary>
ZTEST_CASE ( CopyTo_StreamCanBeCompletelyCopiedWhenBatchSizeIsSmallerThanNumberOfBytesToCopy_Test )
{
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const puint_z BUFFER_SIZE = 4U;
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Open;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream sourceStream(INPUT_PATH, OPEN_MODE, BUFFER_SIZE, errorInfo);

    const Path INPUT_PATH2(PATH_TO_ARTIFACTS + "./WrittenFile.txt");
    const EFileOpenMode OPEN_MODE2 = EFileOpenMode::E_CreateOrOverwrite;
    FileStream stream(INPUT_PATH2, OPEN_MODE2, BUFFER_SIZE, errorInfo);
    const char ORIGINAL_CONTENT[] = {0, 0, 0, 0};
    stream.Write(ORIGINAL_CONTENT, 0, sizeof(ORIGINAL_CONTENT));

    const puint_z SOURCE_OFFSET = 0;
    const puint_z DESTINATION_OFFSET = 0;
    const puint_z NUMBER_OF_BYTES = 4U;
    const puint_z BATCH_SIZE = 3U;
    const char EXPECTED_CONTENT_OFFSET[] = {'A', 'B', 'C', 'D'};

    // [Execution]
    sourceStream.CopyTo(stream, SOURCE_OFFSET, DESTINATION_OFFSET, NUMBER_OF_BYTES, BATCH_SIZE);
    
    // [Verification]
    char szContentOffset[] = {0, 0, 0, 0};
    stream.SetPosition(0);
    stream.Read(szContentOffset, 0, sizeof(szContentOffset));
    bool bResultOffset = CompareByteSequence_TestHelper(szContentOffset, EXPECTED_CONTENT_OFFSET, 4U);
    BOOST_CHECK(bResultOffset);
}

/// <summary>
/// Checks that the destination stream grows when it is necessary.
/// </summary>
ZTEST_CASE ( CopyTo_DestinationStreamGrowsWhenNecessary_Test )
{
    // Assuming the existence of:
    // -./ExistingFile.txt
    // -./FileToWrite3.txt

    // [Preparation]
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const puint_z BUFFER_SIZE = 4U;
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Open;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream sourceStream(INPUT_PATH, OPEN_MODE, BUFFER_SIZE, errorInfo);

    const Path INPUT_PATH2(PATH_TO_ARTIFACTS + "./FileToWrite3.txt");
    FileStream stream(INPUT_PATH2, OPEN_MODE, BUFFER_SIZE, errorInfo);
    
    const puint_z SOURCE_OFFSET = 0;
    const puint_z DESTINATION_OFFSET = 3U;
    const puint_z DESTINATION_STREAM_LENGTH = 4U;

    // [Execution]
    sourceStream.CopyTo(stream, SOURCE_OFFSET, DESTINATION_OFFSET, BUFFER_SIZE);
    
    // [Verification]
    puint_z uDestinationLength = stream.GetLength();
    BOOST_CHECK(uDestinationLength > DESTINATION_STREAM_LENGTH);
}

/// <summary>
/// Checks that the internal pointer of the source stream is moved forward.
/// </summary>
ZTEST_CASE ( CopyTo_SourceStreamInternalPointerIsMovedForward_Test )
{
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const puint_z BUFFER_SIZE = 4U;
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Open;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream sourceStream(INPUT_PATH, OPEN_MODE, BUFFER_SIZE, errorInfo);

    const Path INPUT_PATH2(PATH_TO_ARTIFACTS + "./WrittenFile.txt");
    const EFileOpenMode OPEN_MODE2 = EFileOpenMode::E_CreateOrOverwrite;
    FileStream stream(INPUT_PATH2, OPEN_MODE2, BUFFER_SIZE, errorInfo);

    const puint_z SOURCE_OFFSET = 0;
    const puint_z DESTINATION_OFFSET = 0;
    const puint_z EXPECTED_POSITION = 4U;

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
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const puint_z BUFFER_SIZE = 4U;
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Open;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream sourceStream(INPUT_PATH, OPEN_MODE, BUFFER_SIZE, errorInfo);

    const Path INPUT_PATH2(PATH_TO_ARTIFACTS + "./WrittenFile.txt");
    const EFileOpenMode OPEN_MODE2 = EFileOpenMode::E_CreateOrOverwrite;
    FileStream stream(INPUT_PATH2, OPEN_MODE2, BUFFER_SIZE, errorInfo);

    const puint_z SOURCE_OFFSET = 0;
    const puint_z DESTINATION_OFFSET = 0;
    const puint_z EXPECTED_POSITION = 4U;

    // [Execution]
    sourceStream.CopyTo(stream, SOURCE_OFFSET, DESTINATION_OFFSET, BUFFER_SIZE);
    
    // [Verification]
    puint_z uPosition = stream.GetPosition();
    BOOST_CHECK_EQUAL(uPosition, EXPECTED_POSITION);
}

/// <summary>
/// Checks that the internal pointer of the source stream is moved to the source offset when the number of bytes to copy is zero.
/// </summary>
ZTEST_CASE ( CopyTo_SourceStreamInternalPointerIsMovedToOffsetWhenNumberOfBytesToCopyEqualsZero_Test )
{
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const puint_z BUFFER_SIZE = 4U;
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Open;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream sourceStream(INPUT_PATH, OPEN_MODE, BUFFER_SIZE, errorInfo);

    const Path INPUT_PATH2(PATH_TO_ARTIFACTS + "./WrittenFile.txt");
    const EFileOpenMode OPEN_MODE2 = EFileOpenMode::E_CreateOrOverwrite;
    FileStream stream(INPUT_PATH2, OPEN_MODE2, BUFFER_SIZE, errorInfo);

    const puint_z SOURCE_OFFSET = 2U;
    const puint_z DESTINATION_OFFSET = 0;
    const puint_z BYTES_TO_COPY = 0;
    const puint_z EXPECTED_POSITION = SOURCE_OFFSET;

    // [Execution]
    sourceStream.CopyTo(stream, SOURCE_OFFSET, DESTINATION_OFFSET, BYTES_TO_COPY);
    
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
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const puint_z BUFFER_SIZE = 4U;
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Open;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream sourceStream(INPUT_PATH, OPEN_MODE, BUFFER_SIZE, errorInfo);

    const Path INPUT_PATH2(PATH_TO_ARTIFACTS + "./WrittenFile.txt");
    const EFileOpenMode OPEN_MODE2 = EFileOpenMode::E_CreateOrOverwrite;
    FileStream destinationStream(INPUT_PATH2, OPEN_MODE2, BUFFER_SIZE, errorInfo);

    const puint_z SOURCE_OFFSET = 5U;
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
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const puint_z BUFFER_SIZE = 4U;
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Open;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream sourceStream(INPUT_PATH, OPEN_MODE, BUFFER_SIZE, errorInfo);

    const Path INPUT_PATH2(PATH_TO_ARTIFACTS + "./WrittenFile.txt");
    const EFileOpenMode OPEN_MODE2 = EFileOpenMode::E_CreateOrOverwrite;
    FileStream destinationStream(INPUT_PATH2, OPEN_MODE2, BUFFER_SIZE, errorInfo);

    const puint_z DESTINATION_OFFSET = 1U;
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
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const puint_z BUFFER_SIZE = 4U;
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Open;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream sourceStream(INPUT_PATH, OPEN_MODE, BUFFER_SIZE, errorInfo);

    const Path INPUT_PATH2(PATH_TO_ARTIFACTS + "./WrittenFile.txt");
    const EFileOpenMode OPEN_MODE2 = EFileOpenMode::E_CreateOrOverwrite;
    FileStream destinationStream(INPUT_PATH2, OPEN_MODE2, BUFFER_SIZE, errorInfo);

    const puint_z SOURCE_OFFSET = 2U;
    const puint_z DESTINATION_OFFSET = 0;
    const puint_z NUMBER_OF_BYTES = 3U;
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        sourceStream.CopyTo(destinationStream, SOURCE_OFFSET, DESTINATION_OFFSET, NUMBER_OF_BYTES);
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
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const puint_z BUFFER_SIZE = 4U;
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Open;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream sourceStream(INPUT_PATH, OPEN_MODE, BUFFER_SIZE, errorInfo);

    const Path INPUT_PATH2(PATH_TO_ARTIFACTS + "./WrittenFile.txt");
    const EFileOpenMode OPEN_MODE2 = EFileOpenMode::E_CreateOrOverwrite;
    FileStream destinationStream(INPUT_PATH2, OPEN_MODE2, BUFFER_SIZE, errorInfo);

    const puint_z SOURCE_OFFSET = 0;
    const puint_z DESTINATION_OFFSET = 0;
    const puint_z NUMBER_OF_BYTES = 4U;
    const puint_z BATCH_SIZE = 0;
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        sourceStream.CopyTo(destinationStream, SOURCE_OFFSET, DESTINATION_OFFSET, NUMBER_OF_BYTES, BATCH_SIZE);
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
/// Checks that the pending written bytes are sent to the file.
/// </summary>
ZTEST_CASE ( Flush_PendingWrittenBytesAreSentToFile_Test )
{
    // [Preparation]
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./WrittenFile.txt");
    const char CONTENT_TO_WRITE[] = {'A', 'B', 'C', 'D'};
    const puint_z OFFSET = 0;
    const puint_z BUFFER_SIZE = sizeof(CONTENT_TO_WRITE);
    const puint_z WRITE_BLOCK_SIZE = sizeof(CONTENT_TO_WRITE);
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_CreateOrOverwrite;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream stream(INPUT_PATH, OPEN_MODE, BUFFER_SIZE, errorInfo);
    stream.Write(CONTENT_TO_WRITE, OFFSET, WRITE_BLOCK_SIZE);

    // [Execution]
    stream.Flush();

    // [Verification]
    stream.Close();
    char szContent[] = {0, 0, 0, 0};
    FileStream stream2(INPUT_PATH, EFileOpenMode::E_Open, BUFFER_SIZE, errorInfo);
    stream2.Read(szContent, 0, sizeof(szContent));
    bool bFullContentWasCorrectlySent = CompareByteSequence_TestHelper(szContent, CONTENT_TO_WRITE, sizeof(CONTENT_TO_WRITE));
    BOOST_CHECK(bFullContentWasCorrectlySent);
}

/// <summary>
/// Checks that nothing happens when there are not pending bytes to send to the file.
/// </summary>
ZTEST_CASE ( Flush_NothingHappensWhenThereAreNotPendingBytesToSend_Test )
{
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const char EXPECTED_CONTENT[] = {'A', 'B', 'C', 'D'};
    const puint_z BUFFER_SIZE = sizeof(EXPECTED_CONTENT);
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Open;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream stream(INPUT_PATH, OPEN_MODE, BUFFER_SIZE, errorInfo);

    // [Execution]
    stream.Flush();

    // [Verification]
    stream.Close();
    char szContent[] = {0, 0, 0, 0};
    FileStream stream2(INPUT_PATH, EFileOpenMode::E_Open, BUFFER_SIZE, errorInfo);
    stream2.Read(szContent, 0, sizeof(szContent));
    bool bFullContentWasCorrectlySent = CompareByteSequence_TestHelper(szContent, EXPECTED_CONTENT, sizeof(EXPECTED_CONTENT));
    BOOST_CHECK(bFullContentWasCorrectlySent);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the file is closed.
/// </summary>
ZTEST_CASE ( Flush_AssertionFailsWhenFileIsClosed_Test )
{
    // [Preparation]
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./WrittenFile.txt");
    const puint_z BUFFER_SIZE = 4U;
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_CreateOrOverwrite;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream stream(INPUT_PATH, OPEN_MODE, BUFFER_SIZE, errorInfo);
    stream.Close();
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        stream.Flush();
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the file is read only.
/// </summary>
ZTEST_CASE ( Flush_AssertionFailsWhenFileIsReadOnly_Test )
{
    using ArrayResult;
    using ETextEncoding;
    using i8_z;
    using System::IO::FileSystem::Test::FileStreamWhiteBox;

    // [Preparation]
    const string_z INPUT_PATH(PATH_TO_ARTIFACTS + "./ReadOnly.txt");
    
    // Sets the file as read only
#if defined(Z_OS_LINUX) || defined(Z_OS_MAC)
    static const ETextEncoding PATH_ENCODING = ETextEncoding::E_UTF8;
#elif defined(Z_OS_WINDOWS)
    static const ETextEncoding PATH_ENCODING = string_z::GetLocalEncodingUTF16();
#endif

    ArrayResult<i8_z> arBytesFile = INPUT_PATH.ToBytes(PATH_ENCODING);
    boost::filesystem::path::value_type* szPath = (boost::filesystem::path::value_type*)arBytesFile.Get();
    boost::filesystem::path filePath(szPath);

    boost::system::error_code permissionsErrorCode;
    boost::filesystem::permissions(filePath, boost::filesystem::remove_perms | boost::filesystem::owner_write, permissionsErrorCode);

    const puint_z BUFFER_SIZE = 4U;
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Open;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    const bool ASSERTION_FAILED = true;
    
    const char CONTENT_TO_WRITE[] = {'A', 'B', 'C', 'D'};
    const puint_z OFFSET = 0;
    const puint_z WRITE_BLOCK_SIZE = sizeof(CONTENT_TO_WRITE);
    FileStreamWhiteBox stream(INPUT_PATH, OPEN_MODE, BUFFER_SIZE, errorInfo);
    stream.Write(CONTENT_TO_WRITE, OFFSET, WRITE_BLOCK_SIZE);

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        stream.SetPendingBytesFlagWhenDestroyed(false);
        stream.Flush();
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
/// Checks that the internal pointer is correctly moved.
/// </summary>
ZTEST_CASE ( MoveBackward_PointerIsCorrectlyMoved_Test )
{
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const puint_z MOVEMENT = 1U;

    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const puint_z BUFFER_SIZE = 4U;
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Open;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream stream(INPUT_PATH, OPEN_MODE, BUFFER_SIZE, errorInfo);
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
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const puint_z MOVEMENT = 0;

    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const puint_z BUFFER_SIZE = 4U;
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Open;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream stream(INPUT_PATH, OPEN_MODE, BUFFER_SIZE, errorInfo);
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
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const puint_z MOVEMENT = 1U;
    const bool ASSERTION_FAILED = true;

    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const puint_z BUFFER_SIZE = 4U;
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Open;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream stream(INPUT_PATH, OPEN_MODE, BUFFER_SIZE, errorInfo);

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
/// Checks that the pointer does not move when it points to the first position of the buffer.
/// </summary>
ZTEST_CASE ( MoveBackward_PointerIsNotMovedWhenPointerPointsToFirstPosition_Test )
{
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const puint_z MOVEMENT = 1U;

    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const puint_z BUFFER_SIZE = 4U;
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Open;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream stream(INPUT_PATH, OPEN_MODE, BUFFER_SIZE, errorInfo);
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
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const puint_z MOVEMENT = 1U;

    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const puint_z BUFFER_SIZE = 4U;
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Open;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream stream(INPUT_PATH, OPEN_MODE, BUFFER_SIZE, errorInfo);
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
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const puint_z MOVEMENT = 0;

    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const puint_z BUFFER_SIZE = 4U;
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Open;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream stream(INPUT_PATH, OPEN_MODE, BUFFER_SIZE, errorInfo);
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
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const puint_z BUFFER_SIZE = 6U;
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Open;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream stream(INPUT_PATH, OPEN_MODE, BUFFER_SIZE, errorInfo);
    const puint_z MOVEMENT = 1U;
    const bool ASSERTION_FAILED = true;

    stream.SetPosition(4U);

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
/// Checks that the pointer does not move when the internal pointer points outside of the buffer.
/// </summary>
ZTEST_CASE ( MoveForward_PointerIsNotMovedWhenPointerPointsOutsideOfTheBuffer_Test )
{
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const puint_z BUFFER_SIZE = 6U;
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Open;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream stream(INPUT_PATH, OPEN_MODE, BUFFER_SIZE, errorInfo);
    const puint_z MOVEMENT = 1U;

    stream.SetPosition(4U);
    puint_z uOriginalPointer = stream.GetPosition();

    // [Execution]
    stream.MoveForward(MOVEMENT);
    
    // [Verification]
    puint_z uCurrentPointer = stream.GetPosition();
    BOOST_CHECK_EQUAL(uCurrentPointer, uOriginalPointer);
}

#endif

/// <summary>
/// Checks that it returns Success when the file exists and the open mode is Append.
/// </summary>
ZTEST_CASE ( Open_ReturnsSuccessWhenFileExistsAndOpenModeIsAppend_Test )
{
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const puint_z INITIAL_CAPACITY = 4U;
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Append;
    const EFileSystemError EXPECTED_RESULT = EFileSystemError::E_Success;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream stream(INITIAL_CAPACITY);

    // [Execution]
    errorInfo = stream.Open(INPUT_PATH, OPEN_MODE);

    // [Verification]
    BOOST_CHECK(errorInfo == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns Success when the file exists and the open mode is Open.
/// </summary>
ZTEST_CASE ( Open_ReturnsSuccessWhenFileExistsAndOpenModeIsOpen_Test )
{
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const puint_z INITIAL_CAPACITY = 4U;
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Open;
    const EFileSystemError EXPECTED_RESULT = EFileSystemError::E_Success;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream stream(INITIAL_CAPACITY);

    // [Execution]
    errorInfo = stream.Open(INPUT_PATH, OPEN_MODE);

    // [Verification]
    BOOST_CHECK(errorInfo == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns Success when the file exists and the open mode is CreateOrOverwrite.
/// </summary>
ZTEST_CASE ( Open_ReturnsSuccessWhenFileExistsAndOpenModeIsCreateOrOverwrite_Test )
{
    // Assuming the existence of:
    // -./FileToReplace3.txt

    // [Preparation]
    const puint_z INITIAL_CAPACITY = 4U;
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./FileToReplace3.txt");
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_CreateOrOverwrite;
    const EFileSystemError EXPECTED_RESULT = EFileSystemError::E_Success;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream stream(INITIAL_CAPACITY);

    // [Execution]
    errorInfo = stream.Open(INPUT_PATH, OPEN_MODE);

    // [Verification]
    BOOST_CHECK(errorInfo == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns Success when the file exists and the open mode is OpenOrCreate.
/// </summary>
ZTEST_CASE ( Open_ReturnsSuccessWhenFileExistsAndOpenModeIsOpenOrCreate_Test )
{
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const puint_z INITIAL_CAPACITY = 4U;
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_OpenOrCreate;
    const EFileSystemError EXPECTED_RESULT = EFileSystemError::E_Success;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream stream(INITIAL_CAPACITY);

    // [Execution]
    errorInfo = stream.Open(INPUT_PATH, OPEN_MODE);

    // [Verification]
    BOOST_CHECK(errorInfo == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns DoesNotExist when the file does not exist and the open mode is Append.
/// </summary>
ZTEST_CASE ( Open_ReturnsDoesNotExistWhenFileDoesNotExistAndOpenModeIsAppend_Test )
{
    // [Preparation]
    const puint_z INITIAL_CAPACITY = 4U;
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./NonexistentFile.txt");
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Append;
    const EFileSystemError EXPECTED_RESULT = EFileSystemError::E_DoesNotExist;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream stream(INITIAL_CAPACITY);

    // [Execution]
    errorInfo = stream.Open(INPUT_PATH, OPEN_MODE);

    // [Verification]
    BOOST_CHECK(errorInfo == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns DoesNotExist when the file does not exist and the open mode is Open.
/// </summary>
ZTEST_CASE ( Open_ReturnsDoesNotExistWhenFileDoesNotExistAndOpenModeIsOpen_Test )
{
    // [Preparation]
    const puint_z INITIAL_CAPACITY = 4U;
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./NonexistentFile.txt");
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Open;
    const EFileSystemError EXPECTED_RESULT = EFileSystemError::E_DoesNotExist;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream stream(INITIAL_CAPACITY);

    // [Execution]
    errorInfo = stream.Open(INPUT_PATH, OPEN_MODE);

    // [Verification]
    BOOST_CHECK(errorInfo == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns Success when the file does not exist and the open mode is Create.
/// </summary>
ZTEST_CASE ( Open_ReturnsSuccessWhenFileDoesNotExistAndOpenModeIsCreate_Test )
{
    // [Preparation]
    const puint_z INITIAL_CAPACITY = 4U;
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./NewFile5.txt");
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Create;
    const EFileSystemError EXPECTED_RESULT = EFileSystemError::E_Success;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream stream(INITIAL_CAPACITY);

    // [Execution]
    errorInfo = stream.Open(INPUT_PATH, OPEN_MODE);

    // [Verification]
    BOOST_CHECK(errorInfo == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns AlreadyExists when the file exists and the open mode is Create.
/// </summary>
ZTEST_CASE ( Open_ReturnsAlreadyExistsWhenFileExistsAndOpenModeIsCreate_Test )
{
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const puint_z INITIAL_CAPACITY = 4U;
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Create;
    const EFileSystemError EXPECTED_RESULT = EFileSystemError::E_AlreadyExists;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream stream(INITIAL_CAPACITY);

    // [Execution]
    errorInfo = stream.Open(INPUT_PATH, OPEN_MODE);

    // [Verification]
    BOOST_CHECK(errorInfo == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns Success when the file does not exist and the open mode is CreateOrOverwrite.
/// </summary>
ZTEST_CASE ( Open_ReturnsSuccessWhenFileDoesNotExistAndOpenModeIsCreateOrOverwrite_Test )
{
    // [Preparation]
    const puint_z INITIAL_CAPACITY = 4U;
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./NewFile6.txt");
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_CreateOrOverwrite;
    const EFileSystemError EXPECTED_RESULT = EFileSystemError::E_Success;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream stream(INITIAL_CAPACITY);

    // [Execution]
    errorInfo = stream.Open(INPUT_PATH, OPEN_MODE);

    // [Verification]
    BOOST_CHECK(errorInfo == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns Success when the file does not exist and the open mode is OpenOrCreate.
/// </summary>
ZTEST_CASE ( Open_ReturnsSuccessWhenFileDoesNotExistAndOpenModeIsOpenOrCreate_Test )
{
    // [Preparation]
    const puint_z INITIAL_CAPACITY = 4U;
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./NewFile7.txt");
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_OpenOrCreate;
    const EFileSystemError EXPECTED_RESULT = EFileSystemError::E_Success;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream stream(INITIAL_CAPACITY);

    // [Execution]
    errorInfo = stream.Open(INPUT_PATH, OPEN_MODE);

    // [Verification]
    BOOST_CHECK(errorInfo == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the position is set to the end when the open mode is Append.
/// </summary>
ZTEST_CASE ( Open_PositionIsSetAtTheEndWhenOpenModeIsAppend_Test )
{
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const puint_z INITIAL_CAPACITY = 4U;
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Append;
    const puint_z EXPECTED_POSITION = 4U;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream stream(INITIAL_CAPACITY);

    // [Execution]
    errorInfo = stream.Open(INPUT_PATH, OPEN_MODE);

    // [Verification]
    BOOST_CHECK_EQUAL(stream.GetPosition(), EXPECTED_POSITION);
}

/// <summary>
/// Checks that the position is set to zero when the open mode is Open.
/// </summary>
ZTEST_CASE ( Open_PositionIsSetAtZeroWhenOpenModeIsOpen_Test )
{
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const puint_z INITIAL_CAPACITY = 4U;
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Open;
    const puint_z EXPECTED_POSITION = 0;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream stream(INITIAL_CAPACITY);

    // [Execution]
    errorInfo = stream.Open(INPUT_PATH, OPEN_MODE);

    // [Verification]
    BOOST_CHECK_EQUAL(stream.GetPosition(), EXPECTED_POSITION);
}

/// <summary>
/// Checks that the position is set to zero when the open mode is CreateOrOverwrite.
/// </summary>
ZTEST_CASE ( Open_PositionIsSetAtZeroWhenOpenModeIsCreateOrOverwrite_Test )
{
    // Assuming the existence of:
    // -./FileToReplace3.txt
    
    // [Preparation]
    const puint_z INITIAL_CAPACITY = 4U;
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./FileToReplace3.txt");
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_CreateOrOverwrite;
    const puint_z EXPECTED_POSITION = 0;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream stream(INITIAL_CAPACITY);

    // [Execution]
    errorInfo = stream.Open(INPUT_PATH, OPEN_MODE);

    // [Verification]
    BOOST_CHECK_EQUAL(stream.GetPosition(), EXPECTED_POSITION);
}

/// <summary>
/// Checks that the position is set to zero when the open mode is OpenOrCreate.
/// </summary>
ZTEST_CASE ( Open_PositionIsSetAtZeroWhenOpenModeIsOpenOrCreate_Test )
{
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const puint_z INITIAL_CAPACITY = 4U;
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_OpenOrCreate;
    const puint_z EXPECTED_POSITION = 0;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream stream(INITIAL_CAPACITY);

    // [Execution]
    errorInfo = stream.Open(INPUT_PATH, OPEN_MODE);

    // [Verification]
    BOOST_CHECK_EQUAL(stream.GetPosition(), EXPECTED_POSITION);
}

/// <summary>
/// Checks that the position is set to zero when the open mode is Create.
/// </summary>
ZTEST_CASE ( Open_PositionIsSetAtZeroWhenOpenModeIsCreate_Test )
{
    // [Preparation]
    const puint_z INITIAL_CAPACITY = 4U;
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./NewFile8.txt");
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Create;
    const puint_z EXPECTED_POSITION = 0;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream stream(INITIAL_CAPACITY);

    // [Execution]
    errorInfo = stream.Open(INPUT_PATH, OPEN_MODE);

    // [Verification]
    BOOST_CHECK_EQUAL(stream.GetPosition(), EXPECTED_POSITION);
}

/// <summary>
/// Checks that the file is overwritten when the open mode is CreateOrOverwrite.
/// </summary>
ZTEST_CASE ( Open_FileIsOverwrittenWhenOpenModeIsCreateOrOverwrite_Test )
{
    // Assuming the existence of:
    // -./FileToReplace4.txt (with a size > 0)
    
    // [Preparation]
    const puint_z INITIAL_CAPACITY = 4U;
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./FileToReplace4.txt");
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_CreateOrOverwrite;
    const puint_z EXPECTED_SIZE = 0;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream stream(INITIAL_CAPACITY);

    // [Execution]
    errorInfo = stream.Open(INPUT_PATH, OPEN_MODE);

    // [Verification]
    FileInfo fileInfo = SFile::GetFileInfo(Path(INPUT_PATH), errorInfo);
    BOOST_CHECK_EQUAL(fileInfo.GetSize(), EXPECTED_SIZE);
}

/// <summary>
/// Checks that the length of the steam is the size of the opened file.
/// </summary>
ZTEST_CASE ( Open_LengthOfStreamIsFileSize_Test )
{
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const puint_z INITIAL_CAPACITY = 1U;
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Open;
    const puint_z EXPECTED_LENGTH = 4U;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream stream(INITIAL_CAPACITY);

    // [Execution]
    errorInfo = stream.Open(INPUT_PATH, OPEN_MODE);

    // [Verification]
    BOOST_CHECK_EQUAL(stream.GetLength(), EXPECTED_LENGTH);
}

/// <summary>
/// Checks that it can be called again after the file is closed.
/// </summary>
ZTEST_CASE ( Open_ItCanBeCalledAgainAfterFileIsClosed_Test )
{
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const puint_z INITIAL_CAPACITY = 1U;
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Open;
    const EFileSystemError EXPECTED_RESULT = EFileSystemError::E_Success;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream stream(INPUT_PATH, OPEN_MODE, INITIAL_CAPACITY, errorInfo);
    stream.Close();

    // [Execution]
    errorInfo = stream.Open(INPUT_PATH, OPEN_MODE);

    // [Verification]
    BOOST_CHECK(errorInfo == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the path of the file is stored.
/// </summary>
ZTEST_CASE ( Open_PathIsStored_Test )
{
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const puint_z INITIAL_CAPACITY = 1U;
    const Path EXPECTED_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Open;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream stream(INITIAL_CAPACITY);

    // [Execution]
    errorInfo = stream.Open(EXPECTED_PATH, OPEN_MODE);

    // [Verification]
    BOOST_CHECK(stream.GetPath() == EXPECTED_PATH);
}

/// <summary>
/// Checks that the IsOpen property returns True when the file is open.
/// </summary>
ZTEST_CASE ( Open_IsOpenReturnsTrueWhenFileIsOpen_Test )
{
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const puint_z INITIAL_CAPACITY = 1U;
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Open;
    const bool EXPECTED_OPEN_STATUS = true;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream stream(INITIAL_CAPACITY);

    // [Execution]
    errorInfo = stream.Open(INPUT_PATH, OPEN_MODE);

    // [Verification]
    BOOST_CHECK_EQUAL(stream.IsOpen(), EXPECTED_OPEN_STATUS);
}

/// <summary>
/// Checks that the IsOpen property returns False when the file is not open.
/// </summary>
ZTEST_CASE ( Open_IsOpenReturnsFalseWhenFileIsNotOpen_Test )
{
    // [Preparation]
    const puint_z INITIAL_CAPACITY = 1U;
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./NonexistingFile.txt");
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Open;
    const bool EXPECTED_OPEN_STATUS = false;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream stream(INITIAL_CAPACITY);

    // [Execution]
    errorInfo = stream.Open(INPUT_PATH, OPEN_MODE);

    // [Verification]
    BOOST_CHECK_EQUAL(stream.IsOpen(), EXPECTED_OPEN_STATUS);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the file is already open.
/// </summary>
ZTEST_CASE ( Open_AssertionFailsWhenFileIsAlreadyOpen_Test )
{
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const puint_z INITIAL_CAPACITY = 4U;
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Open;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream stream(INPUT_PATH, OPEN_MODE, INITIAL_CAPACITY, errorInfo);
    bool bAssertionFailed = false;
    
    // [Execution]
    try
    {
        stream.Open(INPUT_PATH, OPEN_MODE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif

/// <summary>
/// Checks that the content of the stream is flushed when the new position is not contiguous.
/// </summary>
ZTEST_CASE ( Close_ContentIsFlushedWhenNewPositionIsNotContiguous_Test )
{
    // Assuming the existence of:
    // -./FileToWrite2.txt

    // [Preparation]
    const puint_z ORIGINAL_FILE_SIZE = 8U;
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./FileToWrite2.txt");
    const char CONTENT_TO_WRITE[] = {'W', 'X', 'Y', 'Z'};
    const puint_z OFFSET = 0;
    const puint_z BUFFER_SIZE = 4U;
    const puint_z WRITE_BLOCK_SIZE = sizeof(CONTENT_TO_WRITE);
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Open;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream stream(INPUT_PATH, OPEN_MODE, BUFFER_SIZE, errorInfo);

    // [Execution]
    stream.SetPosition(6U);
    stream.Write(CONTENT_TO_WRITE, OFFSET, WRITE_BLOCK_SIZE);
    stream.Close(); // Calls Flush

    // [Verification]
    FileInfo fileInfo = SFile::GetFileInfo(Path(INPUT_PATH), errorInfo);
    bool bStreamWasFlushed = fileInfo.GetSize() > ORIGINAL_FILE_SIZE;
    BOOST_CHECK(bStreamWasFlushed);
}

/// <summary>
/// Checks that the IsOpen property returns False when the file is closed.
/// </summary>
ZTEST_CASE ( Close_IsOpenReturnsFalseWhenFileIsClosed_Test )
{
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const puint_z INITIAL_CAPACITY = 1U;
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Open;
    const bool EXPECTED_OPEN_STATUS = false;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream stream(INPUT_PATH, OPEN_MODE, INITIAL_CAPACITY, errorInfo);

    // [Execution]
    stream.Close();

    // [Verification]
    BOOST_CHECK_EQUAL(stream.IsOpen(), EXPECTED_OPEN_STATUS);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the file is already open.
/// </summary>
ZTEST_CASE ( Close_AssertionFailsWhenFileIsAlreadyClosed_Test )
{
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const puint_z INITIAL_CAPACITY = 4U;
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Open;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream stream(INPUT_PATH, OPEN_MODE, INITIAL_CAPACITY, errorInfo);
    stream.Close();
    bool bAssertionFailed = false;
    
    // [Execution]
    try
    {
        stream.Close();
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that an assertion fails when the file is already open.
/// </summary>
ZTEST_CASE ( GetLength_AssertionFailsWhenFileIsClosed_Test )
{
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const puint_z INITIAL_CAPACITY = 4U;
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Open;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream stream(INPUT_PATH, OPEN_MODE, INITIAL_CAPACITY, errorInfo);
    stream.Close();
    bool bAssertionFailed = false;
    
    // [Execution]
    try
    {
        stream.GetLength();
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif

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
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const puint_z INITIAL_CAPACITY = 4U;
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Open;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream stream(INPUT_PATH, OPEN_MODE, INITIAL_CAPACITY, errorInfo);
    const puint_z EXPECTED_POSITION = 4U;

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
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const puint_z INITIAL_CAPACITY = 4U;
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Open;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream stream(INPUT_PATH, OPEN_MODE, INITIAL_CAPACITY, errorInfo);
    const bool ASSERTION_FAILED = true;
    const puint_z NEW_POSITION = 5U;

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

/// <summary>
/// Checks that an assertion fails when the file is already open.
/// </summary>
ZTEST_CASE ( SetPosition_AssertionFailsWhenFileIsClosed_Test )
{
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const puint_z INITIAL_CAPACITY = 4U;
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Open;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream stream(INPUT_PATH, OPEN_MODE, INITIAL_CAPACITY, errorInfo);
    stream.Close();
    bool bAssertionFailed = false;
    
    // [Execution]
    try
    {
        stream.SetPosition(0);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#elif Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that the internal pointer is not moved when the input position is out of bounds.
/// </summary>
ZTEST_CASE ( SetPosition_ThePointerIsNotMovedWhenTheInputPositionIsOutOfBounds_Test )
{
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const puint_z INITIAL_CAPACITY = 4U;
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Open;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream stream(INPUT_PATH, OPEN_MODE, INITIAL_CAPACITY, errorInfo);
    const puint_z ORIGINAL_POSITION = 0;
    const puint_z NEW_POSITION = 5U;

    // [Execution]
    stream.SetPosition(NEW_POSITION);
    
    // [Verification]
    puint_z uPosition = stream.GetPosition();
    BOOST_CHECK_EQUAL(uPosition, ORIGINAL_POSITION);
}

#endif

/// <summary>
/// It is not necessary to test this method since it is just a getter.
/// </summary>
ZTEST_CASE ( GetPath_NotNecessaryToTest_Test )
{
    BOOST_TEST_MESSAGE("It is not necessary to test this method since it is just a getter");
}

/// <summary>
/// It is not necessary to test this method since it is just a getter.
/// </summary>
ZTEST_CASE ( IsOpen_NotNecessaryToTest_Test )
{
    BOOST_TEST_MESSAGE("It is not necessary to test this method since it is just a getter");
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the file is already open.
/// </summary>
ZTEST_CASE ( GetNativeHandle_AssertionFailsWhenFileIsClosed_Test )
{
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const puint_z INITIAL_CAPACITY = 4U;
    const Path INPUT_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const EFileOpenMode OPEN_MODE = EFileOpenMode::E_Open;
    EFileSystemError errorInfo = EFileSystemError::E_Unknown;
    FileStream stream(INPUT_PATH, OPEN_MODE, INITIAL_CAPACITY, errorInfo);
    stream.Close();
    bool bAssertionFailed = false;
    
    // [Execution]
    try
    {
        stream.GetNativeHandle();
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif

// End - Test Suite: FileStream
ZTEST_SUITE_END()
