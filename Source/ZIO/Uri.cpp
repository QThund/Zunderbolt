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

#include "ZIO/Uri.h"

#include "ZCommon/Assertions.h"

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

const Uri::TBitField Uri::FLAG_SCHEME_IS_DEFINED    = 0x01; // 0000 0001
const Uri::TBitField Uri::FLAG_AUTHORITY_IS_DEFINED = 0x02; // 0000 0010
const Uri::TBitField Uri::FLAG_ZUERY_IS_DEFINED     = 0x04; // 0000 0100
const Uri::TBitField Uri::FLAG_FRAGMENT_IS_DEFINED  = 0x08; // 0000 1000
const Uri::TBitField Uri::FLAG_USERINFO_IS_DEFINED  = 0x10; // 0001 0000
const Uri::TBitField Uri::FLAG_HOST_IS_DEFINED      = 0x20; // 0010 0000
const Uri::TBitField Uri::FLAG_PORT_IS_DEFINED      = 0x40; // 0100 0000


const string_z Uri::SINGLE_DOT_SEGMENT = ".";
const string_z Uri::DOUBLE_DOT_SEGMENT = "..";
const string_z Uri::DOUBLE_SLASH = "//";

const string_z Uri::CHAR_COLON = ":";
const string_z Uri::CHAR_SLASH = "/";
const string_z Uri::CHAR_ZUESTION_MARK = "?";
const string_z Uri::CHAR_NUMBER_SIGN   = "#";
const string_z Uri::CHAR_OPENING_SQUARE_BRACKET = "[";
const string_z Uri::CHAR_CLOSING_SQUARE_BRACKET = "]";
const string_z Uri::CHAR_AT_SIGN = "@";
const string_z Uri::CHAR_EXCLAMATION_MARK = "!";
const string_z Uri::CHAR_DOLLAR_SIGN = "$";
const string_z Uri::CHAR_AMPERSAND   = "&";
const string_z Uri::CHAR_APOSTROPHE  = "'";
const string_z Uri::CHAR_COMMA       = ",";
const string_z Uri::CHAR_OPENING_PARENTHESES = "(";
const string_z Uri::CHAR_CLOSING_PARENTHESES = ")";
const string_z Uri::CHAR_SEMICOLON    = ";";
const string_z Uri::CHAR_ASTERISK     = "*";
const string_z Uri::CHAR_EUAL_SIGN   = "=";
const string_z Uri::CHAR_PLUS_SIGN    = "+";
const string_z Uri::CHAR_PERCENT_SIGN = "%";


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |       CONSTRUCTORS         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

Uri::Uri(const string_z &strUri) : m_strOriginalString(strUri), 
                                     m_definedComponents(0)
{
    Z_ASSERT_ERROR(!strUri.IsEmpty(), "The input string cannot be empty. Empty URIs are not valid.");

    m_strOriginalString = strUri;
    this->DecomposeUri(strUri);
    this->Normalize();
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

Uri& Uri::operator=(const Uri &uri)
{
    if(this != &uri)
    {
        m_strHost = uri.m_strHost;
        m_arPathSegments = uri.m_arPathSegments;
        m_strFragment = uri.m_strFragment;
        m_strQuery = uri.m_strQuery;
        m_strScheme = uri.m_strScheme;
        m_strUserInfo = uri.m_strUserInfo;
        m_strPort = uri.m_strPort;
        m_strOriginalString = uri.m_strOriginalString;
        m_definedComponents = uri.m_definedComponents;
    }

    return *this;
}

Uri& Uri::operator=(const string_z &strUri)
{
    Z_ASSERT_ERROR(!strUri.IsEmpty(), "The input string cannot be empty. Empty URIs are not valid.");

    // The URI is reset to default values
    m_strHost = string_z::GetEmpty();
    m_arPathSegments.Clear();
    m_strFragment = string_z::GetEmpty();
    m_strQuery = string_z::GetEmpty();
    m_strScheme = string_z::GetEmpty();
    m_strUserInfo = string_z::GetEmpty();
    m_strPort = string_z::GetEmpty();;
    m_strOriginalString = string_z::GetEmpty();
    m_definedComponents = 0;

    // Creates the new URI
    m_strOriginalString = strUri;
    this->DecomposeUri(strUri);
    this->Normalize();
    return *this;
}

bool Uri::operator==(const Uri &uri) const
{
    return m_strHost == uri.m_strHost                     &&
           m_arPathSegments == uri.m_arPathSegments       &&
           m_strFragment == uri.m_strFragment             &&
           m_strQuery == uri.m_strQuery                   &&
           m_strScheme == uri.m_strScheme                 &&
           m_strUserInfo == uri.m_strUserInfo             &&
           m_strPort == uri.m_strPort                     &&
           m_definedComponents == uri.m_definedComponents;
}

bool Uri::operator!=(const Uri &uri) const
{
    return m_strHost != uri.m_strHost                     ||
           m_arPathSegments != uri.m_arPathSegments       ||
           m_strFragment != uri.m_strFragment             ||
           m_strQuery != uri.m_strQuery                   ||
           m_strScheme != uri.m_strScheme                 ||
           m_strUserInfo != uri.m_strUserInfo             ||
           m_strPort != uri.m_strPort                     ||
           m_definedComponents != uri.m_definedComponents;
}

void Uri::Resolve(const Uri &relativeUri)
{
    Z_ASSERT_ERROR(relativeUri.IsRelative(), "The input URI must be relative.");
    Z_ASSERT_ERROR(!this->IsRelative(), "The URI must be absolute to serve as a base URI.");

    // This class considers as a relative URI anyone that has no scheme. Therefore, the scheme is not checked but ignored.

    if(Uri::FLAG_AUTHORITY_IS_DEFINED & relativeUri.m_definedComponents)
    {
        m_strHost     = relativeUri.m_strHost;
        m_strPort     = relativeUri.m_strPort;
        m_strUserInfo = relativeUri.m_strUserInfo;
        m_strQuery    = relativeUri.m_strQuery;
        m_arPathSegments    = relativeUri.m_arPathSegments;
        m_definedComponents = relativeUri.m_definedComponents | Uri::FLAG_SCHEME_IS_DEFINED; // The relative URI does not have scheme
    }
    else
    {
        if(relativeUri.GetPath().IsEmpty())
        {
            // Uses the base path

            if(Uri::FLAG_ZUERY_IS_DEFINED & relativeUri.m_definedComponents)
            {
                m_strQuery = relativeUri.m_strQuery;
                m_definedComponents |= Uri::FLAG_ZUERY_IS_DEFINED;
            }
            // If not, it uses the base query
        }
        else
        {
            // If the relative URI starts with a slash ("/")
            if(relativeUri.m_arPathSegments[0].IsEmpty() && relativeUri.m_arPathSegments.GetCount() > 1U)
            {
                m_arPathSegments = relativeUri.m_arPathSegments;
            }
            else
            {
                // Merges the paths

                // The last segment will be replaced with the first segment of the relative URI
                m_arPathSegments.Remove(m_arPathSegments.GetCount() - 1U); 

                for(ArrayDynamic<string_z>::ArrayIterator itRelativeSegment = relativeUri.m_arPathSegments.GetFirst(); !itRelativeSegment.IsEnd(); ++itRelativeSegment)
                    m_arPathSegments.Add(*itRelativeSegment);

                Uri::RemoveDotSegments(m_arPathSegments);

            }
            
            // Removes the starting dot segments
            Uri::RemoveFirstDotSegments(m_arPathSegments);

            // Uses the query of the relative URI or none
            if(Uri::FLAG_ZUERY_IS_DEFINED & relativeUri.m_definedComponents)
            {
                m_strQuery = relativeUri.m_strQuery;
                m_definedComponents |= Uri::FLAG_ZUERY_IS_DEFINED;
            }
            else
            {
                m_strQuery = string_z::GetEmpty();
                m_definedComponents &= ~Uri::FLAG_ZUERY_IS_DEFINED;
            }
        }

        // Uses the base authority
    }

    // Uses the base scheme
    
    // Uses the fragment of the relative URI or none
    if(Uri::FLAG_FRAGMENT_IS_DEFINED & relativeUri.m_definedComponents)
    {
        m_strFragment = relativeUri.m_strFragment;
        m_definedComponents |= Uri::FLAG_FRAGMENT_IS_DEFINED;
    }
    else
    {
        m_strFragment = string_z::GetEmpty();
        m_definedComponents &= ~Uri::FLAG_FRAGMENT_IS_DEFINED;
    }

    // The original string is reset
    m_strOriginalString = string_z::GetEmpty();
}

string_z Uri::ToString() const
{
    string_z strUri;

    if(Uri::FLAG_SCHEME_IS_DEFINED & m_definedComponents)
    {
        strUri.Append(m_strScheme);
        strUri.Append(Uri::CHAR_COLON);
    }

    if(Uri::FLAG_AUTHORITY_IS_DEFINED & m_definedComponents)
    {
        strUri.Append(Uri::DOUBLE_SLASH);

        if(Uri::FLAG_USERINFO_IS_DEFINED & m_definedComponents)
        {
            strUri.Append(m_strUserInfo);
            strUri.Append(Uri::CHAR_AT_SIGN);
        }

        if(Uri::FLAG_HOST_IS_DEFINED & m_definedComponents)
        {
            strUri.Append(m_strHost);
        }

        if(Uri::FLAG_PORT_IS_DEFINED & m_definedComponents)
        {
            strUri.Append(Uri::CHAR_COLON);
            strUri.Append(m_strPort);
        }
    }

    strUri.Append(this->GetPath());
    
    if(Uri::FLAG_ZUERY_IS_DEFINED & m_definedComponents)
    {
        strUri.Append(Uri::CHAR_ZUESTION_MARK);
        strUri.Append(m_strQuery);
    }

    if(Uri::FLAG_FRAGMENT_IS_DEFINED & m_definedComponents)
    {
        strUri.Append(Uri::CHAR_NUMBER_SIGN);
        strUri.Append(m_strFragment);
    }

    return strUri;
}

void Uri::EncodePathSegment(const string_z &strInput, string_z &strOutput)
{
    static const bool IS_PATH_SEGMENT = true;
    Uri::Encode(IS_PATH_SEGMENT, strInput, strOutput);
}

void Uri::EncodeQueryOrFragment(const string_z &strInput, string_z &strOutput)
{
    static const bool IS_NOT_PATH_SEGMENT = false;
    Uri::Encode(IS_NOT_PATH_SEGMENT, strInput, strOutput);
}

void Uri::Encode(const bool bIsPathSegment, const string_z &strInput, string_z &strOutput)
{
    if(!strInput.IsEmpty())
    {
        string_z strResult;

        string_z strHexadecimal;

        string_z::ConstCharIterator it = strInput.GetConstCharIterator(0);

        for(; !it.IsEnd(); ++it)
        {
            char_z currentChar = it.GetChar();

            // Checks if the character must be encoded or not
            if(Uri::IsEncodable(currentChar, bIsPathSegment))
            {
                // Encodes the character in UTF8
                string_z strCurrentCharacter(currentChar);
                ArrayResult<i8_z> arBytes = strCurrentCharacter.ToBytes(ETextEncoding::E_UTF8);
                u8_z* arUTF8Codeunits = rcast_z(arBytes.Get(), u8_z*);

                // Adds the code units as hexadecimal values
                for(unsigned int iCodeunit = 0; iCodeunit < arBytes.GetCount() - 1U; ++iCodeunit) // -1U to skip the null terminator
                {
                    // Adds the '%'
                    strResult.Append(Uri::CHAR_PERCENT_SIGN);

                    strHexadecimal = string_z::FromIntegerToHexadecimal(arUTF8Codeunits[iCodeunit]);
                    strResult.Append(strHexadecimal);
                }

                arUTF8Codeunits = null_z;
            }
            else
            {
                strResult.Append(currentChar);
            }
        }

        strOutput = strResult;
    }
    else
    {
        strOutput = strInput;
    }
}

void Uri::Decode(const string_z &strInput, string_z &strOutput)
{
    static unsigned int PERCENT_ENCODED_LENGTH = 3U; // "%FF"
    
    if(strInput.GetLength() >= PERCENT_ENCODED_LENGTH && strInput.Contains(Uri::CHAR_PERCENT_SIGN, EComparisonType::E_BinaryCaseSensitive))
    {
        string_z strResult;

        unsigned int uLastPercentPosition = 0;
        unsigned int uCurrentPercentPosition = 0;

        u8_z* arCodeUnits = new u8_z[strInput.GetLength() / PERCENT_ENCODED_LENGTH];
        u8_z uCurrentCodeUnit = 0;
        bool bPendingCharacters = false;

        // Searches for every percent sign ("%")
        while( (uCurrentPercentPosition = strInput.IndexOf(Uri::CHAR_PERCENT_SIGN, uLastPercentPosition, EComparisonType::E_BinaryCaseSensitive)) 
               != string_z::PATTERN_NOT_FOUND)
        {
            // Percent-encoded values represent code units of UTF8 characters, 
            // so it is necessary to know where does the sequence starts at and how long it is
            // The sequence is interrupted when the next percent-encoded value is not contiguous to the last one
            if(uCurrentPercentPosition != 0)
            {
                if(uCurrentPercentPosition == uLastPercentPosition)
                {
                    // Next code unit in the sequence
                    ++uCurrentCodeUnit;
                }
                else
                {
                    if(bPendingCharacters)
                    {
                        // Adds the characters without encoding
                        strResult.Append( string_z(rcast_z(arCodeUnits, i8_z*), uCurrentCodeUnit + 1U, ETextEncoding::E_UTF8) );
                        bPendingCharacters = false;
                    }

                    // Resets the sequence length counter
                    uCurrentCodeUnit = 0;

                    // Adds all the text between the current percent sign and the last percen-encoded value
                    strResult.Append( strInput.Substring(uLastPercentPosition, uCurrentPercentPosition - 1U) );
                }
            }

            // Gets the UTF8 code unit from the percent-encoded value
            arCodeUnits[uCurrentCodeUnit] = strInput.Substring(uCurrentPercentPosition + Uri::CHAR_PERCENT_SIGN.GetLength(), 
                                                               uCurrentPercentPosition + PERCENT_ENCODED_LENGTH - 1U)
                                                               .ToIntegerFromHexadecimal<u8_z>();

            bPendingCharacters = true;

            // Gets the position after the current percent-encoded value in the string
            uLastPercentPosition = uCurrentPercentPosition + PERCENT_ENCODED_LENGTH;
        }

        // Adds the last decoded UTF8 characters without encoding
        if(bPendingCharacters)
            strResult.Append( string_z(rcast_z(arCodeUnits, i8_z*), uCurrentCodeUnit + 1U, ETextEncoding::E_UTF8) );

        delete[] arCodeUnits;

        // If there is text left after the last percent-encoded value found, adds it to the result
        if(uLastPercentPosition != strInput.GetLength() - PERCENT_ENCODED_LENGTH - 1U)
            strResult.Append( strInput.Substring(uLastPercentPosition) );

        // If there were not any separator in the path, just sets the whole input string
        if(strResult.IsEmpty() && !strInput.IsEmpty())
            strOutput = strInput;
        else
            strOutput = strResult;
    }
    else
    {
        strOutput = strInput;
    }
}

void Uri::DecomposeUri(const string_z &strInputUri)
{
    int nSchemeEndPosition      = strInputUri.IndexOf(Uri::CHAR_COLON, EComparisonType::E_BinaryCaseSensitive);
    int nAuthorityStartPosition = strInputUri.IndexOf(Uri::DOUBLE_SLASH, EComparisonType::E_BinaryCaseSensitive);
    int nQueryStartPosition     = strInputUri.IndexOf(Uri::CHAR_ZUESTION_MARK, EComparisonType::E_BinaryCaseSensitive);
    int nFragmentStartPosition  = strInputUri.IndexOf(Uri::CHAR_NUMBER_SIGN, EComparisonType::E_BinaryCaseSensitive);
    int nPathStartPosition      = string_z::PATTERN_NOT_FOUND;

    // Gets the scheme
    // If there is a scheme termination (":") and it's placed before the authority separator ("//") and the path separator ("/")
    if(nSchemeEndPosition != string_z::PATTERN_NOT_FOUND &&
       !((nAuthorityStartPosition != string_z::PATTERN_NOT_FOUND && nAuthorityStartPosition == 0) ||
        (nPathStartPosition != string_z::PATTERN_NOT_FOUND && nSchemeEndPosition > nPathStartPosition))
      )
    {
        m_definedComponents |= Uri::FLAG_SCHEME_IS_DEFINED;
        m_strScheme = strInputUri.Substring(0, nSchemeEndPosition - 1U);
    }

    // Decomposes the authority component
    // If it starts with a double slash ("//"), it is a relative URI reference so there is no scheme
    if(nAuthorityStartPosition != string_z::PATTERN_NOT_FOUND)
    {
        m_definedComponents |= Uri::FLAG_AUTHORITY_IS_DEFINED;
        nPathStartPosition = strInputUri.IndexOf(Uri::CHAR_SLASH, nAuthorityStartPosition + Uri::DOUBLE_SLASH.GetLength(), EComparisonType::E_BinaryCaseSensitive);

        this->DecomposeAuthority(strInputUri, nAuthorityStartPosition, nPathStartPosition, nQueryStartPosition, nFragmentStartPosition, m_definedComponents);
    }
    else if(nSchemeEndPosition != string_z::PATTERN_NOT_FOUND && 
            nSchemeEndPosition != strInputUri.GetLength() - 1U)
    {
        // The authority is not defined, the scheme is defined and is not alone
        nPathStartPosition = nSchemeEndPosition + 1U;
    }

    // Decomposes de path

    // If there is no scheme nor authority, the first part must be the first segment of the path (in a relative-path reference)
    if(!((Uri::FLAG_SCHEME_IS_DEFINED | Uri::FLAG_AUTHORITY_IS_DEFINED) & m_definedComponents))
        nPathStartPosition = 0;

    if(nQueryStartPosition != 0 && nFragmentStartPosition != 0)
        this->DecomposePath(strInputUri, nPathStartPosition, nQueryStartPosition, nFragmentStartPosition);
    
    // Gets de query
    // If there is a query separator ("?")
    if(nQueryStartPosition != string_z::PATTERN_NOT_FOUND)
    {
        m_definedComponents |= Uri::FLAG_ZUERY_IS_DEFINED;

        int nQueryEndPosition = 0;

        if(nFragmentStartPosition != string_z::PATTERN_NOT_FOUND)
            nQueryEndPosition = nFragmentStartPosition - 1U;
        else
            nQueryEndPosition = strInputUri.GetLength() - 1U;

        m_strQuery = strInputUri.Substring(nQueryStartPosition + Uri::CHAR_ZUESTION_MARK.GetLength(), nQueryEndPosition);
    }
    
    // Gets de fragment
    // If there is a fragment separator ("#")
    if(nFragmentStartPosition != string_z::PATTERN_NOT_FOUND)
    {
        m_definedComponents |= Uri::FLAG_FRAGMENT_IS_DEFINED;
        m_strFragment = strInputUri.Substring(nFragmentStartPosition + Uri::CHAR_NUMBER_SIGN.GetLength());
    }
}

void Uri::DecomposeAuthority(const string_z &strInputUri, 
                              const int nAuthorityStartPosition, 
                              const int nPathStartPosition, 
                              const int nQueryStartPosition, 
                              const int nFragmentStartPosition, 
                              Uri::TBitField &definedComponents)
{
    int nAuthorityEndPosition = 0;

    if(nPathStartPosition != string_z::PATTERN_NOT_FOUND)
        nAuthorityEndPosition = nPathStartPosition - 1U;
    else if(nQueryStartPosition != string_z::PATTERN_NOT_FOUND)
        nAuthorityEndPosition = nQueryStartPosition - 1U;
    else if(nFragmentStartPosition != string_z::PATTERN_NOT_FOUND)
        nAuthorityEndPosition = nFragmentStartPosition - 1U;
    else
        nAuthorityEndPosition = strInputUri.GetLength() - 1U;

    string_z strAuthority(strInputUri.Substring(nAuthorityStartPosition + Uri::DOUBLE_SLASH.GetLength(), nAuthorityEndPosition));

    int nUserInfoEndPosition = strAuthority.IndexOf(Uri::CHAR_AT_SIGN, EComparisonType::E_BinaryCaseSensitive);
    int nHostStartPosition = 0;

    // If there is a user info separator ("@")
    if(nUserInfoEndPosition != string_z::PATTERN_NOT_FOUND)
    {
        // Gets the user info
        m_strUserInfo = strAuthority.Substring(0, nUserInfoEndPosition - 1U);
        definedComponents |= Uri::FLAG_USERINFO_IS_DEFINED;

        nHostStartPosition = nUserInfoEndPosition + Uri::CHAR_AT_SIGN.GetLength();
    }

    int nIPv6EndPosition = strAuthority.IndexOf(Uri::CHAR_CLOSING_SQUARE_BRACKET, EComparisonType::E_BinaryCaseSensitive);
    int nPortStartPosition = string_z::PATTERN_NOT_FOUND;

    // Disambiguates among colons of an IPv6 sub-component and the colon that separates the port
    if(nIPv6EndPosition != string_z::PATTERN_NOT_FOUND)
    {
        nPortStartPosition = strAuthority.IndexOf(Uri::CHAR_COLON, 
                                                  nIPv6EndPosition + Uri::CHAR_CLOSING_SQUARE_BRACKET.GetLength(),
                                                  EComparisonType::E_BinaryCaseSensitive);
    }
    else
    {
        nPortStartPosition = strAuthority.IndexOf(Uri::CHAR_COLON, EComparisonType::E_BinaryCaseSensitive);
    }

    int nHostEndPosition = 0;

    // If there is a port separator (":")
    if(nPortStartPosition != string_z::PATTERN_NOT_FOUND)
    {
        // Gets the port
        m_strPort = strAuthority.Substring(nPortStartPosition + Uri::CHAR_COLON.GetLength());
        definedComponents |= Uri::FLAG_PORT_IS_DEFINED;

        nHostEndPosition = nPortStartPosition - 1U;
    }
    else
    {
        nHostEndPosition = strAuthority.GetLength() - 1U;
    }

    // Gets the host
    m_strHost = strAuthority.Substring(nHostStartPosition, nHostEndPosition);
    definedComponents |= Uri::FLAG_HOST_IS_DEFINED;
}

void Uri::DecomposePath(const string_z &strInputUri, 
                         const int nPathStartPosition, 
                         const int nQueryStartPosition, 
                         const int nFragmentStartPosition)
{
    // Note: When the path starts with a slash, an empty segment is added at the start; 
    //       when the path ends with a slash, an empty segment is added at the end

    if(nPathStartPosition != string_z::PATTERN_NOT_FOUND)
    {
        int nPathEndPosition = 0;

        if(nQueryStartPosition != string_z::PATTERN_NOT_FOUND)
            nPathEndPosition = nQueryStartPosition - 1U;
        else if(nFragmentStartPosition != string_z::PATTERN_NOT_FOUND)
            nPathEndPosition = nFragmentStartPosition - 1U;
        else
            nPathEndPosition = strInputUri.GetLength() - 1U;

        string_z strPath(strInputUri.Substring(nPathStartPosition, nPathEndPosition));

        ArrayResult<string_z> arSegments = strPath.Split(Uri::CHAR_SLASH);

        m_arPathSegments.Clear();

        for(unsigned int i = 0; i < arSegments.GetCount(); ++i)
            m_arPathSegments.Add(arSegments[i]);
    }
}

void Uri::RemoveDotSegments(ArrayDynamic<string_z> &arPathSegments)
{
    puint_z i = 0;

    while(i < arPathSegments.GetCount())
    {
        if(arPathSegments[i] == Uri::SINGLE_DOT_SEGMENT && i > 0)
        {
            // If the dot segment appears the first, it is not removed
            // If the dot segment appears the last, it is replaced by an empty string
            if(i == arPathSegments.GetCount() - 1U)
                arPathSegments[i] = string_z::GetEmpty();
            else
                arPathSegments.Remove(i);
        }
        else if(i > 0                                            && 
                arPathSegments[i] == Uri::DOUBLE_DOT_SEGMENT    && 
                arPathSegments[i-1U] != Uri::DOUBLE_DOT_SEGMENT && 
                arPathSegments[i-1U] != Uri::SINGLE_DOT_SEGMENT && 
                !arPathSegments[i-1U].IsEmpty())
        {
            // The dot segments formed by 2 dots that appear at the beginning of relative URIs must not be removed
            // Two dot segments must not remove previous dot segments nor empty segments

            // Removes ".."
            arPathSegments.Remove(i);

            // If the previous segment is now the last one, it is replaced with an empty segment
            // If not, it is removed
            --i;
            if(i == arPathSegments.GetCount() - 1U)
                arPathSegments[i] = string_z::GetEmpty();
            else
                arPathSegments.Remove(i);
        }
        else
        {
            // It is not a dot segment, it moves next
            ++i;
        }
    }
}

void Uri::Normalize()
{
    this->NormalizeScheme();
    this->NormalizeUserInfo();
    this->NormalizeHost();
    this->NormalizePort();
    this->NormalizePath();
    this->NormalizeQuery();
    this->NormalizeFragment();
}

void Uri::NormalizeScheme()
{
    if(Uri::FLAG_SCHEME_IS_DEFINED & m_definedComponents)
        m_strScheme = m_strScheme.ToLowerCase();
}

void Uri::NormalizeUserInfo()
{
    if(Uri::FLAG_USERINFO_IS_DEFINED & m_definedComponents)
        m_strUserInfo = m_strUserInfo.ToLowerCase();
}

void Uri::NormalizeHost()
{
    if(Uri::FLAG_HOST_IS_DEFINED & m_definedComponents)
        m_strHost = m_strHost.ToLowerCase();
}

void Uri::NormalizePort()
{
    // Empty
}

void Uri::NormalizePath()
{
    if(!m_arPathSegments.IsEmpty())
    {
        Uri::RemoveDotSegments(m_arPathSegments);
        
        for(ArrayDynamic<string_z>::ArrayIterator it = m_arPathSegments.GetFirst(); !it.IsEnd(); ++it)
        {
            if(!it->IsEmpty())
            {
                // First decodes the string to remove possible percent-encoded unreserved character
                Uri::Decode(*it, *it);
                // Then it encodes everything
                Uri::EncodePathSegment(*it, *it);
            }
        }
    }
}

void Uri::NormalizeQuery()
{
    if(Uri::FLAG_ZUERY_IS_DEFINED & m_definedComponents)
    {
        // First decodes the string to remove possible percent-encoded unreserved character
        Uri::Decode(m_strQuery, m_strQuery);
        // Then it encodes everything
        Uri::EncodeQueryOrFragment(m_strQuery, m_strQuery);
    }
}

void Uri::NormalizeFragment()
{
    if(Uri::FLAG_FRAGMENT_IS_DEFINED & m_definedComponents)
    {
        // First decodes the string to remove possible percent-encoded unreserved character
        Uri::Decode(m_strFragment, m_strFragment);
        // Then it encodes everything
        Uri::EncodeQueryOrFragment(m_strFragment, m_strFragment);
    }
}

bool Uri::IsEncodable(const char_z &character, const bool bIsPathSegment)
{
    static const char_z CHAR_HYPHEN                          = '-';
    static const char_z CHAR_DOT                             = '.';
    static const codepoint_z CODEPOINT_FIRST_NUMBER          = '0';
    static const codepoint_z CODEPOINT_LAST_NUMBER           = '9';
    static const codepoint_z CODEPOINT_FIRST_ALPHA_UPPERCASE = 'A';
    static const codepoint_z CODEPOINT_LAST_ALPHA_UPPERCASE  = 'Z';
    static const char_z CHAR_UNDERSCORE                      = '_';
    static const codepoint_z CODEPOINT_FIRST_ALPHA_LOWERCASE = 'a';
    static const codepoint_z CODEPOINT_LAST_ALPHA_LOWERCASE  = 'z';
    static const char_z CHAR_TILDE                           = '~';

    codepoint_z codePoint = character.GetCodePoint();

    return codePoint > CHAR_TILDE.GetCodePoint()                // It's not an allowed ASCII character
           ||
           ((codePoint < CODEPOINT_FIRST_NUMBER ||
            (codePoint > CODEPOINT_LAST_NUMBER && codePoint < CODEPOINT_FIRST_ALPHA_UPPERCASE) ||
            (codePoint > CODEPOINT_LAST_ALPHA_UPPERCASE && codePoint < CODEPOINT_FIRST_ALPHA_LOWERCASE) ||
             codePoint > CODEPOINT_LAST_ALPHA_LOWERCASE)        // It's not an alpha or number chracter
           &&
           character != CHAR_UNDERSCORE                   &&    // It's not other allowed character
           character != CHAR_TILDE                        &&
           character != CHAR_DOT                          &&
           character != CHAR_HYPHEN                       &&
           character != Uri::CHAR_AT_SIGN[0]             &&
           character != Uri::CHAR_COLON[0]               &&
           (bIsPathSegment ||                                   // Allowed characters only for query and fragment
             (character != Uri::CHAR_ZUESTION_MARK[0] && 
              character != Uri::CHAR_SLASH[0]))          &&
           character != Uri::CHAR_AMPERSAND[0]           &&    // It's not a sub-delim character
           character != Uri::CHAR_APOSTROPHE[0]          &&
           character != Uri::CHAR_ASTERISK[0]            &&
           character != Uri::CHAR_CLOSING_PARENTHESES[0] &&
           character != Uri::CHAR_COMMA[0]               &&
           character != Uri::CHAR_DOLLAR_SIGN[0]         &&
           character != Uri::CHAR_EUAL_SIGN[0]          &&
           character != Uri::CHAR_EXCLAMATION_MARK[0]    &&
           character != Uri::CHAR_OPENING_PARENTHESES[0] &&
           character != Uri::CHAR_PERCENT_SIGN[0]        &&
           character != Uri::CHAR_PLUS_SIGN[0]           &&
           character != Uri::CHAR_SEMICOLON[0]);
}

void Uri::RemoveFirstDotSegments(ArrayDynamic<string_z> &arPathSegments)
{
    puint_z uAbsoluteSegment = 0;

    // If the first segment is empty, it must be ignored
    if(!arPathSegments.IsEmpty() && arPathSegments[0].IsEmpty())
        ++uAbsoluteSegment;

    // While the segment is a dot segment, remove it
    while(uAbsoluteSegment < arPathSegments.GetCount() && 
            (arPathSegments[uAbsoluteSegment] == Uri::DOUBLE_DOT_SEGMENT || arPathSegments[uAbsoluteSegment] == Uri::SINGLE_DOT_SEGMENT))
    {
        arPathSegments.Remove(uAbsoluteSegment);
    }
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |         PROPERTIES         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

string_z Uri::GetAuthority() const
{
    string_z strResult;

    if(Uri::FLAG_AUTHORITY_IS_DEFINED & m_definedComponents)
    {
        if(Uri::FLAG_USERINFO_IS_DEFINED & m_definedComponents)
        {
            strResult.Append(m_strUserInfo);
            strResult.Append(Uri::CHAR_AT_SIGN);
        }

        if(Uri::FLAG_HOST_IS_DEFINED & m_definedComponents)
        {
            strResult.Append(m_strHost);
        }

        if(Uri::FLAG_PORT_IS_DEFINED & m_definedComponents)
        {
            strResult.Append(Uri::CHAR_COLON);
            strResult.Append(m_strPort);
        }
    }

    return strResult;
}

string_z Uri::GetFragment() const
{
    return m_strFragment;
}

string_z Uri::GetHost() const
{
    return m_strHost;
}

string_z Uri::GetPath() const
{
    string_z strPath;

    if(!m_arPathSegments.IsEmpty())
    {
        ArrayDynamic<string_z>::ArrayIterator it = m_arPathSegments.GetFirst();
        ArrayDynamic<string_z>::ArrayIterator itLast = m_arPathSegments.GetLast();

        // If the authority is defined or the path begins with an empty segment, adds a slash at the beginning
        if((Uri::FLAG_AUTHORITY_IS_DEFINED & m_definedComponents) || 
           (it->IsEmpty() && m_arPathSegments.GetCount() > 1U))
        {
            strPath.Append(Uri::CHAR_SLASH);
            strPath.Append(*it);
            ++it;
        }

        for(; !it.IsEnd(); ++it)
        {
            strPath.Append(*it);

            if(it != itLast)
                strPath.Append(Uri::CHAR_SLASH);
        }
    }

    return strPath;
}

string_z Uri::GetPort() const
{
    return m_strPort;
}

string_z Uri::GetQuery() const
{
    return m_strQuery;
}

string_z Uri::GetScheme() const
{
    return m_strScheme;
}

string_z Uri::GetUserInfo() const
{
    return m_strUserInfo;
}

string_z Uri::GetOriginalString() const
{
    return m_strOriginalString;
}

ArrayDynamic<string_z> Uri::GetPathSegments() const
{
    return m_arPathSegments;
}

bool Uri::IsRelative() const
{
    return !(m_definedComponents & Uri::FLAG_SCHEME_IS_DEFINED);
}

void Uri::SetAuthority(const string_z &strAuthority)
{
    if(strAuthority.IsEmpty())
    {
        m_definedComponents &= ~(Uri::FLAG_AUTHORITY_IS_DEFINED | Uri::FLAG_USERINFO_IS_DEFINED | Uri::FLAG_HOST_IS_DEFINED | Uri::FLAG_PORT_IS_DEFINED);
        m_strHost = string_z::GetEmpty();
        m_strUserInfo = string_z::GetEmpty();
        m_strPort = string_z::GetEmpty();
    }
    else
    {
        m_definedComponents |= Uri::FLAG_AUTHORITY_IS_DEFINED | Uri::FLAG_HOST_IS_DEFINED;
        this->DecomposeAuthority(Uri::DOUBLE_SLASH + strAuthority, 0, string_z::PATTERN_NOT_FOUND, string_z::PATTERN_NOT_FOUND, string_z::PATTERN_NOT_FOUND, m_definedComponents);
        this->NormalizeUserInfo();
        this->NormalizeHost();
        this->NormalizePort();

        // If the path does not start with a slash
        if(!m_arPathSegments.IsEmpty() && m_arPathSegments[0] != string_z::GetEmpty())
        {
            // Adds an empty segment at the beginning, which means adding a starting slash
            m_arPathSegments.Insert(string_z::GetEmpty(), 0);
        }
    }

    m_strOriginalString = string_z::GetEmpty();
}

void Uri::SetFragment(const string_z &strFragment)
{
    if(strFragment.IsEmpty())
    {
        m_definedComponents &= ~Uri::FLAG_FRAGMENT_IS_DEFINED;
        m_strFragment = string_z::GetEmpty();
    }
    else
    {
        m_definedComponents |= Uri::FLAG_FRAGMENT_IS_DEFINED;
        m_strFragment = strFragment;
        this->NormalizeFragment();
    }

    m_strOriginalString = string_z::GetEmpty();
}

void Uri::SetHost(const string_z &strHost)
{
    if(strHost.IsEmpty())
    {
        // The entire authority will be undefined
        this->SetAuthority(strHost);
    }
    else
    {
        // If the host was already defined, it takes the new value
        if(m_definedComponents & Uri::FLAG_HOST_IS_DEFINED)
        {
            m_strHost = strHost;
            this->NormalizeHost();
            m_strOriginalString = string_z::GetEmpty();
        }
        else
        {
            // If not, the authority is defined using the new value
            this->SetAuthority(strHost);
        }
    }
}

void Uri::SetPath(const string_z &strPath)
{
    string_z strAdjustedInput = strPath;

    if(strAdjustedInput.IsEmpty())
    {
        if(Uri::FLAG_AUTHORITY_IS_DEFINED & m_definedComponents)
            strAdjustedInput = Uri::CHAR_SLASH;
        else
            strAdjustedInput = Uri::SINGLE_DOT_SEGMENT;
    }
    else if((Uri::FLAG_AUTHORITY_IS_DEFINED & m_definedComponents) && strAdjustedInput[0] != Uri::CHAR_SLASH[0])
    {
        // The authority is defined and the input path does not start with a slash ("/"), a slash is added at the start
        strAdjustedInput = Uri::CHAR_SLASH + strAdjustedInput;
    }

    this->DecomposePath(strAdjustedInput, 0, string_z::PATTERN_NOT_FOUND, string_z::PATTERN_NOT_FOUND);
    this->NormalizePath();

    if(!this->IsRelative())
    {
        Uri::RemoveFirstDotSegments(m_arPathSegments);
    }
    else if(!m_arPathSegments.IsEmpty() && m_arPathSegments[0].Contains(Uri::CHAR_COLON, EComparisonType::E_BinaryCaseSensitive))
    {
        // The path cannot start with a segment that contains a colon when there is no scheme
        // A starting single dot segment is added ("./")
        m_arPathSegments.Insert(Uri::SINGLE_DOT_SEGMENT, 0);
    }

    m_strOriginalString = string_z::GetEmpty();
}

void Uri::SetQuery(const string_z &strQuery)
{
    if(strQuery.IsEmpty())
    {
        m_definedComponents &= ~Uri::FLAG_ZUERY_IS_DEFINED;
        m_strQuery = string_z::GetEmpty();
    }
    else
    {
        m_definedComponents |= Uri::FLAG_ZUERY_IS_DEFINED;
        m_strQuery = strQuery;
        this->NormalizeQuery();
    }

    m_strOriginalString = string_z::GetEmpty();
}

void Uri::SetPort(const string_z &strPort)
{
    if(Uri::FLAG_AUTHORITY_IS_DEFINED & m_definedComponents)
    {
        if(strPort.IsEmpty())
        {
            m_definedComponents &= ~Uri::FLAG_PORT_IS_DEFINED;
            m_strPort = string_z::GetEmpty();
        }
        else
        {
            m_definedComponents |= Uri::FLAG_PORT_IS_DEFINED;
            m_strPort = strPort;
            this->NormalizePort();
        }

        m_strOriginalString = string_z::GetEmpty();
    }
}

void Uri::SetScheme(const string_z &strScheme)
{
    if(strScheme.IsEmpty())
    {
        m_definedComponents &= ~Uri::FLAG_SCHEME_IS_DEFINED;
        m_strScheme = string_z::GetEmpty();

        // The path cannot start with a segment that contains a colon when there is no scheme
        if(!m_arPathSegments.IsEmpty() && m_arPathSegments[0].Contains(Uri::CHAR_COLON, EComparisonType::E_BinaryCaseSensitive))
        {
            // A starting single dot segment is added ("./")
            m_arPathSegments.Insert(Uri::SINGLE_DOT_SEGMENT, 0);
        }
    }
    else
    {
        m_definedComponents |= Uri::FLAG_SCHEME_IS_DEFINED;
        m_strScheme = strScheme;
        this->NormalizeScheme();

        // The path may need to be adjusted if it begins with dot segments
        Uri::RemoveFirstDotSegments(m_arPathSegments);
    }

    m_strOriginalString = string_z::GetEmpty();
}

void Uri::SetUserInfo(const string_z &strUserInfo)
{
    if(Uri::FLAG_AUTHORITY_IS_DEFINED & m_definedComponents)
    {
        if(strUserInfo.IsEmpty())
        {
            m_definedComponents &= ~Uri::FLAG_USERINFO_IS_DEFINED;
            m_strUserInfo = string_z::GetEmpty();
        }
        else
        {
            m_definedComponents |= Uri::FLAG_USERINFO_IS_DEFINED;
            m_strUserInfo = strUserInfo;
            this->NormalizeUserInfo();
        }

        m_strOriginalString = string_z::GetEmpty();
    }
}

} // namespace z