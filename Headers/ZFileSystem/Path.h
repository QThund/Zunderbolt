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

#ifndef __PATH__
#define __PATH__

#include "ZFileSystem/FileSystemModuleDefinitions.h"

#include "ZCommon/DataTypes/StringsDefinitions.h"



namespace z
{

/// <summary>
/// Represents a path, which is a text string that is used to point to a logical place in the file system of the operating system.
/// </summary>
/// <remarks>
/// On Windows and Unix-based operative systems, paths are sequences of directories divided by slashes ("/"); every directory is said to be "contained" in the previous one.
/// On Windows, any local directory or file is in turn contained into a drive, which is represented with a letter followed by a colon (":").<br/>
/// Paths can reference to either a file or a directory. This class follows the common rule of considering that paths that have a trailing slash reference to directories.<br/>
/// Paths can be either relative or absolute. Absolute paths reference to a location specifying all the directories from the root to the desired place; they are univocal. Relative
/// paths reference to a location that depends on a base path (which is any absolute path); for this purpose, two special segments are used: "." and "..". The former means "the
/// current directory" whereas the second means "the parent directory". Paths that start with either a slash ("/") or a drive (e.g. "x:/") are considered as absolute.<br/>
/// Remote paths are allowed, i.e. paths that reference to locations that are outside of the current machine, using a hostname or an IP. Remote paths start with
/// two slashes ("//") and may contain an at sign ("@") on Unix-based systems.<br/>
/// <br/>
/// For more information about paths, read:<br/>
/// - RFC 1738: http://tools.ietf.org/html/rfc1738#section-3.10
/// - Naming Files, Paths, and Namespaces (Windows): http://msdn.microsoft.com/en-us/library/windows/desktop/aa365247%28v=vs.85%29.aspx
/// - RFC 1123: http://tools.ietf.org/html/rfc1123#page-13
/// - RFC 952: http://tools.ietf.org/html/rfc952
/// </remarks>
class Z_LAYER_FILESYSTEM_SYMBOLS Path
{
    // CONSTANTS
    // ---------------
private:

    /// <summary>
    /// The separator that divides the path into directories.
    /// </summary>
    static const string_z PATH_SEPARATOR;
    
    /// <summary>
    /// The separator that divides the path into directories, as a char.
    /// </summary>
    static const char_z PATH_SEPARATOR_CHAR;

    /// <summary>
    /// A dot character (".").
    /// </summary>
    static const char_z DOT;


    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Constructor that receives a string that contains a path.
    /// </summary>
    /// <remarks>
    /// Paths can reference to either a file or a directory. This class follows the common rule of considering that paths that have a trailing slash reference to directories.<br/>
    /// Paths can be either relative or absolute. Paths that start with either a slash ("/") or a drive (e.g. "x:/") are considered as absolute. Relative paths can start with
    /// a dot (".") or a double dot (".."), among others. Drive-relative paths (e.g. "C:path1/path2") are allowed on Windows. On Unix-based systems, a relative path can start with
    /// a tilde ("~") to refer to the user's "home" directory.<br/>
    /// The length of a filename cannot exceed 255 characters.<br/>
    /// On Windows, the following characters are neither allowed in a directory name nor in a file name: "*", "?", "\", """, "<", ">", "|", ":", "/".<br/>
    /// Remote paths are allowed, using either a hostname or an IP. Remote paths start with two slashes ("//") and may contain an at sign ("@") on Unix-based systems.<br/>
    /// The only valid characters in a hostname are: "[a-z]", "[A-Z]", "[0-9]", "-". On Unix-based systems, the at sign ("@") is admitted too. Hostnames cannot start with an hyphen ("-").<br/>
    /// The only valid characters in an IP are: "[", "]", "[0-9]", ".". IPs must be compound of 4 numbers separated by periods, where every number must be present and be equal to or 
    /// lower than 255. IPs may be enclosed between square brackets.<br/>
    /// On Windows, backslashes ("\") are internally replaced with slashes ("/").<br/>
    /// Examples of valid paths:<br/>
    /// <br/><ul>
    /// <li>"C:/Windows/System/"
    /// <li>"/home/user/Desktop/"
    /// <li>"~/Desktop/"
    /// <li>"./../../path1/filename.ext"
    /// <li>"//user@myhost/directory/"
    /// <li>"//[255.255.0.1]/"
    /// </ul>
    /// </remarks>
    /// <param name="strPath">[IN] The path to be parsed, validated and stored. Any invalid character will be removed. If it is empty, the path "./" will be used instead; if it only contains 
    /// a hostname or IP, the path will be the root "/".</param>
    Path(const string_z &strPath);
    

    // METHODS
    // ---------------
public:
    
    /// <summary>
    /// Assignment operator that makes a copy of another path.
    /// </summary>
    /// <param name="path">[IN] The path to be copied.</param>
    /// <returns>
    /// A reference to the resultant path.
    /// </returns>
    Path& operator=(const Path &path);

    /// <summary>
    /// Equality operator that checks if two paths are equal or not. Paths are equal if they refer to the same location.
    /// </summary>
    /// <remarks>
    /// Any dot segment ("." or "..") but the leading ones will be resolved before paths are compared; this means that, for example, 
    /// the path "/a/b/./c/d/../e" will be resolved to "/a/b/c/e" whereas the path "./../path1/" will remain the same. Hence two
    /// paths may be referencing the same location even if they are not specified in the same way.<br/>
    /// On Windows, paths are case insensitive whereas on Unix-based systems they are case sensitive.
    /// </remarks>
    /// <param name="path">[IN] Path to compare to.</param>
    /// <returns>
    /// True if both paths are equal; False otherwise.
    /// </returns>
    bool operator==(const Path &path) const;
    
    /// <summary>
    /// Inequality operator that checks if two paths are different or not. Paths are different if they refer to different locations.
    /// </summary>
    /// <remarks>
    /// Any dot segment ("." or "..") but the leading ones will be resolved before paths are compared; this means that, for example, 
    /// the path "/a/b/./c/d/../e" will be resolved to "/a/b/c/e" whereas the path "./../path1/" will remain the same. Hence two
    /// paths may be referencing the same location even if they are not specified in the same way.<br/>
    /// On Windows, paths are case insensitive whereas on Unix-based systems they are case sensitive.
    /// </remarks>
    /// <param name="path">[IN] Path to compare to.</param>
    /// <returns>
    /// False if both paths are equal; True otherwise.
    /// </returns>
    bool operator!=(const Path &path) const;
    
    /// <summary>
    /// Removes the last directory of the path. The file name, if any, is kept.
    /// </summary>
    /// <remarks>
    /// Note that drives ("x:/"), leading tildes ("~/") and leading dots ("./") cannot be removed. If the path refers to the root directory ("/"), nothing is done.
    /// </remarks>
    void RemoveLastDirectory();

    /// <summary>
    /// Adds a directory to the end of the path. The file name, if any, is kept.
    /// </summary>
    /// <remarks>
    /// A trailing slash will be added after the new directory.<br/>
    /// On Windows, the following characters are allowed neither in a directory name nor in a file name: "*", "?", "\", """, "<", ">", "|", ":".
    /// </remarks>
    /// <param name="strDirectory">[IN] A single directory, without trailing slash ("/").</param>
    void AppendDirectory(const string_z &strDirectory);

    /// <summary>
    /// Resolves a relative path against an absolute path and stores the target path.
    /// </summary>
    /// <remarks>
    /// The resident path must be absolute. It can be relative only and only if it starts with a tilde ("~/") on Unix-based systems.<br/>
    /// Path segments formed only by one dot (".") are removed. Path segments formed only by two dots ("..") are removed and imply the removal of its 
    /// previous segment unless it is: a drive (Windows only), a tilde (user's home, on Unix-based systems).<br/>
    /// If the relative path has a filename, it will replace the resident's; otherwise, the filename of the resident path will remain the same.<br/>
    /// Example:<br/>
    /// - Absolute path: "/a/b/c/file1"<br/>
    /// - Relative path: "./../file2"<br/>
    /// - Resultant target path: "/a/b/file2"
    /// </remarks>
    /// <param name="relativePath">[IN] A relative path. It can be absolute if and only if it starts with a slash ("/") and the resident path is absolute;
    /// the entire path will be replaced with the input path. If the resident path has a drive (Windows only), it will be maintained. It cannot be empty.</param>
    void Resolve(const Path &relativePath);

    /// <summary>
    /// Resolves the path against the current working directory.
    /// </summary>
    /// <remarks>
    /// The path must be relative. It can be absolute if and only if it starts with a slash ("/") on Windows.
    /// </remarks>
    /// <returns>
    /// A string that contains the absolute path.
    /// </returns>
    string_z GetAbsolutePath() const;

    /// <summary>
    /// Calculates a relative path to the current working directory.
    /// </summary>
    /// <remarks>
    /// The path must be absolute.<br/>
    /// The file name of the resident path is used in the result.<br/>
    /// If one of the paths has hostname, the other must have it too. Besides, both hostnames must be the same.<br/>
    /// On Windows, if one of the paths has drive, the other must have it too. Besides, both drives must be the same.<br/>
    /// On Unix-based systems, if one of the paths starts with a tilde ("~"), the other must start with it too.<br/>
    /// Example:<br/>
    /// - Current working directory: "/a/b/c/"<br/>
    /// - Resident path: "/a/c/d/file2"<br/>
    /// - Resultant relative path: "./../../b/c/file2"
    /// </remarks>
    /// <returns>
    /// A string that contains the relative path from resident path to the current working directory. If the path is not valid, an empty string is returned.
    /// </returns>
    string_z GetRelativePath() const;
    
    /// <summary>
    /// Calculates a relative path to another absolute path.
    /// </summary>
    /// <remarks>
    /// The resident path must be absolute.<br/>
    /// The file name of the resident path is used in the result.<br/>
    /// If one of the paths has hostname, the other must have it too. Besides, both hostnames must be the same.<br/>
    /// On Windows, if one of the paths has drive, the other must have it too; however, if one of them starts with a slash ("/"), it will be considered as if it had the same drive. 
    /// Besides, both drives must be the same.<br/>
    /// On Unix-based systems, if one of the paths starts with a tilde ("~"), the other must start with it too.
    /// Example:<br/>
    /// - Current working directory: "/a/b/c/"<br/>
    /// - Resident path: "/a/c/d/file2"<br/>
    /// - Resultant relative path: "./../../b/c/file2"
    /// </remarks>
    /// <param name="absolutePath">[IN] An absolute path.</param>
    /// <returns>
    /// A string that contains the relative path from resident path to the input path. If paths are not valid, an empty string is returned.
    /// </returns>
    string_z GetRelativePathTo(const Path &absolutePath) const;
    
    /// <summary>
    /// Gets the last directory in the path.
    /// </summary>
    /// <remarks>
    /// The filename and the hostname, if any, are ignored.
    /// </remarks>
    /// <returns>
    /// The name of the last directory, without separators. If the full directory is just a separator ("/") or a drive specifier ("x:/"), the result is an empty string.
    /// </returns>
    string_z GetLastDirectory() const;
    
    /// <summary>
    /// Gets the full path as a string.
    /// </summary>
    /// <returns>
    /// A string that contains the full path. Note that, if the path contains dot segments ("." or "..") they will not be resolved.
    /// </returns>
    string_z ToString() const;

protected:

#if defined(Z_OS_WINDOWS)
    
    /// <summary>
    /// Removes all the characters that are not allowed in a path.
    /// </summary>
    /// <remarks>
    /// On Windows, the following characters are neither allowed in a directory name nor in a file name: "*", "?", "\", """, "<", ">", "|", ":".
    /// </remarks>
    /// <param name="strPathToBeReplaced">[IN/OUT] The path that will be modified.</param>
    static void _RemoveNotAllowedCharactersInPath(string_z &strPathToBeReplaced);

#endif

    /// <summary>
    /// Removes all the characters that are not allowed in a hostname.
    /// </summary>
    /// <remarks>
    /// The only valid characters in a hostname are: "[a-z]", "[A-Z]", "[0-9]", "-". On Unix-based systems, the at sign ("@") is admitted too. Hostnames cannot start with an hyphen ("-")<br/>
    /// The only valid characters in an IP are: "[", "]", "[0-9]", ".".
    /// </remarks>
    /// <param name="strHostnameToBeReplaced">[IN/OUT] The hostname that will be modified.</param>
    static void _RemoveNotAllowedCharactersInHostname(string_z &strHostnameToBeReplaced);
    
    /// <summary>
    /// Validates the format of a hostname.
    /// </summary>
    /// <remarks>
    /// It checks that the hostname is not empty, it does not start with an hyphen ("-") and, if it contains an IP, it is well-formatted. IPs must be compound of 4 numbers 
    /// separated by periods, where every number must be present and be equal to or lower than 255. IPs may be enclosed between square brackets.
    /// </remarks>
    /// <param name="strHostname">[IN] The hostname to be validated.</param>
    /// <returns>
    /// True if the hostname is valid; False otherwise.
    /// </returns>
    static bool _ValidateHostname(const string_z &strHostname);
    
    /// <summary>
    /// Removes the dot segments ("." and "..") from the path.
    /// </summary>
    /// <remarks>
    /// This process is described in the RFC 3986, section 5.2.4. Every segment that consists in only one or two dots is removed.
    /// Besides, in the second case, the previous segment is removed too, unless it is the first segment. As an exception to this rule,
    /// consecutive dot segments that appear at the beginning of relative paths will not be removed.
    /// </remarks>
    /// <param name="strPathToResolve">[IN/OUT] The path segments which may or may not be removed.</param>
    static void _ResolveDotSegments(string_z &strPathToResolve);

    /// <summary>
    /// Separates the hostname from the rest of the path.
    /// </summary>
    /// <param name="strPath">[IN/OUT] The full path from which the hostname will be obtained and removed.</param>
    /// <param name="strHostname">[OUT] The obtained hostname.</param>
    static void _ExtractHostnameFromPath(string_z &strPath, string_z &strHostname);
    
    /// <summary>
    /// Separates the filename from the rest of the path.
    /// </summary>
    /// <param name="strPath">[IN/OUT] The full path from which the filename will be obtained and removed.</param>
    /// <param name="strFilename">[OUT] The obtained filename.</param>
    static void _ExtractFilenameFromPath(string_z &strPath, string_z &strFilename);

    /// <summary>
    /// Checks whether a hostname is actually an IP or not.
    /// </summary>
    /// <remarks>
    /// If the hostname starts with a number or an opening square bracket ("["), it is an IP.
    /// </remarks>
    /// <param name="strHostname">[IN] The hostname to be checked.</param>
    /// <returns>
    /// True if the hostname is an IP; False otherwise.
    /// </returns>
    static bool _IsIP(const string_z &strHostname);

    /// <summary>
    /// Validates the format of an IP.
    /// </summary>
    /// <remarks>
    /// IPs must be compound of 4 numbers divided by periods, where every number must be present and be equal to or lower than 255. IPs may be enclosed between square brackets.
    /// </remarks>
    /// <param name="strHostname">[IN] The IP to be validated.</param>
    /// <returns>
    /// True if the IP is valid; False otherwise.
    /// </returns>
    static bool _ValidateIP(const string_z &strHostname);


    // PROPERTIES
    // ---------------
public:
    
    /// <summary>
    /// Gets the path separator.
    /// </summary>
    /// <returns>
    /// A string containing the path separator. On Windows, Linux and Mac, this will be a slash ("/").
    /// </returns>
    static const string_z& GetPathSeparator();

    /// <summary>
    /// Checks whether the path is absolute or not.
    /// </summary>
    /// <remarks>
    /// Paths that start with either a slash ("/") or a drive (e.g. "x:/") are considered as absolute.
    /// </remarks>
    /// <returns>
    /// True if the path is absolute; False if it is relative.
    /// </returns>
    bool IsAbsolute() const;

    /// <summary>
    /// Gets the filename only, without the file extension, if any.
    /// </summary>
    /// <returns>
    /// The filename with neither the extension nor the separation dot. If there is no filename, it returns empty.
    /// </returns>
    string_z GetFilenameWithoutExtension() const;

    /// <summary>
    /// Gets the filename only, if any.
    /// </summary>
    /// <returns>
    /// The full filename only. If there is no filename, it returns empty.
    /// </returns>
    string_z GetFilename() const;

    /// <summary>
    /// Gets the file extension only, if any.
    /// </summary>
    /// <returns>
    /// The file extension, without the separation dot. If there is no extension, it returns empty.
    /// </returns>
    string_z GetFileExtension() const;
    
    /// <summary>
    /// Gets the full directory, this means the sequence of path segments between the hostname, if any, and the filename, if any.
    /// </summary>
    /// <returns>
    /// A string that contains the directory. It will always end with a trailing separator.
    /// </returns>
    string_z GetDirectory() const;
    
    /// <summary>
    /// Gets the root directory of the path. Root directories are those that do not have a parent directory.
    /// </summary>
    /// <remarks>
    /// Only absolute paths have root directory (see exceptions below). If the path is relative, the result will be an empty string.<br/>
    /// On Windows, the root directory can be either a drive or a single separator ("/"), which refers to the drive of the current directory.<br/>
    /// On Unix-based systems, the root directory is a single separator ("/"), even if the path starts with a tilde ("~") which is considered an 
    /// abbreviation of the user's "home" directory; this is the only exception for relative paths.<br/>
    /// If the path contains a hostname, it will be included in the result along with the first segment of the directory, if any.<br/>
    /// Examples:<br/>
    /// - "//hostname/dir1/dir2/" --> "//hostname/dir1/"<br/>
    /// - "/dir1/dir2/" --> "/"<br/>
    /// - "x:/dir1/" --> "x:/"<br/>
    /// - "~/dir1/" --> "/"<br/>
    /// - ./dir1/ --> ""
    /// </remarks>
    /// <returns>
    /// A string that contains the root directory. It will always end with a trailing separator. If the path is relative, resultant string will be empty.
    /// </returns>
    string_z GetRoot() const;
    
    /// <summary>
    /// Gets the hostname.
    /// </summary>
    /// <returns>
    /// A string that contains the hostname, without separators.
    /// </returns>
    string_z GetHostname() const;
    
    /// <summary>
    /// Indicates whether the path refers to a file or not.
    /// </summary>
    /// <returns>
    /// True if the path refers to a file; False otherwise.
    /// </returns>
    bool IsFile() const;
    
    /// <summary>
    /// Indicates whether the path refers to a directory or not.
    /// </summary>
    /// <returns>
    /// True if the path refers to a directory; False otherwise.
    /// </returns>
    bool IsDirectory() const;
    
    /// <summary>
    /// Indicates whether the path starts with a drive letter or not (Windows only).
    /// </summary>
    /// <returns>
    /// True if the path starts with a drive letter; False otherwise. On all operating systems but Windows, it will always return False.
    /// </returns>
    bool HasDrive() const;
    
    /// <summary>
    /// Indicates whether the path starts with a hostname or not.
    /// </summary>
    /// <returns>
    /// True if the path starts with a hostname; False otherwise.
    /// </returns>
    bool HasHostname() const;
    
    /// <summary>
    /// Indicates whether the root directory of the path can be deduced or not.
    /// </summary>
    /// <remarks>
    /// Only absolute paths have root directory (see exceptions below).<br/>
    /// On Windows, the root directory can be either a drive or a single separator ("/"), which refers to the drive of the current directory.<br/>
    /// On Unix-based systems, the root directory is a single separator ("/"), even if the path starts with a tilde ("~") which is considered an 
    /// abbreviation of the user's "home" directory; this is the only exception for relative paths.<br/>
    /// </remarks>
    /// <returns>
    /// True if the path has a root directory; False otherwise.
    /// </returns>
    bool HasRoot() const;
    
    /// <summary>
    /// Replaces the filename, keeping the same file extension.
    /// </summary>
    /// <remarks>
    /// The length of a filename cannot exceed 255 characters (including the file extension).<br/>
    /// On Windows, the following characters are not allowed in a file name: "*", "?", "\", """, "<", ">", "|", ":", "/".
    /// </remarks>
    /// <param name="strFilename">[IN] The filename to be set. Any invalid character will be removed.</param>
    void SetFilename(const string_z &strFilename);
    
    /// <summary>
    /// Sets the filename, including the file extension.
    /// </summary>
    /// <remarks>
    /// The length of a filename cannot exceed 255 characters (including the file extension).<br/>
    /// On Windows, the following characters are not allowed in a file name: "*", "?", "\", """, "<", ">", "|", ":", "/".
    /// </remarks>
    /// <param name="strFilenameAndExtension">[IN] The filename and the extension to be set. Any invalid character will be removed.</param>
    void SetFilenameAndExtension(const string_z &strFilenameAndExtension);
    
    /// <summary>
    /// Sets the hostname.
    /// </summary>
    /// <remarks>
    /// The only valid characters in a hostname are: "[a-z]", "[A-Z]", "[0-9]", "-". On Unix-based systems, the at sign ("@") is admitted too. Hostnames cannot start with an hyphen ("-").<br/>
    /// The only valid characters in an IP (v4) are: "[", "]", "[0-9]", ".". IPs must be compound of 4 numbers separated by periods, where every number must be present and be equal to or 
    /// lower than 255. IPs may be enclosed between square brackets.<br/>
    /// On Windows, adding a hostname when the path starts with a drive letter will result in an invalid path.
    /// </remarks>
    /// <param name="strHostname">[IN] The hostname to be set, without separators. It can be either a name or an IP. Any invalid character will be removed.</param>
    void SetHostname(const string_z &strHostname);
    
    /// <summary>
    /// Sets the entire directory, this means the sequence of path segments between the host name, if any, and the filename, if any.
    /// </summary>
    /// <remarks>
    /// On Windows, the following characters are not allowed in a directory name: "*", "?", "\", """, "<", ">", "|", ":", "/". Colons are allowed only to specity a drive letter. 
    /// Slashes and backslashes are allowed only as separators.<br/>
    /// On Unix-based systems, slashes are allowed only as separators.<br/>
    /// On Windows, adding a directory that starts with a drive letter when the path already has a hostname will result in an invalid path.<br/>
    /// </remarks>
    /// <param name="strDirectory">[IN] The directory to be set. Any invalid character will be removed. Backslashes ("\") will be replaced with slashes ("/"). If it does not have a trailing separator, 
    /// it will be added. If it is empty and the path contains a hostname, the directory "/" will be set; if the path does not contain a hostname, the directory "./" will be set instead.</param>
    void SetDirectory(const string_z &strDirectory);


    // ATTRIBUTES
    // ---------------
protected:

    /// <summary>
    /// The hostname, with neither the leading separator ("//") nor the trailing separator ("/").
    /// </summary>
    string_z m_strHostname;

    /// <summary>
    /// The path (directories), with neither the hostname nor the filename.
    /// </summary>
    string_z m_strPath;

    /// <summary>
    /// The filename.
    /// </summary>
    string_z m_strFilename;

};

} // namespace z

#endif // __PATH__
