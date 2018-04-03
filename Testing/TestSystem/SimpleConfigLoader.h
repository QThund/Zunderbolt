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

#ifndef __SIMPLECONFIGLOADER__
#define __SIMPLECONFIGLOADER__

#include <string>
#include <vector>

namespace z
{
namespace Test
{

/// <summary>
/// A very simple machanism to read a list of values from a plain text file. Each entry must be in a separated line.
/// Text must be compound of 8-bits characteres.
/// </summary>
class SimpleConfigLoader
{

	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
	SimpleConfigLoader();

	/// <summary>
	/// Constructor that uses a file path to initialize the loader.
	/// </summary>
	SimpleConfigLoader(const std::string &strPath);


	// DESTRUCTOR
	// ---------------
public:

	/// <summary>
	/// Destructor.
	/// </summary>		
	virtual ~SimpleConfigLoader();


	// METHODS
	// ---------------
public:

    /// <summary>
    /// Retrieves an entry by its position.
    /// </summary>
    /// <param name="index">The entry position in the file.</param>
    /// <returns>
    /// The entry value.
    /// </returns>
    const std::string& operator[](const int &index) const;

    /// <summary>
    /// Uses the stored file path to find the text file to read entries from.
    /// Entries are stored in order of appearance.
    /// </summary>
    /// <returns>
    /// If there was no errors during entries loading, the it returns true.
    /// </returns>
    bool LoadEntries();


	// PROPERTIES
	// ---------------
public:

    /// <summary>
    /// Gets the text file path.
    /// </summary>
    /// <returns>
    /// The file path.
    /// </returns>
    std::string GetFilePath() const;

    /// <summary>
    /// Gets the text file path.
    /// </summary>
    /// <param name="strPath">The file path. It can be absolute or relative path.</param>
    void SetFilePath(const std::string &strPath);


	// ATTRIBUTES
	// ---------------
protected:

    /// <summary>
    /// The text file path.
    /// </summary>
    std::string _strPath;

    /// <summary>
    /// The entry list, in order of appearance.
    /// </summary>
    std::vector<std::string> _arConfigEntries;

};

} // namespace Test
} // namespace z

#endif // __ZTESTCONFIGLOADER__
