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
// Note2: These unit tests make use of some artifacts located at /testing/bin/artifacts/artifacts/SFile/ (copied to the cwd before execution).

#include <boost/test/auto_unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
using namespace boost::unit_test;

#include "../../testsystem/TestingExternalDefinitions.h"

#include "ZFileSystem/SFile.h"

// These includes are needed by WaitForCreationOrDeletion function
#include "ZTiming/Stopwatch.h"
#include "ZCommon/DataTypes/ArrayResult.h"
#include "ZCommon/DataTypes/ETextEncoding.h"
#include "ZThreading/SThisThread.h"
#include "ZFileSystem/SDirectory.h"
#include <fstream>

// The base path to all the artifacts used by these tests
static const string_z PATH_TO_ARTIFACTS("./artifacts/SFile/");

// Function that waits for a predefined amount of time for a file system operation to complete
bool WaitForCreationOrDeletion_SFileTestHelper(const Path &directoryOrFile, const bool bTDeletionFCreation)
{
    static const u64_z MAXIMUM_WAIT_TIME = 600ULL; // milliseconds

#if defined(Z_OS_LINUX) || defined(Z_OS_MAC)
    static const ETextEncoding PATH_ENCODING = ETextEncoding::E_UTF8;
#elif defined(Z_OS_WINDOWS)
    static const ETextEncoding PATH_ENCODING = string_z::GetLocalEncodingUTF16();
#endif

    ArrayResult<i8_z> arBytesDirectory = directoryOrFile.ToString().ToBytes(PATH_ENCODING);
    boost::filesystem::path::value_type* szPath = (boost::filesystem::path::value_type*)arBytesDirectory.Get();
    boost::filesystem::path directoryOrFilePath(szPath);

    Stopwatch elapsedTime;
    elapsedTime.Set();
    bool bTooMuchTime = false;

    while(boost::filesystem::exists(directoryOrFilePath) == bTDeletionFCreation && !bTooMuchTime)
    {
        SThisThread::Yield();
        bTooMuchTime = elapsedTime.GetElapsedTimeAsTimeSpan().GetMilliseconds() < MAXIMUM_WAIT_TIME;
    }

    Z_ASSERT_ERROR(!bTooMuchTime, "The timeout expired, the file or directory could not be created or deleted fast enough.");

    return !bTooMuchTime;
}

// This function checks the existence of the content in a concrete file
bool CheckFileContent(const Path &filePath, const string_z &strExpectedFileContent)
{
    EFileSystemError errorCode = EFileSystemError::E_Success;
    bool bContentMatchesExpectations = true;

    // Checks that the file exists
    bContentMatchesExpectations = bContentMatchesExpectations && SFile::Exists(filePath, errorCode);

    if(bContentMatchesExpectations)
    {
        // [TODO] Thund: Replace this stuff with TextStreamReader<FileStream> when they both exist
        // Opens the file
        ArrayResult<i8_z> arFilePath = filePath.ToString().ToBytes(ETextEncoding::E_ASCII);
        std::ifstream inputFile(arFilePath.Get());

        if(inputFile.is_open())
        {
            std::string strContent;
            bool bEOF = false;

            while(!bEOF)
            {
                bEOF = (inputFile >> strContent).eof();
            }

            string_z strFileContent = strContent.c_str();

            // Checks the content of the file
            bContentMatchesExpectations = bContentMatchesExpectations && strFileContent == strExpectedFileContent;
        }
        else
        {
            bContentMatchesExpectations = false;
        }
    }

    return bContentMatchesExpectations;
}



ZTEST_SUITE_BEGIN( SFile_TestSuite )

/// <summary>
/// Checks that it returns DoesNotExist when the file does not exist.
/// </summary>
ZTEST_CASE ( Delete_FileDoesNotExist_Test )
{
    // [Preparation]
    const Path FILE_PATH(PATH_TO_ARTIFACTS + "./XXXThisFileDoesNotExistXXX");
    const EFileSystemError EXPECTED_RESULT = EFileSystemError::E_DoesNotExist;

    // [Execution]
    EFileSystemError errorCode = SFile::Delete(FILE_PATH);
    
    // [Verification]
    BOOST_CHECK(errorCode == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns Success when the file exists and is removed.
/// </summary>
ZTEST_CASE ( Delete_FileIsDeleted_Test )
{
    // Assuming the existence of:
    // -./FileToDelete.txt

    // [Preparation]
    const Path FILE_PATH(PATH_TO_ARTIFACTS + "./FileToDelete.txt");
    const EFileSystemError EXPECTED_RESULT = EFileSystemError::E_Success;

    // [Execution]
    EFileSystemError errorCode = SFile::Delete(FILE_PATH);
    
    // [Verification]
    WaitForCreationOrDeletion_SFileTestHelper(FILE_PATH, true);

    EFileSystemError existsErrorCode = EFileSystemError::E_Success;
    bool bFileExists = SFile::Exists(FILE_PATH, existsErrorCode);

    BOOST_CHECK(errorCode == EXPECTED_RESULT);
    BOOST_CHECK(!bFileExists);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input path does not refer to a file.
/// </summary>
ZTEST_CASE ( Delete_AssertionFailsWhenInputPathIsNotFile_Test )
{
    // Assuming the existence of:
    // -./NotAFile/

    // [Preparation]
    const Path FILE_PATH(PATH_TO_ARTIFACTS + "./NotAFile/");
    bool bAssertionFailed = false;

    // [Execution]
    try
    {
        SFile::Delete(FILE_PATH);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }
    
    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif

/// <summary>
/// Checks that it returns DoesNotExist when the source file does not exist.
/// </summary>
ZTEST_CASE ( Move_SourceFileDoesNotExist_Test )
{
    // [Preparation]
    const Path SOURCE_FILE_PATH(PATH_TO_ARTIFACTS + "./XXXThisFileDoesNotExistXXX");
    const Path DESTINATION_DIRECTORY(PATH_TO_ARTIFACTS + "./");
    const EFileSystemError EXPECTED_RESULT = EFileSystemError::E_DoesNotExist;

    // [Execution]
    EFileSystemError errorCode = SFile::Move(SOURCE_FILE_PATH, DESTINATION_DIRECTORY, true);
    
    // [Verification]
    BOOST_CHECK(errorCode == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns DoesNotExist when the destination directory does not exist.
/// </summary>
ZTEST_CASE ( Move_DestinationDirectoryDoesNotExist_Test )
{
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const Path SOURCE_FILE_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const Path DESTINATION_DIRECTORY(PATH_TO_ARTIFACTS + "./XXXThisDirectoryDoesNotExistXXX/");
    const EFileSystemError EXPECTED_RESULT = EFileSystemError::E_DoesNotExist;

    // [Execution]
    EFileSystemError errorCode = SFile::Move(SOURCE_FILE_PATH, DESTINATION_DIRECTORY, true);
    
    // [Verification]
    BOOST_CHECK(errorCode == EXPECTED_RESULT);
}

/// <summary>
/// Checks that source file is moved when the destination has a file with the same name and the replace flag is True.
/// </summary>
ZTEST_CASE ( Move_SourceFileIsMovedWhenDestinationHasContentWithSameNameAndReplaceIsTrue_Test )
{
    // Assuming the existence of:
    // -./FileToMove.txt
    // -./MoveDestinationWithSameFile/
    // -./MoveDestinationWithSameFile/FileToMove.txt

    // [Preparation]
    const Path SOURCE_FILE_PATH(PATH_TO_ARTIFACTS + "./FileToMove.txt");
    const Path DESTINATION_DIRECTORY(PATH_TO_ARTIFACTS + "./MoveDestinationWithSameFile/");
    const Path EXPECTED_FILE_PATH(PATH_TO_ARTIFACTS + "./MoveDestinationWithSameFile/FileToMove.txt");
    const string_z EXPECTED_FILE_CONTENT("MOVED");
    const EFileSystemError EXPECTED_RESULT = EFileSystemError::E_Success;
    const bool INPUT_REPLACE = true;

    // [Execution]
    EFileSystemError errorCode = SFile::Move(SOURCE_FILE_PATH, DESTINATION_DIRECTORY, INPUT_REPLACE);
    
    // [Verification]
    WaitForCreationOrDeletion_SFileTestHelper(EXPECTED_FILE_PATH, false);

    EFileSystemError existsErrorCode = EFileSystemError::E_Success;
    bool bDestinationFileExists = SFile::Exists(EXPECTED_FILE_PATH, existsErrorCode);
    bool bDestinationWasReplaced = CheckFileContent(EXPECTED_FILE_PATH, EXPECTED_FILE_CONTENT);
    bool bSourceFileDoesntExist = !SFile::Exists(SOURCE_FILE_PATH, existsErrorCode);

    BOOST_CHECK(errorCode == EXPECTED_RESULT);
    BOOST_CHECK(bDestinationFileExists);
    BOOST_CHECK(bSourceFileDoesntExist);
    BOOST_CHECK(bDestinationWasReplaced);
}

/// <summary>
/// Checks that source file is not moved when the destination has a file with the same name and the replace flag is False.
/// </summary>
ZTEST_CASE ( Move_SourceFileIsNotMovedWhenDestinationHasContentWithSameNameAndReplaceIsFalse_Test )
{
    // Assuming the existence of:
    // -./FileToMove2.txt
    // -./MoveDestinationWithSameFile2/
    // -./MoveDestinationWithSameFile2/FileToMove2.txt

    // [Preparation]
    const Path SOURCE_FILE_PATH(PATH_TO_ARTIFACTS + "./FileToMove2.txt");
    const Path DESTINATION_DIRECTORY(PATH_TO_ARTIFACTS + "./MoveDestinationWithSameFile2/");
    const Path NOT_EXPECTED_CONTENT = Path(PATH_TO_ARTIFACTS + "./MoveDestinationWithSameFile2/FileToMove2.txt");
    const string_z EXPECTED_FILE_CONTENT = string_z::GetEmpty();
    const EFileSystemError EXPECTED_RESULT = EFileSystemError::E_AlreadyExists;
    const bool INPUT_REPLACE = false;

    // [Execution]
    EFileSystemError errorCode = SFile::Move(SOURCE_FILE_PATH, DESTINATION_DIRECTORY, INPUT_REPLACE);
    
    // [Verification]
    EFileSystemError existsErrorCode = EFileSystemError::E_Success;
    bool bDestinationFileContentHasNotChanged = CheckFileContent(NOT_EXPECTED_CONTENT, EXPECTED_FILE_CONTENT);
    bool bSourceFileStillExists = SFile::Exists(SOURCE_FILE_PATH, existsErrorCode);

    BOOST_CHECK(errorCode == EXPECTED_RESULT);
    BOOST_CHECK(bSourceFileStillExists);
    BOOST_CHECK(bDestinationFileContentHasNotChanged);
}

/// <summary>
/// Checks that source file is moved when the destination is empty and the replace flag is False.
/// </summary>
ZTEST_CASE ( Move_SourceFileIsMovedWhenDestinationIsEmptyAndReplaceIsFalse_Test )
{
    // Assuming the existence of:
    // -./FileToMove3.txt

    // [Preparation]
    const Path SOURCE_FILE_PATH(PATH_TO_ARTIFACTS + "./FileToMove3.txt");
    const Path DESTINATION_DIRECTORY(PATH_TO_ARTIFACTS + "./MoveDestinationEmpty/");
    const Path EXPECTED_FILE_PATH(PATH_TO_ARTIFACTS + "./MoveDestinationEmpty/FileToMove3.txt");
    const string_z EXPECTED_FILE_CONTENT("MOVED");
    const EFileSystemError EXPECTED_RESULT = EFileSystemError::E_Success;
    const bool INPUT_REPLACE = false;
    
    // Assures that the directory exists
    Path parentDirectory = DESTINATION_DIRECTORY;
    parentDirectory.RemoveLastDirectory();
    SDirectory::Create(parentDirectory, "MoveDestinationEmpty");

    // [Execution]
    EFileSystemError errorCode = SFile::Move(SOURCE_FILE_PATH, DESTINATION_DIRECTORY, INPUT_REPLACE);
    
    // [Verification]
    WaitForCreationOrDeletion_SFileTestHelper(EXPECTED_FILE_PATH, false);

    EFileSystemError existsErrorCode = EFileSystemError::E_Success;
    bool bDestinationFileExists = SFile::Exists(EXPECTED_FILE_PATH, existsErrorCode);
    bool bSourceFileDoesntExist = !SFile::Exists(SOURCE_FILE_PATH, existsErrorCode);
    bool bContentExists = CheckFileContent(EXPECTED_FILE_PATH, EXPECTED_FILE_CONTENT);

    BOOST_CHECK(errorCode == EXPECTED_RESULT);
    BOOST_CHECK(bDestinationFileExists);
    BOOST_CHECK(bSourceFileDoesntExist);
    BOOST_CHECK(bContentExists);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the source path does not refer to a file.
/// </summary>
ZTEST_CASE ( Move_AssertionFailsWhenSourcePathIsNotFile_Test )
{
    // Assuming the existence of:
    // -./NotAFile/
    
    // [Preparation]
    const Path SOURCE_FILE_PATH(PATH_TO_ARTIFACTS + "./NotAFile/");
    const Path DESTINATION_DIRECTORY(PATH_TO_ARTIFACTS + "./");
    bool bAssertionFailed = false;

    // [Execution]
    try
    {
        SFile::Move(SOURCE_FILE_PATH, DESTINATION_DIRECTORY, true);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }
    
    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that an assertion fails when the destination path does not refer to a directory.
/// </summary>
ZTEST_CASE ( Move_AssertionFailsWhenDestinationPathIsNotDirectory_Test )
{
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const Path SOURCE_FILE_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const Path DESTINATION_DIRECTORY(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    bool bAssertionFailed = false;

    // [Execution]
    try
    {
        SFile::Move(SOURCE_FILE_PATH, DESTINATION_DIRECTORY, true);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }
    
    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif

/// <summary>
/// Checks that it returns DoesNotExist when the source file does not exist.
/// </summary>
ZTEST_CASE ( Rename_SourceFileDoesNotExist_Test )
{
    // [Preparation]
    const Path EXPECTED_NEW_FILE_PATH(PATH_TO_ARTIFACTS + "./XXXThisFileDoesNotExistXXX");
    Path sourceFile = EXPECTED_NEW_FILE_PATH;
    const string_z NEW_NAME("RenamedFile");
    const bool REPLACE_EXTENSION = true;
    const EFileSystemError EXPECTED_RESULT = EFileSystemError::E_DoesNotExist;

    // [Execution]
    EFileSystemError errorCode = SFile::Rename(sourceFile, NEW_NAME, REPLACE_EXTENSION);
    
    // [Verification]
    BOOST_CHECK(errorCode == EXPECTED_RESULT);
    BOOST_CHECK(sourceFile == EXPECTED_NEW_FILE_PATH);
}

/// <summary>
/// Checks that it returns AlreadyExists when the there is already a file with the same name.
/// </summary>
ZTEST_CASE ( Rename_AFileWithSameNameAlreadyExists_Test )
{
    // Assuming the existence of:
    // -./FileToRename.txt
    // -./ExistingRenamedFile.txt

    // [Preparation]
    const Path EXPECTED_NEW_FILE_PATH(PATH_TO_ARTIFACTS + "./FileToRename.txt");
    Path sourceFile = EXPECTED_NEW_FILE_PATH;
    const string_z NEW_NAME("ExistingRenamedFile.txt");
    const bool REPLACE_EXTENSION = true;
    const EFileSystemError EXPECTED_RESULT = EFileSystemError::E_AlreadyExists;

    // [Execution]
    EFileSystemError errorCode = SFile::Rename(sourceFile, NEW_NAME, REPLACE_EXTENSION);
    
    // [Verification]
    BOOST_CHECK(errorCode == EXPECTED_RESULT);
    BOOST_CHECK(sourceFile == EXPECTED_NEW_FILE_PATH);
}

/// <summary>
/// Checks that it returns the new path when the file is successfully renamed.
/// </summary>
ZTEST_CASE ( Rename_ItReturnsNewPathWhenFileIsRenamed_Test )
{
    // Assuming the existence of:
    // -./FileToRename2.txt

    // [Preparation]
    const Path EXPECTED_NEW_FILE_PATH(PATH_TO_ARTIFACTS + "./RenamedFile2.txt");
    Path sourceFile(PATH_TO_ARTIFACTS + "./FileToRename2.txt");
    const string_z NEW_NAME("RenamedFile2.txt");
    const bool REPLACE_EXTENSION = true;
    const EFileSystemError EXPECTED_RESULT = EFileSystemError::E_Success;

    // [Execution]
    EFileSystemError errorCode = SFile::Rename(sourceFile, NEW_NAME, REPLACE_EXTENSION);
    
    // [Verification]
    EFileSystemError existsErrorCode = EFileSystemError::E_Success;
    bool bRenamedFileExists = SFile::Exists(sourceFile, existsErrorCode);
    BOOST_CHECK(bRenamedFileExists);
    BOOST_CHECK(errorCode == EXPECTED_RESULT);
    BOOST_CHECK(sourceFile == EXPECTED_NEW_FILE_PATH);
}

/// <summary>
/// Checks that the extension of the file is not modified when the input flag is False.
/// </summary>
ZTEST_CASE ( Rename_ExtensionIsNotReplacedWhenInputFlagIsFalse_Test )
{
    // Assuming the existence of:
    // -./FileToRename3.txt

    // [Preparation]
    const Path EXPECTED_NEW_FILE_PATH(PATH_TO_ARTIFACTS + "./RenamedFile3.txt");
    Path sourceFile(PATH_TO_ARTIFACTS + "./FileToRename3.txt");
    const string_z NEW_NAME("RenamedFile3");
    const bool REPLACE_EXTENSION = false;
    const EFileSystemError EXPECTED_RESULT = EFileSystemError::E_Success;

    // [Execution]
    EFileSystemError errorCode = SFile::Rename(sourceFile, NEW_NAME, REPLACE_EXTENSION);
    
    // [Verification]
    EFileSystemError existsErrorCode = EFileSystemError::E_Success;
    bool bRenamedFileExists = SFile::Exists(sourceFile, existsErrorCode);
    BOOST_CHECK(bRenamedFileExists);
    BOOST_CHECK(errorCode == EXPECTED_RESULT);
    BOOST_CHECK(sourceFile == EXPECTED_NEW_FILE_PATH);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the source path does not refer to a file.
/// </summary>
ZTEST_CASE ( Rename_AssertionFailsWhenSourcePathIsNotFile_Test )
{
    // Assuming the existence of:
    // -./NotAFile/

    // [Preparation]
    Path sourceFile(PATH_TO_ARTIFACTS + "./NotAFile/");
    const string_z NEW_NAME("RenamedFile");
    bool bAssertionFailed = false;

    // [Execution]
    try
    {
        SFile::Rename(sourceFile, NEW_NAME, true);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }
    
    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif

/// <summary>
/// Checks that it returns DoesNotExist when the source file does not exist.
/// </summary>
ZTEST_CASE ( Copy_SourceFileDoesNotExist_Test )
{
    // [Preparation]
    const Path SOURCE_FILE_PATH(PATH_TO_ARTIFACTS + "./XXXThisFileDoesNotExistXXX");
    const Path DESTINATION_DIRECTORY(PATH_TO_ARTIFACTS + "./");
    const EFileSystemError EXPECTED_RESULT = EFileSystemError::E_DoesNotExist;

    // [Execution]
    EFileSystemError errorCode = SFile::Copy(SOURCE_FILE_PATH, DESTINATION_DIRECTORY, true);
    
    // [Verification]
    BOOST_CHECK(errorCode == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns DoesNotExist when the destination directory does not exist.
/// </summary>
ZTEST_CASE ( Copy_DestinationDirectoryDoesNotExist_Test )
{
    // [Preparation]
    const Path SOURCE_FILE_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const Path DESTINATION_DIRECTORY(PATH_TO_ARTIFACTS + "./XXXThisDirectoryDoesNotExistXXX/");
    const EFileSystemError EXPECTED_RESULT = EFileSystemError::E_DoesNotExist;

    // [Execution]
    EFileSystemError errorCode = SFile::Copy(SOURCE_FILE_PATH, DESTINATION_DIRECTORY, true);
    
    // [Verification]
    BOOST_CHECK(errorCode == EXPECTED_RESULT);
}

/// <summary>
/// Checks that source file is copied when the destination has a directory with the same name and the replace flag is True.
/// </summary>
ZTEST_CASE ( Copy_SourceFileIsCopiedWhenDestinationHasContentWithSameNameAndReplaceIsTrue_Test )
{
    // Assuming the existence of:
    // -./FileToCopy.txt
    // -./CopyDestinationWithSameFile/FileToCopy,txt

    // [Preparation]
    const Path SOURCE_FILE_PATH(PATH_TO_ARTIFACTS + "./FileToCopy.txt");
    const Path DESTINATION_DIRECTORY(PATH_TO_ARTIFACTS + "./CopyDestinationWithSameFile/");
    const Path EXPECTED_FILE_PATH(PATH_TO_ARTIFACTS + "./CopyDestinationWithSameFile/FileToCopy.txt");
    const string_z EXPECTED_FILE_CONTENT("COPIED");
    const EFileSystemError EXPECTED_RESULT = EFileSystemError::E_Success;
    const bool INPUT_REPLACE = true;

    // [Execution]
    EFileSystemError errorCode = SFile::Copy(SOURCE_FILE_PATH, DESTINATION_DIRECTORY, INPUT_REPLACE);
    
    // [Verification]
    WaitForCreationOrDeletion_SFileTestHelper(EXPECTED_FILE_PATH, false);

    EFileSystemError existsErrorCode = EFileSystemError::E_Success;
    bool bDestinationFileExists = SFile::Exists(EXPECTED_FILE_PATH, existsErrorCode);
    bool bSourceFileStillExists = SFile::Exists(SOURCE_FILE_PATH, existsErrorCode);
    bool bContentExists = CheckFileContent(EXPECTED_FILE_PATH, EXPECTED_FILE_CONTENT);

    BOOST_CHECK(errorCode == EXPECTED_RESULT);
    BOOST_CHECK(bDestinationFileExists);
    BOOST_CHECK(bSourceFileStillExists);
    BOOST_CHECK(bContentExists);
}

/// <summary>
/// Checks that source file is not copied when the destination contains a file with the same name and the replace flag is False.
/// </summary>
ZTEST_CASE ( Copy_SourceFileIsNotCopiedWhenDestinationHasContentWithSameNameAndReplaceIsFalse_Test )
{
    // Assuming the existence of:
    // -./FileToCopy2.txt
    // -./CopyDestinationWithSameFile2/FileToCopy2,txt

    // [Preparation]
    const Path SOURCE_FILE_PATH(PATH_TO_ARTIFACTS + "./FileToCopy2.txt");
    const Path DESTINATION_DIRECTORY(PATH_TO_ARTIFACTS + "./CopyDestinationWithSameFile2/");
    const Path EXPECTED_CONTENT = Path(PATH_TO_ARTIFACTS + "./CopyDestinationWithSameFile2/FileToCopy2.txt");
    const string_z EXPECTED_NOT_REPLACED_FILE_CONTENT = string_z::GetEmpty();
    const string_z EXPECTED_COPIED_FILE_CONTENT("COPIED");
    
    const EFileSystemError EXPECTED_RESULT = EFileSystemError::E_AlreadyExists;
    const bool INPUT_REPLACE = false;

    // [Execution]
    EFileSystemError errorCode = SFile::Copy(SOURCE_FILE_PATH, DESTINATION_DIRECTORY, INPUT_REPLACE);
    
    // [Verification]
    EFileSystemError existsErrorCode = EFileSystemError::E_Success;
    bool bDestinationFileContentHasNotChanged = CheckFileContent(EXPECTED_CONTENT, EXPECTED_NOT_REPLACED_FILE_CONTENT);
    bool bSourceFileStillExists = SFile::Exists(SOURCE_FILE_PATH, existsErrorCode);

    BOOST_CHECK(errorCode == EXPECTED_RESULT);
    BOOST_CHECK(bSourceFileStillExists);
    BOOST_CHECK(bDestinationFileContentHasNotChanged);
}

/// <summary>
/// Checks that source file is copied when the destination is empty and the replace flag is False.
/// </summary>
ZTEST_CASE ( Copy_SourceFileAndContentAreCopiedWhenDestinationIsEmptyAndReplaceIsFalse_Test )
{
    // Assuming the existence of:
    // -./FileToCopy3.txt

    // [Preparation]
    const Path SOURCE_FILE_PATH(PATH_TO_ARTIFACTS + "./FileToCopy3.txt");
    const Path DESTINATION_DIRECTORY(PATH_TO_ARTIFACTS + "./CopyDestinationEmpty/");
    const Path EXPECTED_FILE_PATH(PATH_TO_ARTIFACTS + "./CopyDestinationEmpty/FileToCopy3.txt");
    const string_z EXPECTED_FILE_CONTENT("COPIED");
    const EFileSystemError EXPECTED_RESULT = EFileSystemError::E_Success;
    const bool INPUT_REPLACE = true;
        
    // Assures that the directory exists
    Path parentDirectory = DESTINATION_DIRECTORY;
    parentDirectory.RemoveLastDirectory();
    SDirectory::Create(parentDirectory, "CopyDestinationEmpty");

    // [Execution]
    EFileSystemError errorCode = SFile::Copy(SOURCE_FILE_PATH, DESTINATION_DIRECTORY, INPUT_REPLACE);
    
    // [Verification]
    WaitForCreationOrDeletion_SFileTestHelper(EXPECTED_FILE_PATH, false);

    EFileSystemError existsErrorCode = EFileSystemError::E_Success;
    bool bDestinationFileExists = SFile::Exists(EXPECTED_FILE_PATH, existsErrorCode);
    bool bSourceFileStillExists = SFile::Exists(SOURCE_FILE_PATH, existsErrorCode);
    bool bContentExists = CheckFileContent(EXPECTED_FILE_PATH, EXPECTED_FILE_CONTENT);

    BOOST_CHECK(errorCode == EXPECTED_RESULT);
    BOOST_CHECK(bDestinationFileExists);
    BOOST_CHECK(bSourceFileStillExists);
    BOOST_CHECK(bContentExists);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the source path does not refer to a file.
/// </summary>
ZTEST_CASE ( Copy_AssertionFailsWhenSourcePathIsNotFile_Test )
{
    // Assuming the existence of:
    // -./NotAFile/

    // [Preparation]
    const Path SOURCE_FILE_PATH(PATH_TO_ARTIFACTS + "./NotAFile/");
    const Path DESTINATION_DIRECTORY(PATH_TO_ARTIFACTS + "./");
    bool bAssertionFailed = false;

    // [Execution]
    try
    {
        SFile::Copy(SOURCE_FILE_PATH, DESTINATION_DIRECTORY, true);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }
    
    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that an assertion fails when the destination path does not refer to a directory.
/// </summary>
ZTEST_CASE ( Copy_AssertionFailsWhenDestinationPathIsNotDirectory_Test )
{
    // Assuming the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const Path SOURCE_FILE_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const Path DESTINATION_DIRECTORY(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    bool bAssertionFailed = false;

    // [Execution]
    try
    {
        SFile::Copy(SOURCE_FILE_PATH, DESTINATION_DIRECTORY, true);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }
    
    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif

/// <summary>
/// Checks that it returns False when the file does not exist.
/// </summary>
ZTEST_CASE ( Exists_ReturnsFalseWhenFileDoesNotExist_Test )
{
    // [Preparation]
    const Path FILE_PATH(PATH_TO_ARTIFACTS + "./XXXThisFileDoesNotExistXXX");
    const bool EXPECTED_VALUE = false;
    const EFileSystemError EXPECTED_ERRORCODE = EFileSystemError::E_Success;
    EFileSystemError errorCode = EFileSystemError::E_Success;

    // [Execution]
    bool bReturnedValue = SFile::Exists(FILE_PATH, errorCode);
    
    // [Verification]
    BOOST_CHECK(errorCode == EXPECTED_ERRORCODE);
    BOOST_CHECK_EQUAL(bReturnedValue, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns True when the file exists.
/// </summary>
ZTEST_CASE ( Exists_ReturnsTrueWhenFileExists_Test )
{
    // Assumes the existence of:
    // -./ExistingFile.txt

    // [Preparation]
    const Path FILE_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const bool EXPECTED_VALUE = true;
    const EFileSystemError EXPECTED_ERRORCODE = EFileSystemError::E_Success;
    EFileSystemError errorCode = EFileSystemError::E_Success;

    // [Execution]
    bool bReturnedValue = SFile::Exists(FILE_PATH, errorCode);
    
    // [Verification]
    BOOST_CHECK(errorCode == EXPECTED_ERRORCODE);
    BOOST_CHECK_EQUAL(bReturnedValue, EXPECTED_VALUE);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input path does not refer to a file.
/// </summary>
ZTEST_CASE ( Exists_AssertionFailsWhenInputPathIsNotFile_Test )
{
    // Assuming the existence of:
    // -./NotAFile/

    // [Preparation]
    const Path NOT_A_FILE_PATH(PATH_TO_ARTIFACTS + "./NotAFile/");
    bool bAssertionFailed = false;

    // [Execution]
    try
    {
        EFileSystemError errorCode = EFileSystemError::E_Success;
        SFile::Exists(NOT_A_FILE_PATH, errorCode);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }
    
    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif

/// <summary>
/// Checks that it returns DoesNotExist when the file does not exist.
/// </summary>
ZTEST_CASE ( GetFileInfo_FileDoesNotExist_Test )
{
    // [Preparation]
    const Path FILE_PATH(PATH_TO_ARTIFACTS + "./XXXThisFileDoesNotExistXXX");

    const EFileSystemError EXPECTED_ERRORCODE = EFileSystemError::E_DoesNotExist;
    EFileSystemError errorCode = EFileSystemError::E_DoesNotExist;

    // [Execution]
    FileInfo dirInfo = SFile::GetFileInfo(FILE_PATH, errorCode);
    
    // [Verification]
    BOOST_CHECK(errorCode == EXPECTED_ERRORCODE);
}

/// <summary>
/// Checks that it returns expected information when the file exists.
/// </summary>
ZTEST_CASE ( GetFileInfo_ReturnsExpectedInformationWhenFileExists_Test )
{
    // Assumes the existence of:
    // -./ExistingFile.txt (6 bytes length)

    // [Preparation]
    const Path FILE_PATH(PATH_TO_ARTIFACTS + "./ExistingFile.txt");
    const u64_z EXPECTED_FILESIZE = 6;
    const bool EXPECTED_READONLY_FLAG = false;
    const EFileSystemError EXPECTED_ERRORCODE = EFileSystemError::E_Success;
    EFileSystemError errorCode = EFileSystemError::E_Success;

    // [Execution]
    FileInfo fileInfo = SFile::GetFileInfo(FILE_PATH, errorCode);
    
    // [Verification]
    bool bContainsCorrectPath = fileInfo.GetPath() == FILE_PATH;
    bool bCreationDateTimeIsNotUndefined = !fileInfo.GetCreationDate().IsUndefined();
    bool bLastModificationDateTimeIsNotUndefined = !fileInfo.GetCreationDate().IsUndefined();
    u64_z uFileSize = fileInfo.GetSize();
    bool bIsReadOnly = fileInfo.IsReadOnly();
    
    BOOST_CHECK(errorCode == EXPECTED_ERRORCODE);
    BOOST_CHECK(bContainsCorrectPath);
    BOOST_CHECK(bCreationDateTimeIsNotUndefined);
    BOOST_CHECK(bLastModificationDateTimeIsNotUndefined);
    BOOST_CHECK_EQUAL(uFileSize, EXPECTED_FILESIZE);
    BOOST_CHECK_EQUAL(bIsReadOnly, EXPECTED_READONLY_FLAG);
}

/// <summary>
/// Checks that the read-only flag is True when the file is read-only.
/// </summary>
ZTEST_CASE ( GetFileInfo_ReadyOnlyFlagIsTrueWhenFileIsReadOnly_Test )
{
    // Assumes the existence of:
    // -./ReadOnlyFile.txt

    // [Preparation]
    const Path FILE_PATH(PATH_TO_ARTIFACTS + "./ReadOnlyFile.txt");
    const bool EXPECTED_READONLY_FLAG = true;
    const EFileSystemError EXPECTED_ERRORCODE = EFileSystemError::E_Success;
    EFileSystemError errorCode = EFileSystemError::E_Success;

    // Sets the file as read only
#if defined(Z_OS_LINUX) || defined(Z_OS_MAC)
    static const ETextEncoding PATH_ENCODING = ETextEncoding::E_UTF8;
#elif defined(Z_OS_WINDOWS)
    static const ETextEncoding PATH_ENCODING = string_z::GetLocalEncodingUTF16();
#endif

    ArrayResult<i8_z> arBytesFile = FILE_PATH.ToString().ToBytes(PATH_ENCODING);
    boost::filesystem::path::value_type* szPath = (boost::filesystem::path::value_type*)arBytesFile.Get();
    boost::filesystem::path filePath(szPath);

    boost::system::error_code permissionsErrorCode;
    boost::filesystem::permissions(filePath, boost::filesystem::remove_perms | boost::filesystem::owner_write, permissionsErrorCode);

    // [Execution]
    FileInfo fileInfo = SFile::GetFileInfo(FILE_PATH, errorCode);
    
    // [Verification]
    bool bIsReadOnly = fileInfo.IsReadOnly();
    
    BOOST_CHECK(errorCode == EXPECTED_ERRORCODE);
    BOOST_CHECK_EQUAL(bIsReadOnly, EXPECTED_READONLY_FLAG);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input path does not refer to a file.
/// </summary>
ZTEST_CASE ( GetFileInfo_AssertionFailsWhenInputPathIsNotFile_Test )
{
    // Assuming the existence of:
    // -./NotAFile/

    // [Preparation]
    const Path NOT_A_FILE_PATH(PATH_TO_ARTIFACTS + "./NotAFile/");
    bool bAssertionFailed = false;

    // [Execution]
    try
    {
        EFileSystemError errorCode = EFileSystemError::E_Success;
        SFile::GetFileInfo(NOT_A_FILE_PATH, errorCode);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }
    
    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif

// End - Test Suite: SFile
ZTEST_SUITE_END()
