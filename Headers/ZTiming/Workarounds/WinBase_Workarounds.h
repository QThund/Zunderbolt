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

// ABOUT THIS FILE: This file was created only to apply workarounds to solve some issues related to the WinBase.h file that
//                  comes with MinGW (Windows import libraries).

#ifndef __WINBASE_WORKAROUNDS__
#define __WINBASE_WORKAROUNDS__

// Workaround #1: The structure DYNAMIC_TIME_ZONE_INFORMATION and the function GetDynamicTimeZoneInformation do not appear in
//                the original file although they are used and defined in the import library (libkernel32.a). We have added them
//                here to be used when compiling with MinGW.

extern "C" 
{
    typedef struct _TIME_DYNAMIC_ZONE_INFORMATION 
    {
        LONG Bias;
        WCHAR StandardName[32];
        SYSTEMTIME StandardDate;
        LONG StandardBias;
        WCHAR DaylightName[32];
        SYSTEMTIME DaylightDate;
        LONG DaylightBias;
        WCHAR TimeZoneKeyName[128];
        BOOLEAN DynamicDaylightTimeDisabled;
    } DYNAMIC_TIME_ZONE_INFORMATION,*PDYNAMIC_TIME_ZONE_INFORMATION;

    WINBASEAPI DWORD WINAPI GetDynamicTimeZoneInformation (PDYNAMIC_TIME_ZONE_INFORMATION pTimeZoneInformation);
}

#endif // __WINBASE_WORKAROUNDS__
