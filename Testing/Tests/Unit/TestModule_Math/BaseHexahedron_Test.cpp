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
#include <boost/mpl/list.hpp>
using namespace boost::unit_test;

#include "../../testsystem/TestingExternalDefinitions.h"

#include "ZMath/BaseHexahedron.h"
#include "ZMath/Vector3.h"
#include "ZMath/Vector4.h"
#include "ZCommon/DataTypes/SVF32.h"

typedef boost::mpl::list<Vector3, Vector4> TTemplateTypes;


ZTEST_SUITE_BEGIN( BaseHexahedron_TestSuite )

/// <summary>
/// Checks if default values have changed.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor1_DefaultValuesHaveNotChanged_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0 };
    float_z VECTOR_COMPONENTS_C[] = { SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0 };
    float_z VECTOR_COMPONENTS_D[] = { SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0 };
    float_z VECTOR_COMPONENTS_E[] = { SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0 };
    float_z VECTOR_COMPONENTS_F[] = { SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0 };
    float_z VECTOR_COMPONENTS_G[] = { SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0 };
    float_z VECTOR_COMPONENTS_H[] = { SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0 };

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(VECTOR_COMPONENTS_C);
    const T EXPECTED_VALUE_FOR_D(VECTOR_COMPONENTS_D);
    const T EXPECTED_VALUE_FOR_E(VECTOR_COMPONENTS_E);
    const T EXPECTED_VALUE_FOR_F(VECTOR_COMPONENTS_F);
    const T EXPECTED_VALUE_FOR_G(VECTOR_COMPONENTS_G);
    const T EXPECTED_VALUE_FOR_H(VECTOR_COMPONENTS_H);

	// [Execution]
    BaseHexahedron<T> hexahedronUT;

    // [Verification]
    BOOST_CHECK(hexahedronUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(hexahedronUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(hexahedronUT.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(hexahedronUT.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(hexahedronUT.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(hexahedronUT.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(hexahedronUT.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(hexahedronUT.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks if copy constructor sets hexahedron's points properly.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor2_ValuesAreCopiedProperly_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_8 };
    float_z VECTOR_COMPONENTS_C[] = { -SFloat::_1, -SFloat::_2, -SFloat::_3, -SFloat::_4 };
    float_z VECTOR_COMPONENTS_D[] = { -SFloat::_5, -SFloat::_6, -SFloat::_7, -SFloat::_8 };
    float_z VECTOR_COMPONENTS_E[] = { SFloat::_1 - SFloat::_0_5, SFloat::_2 - SFloat::_0_5, SFloat::_3 - SFloat::_0_5, SFloat::_4 - SFloat::_0_5 };
    float_z VECTOR_COMPONENTS_F[] = { SFloat::_5 - SFloat::_0_5, SFloat::_6 - SFloat::_0_5, SFloat::_7 - SFloat::_0_5, SFloat::_8 - SFloat::_0_5 };
    float_z VECTOR_COMPONENTS_G[] = { SFloat::_1 + SFloat::_0_5, SFloat::_2 + SFloat::_0_5, SFloat::_3 + SFloat::_0_5, SFloat::_4 + SFloat::_0_5 };
    float_z VECTOR_COMPONENTS_H[] = { SFloat::_5 + SFloat::_0_5, SFloat::_6 + SFloat::_0_5, SFloat::_7 + SFloat::_0_5, SFloat::_8 + SFloat::_0_5 };

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(VECTOR_COMPONENTS_C);
    const T EXPECTED_VALUE_FOR_D(VECTOR_COMPONENTS_D);
    const T EXPECTED_VALUE_FOR_E(VECTOR_COMPONENTS_E);
    const T EXPECTED_VALUE_FOR_F(VECTOR_COMPONENTS_F);
    const T EXPECTED_VALUE_FOR_G(VECTOR_COMPONENTS_G);
    const T EXPECTED_VALUE_FOR_H(VECTOR_COMPONENTS_H);

    const BaseHexahedron<T> EXPECTED_HEXAHEDRON(EXPECTED_VALUE_FOR_A, 
                                                 EXPECTED_VALUE_FOR_B, 
                                                 EXPECTED_VALUE_FOR_C, 
                                                 EXPECTED_VALUE_FOR_D, 
                                                 EXPECTED_VALUE_FOR_E, 
                                                 EXPECTED_VALUE_FOR_F, 
                                                 EXPECTED_VALUE_FOR_G, 
                                                 EXPECTED_VALUE_FOR_H);

	// [Execution]
    BaseHexahedron<T> hexahedronUT(EXPECTED_HEXAHEDRON);

    // [Verification]
    BOOST_CHECK(hexahedronUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(hexahedronUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(hexahedronUT.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(hexahedronUT.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(hexahedronUT.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(hexahedronUT.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(hexahedronUT.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(hexahedronUT.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks if values used as parameters are properly set.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor3_ValuesAreSetProperly_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_8 };
    float_z VECTOR_COMPONENTS_C[] = { -SFloat::_1, -SFloat::_2, -SFloat::_3, -SFloat::_4 };
    float_z VECTOR_COMPONENTS_D[] = { -SFloat::_5, -SFloat::_6, -SFloat::_7, -SFloat::_8 };
    float_z VECTOR_COMPONENTS_E[] = { SFloat::_1 - SFloat::_0_5, SFloat::_2 - SFloat::_0_5, SFloat::_3 - SFloat::_0_5, SFloat::_4 - SFloat::_0_5 };
    float_z VECTOR_COMPONENTS_F[] = { SFloat::_5 - SFloat::_0_5, SFloat::_6 - SFloat::_0_5, SFloat::_7 - SFloat::_0_5, SFloat::_8 - SFloat::_0_5 };
    float_z VECTOR_COMPONENTS_G[] = { SFloat::_1 + SFloat::_0_5, SFloat::_2 + SFloat::_0_5, SFloat::_3 + SFloat::_0_5, SFloat::_4 + SFloat::_0_5 };
    float_z VECTOR_COMPONENTS_H[] = { SFloat::_5 + SFloat::_0_5, SFloat::_6 + SFloat::_0_5, SFloat::_7 + SFloat::_0_5, SFloat::_8 + SFloat::_0_5 };

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(VECTOR_COMPONENTS_C);
    const T EXPECTED_VALUE_FOR_D(VECTOR_COMPONENTS_D);
    const T EXPECTED_VALUE_FOR_E(VECTOR_COMPONENTS_E);
    const T EXPECTED_VALUE_FOR_F(VECTOR_COMPONENTS_F);
    const T EXPECTED_VALUE_FOR_G(VECTOR_COMPONENTS_G);
    const T EXPECTED_VALUE_FOR_H(VECTOR_COMPONENTS_H);

	// [Execution]
    BaseHexahedron<T> hexahedronUT(EXPECTED_VALUE_FOR_A, 
                                    EXPECTED_VALUE_FOR_B, 
                                    EXPECTED_VALUE_FOR_C, 
                                    EXPECTED_VALUE_FOR_D, 
                                    EXPECTED_VALUE_FOR_E, 
                                    EXPECTED_VALUE_FOR_F, 
                                    EXPECTED_VALUE_FOR_G, 
                                    EXPECTED_VALUE_FOR_H);

    // [Verification]
    BOOST_CHECK(hexahedronUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(hexahedronUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(hexahedronUT.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(hexahedronUT.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(hexahedronUT.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(hexahedronUT.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(hexahedronUT.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(hexahedronUT.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks if the hexahedron is correctly built from 2 common points that represent two of the opposite vertices.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor4_ItsBuiltCorrectlyFromTwoCommonPoints_Test, TTemplateTypes )
{
    //    A --- D
    //   /|    /|
    //  B --- C |
    //  | E --| F
    //  |/    |/
    //  H --- G

    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_1, SFloat::_2, SFloat::_1, SFloat::_4 };
    float_z VECTOR_COMPONENTS_C[] = { SFloat::_3, SFloat::_2, SFloat::_1, SFloat::_4 };
    float_z VECTOR_COMPONENTS_D[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_4 };
    float_z VECTOR_COMPONENTS_E[] = { SFloat::_1, SFloat::_0, SFloat::_3, SFloat::_9 };
    float_z VECTOR_COMPONENTS_F[] = { SFloat::_3, SFloat::_0, SFloat::_3, SFloat::_9 };
    float_z VECTOR_COMPONENTS_G[] = { SFloat::_3, SFloat::_0, SFloat::_1, SFloat::_9 };
    float_z VECTOR_COMPONENTS_H[] = { SFloat::_1, SFloat::_0, SFloat::_1, SFloat::_9 };

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(VECTOR_COMPONENTS_C);
    const T EXPECTED_VALUE_FOR_D(VECTOR_COMPONENTS_D);
    const T EXPECTED_VALUE_FOR_E(VECTOR_COMPONENTS_E);
    const T EXPECTED_VALUE_FOR_F(VECTOR_COMPONENTS_F);
    const T EXPECTED_VALUE_FOR_G(VECTOR_COMPONENTS_G);
    const T EXPECTED_VALUE_FOR_H(VECTOR_COMPONENTS_H);

	// [Execution]
    BaseHexahedron<T> hexahedronUT(EXPECTED_VALUE_FOR_A, 
                                    EXPECTED_VALUE_FOR_G);

    // [Verification]
    BOOST_CHECK(hexahedronUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(hexahedronUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(hexahedronUT.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(hexahedronUT.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(hexahedronUT.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(hexahedronUT.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(hexahedronUT.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(hexahedronUT.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks if all the points of the hexahedron coincide in space when A and G points are the same.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor4_AllPointsCoincideWhenInputPointsCoincide_Test, TTemplateTypes )
{
    //    A --- D
    //   /|    /|
    //  B --- C |
    //  | E --| F
    //  |/    |/
    //  H --- G

    // [Preparation]
    float_z VECTOR_COMPONENTS_EVERY_POINT[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4 };

    const T EXPECTED_VALUE_FOR_ALL_POINTS(VECTOR_COMPONENTS_EVERY_POINT);

	// [Execution]
    BaseHexahedron<T> hexahedronUT(EXPECTED_VALUE_FOR_ALL_POINTS, 
                                    EXPECTED_VALUE_FOR_ALL_POINTS);

    // [Verification]
    BOOST_CHECK(hexahedronUT.A == EXPECTED_VALUE_FOR_ALL_POINTS);
    BOOST_CHECK(hexahedronUT.B == EXPECTED_VALUE_FOR_ALL_POINTS);
    BOOST_CHECK(hexahedronUT.C == EXPECTED_VALUE_FOR_ALL_POINTS);
    BOOST_CHECK(hexahedronUT.D == EXPECTED_VALUE_FOR_ALL_POINTS);
    BOOST_CHECK(hexahedronUT.E == EXPECTED_VALUE_FOR_ALL_POINTS);
    BOOST_CHECK(hexahedronUT.F == EXPECTED_VALUE_FOR_ALL_POINTS);
    BOOST_CHECK(hexahedronUT.G == EXPECTED_VALUE_FOR_ALL_POINTS);
    BOOST_CHECK(hexahedronUT.H == EXPECTED_VALUE_FOR_ALL_POINTS);
}

/// <summary>
/// Checks if the hexahedron is correctly built from 3 common dimension lengths values and a central point.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor5_ItsBuiltCorrectlyFromCommonLengthsAndCentralPoint_Test, TTemplateTypes )
{
    //    A --- D
    //   /|    /|
    //  B --- C |
    //  | E --| F
    //  |/    |/
    //  H --- G

    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_10 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_1, SFloat::_2, SFloat::_1, SFloat::_10 };
    float_z VECTOR_COMPONENTS_C[] = { SFloat::_4, SFloat::_2, SFloat::_1, SFloat::_10 };
    float_z VECTOR_COMPONENTS_D[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_10 };
    float_z VECTOR_COMPONENTS_E[] = { SFloat::_1, -SFloat::_2, SFloat::_3, SFloat::_10 };
    float_z VECTOR_COMPONENTS_F[] = { SFloat::_4, -SFloat::_2, SFloat::_3, SFloat::_10 };
    float_z VECTOR_COMPONENTS_G[] = { SFloat::_4, -SFloat::_2, SFloat::_1, SFloat::_10 };
    float_z VECTOR_COMPONENTS_H[] = { SFloat::_1, -SFloat::_2, SFloat::_1, SFloat::_10 };
    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2 + SFloat::_0_5, SFloat::_0, SFloat::_2, SFloat::_10 };

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(VECTOR_COMPONENTS_C);
    const T EXPECTED_VALUE_FOR_D(VECTOR_COMPONENTS_D);
    const T EXPECTED_VALUE_FOR_E(VECTOR_COMPONENTS_E);
    const T EXPECTED_VALUE_FOR_F(VECTOR_COMPONENTS_F);
    const T EXPECTED_VALUE_FOR_G(VECTOR_COMPONENTS_G);
    const T EXPECTED_VALUE_FOR_H(VECTOR_COMPONENTS_H);

    const float_z INPUT_X = SFloat::_3;
    const float_z INPUT_Y = SFloat::_4;
    const float_z INPUT_Z = SFloat::_2;
    const T INPUT_CENTER(VECTOR_COMPONENTS_CENTER);

	// [Execution]
    BaseHexahedron<T> hexahedronUT(INPUT_CENTER, INPUT_X, INPUT_Y, INPUT_Z);

    // [Verification]
    BOOST_CHECK(hexahedronUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(hexahedronUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(hexahedronUT.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(hexahedronUT.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(hexahedronUT.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(hexahedronUT.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(hexahedronUT.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(hexahedronUT.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks if the hexahedron is correctly built from 3 common dimension lengths values and a central point.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor5_AllPointsCoincideWithCoordinateOriginWhenLengthsEqualZero_Test, TTemplateTypes )
{
    //    A --- D
    //   /|    /|
    //  B --- C |
    //  | E --| F
    //  |/    |/
    //  H --- G

    // [Preparation]
    const T EXPECTED_VALUE_FOR_ALL_POINTS = T::GetNullVector();

    const float_z INPUT_X = SFloat::_0;
    const float_z INPUT_Y = SFloat::_0;
    const float_z INPUT_Z = SFloat::_0;
    const T INPUT_CENTER = T::GetNullVector();

	// [Execution]
    BaseHexahedron<T> hexahedronUT(INPUT_CENTER, INPUT_X, INPUT_Y, INPUT_Z);

    // [Verification]
    BOOST_CHECK(hexahedronUT.A == EXPECTED_VALUE_FOR_ALL_POINTS);
    BOOST_CHECK(hexahedronUT.B == EXPECTED_VALUE_FOR_ALL_POINTS);
    BOOST_CHECK(hexahedronUT.C == EXPECTED_VALUE_FOR_ALL_POINTS);
    BOOST_CHECK(hexahedronUT.D == EXPECTED_VALUE_FOR_ALL_POINTS);
    BOOST_CHECK(hexahedronUT.E == EXPECTED_VALUE_FOR_ALL_POINTS);
    BOOST_CHECK(hexahedronUT.F == EXPECTED_VALUE_FOR_ALL_POINTS);
    BOOST_CHECK(hexahedronUT.G == EXPECTED_VALUE_FOR_ALL_POINTS);
    BOOST_CHECK(hexahedronUT.H == EXPECTED_VALUE_FOR_ALL_POINTS);
}

/// <summary>
/// Checks if the operator returns true when operand components differences equals tolerance value.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorEquality_TrueWhenOperandsDifferTolerance_Test, TTemplateTypes )
{
    // [Preparation]
    const BaseHexahedron<T> LEFT_OPERAND = BaseHexahedron<T>( T::GetNullVector(), T::GetNullVector(), T::GetNullVector(), T::GetNullVector(), T::GetNullVector(), T::GetNullVector(), T::GetNullVector(), T::GetNullVector() );
    const BaseHexahedron<T> RIGHT_OPERAND = BaseHexahedron<T>( T::GetNullVector(), T::GetNullVector(), T::GetNullVector(), T::GetNullVector(), T::GetNullVector(), T::GetNullVector(), T::GetNullVector(), T::GetNullVector() );

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns true when operand components differences are lower than tolerance value.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorEquality_TrueWhenOperandsDifferLessThanTolerance_Test, TTemplateTypes )
{
    // [Preparation]
    const BaseHexahedron<T> LEFT_OPERAND = BaseHexahedron<T>( T(SFloat::Epsilon - SFloat::Epsilon * SFloat::_0_5), 
                                                                T(SFloat::Epsilon - SFloat::Epsilon * SFloat::_0_5), 
                                                                T(SFloat::Epsilon - SFloat::Epsilon * SFloat::_0_5), 
                                                                T(SFloat::Epsilon - SFloat::Epsilon * SFloat::_0_5), 
                                                                T(SFloat::Epsilon - SFloat::Epsilon * SFloat::_0_5), 
                                                                T(SFloat::Epsilon - SFloat::Epsilon * SFloat::_0_5), 
                                                                T(SFloat::Epsilon - SFloat::Epsilon * SFloat::_0_5), 
                                                                T(SFloat::Epsilon - SFloat::Epsilon * SFloat::_0_5) );
    const BaseHexahedron<T> RIGHT_OPERAND = BaseHexahedron<T>( T::GetNullVector(), T::GetNullVector(), T::GetNullVector(), T::GetNullVector(), T::GetNullVector(), T::GetNullVector(), T::GetNullVector(), T::GetNullVector() );

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns false when operand components differences are greater than tolerance value.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorEquality_FalseWhenOperandsDifferGreaterThanTolerance_Test, TTemplateTypes )
{
    // [Preparation]
    const BaseHexahedron<T> LEFT_OPERAND = BaseHexahedron<T>( T(SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5), 
                                                                T(SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5), 
                                                                T(SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5), 
                                                                T(SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5), 
                                                                T(SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5), 
                                                                T(SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5), 
                                                                T(SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5), 
                                                                T(SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5) );
    const BaseHexahedron<T> RIGHT_OPERAND = BaseHexahedron<T>( T::GetNullVector(), T::GetNullVector(), T::GetNullVector(), T::GetNullVector(), T::GetNullVector(), T::GetNullVector(), T::GetNullVector(), T::GetNullVector() );

	// [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND == RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns true when operand components are exactly equal.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorEquality_TrueWhenOperandsAreExactlyEqual_Test, TTemplateTypes )
{
    // [Preparation]
    const BaseHexahedron<T> LEFT_OPERAND = BaseHexahedron<T>( T(SFloat::Epsilon), T(SFloat::Epsilon), T(SFloat::Epsilon), T(SFloat::Epsilon), T(SFloat::Epsilon), T(SFloat::Epsilon), T(SFloat::Epsilon), T(SFloat::Epsilon) );
    const BaseHexahedron<T> RIGHT_OPERAND = BaseHexahedron<T>( T(SFloat::Epsilon), T(SFloat::Epsilon), T(SFloat::Epsilon), T(SFloat::Epsilon), T(SFloat::Epsilon), T(SFloat::Epsilon), T(SFloat::Epsilon), T(SFloat::Epsilon) );

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns false when operand components differences equals tolerance value.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorInequality_FalseWhenOperandsDifferTolerance_Test, TTemplateTypes )
{
    // [Preparation]
    const BaseHexahedron<T> LEFT_OPERAND =  BaseHexahedron<T>( T(SFloat::Epsilon), T(SFloat::Epsilon), T(SFloat::Epsilon), T(SFloat::Epsilon), T(SFloat::Epsilon), T(SFloat::Epsilon), T(SFloat::Epsilon), T(SFloat::Epsilon) );
    const BaseHexahedron<T> RIGHT_OPERAND = BaseHexahedron<T>( T(SFloat::Epsilon), T(SFloat::Epsilon), T(SFloat::Epsilon), T(SFloat::Epsilon), T(SFloat::Epsilon), T(SFloat::Epsilon), T(SFloat::Epsilon), T(SFloat::Epsilon) );

	// [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns false when operand components differences are lower than tolerance value.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorInequality_FalseWhenOperandsDifferLessThanTolerance_Test, TTemplateTypes )
{
    // [Preparation]
    const BaseHexahedron<T> LEFT_OPERAND = BaseHexahedron<T>( T(SFloat::Epsilon - SFloat::Epsilon * SFloat::_0_5), 
                                                                T(SFloat::Epsilon - SFloat::Epsilon * SFloat::_0_5), 
                                                                T(SFloat::Epsilon - SFloat::Epsilon * SFloat::_0_5), 
                                                                T(SFloat::Epsilon - SFloat::Epsilon * SFloat::_0_5), 
                                                                T(SFloat::Epsilon - SFloat::Epsilon * SFloat::_0_5), 
                                                                T(SFloat::Epsilon - SFloat::Epsilon * SFloat::_0_5), 
                                                                T(SFloat::Epsilon - SFloat::Epsilon * SFloat::_0_5), 
                                                                T(SFloat::Epsilon - SFloat::Epsilon * SFloat::_0_5) );
    const BaseHexahedron<T> RIGHT_OPERAND = BaseHexahedron<T>( T(SFloat::Epsilon), T(SFloat::Epsilon), T(SFloat::Epsilon), T(SFloat::Epsilon), T(SFloat::Epsilon), T(SFloat::Epsilon), T(SFloat::Epsilon), T(SFloat::Epsilon) );

	// [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns false when operand components differences are greater than tolerance value.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorInequality_TrueWhenOperandsDifferGreaterThanTolerance_Test, TTemplateTypes )
{
    // [Preparation]
    const BaseHexahedron<T> LEFT_OPERAND = BaseHexahedron<T>( T(SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5), 
                                                                T(SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5), 
                                                                T(SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5), 
                                                                T(SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5), 
                                                                T(SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5), 
                                                                T(SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5), 
                                                                T(SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5), 
                                                                T(SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5) );
    const BaseHexahedron<T> RIGHT_OPERAND = BaseHexahedron<T>( T::GetNullVector(), T::GetNullVector(), T::GetNullVector(), T::GetNullVector(), T::GetNullVector(), T::GetNullVector(), T::GetNullVector(), T::GetNullVector() );

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND != RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns true when operand components are exactly equal.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorInequality_FalseWhenOperandsAreExactlyEqual_Test, TTemplateTypes )
{
    // [Preparation]
    const BaseHexahedron<T> LEFT_OPERAND = BaseHexahedron<T>( T(SFloat::Epsilon), T(SFloat::Epsilon), T(SFloat::Epsilon), T(SFloat::Epsilon), T(SFloat::Epsilon), T(SFloat::Epsilon), T(SFloat::Epsilon), T(SFloat::Epsilon) );
    const BaseHexahedron<T> RIGHT_OPERAND = BaseHexahedron<T>( T(SFloat::Epsilon), T(SFloat::Epsilon), T(SFloat::Epsilon), T(SFloat::Epsilon), T(SFloat::Epsilon), T(SFloat::Epsilon), T(SFloat::Epsilon), T(SFloat::Epsilon) );

	// [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

// End - Test Suite: BaseHexahedron
ZTEST_SUITE_END()
