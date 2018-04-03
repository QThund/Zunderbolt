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

#include "ZIO/Uri.h"

#include "UriWhiteBox.h"
#include "ZContainers/ArrayDynamic.h"
#include "ZCommon/Exceptions/AssertException.h"

using z::Test::UriWhiteBox;


ZTEST_SUITE_BEGIN( Uri_TestSuite )

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input string is empty.
/// </summary>
ZTEST_CASE ( Constructor1_AssertionFailsWhenInputStringIsEmpty_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = string_z::GetEmpty();
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        Uri uri(INPUT_STRING);
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
/// Checks that all the URI componets are empty when an empty string is used as input.
/// </summary>
ZTEST_CASE ( Constructor1_AllComponentsAreEmptyWhenInputStringIsEmpty_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = string_z::GetEmpty();
    const string_z EXPECTED_VALUE = string_z::GetEmpty();

    // [Execution]
    Uri uri(INPUT_STRING);
    
    // [Verification]
    BOOST_CHECK(uri.GetScheme()    == EXPECTED_VALUE);
    BOOST_CHECK(uri.GetAuthority() == EXPECTED_VALUE);
    BOOST_CHECK(uri.GetPath()      == EXPECTED_VALUE);
    BOOST_CHECK(uri.GetQuery()     == EXPECTED_VALUE);
    BOOST_CHECK(uri.GetFragment()  == EXPECTED_VALUE);
}

#endif

/// <summary>
/// Checks that the scheme has the expected value when the input string only contains a scheme.
/// </summary>
ZTEST_CASE ( Constructor1_SchemeIsWhatExpectedWhenInputContainsSchemeOnly_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "scheme:";
    const string_z EXPECTED_VALUE = "scheme";

    // [Execution]
    Uri uri(INPUT_STRING);
    
    // [Verification]
    BOOST_CHECK(uri.GetScheme() == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the scheme and the authority have the expected value when the input string only contains a scheme and the authority.
/// </summary>
ZTEST_CASE ( Constructor1_SchemeAndAuthorityAreWhatExpectedWhenInputContainsSchemeAndAuthorityOnly_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "scheme://authority";
    const string_z EXPECTED_SCHEME_VALUE = "scheme";
    const string_z EXPECTED_AUTHORITY_VALUE = "authority";

    // [Execution]
    Uri uri(INPUT_STRING);
    
    // [Verification]
    BOOST_CHECK(uri.GetScheme()    == EXPECTED_SCHEME_VALUE);
    BOOST_CHECK(uri.GetAuthority() == EXPECTED_AUTHORITY_VALUE);
}

/// <summary>
/// Checks that the scheme, the authority and the path have the expected value when the input string contains the scheme, the authority and the path.
/// </summary>
ZTEST_CASE ( Constructor1_SchemeAuthorityAndPathAreWhatExpectedWhenInputContainsSchemeAuthorityAndPath_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "scheme://authority/path";
    const string_z EXPECTED_SCHEME_VALUE = "scheme";
    const string_z EXPECTED_AUTHORITY_VALUE = "authority";
    const string_z EXPECTED_PATH_VALUE = "/path";

    // [Execution]
    Uri uri(INPUT_STRING);
    
    // [Verification]
    BOOST_CHECK(uri.GetScheme()    == EXPECTED_SCHEME_VALUE);
    BOOST_CHECK(uri.GetAuthority() == EXPECTED_AUTHORITY_VALUE);
    BOOST_CHECK(uri.GetPath()      == EXPECTED_PATH_VALUE);
}

/// <summary>
/// Checks that the scheme, the authority and the path have the expected value when the input string contains an IPv6 as host and a port.
/// </summary>
ZTEST_CASE ( Constructor1_SchemeAuthorityAndPathAreWhatExpectedWhenInputContainsIPv6AndPort_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "scheme://[fe80::4cf7:6fe6:453f:8129]:port/pat:h";
    const string_z EXPECTED_SCHEME_VALUE = "scheme";
    const string_z EXPECTED_HOST_VALUE = "[fe80::4cf7:6fe6:453f:8129]";
    const string_z EXPECTED_PORT_VALUE = "port";
    const string_z EXPECTED_PATH_VALUE = "/pat:h";

    // [Execution]
    Uri uri(INPUT_STRING);
    
    // [Verification]
    BOOST_CHECK(uri.GetScheme() == EXPECTED_SCHEME_VALUE);
    BOOST_CHECK(uri.GetHost()   == EXPECTED_HOST_VALUE);
    BOOST_CHECK(uri.GetPort()   == EXPECTED_PORT_VALUE);
    BOOST_CHECK(uri.GetPath()   == EXPECTED_PATH_VALUE);
    string_z u = uri.GetPath();
}

/// <summary>
/// Checks that the scheme, the authority, the path and the query have the expected value when the input string contains the scheme, the authority, the path and the query.
/// </summary>
ZTEST_CASE ( Constructor1_SchemeAuthorityPathAndQueryAreWhatExpectedWhenInputContainsSchemeAuthorityPathAndQuery_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "scheme://authority/path?query";
    const string_z EXPECTED_SCHEME_VALUE = "scheme";
    const string_z EXPECTED_AUTHORITY_VALUE = "authority";
    const string_z EXPECTED_PATH_VALUE = "/path";
    const string_z EXPECTED_QUERY_VALUE = "query";

    // [Execution]
    Uri uri(INPUT_STRING);
    
    // [Verification]
    BOOST_CHECK(uri.GetScheme()    == EXPECTED_SCHEME_VALUE);
    BOOST_CHECK(uri.GetAuthority() == EXPECTED_AUTHORITY_VALUE);
    BOOST_CHECK(uri.GetPath()      == EXPECTED_PATH_VALUE);
    BOOST_CHECK(uri.GetQuery()     == EXPECTED_QUERY_VALUE);
}

/// <summary>
/// Checks that the scheme and the path have the expected value when the input string contains the scheme and the path only.
/// </summary>
ZTEST_CASE ( Constructor1_SchemeAndPathAreWhatExpectedWhenInputContainsSchemeAndPathOnly_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "scheme:/pathsegment1/pathsegment2";
    const string_z EXPECTED_SCHEME_VALUE = "scheme";
    const string_z EXPECTED_PATH_VALUE = "/pathsegment1/pathsegment2";

    // [Execution]
    Uri uri(INPUT_STRING);
    
    // [Verification]
    BOOST_CHECK(uri.GetScheme() == EXPECTED_SCHEME_VALUE);
    BOOST_CHECK(uri.GetPath()   == EXPECTED_PATH_VALUE);
}

/// <summary>
/// Checks that the path iswhat expected when the input URI contains an empty path and a query.
/// </summary>
ZTEST_CASE ( Constructor1_PathIsWhatExpectedWhenInputContainsEmptyPathAndQuery_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "scheme://host?query";
    const string_z EXPECTED_PATH_VALUE = string_z::GetEmpty();

    // [Execution]
    Uri uri(INPUT_STRING);
    
    // [Verification]
    BOOST_CHECK(uri.GetPath() == EXPECTED_PATH_VALUE);
}

/// <summary>
/// Checks that the path iswhat expected when the input URI contains an empty path and a fragment.
/// </summary>
ZTEST_CASE ( Constructor1_PathIsWhatExpectedWhenInputContainsEmptyPathAndFragment_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "scheme://host#fragment";
    const string_z EXPECTED_PATH_VALUE = string_z::GetEmpty();

    // [Execution]
    Uri uri(INPUT_STRING);
    
    // [Verification]
    BOOST_CHECK(uri.GetPath() == EXPECTED_PATH_VALUE);
}

/// <summary>
/// Checks that the host has the expected value when the authority is formed only by a host.
/// </summary>
ZTEST_CASE ( Constructor1_HostIsWhatExpectedWhenAuthorityIsFormedOnlyByHost_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "scheme://authority/path";
    const string_z EXPECTED_HOST_VALUE = "authority";

    // [Execution]
    Uri uri(INPUT_STRING);
    
    // [Verification]
    BOOST_CHECK(uri.GetHost() == EXPECTED_HOST_VALUE);
}

/// <summary>
/// Checks that the user information and the host have the expected value when the authority is formed only by a host and the user information.
/// </summary>
ZTEST_CASE ( Constructor1_UserInfoAndHostAreWhatExpectedWhenAuthorityIsFormedOnlyByUserInfoAndHost_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "//userinfo@host";
    const string_z EXPECTED_USERINFO_VALUE = "userinfo";
    const string_z EXPECTED_HOST_VALUE = "host";

    // [Execution]
    Uri uri(INPUT_STRING);
    
    // [Verification]
    BOOST_CHECK(uri.GetUserInfo() == EXPECTED_USERINFO_VALUE);
    BOOST_CHECK(uri.GetHost()     == EXPECTED_HOST_VALUE);
}

/// <summary>
/// Checks that the user information, the port and the host have the expected value when the authority is formed only by a host, the port and the user information.
/// </summary>
ZTEST_CASE ( Constructor1_UserInfoHostAndPortAreWhatExpectedWhenAuthorityIsFormedOnlyByUserInfoHostAndPort_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "//userinfo@host:port";
    const string_z EXPECTED_USERINFO_VALUE = "userinfo";
    const string_z EXPECTED_HOST_VALUE = "host";
    const string_z EXPECTED_PORT_VALUE = "port";

    // [Execution]
    Uri uri(INPUT_STRING);
    
    // [Verification]
    BOOST_CHECK(uri.GetUserInfo() == EXPECTED_USERINFO_VALUE);
    BOOST_CHECK(uri.GetHost()     == EXPECTED_HOST_VALUE);
    BOOST_CHECK(uri.GetPort()     == EXPECTED_PORT_VALUE);
}

/// <summary>
/// Checks that the port and the host have the expected value when the authority is formed only by a host and the port.
/// </summary>
ZTEST_CASE ( Constructor1_HostAndPortAreWhatExpectedWhenAuthorityIsFormedOnlyByHostAndPort_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "//host:port";
    const string_z EXPECTED_HOST_VALUE = "host";
    const string_z EXPECTED_PORT_VALUE = "port";

    // [Execution]
    Uri uri(INPUT_STRING);
    
    // [Verification]
    BOOST_CHECK(uri.GetHost() == EXPECTED_HOST_VALUE);
    BOOST_CHECK(uri.GetPort() == EXPECTED_PORT_VALUE);
}

/// <summary>
/// Checks that the authority and the path have the expected value when the URI is formed only by the authority and the path.
/// </summary>
ZTEST_CASE ( Constructor1_AuthorityAndPathAreWhatExpectedWhenUriIsFormedOnlyByAuthorityAndPath_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "//userinfo@host:port/path";
    const string_z EXPECTED_AUTHORITY_VALUE = "userinfo@host:port";
    const string_z EXPECTED_PATH_VALUE = "/path";

    // [Execution]
    Uri uri(INPUT_STRING);
    
    // [Verification]
    BOOST_CHECK(uri.GetAuthority() == EXPECTED_AUTHORITY_VALUE);
    BOOST_CHECK(uri.GetPath()      == EXPECTED_PATH_VALUE);
}

/// <summary>
/// Checks that the authority and the query have the expected value when the URI is formed only by the authority and the query.
/// </summary>
ZTEST_CASE ( Constructor1_AuthorityAndQueryAreWhatExpectedWhenUriIsFormedOnlyByAuthorityAndQuery_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "//userinfo@host:port?query";
    const string_z EXPECTED_AUTHORITY_VALUE = "userinfo@host:port";
    const string_z EXPECTED_QUERY_VALUE = "query";

    // [Execution]
    Uri uri(INPUT_STRING);
    
    // [Verification]
    BOOST_CHECK(uri.GetAuthority() == EXPECTED_AUTHORITY_VALUE);
    BOOST_CHECK(uri.GetQuery()     == EXPECTED_QUERY_VALUE);
}

/// <summary>
/// Checks that the authority and the fragment have the expected value when the URI is formed only by the authority and the fragment.
/// </summary>
ZTEST_CASE ( Constructor1_AuthorityAndFragmentAreWhatExpectedWhenUriIsFormedOnlyByAuthorityAndFragment_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "//userinfo@host:port#fragment";
    const string_z EXPECTED_AUTHORITY_VALUE = "userinfo@host:port";
    const string_z EXPECTED_FRAGMENT_VALUE = "fragment";

    // [Execution]
    Uri uri(INPUT_STRING);
    
    // [Verification]
    string_z c = uri.GetAuthority();
    BOOST_CHECK(uri.GetAuthority() == EXPECTED_AUTHORITY_VALUE);
    BOOST_CHECK(uri.GetFragment()  == EXPECTED_FRAGMENT_VALUE);
}

/// <summary>
/// Checks that the path does not start with a slash when it does not start with a slash in the input string.
/// </summary>
ZTEST_CASE ( Constructor1_PathDoesNotStartWithSlashWhenUriIsFormedOnlyByPathWhichDoesNotStartWithSlash_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "segment1/segment2";
    const string_z EXPECTED_PATH_VALUE = "segment1/segment2";

    // [Execution]
    Uri uri(INPUT_STRING);
    
    // [Verification]
    BOOST_CHECK(uri.GetPath() == EXPECTED_PATH_VALUE);
}

/// <summary>
/// Checks that the path starts with a slash when it starts with a slash in the input string.
/// </summary>
ZTEST_CASE ( Constructor1_PathStartsWithSlashWhenUriIsFormedOnlyByPathWhichStartsWithSlash_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "/segment1/segment2";
    const string_z EXPECTED_PATH_VALUE = "/segment1/segment2";

    // [Execution]
    Uri uri(INPUT_STRING);
    
    // [Verification]
    BOOST_CHECK(uri.GetPath() == EXPECTED_PATH_VALUE);
}

/// <summary>
/// Checks that the path includes the initial dot segment when it starts with one dot.
/// </summary>
ZTEST_CASE ( Constructor1_PathIncludesDotSegmentWhenUriIsFormedOnlyByPathWhichStartsWithOneDot_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "./segment1/segment2";
    const string_z EXPECTED_PATH_VALUE = "./segment1/segment2";

    // [Execution]
    Uri uri(INPUT_STRING);
    
    // [Verification]
    BOOST_CHECK(uri.GetPath() == EXPECTED_PATH_VALUE);
}

/// <summary>
/// Checks that the path does not include the initial dot segment when it starts with two dots.
/// </summary>
ZTEST_CASE ( Constructor1_PathDoesNotIncludeDotSegmentWhenUriIsFormedOnlyByPathWhichStartsWithTwoDots_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "../segment1/segment2";
    const string_z EXPECTED_PATH_VALUE = "../segment1/segment2";

    // [Execution]
    Uri uri(INPUT_STRING);
    
    // [Verification]
    BOOST_CHECK(uri.GetPath() == EXPECTED_PATH_VALUE);
}

/// <summary>
/// Checks that the path and the query have the expected value when the URI is formed only by the path and the query.
/// </summary>
ZTEST_CASE ( Constructor1_PathAndQueryAreWhatExpectedWhenUriIsFormedOnlyByPathAndQuery_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "path1/path2?query=value";
    const string_z EXPECTED_PATH_VALUE = "path1/path2";
    const string_z EXPECTED_QUERY_VALUE = "query=value";

    // [Execution]
    Uri uri(INPUT_STRING);
    
    // [Verification]
    BOOST_CHECK(uri.GetPath()  == EXPECTED_PATH_VALUE);
    BOOST_CHECK(uri.GetQuery() == EXPECTED_QUERY_VALUE);
}

/// <summary>
/// Checks that the path and the fragment have the expected value when the URI is formed only by the path and the fragment.
/// </summary>
ZTEST_CASE ( Constructor1_PathAndFragmentAreWhatExpectedWhenUriIsFormedOnlyByPathAndFragment_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "path1/path2#fragment";
    const string_z EXPECTED_PATH_VALUE = "path1/path2";
    const string_z EXPECTED_FRAGMENT_VALUE = "fragment";

    // [Execution]
    Uri uri(INPUT_STRING);
    
    // [Verification]
    BOOST_CHECK(uri.GetPath()     == EXPECTED_PATH_VALUE);
    BOOST_CHECK(uri.GetFragment() == EXPECTED_FRAGMENT_VALUE);
}

/// <summary>
/// Checks that the path is empty and starts with a slash when the URI only contains a single slash.
/// </summary>
ZTEST_CASE ( Constructor1_PathIsEmptyAndStartsWithSlashWhenUriContainsOnlyOneSlash_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "/";
    const string_z EXPECTED_PATH_VALUE = "/";

    // [Execution]
    Uri uri(INPUT_STRING);
    
    // [Verification]
    BOOST_CHECK(uri.GetPath()     == EXPECTED_PATH_VALUE);
}

/// <summary>
/// Checks that the path, the query and the fragment are encoded.
/// </summary>
ZTEST_CASE ( Constructor1_PathQueryAndFragmentAreEncoded_Test )
{
    // [Preparation]
    string_z INPUT_STRING = "scheme://userinfo@authority:port/p<a th1/pa[]t{}h2?qu ery=va<lue#fra{gment";
    INPUT_STRING.Append(char_z(0x0470)); // CYRILLIC CAPITAL LETTER PSI, UTF8: D1 B0
    INPUT_STRING.Append(char_z(0x01C2)); // LATIN LETTER ALVEOLAR CLICK, UTF8: C7 82

    const string_z EXPECTED_PATH_VALUE = "/p%3Ca%20th1/pa%5B%5Dt%7B%7Dh2";
    const string_z EXPECTED_QUERY_VALUE = "qu%20ery=va%3Clue";
    const string_z EXPECTED_FRAGMENT_VALUE = "fra%7Bgment%D1%B0%C7%82";

    // [Execution]
    Uri uri(INPUT_STRING);
    
    // [Verification]
    BOOST_CHECK(uri.GetPath()     == EXPECTED_PATH_VALUE);
    BOOST_CHECK(uri.GetQuery()    == EXPECTED_QUERY_VALUE);
    BOOST_CHECK(uri.GetFragment() == EXPECTED_FRAGMENT_VALUE);
}

/// <summary>
/// Checks that the question mark ("?") and the slash ("/") are allowed in both the query and the fragment.
/// </summary>
ZTEST_CASE ( Constructor1_QuestionMarkAndSlashAreAllowedInQueryAndFragment_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "scheme://userinfo@authority:port/path1/path2?que?r/y=value#fr?ag/ment";
    const string_z EXPECTED_QUERY_VALUE = "que?r/y=value";
    const string_z EXPECTED_FRAGMENT_VALUE = "fr?ag/ment";

    // [Execution]
    Uri uri(INPUT_STRING);
    
    // [Verification]
    BOOST_CHECK(uri.GetQuery()    == EXPECTED_QUERY_VALUE);
    BOOST_CHECK(uri.GetFragment() == EXPECTED_FRAGMENT_VALUE);
}

/// <summary>
/// Checks that the path, the query and the fragment are encoded.
/// </summary>
ZTEST_CASE ( Constructor1_InputCharactersThatShouldNotBeEncodedAreDecoded_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "scheme://userinfo@authority:port/pa%42th1/pa%50th2?que%43ry=value#fr%51agment";

    const string_z EXPECTED_PATH_VALUE = "/paBth1/paPth2";
    const string_z EXPECTED_QUERY_VALUE = "queCry=value";
    const string_z EXPECTED_FRAGMENT_VALUE = "frQagment";

    // [Execution]
    Uri uri(INPUT_STRING);
    
    // [Verification]
    BOOST_CHECK(uri.GetPath()     == EXPECTED_PATH_VALUE);
    BOOST_CHECK(uri.GetQuery()    == EXPECTED_QUERY_VALUE);
    BOOST_CHECK(uri.GetFragment() == EXPECTED_FRAGMENT_VALUE);
}

/// <summary>
/// Checks that the scheme and the authority are lowercased.
/// </summary>
ZTEST_CASE ( Constructor1_SchemeAndAuthorityAreLowercased_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "SCHEME://UserInfo@HOST:1234/path1/path2?query=value#fragment";

    const string_z EXPECTED_SCHEME_VALUE = "scheme";
    const string_z EXPECTED_AUTHORITY_VALUE = "userinfo@host:1234";

    // [Execution]
    Uri uri(INPUT_STRING);
    
    // [Verification]
    BOOST_CHECK(uri.GetScheme()    == EXPECTED_SCHEME_VALUE);
    BOOST_CHECK(uri.GetAuthority() == EXPECTED_AUTHORITY_VALUE);
}

/// <summary>
/// Checks that the scheme and the authority are not encoded.
/// </summary>
ZTEST_CASE ( Constructor1_SchemeAndAuthorityAreNotEncoded_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "sch eme://user<info@auth ority:port/path1/path2?query=value#fragment";
    
    const string_z EXPECTED_SCHEME_VALUE = "sch eme";
    const string_z EXPECTED_AUTHORITY_VALUE = "user<info@auth ority:port";

    // [Execution]
    Uri uri(INPUT_STRING);
    
    // [Verification]
    BOOST_CHECK(uri.GetScheme()    == EXPECTED_SCHEME_VALUE);
    BOOST_CHECK(uri.GetAuthority() == EXPECTED_AUTHORITY_VALUE);
}

/// <summary>
/// Checks that the path, the query and the fragment are not lowercased.
/// </summary>
ZTEST_CASE ( Constructor1_PathQueryAndFragmentAreNotLowercased_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "scheme://userinfo@authority:port/PATH1/pAth2?querY=vaLlue#FRAGMENt";

    const string_z EXPECTED_PATH_VALUE = "/PATH1/pAth2";
    const string_z EXPECTED_QUERY_VALUE = "querY=vaLlue";
    const string_z EXPECTED_FRAGMENT_VALUE = "FRAGMENt";

    // [Execution]
    Uri uri(INPUT_STRING);
    
    // [Verification]
    BOOST_CHECK(uri.GetPath()     == EXPECTED_PATH_VALUE);
    BOOST_CHECK(uri.GetQuery()    == EXPECTED_QUERY_VALUE);
    BOOST_CHECK(uri.GetFragment() == EXPECTED_FRAGMENT_VALUE);
}

/// <summary>
/// Checks that all dot segments that appear in the middle of the path are removed.
/// </summary>
ZTEST_CASE ( Constructor1_DotSegmentsAreRemoved_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "scheme://userinfo@authority/path1/./path2/../path3";

    const string_z EXPECTED_PATH_VALUE = "/path1/path3";

    // [Execution]
    Uri uri(INPUT_STRING);
    
    // [Verification]
    BOOST_CHECK(uri.GetPath() == EXPECTED_PATH_VALUE);
}

/// <summary>
/// Checks that the path contains one segment when the URI does not contain any separator.
/// </summary>
ZTEST_CASE ( Constructor1_ThePathContainsOneSegmentWhenTheUriDoesNotContainAnySeparator_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "schemeauthoritypath";
    const string_z EXPECTED_PATH_VALUE = "schemeauthoritypath";

    // [Execution]
    Uri uri(INPUT_STRING);
    
    // [Verification]
    BOOST_CHECK(uri.GetPath() == EXPECTED_PATH_VALUE);
}

/// <summary>
/// Checks that the URI is correctly copied.
/// </summary>
ZTEST_CASE ( Constructor2_TheUriIsCorrectlyCopied_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "scheme://authority/path?query#fragment";
    const Uri ORIGINAL_URI(INPUT_STRING);

    // [Execution]
    Uri uri(ORIGINAL_URI);
    
    // [Verification]
    BOOST_CHECK(uri == ORIGINAL_URI);
    BOOST_CHECK(uri.GetOriginalString() == INPUT_STRING);
}

/// <summary>
/// Checks that the URI is correctly copied.
/// </summary>
ZTEST_CASE ( OperatorAssignment1_TheUriIsCorrectlyCopied_Test )
{
    // [Preparation]
    const string_z INPUT_STRING1 = "xxx";
    const string_z INPUT_STRING2 = "scheme://authority/path?query#fragment";
    Uri uri(INPUT_STRING1);
    const Uri ORIGINAL_URI(INPUT_STRING2);

    // [Execution]
    uri = ORIGINAL_URI;
    
    // [Verification]
    BOOST_CHECK(uri == ORIGINAL_URI);
    BOOST_CHECK(uri.GetOriginalString() == INPUT_STRING2);
}

/// <summary>
/// Checks that the scheme has the expected value when the input string only contains a scheme.
/// </summary>
ZTEST_CASE ( OperatorAssignment2_SchemeIsWhatExpectedWhenInputContainsSchemeOnly_Test )
{
    // [Preparation]
    const string_z INPUT_STRING1 = "xxx";
    Uri uri(INPUT_STRING1);
    const string_z INPUT_STRING2 = "scheme:";
    const Uri ORIGINAL_URI(INPUT_STRING2);
    const string_z EXPECTED_VALUE = "scheme";

    // [Execution]
    uri = ORIGINAL_URI;
    
    // [Verification]
    BOOST_CHECK(uri.GetScheme() == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the scheme and the authority have the expected value when the input string only contains a scheme and the authority.
/// </summary>
ZTEST_CASE ( OperatorAssignment2_SchemeAndAuthorityAreWhatExpectedWhenInputContainsSchemeAndAuthorityOnly_Test )
{
    // [Preparation]
    const string_z INPUT_STRING1 = "xxx";
    Uri uri(INPUT_STRING1);
    const string_z INPUT_STRING2 = "scheme://authority";
    const Uri ORIGINAL_URI(INPUT_STRING2);
    const string_z EXPECTED_SCHEME_VALUE = "scheme";
    const string_z EXPECTED_AUTHORITY_VALUE = "authority";

    // [Execution]
    uri = ORIGINAL_URI;
    
    // [Verification]
    BOOST_CHECK(uri.GetScheme()    == EXPECTED_SCHEME_VALUE);
    BOOST_CHECK(uri.GetAuthority() == EXPECTED_AUTHORITY_VALUE);
}

/// <summary>
/// Checks that the scheme, the authority and the path have the expected value when the input string contains the scheme, the authority and the path.
/// </summary>
ZTEST_CASE ( OperatorAssignment2_SchemeAuthorityAndPathAreWhatExpectedWhenInputContainsSchemeAuthorityAndPath_Test )
{
    // [Preparation]
    const string_z INPUT_STRING1 = "xxx";
    Uri uri(INPUT_STRING1);
    const string_z INPUT_STRING2 = "scheme://authority/path";
    const Uri ORIGINAL_URI(INPUT_STRING2);
    const string_z EXPECTED_SCHEME_VALUE = "scheme";
    const string_z EXPECTED_AUTHORITY_VALUE = "authority";
    const string_z EXPECTED_PATH_VALUE = "/path";

    // [Execution]
    uri = ORIGINAL_URI;
    
    // [Verification]
    BOOST_CHECK(uri.GetScheme()    == EXPECTED_SCHEME_VALUE);
    BOOST_CHECK(uri.GetAuthority() == EXPECTED_AUTHORITY_VALUE);
    BOOST_CHECK(uri.GetPath()      == EXPECTED_PATH_VALUE);
}

/// <summary>
/// Checks that the scheme, the authority, the path and the query have the expected value when the input string contains the scheme, the authority, the path and the query.
/// </summary>
ZTEST_CASE ( OperatorAssignment2_SchemeAuthorityPathAndQueryAreWhatExpectedWhenInputContainsSchemeAuthorityPathAndQuery_Test )
{
    // [Preparation]
    const string_z INPUT_STRING1 = "xxx";
    Uri uri(INPUT_STRING1);
    const string_z INPUT_STRING2 = "scheme://authority/path?query";
    const Uri ORIGINAL_URI(INPUT_STRING2);
    const string_z EXPECTED_SCHEME_VALUE = "scheme";
    const string_z EXPECTED_AUTHORITY_VALUE = "authority";
    const string_z EXPECTED_PATH_VALUE = "/path";
    const string_z EXPECTED_QUERY_VALUE = "query";

    // [Execution]
    uri = ORIGINAL_URI;
    
    // [Verification]
    BOOST_CHECK(uri.GetScheme()    == EXPECTED_SCHEME_VALUE);
    BOOST_CHECK(uri.GetAuthority() == EXPECTED_AUTHORITY_VALUE);
    BOOST_CHECK(uri.GetPath()      == EXPECTED_PATH_VALUE);
    BOOST_CHECK(uri.GetQuery()     == EXPECTED_QUERY_VALUE);
}

/// <summary>
/// Checks that the scheme and the path have the expected value when the input string contains the scheme and the path only.
/// </summary>
ZTEST_CASE ( OperatorAssignment2_SchemeAndPathAreWhatExpectedWhenInputContainsSchemeAndPathOnly_Test )
{
    // [Preparation]
    const string_z INPUT_STRING1 = "xxx";
    Uri uri(INPUT_STRING1);
    const string_z INPUT_STRING2 = "scheme:/pathsegment1/pathsegment2";
    const Uri ORIGINAL_URI(INPUT_STRING2);
    const string_z EXPECTED_SCHEME_VALUE = "scheme";
    const string_z EXPECTED_PATH_VALUE = "/pathsegment1/pathsegment2";

    // [Execution]
    uri = ORIGINAL_URI;
    
    // [Verification]
    BOOST_CHECK(uri.GetScheme() == EXPECTED_SCHEME_VALUE);
    BOOST_CHECK(uri.GetPath()   == EXPECTED_PATH_VALUE);
}

/// <summary>
/// Checks that the host has the expected value when the authority is formed only by a host.
/// </summary>
ZTEST_CASE ( OperatorAssignment2_HostIsWhatExpectedWhenAuthorityIsFormedOnlyByHost_Test )
{
    // [Preparation]
    const string_z INPUT_STRING1 = "xxx";
    Uri uri(INPUT_STRING1);
    const string_z INPUT_STRING2 = "scheme://authority/path";
    const Uri ORIGINAL_URI(INPUT_STRING2);
    const string_z EXPECTED_HOST_VALUE = "authority";

    // [Execution]
    uri = ORIGINAL_URI;
    
    // [Verification]
    BOOST_CHECK(uri.GetHost() == EXPECTED_HOST_VALUE);
}

/// <summary>
/// Checks that the user information and the host have the expected value when the authority is formed only by a host and the user information.
/// </summary>
ZTEST_CASE ( OperatorAssignment2_UserInfoAndHostAreWhatExpectedWhenAuthorityIsFormedOnlyByUserInfoAndHost_Test )
{
    // [Preparation]
    const string_z INPUT_STRING1 = "xxx";
    Uri uri(INPUT_STRING1);
    const string_z INPUT_STRING2 = "//userinfo@host";
    const Uri ORIGINAL_URI(INPUT_STRING2);
    const string_z EXPECTED_USERINFO_VALUE = "userinfo";
    const string_z EXPECTED_HOST_VALUE = "host";

    // [Execution]
    uri = ORIGINAL_URI;
    
    // [Verification]
    BOOST_CHECK(uri.GetUserInfo() == EXPECTED_USERINFO_VALUE);
    BOOST_CHECK(uri.GetHost()     == EXPECTED_HOST_VALUE);
}

/// <summary>
/// Checks that the user information, the port and the host have the expected value when the authority is formed only by a host, the port and the user information.
/// </summary>
ZTEST_CASE ( OperatorAssignment2_UserInfoHostAndPortAreWhatExpectedWhenAuthorityIsFormedOnlyByUserInfoHostAndPort_Test )
{
    // [Preparation]
    const string_z INPUT_STRING1 = "xxx";
    Uri uri(INPUT_STRING1);
    const string_z INPUT_STRING2 = "//userinfo@host:port";
    const Uri ORIGINAL_URI(INPUT_STRING2);
    const string_z EXPECTED_USERINFO_VALUE = "userinfo";
    const string_z EXPECTED_HOST_VALUE = "host";
    const string_z EXPECTED_PORT_VALUE = "port";

    // [Execution]
    uri = ORIGINAL_URI;
    
    // [Verification]
    BOOST_CHECK(uri.GetUserInfo() == EXPECTED_USERINFO_VALUE);
    BOOST_CHECK(uri.GetHost()     == EXPECTED_HOST_VALUE);
    BOOST_CHECK(uri.GetPort()     == EXPECTED_PORT_VALUE);
}

/// <summary>
/// Checks that the port and the host have the expected value when the authority is formed only by a host and the port.
/// </summary>
ZTEST_CASE ( OperatorAssignment2_HostAndPortAreWhatExpectedWhenAuthorityIsFormedOnlyByHostAndPort_Test )
{
    // [Preparation]
    const string_z INPUT_STRING1 = "xxx";
    Uri uri(INPUT_STRING1);
    const string_z INPUT_STRING2 = "//host:port";
    const Uri ORIGINAL_URI(INPUT_STRING2);
    const string_z EXPECTED_HOST_VALUE = "host";
    const string_z EXPECTED_PORT_VALUE = "port";

    // [Execution]
    uri = ORIGINAL_URI;
    
    // [Verification]
    BOOST_CHECK(uri.GetHost()     == EXPECTED_HOST_VALUE);
    BOOST_CHECK(uri.GetPort()     == EXPECTED_PORT_VALUE);
}

/// <summary>
/// Checks that the authority and the path have the expected value when the URI is formed only by the authority and the path.
/// </summary>
ZTEST_CASE ( OperatorAssignment2_AuthorityAndPathAreWhatExpectedWhenUriIsFormedOnlyByAuthorityAndPath_Test )
{
    // [Preparation]
    const string_z INPUT_STRING1 = "xxx";
    Uri uri(INPUT_STRING1);
    const string_z INPUT_STRING2 = "//userinfo@host:port/path";
    const Uri ORIGINAL_URI(INPUT_STRING2);
    const string_z EXPECTED_AUTHORITY_VALUE = "userinfo@host:port";
    const string_z EXPECTED_PATH_VALUE = "/path";

    // [Execution]
    uri = ORIGINAL_URI;
    
    // [Verification]
    BOOST_CHECK(uri.GetAuthority() == EXPECTED_AUTHORITY_VALUE);
    BOOST_CHECK(uri.GetPath()      == EXPECTED_PATH_VALUE);
}

/// <summary>
/// Checks that the authority and the query have the expected value when the URI is formed only by the authority and the query.
/// </summary>
ZTEST_CASE ( OperatorAssignment2_AuthorityAndQueryAreWhatExpectedWhenUriIsFormedOnlyByAuthorityAndQuery_Test )
{
    // [Preparation]
    const string_z INPUT_STRING1 = "xxx";
    Uri uri(INPUT_STRING1);
    const string_z INPUT_STRING2 = "//userinfo@host:port?query";
    const Uri ORIGINAL_URI(INPUT_STRING2);
    const string_z EXPECTED_AUTHORITY_VALUE = "userinfo@host:port";
    const string_z EXPECTED_QUERY_VALUE = "query";

    // [Execution]
    uri = ORIGINAL_URI;
    
    // [Verification]
    BOOST_CHECK(uri.GetAuthority() == EXPECTED_AUTHORITY_VALUE);
    BOOST_CHECK(uri.GetQuery()     == EXPECTED_QUERY_VALUE);
}

/// <summary>
/// Checks that the authority and the fragment have the expected value when the URI is formed only by the authority and the fragment.
/// </summary>
ZTEST_CASE ( OperatorAssignment2_AuthorityAndFragmentAreWhatExpectedWhenUriIsFormedOnlyByAuthorityAndFragment_Test )
{
    // [Preparation]
    const string_z INPUT_STRING1 = "xxx";
    Uri uri(INPUT_STRING1);
    const string_z INPUT_STRING2 = "//userinfo@host:port#fragment";
    const Uri ORIGINAL_URI(INPUT_STRING2);
    const string_z EXPECTED_AUTHORITY_VALUE = "userinfo@host:port";
    const string_z EXPECTED_FRAGMENT_VALUE = "fragment";

    // [Execution]
    uri = ORIGINAL_URI;
    
    // [Verification]
    string_z c = uri.GetAuthority();
    BOOST_CHECK(uri.GetAuthority() == EXPECTED_AUTHORITY_VALUE);
    BOOST_CHECK(uri.GetFragment()  == EXPECTED_FRAGMENT_VALUE);
}

/// <summary>
/// Checks that the path does not start with a slash when it does not start with a slash in the input string.
/// </summary>
ZTEST_CASE ( OperatorAssignment2_PathDoesNotStartWithSlashWhenUriIsFormedOnlyByPathWhichDoesNotStartWithSlash_Test )
{
    // [Preparation]
    const string_z INPUT_STRING1 = "xxx";
    Uri uri(INPUT_STRING1);
    const string_z INPUT_STRING2 = "segment1/segment2";
    const Uri ORIGINAL_URI(INPUT_STRING2);
    const string_z EXPECTED_PATH_VALUE = "segment1/segment2";

    // [Execution]
    uri = ORIGINAL_URI;
    
    // [Verification]
    BOOST_CHECK(uri.GetPath() == EXPECTED_PATH_VALUE);
}

/// <summary>
/// Checks that the path starts with a slash when it starts with a slash in the input string.
/// </summary>
ZTEST_CASE ( OperatorAssignment2_PathStartsWithSlashWhenUriIsFormedOnlyByPathWhichStartsWithSlash_Test )
{
    // [Preparation]
    const string_z INPUT_STRING1 = "xxx";
    Uri uri(INPUT_STRING1);
    const string_z INPUT_STRING2 = "/segment1/segment2";
    const Uri ORIGINAL_URI(INPUT_STRING2);
    const string_z EXPECTED_PATH_VALUE = "/segment1/segment2";

    // [Execution]
    uri = ORIGINAL_URI;
    
    // [Verification]
    BOOST_CHECK(uri.GetPath() == EXPECTED_PATH_VALUE);
}

/// <summary>
/// Checks that the path includes the initial dot segment when it starts with one dot.
/// </summary>
ZTEST_CASE ( OperatorAssignment2_PathIncludesDotSegmentWhenUriIsFormedOnlyByPathWhichStartsWithOneDot_Test )
{
    // [Preparation]
    const string_z INPUT_STRING1 = "xxx";
    Uri uri(INPUT_STRING1);
    const string_z INPUT_STRING2 = "./segment1/segment2";
    const Uri ORIGINAL_URI(INPUT_STRING2);
    const string_z EXPECTED_PATH_VALUE = "./segment1/segment2";

    // [Execution]
    uri = ORIGINAL_URI;
    
    // [Verification]
    BOOST_CHECK(uri.GetPath() == EXPECTED_PATH_VALUE);
}

/// <summary>
/// Checks that the path includes the initial dot segment when it starts with two dots.
/// </summary>
ZTEST_CASE ( OperatorAssignment2_PathIncludesDotSegmentWhenUriIsFormedOnlyByPathWhichStartsWithTwoDots_Test )
{
    // [Preparation]
    const string_z INPUT_STRING1 = "xxx";
    Uri uri(INPUT_STRING1);
    const string_z INPUT_STRING2 = "../segment1/segment2";
    const Uri ORIGINAL_URI(INPUT_STRING2);
    const string_z EXPECTED_PATH_VALUE = "../segment1/segment2";

    // [Execution]
    uri = ORIGINAL_URI;
    
    // [Verification]
    BOOST_CHECK(uri.GetPath() == EXPECTED_PATH_VALUE);
}

/// <summary>
/// Checks that the path and the query have the expected value when the URI is formed only by the path and the query.
/// </summary>
ZTEST_CASE ( OperatorAssignment2_PathAndQueryAreWhatExpectedWhenUriIsFormedOnlyByPathAndQuery_Test )
{
    // [Preparation]
    const string_z INPUT_STRING1 = "xxx";
    Uri uri(INPUT_STRING1);
    const string_z INPUT_STRING2 = "path1/path2?query=value";
    const Uri ORIGINAL_URI(INPUT_STRING2);
    const string_z EXPECTED_PATH_VALUE = "path1/path2";
    const string_z EXPECTED_QUERY_VALUE = "query=value";

    // [Execution]
    uri = ORIGINAL_URI;
    
    // [Verification]
    BOOST_CHECK(uri.GetPath()  == EXPECTED_PATH_VALUE);
    BOOST_CHECK(uri.GetQuery() == EXPECTED_QUERY_VALUE);
}

/// <summary>
/// Checks that the path and the fragment have the expected value when the URI is formed only by the path and the fragment.
/// </summary>
ZTEST_CASE ( OperatorAssignment2_PathAndFragmentAreWhatExpectedWhenUriIsFormedOnlyByPathAndFragment_Test )
{
    // [Preparation]
    const string_z INPUT_STRING1 = "xxx";
    Uri uri(INPUT_STRING1);
    const string_z INPUT_STRING2 = "path1/path2#fragment";
    const Uri ORIGINAL_URI(INPUT_STRING2);
    const string_z EXPECTED_PATH_VALUE = "path1/path2";
    const string_z EXPECTED_FRAGMENT_VALUE = "fragment";

    // [Execution]
    uri = ORIGINAL_URI;
    
    // [Verification]
    BOOST_CHECK(uri.GetPath()     == EXPECTED_PATH_VALUE);
    BOOST_CHECK(uri.GetFragment() == EXPECTED_FRAGMENT_VALUE);
}

/// <summary>
/// Checks that the path is empty and starts with a slash when the URI only contains a single slash.
/// </summary>
ZTEST_CASE ( OperatorAssignment2_PathIsEmptyAndStartsWithSlashWhenUriContainsOnlyOneSlash_Test )
{
    // [Preparation]
    const string_z INPUT_STRING1 = "xxx";
    Uri uri(INPUT_STRING1);
    const string_z INPUT_STRING2 = "/";
    const Uri ORIGINAL_URI(INPUT_STRING2);
    const string_z EXPECTED_PATH_VALUE = "/";

    // [Execution]
    uri = ORIGINAL_URI;
    
    // [Verification]
    BOOST_CHECK(uri.GetPath()     == EXPECTED_PATH_VALUE);
}

/// <summary>
/// Checks that the path, the query and the fragment are encoded.
/// </summary>
ZTEST_CASE ( OperatorAssignment2_PathQueryAndFragmentAreEncoded_Test )
{
    // [Preparation]
    const string_z INPUT_STRING1 = "xxx";
    Uri uri(INPUT_STRING1);
    string_z INPUT_STRING2 = "scheme://userinfo@authority:port/p<a th1/pa[]t{}h2?qu ery=va<lue#fra{gment";
    INPUT_STRING2.Append(char_z(0x0470)); // CYRILLIC CAPITAL LETTER PSI, UTF8: D1 B0
    INPUT_STRING2.Append(char_z(0x01C2)); // LATIN LETTER ALVEOLAR CLICK, UTF8: C7 82
    const Uri ORIGINAL_URI(INPUT_STRING2);

    const string_z EXPECTED_PATH_VALUE = "/p%3Ca%20th1/pa%5B%5Dt%7B%7Dh2";
    const string_z EXPECTED_QUERY_VALUE = "qu%20ery=va%3Clue";
    const string_z EXPECTED_FRAGMENT_VALUE = "fra%7Bgment%D1%B0%C7%82";

    // [Execution]
    uri = ORIGINAL_URI;
    
    // [Verification]
    BOOST_CHECK(uri.GetPath()     == EXPECTED_PATH_VALUE);
    BOOST_CHECK(uri.GetQuery()    == EXPECTED_QUERY_VALUE);
    BOOST_CHECK(uri.GetFragment() == EXPECTED_FRAGMENT_VALUE);
}

/// <summary>
/// Checks that the question mark ("?") and the slash ("/") are allowed in both the query and the fragment.
/// </summary>
ZTEST_CASE ( OperatorAssignment2_QuestionMarkAndSlashAreAllowedInQueryAndFragment_Test )
{
    // [Preparation]
    const string_z INPUT_STRING1 = "xxx";
    Uri uri(INPUT_STRING1);
    const string_z INPUT_STRING2 = "scheme://userinfo@authority:port/path1/path2?que?r/y=value#fr?ag/ment";
    const Uri ORIGINAL_URI(INPUT_STRING2);
    const string_z EXPECTED_QUERY_VALUE = "que?r/y=value";
    const string_z EXPECTED_FRAGMENT_VALUE = "fr?ag/ment";

    // [Execution]
    uri = ORIGINAL_URI;
    
    // [Verification]
    BOOST_CHECK(uri.GetQuery()    == EXPECTED_QUERY_VALUE);
    BOOST_CHECK(uri.GetFragment() == EXPECTED_FRAGMENT_VALUE);
}

/// <summary>
/// Checks that the path, the query and the fragment are encoded.
/// </summary>
ZTEST_CASE ( OperatorAssignment2_InputCharactersThatShouldNotBeEncodedAreDecoded_Test )
{
    // [Preparation]
    const string_z INPUT_STRING1 = "xxx";
    Uri uri(INPUT_STRING1);
    const string_z INPUT_STRING2 = "scheme://userinfo@authority:port/pa%42th1/pa%50th2?que%43ry=value#fr%51agment";
    const Uri ORIGINAL_URI(INPUT_STRING2);

    const string_z EXPECTED_PATH_VALUE = "/paBth1/paPth2";
    const string_z EXPECTED_QUERY_VALUE = "queCry=value";
    const string_z EXPECTED_FRAGMENT_VALUE = "frQagment";

    // [Execution]
    uri = ORIGINAL_URI;
    
    // [Verification]
    BOOST_CHECK(uri.GetPath()     == EXPECTED_PATH_VALUE);
    BOOST_CHECK(uri.GetQuery()    == EXPECTED_QUERY_VALUE);
    BOOST_CHECK(uri.GetFragment() == EXPECTED_FRAGMENT_VALUE);
}

/// <summary>
/// Checks that the scheme and the authority are lowercased.
/// </summary>
ZTEST_CASE ( OperatorAssignment2_SchemeAndAuthorityAreLowercased_Test )
{
    // [Preparation]
    const string_z INPUT_STRING1 = "xxx";
    Uri uri(INPUT_STRING1);
    const string_z INPUT_STRING2 = "SCHEME://UserInfo@HOST:1234/path1/path2?query=value#fragment";
    const Uri ORIGINAL_URI(INPUT_STRING2);

    const string_z EXPECTED_SCHEME_VALUE = "scheme";
    const string_z EXPECTED_AUTHORITY_VALUE = "userinfo@host:1234";

    // [Execution]
    uri = ORIGINAL_URI;
    
    // [Verification]
    BOOST_CHECK(uri.GetScheme()    == EXPECTED_SCHEME_VALUE);
    BOOST_CHECK(uri.GetAuthority() == EXPECTED_AUTHORITY_VALUE);
}

/// <summary>
/// Checks that the scheme and the authority are not encoded.
/// </summary>
ZTEST_CASE ( OperatorAssignment2_SchemeAndAuthorityAreNotEncoded_Test )
{
    // [Preparation]
    const string_z INPUT_STRING1 = "xxx";
    Uri uri(INPUT_STRING1);
    const string_z INPUT_STRING2 = "sch eme://user<info@auth ority:port/path1/path2?query=value#fragment";
    const Uri ORIGINAL_URI(INPUT_STRING2);

    const string_z EXPECTED_SCHEME_VALUE = "sch eme";
    const string_z EXPECTED_AUTHORITY_VALUE = "user<info@auth ority:port";

    // [Execution]
    uri = ORIGINAL_URI;
    
    // [Verification]
    BOOST_CHECK(uri.GetScheme()    == EXPECTED_SCHEME_VALUE);
    BOOST_CHECK(uri.GetAuthority() == EXPECTED_AUTHORITY_VALUE);
}

/// <summary>
/// Checks that the path, the query and the fragment are not lowercased.
/// </summary>
ZTEST_CASE ( OperatorAssignment2_PathQueryAndFragmentAreNotLowercased_Test )
{
    // [Preparation]
    const string_z INPUT_STRING1 = "xxx";
    Uri uri(INPUT_STRING1);
    const string_z INPUT_STRING2 = "scheme://userinfo@authority:port/PATH1/pAth2?querY=vaLlue#FRAGMENt";
    const Uri ORIGINAL_URI(INPUT_STRING2);

    const string_z EXPECTED_PATH_VALUE = "/PATH1/pAth2";
    const string_z EXPECTED_QUERY_VALUE = "querY=vaLlue";
    const string_z EXPECTED_FRAGMENT_VALUE = "FRAGMENt";

    // [Execution]
    uri = ORIGINAL_URI;
    
    // [Verification]
    BOOST_CHECK(uri.GetPath()     == EXPECTED_PATH_VALUE);
    BOOST_CHECK(uri.GetQuery()    == EXPECTED_QUERY_VALUE);
    BOOST_CHECK(uri.GetFragment() == EXPECTED_FRAGMENT_VALUE);
}

/// <summary>
/// Checks that the path, the query and the fragment are not lowercased.
/// </summary>
ZTEST_CASE ( OperatorAssignment2_DotSegmentsAreRemoved_Test )
{
    // [Preparation]
    const string_z INPUT_STRING1 = "xxx";
    Uri uri(INPUT_STRING1);
    const string_z INPUT_STRING2 = "scheme://userinfo@authority/path1/./path2/../path3";
    const Uri ORIGINAL_URI(INPUT_STRING2);

    const string_z EXPECTED_PATH_VALUE = "/path1/path3";

    // [Execution]
    uri = ORIGINAL_URI;
    
    // [Verification]
    BOOST_CHECK(uri.GetPath() == EXPECTED_PATH_VALUE);
}

/// <summary>
/// Checks that the path contains one segment when the URI does not contain any separator.
/// </summary>
ZTEST_CASE ( OperatorAssignment2_ThePathContainsOneSegmentWhenTheUriDoesNotContainAnySeparator_Test )
{
    // [Preparation]
    const string_z INPUT_STRING1 = "xxx";
    Uri uri(INPUT_STRING1);
    const string_z INPUT_STRING2 = "schemeauthoritypath";
    const Uri ORIGINAL_URI(INPUT_STRING2);
    const string_z EXPECTED_PATH_VALUE = "schemeauthoritypath";

    // [Execution]
    uri = ORIGINAL_URI;
    
    // [Verification]
    BOOST_CHECK(uri.GetPath() == EXPECTED_PATH_VALUE);
}

/// <summary>
/// Checks that it returns True when URIs are equal although the original strings are not equal.
/// </summary>
ZTEST_CASE ( EqualityOperator_ReturnsTrueWhenUrisAreEqualAlthoughOriginalStringWasNotEqual_Test )
{
    // [Preparation]
    const string_z INPUT_STRING1 = "Scheme://authority/path/./path2/../path3?qu%20ery#fragment";
    const string_z INPUT_STRING2 = "scheme://authority/path/path3?qu ery#fragment";
    const Uri URI1(INPUT_STRING1);
    const Uri URI2(INPUT_STRING2);
    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = URI1 == URI2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when URIs are equal and original strings were equal.
/// </summary>
ZTEST_CASE ( EqualityOperator_ReturnsTrueWhenUrisAreEqualAndOriginalStringWasEqual_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "Scheme://authority/path/./path2/../path3?qu%20ery#fragment";
    const Uri URI1(INPUT_STRING);
    const Uri URI2(INPUT_STRING);
    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = URI1 == URI2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the scheme is different.
/// </summary>
ZTEST_CASE ( EqualityOperator_ReturnsFalseWhenSchemeIsDifferent_Test )
{
    // [Preparation]
    const string_z INPUT_STRING1 = "scheme1://authority/path?query#fragment";
    const string_z INPUT_STRING2 = "scheme2://authority/path?query#fragment";
    const Uri URI1(INPUT_STRING1);
    const Uri URI2(INPUT_STRING2);
    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = URI1 == URI2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the host is different.
/// </summary>
ZTEST_CASE ( EqualityOperator_ReturnsFalseWhenHostIsDifferent_Test )
{
    // [Preparation]
    const string_z INPUT_STRING1 = "scheme://authority1/path?query#fragment";
    const string_z INPUT_STRING2 = "scheme://authority2/path?query#fragment";
    const Uri URI1(INPUT_STRING1);
    const Uri URI2(INPUT_STRING2);
    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = URI1 == URI2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the user information is different.
/// </summary>
ZTEST_CASE ( EqualityOperator_ReturnsFalseWhenUserInfoIsDifferent_Test )
{
    // [Preparation]
    const string_z INPUT_STRING1 = "scheme://userinfo1@authority/path?query#fragment";
    const string_z INPUT_STRING2 = "scheme://userinfo2@authority/path?query#fragment";
    const Uri URI1(INPUT_STRING1);
    const Uri URI2(INPUT_STRING2);
    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = URI1 == URI2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the port is different.
/// </summary>
ZTEST_CASE ( EqualityOperator_ReturnsFalseWhenPortIsDifferent_Test )
{
    // [Preparation]
    const string_z INPUT_STRING1 = "scheme://authority:port1/path?query#fragment";
    const string_z INPUT_STRING2 = "scheme://authority:port2/path?query#fragment";
    const Uri URI1(INPUT_STRING1);
    const Uri URI2(INPUT_STRING2);
    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = URI1 == URI2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the path is different.
/// </summary>
ZTEST_CASE ( EqualityOperator_ReturnsFalseWhenPathIsDifferent_Test )
{
    // [Preparation]
    const string_z INPUT_STRING1 = "scheme://authority/path1?query#fragment";
    const string_z INPUT_STRING2 = "scheme://authority/path2?query#fragment";
    const Uri URI1(INPUT_STRING1);
    const Uri URI2(INPUT_STRING2);
    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = URI1 == URI2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the query is different.
/// </summary>
ZTEST_CASE ( EqualityOperator_ReturnsFalseWhenQueryIsDifferent_Test )
{
    // [Preparation]
    const string_z INPUT_STRING1 = "scheme://authority/path?query1#fragment";
    const string_z INPUT_STRING2 = "scheme://authority/path?query2#fragment";
    const Uri URI1(INPUT_STRING1);
    const Uri URI2(INPUT_STRING2);
    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = URI1 == URI2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the fragment is different.
/// </summary>
ZTEST_CASE ( EqualityOperator_ReturnsFalseWhenFragmentIsDifferent_Test )
{
    // [Preparation]
    const string_z INPUT_STRING1 = "scheme://authority/path?query#fragment1";
    const string_z INPUT_STRING2 = "scheme://authority/path?query#fragment2";
    const Uri URI1(INPUT_STRING1);
    const Uri URI2(INPUT_STRING2);
    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = URI1 == URI2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when URIs are equal although the original strings are not equal.
/// </summary>
ZTEST_CASE ( InequalityOperator_ReturnsFalseWhenUrisAreEqualAlthoughOriginalStringWasNotEqual_Test )
{
    // [Preparation]
    const string_z INPUT_STRING1 = "Scheme://authority/path/./path2/../path3?qu%20ery#fragment";
    const string_z INPUT_STRING2 = "scheme://authority/path/path3?qu ery#fragment";
    const Uri URI1(INPUT_STRING1);
    const Uri URI2(INPUT_STRING2);
    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = URI1 != URI2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when URIs are equal and original strings were equal.
/// </summary>
ZTEST_CASE ( InequalityOperator_ReturnsFalseWhenUrisAreEqualAndOriginalStringWasEqual_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "Scheme://authority/path/./path2/../path3?qu%20ery#fragment";
    const Uri URI1(INPUT_STRING);
    const Uri URI2(INPUT_STRING);
    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = URI1 != URI2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the scheme is different.
/// </summary>
ZTEST_CASE ( InequalityOperator_ReturnsTrueWhenSchemeIsDifferent_Test )
{
    // [Preparation]
    const string_z INPUT_STRING1 = "scheme1://authority/path?query#fragment";
    const string_z INPUT_STRING2 = "scheme2://authority/path?query#fragment";
    const Uri URI1(INPUT_STRING1);
    const Uri URI2(INPUT_STRING2);
    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = URI1 != URI2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the host is different.
/// </summary>
ZTEST_CASE ( InequalityOperator_ReturnsTrueWhenHostIsDifferent_Test )
{
    // [Preparation]
    const string_z INPUT_STRING1 = "scheme://authority1/path?query#fragment";
    const string_z INPUT_STRING2 = "scheme://authority2/path?query#fragment";
    const Uri URI1(INPUT_STRING1);
    const Uri URI2(INPUT_STRING2);
    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = URI1 != URI2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the user information is different.
/// </summary>
ZTEST_CASE ( InequalityOperator_ReturnsTrueWhenUserInfoIsDifferent_Test )
{
    // [Preparation]
    const string_z INPUT_STRING1 = "scheme://userinfo1@authority/path?query#fragment";
    const string_z INPUT_STRING2 = "scheme://userinfo2@authority/path?query#fragment";
    const Uri URI1(INPUT_STRING1);
    const Uri URI2(INPUT_STRING2);
    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = URI1 != URI2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the port is different.
/// </summary>
ZTEST_CASE ( InequalityOperator_ReturnsTrueWhenPortIsDifferent_Test )
{
    // [Preparation]
    const string_z INPUT_STRING1 = "scheme://authority:port1/path?query#fragment";
    const string_z INPUT_STRING2 = "scheme://authority:port2/path?query#fragment";
    const Uri URI1(INPUT_STRING1);
    const Uri URI2(INPUT_STRING2);
    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = URI1 != URI2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the path is different.
/// </summary>
ZTEST_CASE ( InequalityOperator_ReturnsTrueWhenPathIsDifferent_Test )
{
    // [Preparation]
    const string_z INPUT_STRING1 = "scheme://authority/path1?query#fragment";
    const string_z INPUT_STRING2 = "scheme://authority/path2?query#fragment";
    const Uri URI1(INPUT_STRING1);
    const Uri URI2(INPUT_STRING2);
    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = URI1 != URI2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the query is different.
/// </summary>
ZTEST_CASE ( InequalityOperator_ReturnsTrueWhenQueryIsDifferent_Test )
{
    // [Preparation]
    const string_z INPUT_STRING1 = "scheme://authority/path?query1#fragment";
    const string_z INPUT_STRING2 = "scheme://authority/path?query2#fragment";
    const Uri URI1(INPUT_STRING1);
    const Uri URI2(INPUT_STRING2);
    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = URI1 != URI2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the fragment is different.
/// </summary>
ZTEST_CASE ( InequalityOperator_ReturnsTrueWhenFragmentIsDifferent_Test )
{
    // [Preparation]
    const string_z INPUT_STRING1 = "scheme://authority/path?query#fragment1";
    const string_z INPUT_STRING2 = "scheme://authority/path?query#fragment2";
    const Uri URI1(INPUT_STRING1);
    const Uri URI2(INPUT_STRING2);
    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = URI1 != URI2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

// Note: The following tests of the Resolve method have been extracted mostly from the RFC 3986, section 5.4.
//       Since there are lot of different combinations, it was not practical to name them one by one so a generic naming is used.

/// <summary>
/// Checks that it behaves as expected for the case #001.
/// </summary>
ZTEST_CASE ( Resolve_NormalCase001_Test )
{
    // [Preparation]
    const string_z ABSOLUTE_URI = "http://a/b/c/d;p?q";
    const string_z RELATIVE_URI = "g";
    const string_z EXPECTED_URI = "http://a/b/c/g";
    Uri absoluteUri(ABSOLUTE_URI);
    Uri relativeUri(RELATIVE_URI);
    const Uri EXPECTED_RESULT(EXPECTED_URI);

    // [Execution]
    absoluteUri.Resolve(relativeUri);
    
    // [Verification]
    BOOST_CHECK(absoluteUri == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it behaves as expected for the case #002.
/// </summary>
ZTEST_CASE ( Resolve_NormalCase002_Test )
{
    // [Preparation]
    const string_z ABSOLUTE_URI = "http://a/b/c/d;p?q";
    const string_z RELATIVE_URI = "./g";
    const string_z EXPECTED_URI = "http://a/b/c/g";
    Uri absoluteUri(ABSOLUTE_URI);
    Uri relativeUri(RELATIVE_URI);
    const Uri EXPECTED_RESULT(EXPECTED_URI);

    // [Execution]
    absoluteUri.Resolve(relativeUri);
    
    // [Verification]
    BOOST_CHECK(absoluteUri == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it behaves as expected for the case #003.
/// </summary>
ZTEST_CASE ( Resolve_NormalCase003_Test )
{
    // [Preparation]
    const string_z ABSOLUTE_URI = "http://a/b/c/d;p?q";
    const string_z RELATIVE_URI = "g/";
    const string_z EXPECTED_URI = "http://a/b/c/g/";
    Uri absoluteUri(ABSOLUTE_URI);
    Uri relativeUri(RELATIVE_URI);
    const Uri EXPECTED_RESULT(EXPECTED_URI);

    // [Execution]
    absoluteUri.Resolve(relativeUri);
    
    // [Verification]
    BOOST_CHECK(absoluteUri == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it behaves as expected for the case #004.
/// </summary>
ZTEST_CASE ( Resolve_NormalCase004_Test )
{
    // [Preparation]
    const string_z ABSOLUTE_URI = "http://a/b/c/d;p?q";
    const string_z RELATIVE_URI = "/g";
    const string_z EXPECTED_URI = "http://a/g";
    Uri absoluteUri(ABSOLUTE_URI);
    Uri relativeUri(RELATIVE_URI);
    const Uri EXPECTED_RESULT(EXPECTED_URI);

    // [Execution]
    absoluteUri.Resolve(relativeUri);
    
    // [Verification]
    BOOST_CHECK(absoluteUri == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it behaves as expected for the case #005.
/// </summary>
ZTEST_CASE ( Resolve_NormalCase005_Test )
{
    // [Preparation]
    const string_z ABSOLUTE_URI = "http://a/b/c/d;p?q";
    const string_z RELATIVE_URI = "//g";
    const string_z EXPECTED_URI = "http://g";
    Uri absoluteUri(ABSOLUTE_URI);
    Uri relativeUri(RELATIVE_URI);
    const Uri EXPECTED_RESULT(EXPECTED_URI);

    // [Execution]
    absoluteUri.Resolve(relativeUri);
    
    // [Verification]
    BOOST_CHECK(absoluteUri == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it behaves as expected for the case #006.
/// </summary>
ZTEST_CASE ( Resolve_NormalCase006_Test )
{
    // [Preparation]
    const string_z ABSOLUTE_URI = "http://a/b/c/d;p?q";
    const string_z RELATIVE_URI = "?y";
    const string_z EXPECTED_URI = "http://a/b/c/d;p?y";
    Uri absoluteUri(ABSOLUTE_URI);
    Uri relativeUri(RELATIVE_URI);
    const Uri EXPECTED_RESULT(EXPECTED_URI);

    // [Execution]
    absoluteUri.Resolve(relativeUri);
    
    // [Verification]
    string_z s = absoluteUri.ToString();
    BOOST_CHECK(absoluteUri == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it behaves as expected for the case #007.
/// </summary>
ZTEST_CASE ( Resolve_NormalCase007_Test )
{
    // [Preparation]
    const string_z ABSOLUTE_URI = "http://a/b/c/d;p?q";
    const string_z RELATIVE_URI = "g?y";
    const string_z EXPECTED_URI = "http://a/b/c/g?y";
    Uri absoluteUri(ABSOLUTE_URI);
    Uri relativeUri(RELATIVE_URI);
    const Uri EXPECTED_RESULT(EXPECTED_URI);

    // [Execution]
    absoluteUri.Resolve(relativeUri);
    
    // [Verification]
    BOOST_CHECK(absoluteUri == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it behaves as expected for the case #008.
/// </summary>
ZTEST_CASE ( Resolve_NormalCase008_Test )
{
    // [Preparation]
    const string_z ABSOLUTE_URI = "http://a/b/c/d;p?q";
    const string_z RELATIVE_URI = "#s";
    const string_z EXPECTED_URI = "http://a/b/c/d;p?q#s";
    Uri absoluteUri(ABSOLUTE_URI);
    Uri relativeUri(RELATIVE_URI);
    const Uri EXPECTED_RESULT(EXPECTED_URI);

    // [Execution]
    absoluteUri.Resolve(relativeUri);
    
    // [Verification]
    BOOST_CHECK(absoluteUri == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it behaves as expected for the case #009.
/// </summary>
ZTEST_CASE ( Resolve_NormalCase009_Test )
{
    // [Preparation]
    const string_z ABSOLUTE_URI = "http://a/b/c/d;p?q";
    const string_z RELATIVE_URI = "g#s";
    const string_z EXPECTED_URI = "http://a/b/c/g#s";
    Uri absoluteUri(ABSOLUTE_URI);
    Uri relativeUri(RELATIVE_URI);
    const Uri EXPECTED_RESULT(EXPECTED_URI);

    // [Execution]
    absoluteUri.Resolve(relativeUri);
    
    // [Verification]
    BOOST_CHECK(absoluteUri == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it behaves as expected for the case #010.
/// </summary>
ZTEST_CASE ( Resolve_NormalCase010_Test )
{
    // [Preparation]
    const string_z ABSOLUTE_URI = "http://a/b/c/d;p?q";
    const string_z RELATIVE_URI = "g?y#s";
    const string_z EXPECTED_URI = "http://a/b/c/g?y#s";
    Uri absoluteUri(ABSOLUTE_URI);
    Uri relativeUri(RELATIVE_URI);
    const Uri EXPECTED_RESULT(EXPECTED_URI);

    // [Execution]
    absoluteUri.Resolve(relativeUri);
    
    // [Verification]
    BOOST_CHECK(absoluteUri == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it behaves as expected for the case #011.
/// </summary>
ZTEST_CASE ( Resolve_NormalCase011_Test )
{
    // [Preparation]
    const string_z ABSOLUTE_URI = "http://a/b/c/d;p?q";
    const string_z RELATIVE_URI = ";x";
    const string_z EXPECTED_URI = "http://a/b/c/;x";
    Uri absoluteUri(ABSOLUTE_URI);
    Uri relativeUri(RELATIVE_URI);
    const Uri EXPECTED_RESULT(EXPECTED_URI);

    // [Execution]
    absoluteUri.Resolve(relativeUri);
    
    // [Verification]
    BOOST_CHECK(absoluteUri == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it behaves as expected for the case #012.
/// </summary>
ZTEST_CASE ( Resolve_NormalCase012_Test )
{
    // [Preparation]
    const string_z ABSOLUTE_URI = "http://a/b/c/d;p?q";
    const string_z RELATIVE_URI = "g;x";
    const string_z EXPECTED_URI = "http://a/b/c/g;x";
    Uri absoluteUri(ABSOLUTE_URI);
    Uri relativeUri(RELATIVE_URI);
    const Uri EXPECTED_RESULT(EXPECTED_URI);

    // [Execution]
    absoluteUri.Resolve(relativeUri);
    
    // [Verification]
    BOOST_CHECK(absoluteUri == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it behaves as expected for the case #013.
/// </summary>
ZTEST_CASE ( Resolve_NormalCase013_Test )
{
    // [Preparation]
    const string_z ABSOLUTE_URI = "http://a/b/c/d;p?q";
    const string_z RELATIVE_URI = "g;x?y#s";
    const string_z EXPECTED_URI = "http://a/b/c/g;x?y#s";
    Uri absoluteUri(ABSOLUTE_URI);
    Uri relativeUri(RELATIVE_URI);
    const Uri EXPECTED_RESULT(EXPECTED_URI);

    // [Execution]
    absoluteUri.Resolve(relativeUri);
    
    // [Verification]
    BOOST_CHECK(absoluteUri == EXPECTED_RESULT);
}

// Note: Empty URIs are not allowed
/// <summary>
/// Checks that it behaves as expected for the case #014.
/// </summary>
//ZTEST_CASE ( Resolve_NormalCase014_Test )
//{
//    // [Preparation]
//    const string_z ABSOLUTE_URI = "http://a/b/c/d;p?q";
//    const string_z RELATIVE_URI = "";
//    const string_z EXPECTED_URI = "http://a/b/c/d;p?q";
//    Uri absoluteUri(ABSOLUTE_URI);
//    Uri relativeUri(RELATIVE_URI);
//    const Uri EXPECTED_RESULT(EXPECTED_URI);
//
//    // [Execution]
//    absoluteUri.Resolve(relativeUri);
//    
//    // [Verification]
//    BOOST_CHECK(absoluteUri == EXPECTED_RESULT);
//}

/// <summary>
/// Checks that it behaves as expected for the case #015.
/// </summary>
ZTEST_CASE ( Resolve_NormalCase015_Test )
{
    // [Preparation]
    const string_z ABSOLUTE_URI = "http://a/b/c/d;p?q";
    const string_z RELATIVE_URI = ".";
    const string_z EXPECTED_URI = "http://a/b/c/";
    Uri absoluteUri(ABSOLUTE_URI);
    Uri relativeUri(RELATIVE_URI);
    const Uri EXPECTED_RESULT(EXPECTED_URI);

    // [Execution]
    absoluteUri.Resolve(relativeUri);
    
    // [Verification]
    BOOST_CHECK(absoluteUri == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it behaves as expected for the case #016.
/// </summary>
ZTEST_CASE ( Resolve_NormalCase016_Test )
{
    // [Preparation]
    const string_z ABSOLUTE_URI = "http://a/b/c/d;p?q";
    const string_z RELATIVE_URI = "./";
    const string_z EXPECTED_URI = "http://a/b/c/";
    Uri absoluteUri(ABSOLUTE_URI);
    Uri relativeUri(RELATIVE_URI);
    const Uri EXPECTED_RESULT(EXPECTED_URI);

    // [Execution]
    absoluteUri.Resolve(relativeUri);
    
    // [Verification]
    BOOST_CHECK(absoluteUri == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it behaves as expected for the case #017.
/// </summary>
ZTEST_CASE ( Resolve_NormalCase017_Test )
{
    // [Preparation]
    const string_z ABSOLUTE_URI = "http://a/b/c/d;p?q";
    const string_z RELATIVE_URI = "..";
    const string_z EXPECTED_URI = "http://a/b/";
    Uri absoluteUri(ABSOLUTE_URI);
    Uri relativeUri(RELATIVE_URI);
    const Uri EXPECTED_RESULT(EXPECTED_URI);

    // [Execution]
    absoluteUri.Resolve(relativeUri);
    
    // [Verification]
    BOOST_CHECK(absoluteUri == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it behaves as expected for the case #018.
/// </summary>
ZTEST_CASE ( Resolve_NormalCase018_Test )
{
    // [Preparation]
    const string_z ABSOLUTE_URI = "http://a/b/c/d;p?q";
    const string_z RELATIVE_URI = "../";
    const string_z EXPECTED_URI = "http://a/b/";
    Uri absoluteUri(ABSOLUTE_URI);
    Uri relativeUri(RELATIVE_URI);
    const Uri EXPECTED_RESULT(EXPECTED_URI);

    // [Execution]
    absoluteUri.Resolve(relativeUri);
    
    // [Verification]
    BOOST_CHECK(absoluteUri == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it behaves as expected for the case #019.
/// </summary>
ZTEST_CASE ( Resolve_NormalCase019_Test )
{
    // [Preparation]
    const string_z ABSOLUTE_URI = "http://a/b/c/d;p?q";
    const string_z RELATIVE_URI = "../g";
    const string_z EXPECTED_URI = "http://a/b/g";
    Uri absoluteUri(ABSOLUTE_URI);
    Uri relativeUri(RELATIVE_URI);
    const Uri EXPECTED_RESULT(EXPECTED_URI);

    // [Execution]
    absoluteUri.Resolve(relativeUri);
    
    // [Verification]
    BOOST_CHECK(absoluteUri == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it behaves as expected for the case #020.
/// </summary>
ZTEST_CASE ( Resolve_NormalCase020_Test )
{
    // [Preparation]
    const string_z ABSOLUTE_URI = "http://a/b/c/d;p?q";
    const string_z RELATIVE_URI = "../..";
    const string_z EXPECTED_URI = "http://a/";
    Uri absoluteUri(ABSOLUTE_URI);
    Uri relativeUri(RELATIVE_URI);
    const Uri EXPECTED_RESULT(EXPECTED_URI);

    // [Execution]
    absoluteUri.Resolve(relativeUri);
    
    // [Verification]
    BOOST_CHECK(absoluteUri == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it behaves as expected for the case #021.
/// </summary>
ZTEST_CASE ( Resolve_NormalCase021_Test )
{
    // [Preparation]
    const string_z ABSOLUTE_URI = "http://a/b/c/d;p?q";
    const string_z RELATIVE_URI = "../../";
    const string_z EXPECTED_URI = "http://a/";
    Uri absoluteUri(ABSOLUTE_URI);
    Uri relativeUri(RELATIVE_URI);
    const Uri EXPECTED_RESULT(EXPECTED_URI);

    // [Execution]
    absoluteUri.Resolve(relativeUri);
    
    // [Verification]
    BOOST_CHECK(absoluteUri == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it behaves as expected for the case #022.
/// </summary>
ZTEST_CASE ( Resolve_NormalCase022_Test )
{
    // [Preparation]
    const string_z ABSOLUTE_URI = "http://a/b/c/d;p?q";
    const string_z RELATIVE_URI = "../../g";
    const string_z EXPECTED_URI = "http://a/g";
    Uri absoluteUri(ABSOLUTE_URI);
    Uri relativeUri(RELATIVE_URI);
    const Uri EXPECTED_RESULT(EXPECTED_URI);

    // [Execution]
    absoluteUri.Resolve(relativeUri);
    
    // [Verification]
    BOOST_CHECK(absoluteUri == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it behaves as expected for the abnormal case #002.
/// </summary>
ZTEST_CASE ( Resolve_AbnormalCase002_Test )
{
    // [Preparation]
    const string_z ABSOLUTE_URI = "http://a/b/c/d;p?q";
    const string_z RELATIVE_URI = "../../../g";
    const string_z EXPECTED_URI = "http://a/g";
    Uri absoluteUri(ABSOLUTE_URI);
    Uri relativeUri(RELATIVE_URI);
    const Uri EXPECTED_RESULT(EXPECTED_URI);

    // [Execution]
    absoluteUri.Resolve(relativeUri);
    
    // [Verification]
    BOOST_CHECK(absoluteUri == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it behaves as expected for the abnormal case #003.
/// </summary>
ZTEST_CASE ( Resolve_AbnormalCase003_Test )
{
    // [Preparation]
    const string_z ABSOLUTE_URI = "http://a/b/c/d;p?q";
    const string_z RELATIVE_URI = "/./g";
    const string_z EXPECTED_URI = "http://a/g";
    Uri absoluteUri(ABSOLUTE_URI);
    Uri relativeUri(RELATIVE_URI);
    const Uri EXPECTED_RESULT(EXPECTED_URI);

    // [Execution]
    absoluteUri.Resolve(relativeUri);
    
    // [Verification]
    BOOST_CHECK(absoluteUri == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it behaves as expected for the abnormal case #004.
/// </summary>
ZTEST_CASE ( Resolve_AbnormalCase004_Test )
{
    // [Preparation]
    const string_z ABSOLUTE_URI = "http://a/b/c/d;p?q";
    const string_z RELATIVE_URI = "/../g";
    const string_z EXPECTED_URI = "http://a/g";
    Uri absoluteUri(ABSOLUTE_URI);
    Uri relativeUri(RELATIVE_URI);
    const Uri EXPECTED_RESULT(EXPECTED_URI);

    // [Execution]
    absoluteUri.Resolve(relativeUri);
    
    // [Verification]
    BOOST_CHECK(absoluteUri == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it behaves as expected for the abnormal case #005.
/// </summary>
ZTEST_CASE ( Resolve_AbnormalCase005_Test )
{
    // [Preparation]
    const string_z ABSOLUTE_URI = "http://a/b/c/d;p?q";
    const string_z RELATIVE_URI = "g.";
    const string_z EXPECTED_URI = "http://a/b/c/g.";
    Uri absoluteUri(ABSOLUTE_URI);
    Uri relativeUri(RELATIVE_URI);
    const Uri EXPECTED_RESULT(EXPECTED_URI);

    // [Execution]
    absoluteUri.Resolve(relativeUri);
    
    // [Verification]
    BOOST_CHECK(absoluteUri == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it behaves as expected for the abnormal case #006.
/// </summary>
ZTEST_CASE ( Resolve_AbnormalCase006_Test )
{
    // [Preparation]
    const string_z ABSOLUTE_URI = "http://a/b/c/d;p?q";
    const string_z RELATIVE_URI = ".g";
    const string_z EXPECTED_URI = "http://a/b/c/.g";
    Uri absoluteUri(ABSOLUTE_URI);
    Uri relativeUri(RELATIVE_URI);
    const Uri EXPECTED_RESULT(EXPECTED_URI);

    // [Execution]
    absoluteUri.Resolve(relativeUri);
    
    // [Verification]
    BOOST_CHECK(absoluteUri == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it behaves as expected for the abnormal case #007.
/// </summary>
ZTEST_CASE ( Resolve_AbnormalCase007_Test )
{
    // [Preparation]
    const string_z ABSOLUTE_URI = "http://a/b/c/d;p?q";
    const string_z RELATIVE_URI = "g..";
    const string_z EXPECTED_URI = "http://a/b/c/g..";
    Uri absoluteUri(ABSOLUTE_URI);
    Uri relativeUri(RELATIVE_URI);
    const Uri EXPECTED_RESULT(EXPECTED_URI);

    // [Execution]
    absoluteUri.Resolve(relativeUri);
    
    // [Verification]
    BOOST_CHECK(absoluteUri == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it behaves as expected for the abnormal case #008.
/// </summary>
ZTEST_CASE ( Resolve_AbnormalCase008_Test )
{
    // [Preparation]
    const string_z ABSOLUTE_URI = "http://a/b/c/d;p?q";
    const string_z RELATIVE_URI = "..g";
    const string_z EXPECTED_URI = "http://a/b/c/..g";
    Uri absoluteUri(ABSOLUTE_URI);
    Uri relativeUri(RELATIVE_URI);
    const Uri EXPECTED_RESULT(EXPECTED_URI);

    // [Execution]
    absoluteUri.Resolve(relativeUri);
    
    // [Verification]
    BOOST_CHECK(absoluteUri == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it behaves as expected for the abnormal case #009.
/// </summary>
ZTEST_CASE ( Resolve_AbnormalCase009_Test )
{
    // [Preparation]
    const string_z ABSOLUTE_URI = "http://a/b/c/d;p?q";
    const string_z RELATIVE_URI = "./../g";
    const string_z EXPECTED_URI = "http://a/b/g";
    Uri absoluteUri(ABSOLUTE_URI);
    Uri relativeUri(RELATIVE_URI);
    const Uri EXPECTED_RESULT(EXPECTED_URI);

    // [Execution]
    absoluteUri.Resolve(relativeUri);
    
    // [Verification]
    BOOST_CHECK(absoluteUri == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it behaves as expected for the abnormal case #010.
/// </summary>
ZTEST_CASE ( Resolve_AbnormalCase010_Test )
{
    // [Preparation]
    const string_z ABSOLUTE_URI = "http://a/b/c/d;p?q";
    const string_z RELATIVE_URI = "./g/.";
    const string_z EXPECTED_URI = "http://a/b/c/g/";
    Uri absoluteUri(ABSOLUTE_URI);
    Uri relativeUri(RELATIVE_URI);
    const Uri EXPECTED_RESULT(EXPECTED_URI);

    // [Execution]
    absoluteUri.Resolve(relativeUri);
    
    // [Verification]
    BOOST_CHECK(absoluteUri == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it behaves as expected for the abnormal case #011.
/// </summary>
ZTEST_CASE ( Resolve_AbnormalCase011_Test )
{
    // [Preparation]
    const string_z ABSOLUTE_URI = "http://a/b/c/d;p?q";
    const string_z RELATIVE_URI = "g/./h";
    const string_z EXPECTED_URI = "http://a/b/c/g/h";
    Uri absoluteUri(ABSOLUTE_URI);
    Uri relativeUri(RELATIVE_URI);
    const Uri EXPECTED_RESULT(EXPECTED_URI);

    // [Execution]
    absoluteUri.Resolve(relativeUri);
    
    // [Verification]
    BOOST_CHECK(absoluteUri == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it behaves as expected for the abnormal case #012.
/// </summary>
ZTEST_CASE ( Resolve_AbnormalCase012_Test )
{
    // [Preparation]
    const string_z ABSOLUTE_URI = "http://a/b/c/d;p?q";
    const string_z RELATIVE_URI = "g/../h";
    const string_z EXPECTED_URI = "http://a/b/c/h";
    Uri absoluteUri(ABSOLUTE_URI);
    Uri relativeUri(RELATIVE_URI);
    const Uri EXPECTED_RESULT(EXPECTED_URI);

    // [Execution]
    absoluteUri.Resolve(relativeUri);
    
    // [Verification]
    BOOST_CHECK(absoluteUri == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it behaves as expected for the abnormal case #013.
/// </summary>
ZTEST_CASE ( Resolve_AbnormalCase013_Test )
{
    // [Preparation]
    const string_z ABSOLUTE_URI = "http://a/b/c/d;p?q";
    const string_z RELATIVE_URI = "g;x=1/./y";
    const string_z EXPECTED_URI = "http://a/b/c/g;x=1/y";
    Uri absoluteUri(ABSOLUTE_URI);
    Uri relativeUri(RELATIVE_URI);
    const Uri EXPECTED_RESULT(EXPECTED_URI);

    // [Execution]
    absoluteUri.Resolve(relativeUri);
    
    // [Verification]
    BOOST_CHECK(absoluteUri == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it behaves as expected for the abnormal case #014.
/// </summary>
ZTEST_CASE ( Resolve_AbnormalCase014_Test )
{
    // [Preparation]
    const string_z ABSOLUTE_URI = "http://a/b/c/d;p?q";
    const string_z RELATIVE_URI = "g;x=1/../y";
    const string_z EXPECTED_URI = "http://a/b/c/y";
    Uri absoluteUri(ABSOLUTE_URI);
    Uri relativeUri(RELATIVE_URI);
    const Uri EXPECTED_RESULT(EXPECTED_URI);

    // [Execution]
    absoluteUri.Resolve(relativeUri);
    
    // [Verification]
    BOOST_CHECK(absoluteUri == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it behaves as expected for the abnormal case #015.
/// </summary>
ZTEST_CASE ( Resolve_AbnormalCase015_Test )
{
    // [Preparation]
    const string_z ABSOLUTE_URI = "http://a/b/c/d;p?q";
    const string_z RELATIVE_URI = "g?y/./x";
    const string_z EXPECTED_URI = "http://a/b/c/g?y/./x";
    Uri absoluteUri(ABSOLUTE_URI);
    Uri relativeUri(RELATIVE_URI);
    const Uri EXPECTED_RESULT(EXPECTED_URI);

    // [Execution]
    absoluteUri.Resolve(relativeUri);
    
    // [Verification]
    BOOST_CHECK(absoluteUri == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it behaves as expected for the abnormal case #016.
/// </summary>
ZTEST_CASE ( Resolve_AbnormalCase016_Test )
{
    // [Preparation]
    const string_z ABSOLUTE_URI = "http://a/b/c/d;p?q";
    const string_z RELATIVE_URI = "g?y/../x";
    const string_z EXPECTED_URI = "http://a/b/c/g?y/../x";
    Uri absoluteUri(ABSOLUTE_URI);
    Uri relativeUri(RELATIVE_URI);
    const Uri EXPECTED_RESULT(EXPECTED_URI);

    // [Execution]
    absoluteUri.Resolve(relativeUri);
    
    // [Verification]
    BOOST_CHECK(absoluteUri == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it behaves as expected for the abnormal case #017.
/// </summary>
ZTEST_CASE ( Resolve_AbnormalCase017_Test )
{
    // [Preparation]
    const string_z ABSOLUTE_URI = "http://a/b/c/d;p?q";
    const string_z RELATIVE_URI = "g#s/./x";
    const string_z EXPECTED_URI = "http://a/b/c/g#s/./x";
    Uri absoluteUri(ABSOLUTE_URI);
    Uri relativeUri(RELATIVE_URI);
    const Uri EXPECTED_RESULT(EXPECTED_URI);

    // [Execution]
    absoluteUri.Resolve(relativeUri);
    
    // [Verification]
    BOOST_CHECK(absoluteUri == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it behaves as expected for the abnormal case #018.
/// </summary>
ZTEST_CASE ( Resolve_AbnormalCase018_Test )
{
    // [Preparation]
    const string_z ABSOLUTE_URI = "http://a/b/c/d;p?q";
    const string_z RELATIVE_URI = "g#s/../x";
    const string_z EXPECTED_URI = "http://a/b/c/g#s/../x";
    Uri absoluteUri(ABSOLUTE_URI);
    Uri relativeUri(RELATIVE_URI);
    const Uri EXPECTED_RESULT(EXPECTED_URI);

    // [Execution]
    absoluteUri.Resolve(relativeUri);
    
    // [Verification]
    BOOST_CHECK(absoluteUri == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it behaves as expected for the extra case #001.
/// </summary>
ZTEST_CASE ( Resolve_ExtraCase001_Test )
{
    // [Preparation]
    const string_z ABSOLUTE_URI = "http://a/b/c/d;p?q#f";
    const string_z RELATIVE_URI = "g?y#s";
    const string_z EXPECTED_URI = "http://a/b/c/g?y#s";
    Uri absoluteUri(ABSOLUTE_URI);
    Uri relativeUri(RELATIVE_URI);
    const Uri EXPECTED_RESULT(EXPECTED_URI);

    // [Execution]
    absoluteUri.Resolve(relativeUri);
    
    // [Verification]
    BOOST_CHECK(absoluteUri == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it behaves as expected for the extra case #002.
/// </summary>
ZTEST_CASE ( Resolve_ExtraCase002_Test )
{
    // [Preparation]
    const string_z ABSOLUTE_URI = "http://a/b/c/d;p#f";
    const string_z RELATIVE_URI = "#s";
    const string_z EXPECTED_URI = "http://a/b/c/d;p#s";
    Uri absoluteUri(ABSOLUTE_URI);
    Uri relativeUri(RELATIVE_URI);
    const Uri EXPECTED_RESULT(EXPECTED_URI);

    // [Execution]
    absoluteUri.Resolve(relativeUri);
    
    // [Verification]
    BOOST_CHECK(absoluteUri == EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails whent he input URI is not relative.
/// </summary>
ZTEST_CASE ( Resolve_AssertionFailsWhenInputUriIsNotRelative_Test )
{
    // [Preparation]
    const string_z ABSOLUTE_URI = "http://a/b/c/d;p#f";
    const string_z INPUT_URI = "http://z/x/7";
    Uri absoluteUri(ABSOLUTE_URI);
    Uri inputUri(INPUT_URI);
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        absoluteUri.Resolve(inputUri);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }
    
    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails whent he resident URI is not absolute.
/// </summary>
ZTEST_CASE ( Resolve_AssertionFailsWhenResident6UriIsNotAbsolute_Test )
{
    // [Preparation]
    const string_z RELATIVE_URI = "a/b/c/d;p#f";
    const string_z INPUT_URI = "z/x/7";
    Uri relativeUri(RELATIVE_URI);
    Uri inputUri(INPUT_URI);
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        relativeUri.Resolve(inputUri);
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
/// Checks that the string has the expected value when the URI only contains a scheme.
/// </summary>
ZTEST_CASE ( ToString_StringIsWhatExpectedWhenUriContainsSchemeOnly_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "scheme:";
    const string_z EXPECTED_VALUE = INPUT_STRING;
    Uri uri(INPUT_STRING);

    // [Execution]
    string_z strResult = uri.ToString();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the string has the expected value when the URI only contains a scheme and the authority.
/// </summary>
ZTEST_CASE ( ToString_StringIsWhatExpectedWhenUriContainsSchemeAndAuthorityOnly_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "scheme://authority";
    const string_z EXPECTED_VALUE = INPUT_STRING;
    Uri uri(INPUT_STRING);

    // [Execution]
    string_z strResult = uri.ToString();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the string has the expected value when the URI contains the scheme, the authority and the path.
/// </summary>
ZTEST_CASE ( ToString_StringIsWhatExpectedWhenUriContainsSchemeAuthorityAndPath_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "scheme://authority/path";
    const string_z EXPECTED_VALUE = INPUT_STRING;
    Uri uri(INPUT_STRING);

    // [Execution]
    string_z strResult = uri.ToString();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the string has the expected value when the URI contains an IPv6 as host and a port.
/// </summary>
ZTEST_CASE ( ToString_StringIsWhatExpectedWhenUriContainsIPv6AndPort_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "scheme://[fe80::4cf7:6fe6:453f:8129]:port/pat:h";
    const string_z EXPECTED_VALUE = INPUT_STRING;
    Uri uri(INPUT_STRING);

    // [Execution]
    string_z strResult = uri.ToString();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the string has the expected value when the URI contains the scheme, the authority, the path and the query.
/// </summary>
ZTEST_CASE ( ToString_StringIsWhatExpectedWhenUriContainsSchemeAuthorityPathAndQuery_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "scheme://authority/path?query";
    const string_z EXPECTED_VALUE = INPUT_STRING;
    Uri uri(INPUT_STRING);

    // [Execution]
    string_z strResult = uri.ToString();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the string has the expected value when the URI contains the scheme and the path only.
/// </summary>
ZTEST_CASE ( ToString_StringIsWhatExpectedWhenInputContainsSchemeAndPathOnly_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "scheme:/pathsegment1/pathsegment2";
    const string_z EXPECTED_VALUE = INPUT_STRING;
    Uri uri(INPUT_STRING);

    // [Execution]
    string_z strResult = uri.ToString();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the string is what expected when the URI contains an empty path and a query.
/// </summary>
ZTEST_CASE ( ToString_StringIsWhatExpectedWhenUriContainsEmptyPathAndQuery_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "scheme://host?query";
    const string_z EXPECTED_VALUE = INPUT_STRING;
    Uri uri(INPUT_STRING);

    // [Execution]
    string_z strResult = uri.ToString();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the string is what expected when the URI contains an empty path and a fragment.
/// </summary>
ZTEST_CASE ( ToString_StringIsWhatExpectedWhenUriContainsEmptyPathAndFragment_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "scheme://host#fragment";
    const string_z EXPECTED_VALUE = INPUT_STRING;
    Uri uri(INPUT_STRING);

    // [Execution]
    string_z strResult = uri.ToString();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the string has the expected value when the authority is formed only by a host.
/// </summary>
ZTEST_CASE ( ToString_StringIsWhatExpectedWhenAuthorityIsFormedOnlyByHost_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "scheme://authority/path";
    const string_z EXPECTED_VALUE = INPUT_STRING;
    Uri uri(INPUT_STRING);

    // [Execution]
    string_z strResult = uri.ToString();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the string has the expected value when the authority is formed only by a host and the user information.
/// </summary>
ZTEST_CASE ( ToString_StringIsWhatExpectedWhenAuthorityIsFormedOnlyByUserInfoAndHost_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "//userinfo@host";
    const string_z EXPECTED_VALUE = INPUT_STRING;
    Uri uri(INPUT_STRING);

    // [Execution]
    string_z strResult = uri.ToString();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the string has the expected value when the authority is formed only by a host, the port and the user information.
/// </summary>
ZTEST_CASE ( ToString_StringIsWhatExpectedWhenAuthorityIsFormedOnlyByUserInfoHostAndPort_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "//userinfo@host:port";
    const string_z EXPECTED_VALUE = INPUT_STRING;
    Uri uri(INPUT_STRING);

    // [Execution]
    string_z strResult = uri.ToString();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the string has the expected value when the authority is formed only by a host and the port.
/// </summary>
ZTEST_CASE ( ToString_StringIsWhatExpectedWhenAuthorityIsFormedOnlyByHostAndPort_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "//host:port";
    const string_z EXPECTED_VALUE = INPUT_STRING;
    Uri uri(INPUT_STRING);

    // [Execution]
    string_z strResult = uri.ToString();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the string has the expected value when the URI is formed only by the authority and the path.
/// </summary>
ZTEST_CASE ( ToString_StringIsWhatExpectedWhenUriIsFormedOnlyByAuthorityAndPath_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "//userinfo@host:port/path";
    const string_z EXPECTED_VALUE = INPUT_STRING;
    Uri uri(INPUT_STRING);

    // [Execution]
    string_z strResult = uri.ToString();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the string has the expected value when the URI is formed only by the authority and the query.
/// </summary>
ZTEST_CASE ( ToStringStringIsWhatExpectedWhenUriIsFormedOnlyByAuthorityAndQuery_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "//userinfo@host:port?query";
    const string_z EXPECTED_VALUE = INPUT_STRING;
    Uri uri(INPUT_STRING);

    // [Execution]
    string_z strResult = uri.ToString();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the string has the expected value when the URI is formed only by the authority and the fragment.
/// </summary>
ZTEST_CASE ( ToString_StringIsWhatExpectedWhenUriIsFormedOnlyByAuthorityAndFragment_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "//userinfo@host:port#fragment";
    const string_z EXPECTED_VALUE = INPUT_STRING;
    Uri uri(INPUT_STRING);

    // [Execution]
    string_z strResult = uri.ToString();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the path does not start with a slash when it does not start with a slash in the input string.
/// </summary>
ZTEST_CASE ( ToString_PathDoesNotStartWithSlashWhenUriIsFormedOnlyByPathWhichDoesNotStartWithSlash_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "segment1/segment2";
    const string_z EXPECTED_VALUE = INPUT_STRING;
    Uri uri(INPUT_STRING);

    // [Execution]
    string_z strResult = uri.ToString();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the path starts with a slash when it starts with a slash in the input string.
/// </summary>
ZTEST_CASE ( ToString_PathStartsWithSlashWhenUriIsFormedOnlyByPathWhichStartsWithSlash_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "/segment1/segment2";
    const string_z EXPECTED_VALUE = INPUT_STRING;
    Uri uri(INPUT_STRING);

    // [Execution]
    string_z strResult = uri.ToString();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the path includes the initial dot segment when it starts with one dot.
/// </summary>
ZTEST_CASE ( ToString_PathIncludesDotSegmentWhenUriIsFormedOnlyByPathWhichStartsWithOneDot_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "./segment1/segment2";
    const string_z EXPECTED_VALUE = INPUT_STRING;
    Uri uri(INPUT_STRING);

    // [Execution]
    string_z strResult = uri.ToString();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the path does not include the initial dot segment when it starts with two dots.
/// </summary>
ZTEST_CASE ( ToString_PathDoesNotIncludeDotSegmentWhenUriIsFormedOnlyByPathWhichStartsWithTwoDots_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "../segment1/segment2";
    const string_z EXPECTED_VALUE = INPUT_STRING;
    Uri uri(INPUT_STRING);

    // [Execution]
    string_z strResult = uri.ToString();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the string has the expected value when the URI is formed only by the path and the query.
/// </summary>
ZTEST_CASE ( ToString_StringIsWhatExpectedWhenUriIsFormedOnlyByPathAndQuery_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "path1/path2?query=value";
    const string_z EXPECTED_VALUE = INPUT_STRING;
    Uri uri(INPUT_STRING);

    // [Execution]
    string_z strResult = uri.ToString();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the string has the expected value when the URI is formed only by the path and the fragment.
/// </summary>
ZTEST_CASE ( ToString_StringIsWhatExpectedWhenUriIsFormedOnlyByPathAndFragment_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "path1/path2#fragment";
    const string_z EXPECTED_VALUE = INPUT_STRING;
    Uri uri(INPUT_STRING);

    // [Execution]
    string_z strResult = uri.ToString();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the path is empty and starts with a slash when the URI only contains a single slash.
/// </summary>
ZTEST_CASE ( ToString_PathIsEmptyAndStartsWithSlashWhenUriContainsOnlyOneSlash_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "/";
    const string_z EXPECTED_VALUE = INPUT_STRING;
    Uri uri(INPUT_STRING);

    // [Execution]
    string_z strResult = uri.ToString();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_VALUE);
}

/// <summary>
/// Checks that all dot segments that appear in the middle of the path are removed.
/// </summary>
ZTEST_CASE ( ToString_DotSegmentsAreRemoved_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "scheme://userinfo@authority/path1/./path2/../path3";
    const string_z EXPECTED_VALUE = "scheme://userinfo@authority/path1/path3";
    Uri uri(INPUT_STRING);

    // [Execution]
    string_z strResult = uri.ToString();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the path contains one segment when the URI does not contain any separator.
/// </summary>
ZTEST_CASE ( ToString_ThePathContainsOneSegmentWhenTheUriDoesNotContainAnySeparator_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "schemeauthoritypath";
    const string_z EXPECTED_VALUE = INPUT_STRING;
    Uri uri(INPUT_STRING);

    // [Execution]
    string_z strResult = uri.ToString();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_VALUE);
}

/// <summary>
/// Checks that question marks ("?") and slashes ("/") are encoded.
/// </summary>
ZTEST_CASE ( EncodePathSegment_QuestionMarkAndSlashAreEncoded_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "/?";
    const string_z EXPECTED_STRING = "%2F%3F";
    string_z strResult;

    // [Execution]
    Uri::EncodePathSegment(INPUT_STRING, strResult);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_STRING);
}

/// <summary>
/// Checks that all the characters that are allowed in the path are not encoded.
/// </summary>
ZTEST_CASE ( EncodePathSegment_AllowedCharsAreNotEncoded_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-._~&'*(),$=!+;:@";
    const string_z EXPECTED_STRING = INPUT_STRING;
    string_z strResult;

    // [Execution]
    Uri::EncodePathSegment(INPUT_STRING, strResult);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_STRING);
}

/// <summary>
/// Checks that Unicode (non-ASCII) characters are encoded.
/// </summary>
ZTEST_CASE ( EncodePathSegment_UnicodeCharsAreEncoded_Test )
{
    // [Preparation]
    string_z INPUT_STRING;
    INPUT_STRING.Append(char_z(0x00D1)); // LATIN CAPITAL LETTER N WITH TILDE, UTF8: C3 91
    INPUT_STRING.Append(char_z(0x10A3)); // GEORGIAN CAPITAL LETTER DON, UTF8: E1 82 A3
    INPUT_STRING.Append(char_z(0x16E3)); // RUNIC LETTER CALC, UTF8: E1 9B A3
    INPUT_STRING.Append(char_z(0xFF96)); // HALFWIDTH KATAKANA LETTER YO, UTF8: EF BE 96
    const string_z EXPECTED_STRING = "%C3%91%E1%82%A3%E1%9B%A3%EF%BE%96";
    string_z strResult;

    // [Execution]
    Uri::EncodePathSegment(INPUT_STRING, strResult);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_STRING);
}

/// <summary>
/// Checks that all the ASCII characters that are not allowed in the path are encoded.
/// </summary>
ZTEST_CASE ( EncodePathSegment_AsciiNotAllowedCharsAreEncoded_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "<> \\[]{}\"|";
    const string_z EXPECTED_STRING = "%3C%3E%20%5C%5B%5D%7B%7D%22%7C";
    string_z strResult;

    // [Execution]
    Uri::EncodePathSegment(INPUT_STRING, strResult);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_STRING);
}

/// <summary>
/// Checks that all the percent sign ("%") is not encoded.
/// </summary>
ZTEST_CASE ( EncodePathSegment_PercentSignIsNotEncoded_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "%";
    const string_z EXPECTED_STRING = "%";
    string_z strResult;

    // [Execution]
    Uri::EncodePathSegment(INPUT_STRING, strResult);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_STRING);
}

/// <summary>
/// Checks that the input string can be also the output string.
/// </summary>
ZTEST_CASE ( EncodePathSegment_InputStringCanBeAlsoOutputString_Test )
{
    // [Preparation]
    string_z strInputOutput = "123 456";
    const string_z EXPECTED_STRING = "123%20456";

    // [Execution]
    Uri::EncodePathSegment(strInputOutput, strInputOutput);
    
    // [Verification]
    BOOST_CHECK(strInputOutput == EXPECTED_STRING);
}

/// <summary>
/// Checks that the output string equals empty when the input string is empty.
/// </summary>
ZTEST_CASE ( EncodePathSegment_OutputStringEqualsEmptyWhenInputIsEmpty_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = string_z::GetEmpty();
    const string_z EXPECTED_STRING = string_z::GetEmpty();
    string_z strResult = "123456";

    // [Execution]
    Uri::EncodePathSegment(INPUT_STRING, strResult);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_STRING);
}

/// <summary>
/// Checks that question marks ("?") and slashes ("/") are not encoded.
/// </summary>
ZTEST_CASE ( EncodeQueryOrFragment_QuestionMarkAndSlashAreNotEncoded_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "/?";
    const string_z EXPECTED_STRING = "/?";
    string_z strResult;

    // [Execution]
    Uri::EncodeQueryOrFragment(INPUT_STRING, strResult);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_STRING);
}

/// <summary>
/// Checks that all the characters that are allowed in the path are not encoded.
/// </summary>
ZTEST_CASE ( EncodeQueryOrFragment_AllowedCharsAreNotEncoded_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-._~&'*(),$=!+;:@";
    const string_z EXPECTED_STRING = INPUT_STRING;
    string_z strResult;

    // [Execution]
    Uri::EncodeQueryOrFragment(INPUT_STRING, strResult);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_STRING);
}

/// <summary>
/// Checks that Unicode (non-ASCII) characters are encoded.
/// </summary>
ZTEST_CASE ( EncodeQueryOrFragment_UnicodeCharsAreEncoded_Test )
{
    // [Preparation]
    string_z INPUT_STRING;
    INPUT_STRING.Append(char_z(0x00D1)); // LATIN CAPITAL LETTER N WITH TILDE, UTF8: C3 91
    INPUT_STRING.Append(char_z(0x10A3)); // GEORGIAN CAPITAL LETTER DON, UTF8: E1 82 A3
    INPUT_STRING.Append(char_z(0x16E3)); // RUNIC LETTER CALC, UTF8: E1 9B A3
    INPUT_STRING.Append(char_z(0xFF96)); // HALFWIDTH KATAKANA LETTER YO, UTF8: EF BE 96
    const string_z EXPECTED_STRING = "%C3%91%E1%82%A3%E1%9B%A3%EF%BE%96";
    string_z strResult;

    // [Execution]
    Uri::EncodeQueryOrFragment(INPUT_STRING, strResult);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_STRING);
}

/// <summary>
/// Checks that all the ASCII characters that are not allowed in the path are encoded.
/// </summary>
ZTEST_CASE ( EncodeQueryOrFragment_AsciiNotAllowedCharsAreEncoded_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "<> \\[]{}\"|";
    const string_z EXPECTED_STRING = "%3C%3E%20%5C%5B%5D%7B%7D%22%7C";
    string_z strResult;

    // [Execution]
    Uri::EncodeQueryOrFragment(INPUT_STRING, strResult);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_STRING);
}

/// <summary>
/// Checks that all the percent sign ("%") is not encoded.
/// </summary>
ZTEST_CASE ( EncodeQueryOrFragment_PercentSignIsNotEncoded_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "%";
    const string_z EXPECTED_STRING = "%";
    string_z strResult;

    // [Execution]
    Uri::EncodeQueryOrFragment(INPUT_STRING, strResult);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_STRING);
}

/// <summary>
/// Checks that the input string can be also the output string.
/// </summary>
ZTEST_CASE ( EncodeQueryOrFragment_InputStringCanBeAlsoOutputString_Test )
{
    // [Preparation]
    string_z strInputOutput = "123 456";
    const string_z EXPECTED_STRING = "123%20456";

    // [Execution]
    Uri::EncodeQueryOrFragment(strInputOutput, strInputOutput);
    
    // [Verification]
    BOOST_CHECK(strInputOutput == EXPECTED_STRING);
}

/// <summary>
/// Checks that the output string equals empty when the input string is empty.
/// </summary>
ZTEST_CASE ( EncodeQueryOrFragment_OutputStringEqualsEmptyWhenInputIsEmpty_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = string_z::GetEmpty();
    const string_z EXPECTED_STRING = string_z::GetEmpty();
    string_z strResult = "123456";

    // [Execution]
    Uri::EncodeQueryOrFragment(INPUT_STRING, strResult);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_STRING);
}

/// <summary>
/// Checks that all the allowed characters are decoded.
/// </summary>
ZTEST_CASE ( Decode_AllowedCharactersAreDecoded_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "%41%61%2B";
    const string_z EXPECTED_STRING = "Aa+";
    string_z strResult;

    // [Execution]
    Uri::Decode(INPUT_STRING, strResult);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_STRING);
}

/// <summary>
/// Checks that all the not allowed ASCII characters are decoded.
/// </summary>
ZTEST_CASE ( Decode_AsciiNotAllowedCharactersAreDecoded_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "%20%3C%7B";
    const string_z EXPECTED_STRING = " <{";
    string_z strResult;

    // [Execution]
    Uri::Decode(INPUT_STRING, strResult);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_STRING);
}

/// <summary>
/// Checks that all the Unicode characters are decoded.
/// </summary>
ZTEST_CASE ( Decode_UnicodeCharactersAreDecoded_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = "%C9%AC%CD%9C%D9%82";
    string_z EXPECTED_STRING;
    EXPECTED_STRING.Append(char_z(0x026C)); // LATIN SMALL LETTER L WITH BELT, UTF8: C9 AC
    EXPECTED_STRING.Append(char_z(0x035C)); // COMBINING DOUBLE BREVE BELOW, UTF8: CD 9C
    EXPECTED_STRING.Append(char_z(0x0642)); // ARABIC LETTER QAF, UTF8: D9 82
    string_z strResult;

    // [Execution]
    Uri::Decode(INPUT_STRING, strResult);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_STRING);
}

/// <summary>
/// Checks that the input string can be also the output string.
/// </summary>
ZTEST_CASE ( Decode_InputStringCanBeAlsoOutputString_Test )
{
    // [Preparation]
    string_z strInputOutput = "123%20456";
    const string_z EXPECTED_STRING = "123 456";

    // [Execution]
    Uri::Decode(strInputOutput, strInputOutput);
    
    // [Verification]
    BOOST_CHECK(strInputOutput == EXPECTED_STRING);
}

/// <summary>
/// Checks that the output string equals empty when the input string is empty.
/// </summary>
ZTEST_CASE ( Decode_OutputStringEqualsEmptyWhenInputIsEmpty_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = string_z::GetEmpty();
    const string_z EXPECTED_STRING = string_z::GetEmpty();
    string_z strResult = "123456";

    // [Execution]
    Uri::Decode(INPUT_STRING, strResult);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_STRING);
}

/// <summary>
/// Checks that single dot segments are not removed when they appear the first.
/// </summary>
ZTEST_CASE ( RemoveDotSegments_SingleDotSegmentsAreNotRemovedWhenTheyAppearTheFirst_Test )
{
    // [Preparation]
    const string_z SINGLE_DOT(".");

    ArrayDynamic<string_z> inputArrayWithSingleDot(3);
    inputArrayWithSingleDot.Add(SINGLE_DOT);
    inputArrayWithSingleDot.Add("path1");
    inputArrayWithSingleDot.Add("path2");

    // [Execution]
    UriWhiteBox::RemoveDotSegments(inputArrayWithSingleDot);
    
    // [Verification]
    bool bSingleDotSegmentWasNotRemoved = inputArrayWithSingleDot[0] == SINGLE_DOT;
    BOOST_CHECK(bSingleDotSegmentWasNotRemoved);
}

/// <summary>
/// Checks that double dot segments are not removed when they appear the first.
/// </summary>
ZTEST_CASE ( RemoveDotSegments_DoubleDotSegmentsAreNotRemovedWhenTheyAppearTheFirst_Test )
{
    // [Preparation]
    const string_z DOUBLE_DOT("..");

    ArrayDynamic<string_z> inputArrayWithDoubleDot(3);
    inputArrayWithDoubleDot.Add(DOUBLE_DOT);
    inputArrayWithDoubleDot.Add("path1");
    inputArrayWithDoubleDot.Add("path2");

    // [Execution]
    UriWhiteBox::RemoveDotSegments(inputArrayWithDoubleDot);
    
    // [Verification]
    bool bDoubleDotSegmentWasNotRemoved = inputArrayWithDoubleDot[0] == DOUBLE_DOT;

    BOOST_CHECK(bDoubleDotSegmentWasNotRemoved);
}

/// <summary>
/// Checks that contiguous double dot segments are not removed when they appear the first.
/// </summary>
ZTEST_CASE ( RemoveDotSegments_ContiguousDoubleDotSegmentsAreNotRemovedWhenTheyAppearTheFirst_Test )
{
    // [Preparation]
    const string_z DOUBLE_DOT("..");

    ArrayDynamic<string_z> inputArrayWithDoubleDot(3);
    inputArrayWithDoubleDot.Add(DOUBLE_DOT);
    inputArrayWithDoubleDot.Add(DOUBLE_DOT);
    inputArrayWithDoubleDot.Add("path1");
    inputArrayWithDoubleDot.Add("path2");

    // [Execution]
    UriWhiteBox::RemoveDotSegments(inputArrayWithDoubleDot);
    
    // [Verification]
    bool bDoubleDotSegmentWasNotRemoved = inputArrayWithDoubleDot[0] == DOUBLE_DOT && 
                                          inputArrayWithDoubleDot[1] == DOUBLE_DOT;

    BOOST_CHECK(bDoubleDotSegmentWasNotRemoved);
}

/// <summary>
/// Checks that it works as expected when there are several double dot segments after one common segment at the beginning.
/// </summary>
ZTEST_CASE ( RemoveDotSegments_WorksAsExpectedWhenThereAreSeveralDoubleDotSegmentsAfterOneCommonSegmentAtTheBeginning_Test )
{
    // [Preparation]
    const string_z DOUBLE_DOT("..");

    const string_z EXPECTED_FIRST_SEGMENT = DOUBLE_DOT;
    const puint_z EXPECTED_COUNT = 1;
    ArrayDynamic<string_z> inputArrayWithDoubleDot(3);
    inputArrayWithDoubleDot.Add("path1");
    inputArrayWithDoubleDot.Add(DOUBLE_DOT);
    inputArrayWithDoubleDot.Add(DOUBLE_DOT);

    // [Execution]
    UriWhiteBox::RemoveDotSegments(inputArrayWithDoubleDot);
    
    // [Verification]
    string_z strFirstElement = inputArrayWithDoubleDot[0];
    puint_z uCount = inputArrayWithDoubleDot.GetCount();

    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
    BOOST_CHECK(strFirstElement == EXPECTED_FIRST_SEGMENT);
}

/// <summary>
/// Checks that it works as expected when there are more double dot segments than common segments at the beginning.
/// </summary>
ZTEST_CASE ( RemoveDotSegments_WorksAsExpectedWhenThereAreMoreDoubleDotSegmentsThanCommonSegmentsAtTheBeginning_Test )
{
    // [Preparation]
    const string_z DOUBLE_DOT("..");

    const string_z EXPECTED_FIRST_SEGMENT = DOUBLE_DOT;
    const puint_z EXPECTED_COUNT = 1;
    ArrayDynamic<string_z> inputArrayWithDoubleDot(5);
    inputArrayWithDoubleDot.Add("path1");
    inputArrayWithDoubleDot.Add("path2");
    inputArrayWithDoubleDot.Add(DOUBLE_DOT);
    inputArrayWithDoubleDot.Add(DOUBLE_DOT);
    inputArrayWithDoubleDot.Add(DOUBLE_DOT);

    // [Execution]
    UriWhiteBox::RemoveDotSegments(inputArrayWithDoubleDot);
    
    // [Verification]
    string_z strFirstElement = inputArrayWithDoubleDot[0];
    puint_z uCount = inputArrayWithDoubleDot.GetCount();

    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
    BOOST_CHECK(strFirstElement == EXPECTED_FIRST_SEGMENT);
}

/// <summary>
/// Checks that dot segments are not removed when the path is compound only of double dot segments.
/// </summary>
ZTEST_CASE ( RemoveDotSegments_DotSegmentsAreNotRemovedWhenPathIsCompoundOnlyOfDoubleDotSegments_Test )
{
    // [Preparation]
    const string_z DOUBLE_DOT("..");

    const puint_z EXPECTED_COUNT = 3;
    ArrayDynamic<string_z> inputArrayWithDoubleDot(3);
    inputArrayWithDoubleDot.Add(DOUBLE_DOT);
    inputArrayWithDoubleDot.Add(DOUBLE_DOT);
    inputArrayWithDoubleDot.Add(DOUBLE_DOT);

    // [Execution]
    UriWhiteBox::RemoveDotSegments(inputArrayWithDoubleDot);
    
    // [Verification]
    puint_z uCount = inputArrayWithDoubleDot.GetCount();

    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that single dot segments are removed when they appear in between of contiguous double dot segments which appear the first.
/// </summary>
ZTEST_CASE ( RemoveDotSegments_SingleDotSegmentsAreRemovedWhenTheyAppearBetweenContiguousDoubleDotSegmentsThatAppearTheFirst_Test )
{
    // [Preparation]
    const string_z SINGLE_DOT(".");
    const string_z DOUBLE_DOT("..");

    ArrayDynamic<string_z> inputArrayWithDoubleDot(5);
    inputArrayWithDoubleDot.Add(DOUBLE_DOT);
    inputArrayWithDoubleDot.Add(SINGLE_DOT);
    inputArrayWithDoubleDot.Add(DOUBLE_DOT);
    inputArrayWithDoubleDot.Add("path1");
    inputArrayWithDoubleDot.Add("path2");

    // [Execution]
    UriWhiteBox::RemoveDotSegments(inputArrayWithDoubleDot);
    
    // [Verification]
    bool bSingleDotSegmentWasRemoved = inputArrayWithDoubleDot[0] == DOUBLE_DOT && 
                                          inputArrayWithDoubleDot[1] == DOUBLE_DOT;

    BOOST_CHECK(bSingleDotSegmentWasRemoved);
}

/// <summary>
/// Checks that single dot segments are just removed.
/// </summary>
ZTEST_CASE ( RemoveDotSegments_SingleDotSegmentsAreJustRemoved_Test )
{
    // [Preparation]
    const string_z SINGLE_DOT(".");

    ArrayDynamic<string_z> inputArrayWithSingleDot(4);
    inputArrayWithSingleDot.Add("path1");
    inputArrayWithSingleDot.Add(SINGLE_DOT);
    inputArrayWithSingleDot.Add("path2");
    inputArrayWithSingleDot.Add(SINGLE_DOT);

    // [Execution]
    UriWhiteBox::RemoveDotSegments(inputArrayWithSingleDot);
 
    // [Verification]
    bool bSingleDotSegmentWasRemoved = true;

    for(ArrayDynamic<string_z>::ArrayIterator it = inputArrayWithSingleDot.GetFirst(); !it.IsEnd(); ++it)
        bSingleDotSegmentWasRemoved = bSingleDotSegmentWasRemoved && *it != SINGLE_DOT;

    BOOST_CHECK(bSingleDotSegmentWasRemoved);
}

/// <summary>
/// Checks that double dot segments imply previous segment to be removed.
/// </summary>
ZTEST_CASE ( RemoveDotSegments_DoubleDotSegmentsImplyPreviousSegmentToBeRemoved_Test )
{
    // [Preparation]
    const string_z DOUBLE_DOT("..");
    const string_z SEGMENT_TO_BE_REMOVED("path2");

    ArrayDynamic<string_z> inputArrayWithDoubleDots(4);
    inputArrayWithDoubleDots.Add("path1");
    inputArrayWithDoubleDots.Add(SEGMENT_TO_BE_REMOVED);
    inputArrayWithDoubleDots.Add(DOUBLE_DOT);
    inputArrayWithDoubleDots.Add("path3");

    // [Execution]
    UriWhiteBox::RemoveDotSegments(inputArrayWithDoubleDots);
 
    // [Verification]
    bool bDoubleDotSegmentWasRemoved = true;
    bool bSegmentPriorToDotSegmentWasRemoved = true;
    
    ArrayDynamic<string_z>::ArrayIterator it = inputArrayWithDoubleDots.GetFirst();

    for(; !it.IsEnd(); ++it)
        bDoubleDotSegmentWasRemoved = bDoubleDotSegmentWasRemoved && *it != DOUBLE_DOT;

    for(it.MoveFirst(); !it.IsEnd(); ++it)
        bSegmentPriorToDotSegmentWasRemoved = bSegmentPriorToDotSegmentWasRemoved && *it != SEGMENT_TO_BE_REMOVED;

    BOOST_CHECK(bDoubleDotSegmentWasRemoved);
}

/// <summary>
/// Checks that dot segments can be concatenated.
/// </summary>
ZTEST_CASE ( RemoveDotSegments_DotSegmentsCanBeConcatenated_Test )
{
    // [Preparation]
    const string_z SINGLE_DOT(".");
    const string_z DOUBLE_DOT("..");

    ArrayDynamic<string_z> EXPECTED_ARRAY(8);
    EXPECTED_ARRAY.Add("path1");
    EXPECTED_ARRAY.Add("path4");
    
    ArrayDynamic<string_z> inputArrayWithDots(2);
    inputArrayWithDots.Add("path1");
    inputArrayWithDots.Add("path2");
    inputArrayWithDots.Add(SINGLE_DOT);
    inputArrayWithDots.Add("path3");
    inputArrayWithDots.Add(SINGLE_DOT);
    inputArrayWithDots.Add(DOUBLE_DOT);
    inputArrayWithDots.Add(DOUBLE_DOT);
    inputArrayWithDots.Add("path4");

    // [Execution]
    UriWhiteBox::RemoveDotSegments(inputArrayWithDots);
 
    // [Verification]
    bool bResultantArrayIsWhatExpected = true;

    ArrayDynamic<string_z>::ArrayIterator iExpected = EXPECTED_ARRAY.GetFirst();
    ArrayDynamic<string_z>::ArrayIterator iResult = inputArrayWithDots.GetFirst();

    for(; !iExpected.IsEnd(); ++iExpected, ++iResult)
        bResultantArrayIsWhatExpected = bResultantArrayIsWhatExpected && *iExpected == *iResult;

    BOOST_CHECK(bResultantArrayIsWhatExpected);
}

/// <summary>
/// Checks that nothing happens when the array is empty.
/// </summary>
ZTEST_CASE ( RemoveDotSegments_NothingHappensWhenArrayIsEmpty_Test )
{
    // [Preparation]
    ArrayDynamic<string_z> arEmptyArray(1);

    // [Execution]
    UriWhiteBox::RemoveDotSegments(arEmptyArray);
 
    // [Verification]
    BOOST_CHECK(arEmptyArray.IsEmpty());
}

/// <summary>
/// Checks that nothing happens when the array contains only an empty string.
/// </summary>
ZTEST_CASE ( RemoveDotSegments_NothingHappensWhenArrayContainsOnlyAnEmptyString_Test )
{
    // [Preparation]
    ArrayDynamic<string_z> arEmptyArray(1);
    arEmptyArray.Add(string_z::GetEmpty());

    // [Execution]
    UriWhiteBox::RemoveDotSegments(arEmptyArray);
 
    // [Verification]
    BOOST_CHECK(arEmptyArray[0].IsEmpty());
}

/// <summary>
/// Checks that single dot segments are not removed when the path only contains one single dot segment.
/// </summary>
ZTEST_CASE ( RemoveDotSegments_SingleDotSegmentIsNotRemovedWhenPathOnlyContainsOneSingleDotSegment_Test )
{
    // [Preparation]
    const string_z SINGLE_DOT(".");

    ArrayDynamic<string_z> EXPECTED_ARRAY(1);
    EXPECTED_ARRAY.Add(string_z::GetEmpty());
    
    ArrayDynamic<string_z> inputArrayWithDots(2);
    inputArrayWithDots.Add(SINGLE_DOT);

    // [Execution]
    UriWhiteBox::RemoveDotSegments(inputArrayWithDots);
 
    // [Verification]
    bool bSegmentIsNotEmpty = !inputArrayWithDots[0].IsEmpty();
    BOOST_CHECK(bSegmentIsNotEmpty);
}

/// <summary>
/// Checks that single dot segments are not removed when the path starts with one single dot segment followed by a double dot segment.
/// </summary>
ZTEST_CASE ( RemoveDotSegments_SingleDotSegmentIsNotRemovedWhenPathStartsWithOneSingleDotSegmentFollowedByDoubleDotSegment_Test )
{
    // [Preparation]
    const string_z SINGLE_DOT(".");
    const string_z DOUBLE_DOT("..");

    ArrayDynamic<string_z> EXPECTED_ARRAY(2);
    EXPECTED_ARRAY.Add(SINGLE_DOT);
    EXPECTED_ARRAY.Add(DOUBLE_DOT);
    EXPECTED_ARRAY.Add("path1");

    ArrayDynamic<string_z> inputArrayWithDots(3);
    inputArrayWithDots.Add(SINGLE_DOT);
    inputArrayWithDots.Add(DOUBLE_DOT);
    inputArrayWithDots.Add("path1");

    // [Execution]
    UriWhiteBox::RemoveDotSegments(inputArrayWithDots);
 
    // [Verification]
    bool bResultantArrayIsWhatExpected = true;

    ArrayDynamic<string_z>::ArrayIterator iExpected = EXPECTED_ARRAY.GetFirst();
    ArrayDynamic<string_z>::ArrayIterator iResult = inputArrayWithDots.GetFirst();

    for(; !iExpected.IsEnd(); ++iExpected, ++iResult)
        bResultantArrayIsWhatExpected = bResultantArrayIsWhatExpected && *iExpected == *iResult;
    
    BOOST_CHECK(bResultantArrayIsWhatExpected);
}

/// <summary>
/// Checks that dot segments are removed when the path starts with a common segment followed by one single dot segment followed by a double dot segment.
/// </summary>
ZTEST_CASE ( RemoveDotSegments_DotSegmentsAreRemovedWhenPathStartsWithACommonSegmentFollowedByOneSingleDotSegmentFollowedByDoubleDotSegment_Test )
{
    // [Preparation]
    const string_z SINGLE_DOT(".");
    const string_z DOUBLE_DOT("..");

    ArrayDynamic<string_z> EXPECTED_ARRAY(1);
    EXPECTED_ARRAY.Add("path2");

    ArrayDynamic<string_z> inputArrayWithDots(4);
    inputArrayWithDots.Add("path1");
    inputArrayWithDots.Add(SINGLE_DOT);
    inputArrayWithDots.Add(DOUBLE_DOT);
    inputArrayWithDots.Add("path2");

    // [Execution]
    UriWhiteBox::RemoveDotSegments(inputArrayWithDots);
 
    // [Verification]
    bool bResultantArrayIsWhatExpected = true;

    ArrayDynamic<string_z>::ArrayIterator iExpected = EXPECTED_ARRAY.GetFirst();
    ArrayDynamic<string_z>::ArrayIterator iResult = inputArrayWithDots.GetFirst();

    for(; !iExpected.IsEnd(); ++iExpected, ++iResult)
        bResultantArrayIsWhatExpected = bResultantArrayIsWhatExpected && *iExpected == *iResult;
    
    BOOST_CHECK(bResultantArrayIsWhatExpected);
}

/// <summary>
/// Checks that double dot segment is not removed when it appears in the middle of two slashes.
/// </summary>
ZTEST_CASE ( RemoveDotSegments_DoubleDotSegmentIsNotRemovedWhenItAppearsFirstBetweenTwoSlashes_Test )
{
    // [Preparation]
    const string_z DOUBLE_DOT("..");

    ArrayDynamic<string_z> EXPECTED_ARRAY(3);
    EXPECTED_ARRAY.Add(string_z::GetEmpty());
    EXPECTED_ARRAY.Add(DOUBLE_DOT);
    EXPECTED_ARRAY.Add(string_z::GetEmpty());

    ArrayDynamic<string_z> inputArrayWithDots(EXPECTED_ARRAY);

    // [Execution]
    UriWhiteBox::RemoveDotSegments(inputArrayWithDots);
 
    // [Verification]
    bool bResultantArrayIsWhatExpected = true;

    ArrayDynamic<string_z>::ArrayIterator iExpected = EXPECTED_ARRAY.GetFirst();
    ArrayDynamic<string_z>::ArrayIterator iResult = inputArrayWithDots.GetFirst();

    for(; !iExpected.IsEnd(); ++iExpected, ++iResult)
        bResultantArrayIsWhatExpected = bResultantArrayIsWhatExpected && *iExpected == *iResult;
    
    BOOST_CHECK(bResultantArrayIsWhatExpected);
}

/// <summary>
/// Checks that the user information appears in the authority if it was defined.
/// </summary>
ZTEST_CASE ( GetAuthority_UserInformationAppearsIfDefined_Test )
{
    // [Preparation]
    const string_z INPUT_STRING("//userinfo@host");
    const string_z EXPECTED_STRING("userinfo@host");
    Uri uri(INPUT_STRING);

    // [Execution]
    string_z strResult = uri.GetAuthority();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_STRING);
}

/// <summary>
/// Checks that the host appears in the authority if it was defined.
/// </summary>
ZTEST_CASE ( GetAuthority_HostAppearsIfDefined_Test )
{
    // [Preparation]
    const string_z INPUT_STRING("//host:port");
    const string_z EXPECTED_STRING("host:port");
    Uri uri(INPUT_STRING);

    // [Execution]
    string_z strResult = uri.GetAuthority();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_STRING);
}

/// <summary>
/// Checks that the port appears in the authority if it was defined.
/// </summary>
ZTEST_CASE ( GetAuthority_PortAppearsIfDefined_Test )
{
    // [Preparation]
    const string_z INPUT_STRING("//host:port");
    const string_z EXPECTED_STRING("host:port");
    Uri uri(INPUT_STRING);

    // [Execution]
    string_z strResult = uri.GetAuthority();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_STRING);
}

/// <summary>
/// Checks that the authority does not include the initial separator.
/// </summary>
ZTEST_CASE ( GetAuthority_AuthorityDoesNotIncludeInitialSeparator_Test )
{
    // [Preparation]
    const string_z INPUT_STRING("//authority");
    const string_z EXPECTED_STRING("authority");
    Uri uri(INPUT_STRING);

    // [Execution]
    string_z strResult = uri.GetAuthority();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_STRING);
}

/// <summary>
/// Checks that the entire authority is correctly formed.
/// </summary>
ZTEST_CASE ( GetAuthority_TheEntireAuthorityIsCorrectlyFormed_Test )
{
    // [Preparation]
    const string_z INPUT_STRING("//userinfo@host:port");
    const string_z EXPECTED_STRING("userinfo@host:port");
    Uri uri(INPUT_STRING);

    // [Execution]
    string_z strResult = uri.GetAuthority();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_STRING);
}

/// <summary>
/// Checks that the result does not start with a slash when it is a relative path.
/// </summary>
ZTEST_CASE ( GetPath_ItDoesNotStartWithSlashWhenIsRelativePath_Test )
{
    // [Preparation]
    const string_z INPUT_STRING("path1/path/path3");
    const string_z EXPECTED_STRING("path1/path/path3");
    Uri uri(INPUT_STRING);

    // [Execution]
    string_z strResult = uri.GetPath();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_STRING);
}

/// <summary>
/// Checks that the result starts with a slash when it is an absolute path (relative reference URI).
/// </summary>
ZTEST_CASE ( GetPath_ItStartsWithSlashWhenIsAbsolutePath_Test )
{
    // [Preparation]
    const string_z INPUT_STRING("/path1/path/path3");
    const string_z EXPECTED_STRING("/path1/path/path3");
    Uri uri(INPUT_STRING);

    // [Execution]
    string_z strResult = uri.GetPath();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_STRING);
}

/// <summary>
/// Checks that the result does not include any dot segment.
/// </summary>
ZTEST_CASE ( GetPath_DotSegmentsAreRemoved_Test )
{
    // [Preparation]
    const string_z INPUT_STRING("/path1/../path/./path3");
    const string_z EXPECTED_STRING("/path/path3");
    Uri uri(INPUT_STRING);

    // [Execution]
    string_z strResult = uri.GetPath();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_STRING);
}

/// <summary>
/// Checks that the result ends with a slash when last segment is empty.
/// </summary>
ZTEST_CASE ( GetPath_EndsWithSlashWhenLastSegmentIsEmpty_Test )
{
    // [Preparation]
    const string_z INPUT_STRING("/path1/path/path3/");
    const string_z EXPECTED_STRING("/path1/path/path3/");
    Uri uri(INPUT_STRING);

    // [Execution]
    string_z strResult = uri.GetPath();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_STRING);
}

/// <summary>
/// It is not necessary to test this method since it is just a getter.
/// </summary>
ZTEST_CASE ( GetHost_NotNecessaryToTest_Test )
{
    BOOST_TEST_MESSAGE("It is not necessary to test this method since it is just a getter");
}

/// <summary>
/// It is not necessary to test this method since it is just a getter.
/// </summary>
ZTEST_CASE ( GetUserInfo_NotNecessaryToTest_Test )
{
    BOOST_TEST_MESSAGE("It is not necessary to test this method since it is just a getter");
}

/// <summary>
/// It is not necessary to test this method since it is just a getter.
/// </summary>
ZTEST_CASE ( GetQuery_NotNecessaryToTest_Test )
{
    BOOST_TEST_MESSAGE("It is not necessary to test this method since it is just a getter");
}

/// <summary>
/// It is not necessary to test this method since it is just a getter.
/// </summary>
ZTEST_CASE ( GetFragment_NotNecessaryToTest_Test )
{
    BOOST_TEST_MESSAGE("It is not necessary to test this method since it is just a getter");
}

/// <summary>
/// It is not necessary to test this method since it is just a getter.
/// </summary>
ZTEST_CASE ( GetPort_NotNecessaryToTest_Test )
{
    BOOST_TEST_MESSAGE("It is not necessary to test this method since it is just a getter");
}

/// <summary>
/// It is not necessary to test this method since it is just a getter.
/// </summary>
ZTEST_CASE ( GetScheme_NotNecessaryToTest_Test )
{
    BOOST_TEST_MESSAGE("It is not necessary to test this method since it is just a getter");
}

/// <summary>
/// Checks that it returns True when the URI has not got scheme.
/// </summary>
ZTEST_CASE ( IsRelative_ReturnsTrueWhenSchemeIsNotPresent_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = true;
    const string_z INPUT_STRING("//authority/path?query#fragment");
    Uri uri(INPUT_STRING);

    // [Execution]
    bool bResult = uri.IsRelative();
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the URI has got scheme.
/// </summary>
ZTEST_CASE ( IsRelative_ReturnsFalseWhenSchemeIsPresent_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = false;
    const string_z INPUT_STRING("scheme://authority/path?query#fragment");
    Uri uri(INPUT_STRING);

    // [Execution]
    bool bResult = uri.IsRelative();
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the value is correctly stored.
/// </summary>
ZTEST_CASE ( SetAuthority_TheValueIsCorrectlyStored_Test )
{
    // [Preparation]
    const string_z INPUT_STRING("authority");
    Uri uri("scheme://xxx/path?query#fragment");
    const string_z EXPECTED_STRING("scheme://authority/path?query#fragment");

    // [Execution]
    uri.SetAuthority(INPUT_STRING);
    
    // [Verification]
    string_z strFullUri(uri.ToString());
    BOOST_CHECK(strFullUri == EXPECTED_STRING);
}

/// <summary>
/// Checks that the value is correctly stored when the authority was not defined.
/// </summary>
ZTEST_CASE ( SetAuthority_TheValueIsCorrectlyStoredWhenAuthorityWasNotDefined_Test )
{
    // [Preparation]
    const string_z INPUT_STRING("authority");
    Uri uri("scheme:/path?query#fragment");
    const string_z EXPECTED_STRING("scheme://authority/path?query#fragment");

    // [Execution]
    uri.SetAuthority(INPUT_STRING);
    
    // [Verification]
    string_z strFullUri(uri.ToString());
    BOOST_CHECK(strFullUri == EXPECTED_STRING);
}

/// <summary>
/// Checks that the value is correctly stored when the authority was not defined and the path does not start with a slash.
/// </summary>
ZTEST_CASE ( SetAuthority_TheValueIsCorrectlyStoredWhenAuthorityWasNotDefinedAndPathDoesNotStartWithSlash_Test )
{
    // [Preparation]
    const string_z INPUT_STRING("authority");
    Uri uri("path?query#fragment");
    const string_z EXPECTED_STRING("//authority/path?query#fragment");

    // [Execution]
    uri.SetAuthority(INPUT_STRING);
    
    // [Verification]
    string_z strFullUri(uri.ToString());
    BOOST_CHECK(strFullUri == EXPECTED_STRING);
}

/// <summary>
/// Checks that the original string is emptied.
/// </summary>
ZTEST_CASE ( SetAuthority_OriginalStringIsEmptied_Test )
{
    // [Preparation]
    const string_z INPUT_STRING("authority");
    Uri uri("scheme://xxx/path?query#fragment");
    const bool ORIGINAL_STRING_IS_EMPTY = true;

    // [Execution]
    uri.SetAuthority(INPUT_STRING);
    
    // [Verification]
    bool bOriginalStringWasEmptied = uri.GetOriginalString().IsEmpty();
    BOOST_CHECK_EQUAL(bOriginalStringWasEmptied, ORIGINAL_STRING_IS_EMPTY);
}

/// <summary>
/// Checks that the authority is undefined when input string is empty.
/// </summary>
ZTEST_CASE ( SetAuthority_TheAuthorityIsUndefinedWhenInputStringIsEmpty_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = string_z::GetEmpty();
    Uri uri("scheme://authority/path?query#fragment");
    const string_z EXPECTED_STRING("scheme:/path?query#fragment");

    // [Execution]
    uri.SetAuthority(INPUT_STRING);
    
    // [Verification]
    string_z strFullUri(uri.ToString());
    BOOST_CHECK(strFullUri == EXPECTED_STRING);
}

/// <summary>
/// Checks that the value is correctly stored.
/// </summary>
ZTEST_CASE ( SetFragment_TheValueIsCorrectlyStored_Test )
{
    // [Preparation]
    const string_z INPUT_STRING("fragment");
    Uri uri("scheme://authority/path?query#fff");
    const string_z EXPECTED_STRING("scheme://authority/path?query#fragment");

    // [Execution]
    uri.SetFragment(INPUT_STRING);
    
    // [Verification]
    string_z strFullUri(uri.ToString());
    BOOST_CHECK(strFullUri == EXPECTED_STRING);
}

/// <summary>
/// Checks that the value is correctly stored when the fragment was not defined.
/// </summary>
ZTEST_CASE ( SetFragment_TheValueIsCorrectlyStoredWhenFragmentWasNotDefined_Test )
{
    // [Preparation]
    const string_z INPUT_STRING("fragment");
    Uri uri("scheme://authority/path?query");
    const string_z EXPECTED_STRING("scheme://authority/path?query#fragment");

    // [Execution]
    uri.SetFragment(INPUT_STRING);
    
    // [Verification]
    string_z strFullUri(uri.ToString());
    BOOST_CHECK(strFullUri == EXPECTED_STRING);
}

/// <summary>
/// Checks that the original string is emptied.
/// </summary>
ZTEST_CASE ( SetFragment_OriginalStringIsEmptied_Test )
{
    // [Preparation]
    const string_z INPUT_STRING("fragment");
    Uri uri("scheme://authority/path?query#fragment");
    const bool ORIGINAL_STRING_IS_EMPTY = true;

    // [Execution]
    uri.SetFragment(INPUT_STRING);
    
    // [Verification]
    bool bOriginalStringWasEmptied = uri.GetOriginalString().IsEmpty();
    BOOST_CHECK_EQUAL(bOriginalStringWasEmptied, ORIGINAL_STRING_IS_EMPTY);
}

/// <summary>
/// Checks that the fragment is undefined when input string is empty.
/// </summary>
ZTEST_CASE ( SetFragment_TheFragmentIsUndefinedWhenInputStringIsEmpty_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = string_z::GetEmpty();
    Uri uri("scheme://authority/path?query#fragment");
    const string_z EXPECTED_STRING("scheme://authority/path?query");

    // [Execution]
    uri.SetFragment(INPUT_STRING);
    
    // [Verification]
    string_z strFullUri(uri.ToString());
    BOOST_CHECK(strFullUri == EXPECTED_STRING);
}

/// <summary>
/// Checks that the value is correctly stored.
/// </summary>
ZTEST_CASE ( SetHost_TheValueIsCorrectlyStored_Test )
{
    // [Preparation]
    const string_z INPUT_STRING("host");
    Uri uri("scheme://userinfo@xxx:port/path?query#fragment");
    const string_z EXPECTED_STRING("scheme://userinfo@host:port/path?query#fragment");

    // [Execution]
    uri.SetHost(INPUT_STRING);
    
    // [Verification]
    string_z strFullUri(uri.ToString());
    BOOST_CHECK(strFullUri == EXPECTED_STRING);
}

/// <summary>
/// Checks that the value is correctly stored when the authority was not defined.
/// </summary>
ZTEST_CASE ( SetHost_TheValueIsCorrectlyStoredWhenAuthorityWasNotDefined_Test )
{
    // [Preparation]
    const string_z INPUT_STRING("host");
    Uri uri("scheme:/path?query#fragment");
    const string_z EXPECTED_STRING("scheme://host/path?query#fragment");

    // [Execution]
    uri.SetHost(INPUT_STRING);
    
    // [Verification]
    string_z strFullUri(uri.ToString());
    BOOST_CHECK(strFullUri == EXPECTED_STRING);
}

/// <summary>
/// Checks that the original string is emptied.
/// </summary>
ZTEST_CASE ( SetHost_OriginalStringIsEmptied_Test )
{
    // [Preparation]
    const string_z INPUT_STRING("host");
    Uri uri("scheme://authority/path?query#fragment");
    const bool ORIGINAL_STRING_IS_EMPTY = true;

    // [Execution]
    uri.SetHost(INPUT_STRING);
    
    // [Verification]
    bool bOriginalStringWasEmptied = uri.GetOriginalString().IsEmpty();
    BOOST_CHECK_EQUAL(bOriginalStringWasEmptied, ORIGINAL_STRING_IS_EMPTY);
}

/// <summary>
/// Checks that the authority is undefined when input string is empty.
/// </summary>
ZTEST_CASE ( SetHost_TheFullAuthorityIsUndefinedWhenInputStringIsEmpty_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = string_z::GetEmpty();
    Uri uri("scheme://userinfo@authority:port/path?query#fragment");
    const string_z EXPECTED_STRING("scheme:/path?query#fragment");

    // [Execution]
    uri.SetHost(INPUT_STRING);
    
    // [Verification]
    string_z strFullUri(uri.ToString());
    BOOST_CHECK(strFullUri == EXPECTED_STRING);
}

/// <summary>
/// Checks that the value is correctly stored when the authority was not defined and the path does not start with a slash.
/// </summary>
ZTEST_CASE ( SetHost_TheValueIsCorrectlyStoredWhenAuthorityWasNotDefinedAndPathDoesNotStartWithSlash_Test )
{
    // [Preparation]
    const string_z INPUT_STRING("host");
    Uri uri("path?query#fragment");
    const string_z EXPECTED_STRING("//host/path?query#fragment");

    // [Execution]
    uri.SetAuthority(INPUT_STRING);
    
    // [Verification]
    string_z strFullUri(uri.ToString());
    BOOST_CHECK(strFullUri == EXPECTED_STRING);
}

/// <summary>
/// Checks that the value is correctly stored.
/// </summary>
ZTEST_CASE ( SetPath_TheValueIsCorrectlyStored_Test )
{
    // [Preparation]
    const string_z INPUT_STRING("path");
    Uri uri("scheme://userinfo@host:port?query#fragment");
    const string_z EXPECTED_STRING("scheme://userinfo@host:port/path?query#fragment");

    // [Execution]
    uri.SetPath(INPUT_STRING);
    
    // [Verification]
    string_z strFullUri(uri.ToString());
    BOOST_CHECK(strFullUri == EXPECTED_STRING);
}

/// <summary>
/// Checks that the value is correctly stored when the scheme and the authority are not defined.
/// </summary>
ZTEST_CASE ( SetPath_TheValueIsCorrectlyStoredWhenAuthorityAndSchemeAreNotDefined_Test )
{
    // [Preparation]
    const string_z INPUT_STRING("path");
    Uri uri("?query#fragment");
    const string_z EXPECTED_STRING("path?query#fragment");

    // [Execution]
    uri.SetPath(INPUT_STRING);
    
    // [Verification]
    string_z strFullUri(uri.ToString());
    BOOST_CHECK(strFullUri == EXPECTED_STRING);
}

/// <summary>
/// Checks that the value is correctly stored when the scheme and the authority are not defined and the input path begins with dot segments.
/// </summary>
ZTEST_CASE ( SetPath_TheValueIsCorrectlyStoredWhenAuthorityAndSchemeAreNotDefinedAndInputPathBeginsWithDotSegments_Test )
{
    // [Preparation]
    const string_z INPUT_STRING("../path1/path2");
    Uri uri(".");
    const string_z EXPECTED_STRING("../path1/path2");

    // [Execution]
    uri.SetPath(INPUT_STRING);
    
    // [Verification]
    string_z strFullUri(uri.ToString());
    BOOST_CHECK(strFullUri == EXPECTED_STRING);
}

/// <summary>
/// Checks that the value is correctly stored when the scheme is defined and the input path begins with dot segments.
/// </summary>
ZTEST_CASE ( SetPath_TheValueIsCorrectlyStoredWhenSchemeIsDefinedAndInputPathBeginsWithDotSegments_Test )
{
    // [Preparation]
    const string_z INPUT_STRING("../path1/path2");
    Uri uri("scheme://userinfo@host:port/path1?query#fragment");
    const string_z EXPECTED_STRING("scheme://userinfo@host:port/path1/path2?query#fragment");

    // [Execution]
    uri.SetPath(INPUT_STRING);
    
    // [Verification]
    string_z strFullUri(uri.ToString());
    BOOST_CHECK(strFullUri == EXPECTED_STRING);
}

/// <summary>
/// Checks that the value is correctly stored when the scheme is not defined and the input path begins with dot segments.
/// </summary>
ZTEST_CASE ( SetPath_TheValueIsCorrectlyStoredWhenSchemeIsNotDefinedAndInputPathBeginsWithDotSegments_Test )
{
    // [Preparation]
    const string_z INPUT_STRING("../path1/path2");
    Uri uri("//userinfo@host:port/path1?query#fragment");
    const string_z EXPECTED_STRING("//userinfo@host:port/../path1/path2?query#fragment");

    // [Execution]
    uri.SetPath(INPUT_STRING);
    
    // [Verification]
    string_z strFullUri(uri.ToString());
    BOOST_CHECK(strFullUri == EXPECTED_STRING);
}

/// <summary>
/// Checks that the value is correctly stored when the scheme and the authority is defined and the input path begins with a slash.
/// </summary>
ZTEST_CASE ( SetPath_TheValueIsCorrectlyStoredWhenAuthorityIsDefinedAndInputPathBeginsWithSlash_Test )
{
    // [Preparation]
    const string_z INPUT_STRING("/path2");
    Uri uri("scheme://userinfo@host:port/path1?query#fragment");
    const string_z EXPECTED_STRING("scheme://userinfo@host:port/path2?query#fragment");

    // [Execution]
    uri.SetPath(INPUT_STRING);
    
    // [Verification]
    string_z strFullUri(uri.ToString());
    BOOST_CHECK(strFullUri == EXPECTED_STRING);
}

/// <summary>
/// Checks that a dot segment is added to the path when the scheme is not defined and the first segment of the path contains a colon.
/// </summary>
ZTEST_CASE ( SetPath_DotSegmentIsAddedToPathWhenSchemeIsNotDefinedAndFirstSegmentContainsColon_Test )
{
    // [Preparation]
    const string_z INPUT_STRING("path:/path2");
    Uri uri("path?query#fragment");
    const string_z EXPECTED_STRING("./path:/path2?query#fragment");

    // [Execution]
    uri.SetPath(INPUT_STRING);
    
    // [Verification]
    string_z strFullUri(uri.ToString());
    BOOST_CHECK(strFullUri == EXPECTED_STRING);
}

/// <summary>
/// Checks that the value is correctly stored.
/// </summary>
ZTEST_CASE ( SetQuery_TheValueIsCorrectlyStored_Test )
{
    // [Preparation]
    const string_z INPUT_STRING("query");
    Uri uri("scheme://authority/path?qqq#fragment");
    const string_z EXPECTED_STRING("scheme://authority/path?query#fragment");

    // [Execution]
    uri.SetQuery(INPUT_STRING);
    
    // [Verification]
    string_z strFullUri(uri.ToString());
    BOOST_CHECK(strFullUri == EXPECTED_STRING);
}

/// <summary>
/// Checks that the value is correctly stored when the query was not defined.
/// </summary>
ZTEST_CASE ( SetQuery_TheValueIsCorrectlyStoredWhenQueryWasNotDefined_Test )
{
    // [Preparation]
    const string_z INPUT_STRING("query");
    Uri uri("scheme://authority/path#fragment");
    const string_z EXPECTED_STRING("scheme://authority/path?query#fragment");

    // [Execution]
    uri.SetQuery(INPUT_STRING);
    
    // [Verification]
    string_z strFullUri(uri.ToString());
    BOOST_CHECK(strFullUri == EXPECTED_STRING);
}

/// <summary>
/// Checks that the original string is emptied.
/// </summary>
ZTEST_CASE ( SetQuery_OriginalStringIsEmptied_Test )
{
    // [Preparation]
    const string_z INPUT_STRING("query");
    Uri uri("scheme://authority/path?query#fragment");
    const bool ORIGINAL_STRING_IS_EMPTY = true;

    // [Execution]
    uri.SetQuery(INPUT_STRING);
    
    // [Verification]
    bool bOriginalStringWasEmptied = uri.GetOriginalString().IsEmpty();
    BOOST_CHECK_EQUAL(bOriginalStringWasEmptied, ORIGINAL_STRING_IS_EMPTY);
}

/// <summary>
/// Checks that the fragment is undefined when input string is empty.
/// </summary>
ZTEST_CASE ( SetQuery_TheQueryIsUndefinedWhenInputStringIsEmpty_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = string_z::GetEmpty();
    Uri uri("scheme://authority/path?query#fragment");
    const string_z EXPECTED_STRING("scheme://authority/path#fragment");

    // [Execution]
    uri.SetQuery(INPUT_STRING);
    
    // [Verification]
    string_z strFullUri(uri.ToString());
    BOOST_CHECK(strFullUri == EXPECTED_STRING);
}

/// <summary>
/// Checks that the value is correctly stored.
/// </summary>
ZTEST_CASE ( SetPort_TheValueIsCorrectlyStored_Test )
{
    // [Preparation]
    const string_z INPUT_STRING("port");
    Uri uri("scheme://authority:ppp/path?query#fragment");
    const string_z EXPECTED_STRING("scheme://authority:port/path?query#fragment");

    // [Execution]
    uri.SetPort(INPUT_STRING);
    
    // [Verification]
    string_z strFullUri(uri.ToString());
    BOOST_CHECK(strFullUri == EXPECTED_STRING);
}

/// <summary>
/// Checks that the value is correctly stored when the port was not defined.
/// </summary>
ZTEST_CASE ( SetPort_TheValueIsCorrectlyStoredWhenPortWasNotDefined_Test )
{
    // [Preparation]
    const string_z INPUT_STRING("port");
    Uri uri("scheme://authority/path?query#fragment");
    const string_z EXPECTED_STRING("scheme://authority:port/path?query#fragment");

    // [Execution]
    uri.SetPort(INPUT_STRING);
    
    // [Verification]
    string_z strFullUri(uri.ToString());
    BOOST_CHECK(strFullUri == EXPECTED_STRING);
}

/// <summary>
/// Checks that the original string is emptied.
/// </summary>
ZTEST_CASE ( SetPort_OriginalStringIsEmptied_Test )
{
    // [Preparation]
    const string_z INPUT_STRING("port");
    Uri uri("scheme://authority/path?query#fragment");
    const bool ORIGINAL_STRING_IS_EMPTY = true;

    // [Execution]
    uri.SetPort(INPUT_STRING);
    
    // [Verification]
    bool bOriginalStringWasEmptied = uri.GetOriginalString().IsEmpty();
    BOOST_CHECK_EQUAL(bOriginalStringWasEmptied, ORIGINAL_STRING_IS_EMPTY);
}

/// <summary>
/// Checks that the port is undefined when input string is empty.
/// </summary>
ZTEST_CASE ( SetPort_ThePortIsUndefinedWhenInputStringIsEmpty_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = string_z::GetEmpty();
    Uri uri("scheme://authority:port/path?query#fragment");
    const string_z EXPECTED_STRING("scheme://authority/path?query#fragment");

    // [Execution]
    uri.SetPort(INPUT_STRING);
    
    // [Verification]
    string_z strFullUri(uri.ToString());
    BOOST_CHECK(strFullUri == EXPECTED_STRING);
}

/// <summary>
/// Checks that the port is not set when the authority is not defined.
/// </summary>
ZTEST_CASE ( SetPort_ThePortIsNotSetWhenAuthorityIsNotDefined_Test )
{
    // [Preparation]
    const string_z INPUT_STRING("port");
    Uri uri("scheme:path?query#fragment");
    const string_z EXPECTED_STRING("scheme:path?query#fragment");

    // [Execution]
    uri.SetPort(INPUT_STRING);
    
    // [Verification]
    string_z strFullUri(uri.ToString());
    BOOST_CHECK(strFullUri == EXPECTED_STRING);
}

/// <summary>
/// Checks that the value is correctly stored.
/// </summary>
ZTEST_CASE ( SetScheme_TheValueIsCorrectlyStored_Test )
{
    // [Preparation]
    const string_z INPUT_STRING("scheme");
    Uri uri("sss://authority/path?query#fragment");
    const string_z EXPECTED_STRING("scheme://authority/path?query#fragment");

    // [Execution]
    uri.SetScheme(INPUT_STRING);
    
    // [Verification]
    string_z strFullUri(uri.ToString());
    BOOST_CHECK(strFullUri == EXPECTED_STRING);
}

/// <summary>
/// Checks that the value is correctly stored when the authority was not defined.
/// </summary>
ZTEST_CASE ( SetScheme_TheValueIsCorrectlyStoredWhenSchemeWasNotDefined_Test )
{
    // [Preparation]
    const string_z INPUT_STRING("scheme");
    Uri uri("//authority/path?query#fragment");
    const string_z EXPECTED_STRING("scheme://authority/path?query#fragment");

    // [Execution]
    uri.SetScheme(INPUT_STRING);
    
    // [Verification]
    string_z strFullUri(uri.ToString());
    BOOST_CHECK(strFullUri == EXPECTED_STRING);
}

/// <summary>
/// Checks that the value is correctly stored when the authority was not defined and the path does not start with a slash.
/// </summary>
ZTEST_CASE ( SetScheme_TheValueIsCorrectlyStoredWhenSchemeWasNotDefinedAndPathDoesNotStartWithSlash_Test )
{
    // [Preparation]
    const string_z INPUT_STRING("scheme");
    Uri uri("path?query#fragment");
    const string_z EXPECTED_STRING("scheme:path?query#fragment");

    // [Execution]
    uri.SetScheme(INPUT_STRING);
    
    // [Verification]
    string_z strFullUri(uri.ToString());
    BOOST_CHECK(strFullUri == EXPECTED_STRING);
}

/// <summary>
/// Checks that the value is correctly stored when the authority was not defined and the path starts with dot segments.
/// </summary>
ZTEST_CASE ( SetScheme_TheValueIsCorrectlyStoredWhenSchemeWasNotDefinedAndPathStartsWithDotSegments_Test )
{
    // [Preparation]
    const string_z INPUT_STRING("scheme");
    Uri uri("./../../path?query#fragment");
    const string_z EXPECTED_STRING("scheme:path?query#fragment");

    // [Execution]
    uri.SetScheme(INPUT_STRING);
    
    // [Verification]
    string_z strFullUri(uri.ToString());
    BOOST_CHECK(strFullUri == EXPECTED_STRING);
}

/// <summary>
/// Checks that the original string is emptied.
/// </summary>
ZTEST_CASE ( SetScheme_OriginalStringIsEmptied_Test )
{
    // [Preparation]
    const string_z INPUT_STRING("authority");
    Uri uri("scheme://xxx/path?query#fragment");
    const bool ORIGINAL_STRING_IS_EMPTY = true;

    // [Execution]
    uri.SetScheme(INPUT_STRING);
    
    // [Verification]
    bool bOriginalStringWasEmptied = uri.GetOriginalString().IsEmpty();
    BOOST_CHECK_EQUAL(bOriginalStringWasEmptied, ORIGINAL_STRING_IS_EMPTY);
}

/// <summary>
/// Checks that the authority is undefined when input string is empty.
/// </summary>
ZTEST_CASE ( SetScheme_TheSchemeIsUndefinedWhenInputStringIsEmpty_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = string_z::GetEmpty();
    Uri uri("scheme://authority/path?query#fragment");
    const string_z EXPECTED_STRING("//authority/path?query#fragment");

    // [Execution]
    uri.SetScheme(INPUT_STRING);
    
    // [Verification]
    string_z strFullUri(uri.ToString());
    BOOST_CHECK(strFullUri == EXPECTED_STRING);
}

/// <summary>
/// Checks that a dot segment is added to the path when the scheme is not defined and the first segment of the path contains a colon.
/// </summary>
ZTEST_CASE ( SetScheme_DotSegmentIsAddedToPathWhenSchemeIsNotDefinedAndFirstSegmentContainsColon_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = string_z::GetEmpty();
    Uri uri("scheme:path:/path2?query#fragment");
    const string_z EXPECTED_STRING("./path:/path2?query#fragment");

    // [Execution]
    uri.SetScheme(INPUT_STRING);
    
    // [Verification]
    string_z strFullUri(uri.ToString());
    BOOST_CHECK(strFullUri == EXPECTED_STRING);
}

/// <summary>
/// Checks that the value is correctly stored.
/// </summary>
ZTEST_CASE ( SetUserInfo_TheValueIsCorrectlyStored_Test )
{
    // [Preparation]
    const string_z INPUT_STRING("userinfo");
    Uri uri("scheme://uuuu@authority:port/path?query#fragment");
    const string_z EXPECTED_STRING("scheme://userinfo@authority:port/path?query#fragment");

    // [Execution]
    uri.SetUserInfo(INPUT_STRING);
    
    // [Verification]
    string_z strFullUri(uri.ToString());
    BOOST_CHECK(strFullUri == EXPECTED_STRING);
}

/// <summary>
/// Checks that the value is correctly stored when the user information was not defined.
/// </summary>
ZTEST_CASE ( SetUserInfo_TheValueIsCorrectlyStoredWhenUserInfoWasNotDefined_Test )
{
    // [Preparation]
    const string_z INPUT_STRING("userinfo");
    Uri uri("scheme://authority:port/path?query#fragment");
    const string_z EXPECTED_STRING("scheme://userinfo@authority:port/path?query#fragment");

    // [Execution]
    uri.SetUserInfo(INPUT_STRING);
    
    // [Verification]
    string_z strFullUri(uri.ToString());
    BOOST_CHECK(strFullUri == EXPECTED_STRING);
}

/// <summary>
/// Checks that the original string is emptied.
/// </summary>
ZTEST_CASE ( SetUserInfo_OriginalStringIsEmptied_Test )
{
    // [Preparation]
    const string_z INPUT_STRING("userinfo");
    Uri uri("scheme://authority:port/path?query#fragment");
    const bool ORIGINAL_STRING_IS_EMPTY = true;

    // [Execution]
    uri.SetUserInfo(INPUT_STRING);
    
    // [Verification]
    bool bOriginalStringWasEmptied = uri.GetOriginalString().IsEmpty();
    BOOST_CHECK_EQUAL(bOriginalStringWasEmptied, ORIGINAL_STRING_IS_EMPTY);
}

/// <summary>
/// Checks that the user information is undefined when input string is empty.
/// </summary>
ZTEST_CASE ( SetUserInfo_TheUserInfoIsUndefinedWhenInputStringIsEmpty_Test )
{
    // [Preparation]
    const string_z INPUT_STRING = string_z::GetEmpty();
    Uri uri("scheme://userinfo@authority:port/path?query#fragment");
    const string_z EXPECTED_STRING("scheme://authority:port/path?query#fragment");

    // [Execution]
    uri.SetUserInfo(INPUT_STRING);
    
    // [Verification]
    string_z strFullUri(uri.ToString());
    BOOST_CHECK(strFullUri == EXPECTED_STRING);
}

/// <summary>
/// Checks that the user information is not set when the authority is not defined.
/// </summary>
ZTEST_CASE ( SetUserInfo_TheUserInfoIsNotSetWhenAuthorityIsNotDefined_Test )
{
    // [Preparation]
    const string_z INPUT_STRING("userinfo");
    Uri uri("scheme:path?query#fragment");
    const string_z EXPECTED_STRING("scheme:path?query#fragment");

    // [Execution]
    uri.SetUserInfo(INPUT_STRING);
    
    // [Verification]
    string_z strFullUri(uri.ToString());
    BOOST_CHECK(strFullUri == EXPECTED_STRING);
}

// End - Test Suite: Uri
ZTEST_SUITE_END()
