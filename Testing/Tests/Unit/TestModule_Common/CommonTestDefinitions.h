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

#ifndef __COMMONTESTDEFINITIONS__
#define __COMMONTESTDEFINITIONS__

// --------------------------------------------------------------------------------------------------------
// StringUnicode::Normalization test switch: This switch enables or disables the tests of the Normalize
// method of the class StringUnicode, which takes a lot of time.
// --------------------------------------------------------------------------------------------------------
#define Z_TEST_CONFIG_STRINGUNICODE_NORMALIZE_TEST_ENABLED 0x0
#define Z_TEST_CONFIG_STRINGUNICODE_NORMALIZE_TEST_DISABLED 0x1

#define Z_TEST_CONFIG_STRINGUNICODE_NORMALIZE_TEST Z_TEST_CONFIG_STRINGUNICODE_NORMALIZE_TEST_DISABLED

// --------------------------------------------------------------------------------------------------------
// StringUnicode::CompareTo test switch: This switch enables or disables the tests of the CompareTo
// method of the class StringUnicode, which takes a lot of time.
// --------------------------------------------------------------------------------------------------------
#define Z_TEST_CONFIG_STRINGUNICODE_COMPARE_TEST_ENABLED 0x0
#define Z_TEST_CONFIG_STRINGUNICODE_COMPARE_TEST_DISABLED 0x1

#define Z_TEST_CONFIG_STRINGUNICODE_COMPARE_TEST Z_TEST_CONFIG_STRINGUNICODE_COMPARE_TEST_ENABLED

#endif // __COMMONTESTDEFINITIONS__
