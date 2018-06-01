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
// Note2: These unit tests make use of some artifacts located at /testing/bin/artifacts/artifacts/SDirectory/ (copied to the cwd before execution).

#include <boost/test/auto_unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
using namespace boost::unit_test;

#include "../../testsystem/TestingExternalDefinitions.h"

#include "ZFileSystem/SDirectory.h"

// These includes are needed by WaitForCreationOrDeletion function
#include "ZTiming/Stopwatch.h"
#include "ZCommon/DataTypes/ArrayResult.h"
#include "ZCommon/DataTypes/ETextEncoding.h"
#include "ZFileSystem/SFile.h"
#include "ZThreading/SThisThread.h"
#include "ZContainers/ArrayDynamic.h"
#include "ZCommon/Exceptions/AssertException.h"
#include <fstream>


// The base path to all the artifacts used by these tests
static const string_z PATH_TO_ARTIFACTS("./artifacts/SDirectory/");

// Function that waits for a predefined amount of time for a file system operation to complete
bool WaitForCreationOrDeletion_SDirectoryTestHelper(const Path &directoryOrFile, const bool bTDeletionFCreation)
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

// This function checks the existence of the content in a concrete directory
bool CheckDirectoryContent(const ArrayBasic<const Path> arContents, const string_z &strExpectedFileContent)
{
    EFileSystemError eErrorCode = EFileSystemError::E_Success;
    bool bContentMatchesExpectations = true;
    puint_z uContentIndex = 0;

    while(bContentMatchesExpectations && uContentIndex < arContents.GetCount())
    {
        if(arContents[uContentIndex].IsDirectory())
        {
            // Checks that the directory exists
            bContentMatchesExpectations = bContentMatchesExpectations && SDirectory::Exists(arContents[uContentIndex], eErrorCode);
        }
        else
        {
            // Checks that the file exists
            bContentMatchesExpectations = bContentMatchesExpectations && 
                                          SFile::Exists(arContents[uContentIndex], eErrorCode);

            if(bContentMatchesExpectations)
            {
                // [TODO] Thund: Replace this stuff with TextStreamReader<FileStream> when they both exist
                // Opens the file
                ArrayResult<i8_z> arFilePath = arContents[uContentIndex].ToString().ToBytes(ETextEncoding::E_ASCII);
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
        }

        ++uContentIndex;
    }

    return bContentMatchesExpectations;
}



ZTEST_SUITE_BEGIN( SDirectory_TestSuite )

/// <summary>
/// Checks that it returns DoesNotExist when the directory does not exist.
/// </summary>
ZTEST_CASE ( Delete_DirectoryDoesNotExist_Test )
{
    // [Preparation]
    const Path DIRECTORY(PATH_TO_ARTIFACTS + "./XXXThisDirectoryDoesNotExistXXX/");
    const EFileSystemError EXPECTED_RESULT = EFileSystemError::E_DoesNotExist;

    // [Execution]
    EFileSystemError eErrorCode = SDirectory::Delete(DIRECTORY);
    
    // [Verification]
    BOOST_CHECK(eErrorCode == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns Success when the directory exists and the directory along with its content are removed.
/// </summary>
ZTEST_CASE ( Delete_DirectoryAndContentAreDeleted_Test )
{
    // Assuming the existence of:
    // -./DirectoryToDelete/
    // -./DirectoryToDelete/Content1/
    // -./DirectoryToDelete/Content2.txt

    // [Preparation]
    const Path DIRECTORY(PATH_TO_ARTIFACTS + "./DirectoryToDelete/");
    const EFileSystemError EXPECTED_RESULT = EFileSystemError::E_Success;

    // [Execution]
    EFileSystemError eErrorCode = SDirectory::Delete(DIRECTORY);
    
    // [Verification]
    WaitForCreationOrDeletion_SDirectoryTestHelper(DIRECTORY, true);

    EFileSystemError existsErrorCode = EFileSystemError::E_Success;
    bool bDirectoryExists = SDirectory::Exists(DIRECTORY, existsErrorCode);

    BOOST_CHECK(eErrorCode == EXPECTED_RESULT);
    BOOST_CHECK(!bDirectoryExists);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input path does not refer to a directory.
/// </summary>
ZTEST_CASE ( Delete_AssertionFailsWhenInputPathIsNotDirectory_Test )
{
    // Assuming the existence of:
    // -./NotADirectory.txt

    // [Preparation]
    const Path DIRECTORY(PATH_TO_ARTIFACTS + "./NotADirectory.txt");
    bool bAssertionFailed = false;

    // [Execution]
    try
    {
        SDirectory::Delete(DIRECTORY);
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
/// Checks that it returns DoesNotExist when the source directory does not exist.
/// </summary>
ZTEST_CASE ( Move_SourceDirectoryDoesNotExist_Test )
{
    // [Preparation]
    const Path SOURCE_DIRECTORY(PATH_TO_ARTIFACTS + "./XXXThisDirectoryDoesNotExistXXX/");
    const Path DESTINATION_DIRECTORY(PATH_TO_ARTIFACTS + "./");
    const EFileSystemError EXPECTED_RESULT = EFileSystemError::E_DoesNotExist;

    // [Execution]
    EFileSystemError eErrorCode = SDirectory::Move(SOURCE_DIRECTORY, DESTINATION_DIRECTORY, true);
    
    // [Verification]
    BOOST_CHECK(eErrorCode == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns DoesNotExist when the destination directory does not exist.
/// </summary>
ZTEST_CASE ( Move_DestinationDirectoryDoesNotExist_Test )
{
    // [Preparation]
    const Path SOURCE_DIRECTORY(PATH_TO_ARTIFACTS + "./");
    const Path DESTINATION_DIRECTORY(PATH_TO_ARTIFACTS + "./XXXThisDirectoryDoesNotExistXXX/");
    const EFileSystemError EXPECTED_RESULT = EFileSystemError::E_DoesNotExist;

    // [Execution]
    EFileSystemError eErrorCode = SDirectory::Move(SOURCE_DIRECTORY, DESTINATION_DIRECTORY, true);
    
    // [Verification]
    BOOST_CHECK(eErrorCode == EXPECTED_RESULT);
}

/// <summary>
/// Checks that source directory and its content are moved when the destination has a directory with the same name and the replace flag is True.
/// </summary>
ZTEST_CASE ( Move_SourceDirectoryAndContentAreMovedWhenDestinationHasContentWithSameNameAndReplaceIsTrue_Test )
{
    // Assuming the existence of:
    // -./DirectoryToMove/
    // -./DirectoryToMove/Content1/
    // -./DirectoryToMove/Content2.txt
    // -./DirectoryToMove/Content1/Content3.txt
    // -./MoveDestinationWithSameDirectory/
    // -./MoveDestinationWithSameDirectory/DirectoryToMove/
    // -./MoveDestinationWithSameDirectory/DirectoryToMove/Content1/
    // -./MoveDestinationWithSameDirectory/DirectoryToMove/Content2.txt
    // -./MoveDestinationWithSameDirectory/DirectoryToMove/Content1/Content3.txt

    // [Preparation]
    const Path SOURCE_DIRECTORY(PATH_TO_ARTIFACTS + "./DirectoryToMove/");
    const Path DESTINATION_DIRECTORY(PATH_TO_ARTIFACTS + "./MoveDestinationWithSameDirectory/");
    const Path EXPECTED_DIRECTORY(PATH_TO_ARTIFACTS + "./MoveDestinationWithSameDirectory/DirectoryToMove/");
    const Path EXPECTED_CONTENT[] = { Path(PATH_TO_ARTIFACTS + "./MoveDestinationWithSameDirectory/DirectoryToMove/Content1/"),
                                       Path(PATH_TO_ARTIFACTS + "./MoveDestinationWithSameDirectory/DirectoryToMove/Content2.txt"),
                                       Path(PATH_TO_ARTIFACTS + "./MoveDestinationWithSameDirectory/DirectoryToMove/Content1/Content3.txt") };
    const string_z EXPECTED_FILE_CONTENT("MOVED");
    const EFileSystemError EXPECTED_RESULT = EFileSystemError::E_Success;
    const bool INPUT_REPLACE = true;

    // [Execution]
    EFileSystemError eErrorCode = SDirectory::Move(SOURCE_DIRECTORY, DESTINATION_DIRECTORY, INPUT_REPLACE);
    
    // [Verification]
    WaitForCreationOrDeletion_SDirectoryTestHelper(EXPECTED_DIRECTORY, false);

    EFileSystemError existsErrorCode = EFileSystemError::E_Success;
    bool bDestinationDirectoryExists = SDirectory::Exists(EXPECTED_DIRECTORY, existsErrorCode);
    bool bSourceDirectoryDoesntExist = !SDirectory::Exists(SOURCE_DIRECTORY, existsErrorCode);
    bool bContentExists = CheckDirectoryContent(ArrayBasic<const Path>(EXPECTED_CONTENT, 3), EXPECTED_FILE_CONTENT);

    BOOST_CHECK(eErrorCode == EXPECTED_RESULT);
    BOOST_CHECK(bDestinationDirectoryExists);
    BOOST_CHECK(bSourceDirectoryDoesntExist);
    BOOST_CHECK(bContentExists);
}

/// <summary>
/// Checks that source directory is not moved when the destination has a directory with the same name and the replace flag is False.
/// </summary>
ZTEST_CASE ( Move_SourceDirectoryIsNotMovedWhenDestinationHasContentWithSameNameAndReplaceIsFalse_Test )
{
    // Assuming the existence of:
    // -./DirectoryToMove2/
    // -./DirectoryToMove2/Content1/
    // -./DirectoryToMove2/Content2.txt
    // -./DirectoryToMove2/Content1/Content3.txt
    // -./MoveDestinationWithSameDirectory2/
    // -./MoveDestinationWithSameDirectory2/DirectoryToMove/
    // -./MoveDestinationWithSameDirectory2/DirectoryToMove/Content1/
    // -./MoveDestinationWithSameDirectory2/DirectoryToMove/Content1/Content3.txt

    // [Preparation]
    const Path SOURCE_DIRECTORY(PATH_TO_ARTIFACTS + "./DirectoryToMove2/");
    const Path DESTINATION_DIRECTORY(PATH_TO_ARTIFACTS + "./MoveDestinationWithSameDirectory2/");
    const Path EXPECTED_CONTENT[] = { Path(PATH_TO_ARTIFACTS + "./MoveDestinationWithSameDirectory2/DirectoryToMove2/Content1/Content3.txt") };
    const Path NOT_EXPECTED_CONTENT[] = {  Path(PATH_TO_ARTIFACTS + "./MoveDestinationWithSameDirectory2/DirectoryToMove2/Content2.txt") };
    const string_z EXPECTED_FILE_CONTENT = string_z::GetEmpty();
    const EFileSystemError EXPECTED_RESULT = EFileSystemError::E_AlreadyExists;
    const bool INPUT_REPLACE = false;

    // [Execution]
    EFileSystemError eErrorCode = SDirectory::Move(SOURCE_DIRECTORY, DESTINATION_DIRECTORY, INPUT_REPLACE);
    
    // [Verification]
    EFileSystemError existsErrorCode = EFileSystemError::E_Success;
    bool bDestinationFileContentHasNotChanged = CheckDirectoryContent(ArrayBasic<const Path>(EXPECTED_CONTENT, 1), EXPECTED_FILE_CONTENT);
    bool bContentIsNotMixed = !CheckDirectoryContent(ArrayBasic<const Path>(NOT_EXPECTED_CONTENT, 1), EXPECTED_FILE_CONTENT);
    bool bSourceDirectoryStillExists = SDirectory::Exists(SOURCE_DIRECTORY, existsErrorCode);

    BOOST_CHECK(eErrorCode == EXPECTED_RESULT);
    BOOST_CHECK(bSourceDirectoryStillExists);
    BOOST_CHECK(bContentIsNotMixed);
    BOOST_CHECK(bDestinationFileContentHasNotChanged);
}

/// <summary>
/// Checks that source directory and its content are moved when the destination has a directory with the same name and the replace flag is True.
/// </summary>
ZTEST_CASE ( Move_SourceDirectoryAndContentAreMovedWhenDestinationIsEmptyAndReplaceIsFalse_Test )
{
    // Assuming the existence of:
    // -./DirectoryToMove3/
    // -./DirectoryToMove3/Content1/
    // -./DirectoryToMove3/Content2.txt
    // -./DirectoryToMove3/Content1/Content3.txt

    // [Preparation]
    const Path SOURCE_DIRECTORY(PATH_TO_ARTIFACTS + "./DirectoryToMove3/");
    const Path DESTINATION_DIRECTORY(PATH_TO_ARTIFACTS + "./MoveDestinationEmpty/");
    const Path EXPECTED_DIRECTORY(PATH_TO_ARTIFACTS + "./MoveDestinationEmpty/DirectoryToMove3/");
    const Path EXPECTED_CONTENT[] = { Path(PATH_TO_ARTIFACTS + "./MoveDestinationEmpty/DirectoryToMove3/Content1/"),
                                       Path(PATH_TO_ARTIFACTS + "./MoveDestinationEmpty/DirectoryToMove3/Content2.txt"),
                                       Path(PATH_TO_ARTIFACTS + "./MoveDestinationEmpty/DirectoryToMove3/Content1/Content3.txt") };
    const string_z EXPECTED_FILE_CONTENT("MOVED");
    const EFileSystemError EXPECTED_RESULT = EFileSystemError::E_Success;
    const bool INPUT_REPLACE = false;

    // Assures that the directory exists
    Path parentDirectory = DESTINATION_DIRECTORY;
    parentDirectory.RemoveLastDirectory();
    SDirectory::Create(parentDirectory, "MoveDestinationEmpty");

    // [Execution]
    EFileSystemError eErrorCode = SDirectory::Move(SOURCE_DIRECTORY, DESTINATION_DIRECTORY, INPUT_REPLACE);
    
    // [Verification]
    WaitForCreationOrDeletion_SDirectoryTestHelper(EXPECTED_DIRECTORY, false);

    EFileSystemError existsErrorCode = EFileSystemError::E_Success;
    bool bDestinationDirectoryExists = SDirectory::Exists(EXPECTED_DIRECTORY, existsErrorCode);
    bool bSourceDirectoryDoesntExist = !SDirectory::Exists(SOURCE_DIRECTORY, existsErrorCode);
    bool bContentExists = CheckDirectoryContent(ArrayBasic<const Path>(EXPECTED_CONTENT, 3), EXPECTED_FILE_CONTENT);

    BOOST_CHECK(eErrorCode == EXPECTED_RESULT);
    BOOST_CHECK(bDestinationDirectoryExists);
    BOOST_CHECK(bSourceDirectoryDoesntExist);
    BOOST_CHECK(bContentExists);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the source path does not refer to a directory.
/// </summary>
ZTEST_CASE ( Move_AssertionFailsWhenSourcePathIsNotDirectory_Test )
{
    // Assuming the existence of:
    // -./NotADirectory.txt

    // [Preparation]
    const Path SOURCE_DIRECTORY(PATH_TO_ARTIFACTS + "./NotADirectory.txt");
    const Path DESTINATION_DIRECTORY(PATH_TO_ARTIFACTS + "./");
    bool bAssertionFailed = false;

    // [Execution]
    try
    {
        SDirectory::Move(SOURCE_DIRECTORY, DESTINATION_DIRECTORY, true);
    }
    catch(const AssertException&)
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
    // -./NotADirectory.txt

    // [Preparation]
    const Path SOURCE_DIRECTORY(PATH_TO_ARTIFACTS + "./");
    const Path DESTINATION_DIRECTORY(PATH_TO_ARTIFACTS + "./NotADirectory.txt");
    bool bAssertionFailed = false;

    // [Execution]
    try
    {
        SDirectory::Move(SOURCE_DIRECTORY, DESTINATION_DIRECTORY, true);
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
/// Checks that it returns DoesNotExist when the source directory does not exist.
/// </summary>
ZTEST_CASE ( Rename_SourceDirectoryDoesNotExist_Test )
{
    // [Preparation]
    const Path EXPECTED_NEW_DIRECTORY(PATH_TO_ARTIFACTS + "./XXXThisDirectoryDoesNotExistXXX/");
    Path sourceDirectory = EXPECTED_NEW_DIRECTORY;
    const string_z NEW_NAME("RenamedDirectory");
    const EFileSystemError EXPECTED_RESULT = EFileSystemError::E_DoesNotExist;

    // [Execution]
    EFileSystemError eErrorCode = SDirectory::Rename(sourceDirectory, NEW_NAME);
    
    // [Verification]
    BOOST_CHECK(eErrorCode == EXPECTED_RESULT);
    BOOST_CHECK(sourceDirectory == EXPECTED_NEW_DIRECTORY);
}

/// <summary>
/// Checks that it returns AlreadyExists when there is already a directory with the same name.
/// </summary>
ZTEST_CASE ( Rename_ADirectoryWithSameNameAlreadyExists_Test )
{
    // [Preparation]
    SDirectory::Create(PATH_TO_ARTIFACTS, "ExistingRenamedDirectory");
    SDirectory::Create(PATH_TO_ARTIFACTS, "DirectoryToRename");
    const Path EXPECTED_NEW_DIRECTORY(PATH_TO_ARTIFACTS + "./DirectoryToRename/");
    Path sourceDirectory = EXPECTED_NEW_DIRECTORY;
    const string_z NEW_NAME("ExistingRenamedDirectory");
    const EFileSystemError EXPECTED_RESULT = EFileSystemError::E_AlreadyExists;

    // [Execution]
    EFileSystemError eErrorCode = SDirectory::Rename(sourceDirectory, NEW_NAME);
    
    // [Verification]
    BOOST_CHECK(eErrorCode == EXPECTED_RESULT);
    BOOST_CHECK(sourceDirectory == EXPECTED_NEW_DIRECTORY);
}

/// <summary>
/// Checks that it returns the new path whent he directory is successfully renamed.
/// </summary>
ZTEST_CASE ( Rename_ItReturnsNewPathWhenDirectoryIsRenamed_Test )
{
    // [Preparation]
    SDirectory::Create(PATH_TO_ARTIFACTS, "DirectoryToRename2");
    const Path EXPECTED_NEW_DIRECTORY(PATH_TO_ARTIFACTS + "./RenamedDirectory2/");
    Path sourceDirectory(PATH_TO_ARTIFACTS + "./DirectoryToRename2/");
    const string_z NEW_NAME("RenamedDirectory2");
    const EFileSystemError EXPECTED_RESULT = EFileSystemError::E_Success;

    // [Execution]
    EFileSystemError eErrorCode = SDirectory::Rename(sourceDirectory, NEW_NAME);
    
    // [Verification]
    EFileSystemError existsErrorCode = EFileSystemError::E_Success;
    bool bRenamedDirectoryExists = SDirectory::Exists(sourceDirectory, existsErrorCode);
    BOOST_CHECK(bRenamedDirectoryExists);
    BOOST_CHECK(eErrorCode == EXPECTED_RESULT);
    BOOST_CHECK(sourceDirectory == EXPECTED_NEW_DIRECTORY);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the source path does not refer to a directory.
/// </summary>
ZTEST_CASE ( Rename_AssertionFailsWhenSourcePathIsNotDirectory_Test )
{
    // Assuming the existence of:
    // -./NotADirectory.txt

    // [Preparation]
    Path sourceDirectory(PATH_TO_ARTIFACTS + "./NotADirectory.txt");
    const string_z NEW_NAME("RenamedDirectory");
    bool bAssertionFailed = false;

    // [Execution]
    try
    {
        SDirectory::Rename(sourceDirectory, NEW_NAME);
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
/// Checks that it returns DoesNotExist when the source directory does not exist.
/// </summary>
ZTEST_CASE ( Copy_SourceDirectoryDoesNotExist_Test )
{
    // [Preparation]
    const Path SOURCE_DIRECTORY(PATH_TO_ARTIFACTS + "./XXXThisDirectoryDoesNotExistXXX/");
    const Path DESTINATION_DIRECTORY(PATH_TO_ARTIFACTS + "./");
    const EFileSystemError EXPECTED_RESULT = EFileSystemError::E_DoesNotExist;

    // [Execution]
    EFileSystemError eErrorCode = SDirectory::Copy(SOURCE_DIRECTORY, DESTINATION_DIRECTORY, true);
    
    // [Verification]
    BOOST_CHECK(eErrorCode == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns DoesNotExist when the destination directory does not exist.
/// </summary>
ZTEST_CASE ( Copy_DestinationDirectoryDoesNotExist_Test )
{
    // [Preparation]
    const Path SOURCE_DIRECTORY(PATH_TO_ARTIFACTS + "./");
    const Path DESTINATION_DIRECTORY(PATH_TO_ARTIFACTS + "./XXXThisDirectoryDoesNotExistXXX/");
    const EFileSystemError EXPECTED_RESULT = EFileSystemError::E_DoesNotExist;

    // [Execution]
    EFileSystemError eErrorCode = SDirectory::Copy(SOURCE_DIRECTORY, DESTINATION_DIRECTORY, true);
    
    // [Verification]
    BOOST_CHECK(eErrorCode == EXPECTED_RESULT);
}

/// <summary>
/// Checks that source directory and its content are copied when the destination has a directory with the same name and the replace flag is True.
/// </summary>
ZTEST_CASE ( Copy_SourceDirectoryAndContentAreCopiedWhenDestinationHasContentWithSameNameAndReplaceIsTrue_Test )
{
    // Assuming the existence of:
    // -./DirectoryToCopy/
    // -./DirectoryToCopy/Content1/
    // -./DirectoryToCopy/Content2.txt
    // -./DirectoryToCopy/Content1/Content3.txt
    // -./CopyDestinationWithSameDirectory/
    // -./CopyDestinationWithSameDirectory/DirectoryToCopy/
    // -./CopyDestinationWithSameDirectory/DirectoryToCopy/Content1/
    // -./CopyDestinationWithSameDirectory/DirectoryToCopy/Content2.txt
    // -./CopyDestinationWithSameDirectory/DirectoryToCopy/Content1/Content3.txt

    // [Preparation]
    const Path SOURCE_DIRECTORY(PATH_TO_ARTIFACTS + "./DirectoryToCopy/");
    const Path DESTINATION_DIRECTORY(PATH_TO_ARTIFACTS + "./CopyDestinationWithSameDirectory/");
    const Path EXPECTED_DIRECTORY(PATH_TO_ARTIFACTS + "./CopyDestinationWithSameDirectory/DirectoryToCopy/");
    const Path EXPECTED_CONTENT[] = { Path(PATH_TO_ARTIFACTS + "./CopyDestinationWithSameDirectory/DirectoryToCopy/Content1/"),
                                       Path(PATH_TO_ARTIFACTS + "./CopyDestinationWithSameDirectory/DirectoryToCopy/Content2.txt"),
                                       Path(PATH_TO_ARTIFACTS + "./CopyDestinationWithSameDirectory/DirectoryToCopy/Content1/Content3.txt") };
    const string_z EXPECTED_FILE_CONTENT("COPIED");
    const EFileSystemError EXPECTED_RESULT = EFileSystemError::E_Success;
    const bool INPUT_REPLACE = true;

    // [Execution]
    EFileSystemError eErrorCode = SDirectory::Copy(SOURCE_DIRECTORY, DESTINATION_DIRECTORY, INPUT_REPLACE);
    
    // [Verification]
    WaitForCreationOrDeletion_SDirectoryTestHelper(EXPECTED_DIRECTORY, false);

    EFileSystemError existsErrorCode = EFileSystemError::E_Success;
    bool bDestinationDirectoryExists = SDirectory::Exists(EXPECTED_DIRECTORY, existsErrorCode);
    bool bSourceDirectoryStillExists = SDirectory::Exists(SOURCE_DIRECTORY, existsErrorCode);
    bool bContentExists = CheckDirectoryContent(ArrayBasic<const Path>(EXPECTED_CONTENT, 3), EXPECTED_FILE_CONTENT);

    BOOST_CHECK(eErrorCode == EXPECTED_RESULT);
    BOOST_CHECK(bDestinationDirectoryExists);
    BOOST_CHECK(bSourceDirectoryStillExists);
    BOOST_CHECK(bContentExists);
}

/// <summary>
/// Checks that source directory is copied without replacing content when the destination has a directory with the same name and the replace flag is False.
/// </summary>
ZTEST_CASE ( Copy_SourceDirectoryIsCopiedWithoutReplacingWhenDestinationHasContentWithSameNameAndReplaceIsFalse_Test )
{
    // Assuming the existence of:
    // -./DirectoryToCopy2/
    // -./DirectoryToCopy2/Content1/
    // -./DirectoryToCopy2/Content2.txt
    // -./DirectoryToCopy2/Content1/Content3.txt
    // -./CopyDestinationWithSameDirectory2/
    // -./CopyDestinationWithSameDirectory2/DirectoryToCopy/
    // -./CopyDestinationWithSameDirectory2/DirectoryToCopy/Content1/
    // -./CopyDestinationWithSameDirectory2/DirectoryToCopy/Content1/Content3.txt

    // [Preparation]
    const Path SOURCE_DIRECTORY(PATH_TO_ARTIFACTS + "./DirectoryToCopy2/");
    const Path DESTINATION_DIRECTORY(PATH_TO_ARTIFACTS + "./CopyDestinationWithSameDirectory2/");
    const Path EXPECTED_CONTENT[] = { Path(PATH_TO_ARTIFACTS + "./CopyDestinationWithSameDirectory2/DirectoryToCopy2/Content1/Content3.txt") };
    const string_z EXPECTED_NOT_REPLACED_FILE_CONTENT = string_z::GetEmpty();
    const Path EXPECTED_NEW_CONTENT[] = {  Path(PATH_TO_ARTIFACTS + "./CopyDestinationWithSameDirectory2/DirectoryToCopy2/Content2.txt") };
    const string_z EXPECTED_COPIED_FILE_CONTENT("COPIED");
    
    const EFileSystemError EXPECTED_RESULT = EFileSystemError::E_AlreadyExists;
    const bool INPUT_REPLACE = false;

    // [Execution]
    EFileSystemError eErrorCode = SDirectory::Copy(SOURCE_DIRECTORY, DESTINATION_DIRECTORY, INPUT_REPLACE);
    
    // [Verification]
    EFileSystemError existsErrorCode = EFileSystemError::E_Success;
    bool bDestinationFileContentHasNotChanged = CheckDirectoryContent(ArrayBasic<const Path>(EXPECTED_CONTENT, 1), EXPECTED_NOT_REPLACED_FILE_CONTENT);
    bool bNotExistingFilesHaveBeenCopied = CheckDirectoryContent(ArrayBasic<const Path>(EXPECTED_NEW_CONTENT, 1), EXPECTED_COPIED_FILE_CONTENT);
    bool bSourceDirectoryStillExists = SDirectory::Exists(SOURCE_DIRECTORY, existsErrorCode);

    BOOST_CHECK(eErrorCode == EXPECTED_RESULT);
    BOOST_CHECK(bSourceDirectoryStillExists);
    BOOST_CHECK(bNotExistingFilesHaveBeenCopied);
    BOOST_CHECK(bDestinationFileContentHasNotChanged);
}

/// <summary>
/// Checks that source directory and its content are copied when the destination has a directory with the same name and the replace flag is False.
/// </summary>
ZTEST_CASE ( Copy_SourceDirectoryAndContentAreCopydWhenDestinationIsEmptyAndReplaceIsFalse_Test )
{
    // Assuming the existence of:
    // -./DirectoryToCopy3/
    // -./DirectoryToCopy3/Content1/
    // -./DirectoryToCopy3/Content2.txt
    // -./DirectoryToCopy3/Content1/Content3.txt

    // [Preparation]
    const Path SOURCE_DIRECTORY(PATH_TO_ARTIFACTS + "./DirectoryToCopy3/");
    const Path DESTINATION_DIRECTORY(PATH_TO_ARTIFACTS + "./CopyDestinationEmpty/");
    const Path EXPECTED_DIRECTORY(PATH_TO_ARTIFACTS + "./CopyDestinationEmpty/DirectoryToCopy3/");
    const Path EXPECTED_CONTENT[] = { Path(PATH_TO_ARTIFACTS + "./CopyDestinationEmpty/DirectoryToCopy3/Content1/"),
                                       Path(PATH_TO_ARTIFACTS + "./CopyDestinationEmpty/DirectoryToCopy3/Content2.txt"),
                                       Path(PATH_TO_ARTIFACTS + "./CopyDestinationEmpty/DirectoryToCopy3/Content1/Content3.txt") };
    const string_z EXPECTED_FILE_CONTENT("COPIED");
    const EFileSystemError EXPECTED_RESULT = EFileSystemError::E_Success;
    const bool INPUT_REPLACE = true;
    
    // Assures that the directory exists
    Path parentDirectory = DESTINATION_DIRECTORY;
    parentDirectory.RemoveLastDirectory();
    SDirectory::Create(parentDirectory, "CopyDestinationEmpty");

    // [Execution]
    EFileSystemError eErrorCode = SDirectory::Copy(SOURCE_DIRECTORY, DESTINATION_DIRECTORY, INPUT_REPLACE);
    
    // [Verification]
    WaitForCreationOrDeletion_SDirectoryTestHelper(EXPECTED_DIRECTORY, false);

    EFileSystemError existsErrorCode = EFileSystemError::E_Success;
    bool bDestinationDirectoryExists = SDirectory::Exists(EXPECTED_DIRECTORY, existsErrorCode);
    bool bSourceDirectoryStillExists = SDirectory::Exists(SOURCE_DIRECTORY, existsErrorCode);
    bool bContentExists = CheckDirectoryContent(ArrayBasic<const Path>(EXPECTED_CONTENT, 3), EXPECTED_FILE_CONTENT);

    BOOST_CHECK(eErrorCode == EXPECTED_RESULT);
    BOOST_CHECK(bDestinationDirectoryExists);
    BOOST_CHECK(bSourceDirectoryStillExists);
    BOOST_CHECK(bContentExists);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the source path does not refer to a directory.
/// </summary>
ZTEST_CASE ( Copy_AssertionFailsWhenSourcePathIsNotDirectory_Test )
{
    // Assuming the existence of:
    // -./NotADirectory.txt

    // [Preparation]
    const Path SOURCE_DIRECTORY(PATH_TO_ARTIFACTS + "./NotADirectory.txt");
    const Path DESTINATION_DIRECTORY(PATH_TO_ARTIFACTS + "./");
    bool bAssertionFailed = false;

    // [Execution]
    try
    {
        SDirectory::Copy(SOURCE_DIRECTORY, DESTINATION_DIRECTORY, true);
    }
    catch(const AssertException&)
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
    // -./NotADirectory.txt

    // [Preparation]
    const Path SOURCE_DIRECTORY(PATH_TO_ARTIFACTS + "./");
    const Path DESTINATION_DIRECTORY(PATH_TO_ARTIFACTS + "./NotADirectory.txt");
    bool bAssertionFailed = false;

    // [Execution]
    try
    {
        SDirectory::Copy(SOURCE_DIRECTORY, DESTINATION_DIRECTORY, true);
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
/// Checks that it returns an existing path.
/// </summary>
ZTEST_CASE ( GetCurrentWorkingDirectory_ReturnsExistingPath_Test )
{
    // [Preparation]
    
    // [Execution]
    Path currentDir = SDirectory::GetCurrentWorkingDirectory();
    
    // [Verification]
    EFileSystemError eErrorCode = EFileSystemError::E_Success;
    bool bExists = SDirectory::Exists(currentDir, eErrorCode);
    BOOST_CHECK(bExists);
}

/// <summary>
/// Checks that it returns an absolute path.
/// </summary>
ZTEST_CASE ( GetCurrentWorkingDirectory_ReturnsAbsolutePath_Test )
{
    // [Preparation]
    
    // [Execution]
    Path currentDir = SDirectory::GetCurrentWorkingDirectory();
    
    // [Verification]
    bool bIsAbsolute = currentDir.IsAbsolute();
    BOOST_CHECK(bIsAbsolute);
}

/// <summary>
/// Checks that the path is correctly stored when it exists.
/// </summary>
ZTEST_CASE ( SetCurrentWorkingDirectory_PathIsCorrectlyStoredWhenItExists_Test )
{
    // [Preparation]
    SDirectory::Create(PATH_TO_ARTIFACTS, "ExistingPath");
    const Path ORIGINAL_CWD = SDirectory::GetCurrentWorkingDirectory();
    const Path NEW_CWD(ORIGINAL_CWD.ToString() + PATH_TO_ARTIFACTS + "./ExistingPath/");
    const EFileSystemError EXPECTED_ERROR_CODE = EFileSystemError::E_Success;
    EFileSystemError eErrorCode = EFileSystemError::E_Success;

    // [Execution]
    SDirectory::SetCurrentWorkingDirectory(NEW_CWD, eErrorCode);
    
    // [Verification]
    Path currentDir = SDirectory::GetCurrentWorkingDirectory();
    BOOST_CHECK(currentDir == NEW_CWD);
    BOOST_CHECK(eErrorCode == EXPECTED_ERROR_CODE);

    // [Cleaning]
    SDirectory::SetCurrentWorkingDirectory(ORIGINAL_CWD, eErrorCode);
}

/// <summary>
/// Checks that the path is not stored when it does not exist.
/// </summary>
ZTEST_CASE ( SetCurrentWorkingDirectory_PathIsNotStoredWhenItDoesNotExist_Test )
{
    // [Preparation]
    const Path ORIGINAL_CWD = SDirectory::GetCurrentWorkingDirectory();
    const Path NEW_CWD(PATH_TO_ARTIFACTS + "./NotExistingPath/");
    const EFileSystemError EXPECTED_ERROR_CODE = EFileSystemError::E_DoesNotExist;
    EFileSystemError eErrorCode = EFileSystemError::E_Success;

    // [Execution]
    SDirectory::SetCurrentWorkingDirectory(NEW_CWD, eErrorCode);
    
    // [Verification]
    Path currentDir = SDirectory::GetCurrentWorkingDirectory();
    BOOST_CHECK(currentDir == ORIGINAL_CWD);
    BOOST_CHECK(eErrorCode == EXPECTED_ERROR_CODE);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input path does not refer to a directory.
/// </summary>
ZTEST_CASE ( SetCurrentWorkingDirectory_AssertionFailsWhenInputPathIsNotDirectory_Test )
{
    // Assuming the existence of:
    // -./NotADirectory.txt

    // [Preparation]
    const Path NOT_A_DIRECTORY(PATH_TO_ARTIFACTS + "./NotADirectory.txt");
    EFileSystemError eErrorCode = EFileSystemError::E_Success;
    bool bAssertionFailed = false;

    // [Execution]
    try
    {
        SDirectory::SetCurrentWorkingDirectory(NOT_A_DIRECTORY, eErrorCode);
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
/// Checks that it returns False when the directory does not exist.
/// </summary>
ZTEST_CASE ( Exists_ReturnsFalseWhenDirectoryDoesNotExist_Test )
{
    // [Preparation]
    const Path DIRECTORY(PATH_TO_ARTIFACTS + "./XXXThisDirectoryDoesNotExistXXX/");
    const bool EXPECTED_VALUE = false;
    const EFileSystemError EXPECTED_ERRORCODE = EFileSystemError::E_Success;
    EFileSystemError eErrorCode = EFileSystemError::E_Success;

    // [Execution]
    bool bReturnedValue = SDirectory::Exists(DIRECTORY, eErrorCode);
    
    // [Verification]
    BOOST_CHECK(eErrorCode == EXPECTED_ERRORCODE);
    BOOST_CHECK_EQUAL(bReturnedValue, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns True when the directory exists.
/// </summary>
ZTEST_CASE ( Exists_ReturnsTrueWhenDirectoryExists_Test )
{
    // [Preparation]
    SDirectory::Create(PATH_TO_ARTIFACTS, "ExistingPath");
    const Path DIRECTORY(PATH_TO_ARTIFACTS + "./ExistingPath/");
    const bool EXPECTED_VALUE = true;
    const EFileSystemError EXPECTED_ERRORCODE = EFileSystemError::E_Success;
    EFileSystemError eErrorCode = EFileSystemError::E_Success;

    // [Execution]
    bool bReturnedValue = SDirectory::Exists(DIRECTORY, eErrorCode);
    
    // [Verification]
    BOOST_CHECK(eErrorCode == EXPECTED_ERRORCODE);
    BOOST_CHECK_EQUAL(bReturnedValue, EXPECTED_VALUE);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input path does not refer to a directory.
/// </summary>
ZTEST_CASE ( Exists_AssertionFailsWhenInputPathIsNotDirectory_Test )
{
    // Assuming the existence of:
    // -./NotADirectory.txt

    // [Preparation]
    const Path NOT_A_DIRECTORY(PATH_TO_ARTIFACTS + "./NotADirectory.txt");
    bool bAssertionFailed = false;

    // [Execution]
    try
    {
        EFileSystemError eErrorCode = EFileSystemError::E_Success;
        SDirectory::Exists(NOT_A_DIRECTORY, eErrorCode);
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
/// Checks that it returns DoesNotExist when the directory does not exist.
/// </summary>
ZTEST_CASE ( GetDirectoryInfo_DirectoryDoesNotExist_Test )
{
    // [Preparation]
    const Path DIRECTORY(PATH_TO_ARTIFACTS + "./XXXThisDirectoryDoesNotExistXXX/");

    const EFileSystemError EXPECTED_ERRORCODE = EFileSystemError::E_DoesNotExist;
    EFileSystemError eErrorCode = EFileSystemError::E_DoesNotExist;

    // [Execution]
    DirectoryInfo dirInfo = SDirectory::GetDirectoryInfo(DIRECTORY, eErrorCode);
    
    // [Verification]
    BOOST_CHECK(eErrorCode == EXPECTED_ERRORCODE);
}

/// <summary>
/// Checks that it returns expected information when the directory exists.
/// </summary>
ZTEST_CASE ( GetDirectoryInfo_ReturnsExpectedInformationWhenDirectoryExists_Test )
{
    // [Preparation]
    SDirectory::Create(PATH_TO_ARTIFACTS, "ExistingPath");
    const Path DIRECTORY(PATH_TO_ARTIFACTS + "./ExistingPath/");
    const EFileSystemError EXPECTED_ERRORCODE = EFileSystemError::E_Success;
    EFileSystemError eErrorCode = EFileSystemError::E_Success;

    // [Execution]
    DirectoryInfo dirInfo = SDirectory::GetDirectoryInfo(DIRECTORY, eErrorCode);
    
    // [Verification]
    bool bContainsCorrectPath = dirInfo.GetPath() == DIRECTORY;
    bool bCreationDateTimeIsNotUndefined = !dirInfo.GetCreationDate().IsUndefined();
    
    BOOST_CHECK(eErrorCode == EXPECTED_ERRORCODE);
    BOOST_CHECK(bContainsCorrectPath);
    BOOST_CHECK(bCreationDateTimeIsNotUndefined);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input path does not refer to a directory.
/// </summary>
ZTEST_CASE ( GetDirectoryInfo_AssertionFailsWhenInputPathIsNotDirectory_Test )
{
    // Assuming the existence of:
    // -./NotADirectory.txt

    // [Preparation]
    const Path NOT_A_DIRECTORY(PATH_TO_ARTIFACTS + "./NotADirectory.txt");
    bool bAssertionFailed = false;

    // [Execution]
    try
    {
        EFileSystemError eErrorCode = EFileSystemError::E_Success;
        SDirectory::GetDirectoryInfo(NOT_A_DIRECTORY, eErrorCode);
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
/// Checks that it returns Success and the directory is created when the input directory exists and the new directory does not exist.
/// </summary>
ZTEST_CASE ( Create_ReturnsSuccessWhenInputDirectoryExistsAndNewDirectoryDoesNotExist_Test )
{
    // [Preparation]
    const Path DIRECTORY(PATH_TO_ARTIFACTS + "./");
    const string_z NEW_DIRECTORY_NAME("NewDirectory");
    Path EXPECTED_DIRECTORY(DIRECTORY);
    EXPECTED_DIRECTORY.AppendDirectory(NEW_DIRECTORY_NAME);
    const EFileSystemError EXPECTED_ERRORCODE = EFileSystemError::E_Success;
    EFileSystemError eErrorCode = EFileSystemError::E_Success;

    // [Execution]
    eErrorCode = SDirectory::Create(DIRECTORY, NEW_DIRECTORY_NAME);
    
    // [Verification]
    WaitForCreationOrDeletion_SDirectoryTestHelper(EXPECTED_DIRECTORY, false);
    
    EFileSystemError existsErrorCode = EFileSystemError::E_Success;
    bool bDirectoryWasCreated = SDirectory::Exists(EXPECTED_DIRECTORY, existsErrorCode);
    BOOST_CHECK(bDirectoryWasCreated);
    BOOST_CHECK(eErrorCode == EXPECTED_ERRORCODE);
}

/// <summary>
/// Checks that it returns Success and the directory is created when the input directory exists and the new directory already exists.
/// </summary>
ZTEST_CASE ( Create_ReturnsSuccessWhenInputDirectoryExistsAndNewDirectoryAlreadyExists_Test )
{
    // Assumes the existence of:
    // -./ExistingPath/

    // [Preparation]
    const Path DIRECTORY(PATH_TO_ARTIFACTS + "./");
    const string_z NEW_DIRECTORY_NAME("ExistingPath");
    Path EXPECTED_DIRECTORY(DIRECTORY);
    EXPECTED_DIRECTORY.AppendDirectory(NEW_DIRECTORY_NAME);
    const EFileSystemError EXPECTED_ERRORCODE = EFileSystemError::E_Success;
    EFileSystemError eErrorCode = EFileSystemError::E_Success;

    // [Execution]
    eErrorCode = SDirectory::Create(DIRECTORY, NEW_DIRECTORY_NAME);
    
    // [Verification]
    BOOST_CHECK(eErrorCode == EXPECTED_ERRORCODE);
}

/// <summary>
/// Checks that it returns DoesNotExist when the input directory does not exist.
/// </summary>
ZTEST_CASE ( Create_ReturnsDoesNotExistWhenInputDirectoryExistsAndNewDirectoryAlreadyExists_Test )
{
    // [Preparation]
    const Path DIRECTORY(PATH_TO_ARTIFACTS + "./NonExistingPath/");
    const string_z NEW_DIRECTORY_NAME("Whatever");
    Path EXPECTED_DIRECTORY(DIRECTORY);
    EXPECTED_DIRECTORY.AppendDirectory(NEW_DIRECTORY_NAME);
    const EFileSystemError EXPECTED_ERRORCODE = EFileSystemError::E_DoesNotExist;
    EFileSystemError eErrorCode = EFileSystemError::E_Success;

    // [Execution]
    eErrorCode = SDirectory::Create(DIRECTORY, NEW_DIRECTORY_NAME);
    
    // [Verification]
    BOOST_CHECK(eErrorCode == EXPECTED_ERRORCODE);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input path does not refer to a directory.
/// </summary>
ZTEST_CASE ( Create_AssertionFailsWhenInputPathIsNotDirectory_Test )
{
    // Assuming the existence of:
    // -./NotADirectory.txt

    // [Preparation]
    const Path NOT_A_DIRECTORY(PATH_TO_ARTIFACTS + "./NotADirectory.txt");
    bool bAssertionFailed = false;

    // [Execution]
    try
    {
        SDirectory::Create(NOT_A_DIRECTORY, "DirectoryName");
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
/// Checks that it returns Success and fills the container with expected file paths when the input directory exists.
/// </summary>
ZTEST_CASE ( GetFiles1_ReturnsSuccessAndExpectedFilesWhenInputDirectoryExists_Test )
{
    // Assumes the existence of:
    // -./DirectoryWithContent/
    // -./DirectoryWithContent/Directory1/
    // -./DirectoryWithContent/Directory1/File3.txt
    // -./DirectoryWithContent/Directory2/
    // -./DirectoryWithContent/File1.txt
    // -./DirectoryWithContent/File2.txt
    // -./DirectoryWithContent/File4.log

    // [Preparation]
    const Path DIRECTORY(PATH_TO_ARTIFACTS + "./DirectoryWithContent/");
    const EFileSystemError EXPECTED_ERRORCODE = EFileSystemError::E_Success;
    EFileSystemError eErrorCode = EFileSystemError::E_Success;
    ArrayDynamic<string_z> EXPECTED_FILES;
    EXPECTED_FILES.Add("File1.txt");
    EXPECTED_FILES.Add("File2.txt");
    EXPECTED_FILES.Add("File4.log");

    ArrayDynamic<Path> arFiles;

    // [Execution]
    eErrorCode = SDirectory::GetFiles(DIRECTORY, arFiles);
    
    // [Verification]
    bool bAllExpectedFilesRetrieved = true;

    for(puint_z i = 0; i < sizeof(EXPECTED_FILES) / sizeof(string_z); ++i)
        bAllExpectedFilesRetrieved = bAllExpectedFilesRetrieved && EXPECTED_FILES.Contains(arFiles[i].GetFilename());
    
    BOOST_CHECK(bAllExpectedFilesRetrieved);
    BOOST_CHECK(eErrorCode == EXPECTED_ERRORCODE);
}

/// <summary>
/// Checks that found file paths are appended to the existing elements in the container.
/// </summary>
ZTEST_CASE ( GetFiles1_PathsAreAppended_Test )
{
    // Assumes the existence of:
    // -./DirectoryWithContent/
    // -./DirectoryWithContent/Directory1/
    // -./DirectoryWithContent/Directory1/File3.txt
    // -./DirectoryWithContent/Directory2/
    // -./DirectoryWithContent/File1.txt
    // -./DirectoryWithContent/File2.txt
    // -./DirectoryWithContent/File4.log

    // [Preparation]
    const Path DIRECTORY(PATH_TO_ARTIFACTS + "./DirectoryWithContent/");
    const EFileSystemError EXPECTED_ERRORCODE = EFileSystemError::E_Success;
    EFileSystemError eErrorCode = EFileSystemError::E_Success;
    ArrayDynamic<string_z> EXPECTED_FILES;
    EXPECTED_FILES.Add("ExistingElement1");
    EXPECTED_FILES.Add("ExistingElement2");
    EXPECTED_FILES.Add("File1.txt");
    EXPECTED_FILES.Add("File2.txt");
    EXPECTED_FILES.Add("File4.log");

    ArrayDynamic<Path> arFiles;
    arFiles.Add(Path("ExistingElement1"));
    arFiles.Add(Path("ExistingElement2"));

    // [Execution]
    eErrorCode = SDirectory::GetFiles(DIRECTORY, arFiles);
    
    // [Verification]
    bool bAllExpectedFilesRetrieved = true;

    for(puint_z i = 0; i < sizeof(EXPECTED_FILES) / sizeof(string_z); ++i)
        bAllExpectedFilesRetrieved = bAllExpectedFilesRetrieved && EXPECTED_FILES.Contains(arFiles[i].GetFilename());
    
    BOOST_CHECK(bAllExpectedFilesRetrieved);
    BOOST_CHECK(eErrorCode == EXPECTED_ERRORCODE);
}

/// <summary>
/// Checks that it returns Success when the directory is empty.
/// </summary>
ZTEST_CASE ( GetFiles1_ReturnsSuccessWhenDirectoryIsEmpty_Test )
{
    // [Preparation]
    SDirectory::Create(PATH_TO_ARTIFACTS, "EmptyDirectory");
    const Path DIRECTORY(PATH_TO_ARTIFACTS + "./EmptyDirectory/");
    const EFileSystemError EXPECTED_ERRORCODE = EFileSystemError::E_Success;
    EFileSystemError eErrorCode = EFileSystemError::E_Success;
    ArrayDynamic<Path> arFiles;

    // [Execution]
    eErrorCode = SDirectory::GetFiles(DIRECTORY, arFiles);
    
    // [Verification]
    BOOST_CHECK(eErrorCode == EXPECTED_ERRORCODE);
    BOOST_CHECK(arFiles.IsEmpty());
}

/// <summary>
/// Checks that it returns DoesNotExist when the directory does not exist.
/// </summary>
ZTEST_CASE ( GetFiles1_ReturnsDoesNotExistWhenTheDirectoryDoesNotExist_Test )
{
    // [Preparation]
    const Path DIRECTORY(PATH_TO_ARTIFACTS + "./NonExistentDirectory/");
    const EFileSystemError EXPECTED_ERRORCODE = EFileSystemError::E_DoesNotExist;
    EFileSystemError eErrorCode = EFileSystemError::E_Success;
    ArrayDynamic<Path> arFiles;

    // [Execution]
    eErrorCode = SDirectory::GetFiles(DIRECTORY, arFiles);
    
    // [Verification]
    BOOST_CHECK(eErrorCode == EXPECTED_ERRORCODE);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input path does not refer to a directory.
/// </summary>
ZTEST_CASE ( GetFiles1_AssertionFailsWhenInputPathIsNotDirectory_Test )
{
    // Assuming the existence of:
    // -./NotADirectory.txt

    // [Preparation]
    const Path NOT_A_DIRECTORY(PATH_TO_ARTIFACTS + "./NotADirectory.txt");
    ArrayDynamic<Path> arFiles;
    bool bAssertionFailed = false;

    // [Execution]
    try
    {
        SDirectory::GetFiles(NOT_A_DIRECTORY, arFiles);
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
/// Checks that it returns Success and fills the container with expected file paths when the input directory exists.
/// </summary>
ZTEST_CASE ( GetFiles2_ReturnsSuccessAndExpectedFilesWhenInputDirectoryExists_Test )
{
    // Assumes the existence of:
    // -./DirectoryWithContent/
    // -./DirectoryWithContent/Directory1/
    // -./DirectoryWithContent/Directory1/File3.txt
    // -./DirectoryWithContent/Directory2/
    // -./DirectoryWithContent/File1.txt
    // -./DirectoryWithContent/File2.txt
    // -./DirectoryWithContent/File4.log

    // [Preparation]
    const string_z EXTENSION_FILTER("txt");
    const Path DIRECTORY(PATH_TO_ARTIFACTS + "./DirectoryWithContent/");
    const EFileSystemError EXPECTED_ERRORCODE = EFileSystemError::E_Success;
    EFileSystemError eErrorCode = EFileSystemError::E_Success;
    ArrayDynamic<string_z> EXPECTED_FILES;
    EXPECTED_FILES.Add("File1.txt");
    EXPECTED_FILES.Add("File2.txt");

    ArrayDynamic<Path> arFiles;

    // [Execution]
    eErrorCode = SDirectory::GetFiles(DIRECTORY, arFiles, EXTENSION_FILTER);
    
    // [Verification]
    bool bAllExpectedFilesRetrieved = true;

    for(puint_z i = 0; i < sizeof(EXPECTED_FILES) / sizeof(string_z); ++i)
        bAllExpectedFilesRetrieved = bAllExpectedFilesRetrieved && EXPECTED_FILES.Contains(arFiles[i].GetFilename());
    
    BOOST_CHECK(bAllExpectedFilesRetrieved);
    BOOST_CHECK(eErrorCode == EXPECTED_ERRORCODE);
}

/// <summary>
/// Checks that found file paths are appended to the existing elements in the container.
/// </summary>
ZTEST_CASE ( GetFiles2_PathsAreAppended_Test )
{
    // Assumes the existence of:
    // -./DirectoryWithContent/
    // -./DirectoryWithContent/Directory1/
    // -./DirectoryWithContent/Directory1/File3.txt
    // -./DirectoryWithContent/Directory2/
    // -./DirectoryWithContent/File1.txt
    // -./DirectoryWithContent/File2.txt
    // -./DirectoryWithContent/File4.log

    // [Preparation]
    const string_z EXTENSION_FILTER("txt");
    const Path DIRECTORY(PATH_TO_ARTIFACTS + "./DirectoryWithContent/");
    const EFileSystemError EXPECTED_ERRORCODE = EFileSystemError::E_Success;
    EFileSystemError eErrorCode = EFileSystemError::E_Success;
    ArrayDynamic<string_z> EXPECTED_FILES;
    EXPECTED_FILES.Add("ExistingElement1");
    EXPECTED_FILES.Add("ExistingElement2");
    EXPECTED_FILES.Add("File1.txt");
    EXPECTED_FILES.Add("File2.txt");

    ArrayDynamic<Path> arFiles;
    arFiles.Add(Path("ExistingElement1"));
    arFiles.Add(Path("ExistingElement2"));

    // [Execution]
    eErrorCode = SDirectory::GetFiles(DIRECTORY, arFiles, EXTENSION_FILTER);
    
    // [Verification]
    bool bAllExpectedFilesRetrieved = true;

    for(puint_z i = 0; i < sizeof(EXPECTED_FILES) / sizeof(string_z); ++i)
        bAllExpectedFilesRetrieved = bAllExpectedFilesRetrieved && EXPECTED_FILES.Contains(arFiles[i].GetFilename());
    
    BOOST_CHECK(bAllExpectedFilesRetrieved);
    BOOST_CHECK(eErrorCode == EXPECTED_ERRORCODE);
}

/// <summary>
/// Checks that it returns Success when the directory is empty.
/// </summary>
ZTEST_CASE ( GetFiles2_ReturnsSuccessWhenDirectoryIsEmpty_Test )
{
    // [Preparation]
    SDirectory::Create(PATH_TO_ARTIFACTS, "EmptyDirectory");
    const string_z EXTENSION_FILTER("txt");
    const Path DIRECTORY(PATH_TO_ARTIFACTS + "./EmptyDirectory/");
    const EFileSystemError EXPECTED_ERRORCODE = EFileSystemError::E_Success;
    EFileSystemError eErrorCode = EFileSystemError::E_Success;
    ArrayDynamic<Path> arFiles;

    // [Execution]
    eErrorCode = SDirectory::GetFiles(DIRECTORY, arFiles, EXTENSION_FILTER);
    
    // [Verification]
    BOOST_CHECK(eErrorCode == EXPECTED_ERRORCODE);
    BOOST_CHECK(arFiles.IsEmpty());
}

/// <summary>
/// Checks that it returns DoesNotExist when the directory does not exist.
/// </summary>
ZTEST_CASE ( GetFiles2_ReturnsDoesNotExistWhenTheDirectoryDoesNotExist_Test )
{
    // [Preparation]
    const string_z EXTENSION_FILTER("txt");
    const Path DIRECTORY(PATH_TO_ARTIFACTS + "./NonExistentDirectory/");
    const EFileSystemError EXPECTED_ERRORCODE = EFileSystemError::E_DoesNotExist;
    EFileSystemError eErrorCode = EFileSystemError::E_Success;
    ArrayDynamic<Path> arFiles;

    // [Execution]
    eErrorCode = SDirectory::GetFiles(DIRECTORY, arFiles, EXTENSION_FILTER);
    
    // [Verification]
    BOOST_CHECK(eErrorCode == EXPECTED_ERRORCODE);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input path does not refer to a directory.
/// </summary>
ZTEST_CASE ( GetFiles2_AssertionFailsWhenInputPathIsNotDirectory_Test )
{
    // Assuming the existence of:
    // -./NotADirectory.txt

    // [Preparation]
    const string_z EXTENSION_FILTER("txt");
    const Path NOT_A_DIRECTORY(PATH_TO_ARTIFACTS + "./NotADirectory.txt");
    ArrayDynamic<Path> arFiles;
    bool bAssertionFailed = false;

    // [Execution]
    try
    {
        SDirectory::GetFiles(NOT_A_DIRECTORY, arFiles, EXTENSION_FILTER);
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
/// Checks that it returns Success and fills the container with expected directory paths when the input directory exists.
/// </summary>
ZTEST_CASE ( GetSubdirectories_ReturnsSuccessAndExpectedDirectoriesWhenInputDirectoryExists_Test )
{
    // Assumes the existence of:
    // -./DirectoryWithContent/
    // -./DirectoryWithContent/Directory1/
    // -./DirectoryWithContent/Directory1/File3.txt
    // -./DirectoryWithContent/Directory2/
    // -./DirectoryWithContent/File1.txt
    // -./DirectoryWithContent/File2.txt
    // -./DirectoryWithContent/File4.log

    // [Preparation]
    const Path DIRECTORY(PATH_TO_ARTIFACTS + "./DirectoryWithContent/");
    const EFileSystemError EXPECTED_ERRORCODE = EFileSystemError::E_Success;
    EFileSystemError eErrorCode = EFileSystemError::E_Success;
    ArrayDynamic<string_z> EXPECTED_DIRS;
    EXPECTED_DIRS.Add("Directory1");
    EXPECTED_DIRS.Add("Directory2");

    ArrayDynamic<Path> arDirectories;

    // [Execution]
    eErrorCode = SDirectory::GetSubdirectories(DIRECTORY, arDirectories);
    
    // [Verification]
    bool bAllExpectedDirectoriesRetrieved = true;

    for(puint_z i = 0; i < sizeof(EXPECTED_DIRS) / sizeof(string_z); ++i)
        bAllExpectedDirectoriesRetrieved = bAllExpectedDirectoriesRetrieved && EXPECTED_DIRS.Contains(arDirectories[i].GetLastDirectory());
    
    BOOST_CHECK(bAllExpectedDirectoriesRetrieved);
    BOOST_CHECK(eErrorCode == EXPECTED_ERRORCODE);
}

/// <summary>
/// Checks that found directory paths are appended to the existing elements in the container.
/// </summary>
ZTEST_CASE ( GetSubdirectories_PathsAreAppended_Test )
{
    // Assumes the existence of:
    // -./DirectoryWithContent/
    // -./DirectoryWithContent/Directory1/
    // -./DirectoryWithContent/Directory1/File3.txt
    // -./DirectoryWithContent/Directory2/
    // -./DirectoryWithContent/File1.txt
    // -./DirectoryWithContent/File2.txt
    // -./DirectoryWithContent/File4.log

    // [Preparation]
    const Path DIRECTORY(PATH_TO_ARTIFACTS + "./DirectoryWithContent/");
    const EFileSystemError EXPECTED_ERRORCODE = EFileSystemError::E_Success;
    EFileSystemError eErrorCode = EFileSystemError::E_Success;
    ArrayDynamic<string_z> EXPECTED_DIRS;
    EXPECTED_DIRS.Add("ExistingElement1");
    EXPECTED_DIRS.Add("ExistingElement2");
    EXPECTED_DIRS.Add("Directory1");
    EXPECTED_DIRS.Add("Directory2");

    ArrayDynamic<Path> arDirectories;
    arDirectories.Add(Path("/ExistingElement1/"));
    arDirectories.Add(Path("/ExistingElement2/"));

    // [Execution]
    eErrorCode = SDirectory::GetSubdirectories(DIRECTORY, arDirectories);
    
    // [Verification]
    bool bAllExpectedDirectoriesRetrieved = true;

    for(puint_z i = 0; i < sizeof(EXPECTED_DIRS) / sizeof(string_z); ++i)
        bAllExpectedDirectoriesRetrieved = bAllExpectedDirectoriesRetrieved && EXPECTED_DIRS.Contains(arDirectories[i].GetLastDirectory());
    
    BOOST_CHECK(bAllExpectedDirectoriesRetrieved);
    BOOST_CHECK(eErrorCode == EXPECTED_ERRORCODE);
}

/// <summary>
/// Checks that it returns Success when the directory is empty.
/// </summary>
ZTEST_CASE ( GetSubdirectories_ReturnsSuccessWhenDirectoryIsEmpty_Test )
{
    // [Preparation]
    SDirectory::Create(PATH_TO_ARTIFACTS, "EmptyDirectory");
    const Path DIRECTORY(PATH_TO_ARTIFACTS + "./EmptyDirectory/");
    const EFileSystemError EXPECTED_ERRORCODE = EFileSystemError::E_Success;
    EFileSystemError eErrorCode = EFileSystemError::E_Success;
    ArrayDynamic<Path> arDirectories;

    // [Execution]
    eErrorCode = SDirectory::GetSubdirectories(DIRECTORY, arDirectories);
    
    // [Verification]
    BOOST_CHECK(eErrorCode == EXPECTED_ERRORCODE);
    BOOST_CHECK(arDirectories.IsEmpty());
}

/// <summary>
/// Checks that it returns DoesNotExist when the directory does not exist.
/// </summary>
ZTEST_CASE ( GetSubdirectories_ReturnsDoesNotExistWhenTheDirectoryDoesNotExist_Test )
{
    // [Preparation]
    const Path DIRECTORY(PATH_TO_ARTIFACTS + "./NonExistentDirectory/");
    const EFileSystemError EXPECTED_ERRORCODE = EFileSystemError::E_DoesNotExist;
    EFileSystemError eErrorCode = EFileSystemError::E_Success;
    ArrayDynamic<Path> arDirectories;

    // [Execution]
    eErrorCode = SDirectory::GetSubdirectories(DIRECTORY, arDirectories);
    
    // [Verification]
    BOOST_CHECK(eErrorCode == EXPECTED_ERRORCODE);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input path does not refer to a directory.
/// </summary>
ZTEST_CASE ( GetSubdirectories_AssertionFailsWhenInputPathIsNotDirectory_Test )
{
    // Assuming the existence of:
    // -./NotADirectory.txt

    // [Preparation]
    const Path NOT_A_DIRECTORY(PATH_TO_ARTIFACTS + "./NotADirectory.txt");
    ArrayDynamic<Path> arDirectories;
    bool bAssertionFailed = false;

    // [Execution]
    try
    {
        SDirectory::GetSubdirectories(NOT_A_DIRECTORY, arDirectories);
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
/// Checks that it returns Success when the directory exists and has parent.
/// </summary>
ZTEST_CASE ( GetParentDirectory_ReturnsSuccessWhenDirectoryExistsAndHasParent_Test )
{
    // Assumes the existence of:
    // -./DirectoryWithContent/
    // -./DirectoryWithContent/Directory1/

    // [Preparation]
    const Path DIRECTORY(Path(PATH_TO_ARTIFACTS + "./DirectoryWithContent/Directory1/").GetAbsolutePath());
    const EFileSystemError EXPECTED_ERRORCODE = EFileSystemError::E_Success;
    EFileSystemError eErrorCode = EFileSystemError::E_Success;
    const string_z EXPECTED_RELATIVE_PATH("./Directory1/");

    // [Execution]
    Path parentPath = SDirectory::GetParentDirectory(DIRECTORY, eErrorCode);
    
    // [Verification]
    BOOST_CHECK(eErrorCode == EXPECTED_ERRORCODE);
    BOOST_CHECK(parentPath.GetRelativePathTo(DIRECTORY) == EXPECTED_RELATIVE_PATH);
}

/// <summary>
/// Checks that it returns Success and the same path when the directory exists and does not have parent.
/// </summary>
ZTEST_CASE ( GetParentDirectory_ReturnsSuccessAndSamePathWhenDirectoryExistsAndDoesNotHaveParent_Test )
{
    // [Preparation]
    const Path DIRECTORY = SDirectory::GetCurrentWorkingDirectory().GetRoot();
    const EFileSystemError EXPECTED_ERRORCODE = EFileSystemError::E_Success;
    EFileSystemError eErrorCode = EFileSystemError::E_Success;
    const Path EXPECTED_PATH = DIRECTORY;

    // [Execution]
    Path parentPath = SDirectory::GetParentDirectory(DIRECTORY, eErrorCode);
    
    // [Verification]
    BOOST_CHECK(eErrorCode == EXPECTED_ERRORCODE);
    BOOST_CHECK(parentPath == EXPECTED_PATH);
}

/// <summary>
/// Checks that it returns DoesNotExist when the directory does not exist.
/// </summary>
ZTEST_CASE ( GetParentDirectory_ReturnsDoesNotExistWhenDirectoryDoesNotExist_Test )
{
    // [Preparation]
    const Path DIRECTORY(PATH_TO_ARTIFACTS + "./NonExistentDirectory/");
    const EFileSystemError EXPECTED_ERRORCODE = EFileSystemError::E_DoesNotExist;
    EFileSystemError eErrorCode = EFileSystemError::E_Success;
    const Path EXPECTED_PATH("./");

    // [Execution]
    Path parentPath = SDirectory::GetParentDirectory(DIRECTORY, eErrorCode);
    
    // [Verification]
    BOOST_CHECK(eErrorCode == EXPECTED_ERRORCODE);
    BOOST_CHECK(parentPath == EXPECTED_PATH);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input path does not refer to a directory.
/// </summary>
ZTEST_CASE ( GetParentDirectory_AssertionFailsWhenInputPathIsNotDirectory_Test )
{
    // Assuming the existence of:
    // -./NotADirectory.txt

    // [Preparation]
    const Path NOT_A_DIRECTORY(PATH_TO_ARTIFACTS + "./NotADirectory.txt");
    EFileSystemError eErrorCode = EFileSystemError::E_Success;
    bool bAssertionFailed = false;

    // [Execution]
    try
    {
        SDirectory::GetParentDirectory(NOT_A_DIRECTORY, eErrorCode);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }
    
    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif

// End - Test Suite: SDirectory
ZTEST_SUITE_END()
