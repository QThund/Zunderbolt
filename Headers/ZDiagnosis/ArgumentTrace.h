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

#ifndef __ARGUMENTTRACE__
#define __ARGUMENTTRACE__

#include "ZDiagnosis/DiagnosisModuleDefinitions.h"

#include "ZCommon/DataTypes/StringsDefinitions.h"
#include "ZCommon/DataTypes/SAnyTypeToStringConverter.h"
#include "ZCommon/DataTypes/SInteger.h"
#include "ZCommon/DataTypes/Type.h"
#include "ZDiagnosis/TypeWithGetType.h"
#include "ZDiagnosis/TypeWithToString.h"



namespace z
{

/// <summary>
/// Small component used to trace all the information about a function argument.
/// </summary>
class Z_LAYER_DIAGNOSIS_SYMBOLS ArgumentTrace
{
    // CONSTANTS
    // ---------------

    /// <summary>
    /// The const keyword, used in type names.
    /// </summary>
    static const string_z CONSTANT;

    /// <summary>
    /// An asterisk used in pointer type names.
    /// </summary>
    static const string_z ASTERISK;


    // CONSTRUCTORS
    // ---------------
public:
    
    /// <summary>
    /// Constructor that receives a function argument.
    /// </summary>
    /// <remarks>
    /// The type of the argument is retrieved as well as its value, both stored as text strings.<br/>
    /// Pointers-to-constant and pointers-to-non-constant are considered as different types and therefore have different names.<br/>
    /// If the type of the argument is not a basic type (void, u8_z, u16_z, u32_z, u64_z, i8_z, i16_z, i32_z, i64_z, f32_z, f64_z or bool), a string_z nor a pointer
    /// to any of the previous types then a special format will be used:<br/>
    /// - Type name: "<Unknown type (size: #)>" (where "#" means a number of bytes).<br/>
    /// - Value: "0x######## <Unknown type at 0x########>" (where "#" means a hexadecimal number to indicate the memory address of the instance).<br/>
    /// For every pointer dereferencing, a memory address will be added before the value of the instance.<br/>
    /// <br/>
    /// Examples (Code / Type name / "Value"):<br/>
    /// - i32_z i = 3 / i32 / "3"<br/>
    /// - i32_z* pInt = &i / i32* / "0x######## 3"<br/>
    /// - const i32_z ci = 3 / i32 / "3"<br/>
    /// - const i32_z* pInt = &ci / const i32* / "0x######## 3"<br/>
    /// - const i32_z** ppInt = &pInt / const i32** / "0x######## 0x######## 3"<br/>
    /// - string_z strInt = "text" / string / "text"<br/>
    /// - MyCustomType t / "<Unknown type (size: #)>" / "<Unknown type at 0x########>"<br/>
    /// - i32_z* pNull = null_z / i32* / "<Null>"
    /// </remarks>
    /// <typeparam name="T">The type of the argument. It can be whichever.</typeparam>
    /// <param name="argument">[IN] The argument to be traced.</param>
    template<class T>
    ArgumentTrace(const T &argument) : m_pType(Type::FindType(argument)),
                                        m_strTypeName(string_z::GetEmpty()),
                                        m_strValue(SAnyTypeToStringConverter::Convert(argument))
    {
        this->_FillTypeName(argument);
    }
    
    /// <summary>
    /// Constructor that receives a function argument and a constructor selection object. This constructor assumes that the type of the argument
    /// provides a non-static method called GetType, which returns a pointer to a Type instance and receives no parameters.
    /// </summary>
    /// <remarks>
    /// The type of the argument is retrieved as well as its value, both stored as text strings.<br/>
    /// Pointers-to-constant and pointers-to-non-constant are considered as different types and therefore have different names.<br/>
    /// The value of the argument will not be parsed and the following format will be used:<br/>
    /// "0x######## <Unknown type at 0x########>" (where "#" means a hexadecimal number to indicate the memory address of the instance).<br/>
    /// For every pointer dereferencing, a memory address will be added before the value of the instance.<br/>
    /// <br/>
    /// Examples (Code / Type name / "Value"):<br/>
    /// - type i = type() / type / "<Unknown type at 0x########>"<br/>
    /// - type* pI = new type() / type* / "0x######## <Unknown type at 0x########>"<br/>
    /// - const type** ppI = &pI / const type** / "0x######## 0x######## <Unknown type at 0x########>"<br/>
    /// - type* pNull = null_z / type* / "<Null>"
    /// </remarks>
    /// <typeparam name="T">The type of the argument, which provides GetTypeObject non-static method and GetTypeClass static method method. 
    /// It can be whichever.</typeparam>
    /// <param name="argument">[IN] The argument to be traced.</param>
    template<class T>
    ArgumentTrace(const T &argument, const TypeWithGetType) : 
                                        m_pType(argument.GetTypeObject()),
                                        m_strTypeName(argument.GetTypeObject()->GetName()),
                                        m_strValue(SAnyTypeToStringConverter::Convert(argument))
    {
    }

    /// <summary>
    /// Constructor that receives a function argument and a constructor selection object. This constructor assumes that the type of the argument
    /// provides a non-static method called ToString, which returns a string and receives no parameters.
    /// </summary>
    /// <remarks>
    /// The type of the argument is retrieved as well as its value, both stored as text strings.<br/>
    /// Pointers-to-constant and pointers-to-non-constant are considered as different types and therefore have different names.<br/>
    /// The type of the argument will not be found and the following format will be used:<br/>
    /// "<Unknown type (size: #)>" (where "#" means a hexadecimal number to indicate the memory address of the instance).<br/>
    /// For every pointer dereferencing, a memory address will be added before the value of the instance.<br/>
    /// <br/>
    /// Examples (Code / Type name / "Value"):<br/>
    /// - type i = type() / <Unknown type (size: #)> / "type string"<br/>
    /// - type* pI = new type() / <Unknown type (size: #)>* / "0x######## type string"<br/>
    /// - const type** ppI = &pI / const <Unknown type (size: #)>** / "0x######## 0x######## type string"<br/>
    /// - type* pNull = null_z / <Unknown type (size: #)>* / "<Null>"
    /// </remarks>
    /// <typeparam name="T">The type of the argument, which provides ToString method. It can be whichever.</typeparam>
    /// <param name="argument">[IN] The argument to be traced.</param>
    template<class T>
    ArgumentTrace(const T &argument, const TypeWithToString) : 
                                        m_pType(Type::FindType(argument)),
                                        m_strTypeName(string_z::GetEmpty()),
                                        m_strValue(argument.ToString())
    {
        this->_FillTypeName(argument);
    }

    /// <summary>
    /// Constructor that receives a function argument and two constructor selection objects. This constructor assumes that the type of the argument
    /// provides a non-static method called ToString, which returns a string and receives no parameters, and non-static method called GetType, which 
    /// returns a pointer to a Type instance and receives no parameters.
    /// </summary>
    /// <remarks>
    /// The type of the argument is retrieved as well as its value, both stored as text strings.<br/>
    /// Pointers-to-constant and pointers-to-non-constant are considered as different types and therefore have different names.<br/>
    /// For every pointer dereferencing, a memory address will be added before the value of the instance.<br/>
    /// <br/>
    /// Examples (Code / Type name / "Value"):<br/>
    /// - type i = type() / type / "type string"<br/>
    /// - type* pI = new type() / type* / "0x######## type string"<br/>
    /// - const type** ppI = &pI / const type** / "0x######## 0x######## type string"<br/>
    /// - type* pNull = null_z / type* / "<Null>"
    /// </remarks>
    /// <typeparam name="T">The type of the argument, which provides GetTypeObject non-static method, GetTypeClass static method and ToString methods. 
    /// It can be whichever.</typeparam>
    /// <param name="argument">[IN] The argument to be traced.</param>
    template<class T>
    ArgumentTrace(const T &argument, const TypeWithGetType, const TypeWithToString) : 
                                        m_pType(argument.GetTypeObject()),
                                        m_strTypeName(argument.GetTypeObject()->GetName()),
                                        m_strValue(argument.ToString())
    {
    }
     
    /// <summary>
    /// Constructor that receives a function argument.
    /// </summary>
    /// <remarks>
    /// The type of the argument is retrieved as well as its value, both stored as text strings.<br/>
    /// Pointers-to-constant and pointers-to-non-constant are considered as different types and therefore have different names.<br/>
    /// If the type of the argument is not a basic type (void, u8_z, u16_z, u32_z, u64_z, i8_z, i16_z, i32_z, i64_z, f32_z, f64_z or bool), a string_z nor a pointer
    /// to any of the previous types then a special format will be used:<br/>
    /// - Type name: "<Unknown type (size: #)>" (where "#" means a number of bytes).<br/>
    /// - Value: "0x######## <Unknown type at 0x########>" (where "#" means a hexadecimal number to indicate the memory address of the instance).<br/>
    /// For every pointer dereferencing, a memory address will be added before the value of the instance.<br/>
    /// <br/>
    /// Examples (Code / Type name / "Value"):<br/>
    /// - i32_z i = 3 / i32 / "3"<br/>
    /// - i32_z* pInt = &i / i32* / "0x######## 3"<br/>
    /// - const i32_z ci = 3 / i32 / "3"<br/>
    /// - const i32_z* pInt = &ci / const i32* / "0x######## 3"<br/>
    /// - const i32_z** ppInt = &pInt / const i32** / "0x######## 0x######## 3"<br/>
    /// - string_z strInt = "text" / string / "text"<br/>
    /// - MyCustomType t / "<Unknown type (size: #)>" / "<Unknown type at 0x########>"<br/>
    /// - i32_z* pNull = null_z / i32* / "<Null>"
    /// </remarks>
    /// <typeparam name="T">The type of the argument. It can be whichever.</typeparam>
    /// <param name="pArgument">[IN] The argument to be traced.</param>
    template<class T>
    ArgumentTrace(T* pArgument) : m_pType(Type::FindType(pArgument)),
                                   m_strTypeName(string_z::GetEmpty()),
                                   m_strValue(SAnyTypeToStringConverter::Convert(pArgument))
    {
        this->_FillTypeName(pArgument);
    }
    
    /// <summary>
    /// Constructor that receives a function argument and a constructor selection object. This constructor assumes that the type of the argument
    /// provides a non-static method called GetType, which returns a pointer to a Type instance and receives no parameters.
    /// </summary>
    /// <remarks>
    /// The type of the argument is retrieved as well as its value, both stored as text strings.<br/>
    /// Pointers-to-constant and pointers-to-non-constant are considered as different types and therefore have different names.<br/>
    /// The value of the argument will not be parsed and the following format will be used:<br/>
    /// "0x######## <Unknown type at 0x########>" (where "#" means a hexadecimal number to indicate the memory address of the instance).<br/>
    /// For every pointer dereferencing, a memory address will be added before the value of the instance.<br/>
    /// If the pointer is null, the resolved type will be the type of the pointer and its value will be "<Null>".<br/>
    /// <br/>
    /// Examples (Code / Type name / "Value"):<br/>
    /// - type i = type() / type / "<Unknown type at 0x########>"<br/>
    /// - type* pI = new type() / type* / "0x######## <Unknown type at 0x########>"<br/>
    /// - const type** ppI = &pI / const type** / "0x######## 0x######## <Unknown type at 0x########>"<br/>
    /// - type* pNull = null_z / type* / "<Null>"
    /// </remarks>
    /// <typeparam name="T">The type of the argument, which provides GetTypeObject non-static method and GetTypeClass static method. 
    /// It can be whichever.</typeparam>
    /// <param name="pArgument">[IN] The argument to be traced.</param>
    template<class T>
    ArgumentTrace(T* pArgument, const TypeWithGetType) : 
                                        m_pType(null_z),
                                        m_strTypeName(string_z::GetEmpty()),
                                        m_strValue(SAnyTypeToStringConverter::Convert(pArgument))
    {
        m_pType = pArgument == null_z ? T::GetTypeClass() :
                                        pArgument->GetTypeObject();
        this->_FillTypeName(pArgument);
    }
    
    /// <summary>
    /// Constructor that receives a function argument and a constructor selection object. This constructor assumes that the type of the argument
    /// provides a non-static method called ToString, which returns a string and receives no parameters.
    /// </summary>
    /// <remarks>
    /// The type of the argument is retrieved as well as its value, both stored as text strings.<br/>
    /// Pointers-to-constant and pointers-to-non-constant are considered as different types and therefore have different names.<br/>
    /// The type of the argument will not be found and the following format will be used:<br/>
    /// "<Unknown type (size: #)>" (where "#" means a hexadecimal number to indicate the memory address of the instance).<br/>
    /// For every pointer dereferencing, a memory address will be added before the value of the instance.<br/>
    /// <br/>
    /// Examples (Code / Type name / "Value"):<br/>
    /// - type i = type() / <Unknown type (size: #)> / "type string"<br/>
    /// - type* pI = new type() / <Unknown type (size: #)>* / "0x######## type string"<br/>
    /// - const type** ppI = &pI / const <Unknown type (size: #)>** / "0x######## 0x######## type string"<br/>
    /// - type* pNull = null_z / <Unknown type (size: #)>* / "<Null>"
    /// </remarks>
    /// <typeparam name="T">The type of the argument, which provides ToString method. It can be whichever.</typeparam>
    /// <param name="pArgument">[IN] The argument to be traced.</param>
    template<class T>
    ArgumentTrace(T* pArgument, const TypeWithToString) : 
                                        m_pType(Type::FindType(pArgument)),
                                        m_strTypeName(string_z::GetEmpty()),
                                        m_strValue(ArgumentTrace::_ConvertToString(pArgument))
    {
        this->_FillTypeName(pArgument);
    }

    /// <summary>
    /// Constructor that receives a function argument and two constructor selection objects. This constructor assumes that the type of the argument
    /// provides a non-static method called ToString, which returns a string and receives no parameters, and non-static method called GetType, which 
    /// returns a pointer to a Type instance and receives no parameters.
    /// </summary>
    /// <remarks>
    /// The type of the argument is retrieved as well as its value, both stored as text strings.<br/>
    /// Pointers-to-constant and pointers-to-non-constant are considered as different types and therefore have different names.<br/>
    /// For every pointer dereferencing, a memory address will be added before the value of the instance.<br/>
    /// If the pointer is null, the resolved type will be the type of the pointer and its value will be "<Null>".<br/>
    /// <br/>
    /// Examples (Code / Type name / "Value"):<br/>
    /// - type i = type() / type / "type string"<br/>
    /// - type* pI = new type() / type* / "0x######## type string"<br/>
    /// - const type** ppI = &pI / const type** / "0x######## 0x######## type string"<br/>
    /// - type* pNull = null_z / type* / "<Null>"
    /// </remarks>
    /// <typeparam name="T">The type of the argument, which provides GetTypeObject non-static method, GetTypeClass static method and ToString methods. 
    /// It can be whichever.</typeparam>
    /// <param name="pArgument">[IN] The argument to be traced.</param>
    template<class T>
    ArgumentTrace(T* pArgument, const TypeWithGetType, const TypeWithToString) : 
                                        m_pType(null_z),
                                        m_strTypeName(string_z::GetEmpty()),
                                        m_strValue(ArgumentTrace::_ConvertToString(pArgument))
    {
        m_pType = pArgument == null_z ? T::GetTypeClass() :
                                        pArgument->GetTypeObject();
        this->_FillTypeName(pArgument);
    }
     
    /// <summary>
    /// Constructor that receives a function argument.
    /// </summary>
    /// <remarks>
    /// The type of the argument is retrieved as well as its value, both stored as text strings.<br/>
    /// Pointers-to-constant and pointers-to-non-constant are considered as different types and therefore have different names.<br/>
    /// If the type of the argument is not a basic type (void, u8_z, u16_z, u32_z, u64_z, i8_z, i16_z, i32_z, i64_z, f32_z, f64_z or bool), a string_z nor a pointer
    /// to any of the previous types then a special format will be used:<br/>
    /// - Type name: "<Unknown type (size: #)>" (where "#" means a number of bytes).<br/>
    /// - Value: "0x######## <Unknown type at 0x########>" (where "#" means a hexadecimal number to indicate the memory address of the instance).<br/>
    /// For every pointer dereferencing, a memory address will be added before the value of the instance.<br/>
    /// <br/>
    /// Examples (Code / Type name / "Value"):<br/>
    /// - i32_z i = 3 / i32 / "3"<br/>
    /// - i32_z* pInt = &i / i32* / "0x######## 3"<br/>
    /// - const i32_z ci = 3 / i32 / "3"<br/>
    /// - const i32_z* pInt = &ci / const i32* / "0x######## 3"<br/>
    /// - const i32_z** ppInt = &pInt / const i32** / "0x######## 0x######## 3"<br/>
    /// - string_z strInt = "text" / string / "text"<br/>
    /// - MyCustomType t / "<Unknown type (size: #)>" / "<Unknown type at 0x########>"<br/>
    /// - i32_z* pNull = null_z / i32* / "<Null>"
    /// </remarks>
    /// <typeparam name="T">The type of the argument. It can be whichever.</typeparam>
    /// <param name="pArgument">[IN] The argument to be traced.</param>
    template<class T>
    ArgumentTrace(const T* pArgument) : m_pType(Type::FindType(pArgument)),
                                         m_strTypeName(string_z::GetEmpty()),
                                         m_strValue(SAnyTypeToStringConverter::Convert(pArgument))
    {
        this->_FillTypeName(pArgument);
    }
    
    /// <summary>
    /// Constructor that receives a function argument and a constructor selection object. This constructor assumes that the type of the argument
    /// provides a non-static method called GetType, which returns a pointer to a Type instance and receives no parameters.
    /// </summary>
    /// <remarks>
    /// The type of the argument is retrieved as well as its value, both stored as text strings.<br/>
    /// Pointers-to-constant and pointers-to-non-constant are considered as different types and therefore have different names.<br/>
    /// The value of the argument will not be parsed and the following format will be used:<br/>
    /// "0x######## <Unknown type at 0x########>" (where "#" means a hexadecimal number to indicate the memory address of the instance).<br/>
    /// For every pointer dereferencing, a memory address will be added before the value of the instance.<br/>
    /// If the pointer is null, the resolved type will be the type of the pointer and its value will be "<Null>".<br/>
    /// <br/>
    /// Examples (Code / Type name / "Value"):<br/>
    /// - type i = type() / type / "<Unknown type at 0x########>"<br/>
    /// - type* pI = new type() / type* / "0x######## <Unknown type at 0x########>"<br/>
    /// - const type** ppI = &pI / const type** / "0x######## 0x######## <Unknown type at 0x########>"<br/>
    /// - type* pNull = null_z / type* / "<Null>"
    /// </remarks>
    /// <typeparam name="T">The type of the argument, which provides GetTypeObject non-static method and GetTypeClass static method. It can be whichever.</typeparam>
    /// <param name="pArgument">[IN] The argument to be traced.</param>
    template<class T>
    ArgumentTrace(const T* pArgument, const TypeWithGetType) : 
                                        m_pType(null_z),
                                        m_strTypeName(string_z::GetEmpty()),
                                        m_strValue(SAnyTypeToStringConverter::Convert(pArgument))
    {
        m_pType = pArgument == null_z ? T::GetTypeClass() :
                                        pArgument->GetTypeObject();
        this->_FillTypeName(pArgument);
    }

    /// <summary>
    /// Constructor that receives a function argument and a constructor selection object. This constructor assumes that the type of the argument
    /// provides a non-static method called ToString, which returns a string and receives no parameters.
    /// </summary>
    /// <remarks>
    /// The type of the argument is retrieved as well as its value, both stored as text strings.<br/>
    /// Pointers-to-constant and pointers-to-non-constant are considered as different types and therefore have different names.<br/>
    /// The type of the argument will not be found and the following format will be used:<br/>
    /// "<Unknown type (size: #)>" (where "#" means a hexadecimal number to indicate the memory address of the instance).<br/>
    /// For every pointer dereferencing, a memory address will be added before the value of the instance.<br/>
    /// <br/>
    /// Examples (Code / Type name / "Value"):<br/>
    /// - type i = type() / <Unknown type (size: #)> / "type string"<br/>
    /// - type* pI = new type() / <Unknown type (size: #)>* / "0x######## type string"<br/>
    /// - const type** ppI = &pI / const <Unknown type (size: #)>** / "0x######## 0x######## type string"<br/>
    /// - type* pNull = null_z / <Unknown type (size: #)>* / "<Null>"
    /// </remarks>
    /// <typeparam name="T">The type of the argument, which provides ToString method. It can be whichever.</typeparam>
    /// <param name="pArgument">[IN] The argument to be traced.</param>
    template<class T>
    ArgumentTrace(const T* pArgument, const TypeWithToString) : 
                                        m_pType(Type::FindType(pArgument)),
                                        m_strTypeName(string_z::GetEmpty()),
                                        m_strValue(ArgumentTrace::_ConvertToString(pArgument))
    {
        this->_FillTypeName(pArgument);
    }

    /// <summary>
    /// Constructor that receives a function argument and two constructor selection objects. This constructor assumes that the type of the argument
    /// provides a non-static method called ToString, which returns a string and receives no parameters, and non-static method called GetType, which 
    /// returns a pointer to a Type instance and receives no parameters.
    /// </summary>
    /// <remarks>
    /// The type of the argument is retrieved as well as its value, both stored as text strings.<br/>
    /// Pointers-to-constant and pointers-to-non-constant are considered as different types and therefore have different names.<br/>
    /// For every pointer dereferencing, a memory address will be added before the value of the instance.<br/>
    /// If the pointer is null, the resolved type will be the type of the pointer and its value will be "<Null>".<br/>
    /// <br/>
    /// Examples (Code / Type name / "Value"):<br/>
    /// - type i = type() / type / "type string"<br/>
    /// - type* pI = new type() / type* / "0x######## type string"<br/>
    /// - const type** ppI = &pI / const type** / "0x######## 0x######## type string"<br/>
    /// - type* pNull = null_z / type* / "<Null>"
    /// </remarks>
    /// <typeparam name="T">The type of the argument, which provides GetTypeObject non-static method, GetTypeClass static method and ToString non-static 
    /// method. It can be whichever.</typeparam>
    /// <param name="pArgument">[IN] The argument to be traced.</param>
    template<class T>
    ArgumentTrace(const T* pArgument, const TypeWithGetType, const TypeWithToString) : 
                                        m_pType(null_z),
                                        m_strTypeName(string_z::GetEmpty()),
                                        m_strValue(ArgumentTrace::_ConvertToString(pArgument))
    {
        m_pType = pArgument == null_z ? T::GetTypeClass() :
                                        pArgument->GetTypeObject();
        this->_FillTypeName(pArgument);
    }


    // METHODS
    // ---------------
private:
    
    /// <summary>
    /// Fills the type name of the argument.
    /// </summary>
    /// <typeparam name="T">The type of the argument. It can be whichever.</typeparam>
    template<class T>
    void _FillTypeName(const T&)
    {
        static const string_z UNKNOWN_TYPE_PART1("<Unknown type (size: ");
        static const string_z UNKNOWN_TYPE_PART2(")>");

        if(m_pType)
        {
            m_strTypeName.Append(m_pType->GetName());
        }
        else
        {
            m_strTypeName.Append(UNKNOWN_TYPE_PART1);
            m_strTypeName.Append(string_z::FromInteger(sizeof(T)));
            m_strTypeName.Append(UNKNOWN_TYPE_PART2);
        }
    }
    
    /// <summary>
    /// Fills the type name of the argument.
    /// </summary>
    /// <typeparam name="T">The type of the argument. It can be whichever.</typeparam>
    /// <param name="pArgument">[IN] The argument to be traced.</param>
    template<class T>
    void _FillTypeName(T* pArgument)
    {
        this->_FillTypeName(*pArgument);
        m_strTypeName.Append(ArgumentTrace::ASTERISK);
    }
    
    /// <summary>
    /// Fills the type name of the argument.
    /// </summary>
    /// <typeparam name="T">The type of the argument. It can be whichever.</typeparam>
    /// <param name="pArgument">[IN] The argument to be traced.</param>
    template<class T>
    void _FillTypeName(const T* pArgument)
    {
        if(m_strTypeName.IsEmpty())
            m_strTypeName.Append(ArgumentTrace::CONSTANT);

        this->_FillTypeName(*pArgument);
        m_strTypeName.Append(ArgumentTrace::ASTERISK);
    }

    /// <summary>
    /// Converts an instance of any type to its corresponding representation as string.
    /// </summary>
    /// <typeparam name="T">The type of the pointer to be converted, which must provide a ToString non-static method that returns a string and receives no parameters.</typeparam>
    /// <param name="object">[IN] The instance to be converted.</param>
    /// <returns>
    /// The string that contains the representation of the object.
    /// </returns>
    template<class T>
    static string_z _ConvertToString(const T &object)
    {
        return object.ToString();
    }
    
    /// <summary>
    /// Converts a pointer-to-non-constant-type to its corresponding representation as string.
    /// </summary>
    /// <remarks>
    /// The string will contain both the memory address contained in the pointer (hexadecimal number, using the suffix "0x") and 
    /// the representation as a string of the instance it points to, in that order, separated with a white-space. If the pointer points to another pointer, 
    /// then both will be dereferenced; this is the maximum number of dereferences supported. Example: type** --> "0x10AFB34D 0x90AFB11A value".<br/>
    /// If the pointer is null, the resultant string will only contain the text "<Null>".<br/>
    /// </remarks>
    /// <typeparam name="T">The type of the pointer to be converted, which must provide a ToString non-static method that returns a string and receives no parameters.</typeparam>
    /// <param name="pObject">[IN] The pointer to the instance to be converted.</param>
    /// <returns>
    /// The string that contains the representation of the object.
    /// </returns>
    template<class T>
    static string_z _ConvertToString(T* pObject)
    {
        return ArgumentTrace::_ConvertToString(ccast_z(pObject, const T*));
    }
    
    /// <summary>
    /// Converts a pointer-to-constant-type to its corresponding representation as string.
    /// </summary>
    /// <remarks>
    /// The string will contain both the memory address contained in the pointer (hexadecimal number, using the suffix "0x") and 
    /// the representation as a string of the instance it points to, in that order, separated with a white-space. If the pointer points to another pointer, 
    /// then both will be dereferenced; this is the maximum number of dereferences supported. Example: type** --> "0x10AFB34D 0x90AFB11A value".<br/>
    /// If the pointer is null, the resultant string will only contain the text "<Null>".<br/>
    /// </remarks>
    /// <typeparam name="T">The type of the pointer to be converted, which must provide a ToString non-static method that returns a string and receives no parameters.</typeparam>
    /// <param name="pObject">[IN] The pointer to the instance to be converted.</param>
    /// <returns>
    /// The string that contains the representation of the object.
    /// </returns>
    template<class T>
    static string_z _ConvertToString(const T* pObject)
    {
        static const string_z HEXADECIMAL_PREFIX("0x");
        static const string_z WHITESPACE(" ");
        static const string_z NULL_POINTER("<Null>");
        
        string_z strResult;

        if(pObject != null_z)
        {
            // Prints the memory address to which the pointer points
            strResult.Append(HEXADECIMAL_PREFIX);
            strResult.Append(string_z::FromIntegerToHexadecimal(rcast_z(pObject, puint_z)));
            strResult.Append(WHITESPACE);

            // It is a pointer to either a basic data type or an unknown type
            strResult.Append(ArgumentTrace::_ConvertToString(*pObject));
        }
        else
        {
            // It is a null pointer
            strResult.Append(NULL_POINTER);
        }

        return strResult;
    }


    // PROPERTIES
    // ---------------
public:

    /// <summary>
    /// Gets the name of the type of the argument.
    /// </summary>
    /// <returns>
    /// The argument type name. If the type of the argument is not recognized, this name will follow a special format.
    /// </returns>
    const string_z& GetTypeName() const;

    /// <summary>
    /// Gets the value of the argument.
    /// </summary>
    /// <returns>
    /// The value of the argument, as a text string. If the type of the argument is not recognized, this value will follow a special format.
    /// </returns>
    const string_z& GetValue() const;


    // ATTRIBUTES
    // ---------------
protected:

    /// <summary>
    /// The type of the argument.
    /// </summary>
    const Type* m_pType;

    /// <summary>
    /// The name of the type of the argument.
    /// </summary>
    string_z m_strTypeName;

    /// <summary>
    /// The value of the argument.
    /// </summary>
    string_z m_strValue;

};


// SPECIALIZATIONS
// ---------------

/// <summary>
/// Constructor that receives a function argument.
/// </summary>
/// <remarks>
/// The type of the argument is retrieved as well as its value, both stored as text strings.<br/>
/// Pointers-to-constant and pointers-to-non-constant are considered as different types and therefore have different names.<br/>
/// If the type of the argument is not a basic type (void, u8_z, u16_z, u32_z, u64_z, i8_z, i16_z, i32_z, i64_z, f32_z, f64_z or bool), a string_z nor a pointer
/// to any of the previous types then a special format will be used:<br/>
/// - Type name: "<Unknown type (size: #)>" (where "#" means a number of bytes).<br/>
/// - Value: "0x######## <Unknown type at 0x########>" (where "#" means a hexadecimal number to indicate the memory address of the instance).<br/>
/// For every pointer dereferencing, a memory address will be added before the value of the instance.<br/>
/// <br/>
/// Examples (Code / Type name / "Value"):<br/>
/// - i32_z i = 3 / i32 / "3"<br/>
/// - i32_z* pInt = &i / i32* / "0x######## 3"<br/>
/// - const i32_z ci = 3 / i32 / "3"<br/>
/// - const i32_z* pInt = &ci / const i32* / "0x######## 3"<br/>
/// - const i32_z** ppInt = &pInt / const i32** / "0x######## 0x######## 3"<br/>
/// - string_z strInt = "text" / string / "text"<br/>
/// - MyCustomType t / "<Unknown type (size: #)>" / "<Unknown type at 0x########>"<br/>
/// - i32_z* pNull = null_z / i32* / "<Null>"
/// </remarks>
/// <typeparam name="T">The type of the argument. It can be whichever.</typeparam>
/// <param name="pArgument">[IN] The argument to be traced.</param>
template<>
Z_LAYER_DIAGNOSIS_SYMBOLS void ArgumentTrace::_FillTypeName(void* pArgument);

/// <summary>
/// Constructor that receives a function argument.
/// </summary>
/// <remarks>
/// The type of the argument is retrieved as well as its value, both stored as text strings.<br/>
/// Pointers-to-constant and pointers-to-non-constant are considered as different types and therefore have different names.<br/>
/// If the type of the argument is not a basic type (void, u8_z, u16_z, u32_z, u64_z, i8_z, i16_z, i32_z, i64_z, f32_z, f64_z or bool), a string_z nor a pointer
/// to any of the previous types then a special format will be used:<br/>
/// - Type name: "<Unknown type (size: #)>" (where "#" means a number of bytes).<br/>
/// - Value: "0x######## <Unknown type at 0x########>" (where "#" means a hexadecimal number to indicate the memory address of the instance).<br/>
/// For every pointer dereferencing, a memory address will be added before the value of the instance.<br/>
/// <br/>
/// Examples (Code / Type name / "Value"):<br/>
/// - i32_z i = 3 / i32 / "3"<br/>
/// - i32_z* pInt = &i / i32* / "0x######## 3"<br/>
/// - const i32_z ci = 3 / i32 / "3"<br/>
/// - const i32_z* pInt = &ci / const i32* / "0x######## 3"<br/>
/// - const i32_z** ppInt = &pInt / const i32** / "0x######## 0x######## 3"<br/>
/// - string_z strInt = "text" / string / "text"<br/>
/// - MyCustomType t / "<Unknown type (size: #)>" / "<Unknown type at 0x########>"<br/>
/// - i32_z* pNull = null_z / i32* / "<Null>"
/// </remarks>
/// <typeparam name="T">The type of the argument. It can be whichever.</typeparam>
/// <param name="pArgument">[IN] The argument to be traced.</param>
template<>
Z_LAYER_DIAGNOSIS_SYMBOLS void ArgumentTrace::_FillTypeName(const void* pArgument);


} // namespace z


#endif // __ARGUMENTTRACE__
