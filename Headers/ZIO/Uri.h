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

#ifndef __URI__
#define __URI__

#include "ZIO/IOModuleDefinitions.h"
#include "ZCommon/DataTypes/DataTypesDefinitions.h"
#include "ZContainers/ArrayDynamic.h"
#include <math.h>


#ifdef Z_COMPILER_MSVC
    #pragma warning( push )
    #pragma warning( disable: 4251 ) // This warning occurs when using a template specialization as attribute
#endif


namespace z
{

/// <summary>
/// Represents a URI (Uniform Resource Identifier) as described in the RFC 3986.
/// </summary>
/// <remarks>
/// URIs provide a simple way to identify a resource in a system through a string which consists of several components: scheme, 
/// authority (divided in user information, host and port), path, query and fragment.<br/>
/// URIs can be either absolute, describing exactly how to find the resource, or relative, acting as a reference that depends on 
/// another URI (a base URI, which is absolute); in order to get the target URI, the relative URI has to be resolved against the base URI.<br/>
/// Although two strings are not exactly the same, the URIs they contain may be equivalent. In order to compare two URIs, they have to be normalized.
/// Every instance of this class is guaranteed to be normalized; although this is a slow process, it allows the rest of operations to be much faster.<br/>
/// <br/>
/// For more information about URIs, read: http://www.ietf.org/rfc/rfc3986.txt .
/// </remarks>
class Z_IO_MODULE_SYMBOLS Uri
{
    // TYPEDEFS
    // ---------------
private:

    /// <summary>
    /// Type used to store a bit field of 8 bits.
    /// </summary>
    typedef u8_z TBitField;


    // CONSTANTS
    // ---------------
protected:

    /// <summary>
    /// Flag that indicates whether the scheme is defined in the URI or not.
    /// </summary>
    static const TBitField FLAG_SCHEME_IS_DEFINED;

    /// <summary>
    /// Flag that indicates whether the authority is defined in the URI or not.
    /// </summary>
    static const TBitField FLAG_AUTHORITY_IS_DEFINED;

    /// <summary>
    /// Flag that indicates whether the query is defined in the URI or not.
    /// </summary>
    static const TBitField FLAG_ZUERY_IS_DEFINED;

    /// <summary>
    /// Flag that indicates whether the fragment is defined in the URI or not.
    /// </summary>
    static const TBitField FLAG_FRAGMENT_IS_DEFINED;

    /// <summary>
    /// Flag that indicates whether the user information is defined in the URI or not.
    /// </summary>
    static const TBitField FLAG_USERINFO_IS_DEFINED;

    /// <summary>
    /// Flag that indicates whether the host is defined in the URI or not.
    /// </summary>
    static const TBitField FLAG_HOST_IS_DEFINED;

    /// <summary>
    /// Flag that indicates whether the port is defined in the URI or not.
    /// </summary>
    static const TBitField FLAG_PORT_IS_DEFINED;
    
    /// <summary>
    /// A dot segment compound of one dot (".").
    /// </summary>
    static const string_z SINGLE_DOT_SEGMENT;
    
    /// <summary>
    /// A dot segment compound of two dots ("..").
    /// </summary>
    static const string_z DOUBLE_DOT_SEGMENT;
    
    /// <summary>
    /// Two slash characters ("//").
    /// </summary>
    static const string_z DOUBLE_SLASH;
    
    /// <summary>
    /// A colon character (":").
    /// </summary>
    static const string_z CHAR_COLON;
    
    /// <summary>
    /// A slash character ("/").
    /// </summary>
    static const string_z CHAR_SLASH;
    
    /// <summary>
    /// A question mark character ("?").
    /// </summary>
    static const string_z CHAR_ZUESTION_MARK;
    
    /// <summary>
    /// A number sign character ("#").
    /// </summary>
    static const string_z CHAR_NUMBER_SIGN;
    
    /// <summary>
    /// An opening square bracket character ("[").
    /// </summary>
    static const string_z CHAR_OPENING_SQUARE_BRACKET;
    
    /// <summary>
    /// A closing square bracket character ("]").
    /// </summary>
    static const string_z CHAR_CLOSING_SQUARE_BRACKET;
    
    /// <summary>
    /// An at sign character ("@").
    /// </summary>
    static const string_z CHAR_AT_SIGN;
    
    /// <summary>
    /// An exclamation mark character ("!").
    /// </summary>
    static const string_z CHAR_EXCLAMATION_MARK;
    
    /// <summary>
    /// A dollar sign character ("$").
    /// </summary>
    static const string_z CHAR_DOLLAR_SIGN;
    
    /// <summary>
    /// An ampersand character ("&").
    /// </summary>
    static const string_z CHAR_AMPERSAND;
    
    /// <summary>
    /// An apostrophe character ("'").
    /// </summary>
    static const string_z CHAR_APOSTROPHE;
    
    /// <summary>
    /// A comma character (",").
    /// </summary>
    static const string_z CHAR_COMMA;
    
    /// <summary>
    /// An opening parentheses character ("(").
    /// </summary>
    static const string_z CHAR_OPENING_PARENTHESES;
    
    /// <summary>
    /// A closing parentheses character (")").
    /// </summary>
    static const string_z CHAR_CLOSING_PARENTHESES;
    
    /// <summary>
    /// A semicolon character (";").
    /// </summary>
    static const string_z CHAR_SEMICOLON;
    
    /// <summary>
    /// An asterisk character ("*").
    /// </summary>
    static const string_z CHAR_ASTERISK;
    
    /// <summary>
    /// An equal sign character ("=").
    /// </summary>
    static const string_z CHAR_EUAL_SIGN;
    
    /// <summary>
    /// A plus sign character ("+").
    /// </summary>
    static const string_z CHAR_PLUS_SIGN;
    
    /// <summary>
    /// A percent sign character ("%").
    /// </summary>
    static const string_z CHAR_PERCENT_SIGN;


    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Constructor that receives a string which contains a URI.
    /// </summary>
    /// <remarks>
    /// The input string will be decomposed to get all the components of the URI. Then, every part will be normalized.
    /// </remarks>
    /// <param name="strUri">[IN] A string that contains a URI. The URI may be absolute or relative, it may define every component 
    /// or not and may not be normalized. Remember that absolute URIs must define the scheme. No validation is performed. Empty strings are not allowed.</param>
    explicit Uri(const string_z &strUri);


    // METHODS
    // ---------------
public:
    
    /// <summary>
    /// Assignment operator that copies another URI.
    /// </summary>
    /// <remarks>
    /// Every component is copied as is, no additional processing is performed.
    /// </remarks>
    /// <param name="uri">[IN] The other URI to be copied.</param>
    /// <returns>
    /// A reference to the resultant copy.
    /// </returns>
    Uri& operator=(const Uri &uri);
    
    /// <summary>
    /// Assignment operator that receives a string which contains a URI.
    /// </summary>
    /// <remarks>
    /// The input string will be decomposed to get all the components of the URI. Then, every part will be normalized.
    /// </remarks>
    /// <param name="strUri">[IN] A string that contains a URI. The URI may be absolute or relative, it may define every component 
    /// or not and may not be normalized. Remember that absolute URIs must define the scheme. No validation is performed. Empty strings are not allowed.</param>
    /// <returns>
    /// A reference to the resultant URI.
    /// </returns>
    Uri& operator=(const string_z &strUri);
    
    /// <summary>
    /// Equality operator that checks whether two URIs are equivalent.
    /// </summary>
    /// <remarks>
    /// Since URIs are normalized at their creation, the comparison consists in checking whether every component is exactly the same.<br/>
    /// If URIs differ only in the trailing path separator ("/"), they will be considered different.
    /// </remarks>
    /// <param name="uri">[IN] The other URI to compare to.</param>
    /// <returns>
    /// True if URIs are equivalent; False otherwise.
    /// </returns>
    bool operator==(const Uri &uri) const;
    
    /// <summary>
    /// Equality operator that checks whether two URIs are not equivalent.
    /// </summary>
    /// <remarks>
    /// Since URIs are normalized at their creation, the comparison consists in checking whether every component is not exactly the same.<br/>
    /// If URIs differ only in the trailing path separator ("/"), they will be considered different.
    /// </remarks>
    /// <param name="uri">[IN] The other URI to compare to.</param>
    /// <returns>
    /// True if URIs are not equivalent; False otherwise.
    /// </returns>
    bool operator!=(const Uri &uri) const;
    
    /// <summary>
    /// Resolves a reference URI against an absolute URI and stores the target URI.
    /// </summary>
    /// <remarks>
    /// The process is described in the RFC 3986, section 5.<br/>
    /// The resident URI must be absolute.<br/>
    /// Example:<br/>
    /// - Absolute URI / base URI: "http://a/b/c/d?q#f"<br/>
    /// - Relative reference URI: "./../g?y"<br/>
    /// - Resultant target URI: "http://a/b/g?y"
    /// </remarks>
    /// <param name="relativeUri">[IN] The relative reference URI.</param>
    void Resolve(const Uri &relativeUri);

    /// <summary>
    /// Gets the full normalized URI as a string.
    /// </summary>
    /// <remarks>
    /// The process is described in the RFC 3986, section 5.3.
    /// </remarks>
    /// <returns>
    /// A string that contains the full normalized URI.
    /// </returns>
    string_z ToString() const;

    /// <summary>
    /// Encodes a character sequence so some characters are "percent-encoded", following certain rules for path segments.
    /// </summary>
    /// <remarks>
    /// Characters that are not unreserved, a subdelimiter, a colon (":") or an at sign("@") are encoded.<br/>
    /// The encoding algorithm is described in the RFC 3986, section 2.1. For every character that must be encoded:<br/>
    /// - It is encoded as UTF-8.<br/>
    /// - Every code unit is transformed to hexadecimal (upper-case).<br/>
    /// - A percent sign ("%") is put before every code unit.<br/>
    /// - The original character is replaced by its percent-encoded version.
    /// </remarks>
    /// <param name="strInput">[IN] The string to encode.</param>
    /// <param name="strOutput">[OUT] The result of the encoding process. The same string used as input can be used to store the result.</param>
    static void EncodePathSegment(const string_z &strInput, string_z &strOutput);
    
    /// <summary>
    /// Encodes a character sequence so some characters are "percent-encoded", following certain rules for queries and fragments.
    /// </summary>
    /// <remarks>
    /// Characters that are not unreserved, a subdelimiter, a colon (":"), an at sign("@"), a slash ("/") or a question mark ("?") are encoded.<br/>
    /// The encoding algorithm is described in the RFC 3986, section 2.1. For every character that must be encoded:<br/>
    /// - It is encoded as UTF-8.<br/>
    /// - Every code unit is transformed to hexadecimal (upper-case).<br/>
    /// - A percent sign ("%") is put before every code unit.<br/>
    /// - The original character is replaced by its percent-encoded version.
    /// </remarks>
    /// <param name="strInput">[IN] The string to encode.</param>
    /// <param name="strOutput">[OUT] The result of the encoding process. The same string used as input can be used to store the result.</param>
    static void EncodeQueryOrFragment(const string_z &strInput, string_z &strOutput);
    
    /// <summary>
    /// Decodes a character sequence so some characters are "percent-decoded", following certain rules.
    /// </summary>
    /// <remarks>
    /// Every "percent-encoded" character (which is preceded by a percent sign ("%")) is decoded as follows:<br/>
    /// - The hexadecimal value is transformed into an integer value, which is a code unit.<br/>
    /// - All code units that are contiguous are encoded together using the string's default text encoding.<br/>
    /// - Percent signs along with the hexadecimal values are replaced with the actual characters in the output string.
    /// </remarks>
    /// <param name="strInput">[IN] The string to decode.</param>
    /// <param name="strOutput">[OUT] The result of the decoding process. The same string used as input can be used to store the result.</param>
    static void Decode(const string_z &strInput, string_z &strOutput);

protected:
    
    /// <summary>
    /// Decomposes the authority component of a URI into the user information, the host and the port, if any, and stores them in the object.
    /// </summary>
    /// <remarks>
    /// Sub-component separators are not stored anywhere.
    /// </remarks>
    /// <param name="strInputUri">[IN] The string that contains the full URI whose authority component is to be decomposed.</param>
    /// <param name="nAuthorityStartPosition">[IN] The position (zero-based index) of the first occurrence of the authority separator ("//").
    /// It may be equal to string_z::PATTERN_NOT_FOUND.</param>
    /// <param name="nPathStartPosition">[IN] The position (zero-based index) of the first occurrence of the path separator ("/").
    /// It may be equal to string_z::PATTERN_NOT_FOUND.</param>
    /// <param name="nQueryStartPosition">[IN] The position (zero-based index) of the first occurrence of the query separator ("?").
    /// It may be equal to string_z::PATTERN_NOT_FOUND.</param>
    /// <param name="nFragmentStartPosition">[IN] The position (zero-base index) of the first occurrence of the fragment separator ("#").
    /// It may be equal to string_z::PATTERN_NOT_FOUND.</param>
    /// <param name="definedComponents">[IN/OUT] The bit field that indicates whether every component is present or not in the URI. 
    /// It may be modified by the method.</param>
    virtual void DecomposeAuthority(const string_z &strInputUri, 
                                    const int nAuthorityStartPosition, 
                                    const int nPathStartPosition, 
                                    const int nQueryStartPosition, 
                                    const int nFragmentStartPosition, 
                                    Uri::TBitField &definedComponents);
    
    /// <summary>
    /// Decomposes the path into segments and stores them in the object.
    /// </summary>
    /// <remarks>
    /// Segment separators are not stored anywhere.
    /// </remarks>
    /// <param name="strInputUri">[IN] The string that contains the full URI whose path component is to be decomposed.</param>
    /// <param name="nPathStartPosition">[IN] The position (zero-based index) of the first occurrence of the path separator ("/").
    /// It may be equal to string_z::PATTERN_NOT_FOUND.</param>
    /// <param name="nQueryStartPosition">[IN] The position (zero-based index) of the first occurrence of the query separator ("?").
    /// It may be equal to string_z::PATTERN_NOT_FOUND.</param>
    /// <param name="nFragmentStartPosition">[IN] The position (zero-base index) of the first occurrence of the fragment separator ("#").
    /// It may be equal to string_z::PATTERN_NOT_FOUND.</param>
    virtual void DecomposePath(const string_z &strInputUri, 
                               const int nPathStartPosition, 
                               const int nQueryStartPosition, 
                               const int nFragmentStartPosition);

    /// <summary>
    /// Removes the dot segments ("." and "..") from the path.
    /// </summary>
    /// <remarks>
    /// This process is described in the RFC 3986, section 5.2.4. Every segment that consists in only one or two dots is removed.
    /// Besides, in the second case, the previous segment is removed too, unless it is the first segment. As an exception to this rule,
    /// consecutive dot segments that appear at the beginning of relative URIs will not be removed.
    /// </remarks>
    /// <param name="arPathSegments">[IN/OUT] The path segments which may or may not be removed.</param>
    static void RemoveDotSegments(ArrayDynamic<string_z> &arPathSegments);
    
    /// <summary>
    /// Normalizes the URI.
    /// </summary>
    /// <remarks>
    /// The normalization process is described in the RFC 3986, section 6.2, and includes:<br/>
    /// - Removal of dot segments, which may imply to remove other segments (path only).<br/>
    /// - Decoding any percent-encoded character.<br/>
    /// - Lower-casing letters (scheme and authority only).<br/>
    /// - Percent-encoding any character that is not: unreserved, a subdelimiter, a colon (":") or an at sign("@") (path, query and fragment only).<br/>
    /// <br/>
    /// This process does not affect the original string (see GetOriginalString method).<br/>
    /// Since the normalization of the URI may differ depending on the scheme (http, ftp, gile, etc.), the process can
    /// be customized in derived classes. See Normalize<component> methods.
    /// </remarks>
    virtual void Normalize();

    /// <summary>
    /// Normalizes the user information.
    /// </summary>
    /// <remarks>
    /// This implementation only lowercases the entire sub-component.
    /// </remarks>
    virtual void NormalizeUserInfo();
    
    /// <summary>
    /// Normalizes the host.
    /// </summary>
    /// <remarks>
    /// This implementation only lowercases the entire sub-component.
    /// </remarks>
    virtual void NormalizeHost();
    
    /// <summary>
    /// Normalizes the port.
    /// </summary>
    /// <remarks>
    /// This implementation does nothing.
    /// </remarks>
    virtual void NormalizePort();
    
    /// <summary>
    /// Normalizes the path.
    /// </summary>
    /// <remarks>
    /// This implementation includes:<br/>
    /// - Removal of dot segments, which may imply to remove other segments.<br/>
    /// - Decoding any percent-encoded character.<br/>
    /// - Percent-encoding any character that is not: unreserved, a subdelimiter, a colon (":") or an at sign("@").
    /// </remarks>
    virtual void NormalizePath();
    
    /// <summary>
    /// Normalizes the query.
    /// </summary>
    /// <remarks>
    /// This implementation includes:<br/>
    /// - Decoding any percent-encoded character.<br/>
    /// - Percent-encoding any character that is not: unreserved, a subdelimiter, a colon (":"), an at sign("@") a slash ("/") or a question mark ("?").
    /// </remarks>
    virtual void NormalizeQuery();
    
    /// <summary>
    /// Normalizes the fragment.
    /// </summary>
    /// <remarks>
    /// This implementation includes:<br/>
    /// - Decoding any percent-encoded character.<br/>
    /// - Percent-encoding any character that is not: unreserved, a subdelimiter, a colon (":"), an at sign("@") a slash ("/") or a question mark ("?").
    /// </remarks>
    virtual void NormalizeFragment();

private:
    
    /// <summary>
    /// Normalizes the scheme.
    /// </summary>
    /// <remarks>
    /// This implementation only lowercases the entire component.
    /// </remarks>
    void NormalizeScheme();

    /// <summary>
    /// Encodes a character sequence so some characters are "percent-encoded", following certain rules depending on whether it is
    /// a path segment, a query or a fragment.
    /// </summary>
    /// <remarks>
    /// Characters that are not: unreserved, a subdelimiter, a colon (":"), an at sign("@"), a slash* ("/") or a question mark* ("?") are encoded.<br/>
    /// Characters marked with an asterisk above are included only if the input string is a fragment or a query.<br/>
    /// The encoding algorithm is described in the RFC 3986, section 2.1. For every character that must be encoded:<br/>
    /// - It is encoded as UTF-8.<br/>
    /// - Every code unit is transformed to its hexadecimal (upper-case).<br/>
    /// - A percent sign ("%") is put before every code unit.<br/>
    /// - The original character is replaced by it percent-encoded version.
    /// </remarks>
    /// <param name="bIsPathSegment">[IN] Indicates whether the input strings belongs to either a path segment (true) or a query / fragment (false).</param>
    /// <param name="strInput">[IN] The string to encode.</param>
    /// <param name="strOutput">[OUT] The result of the encoding process. The same string used as input can be used to store the result.</param>
    static void Encode(const bool bIsPathSegment, const string_z &strInput, string_z &strOutput);

    /// <summary>
    /// Decomposes a URI into its components, including the authority sub-components, and stores them in the object.
    /// </summary>
    /// <remarks>
    /// The component definition bit field is modified by this method.<br/>
    /// Component separators are not stored anywhere.
    /// </remarks>
    /// <param name="strInputUri">[IN] The URI to decompose.</param>
    void DecomposeUri(const string_z &strInputUri);
    
    /// <summary>
    /// Checks whether a character is not in the group of allowed characters in a URI component and therefore should be percent-encoded.
    /// The result depends on whether the character belongs to either a path segment or a query / fragment.
    /// </summary>
    /// <remarks>
    /// Allowed characters are: "[A-Z]", "[a-z]", "[0-9]", "_", "~", ".", "-", "&", "'", "*", "(", ")", ",", "$", "=", "!", "%", "+", ";".<br/>
    /// If the character belongs to a query or a fragment, additional values are allowed: "?" and "/".
    /// </remarks>
    /// <param name="character">[IN] The character to be checked.</param>
    /// <returns>
    /// True if the character should be percent-encoded; False otherwise.
    /// </returns>
    static bool IsEncodable(const char_z &character, const bool bIsPathSegment);
    
    /// <summary>
    /// Removes the dot segments ("." and "..") at the beginning of the path.
    /// </summary>
    /// <param name="arPathSegments">[IN/OUT] The path segments which may or may not be removed.</param>
    static void RemoveFirstDotSegments(ArrayDynamic<string_z> &arPathSegments);


    // PROPERTIES
    // ---------------
public:

    /// <summary>
    /// Gets the authority component of the URI.
    /// </summary>
    /// <returns>
    /// The full authority component without including the initial separator ("//").
    /// </returns>
    string_z GetAuthority() const;

    /// <summary>
    /// Gets the fragment component of the URI.
    /// </summary>
    /// <returns>
    /// The full fragment component without including the initial separator ("#").
    /// </returns>
    string_z GetFragment() const;
    
    /// <summary>
    /// Gets the host sub-component of the URI.
    /// </summary>
    /// <returns>
    /// The host sub-component of the authority. If it is an IPv6, it will include the square brackets.
    /// </returns>
    string_z GetHost() const;
    
    /// <summary>
    /// Gets the path component of the URI.
    /// </summary>
    /// <returns>
    /// The full path component. If it is a relative URI, the initial separator ("/") will be included if it started with a separator. If the authority component is defined, 
    /// the path will include the initial separator. It will not include a separator at the end if it did not have one.
    /// </returns>
    string_z GetPath() const;
    
    /// <summary>
    /// Gets the port sub-component of the URI.
    /// </summary>
    /// <returns>
    /// The port sub-component of the authority without including the initial separator (":").
    /// </returns>
    string_z GetPort() const;
    
    /// <summary>
    /// Gets the query component of the URI.
    /// </summary>
    /// <returns>
    /// The full query component without including the initial separator ("?").
    /// </returns>
    string_z GetQuery() const;
    
    /// <summary>
    /// Gets the scheme component of the URI.
    /// </summary>
    /// <returns>
    /// The scheme component without including the final separator (":").
    /// </returns>
    string_z GetScheme() const;
    
    /// <summary>
    /// Gets the user information sub-component of the URI.
    /// </summary>
    /// <returns>
    /// The user information sub-component of the authority without including the final separator ("@").
    /// </returns>
    string_z GetUserInfo() const;

    /// <summary>
    /// Gets the string that was provided originally to form the URI.
    /// </summary>
    /// <remarks>
    /// This string will be reset (set to empty) if any component of the URI is changed after its creation.
    /// </remarks>
    /// <returns>
    /// The original URI, without modifications.
    /// </returns>
    string_z GetOriginalString() const;

    /// <summary>
    /// Gets path of the URI as an array of segments.
    /// </summary>
    /// <returns>
    /// Array of segments of the path. If the path was empty, it will contain an empty string.
    /// </returns>
    ArrayDynamic<string_z> GetPathSegments() const;

    /// <summary>
    /// Indicates whether the URI is relative or not.
    /// </summary>
    /// <returns>
    /// True if the URI is a relative reference; False if it is an absolute URI.
    /// </returns>
    bool IsRelative() const;
    
    /// <summary>
    /// Sets the authority component of the URI.
    /// </summary>
    /// <remarks>
    /// If the path is not empty and does not start with a slash ("/"), a slash will be added at the beginning.<br/>
    /// The component will be normalized.<br/>
    /// The original string (see GetOriginalString method) will be reset since it will not match the modified URI.
    /// </remarks>
    /// <param name="strAuthority">[IN] The new authority. It must not contain the initial separator ("//"). It may contain the user information, 
    /// the host, the port or none of them (empty).</param>
    void SetAuthority(const string_z &strAuthority);

    /// <summary>
    /// Sets the fragment component of the URI.
    /// </summary>
    /// <remarks>
    /// The component will be normalized.<br/>
    /// The original string (see GetOriginalString method) will be reset since it will not match the modified URI.
    /// </remarks>
    /// <param name="strFragment">[IN] The new fragment. It must not contain the initial separator ("#"). It can be empty.</param>
    void SetFragment(const string_z &strFragment);
    
    /// <summary>
    /// Sets the host sub-component of the URI.
    /// </summary>
    /// <remarks>
    /// If the path is not empty and does not start with a slash ("/"), a slash will be added at the beginning.<br/>
    /// The sub-component will be normalized.<br/>
    /// The original string (see GetOriginalString method) will be reset since it will not match the modified URI.
    /// </remarks>
    /// <param name="strHost">[IN] The new host. It can be empty; in this case, the entire authority will be undefined.</param>
    void SetHost(const string_z &strHost);
    
    /// <summary>
    /// Sets the path component of the URI.
    /// </summary>
    /// <remarks>
    /// If the scheme is not defined and the first segment of the input path contains a colon (":"), a dot segment will be added at the start ("./").<br/>
    /// The component will be normalized.<br/>
    /// The original string (see GetOriginalString method) will be reset since it will not match the modified URI.
    /// </remarks>
    /// <param name="strPath">[IN] The new path. It can be empty; in such case, it will be considered as ".".</param>
    void SetPath(const string_z &strPath);
    
    /// <summary>
    /// Sets the query component of the URI.
    /// </summary>
    /// <remarks>
    /// The sub-component will be normalized.<br/>
    /// The original string (see GetOriginalString method) will be reset since it will not match the modified URI.
    /// </remarks>
    /// <param name="&strQuery">[IN] The new query. It can be empty.</param>
    void SetQuery(const string_z &strQuery);
    
    /// <summary>
    /// Sets the port sub-component of the URI.
    /// </summary>
    /// <remarks>
    /// If the authority is not already defined, the value will not be set.<br/>
    /// The sub-component will be normalized.<br/>
    /// The original string (see GetOriginalString method) will be reset since it will not match the modified URI.
    /// </remarks>
    /// <param name="strPort">[IN] The new port. It can be empty.</param>
    void SetPort(const string_z &strPort);

    /// <summary>
    /// Sets the scheme component of the URI.
    /// </summary>
    /// <remarks>
    /// If there was not a defined scheme and the first segment of the path contains a colon (":"), a dot segment will be added at the start ("./").<br/>
    /// The sub-component will be normalized.<br/>
    /// The original string (see GetOriginalString method) will be reset since it will not match the modified URI.
    /// </remarks>
    /// <param name="strScheme">[IN] The new scheme. It can be empty.</param>
    void SetScheme(const string_z &strScheme);
    
    /// <summary>
    /// Sets the user information sub-component of the URI.
    /// </summary>
    /// <remarks>
    /// If the authority is not already defined, the value will not be set.<br/>
    /// The sub-component will be normalized.<br/>
    /// The original string (see GetOriginalString method) will be reset since it will not match the modified URI.
    /// </remarks>
    /// <param name="strUserInfo">[IN] The new user information. It can be empty.</param>
    void SetUserInfo(const string_z &strUserInfo);


    // ATTRIBUTES
    // ---------------
protected:

    /// <summary>
    /// The host subcomponent of the authority.
    /// </summary>
    string_z m_strHost;

    /// <summary>
    /// The fragment component.
    /// </summary>
    string_z m_strFragment;

    /// <summary>
    /// The query component.
    /// </summary>
    string_z m_strQuery;

    /// <summary>
    /// The scheme component.
    /// </summary>
    string_z m_strScheme;

    /// <summary>
    /// The user information subcomponent of the authority.
    /// </summary>
    string_z m_strUserInfo;

    /// <summary>
    /// The port subcomponent of the authority.
    /// </summary>
    string_z m_strPort;

    /// <summary>
    /// The original string provided to construct the URI, without modifications.
    /// </summary>
    string_z m_strOriginalString;

    /// <summary>
    /// The path component.
    /// </summary>
    ArrayDynamic<string_z> m_arPathSegments;

    /// <summary>
    /// A bit field that indicates whether every component / sub-component is defined (1) or not (0). See FLAG_<component>_IS_DEFINED constants.
    /// </summary>
    TBitField m_definedComponents;
};

} // namespace z

#endif // __URI__
