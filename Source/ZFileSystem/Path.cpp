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

#include "ZFileSystem/Path.h"

#include "ZContainers/ArrayDynamic.h"
#include "ZCommon/DataTypes/ArrayResult.h"
#include "ZIO/Uri.h"
#include "ZFileSystem/SDirectory.h"



namespace z
{

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |  ATTRIBUTES INITIALIZATION |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

const string_z Path::PATH_SEPARATOR("/");
const char_z Path::PATH_SEPARATOR_CHAR('/');
const char_z Path::DOT('.');


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |       CONSTRUCTORS         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

Path::Path(const string_z &strPath)
{
    string_z strReplacedPath = strPath;

#if defined(Z_OS_WINDOWS)
    
    // On Windows, paths can be created using backslashes as segment separator. They have to be replaced with slashes.
    static const string_z BACK_SLASH("\\");
    if(strReplacedPath.Contains(BACK_SLASH, EComparisonType::E_BinaryCaseSensitive))
        strReplacedPath.Replace(BACK_SLASH, Path::PATH_SEPARATOR, EComparisonType::E_BinaryCaseSensitive);

#endif

    // The path can be preceded by the hostname
    string_z strHostname;
    Path::_ExtractHostnameFromPath(strReplacedPath, strHostname);

    if(!strHostname.IsEmpty())
        this->SetHostname(strHostname);

    // Gets the filename if any
    string_z strFilename;
    Path::_ExtractFilenameFromPath(strReplacedPath, strFilename);

    this->SetFilenameAndExtension(strFilename);
    this->SetDirectory(strReplacedPath);
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

void Path::_ResolveDotSegments(string_z &strPathToResolve)
{
    static const string_z FILE_SCHEME("file:");
    static const char_z CHAR_TILDE('~');

    string_z strFirstPart; // Stores the part of the path that is not affected by this operation (for example, the drive)
    string_z strRest;

#if defined(Z_OS_WINDOWS)

    const Path PATH_TO_RESOLVE(strPathToResolve);

    if(PATH_TO_RESOLVE.HasDrive())
    {
        // Extracts the drive part
        strFirstPart = PATH_TO_RESOLVE.GetRoot();
        strRest = strPathToResolve.Substring(strFirstPart.GetLength() + 1U); // +1 due to the colon (:)
    }
#else
    if(strPathToResolve[0] == CHAR_TILDE)
    {
        // Extracts the tilde (~)
        strFirstPart = CHAR_TILDE;
        strRest = strPathToResolve.Substring(strFirstPart.GetLength() + 1U); // +1 due to the colon (:)
    }
#endif
    else
    {
        strRest = strPathToResolve;
    }

    Uri uri(FILE_SCHEME + strRest);
    strRest = uri.GetPath();
    Uri::Decode(strRest, strRest);

    if(strFirstPart.IsEmpty())
    {
        strPathToResolve = strRest;
    }
    else
    {
        strPathToResolve = strFirstPart;
        strPathToResolve.Append(strRest);
    }
}

#if defined(Z_OS_WINDOWS)

void Path::_RemoveNotAllowedCharactersInPath(string_z &strPathToBeReplaced)
{
    // Windows's file system allows any UTF-16 character in path names but: NUL \ / : * ? " < > |
    static const string_z COLON(":");
    static const string_z ASTERISK("*");
    static const string_z QUESTION_MARK("?");
    static const string_z QUOTES("\"");
    static const string_z LOWER_THAN("<");
    static const string_z GREATER_THAN(">");
    static const string_z PIPE("|");

    Z_ASSERT_WARNING(!strPathToBeReplaced.Contains(ASTERISK,      EComparisonType::E_BinaryCaseSensitive) &&
                      !strPathToBeReplaced.Contains(QUESTION_MARK, EComparisonType::E_BinaryCaseSensitive) &&
                      !strPathToBeReplaced.Contains(QUOTES,        EComparisonType::E_BinaryCaseSensitive) &&
                      !strPathToBeReplaced.Contains(LOWER_THAN,    EComparisonType::E_BinaryCaseSensitive) &&
                      !strPathToBeReplaced.Contains(GREATER_THAN,  EComparisonType::E_BinaryCaseSensitive) &&
                      !strPathToBeReplaced.Contains(PIPE,          EComparisonType::E_BinaryCaseSensitive),
                      "Characters :  \\ / * ? \" < > | are not allowed.");

    if(strPathToBeReplaced.Contains(ASTERISK, EComparisonType::E_BinaryCaseSensitive))
        strPathToBeReplaced.Replace(ASTERISK, string_z::GetEmpty(), EComparisonType::E_BinaryCaseSensitive);

    if(strPathToBeReplaced.Contains(QUESTION_MARK, EComparisonType::E_BinaryCaseSensitive))
        strPathToBeReplaced.Replace(QUESTION_MARK, string_z::GetEmpty(), EComparisonType::E_BinaryCaseSensitive);

    if(strPathToBeReplaced.Contains(QUOTES, EComparisonType::E_BinaryCaseSensitive))
        strPathToBeReplaced.Replace(QUOTES, string_z::GetEmpty(), EComparisonType::E_BinaryCaseSensitive);

    if(strPathToBeReplaced.Contains(LOWER_THAN, EComparisonType::E_BinaryCaseSensitive))
        strPathToBeReplaced.Replace(LOWER_THAN, string_z::GetEmpty(), EComparisonType::E_BinaryCaseSensitive);

    if(strPathToBeReplaced.Contains(GREATER_THAN, EComparisonType::E_BinaryCaseSensitive))
        strPathToBeReplaced.Replace(GREATER_THAN, string_z::GetEmpty(), EComparisonType::E_BinaryCaseSensitive);

    if(strPathToBeReplaced.Contains(PIPE, EComparisonType::E_BinaryCaseSensitive))
        strPathToBeReplaced.Replace(PIPE, string_z::GetEmpty(), EComparisonType::E_BinaryCaseSensitive);

    // Colons are not allowed in path names, but Windows uses the concept of drives, which are specified using a colon
    // Therefore, this colon must be treated differently
    int nFirstSlashPosition = strPathToBeReplaced.IndexOf(Path::PATH_SEPARATOR, 0, EComparisonType::E_BinaryCaseSensitive);
    int nFirstColonPosition = strPathToBeReplaced.IndexOf(COLON, 0, EComparisonType::E_BinaryCaseSensitive);

    if(nFirstSlashPosition != string_z::PATTERN_NOT_FOUND && nFirstColonPosition != string_z::PATTERN_NOT_FOUND)
    {
        if(nFirstColonPosition > nFirstSlashPosition)
        {
            Z_ASSERT_WARNING(false, "Colons (\":\") are not allowed but for specifying drives.");

            // Replaces all colons
            strPathToBeReplaced.Replace(COLON, string_z::GetEmpty(), EComparisonType::E_BinaryCaseSensitive);
        }
        else
        {
            // Replaces all colons but first one (reserved for the drive)
            string_z strAfterDriveColon = strPathToBeReplaced.Substring(nFirstColonPosition + 1U, strPathToBeReplaced.GetLength() - 1U);

            if(strAfterDriveColon.Contains(COLON, EComparisonType::E_BinaryCaseSensitive))
            {
                Z_ASSERT_WARNING(false, "Colons (\":\") are not allowed but for specifying drives.");
                strAfterDriveColon.Replace(COLON, string_z::GetEmpty(), EComparisonType::E_BinaryCaseSensitive);
                strPathToBeReplaced = strPathToBeReplaced.Substring(0, nFirstColonPosition) + strAfterDriveColon;
            }
        }
    }
}

#endif

void Path::_RemoveNotAllowedCharactersInHostname(string_z &strHostnameToBeReplaced)
{
    static const char_z CHAR_HYPHEN                          = '-';
    static const char_z CHAR_DOT                             = '.';
    static const codepoint_z CODEPOINT_FIRST_NUMBER          = '0';
    static const codepoint_z CODEPOINT_LAST_NUMBER           = '9';
#if defined(Z_OS_LINUX) || defined(Z_OS_MAC)
    static const char_z CHAR_AT_SIGN                         = '@';
#endif
    static const codepoint_z CODEPOINT_FIRST_ALPHA_UPPERCASE = 'A';
    static const codepoint_z CODEPOINT_LAST_ALPHA_UPPERCASE  = 'Z';
    static const char_z CHAR_OPENING_SQUARE_BRACKET          = '[';
    static const char_z CHAR_CLOSING_SQUARE_BRACKET          = ']';
    static const codepoint_z CODEPOINT_FIRST_ALPHA_LOWERCASE = 'a';
    static const codepoint_z CODEPOINT_LAST_ALPHA_LOWERCASE  = 'z';

    codepoint_z currentCodepoint = 0;
    char_z currentChar(0);
    unsigned int i = 0;

    if(Path::_IsIP(strHostnameToBeReplaced))
    {
        // Expected string example: [255.255.255.255]

        while(i < strHostnameToBeReplaced.GetLength())
        {
            currentChar = strHostnameToBeReplaced[i];
            currentCodepoint = currentChar.GetCodePoint();

            if((currentCodepoint < CODEPOINT_FIRST_NUMBER || currentCodepoint > CODEPOINT_LAST_NUMBER) && 
               currentChar != CHAR_OPENING_SQUARE_BRACKET &&
               currentChar != CHAR_CLOSING_SQUARE_BRACKET &&
               currentChar != CHAR_DOT)
            {
                Z_ASSERT_WARNING(false, string_z("The character '") + currentChar + "' is not allowed in this hostname.");
                strHostnameToBeReplaced.Replace(currentChar, string_z::GetEmpty(), EComparisonType::E_BinaryCaseSensitive);
            }
            else
            {
                ++i;
            }
        }
    }
    else
    {
        // Expected string example: AZaz-09

        while(i < strHostnameToBeReplaced.GetLength())
        {
            currentChar = strHostnameToBeReplaced[i];
            currentCodepoint = currentChar.GetCodePoint();

            if((currentCodepoint < CODEPOINT_FIRST_NUMBER ||
                (currentCodepoint > CODEPOINT_LAST_NUMBER && currentCodepoint < CODEPOINT_FIRST_ALPHA_UPPERCASE) ||
                (currentCodepoint > CODEPOINT_LAST_ALPHA_UPPERCASE && currentCodepoint < CODEPOINT_FIRST_ALPHA_LOWERCASE) ||
                currentCodepoint > CODEPOINT_LAST_ALPHA_LOWERCASE)          // It's not an alpha or numerical chracter
#if defined(Z_OS_LINUX) || defined(Z_OS_MAC)
                &&
                currentChar != CHAR_AT_SIGN // On Unix-based systems, the hostname may appear accompanied with the username using an at sign
#endif
                &&
                currentChar != CHAR_HYPHEN)
            {
                Z_ASSERT_WARNING(false, string_z("The character '") + currentChar + "' is not allowed in this hostname.");
                strHostnameToBeReplaced.Replace(currentChar, string_z::GetEmpty(), EComparisonType::E_BinaryCaseSensitive);
            }
            else
            {
                ++i;
            }
        }
    }
}

void Path::_ExtractHostnameFromPath(string_z &strPath, string_z &strHostname)
{
    static const string_z AUTHORITY_SEPARATOR = "//";

    Z_ASSERT_WARNING(strPath != AUTHORITY_SEPARATOR, string_z("The path \"") + strPath + "\" is malformed.");
    
    int nHostnameStartPosition = strPath.IndexOf(AUTHORITY_SEPARATOR, EComparisonType::E_BinaryCaseSensitive);

    if(nHostnameStartPosition == 0)
    {
        nHostnameStartPosition += AUTHORITY_SEPARATOR.GetLength();
        int nHostnameEndPosition = strPath.IndexOf(Path::PATH_SEPARATOR, nHostnameStartPosition, EComparisonType::E_BinaryCaseSensitive);

        if(nHostnameEndPosition != string_z::PATTERN_NOT_FOUND)
        {
            // The authority is defined and the path is not empty
            strHostname = strPath.Substring(nHostnameStartPosition, nHostnameEndPosition - Path::PATH_SEPARATOR.GetLength());
            
            // All the components prior to the path are removed so only the path is processed in next steps
            strPath = strPath.Substring(nHostnameEndPosition);
        }
        else
        {
            // The authority is defined and the path is empty
            strHostname = strPath.Substring(nHostnameStartPosition);
            
            // All the components prior to the path are removed so only the path is processed in next steps
            strPath = string_z::GetEmpty();
        }
    }
}

bool Path::_ValidateHostname(const string_z &strHostname)
{
    static const char_z CHAR_HYPHEN = '-';

    const bool IS_NOT_EMPTY = !strHostname.IsEmpty();
    const bool DOES_NOT_START_WITH_HYPHEN = strHostname.IsEmpty() || strHostname[0] != CHAR_HYPHEN;
    const bool IS_VALID_IP = !Path::_IsIP(strHostname) || Path::_ValidateIP(strHostname);

    // RFC1123 section 2.1 says that hostnames are allowed to start with either a digit or a letter, so the restriction described in RFC 952 is relaxed

    Z_ASSERT_WARNING(IS_NOT_EMPTY, "The hostname is empty.");
    Z_ASSERT_WARNING(DOES_NOT_START_WITH_HYPHEN, "Hostnames cannot start with an hyphen.");
    Z_ASSERT_WARNING(IS_VALID_IP, "The IP is malformed.");
    
    return IS_NOT_EMPTY               &&
           DOES_NOT_START_WITH_HYPHEN && 
           IS_VALID_IP;
}

bool Path::_IsIP(const string_z &strHostname)
{
    static const codepoint_z CODEPOINT_FIRST_NUMBER           = '0';
    static const codepoint_z CODEPOINT_LAST_NUMBER            = '9';
    static const codepoint_z CODEPOINT_OPENING_SQUARE_BRACKET = '[';

    // If it begins with an opening square bracket ("[") or a number ("0-9"), it must be an IP
    const codepoint_z FIRST_CODEPOINT = strHostname.IsEmpty() ? 0 : strHostname[0].GetCodePoint();
    return (FIRST_CODEPOINT >= CODEPOINT_FIRST_NUMBER && FIRST_CODEPOINT <= CODEPOINT_LAST_NUMBER) || FIRST_CODEPOINT == CODEPOINT_OPENING_SQUARE_BRACKET;
}

bool Path::_ValidateIP(const string_z &strHostname)
{
    static const codepoint_z CODEPOINT_FIRST_NUMBER           = '0';
    static const codepoint_z CODEPOINT_LAST_NUMBER            = '9';
    static const codepoint_z CODEPOINT_OPENING_SQUARE_BRACKET = '[';
    static const codepoint_z CODEPOINT_CLOSING_SQUARE_BRACKET = ']';
    static const string_z DOT = ".";

    bool bIsValid = false;

    if(Path::_IsIP(strHostname))
    {
        static const unsigned int PARTS_OF_IPV4 = 4U;

        // If the IP starts with a square bracket "[" it must end with another "]"
        const bool STARTS_WITH_SQUARE_BRACKET = strHostname[0].GetCodePoint() == CODEPOINT_OPENING_SQUARE_BRACKET;
        const bool ENDS_WITH_SQUARE_BRACKET = strHostname[strHostname.GetLength() - 1U].GetCodePoint() == CODEPOINT_CLOSING_SQUARE_BRACKET;
        const bool MISSING_SQUARE_BRACKET = STARTS_WITH_SQUARE_BRACKET != ENDS_WITH_SQUARE_BRACKET;
        string_z strIP;

        // Removes the square brackets
        if(STARTS_WITH_SQUARE_BRACKET && ENDS_WITH_SQUARE_BRACKET)
            strIP = strHostname.Substring(1U, strHostname.GetLength() - 2U);
        else
            strIP = strHostname;

        Z_ASSERT_WARNING(!MISSING_SQUARE_BRACKET, "If the IP starts with an opening square bracket (\"[\") it must end with a closing square bracket (\"]\").");

        if(!MISSING_SQUARE_BRACKET)
        {
            ArrayResult<string_z> arParts = strIP.Split(DOT);

            Z_ASSERT_WARNING(arParts.GetCount() == PARTS_OF_IPV4, "The IP (v4) must be compound of four parts.");

            if(arParts.GetCount() == PARTS_OF_IPV4)
            {
                bool bAllPartsAreValid = true;

                unsigned int iPart = 0;

                // For every part of the IP NNN.NNN.NNN.NNN
                while(iPart < PARTS_OF_IPV4 && bAllPartsAreValid)
                {
                    // IP values cannot be empty
                    bAllPartsAreValid = bAllPartsAreValid && !arParts[iPart].IsEmpty();

                    Z_ASSERT_WARNING(!arParts[iPart].IsEmpty(), "Every part of the IP must contain a number in the range [0-255].");

                    unsigned int iChar = 0;
                    const unsigned int PART_LENGTH = arParts[iPart].GetLength();

                    // Checks for valid characters: [0-9]
                    while(iChar < PART_LENGTH && bAllPartsAreValid)
                    {
                        codepoint_z currentCodepoint = arParts[iPart][iChar].GetCodePoint();

                        bAllPartsAreValid = bAllPartsAreValid &&
                                            currentCodepoint >= CODEPOINT_FIRST_NUMBER && currentCodepoint <= CODEPOINT_LAST_NUMBER;

                        Z_ASSERT_WARNING(bAllPartsAreValid, "The IP contains non-allowed characters. Allowed characters are: \"[0-9]\", \".\", \"[\", \"]\".");

                        ++iChar;
                    }

                    // Checks that every number in the IP is not greater than 255 and is compound of up to 3 numbers
                    if(bAllPartsAreValid)
                    {
                        static const i64_z MAXIMUM_VALUE_ALLOWED = 255;
                        static const i64_z MAXIMUM_VALUE_LENGTH = 3;

                        const i64_z CURRENT_VALUE = arParts[iPart].ToInteger();

                        Z_ASSERT_WARNING(CURRENT_VALUE <= MAXIMUM_VALUE_ALLOWED, string_z("The number ") + arParts[iPart] + " is greater than maximum allowed (255).");
                        Z_ASSERT_WARNING(arParts[iPart].GetLength() <= MAXIMUM_VALUE_LENGTH, "Every part of the IP must, at most, 3-characters length.");

                        bAllPartsAreValid = bAllPartsAreValid && CURRENT_VALUE <= MAXIMUM_VALUE_ALLOWED;
                        bAllPartsAreValid = bAllPartsAreValid && arParts[iPart].GetLength() <= MAXIMUM_VALUE_LENGTH;
                    }

                    ++iPart;
                }

                bIsValid = bAllPartsAreValid;
            }
        }
    }

    return bIsValid;
}

void Path::_ExtractFilenameFromPath(string_z &strPath, string_z &strFilename)
{
    static const char_z CHAR_SEPARATOR(Path::PATH_SEPARATOR_CHAR);

    const int STRING_LAST_POSITION = strPath.GetLength() - 1;

    if(!strPath.IsEmpty() && strPath[STRING_LAST_POSITION] != CHAR_SEPARATOR)
    {
        int nLastSlashPosition = strPath.LastIndexOf(CHAR_SEPARATOR, EComparisonType::E_BinaryCaseSensitive);

        if(nLastSlashPosition != string_z::PATTERN_NOT_FOUND)
        {
            strFilename = strPath.Substring(nLastSlashPosition + 1);
            strPath = strPath.Substring(0, nLastSlashPosition);
        }
        else
        {
            // It only contains a filename
            strFilename = strPath;
            strPath = string_z::GetEmpty();
        }
    }
    else
    {
        strFilename = string_z::GetEmpty();
    }
}

Path& Path::operator=(const Path &path)
{
    if(this != &path)
    {
        m_strHostname = path.m_strHostname;
        m_strPath     = path.m_strPath;
        m_strFilename = path.m_strFilename;
    }

    return *this;
}

bool Path::operator==(const Path &path) const
{
    string_z strResolvedResidentPath = m_strPath;
    Path::_ResolveDotSegments(strResolvedResidentPath);

    string_z strResolvedInputPath = path.m_strPath;
    Path::_ResolveDotSegments(strResolvedInputPath);

#if defined(Z_OS_WINDOWS)
    // On Windows (NTFS, FAT16, FAT32, etc.) paths are case insensitive
    return m_strHostname.CompareTo(path.m_strHostname, EComparisonType::E_BinaryCaseInsensitive) == 0 &&
           strResolvedResidentPath.CompareTo(strResolvedInputPath, EComparisonType::E_BinaryCaseInsensitive) == 0 &&
           m_strFilename.CompareTo(path.m_strFilename, EComparisonType::E_BinaryCaseInsensitive) == 0;
#else
    // On Unix and Mac (Posix) paths are case sensitive
    return m_strHostname == path.m_strHostname && strResolvedResidentPath == strResolvedInputPath && m_strFilename == path.m_strFilename;
#endif

}

bool Path::operator!=(const Path &path) const
{
    return !this->operator==(path);
}

void Path::RemoveLastDirectory()
{
    static const char_z CHAR_SEPARATOR(Path::PATH_SEPARATOR_CHAR);
    static const string_z LEADING_DOT(string_z(Path::DOT) + Path::PATH_SEPARATOR);

    if(!m_strPath.IsEmpty() && 
        m_strPath != LEADING_DOT &&
        m_strPath != Path::PATH_SEPARATOR)
    {
        int nPreviousDirectorySlash = m_strPath.LastIndexOf(Path::PATH_SEPARATOR, m_strPath.GetLength() - 2, EComparisonType::E_BinaryCaseSensitive);

        // If it is not a relative path with only one directory
        if(nPreviousDirectorySlash != string_z::PATTERN_NOT_FOUND)
            m_strPath = m_strPath.Substring(0, nPreviousDirectorySlash);
    }
}

void Path::AppendDirectory(const string_z &strDirectory)
{
    Z_ASSERT_WARNING(!strDirectory.IsEmpty(), "The input directory cannot be empty.");

    if(!strDirectory.IsEmpty())
    {
        string_z strFixedDirectory = strDirectory;

        Z_ASSERT_WARNING(!strFixedDirectory.Contains(Path::PATH_SEPARATOR, EComparisonType::E_BinaryCaseSensitive),
                          "Character '/' is not allowed.");

        if(strFixedDirectory.Contains(Path::PATH_SEPARATOR, EComparisonType::E_BinaryCaseSensitive))
            strFixedDirectory.Replace(Path::PATH_SEPARATOR, string_z::GetEmpty(), EComparisonType::E_BinaryCaseSensitive);

#if defined(Z_OS_WINDOWS)

        static const string_z COLON(":");

        if(strFixedDirectory.Contains(COLON, EComparisonType::E_BinaryCaseSensitive))
        {
            Z_ASSERT_WARNING(false, "Colons (\":\") are not allowed but for specifying drives.");
            strFixedDirectory.Replace(COLON, string_z::GetEmpty(), EComparisonType::E_BinaryCaseSensitive);
        }

        Path::_RemoveNotAllowedCharactersInPath(strFixedDirectory);
        
        static const string_z BACKSLASH = "\\";

        Z_ASSERT_WARNING(!strFixedDirectory.Contains(BACKSLASH, EComparisonType::E_BinaryCaseSensitive),
                          "Character '\\' is not allowed.");

        if(strFixedDirectory.Contains(BACKSLASH, EComparisonType::E_BinaryCaseSensitive))
            strFixedDirectory.Replace(BACKSLASH, string_z::GetEmpty(), EComparisonType::E_BinaryCaseSensitive);

        m_strPath.Append(strFixedDirectory);
#else
        // Note: Linux and Mac use Posix path names (case sensitive, separed with slashes, allowing any UTF-16 character but NUL and /)
        m_strPath.Append(strFixedDirectory);
#endif
        m_strPath.Append(Path::PATH_SEPARATOR);
    }
}

void Path::Resolve(const Path &relativePath)
{
#if defined(Z_OS_WINDOWS)    
    const bool RESIDENT_IS_ABSOLUTE = this->IsAbsolute();
#else
    static const char_z TILDE('~');
    const bool RESIDENT_IS_ABSOLUTE = this->IsAbsolute() || m_strPath[0] == TILDE;
#endif
    
    Z_ASSERT_WARNING(RESIDENT_IS_ABSOLUTE, "Resident path should be absolute.");

    if(relativePath.IsAbsolute())
    {
#if defined(Z_OS_WINDOWS)
        if(this->HasDrive() && !relativePath.HasHostname() && !relativePath.HasDrive())
        {
            string_z strDrive = this->GetRoot();
            strDrive = strDrive.Substring(0, strDrive.GetLength() - Path::PATH_SEPARATOR.GetLength() - 1U);
            *this = relativePath;
            m_strPath = strDrive + m_strPath;
        }
        else
        {
            Z_ASSERT_WARNING(false, "Input path should be relative.");
            *this = relativePath;
        }
#else
        Z_ASSERT_WARNING(false, "Input path should be relative.");
        *this = relativePath;
#endif
    }
    else if(RESIDENT_IS_ABSOLUTE)
    {
        static const string_z FILE_SCHEME("file:");

        string_z strPathStart;

#if defined(Z_OS_WINDOWS)
        if(this->HasDrive())
            strPathStart = this->GetRoot();
#else
        if(m_strPath[0] == TILDE)
            strPathStart = string_z(TILDE) + Path::PATH_SEPARATOR;
#endif

        Uri relativeUri(relativePath.m_strPath);
        Uri absoluteURI(FILE_SCHEME + m_strPath);
        absoluteURI.Resolve(relativeUri);
        string_z strResolvedPath = absoluteURI.GetPath();

        if(!strPathStart.IsEmpty() && strResolvedPath.IndexOf(strPathStart, EComparisonType::E_BinaryCaseSensitive) != 0)
        {
            m_strPath = strPathStart;
            m_strPath.Append(strResolvedPath);
        }
        else
        {
            m_strPath = strResolvedPath;
        }

        Uri::Decode(m_strPath, m_strPath);
        
        if(!relativePath.m_strFilename.IsEmpty())
            m_strFilename = relativePath.m_strFilename;
    }
}

string_z Path::GetAbsolutePath() const
{
    string_z strResult;

    if(this->IsAbsolute())
    {
        strResult = this->ToString();
    }
    else
    {
        Path targetPath = SDirectory::GetCurrentWorkingDirectory();
        targetPath.Resolve(*this);
        strResult = targetPath.ToString();
    }

    return strResult;
}

string_z Path::GetRelativePath() const
{
    return this->GetRelativePathTo(SDirectory::GetCurrentWorkingDirectory());
}

string_z Path::GetRelativePathTo(const Path &absolutePath) const
{
#if defined(Z_OS_WINDOWS)
    // On Windows, paths are not case sensitive
    static const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseInsensitive;
#else
    static const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseSensitive;
    static const char_z CHAR_TILDE('~');
#endif

    Z_ASSERT_WARNING(absolutePath.IsAbsolute(), "The input path must be absolute.");
    Z_ASSERT_WARNING(this->IsAbsolute(), "The resident path must be absolute.");
    Z_ASSERT_WARNING(absolutePath.m_strHostname.CompareTo(m_strHostname, COMPARISON_TYPE) == 0, "When paths have hostname, they must be equal.");

#if defined(Z_OS_WINDOWS)

    string_z strDrive;
    const bool RESIDENT_PATH_HAS_DRIVE = this->HasDrive();
    const bool INPUT_PATH_HAS_DRIVE = absolutePath.HasDrive();

    Z_ASSERT_WARNING((RESIDENT_PATH_HAS_DRIVE && INPUT_PATH_HAS_DRIVE && this->GetRoot() == absolutePath.GetRoot()) || 
                      (!RESIDENT_PATH_HAS_DRIVE && !INPUT_PATH_HAS_DRIVE) ||
                      (RESIDENT_PATH_HAS_DRIVE && !absolutePath.m_strPath.IsEmpty() && absolutePath.m_strPath[0] == Path::PATH_SEPARATOR_CHAR) ||
                      (INPUT_PATH_HAS_DRIVE && !m_strPath.IsEmpty() && m_strPath[0] == Path::PATH_SEPARATOR_CHAR), 
                      "When paths have drive, they must be equal.");
#else
    Z_ASSERT_WARNING((m_strPath[0] == CHAR_TILDE) == (absolutePath.m_strPath[0] == CHAR_TILDE), "When paths start with a tilde ('~'), both must start with it.");
#endif

    string_z strRelativePath;

    if(absolutePath.m_strHostname.CompareTo(m_strHostname, COMPARISON_TYPE) == 0 &&
       absolutePath.IsAbsolute() && 
       this->IsAbsolute()
#if defined(Z_OS_WINDOWS)
       && // If both have drives, they must be equal. Otherwise they must not have drives.
       ((RESIDENT_PATH_HAS_DRIVE && INPUT_PATH_HAS_DRIVE && this->GetRoot() == absolutePath.GetRoot()) || 
        (!RESIDENT_PATH_HAS_DRIVE && !INPUT_PATH_HAS_DRIVE) ||
        (RESIDENT_PATH_HAS_DRIVE && !absolutePath.m_strPath.IsEmpty() && absolutePath.m_strPath[0] == Path::PATH_SEPARATOR_CHAR) ||
        (INPUT_PATH_HAS_DRIVE && !m_strPath.IsEmpty() && m_strPath[0] == Path::PATH_SEPARATOR_CHAR))
#else
       && // Both must start with tildes ("~") or none
       ((m_strPath[0] == CHAR_TILDE) == (absolutePath.m_strPath[0] == CHAR_TILDE))
#endif
       )
    {
        static const string_z DOUBLE_DOT(string_z("..") + Path::PATH_SEPARATOR);
        static const string_z SINGLE_DOT(string_z(".") + Path::PATH_SEPARATOR);

        // Variables for resident path
        int nSlashPosition1 = 0;
        int nPreviousSlashPosition1 = 0;
        string_z strCurrentSegment1;

        // Variables for input path
        int nSlashPosition2 = 0;
        int nPreviousSlashPosition2 = 0;
        string_z strCurrentSegment2;

        int nFirstDifferentDirectory = string_z::PATTERN_NOT_FOUND;

        strRelativePath.Append(SINGLE_DOT);

#if defined(Z_OS_WINDOWS)

        if(this->HasDrive())
        {
            // Skips the drive of the resident path
            nSlashPosition1 = m_strPath.IndexOf(Path::PATH_SEPARATOR, EComparisonType::E_BinaryCaseSensitive);
            nPreviousSlashPosition1 = nSlashPosition1;
        }

        if(absolutePath.HasDrive())
        {
            // Skips the drive of the input path
            nSlashPosition2 = absolutePath.m_strPath.IndexOf(Path::PATH_SEPARATOR, EComparisonType::E_BinaryCaseSensitive);
            nPreviousSlashPosition2 = nSlashPosition2;
        }

#endif

        // For every segment in the resident path
        while((nSlashPosition1 = m_strPath.IndexOf(Path::PATH_SEPARATOR, nSlashPosition1, EComparisonType::E_BinaryCaseSensitive)) != string_z::PATTERN_NOT_FOUND)
        {
            // If there were more segments in the input path
            if(nSlashPosition2 != string_z::PATTERN_NOT_FOUND)
            {
                nSlashPosition2 = absolutePath.m_strPath.IndexOf(Path::PATH_SEPARATOR, nSlashPosition2, EComparisonType::E_BinaryCaseSensitive);

                // If there are more segments in the input path
                if(nSlashPosition2 != string_z::PATTERN_NOT_FOUND)
                {
                    // Gets the current segment from both paths
                    strCurrentSegment1 = m_strPath.Substring(nPreviousSlashPosition1, nSlashPosition1);
                    strCurrentSegment2 = absolutePath.m_strPath.Substring(nPreviousSlashPosition2, nSlashPosition2);

                    // If they are not equal
                    if(strCurrentSegment1.CompareTo(strCurrentSegment2, COMPARISON_TYPE) != 0)
                    {
                        // Puts a mark at the first different segment found
                        if(nFirstDifferentDirectory == string_z::PATTERN_NOT_FOUND)
                            nFirstDifferentDirectory = nPreviousSlashPosition2 + 1;

                        strRelativePath.Append(DOUBLE_DOT);
                    }

                    nPreviousSlashPosition2 = nSlashPosition2;
                    ++nSlashPosition2;
                }
                else
                {
                    // There one segment more in the resident path than in the input path
                    strRelativePath.Append(DOUBLE_DOT);
                }
            }
            else
            {
                strRelativePath.Append(DOUBLE_DOT);
            }

            nPreviousSlashPosition1 = nSlashPosition1;
            ++nSlashPosition1;
        }

        // Adds the rest of segments of the input path
        if(nFirstDifferentDirectory != string_z::PATTERN_NOT_FOUND && nFirstDifferentDirectory < scast_z(absolutePath.m_strPath.GetLength(), int))
        {
            // If there are differences between paths, it adds the segments that are different
            strRelativePath.Append(absolutePath.m_strPath.Substring(nFirstDifferentDirectory));
        }
        else if(absolutePath.m_strPath.GetLength() > m_strPath.GetLength())
        {
            // If there are more segments in the input path than in the resident path, adds the rest
            strRelativePath.Append(absolutePath.m_strPath.Substring(m_strPath.GetLength()));
        }
    }

    return strRelativePath;
}

string_z Path::GetLastDirectory() const
{
    string_z strResult;

    if(m_strPath != Path::PATH_SEPARATOR && m_strPath != this->GetRoot())
    {
        if(m_strPath.GetLength() <= 1U)
        {
            strResult = m_strPath;
        }
        else
        {
            int nLastSeparatorPosition = m_strPath.LastIndexOf(Path::PATH_SEPARATOR, m_strPath.GetLength() - 2U, EComparisonType::E_BinaryCaseSensitive);

            if(nLastSeparatorPosition != string_z::PATTERN_NOT_FOUND)
                strResult = m_strPath.Substring(nLastSeparatorPosition + 1, m_strPath.GetLength() - 2U);
            else
                strResult = m_strPath.Substring(0, m_strPath.GetLength() - 2U);
        }
    }

    return strResult;
}

string_z Path::ToString() const
{
    static const string_z HOSTNAME_SEPARATOR("//");

    string_z strCompletePath;
    
    if(this->HasHostname())
    {
        strCompletePath.Append(HOSTNAME_SEPARATOR);
        strCompletePath.Append(m_strHostname);
    }

    strCompletePath.Append(m_strPath);

    if(this->IsFile())
        strCompletePath.Append(m_strFilename);

    return strCompletePath;
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |         PROPERTIES         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

const string_z& Path::GetPathSeparator()
{
    return Path::PATH_SEPARATOR;
}

bool Path::IsAbsolute() const
{
    static const string_z COLON_FOLLOWED_BY_SEPARATOR(string_z(":") + Path::PATH_SEPARATOR);
    static const char_z CHAR_SEPARATOR(Path::PATH_SEPARATOR_CHAR);
    
    return m_strPath[0] == CHAR_SEPARATOR || this->HasHostname()
#if defined(Z_OS_WINDOWS)
           // Note: On Windows, the path "C:directory1" (without slash after the drive letter), for example, means a relative path in the current directory of the drive C
           || 
           m_strPath.Contains(COLON_FOLLOWED_BY_SEPARATOR, EComparisonType::E_BinaryCaseSensitive)
#endif
           ;
}

string_z Path::GetFilenameWithoutExtension() const
{
    string_z strFilename;

    if(!m_strFilename.IsEmpty())
    {
        // Searches for the last dot
        int nDotPosition = string_z::PATTERN_NOT_FOUND;
        nDotPosition = m_strFilename.LastIndexOf(Path::DOT, EComparisonType::E_BinaryCaseSensitive);

        if(nDotPosition != 0)
        {
            if(nDotPosition != string_z::PATTERN_NOT_FOUND)
                strFilename = m_strFilename.Substring(0, nDotPosition - 1U);
            else
                strFilename = m_strFilename;
        }
    }

    return strFilename;
}

string_z Path::GetFilename() const
{
    return m_strFilename;
}

string_z Path::GetFileExtension() const
{
    string_z strExtension;

    if(!m_strFilename.IsEmpty())
    {
        // Searches for the last dot
        int nDotPosition = string_z::PATTERN_NOT_FOUND;
        nDotPosition = m_strFilename.LastIndexOf(Path::DOT, EComparisonType::E_BinaryCaseSensitive);

        if(nDotPosition != string_z::PATTERN_NOT_FOUND && scast_z(nDotPosition + 1, unsigned int) < m_strFilename.GetLength())
            strExtension = m_strFilename.Substring(nDotPosition + 1);
    }

    return strExtension;
}

string_z Path::GetDirectory() const
{
    return m_strPath;
}

string_z Path::GetRoot() const
{
    static const string_z TILDE_AND_SEPARATOR("~/");
    static const string_z HOSTNAME_SEPARATOR("//");

    string_z strResult;

    if(this->HasHostname())
    {
        strResult.Append(HOSTNAME_SEPARATOR);
        strResult.Append(m_strHostname);

        if(m_strPath.GetLength() > 1U)
        {
            // Gets the first segment
            int nFirstSeparatorPosition = m_strPath.IndexOf(Path::PATH_SEPARATOR_CHAR, 1U, EComparisonType::E_BinaryCaseSensitive);

            if(nFirstSeparatorPosition != string_z::PATTERN_NOT_FOUND)
                strResult.Append(m_strPath.Substring(0, nFirstSeparatorPosition));
        }
        else
        {
            strResult.Append(Path::PATH_SEPARATOR);
        }
    }
#if defined(Z_OS_WINDOWS)
    else if(this->HasDrive())
    {
        static string_z DRIVE_SEPARATOR(":/");

        // Gets the drive
        int nDriveEndPosition = m_strPath.IndexOf(DRIVE_SEPARATOR, EComparisonType::E_BinaryCaseSensitive);
        strResult = m_strPath.Substring(0, nDriveEndPosition + 1U);
    }
#elif defined(Z_OS_LINUX) || defined(Z_OS_MAC)
    else if(m_strPath.IndexOf(TILDE_AND_SEPARATOR, EComparisonType::E_BinaryCaseSensitive) == 0)
    {
        strResult = Path::PATH_SEPARATOR;
    }
#endif
    else if(!m_strPath.IsEmpty() && m_strPath[0] == Path::PATH_SEPARATOR_CHAR)
    {
        strResult = Path::PATH_SEPARATOR;
    }

    return strResult;
}

string_z Path::GetHostname() const
{
    return m_strHostname;
}

bool Path::IsFile() const
{
    return !m_strFilename.IsEmpty();
}

bool Path::IsDirectory() const
{
    return m_strFilename.IsEmpty();
}

bool Path::HasDrive() const
{
#if defined(Z_OS_WINDOWS)

    static string_z DRIVE_SEPARATOR(":/");

    return m_strPath.IndexOf(DRIVE_SEPARATOR, EComparisonType::E_BinaryCaseSensitive) != string_z::PATTERN_NOT_FOUND;
#else
    return false;
#endif
}

bool Path::HasHostname() const
{
    return !m_strHostname.IsEmpty();
}

bool Path::HasRoot() const
{
    static const string_z TILDE_AND_SEPARATOR("~/");

    bool bHasRoot = this->HasHostname() ||
#if defined(Z_OS_WINDOWS)
                    this->HasDrive()    ||
#elif defined(Z_OS_LINUX) || defined(Z_OS_MAC)
                    m_strPath.IndexOf(TILDE_AND_SEPARATOR, EComparisonType::E_BinaryCaseSensitive) == 0 ||
#endif
                    (!m_strPath.IsEmpty() && m_strPath[0] == Path::PATH_SEPARATOR_CHAR);

    return bHasRoot;
}

void Path::SetHostname(const string_z &strHostname)
{
    m_strHostname = strHostname;

    if(!m_strHostname.IsEmpty())
    {
        Path::_RemoveNotAllowedCharactersInHostname(m_strHostname);
        Path::_ValidateHostname(m_strHostname);

#if defined(Z_OS_WINDOWS)
        Z_ASSERT_WARNING(!this->HasDrive() || !this->HasHostname(), "The path contains both a hostname and a drive letter, it is not a valid path.");
#endif
    }
}

void Path::SetDirectory(const string_z &strDirectory)
{
    m_strPath = strDirectory;
    
#if defined(Z_OS_WINDOWS)
    
    // On Windows, paths can be created using backslashes as segment separator. They have to be replaced with slashes.
    static const string_z BACK_SLASH("\\");

    if(m_strPath.Contains(BACK_SLASH, EComparisonType::E_BinaryCaseSensitive))
        m_strPath.Replace(BACK_SLASH, Path::PATH_SEPARATOR, EComparisonType::E_BinaryCaseSensitive);

    // Adds a slash at the end if the path consists only in a drive letter
    static const char_z CHAR_COLON(':');

    if(!m_strPath.IsEmpty() && m_strPath[m_strPath.GetLength() - 1U] == CHAR_COLON)
        m_strPath.Append(Path::PATH_SEPARATOR);

    // Removes all the characters that are not allowed in Windows' file systems
    Path::_RemoveNotAllowedCharactersInPath(m_strPath);
    // Note: Linux and Mac use Posix path names (case sensitive, separed with slashes, allowing any UTF-16 character but NUL and /)

#endif

    static const string_z DOT_SEPARATOR(string_z(Path::DOT) + Path::PATH_SEPARATOR);

    if(m_strPath.IsEmpty())
        m_strPath = this->HasHostname() ? Path::PATH_SEPARATOR : DOT_SEPARATOR;

    if(m_strPath[m_strPath.GetLength() - 1U] != Path::PATH_SEPARATOR_CHAR)
        m_strPath.Append(Path::PATH_SEPARATOR);

#if defined(Z_OS_WINDOWS)
    Z_ASSERT_WARNING(!this->HasDrive() || !this->HasHostname(), "The path contains both a hostname and a drive letter, it is not a valid path.");
#endif

}

void Path::SetFilename(const string_z &strFilename)
{
    // Replaces only the name
    int nLastDotPosition = m_strFilename.LastIndexOf(Path::DOT, m_strFilename.GetLength() - 2U, EComparisonType::E_BinaryCaseSensitive);
    string_z strReplacedName;
    
    if(nLastDotPosition != string_z::PATTERN_NOT_FOUND)
    {
        strReplacedName = strFilename;
        strReplacedName.Append(m_strFilename.Substring(nLastDotPosition));
    }
    else
    {
        strReplacedName = strFilename;
    }

    this->SetFilenameAndExtension(strReplacedName);
}

void Path::SetFilenameAndExtension(const string_z &strFilenameAndExtension)
{
    static const string_z BACK_SLASH("\\");

    m_strFilename = strFilenameAndExtension;

    if(!strFilenameAndExtension.IsEmpty())
    {
        Z_ASSERT_WARNING(!strFilenameAndExtension.Contains(Path::PATH_SEPARATOR, EComparisonType::E_BinaryCaseSensitive), "Path separators are not allowed in filenames.");

#if defined(Z_OS_WINDOWS)

        Z_ASSERT_WARNING(!strFilenameAndExtension.Contains(BACK_SLASH, EComparisonType::E_BinaryCaseSensitive), "Path separators are not allowed in filenames.");
        
        static const string_z COLON(":");

        if(m_strFilename.Contains(COLON, EComparisonType::E_BinaryCaseSensitive))
        {
            Z_ASSERT_WARNING(false, "Colons (\":\") are not allowed but for specifying drives.");
            m_strFilename.Replace(COLON, string_z::GetEmpty(), EComparisonType::E_BinaryCaseSensitive);
        }

        // Removes all the characters that are not allowed in Windows' file systems
        Path::_RemoveNotAllowedCharactersInPath(m_strFilename);
        // Note: Linux and Mac use Posix path names (case sensitive, separed with slashes, allowing any UTF-16 character but NUL and /)

        if(m_strFilename.Contains(BACK_SLASH, EComparisonType::E_BinaryCaseSensitive))
            m_strFilename.Replace(BACK_SLASH, string_z::GetEmpty(), EComparisonType::E_BinaryCaseSensitive);

#endif

        if(m_strFilename.Contains(Path::PATH_SEPARATOR, EComparisonType::E_BinaryCaseSensitive))
            m_strFilename.Replace(Path::PATH_SEPARATOR, string_z::GetEmpty(), EComparisonType::E_BinaryCaseSensitive);

        // Note: About the length restriction of 255 characters http://www.linfo.org/file_name.html
        Z_ASSERT_WARNING(m_strFilename.GetLength() <= 255, 
                          string_z("The length of the file name (") + string_z::FromInteger(m_strFilename.GetLength()) + ") exceeds the maximum allowed (255).");
    }
}


} // namespace z