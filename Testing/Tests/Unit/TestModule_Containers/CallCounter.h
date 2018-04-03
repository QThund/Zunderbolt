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

#ifndef __CALLCOUNTER__
#define __CALLCOUNTER__

#include "ZCommon/DataTypes/CrossPlatformBasicTypes.h"

namespace z
{
namespace Test
{

/// <summary>
/// Counts the number of calls to 4 methods: default constructor, copy constructor, destructor and assignment operator.
/// It should be Reset before it is used to assure a clean test scenario.
/// </summary>
class CallCounter
{
	// CONSTRUCTORS
	// ---------------

public:

    /// <summary>
    /// Default constructor. Increases the constructor call count.
    /// </summary>
    CallCounter()
    {
        CallCounter::sm_uConstructorCalls++;
    }

    /// <summary>
    /// Copy constructor. Increases the copy constructor call count.
    /// </summary>
    /// <param name="">Another instance. Not used.</param>
    CallCounter(const CallCounter&)
    {
        CallCounter::sm_uCopyConstructorCalls++;
    }
	
	// DESTRUCTOR
	// ---------------

public:

    /// <summary>
    /// Destructor. Increases the destructor call count.
    /// </summary>
    ~CallCounter()
    {
        CallCounter::sm_uDestructorCalls++;
    }


	// METHODS
	// ---------------

public:
    
    /// <summary>
    /// Assignment operator. Increments assignment call count.
    /// </summary>
    /// <param name="">Another instance. Not used.</param>
    CallCounter& operator=(const CallCounter&)
    {
        CallCounter::sm_uAssignmentCalls++;
        return *this;
    }

    /// <summary>
    /// Sets all counters to zero.
    /// </summary>
    static void ResetCounters()
    {
        CallCounter::sm_uConstructorCalls = 0;
        CallCounter::sm_uDestructorCalls = 0;
        CallCounter::sm_uCopyConstructorCalls = 0;
        CallCounter::sm_uAssignmentCalls = 0;
    }
    
    /// <summary>
    /// Greater than operator. Included to be able to use this type inside containers with QComparatorDefault.
    /// </summary>
    /// <param name="instance">Another instance.</param>
    /// <returns>
    /// A boolean value with no meaning.
    /// </returns>
    bool operator<(const CallCounter &instance) const
    {
        return this < &instance;
    }
    
    /// <summary>
    /// Equality operator. Included to be able to use this type inside containers with QComparatorDefault.
    /// </summary>
    /// <param name="instance">Another instance. Not used.</param>
    /// <returns>
    /// A boolean value with no meaning.
    /// </returns>
    bool operator==(const CallCounter &instance) const
    {
        return this == &instance;
    }
        
    /// <summary>
    /// Modulo operator. Included to be able to use this type inside containers with SIntegerHashProvider.
    /// </summary>
    /// <param name="uValue">An integer.</param>
    /// <returns>
    /// A resultant integer.
    /// </returns>
    puint_z operator%(const puint_z uValue) const
    {
        return (puint_z)this % uValue;
    }


    // PROPERTIES
	// ---------------

public:

    /// <summary>
    /// Gets the constructor call count.
    /// </summary>
    /// <returns>
    /// The number of times the constructor has been called.
    /// </returns>
    static unsigned int GetConstructorCallsCount()
    {
        return CallCounter::sm_uConstructorCalls;
    }
    
    /// <summary>
    /// Gets the copy constructor call count.
    /// </summary>
    /// <returns>
    /// The number of times the copy constructor has been called.
    /// </returns>
    static unsigned int GetCopyConstructorCallsCount()
    {
        return CallCounter::sm_uCopyConstructorCalls;
    }
    
    /// <summary>
    /// Gets the destructor call count.
    /// </summary>
    /// <returns>
    /// The number of times the destructor has been called.
    /// </returns>
    static unsigned int GetDestructorCallsCount()
    {
        return CallCounter::sm_uDestructorCalls;
    }
    
    /// <summary>
    /// Gets the assignment call count.
    /// </summary>
    /// <returns>
    /// The number of times the assignment operator has been called.
    /// </returns>
    static unsigned int GetAssignmentCallsCount()
    {
        return CallCounter::sm_uAssignmentCalls;
    }
    
    // ATTRIBUTES
	// ---------------

private:

    /// <returns>
    /// The number of times the constructor has been called.
    /// </returns>
    static unsigned int sm_uConstructorCalls;

    /// <returns>
    /// The number of times the copy constructor has been called.
    /// </returns>
    static unsigned int sm_uCopyConstructorCalls;

    /// <returns>
    /// The number of times the destructor has been called.
    /// </returns>
    static unsigned int sm_uDestructorCalls;

    /// <returns>
    /// The number of times the assignment operator has been called.
    /// </returns>
    static unsigned int sm_uAssignmentCalls;

};


} // namespace Test
} // namespace z

#endif // __CALLCOUNTER__
