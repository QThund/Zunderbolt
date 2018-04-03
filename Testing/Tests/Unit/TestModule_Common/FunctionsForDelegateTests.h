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

#ifndef __FUNCTIONSFORQDELEGATETESTS__
#define __FUNCTIONSFORQDELEGATETESTS__

// ---------------------------------------------------------------------------------------------------------
// This file contains test artifacts used in Delegate_Test.cpp to test many different cases of the Delegate 
// class. They MUST NOT be modified in any case, unless you are modifying the existing unit tests that use 
// them and you really know what you are doing.
// ---------------------------------------------------------------------------------------------------------

namespace z
{
namespace Test
{
    class Methods
    {
    public:

        Methods()
        {
        }

        int ConstMethod() const
        {
            return 0;
        }

        int ConstMethod(int p1) const
        {
            return p1;
        }

        int ConstMethod(int p1, int p2) const
        {
            return p1 + p2;
        }

        int ConstMethod(int p1, int p2, int p3) const
        {
            return p1 + p2 + p3;
        }

        int ConstMethod(int p1, int p2, int p3, int p4) const
        {
            return p1 + p2 + p3 + p4;
        }

        int ConstMethod(int p1, int p2, int p3, int p4, int p5) const
        {
            return p1 + p2 + p3 + p4 + p5;
        }

        int ConstMethod(int p1, int p2, int p3, int p4, int p5, int p6) const
        {
            return p1 + p2 + p3 + p4 + p5 + p6;
        }

        int ConstMethod(int p1, int p2, int p3, int p4, int p5, int p6, int p7) const
        {
            return p1 + p2 + p3 + p4 + p5 + p6 + p7;
        }

        int ConstMethod(int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8) const
        {
            return p1 + p2 + p3 + p4 + p5 + p6 + p7 + p8;
        }

        int Method()
        {
            return 0;
        }

        int Method(int p1)
        {
            return p1;
        }

        int Method(int p1, int p2)
        {
            return p1 + p2;
        }

        int Method(int p1, int p2, int p3)
        {
            return p1 + p2 + p3;
        }

        int Method(int p1, int p2, int p3, int p4)
        {
            return p1 + p2 + p3 + p4;
        }

        int Method(int p1, int p2, int p3, int p4, int p5)
        {
            return p1 + p2 + p3 + p4 + p5;
        }

        int Method(int p1, int p2, int p3, int p4, int p5, int p6)
        {
            return p1 + p2 + p3 + p4 + p5 + p6;
        }

        int Method(int p1, int p2, int p3, int p4, int p5, int p6, int p7)
        {
            return p1 + p2 + p3 + p4 + p5 + p6 + p7;
        }

        int Method(int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8)
        {
            return p1 + p2 + p3 + p4 + p5 + p6 + p7 + p8;
        }

        virtual int VMethod(int p1)
        {
            return p1;
        }

        static int SMethod(int p1, int p2)
        {
            return p1 + p2;
        }

        static int SMethod2(int p1, int p2)
        {
            return p1 + p2 * 2;
        }

        int Method2(int p1, int p2)
        {
            return p1 + p2 * 2;
        }

    };

    class MethodsDerived1 : public virtual Methods
    {
    public:

        virtual int VMethod(int p1)
        {
            return p1 * 2;
        }
    };
    
    class MethodsDerived2 : public virtual Methods
    {
    public:

        virtual int VMethod(int p1)
        {
            return p1 * 3;
        }
    };
    
    class MethodsDerived3 : public MethodsDerived1, public MethodsDerived2
    {
    public:

        virtual int VMethod(int p1)
        {
            return p1 * 4;
        }
    };

    int LAST_FREEFUNCTION_RESULT = -1;

    void FreeFunctionWithConstant(const int &p1)
    {
        LAST_FREEFUNCTION_RESULT = p1;
    }

    void FreeFunction2()
    {
    }

    void FreeFunction()
    {
        LAST_FREEFUNCTION_RESULT = 0;
    }

    void FreeFunction(int p1)
    {
        LAST_FREEFUNCTION_RESULT = p1;
    }

    void FreeFunction(int p1, int p2)
    {
        LAST_FREEFUNCTION_RESULT = p1 + p2;
    }

    void FreeFunction(int p1, int p2, int p3)
    {
        LAST_FREEFUNCTION_RESULT = p1 + p2 + p3;
    }

    void FreeFunction(int p1, int p2, int p3, int p4)
    {
        LAST_FREEFUNCTION_RESULT = p1 + p2 + p3 + p4;
    }

    void FreeFunction(int p1, int p2, int p3, int p4, int p5)
    {
        LAST_FREEFUNCTION_RESULT = p1 + p2 + p3 + p4 + p5;
    }

    void FreeFunction(int p1, int p2, int p3, int p4, int p5, int p6)
    {
        LAST_FREEFUNCTION_RESULT = p1 + p2 + p3 + p4 + p5 + p6;
    }

    void FreeFunction(int p1, int p2, int p3, int p4, int p5, int p6, int p7)
    {
        LAST_FREEFUNCTION_RESULT = p1 + p2 + p3 + p4 + p5 + p6 + p7;
    }

    void FreeFunction(int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8)
    {
        LAST_FREEFUNCTION_RESULT = p1 + p2 + p3 + p4 + p5 + p6 + p7 + p8;
    }
    
    int FreeFunctionWithReturn()
    {
        return 0;
    }

    int FreeFunctionWithReturn(int p1)
    {
        return p1;
    }

    int FreeFunctionWithReturn(int p1, int p2)
    {
        return p1 + p2;
    }

    int FreeFunctionWithReturn(int p1, int p2, int p3)
    {
        return p1 + p2 + p3;
    }

    int FreeFunctionWithReturn(int p1, int p2, int p3, int p4)
    {
        return p1 + p2 + p3 + p4;
    }

    int FreeFunctionWithReturn(int p1, int p2, int p3, int p4, int p5)
    {
        return p1 + p2 + p3 + p4 + p5;
    }

    int FreeFunctionWithReturn(int p1, int p2, int p3, int p4, int p5, int p6)
    {
        return p1 + p2 + p3 + p4 + p5 + p6;
    }

    int FreeFunctionWithReturn(int p1, int p2, int p3, int p4, int p5, int p6, int p7)
    {
        return p1 + p2 + p3 + p4 + p5 + p6 + p7;
    }

    int FreeFunctionWithReturn(int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8)
    {
        return p1 + p2 + p3 + p4 + p5 + p6 + p7 + p8;
    }

} //namespace Test
} // namespace z

#endif // __FUNCTIONSFORQDELEGATETESTS__
