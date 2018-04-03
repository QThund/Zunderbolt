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

#ifndef __BINARYSTREAMREADER__
#define __BINARYSTREAMREADER__

#include "ZIO/IOModuleDefinitions.h"

#include "ZCommon/DataTypes/StringsDefinitions.h"
#include "ZCommon/Assertions.h"

namespace z
{

/// <summary>
/// Component that parses a stream and interprets its bytes as known type instances.
/// </summary>
/// <typeparam name="StreamT">The type of the stream to be read (memory stream, file stream, etc.).</typeparam>
template<class StreamT>
class BinaryStreamReader
{
    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Constructor that receives a stream and stores a reference to it.
    /// </summary>
    /// <param name="stream">[IN] The stream to be read.</param>
    BinaryStreamReader(StreamT &stream) : m_stream(stream)
    {
    }

private:

    // Not allowed
    BinaryStreamReader(const BinaryStreamReader &);


    // METHODS
    // ---------------
private:

    // Not allowed
    BinaryStreamReader operator=(const BinaryStreamReader &);

public:

    /// <summary>
    /// Bitwise operator that reads enough bytes from the stream to fill an instance of a given type.
    /// </summary>
    /// <remarks>
    /// Note that the read pointer of the stream is not restored after this operation.<br/>
    /// No instance's constructors nor operators are called.
    /// </remarks>
    /// <typeparam name="T">The data type as which to interpret the read bytes.</typeparam>
    /// <param name="value">[OUT] The instance to be filled with stream's bytes.</param>
    /// <returns>
    /// A reference to the resident binary stream reader.
    /// </returns>
    template<class T>
    BinaryStreamReader& operator>>(T &value)
    {
        m_stream.Read(&value, 0, sizeof(T));
        return *this;
    }
    
    /// <summary>
    /// Reads a concrete amount of bytes and fills an output buffer.
    /// </summary>
    /// <remarks>
    /// Note that the read pointer of the stream is not restored after this operation.
    /// </remarks>
    /// <param name="pBuffer">[OUT] The buffer to be filled with the read bytes. It must not be null.</param>
    /// <param name="uSize">[IN] The size of the buffer, in bytes. The same number of bytes will be read. It must be greater than zero.</param>
    void ReadBytes(void* pBuffer, const puint_z uSize)
    {
        Z_ASSERT_ERROR(pBuffer != null_z, "The input buffer cannot be null.");
        Z_ASSERT_ERROR(uSize > 0, "The size of the input buffer cannot equal zero.");

        m_stream.Read(pBuffer, 0, uSize);
    }
    
    /// <summary>
    /// Reads enough bytes from the stream to fill an instance of a given type and returns it.
    /// </summary>
    /// <remarks>
    /// Note that the read pointer of the stream is not restored after this operation.<br/>
    /// The default constructor, the copy constructor and the destructor of the returned instance will be called.<br/>
    /// This method does almost the same as the bitwise operator (">>") but in a slower manner due to the construction and the return-copy 
    /// of the instance. It's provided with the only purpose of improving readability and/or usability in certain scenarios.
    /// </remarks>
    /// <typeparam name="T">The data type as which to interpret the read bytes.</typeparam>
    /// <returns>
    /// The instance constructed from the read bytes.
    /// </returns>
    template<class T>
    T Read()
    {
        T instance;
        m_stream.Read(&instance, 0, sizeof(T));

        return instance;
    }


    // PROPERTIES
    // ---------------
public:
    
    /// <summary>
    /// Gets the stream being read.
    /// </summary>
    /// <returns>
    /// A reference to the stream being read.
    /// </returns>
    StreamT& GetStream() const
    {
        return m_stream;
    }


    // ATTRIBUTES
    // ---------------
protected:
    
    /// <summary>
    /// The stream being read.
    /// </summary>
    StreamT& m_stream;

};

} // namespace z

#endif // __BINARYSTREAMREADER__
