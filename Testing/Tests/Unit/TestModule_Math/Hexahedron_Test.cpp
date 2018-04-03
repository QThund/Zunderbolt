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

#include "ZMath/Hexahedron.h"

#include "ZMath/Vector3.h"
#include "ZMath/Vector4.h"
#include "ZMath/Matrix4x3.h"
#include "ZMath/RotationMatrix3x3.h"
#include "ZMath/ScalingMatrix3x3.h"
#include "ZMath/TranslationMatrix.h"
#include "ZMath/TransformationMatrix.h"
#include "ZMath/SpaceConversionMatrix.h"
#include "ZCommon/Exceptions/AssertException.h"


typedef boost::mpl::list<Vector3, Vector4> TTemplateTypes;


ZTEST_SUITE_BEGIN( Hexahedron_TestSuite )

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
    Hexahedron<T> hexahedronUT;

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

    const Hexahedron<T> EXPECTED_HEXAHEDRON(EXPECTED_VALUE_FOR_A,
                                             EXPECTED_VALUE_FOR_B,
                                             EXPECTED_VALUE_FOR_C,
                                             EXPECTED_VALUE_FOR_D,
                                             EXPECTED_VALUE_FOR_E,
                                             EXPECTED_VALUE_FOR_F,
                                             EXPECTED_VALUE_FOR_G,
                                             EXPECTED_VALUE_FOR_H);

	// [Execution]
    Hexahedron<T> hexahedronUT(EXPECTED_HEXAHEDRON);

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
ZTEST_CASE_TEMPLATE ( Constructor4_ValuesAreSetProperly_Test, TTemplateTypes )
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
    Hexahedron<T> hexahedronUT(EXPECTED_VALUE_FOR_A,
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
ZTEST_CASE_TEMPLATE ( Constructor5_ItsBuiltCorrectlyFromTwoCommonPoints_Test, TTemplateTypes )
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
    Hexahedron<T> hexahedronUT(EXPECTED_VALUE_FOR_A,
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
ZTEST_CASE_TEMPLATE ( Constructor5_AllPointsCoincideWhenInputPointsCoincide_Test, TTemplateTypes )
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
    Hexahedron<T> hexahedronUT(EXPECTED_VALUE_FOR_ALL_POINTS,
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
ZTEST_CASE_TEMPLATE ( Constructor6_ItsBuiltCorrectlyFromCommonLengthsAndCentralPoint_Test, TTemplateTypes )
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
    Hexahedron<T> hexahedronUT(INPUT_CENTER, INPUT_X, INPUT_Y, INPUT_Z);

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
ZTEST_CASE_TEMPLATE ( Constructor6_AllPointsCoincideWithCoordinateOriginWhenLengthsEqualZero_Test, TTemplateTypes )
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
    Hexahedron<T> hexahedronUT(INPUT_CENTER, INPUT_X, INPUT_Y, INPUT_Z);

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
/// Checks if it returns a unit cube set at the coordinate origin.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetUnitCube_ItReturnsWhatExpected_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z POINT_COMPONENTS_A[] = {-SFloat::_0_5, SFloat::_0_5, SFloat::_0_5, SFloat::_1 };
    const float_z POINT_COMPONENTS_B[] = {-SFloat::_0_5, SFloat::_0_5, -SFloat::_0_5, SFloat::_1 };
    const float_z POINT_COMPONENTS_C[] = {SFloat::_0_5, SFloat::_0_5, -SFloat::_0_5, SFloat::_1 };
    const float_z POINT_COMPONENTS_D[] = {SFloat::_0_5, SFloat::_0_5, SFloat::_0_5, SFloat::_1 };
    const float_z POINT_COMPONENTS_E[] = {-SFloat::_0_5, -SFloat::_0_5, SFloat::_0_5, SFloat::_1 };
    const float_z POINT_COMPONENTS_F[] = {SFloat::_0_5, -SFloat::_0_5, SFloat::_0_5, SFloat::_1 };
    const float_z POINT_COMPONENTS_G[] = {SFloat::_0_5, -SFloat::_0_5, -SFloat::_0_5, SFloat::_1 };
    const float_z POINT_COMPONENTS_H[] = {-SFloat::_0_5, -SFloat::_0_5, -SFloat::_0_5, SFloat::_1 };

    const Hexahedron<T> UNIT_CUBE = Hexahedron<T>( T(POINT_COMPONENTS_A),
                                                     T(POINT_COMPONENTS_B),
                                                     T(POINT_COMPONENTS_C),
                                                     T(POINT_COMPONENTS_D),
                                                     T(POINT_COMPONENTS_E),
                                                     T(POINT_COMPONENTS_F),
                                                     T(POINT_COMPONENTS_G),
                                                     T(POINT_COMPONENTS_H) );

	// [Execution]
    Hexahedron<T> hexahedron = Hexahedron<T>::GetUnitCube();

    // [Verification]
    BOOST_CHECK(hexahedron.A == UNIT_CUBE.A);
    BOOST_CHECK(hexahedron.B == UNIT_CUBE.B);
    BOOST_CHECK(hexahedron.C == UNIT_CUBE.C);
    BOOST_CHECK(hexahedron.D == UNIT_CUBE.D);
    BOOST_CHECK(hexahedron.E == UNIT_CUBE.E);
    BOOST_CHECK(hexahedron.F == UNIT_CUBE.F);
    BOOST_CHECK(hexahedron.G == UNIT_CUBE.G);
    BOOST_CHECK(hexahedron.H == UNIT_CUBE.H);
}

/// <summary>
/// Checks if points are correctly copied.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorAssignation_ValuesAreCopiedProperly_Test, TTemplateTypes )
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
    Hexahedron<T> hexahedronUT;
    hexahedronUT = EXPECTED_HEXAHEDRON;

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
/// Checks that the hexahedron is correctly transformed by an arbitrary quaternion.
/// </summary>
ZTEST_CASE_TEMPLATE ( Rotate1_HexahedronIsCorrectlyTransformedByCommonRotationMatrix_Test, TTemplateTypes )
{
    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z EULER_ANGLE_X = SAngle::_HalfPi;
    const float_z EULER_ANGLE_Y = SAngle::_Pi;
    const float_z EULER_ANGLE_Z = SAngle::_QuarterPi;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z EULER_ANGLE_X = SAngle::_90;
    const float_z EULER_ANGLE_Y = SAngle::_180;
    const float_z EULER_ANGLE_Z = SAngle::_45;
#endif

    const Quaternion ROTATION = Quaternion(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);

    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>::GetUnitCube();

    const float_z EXPECTED_VECTOR_COMPONENTS_A[] = { (float_z)-5.5511151231257827e-017, (float_z)-0.70710678118654746, (float_z)-0.50000000000000011, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_B[] = { (float_z)0.70710678118654746, (float_z)-2.7755575615628914e-017, (float_z)-0.49999999999999994, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_C[] = { (float_z)1.6653345369377348e-016, (float_z)0.70710678118654757, (float_z)-0.49999999999999989, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_D[] = { (float_z)-0.70710678118654735, (float_z)1.2490009027033011e-016, (float_z)-0.50000000000000011, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_E[] = { (float_z)-1.6653345369377348e-016, (float_z)-0.70710678118654757, (float_z)0.49999999999999989, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_F[] = { (float_z)-0.70710678118654746, (float_z)2.7755575615628914e-017, (float_z)0.49999999999999994, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_G[] = { (float_z)5.5511151231257827e-017, (float_z)0.70710678118654746, (float_z)0.50000000000000011, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_H[] = { (float_z)0.70710678118654735, (float_z)-1.2490009027033011e-016, (float_z)0.50000000000000011, SFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(EXPECTED_VECTOR_COMPONENTS_C);
    const T EXPECTED_VALUE_FOR_D(EXPECTED_VECTOR_COMPONENTS_D);
    const T EXPECTED_VALUE_FOR_E(EXPECTED_VECTOR_COMPONENTS_E);
    const T EXPECTED_VALUE_FOR_F(EXPECTED_VECTOR_COMPONENTS_F);
    const T EXPECTED_VALUE_FOR_G(EXPECTED_VECTOR_COMPONENTS_G);
    const T EXPECTED_VALUE_FOR_H(EXPECTED_VECTOR_COMPONENTS_H);

	// [Execution]
    Hexahedron<T> returnedHexahedron = HEXAHEDRON.Rotate(ROTATION);

    // [Verification]
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);

}

/// <summary>
/// Checks that a hexahedron is not rotated when the quaternion equals identity.
/// </summary>
ZTEST_CASE_TEMPLATE ( Rotate1_HexahedronIsNotRotatedWhenQuaternionEqualsIdentity_Test, TTemplateTypes )
{
    // [Preparation]
    const Quaternion ROTATION = Quaternion::GetIdentity();

    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>::GetUnitCube();

    const T EXPECTED_VALUE_FOR_A = HEXAHEDRON.A;
    const T EXPECTED_VALUE_FOR_B = HEXAHEDRON.B;
    const T EXPECTED_VALUE_FOR_C = HEXAHEDRON.C;
    const T EXPECTED_VALUE_FOR_D = HEXAHEDRON.D;
    const T EXPECTED_VALUE_FOR_E = HEXAHEDRON.E;
    const T EXPECTED_VALUE_FOR_F = HEXAHEDRON.F;
    const T EXPECTED_VALUE_FOR_G = HEXAHEDRON.G;
    const T EXPECTED_VALUE_FOR_H = HEXAHEDRON.H;

	// [Execution]
    Hexahedron<T> returnedHexahedron = HEXAHEDRON.Rotate(ROTATION);

    // [Verification]
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that the vertices of the hexahedron are moved to the coordinate origin when the quaternion is null.
/// </summary>
ZTEST_CASE_TEMPLATE ( Rotate1_VerticesAreMovedToCoordinateOriginWhenQuaternionIsNull_Test, TTemplateTypes )
{
    // [Preparation]
    const Quaternion ROTATION = Quaternion(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);

    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>::GetUnitCube();

    const float_z NULL_VECTOR_COMPONENTS[] = {SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1};
    const T COORDINATE_ORIGIN = T(NULL_VECTOR_COMPONENTS);

	// [Execution]
    Hexahedron<T> returnedHexahedron = HEXAHEDRON.Rotate(ROTATION);

    // [Verification]
    BOOST_CHECK(returnedHexahedron.A == COORDINATE_ORIGIN);
    BOOST_CHECK(returnedHexahedron.B == COORDINATE_ORIGIN);
    BOOST_CHECK(returnedHexahedron.C == COORDINATE_ORIGIN);
    BOOST_CHECK(returnedHexahedron.D == COORDINATE_ORIGIN);
    BOOST_CHECK(returnedHexahedron.E == COORDINATE_ORIGIN);
    BOOST_CHECK(returnedHexahedron.F == COORDINATE_ORIGIN);
    BOOST_CHECK(returnedHexahedron.G == COORDINATE_ORIGIN);
    BOOST_CHECK(returnedHexahedron.H == COORDINATE_ORIGIN);
}

/// <summary>
/// Checks that the hexahedron is correctly transformed by an arbitrary quaternion.
/// </summary>
ZTEST_CASE_TEMPLATE ( RotateWithPivot1_HexahedronIsCorrectlyTransformedByCommonQuaternions_Test, TTemplateTypes )
{
    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z EULER_ANGLE_X = SAngle::_HalfPi;
    const float_z EULER_ANGLE_Y = SAngle::_Pi;
    const float_z EULER_ANGLE_Z = SAngle::_QuarterPi;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z EULER_ANGLE_X = SAngle::_90;
    const float_z EULER_ANGLE_Y = SAngle::_180;
    const float_z EULER_ANGLE_Z = SAngle::_45;
#endif

    const Quaternion ROTATION = Quaternion(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);

    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>::GetUnitCube();

    const float_z EXPECTED_VECTOR_COMPONENTS_A[] = { (float_z)3.8284271247461898, (float_z)2.707106781186547, (float_z)4.5, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_B[] = { (float_z)4.5355339059327378, (float_z)3.414213562373094, (float_z)4.5, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_C[] = { (float_z)3.8284271247461898, (float_z)4.1213203435596419, (float_z)4.5, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_D[] = { (float_z)3.1213203435596424, (float_z)3.4142135623730945, (float_z)4.5, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_E[] = { (float_z)3.8284271247461898, (float_z)2.7071067811865466, (float_z)5.5, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_F[] = { (float_z)3.1213203435596424, (float_z)3.4142135623730945, (float_z)5.5, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_G[] = { (float_z)3.8284271247461898, (float_z)4.1213203435596419, (float_z)5.5, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_H[] = { (float_z)4.5355339059327378, (float_z)3.4142135623730940, (float_z)5.5, SFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(EXPECTED_VECTOR_COMPONENTS_C);
    const T EXPECTED_VALUE_FOR_D(EXPECTED_VECTOR_COMPONENTS_D);
    const T EXPECTED_VALUE_FOR_E(EXPECTED_VECTOR_COMPONENTS_E);
    const T EXPECTED_VALUE_FOR_F(EXPECTED_VECTOR_COMPONENTS_F);
    const T EXPECTED_VALUE_FOR_G(EXPECTED_VECTOR_COMPONENTS_G);
    const T EXPECTED_VALUE_FOR_H(EXPECTED_VECTOR_COMPONENTS_H);

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// [Execution]
    Hexahedron<T> returnedHexahedron = HEXAHEDRON.RotateWithPivot(ROTATION, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that a hexahedron is not rotated when the quaternion equals identity.
/// </summary>
ZTEST_CASE_TEMPLATE ( RotateWithPivot1_HexahedronIsNotRotateWithPivotdWhenQuaternionEqualsIdentity_Test, TTemplateTypes )
{
    // [Preparation]
    const Quaternion ROTATION = Quaternion::GetIdentity();

    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>::GetUnitCube();

    const T EXPECTED_VALUE_FOR_A = HEXAHEDRON.A;
    const T EXPECTED_VALUE_FOR_B = HEXAHEDRON.B;
    const T EXPECTED_VALUE_FOR_C = HEXAHEDRON.C;
    const T EXPECTED_VALUE_FOR_D = HEXAHEDRON.D;
    const T EXPECTED_VALUE_FOR_E = HEXAHEDRON.E;
    const T EXPECTED_VALUE_FOR_F = HEXAHEDRON.F;
    const T EXPECTED_VALUE_FOR_G = HEXAHEDRON.G;
    const T EXPECTED_VALUE_FOR_H = HEXAHEDRON.H;

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// [Execution]
    Hexahedron<T> returnedHexahedron = HEXAHEDRON.RotateWithPivot(ROTATION, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that the vertices of the hexahedron are moved to the position of the pivot point when the quaternion is null.
/// </summary>
ZTEST_CASE_TEMPLATE ( RotateWithPivot1_VerticesAreMovedToPivotPositionWhenQuaternionIsNull_Test, TTemplateTypes )
{
    // [Preparation]
    const Quaternion ROTATION = Quaternion(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);

    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>::GetUnitCube();

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const T EXPECTED_VALUE_FOR_A = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_B = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_C = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_D = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_E = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_F = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_G = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_H = PIVOT_POINT;

	// [Execution]
    Hexahedron<T> returnedHexahedron = HEXAHEDRON.RotateWithPivot(ROTATION, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that a common hexahedron is correctly translated using common translation vector.
/// </summary>
ZTEST_CASE_TEMPLATE ( Translate1_CommonHexahedronIsCorrectlyTranslatedWhenUsingCommonVector_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_D[] = { SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_E[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_F[] = { SFloat::_4, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_G[] = { -SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_H[] = { SFloat::_0, SFloat::_1, SFloat::_4, SFloat::_1 };

    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>(T(VECTOR_COMPONENTS_A),
                                                     T(VECTOR_COMPONENTS_B),
                                                     T(VECTOR_COMPONENTS_C),
                                                     T(VECTOR_COMPONENTS_D),
                                                     T(VECTOR_COMPONENTS_E),
                                                     T(VECTOR_COMPONENTS_F),
                                                     T(VECTOR_COMPONENTS_G),
                                                     T(VECTOR_COMPONENTS_H));

    const float_z EXPECTED_VECTOR_COMPONENTS_A[] = { SFloat::_2, SFloat::_4, SFloat::_7, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_B[] = { SFloat::_4, SFloat::_3, SFloat::_7, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_C[] = { SFloat::_3, SFloat::_5, SFloat::_6, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_D[] = { SFloat::_5, SFloat::_7, SFloat::_9, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_E[] = { SFloat::_4, SFloat::_4, SFloat::_6, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_F[] = { SFloat::_5, SFloat::_3, SFloat::_6, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_G[] = { SFloat::_0, SFloat::_4, SFloat::_7, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_H[] = { SFloat::_1, SFloat::_3, SFloat::_7, SFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(EXPECTED_VECTOR_COMPONENTS_C);
    const T EXPECTED_VALUE_FOR_D(EXPECTED_VECTOR_COMPONENTS_D);
    const T EXPECTED_VALUE_FOR_E(EXPECTED_VECTOR_COMPONENTS_E);
    const T EXPECTED_VALUE_FOR_F(EXPECTED_VECTOR_COMPONENTS_F);
    const T EXPECTED_VALUE_FOR_G(EXPECTED_VECTOR_COMPONENTS_G);
    const T EXPECTED_VALUE_FOR_H(EXPECTED_VECTOR_COMPONENTS_H);

    const Vector3 TRANSLATION = Vector3(SFloat::_1, SFloat::_2, SFloat::_3);

	// [Execution]
    Hexahedron<T> returnedHexahedron = HEXAHEDRON.Translate(TRANSLATION);

    // [Verification]
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that a hexahedron is not translated when translation is zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( Translate1_HexahedronIsNotTranslatedWhenTranslationIsZero_Test, TTemplateTypes )
{
    // [Preparation]
    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>::GetUnitCube();

    const T EXPECTED_VALUE_FOR_A = HEXAHEDRON.A;
    const T EXPECTED_VALUE_FOR_B = HEXAHEDRON.B;
    const T EXPECTED_VALUE_FOR_C = HEXAHEDRON.C;
    const T EXPECTED_VALUE_FOR_D = HEXAHEDRON.D;
    const T EXPECTED_VALUE_FOR_E = HEXAHEDRON.E;
    const T EXPECTED_VALUE_FOR_F = HEXAHEDRON.F;
    const T EXPECTED_VALUE_FOR_G = HEXAHEDRON.G;
    const T EXPECTED_VALUE_FOR_H = HEXAHEDRON.H;

    const Vector3 TRANSLATION = Vector3::GetNullVector();

	// [Execution]
    Hexahedron<T> returnedHexahedron = HEXAHEDRON.Translate(TRANSLATION);

    // [Verification]
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that a common hexahedron is correctly translated using common translation values.
/// </summary>
ZTEST_CASE_TEMPLATE ( Translate2_CommonHexahedronIsCorrectlyTranslatedWhenUsingCommonValues_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_D[] = { SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_E[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_F[] = { SFloat::_4, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_G[] = { -SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_H[] = { SFloat::_0, SFloat::_1, SFloat::_4, SFloat::_1 };

    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>(T(VECTOR_COMPONENTS_A),
                                                     T(VECTOR_COMPONENTS_B),
                                                     T(VECTOR_COMPONENTS_C),
                                                     T(VECTOR_COMPONENTS_D),
                                                     T(VECTOR_COMPONENTS_E),
                                                     T(VECTOR_COMPONENTS_F),
                                                     T(VECTOR_COMPONENTS_G),
                                                     T(VECTOR_COMPONENTS_H));

    const float_z EXPECTED_VECTOR_COMPONENTS_A[] = { SFloat::_2, SFloat::_4, SFloat::_7, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_B[] = { SFloat::_4, SFloat::_3, SFloat::_7, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_C[] = { SFloat::_3, SFloat::_5, SFloat::_6, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_D[] = { SFloat::_5, SFloat::_7, SFloat::_9, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_E[] = { SFloat::_4, SFloat::_4, SFloat::_6, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_F[] = { SFloat::_5, SFloat::_3, SFloat::_6, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_G[] = { SFloat::_0, SFloat::_4, SFloat::_7, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_H[] = { SFloat::_1, SFloat::_3, SFloat::_7, SFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(EXPECTED_VECTOR_COMPONENTS_C);
    const T EXPECTED_VALUE_FOR_D(EXPECTED_VECTOR_COMPONENTS_D);
    const T EXPECTED_VALUE_FOR_E(EXPECTED_VECTOR_COMPONENTS_E);
    const T EXPECTED_VALUE_FOR_F(EXPECTED_VECTOR_COMPONENTS_F);
    const T EXPECTED_VALUE_FOR_G(EXPECTED_VECTOR_COMPONENTS_G);
    const T EXPECTED_VALUE_FOR_H(EXPECTED_VECTOR_COMPONENTS_H);

    const float_z TRANSLATION_X = SFloat::_1;
    const float_z TRANSLATION_Y = SFloat::_2;
    const float_z TRANSLATION_Z = SFloat::_3;

	// [Execution]
    Hexahedron<T> returnedHexahedron = HEXAHEDRON.Translate(TRANSLATION_X, TRANSLATION_Y, TRANSLATION_Z);

    // [Verification]
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that a hexahedron is not translated when translation is zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( Translate2_HexahedronIsNotTranslatedWhenTranslationIsZero_Test, TTemplateTypes )
{
    // [Preparation]
    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>::GetUnitCube();

    const T EXPECTED_VALUE_FOR_A = HEXAHEDRON.A;
    const T EXPECTED_VALUE_FOR_B = HEXAHEDRON.B;
    const T EXPECTED_VALUE_FOR_C = HEXAHEDRON.C;
    const T EXPECTED_VALUE_FOR_D = HEXAHEDRON.D;
    const T EXPECTED_VALUE_FOR_E = HEXAHEDRON.E;
    const T EXPECTED_VALUE_FOR_F = HEXAHEDRON.F;
    const T EXPECTED_VALUE_FOR_G = HEXAHEDRON.G;
    const T EXPECTED_VALUE_FOR_H = HEXAHEDRON.H;

    const float_z TRANSLATION_X = SFloat::_0;
    const float_z TRANSLATION_Y = SFloat::_0;
    const float_z TRANSLATION_Z = SFloat::_0;

	// [Execution]
    Hexahedron<T> returnedHexahedron = HEXAHEDRON.Translate(TRANSLATION_X, TRANSLATION_Y, TRANSLATION_Z);

    // [Verification]
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that a common hexahedron is correctly scaled using common scaling vector.
/// </summary>
ZTEST_CASE_TEMPLATE ( Scale1_CommonHexahedronIsCorrectlyScaledWhenUsingCommonVector_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1,  SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3,  SFloat::_4, SFloat::_2, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_2,  SFloat::_3, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_D[] = { SFloat::_4,  SFloat::_5, SFloat::_6, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_E[] = { SFloat::_3,  SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_F[] = { SFloat::_4,  SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_G[] = { -SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_H[] = { SFloat::_0,  SFloat::_1, SFloat::_4, SFloat::_1 };

    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>(T(VECTOR_COMPONENTS_A),
                                                     T(VECTOR_COMPONENTS_B),
                                                     T(VECTOR_COMPONENTS_C),
                                                     T(VECTOR_COMPONENTS_D),
                                                     T(VECTOR_COMPONENTS_E),
                                                     T(VECTOR_COMPONENTS_F),
                                                     T(VECTOR_COMPONENTS_G),
                                                     T(VECTOR_COMPONENTS_H));

    const float_z EXPECTED_VECTOR_COMPONENTS_A[] = { SFloat::_1,  SFloat::_4,  SFloat::_9,   SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_B[] = { SFloat::_3,  SFloat::_8,  SFloat::_6,   SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_C[] = { SFloat::_2,  SFloat::_6,  SFloat::_9,   SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_D[] = { SFloat::_4,  SFloat::_10, (float_z)18.0, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_E[] = { SFloat::_3,  SFloat::_4,  SFloat::_9,   SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_F[] = { SFloat::_4,  SFloat::_2,  SFloat::_9,   SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_G[] = { -SFloat::_1, SFloat::_4,  (float_z)12.0, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_H[] = { SFloat::_0,  SFloat::_2,  (float_z)12.0, SFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(EXPECTED_VECTOR_COMPONENTS_C);
    const T EXPECTED_VALUE_FOR_D(EXPECTED_VECTOR_COMPONENTS_D);
    const T EXPECTED_VALUE_FOR_E(EXPECTED_VECTOR_COMPONENTS_E);
    const T EXPECTED_VALUE_FOR_F(EXPECTED_VECTOR_COMPONENTS_F);
    const T EXPECTED_VALUE_FOR_G(EXPECTED_VECTOR_COMPONENTS_G);
    const T EXPECTED_VALUE_FOR_H(EXPECTED_VECTOR_COMPONENTS_H);

    const Vector3 SCALE = Vector3(SFloat::_1, SFloat::_2, SFloat::_3);

	// [Execution]
    Hexahedron<T> returnedHexahedron = HEXAHEDRON.Scale(SCALE);

    // [Verification]
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that a hexahedron is not scaled when scale is a vector of ones.
/// </summary>
ZTEST_CASE_TEMPLATE ( Scale1_HexahedronIsNotScaledWhenVectorComponentsEqualOne_Test, TTemplateTypes )
{
    // [Preparation]
    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>::GetUnitCube();

    const T EXPECTED_VALUE_FOR_A = HEXAHEDRON.A;
    const T EXPECTED_VALUE_FOR_B = HEXAHEDRON.B;
    const T EXPECTED_VALUE_FOR_C = HEXAHEDRON.C;
    const T EXPECTED_VALUE_FOR_D = HEXAHEDRON.D;
    const T EXPECTED_VALUE_FOR_E = HEXAHEDRON.E;
    const T EXPECTED_VALUE_FOR_F = HEXAHEDRON.F;
    const T EXPECTED_VALUE_FOR_G = HEXAHEDRON.G;
    const T EXPECTED_VALUE_FOR_H = HEXAHEDRON.H;

    const Vector3 SCALE = Vector3::GetVectorOfOnes();

	// [Execution]
    Hexahedron<T> returnedHexahedron = HEXAHEDRON.Scale(SCALE);

    // [Verification]
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that the vertices of the hexahedron are moved to the coordinate origin when the vector is null.
/// </summary>
ZTEST_CASE_TEMPLATE ( Scale1_VerticesAreMovedToCoordinateOriginWhenVectorIsNull_Test, TTemplateTypes )
{
    // [Preparation]
    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>::GetUnitCube();

    const float_z NULL_VECTOR_COMPONENTS[] = {SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1};
    const T COORDINATE_ORIGIN = T(NULL_VECTOR_COMPONENTS);

    const Vector3 SCALE = Vector3::GetNullVector();

	// [Execution]
    Hexahedron<T> returnedHexahedron = HEXAHEDRON.Scale(SCALE);

    // [Verification]
    BOOST_CHECK(returnedHexahedron.A == COORDINATE_ORIGIN);
    BOOST_CHECK(returnedHexahedron.B == COORDINATE_ORIGIN);
    BOOST_CHECK(returnedHexahedron.C == COORDINATE_ORIGIN);
    BOOST_CHECK(returnedHexahedron.D == COORDINATE_ORIGIN);
    BOOST_CHECK(returnedHexahedron.E == COORDINATE_ORIGIN);
    BOOST_CHECK(returnedHexahedron.F == COORDINATE_ORIGIN);
    BOOST_CHECK(returnedHexahedron.G == COORDINATE_ORIGIN);
    BOOST_CHECK(returnedHexahedron.H == COORDINATE_ORIGIN);
}

/// <summary>
/// Checks that a common hexahedron is correctly scaled using common scaling vector.
/// </summary>
ZTEST_CASE_TEMPLATE ( Scale2_CommonHexahedronIsCorrectlyScaledWhenUsingCommonVector_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1,  SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3,  SFloat::_4, SFloat::_2, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_2,  SFloat::_3, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_D[] = { SFloat::_4,  SFloat::_5, SFloat::_6, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_E[] = { SFloat::_3,  SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_F[] = { SFloat::_4,  SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_G[] = { -SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_H[] = { SFloat::_0,  SFloat::_1, SFloat::_4, SFloat::_1 };

    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>(T(VECTOR_COMPONENTS_A),
                                                     T(VECTOR_COMPONENTS_B),
                                                     T(VECTOR_COMPONENTS_C),
                                                     T(VECTOR_COMPONENTS_D),
                                                     T(VECTOR_COMPONENTS_E),
                                                     T(VECTOR_COMPONENTS_F),
                                                     T(VECTOR_COMPONENTS_G),
                                                     T(VECTOR_COMPONENTS_H));

    const float_z EXPECTED_VECTOR_COMPONENTS_A[] = { SFloat::_1,  SFloat::_4,  SFloat::_9,   SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_B[] = { SFloat::_3,  SFloat::_8,  SFloat::_6,   SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_C[] = { SFloat::_2,  SFloat::_6,  SFloat::_9,   SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_D[] = { SFloat::_4,  SFloat::_10, (float_z)18.0, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_E[] = { SFloat::_3,  SFloat::_4,  SFloat::_9,   SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_F[] = { SFloat::_4,  SFloat::_2,  SFloat::_9,   SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_G[] = { -SFloat::_1, SFloat::_4,  (float_z)12.0, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_H[] = { SFloat::_0,  SFloat::_2,  (float_z)12.0, SFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(EXPECTED_VECTOR_COMPONENTS_C);
    const T EXPECTED_VALUE_FOR_D(EXPECTED_VECTOR_COMPONENTS_D);
    const T EXPECTED_VALUE_FOR_E(EXPECTED_VECTOR_COMPONENTS_E);
    const T EXPECTED_VALUE_FOR_F(EXPECTED_VECTOR_COMPONENTS_F);
    const T EXPECTED_VALUE_FOR_G(EXPECTED_VECTOR_COMPONENTS_G);
    const T EXPECTED_VALUE_FOR_H(EXPECTED_VECTOR_COMPONENTS_H);

    const float_z SCALE_X = SFloat::_1;
    const float_z SCALE_Y = SFloat::_2;
    const float_z SCALE_Z = SFloat::_3;

	// [Execution]
    Hexahedron<T> returnedHexahedron = HEXAHEDRON.Scale(SCALE_X, SCALE_Y, SCALE_Z);

    // [Verification]
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that a hexahedron is not scaled when scale is a vector of ones.
/// </summary>
ZTEST_CASE_TEMPLATE ( Scale2_HexahedronIsNotScaledWhenVectorComponentsEqualOne_Test, TTemplateTypes )
{
    // [Preparation]
    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>::GetUnitCube();

    const T EXPECTED_VALUE_FOR_A = HEXAHEDRON.A;
    const T EXPECTED_VALUE_FOR_B = HEXAHEDRON.B;
    const T EXPECTED_VALUE_FOR_C = HEXAHEDRON.C;
    const T EXPECTED_VALUE_FOR_D = HEXAHEDRON.D;
    const T EXPECTED_VALUE_FOR_E = HEXAHEDRON.E;
    const T EXPECTED_VALUE_FOR_F = HEXAHEDRON.F;
    const T EXPECTED_VALUE_FOR_G = HEXAHEDRON.G;
    const T EXPECTED_VALUE_FOR_H = HEXAHEDRON.H;

    const float_z SCALE_X = SFloat::_1;
    const float_z SCALE_Y = SFloat::_1;
    const float_z SCALE_Z = SFloat::_1;

	// [Execution]
    Hexahedron<T> returnedHexahedron = HEXAHEDRON.Scale(SCALE_X, SCALE_Y, SCALE_Z);

    // [Verification]
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that the vertices of the hexahedron are moved to the coordinate origin when the vector is null.
/// </summary>
ZTEST_CASE_TEMPLATE ( Scale2_VerticesAreMovedToCoordinateOriginWhenVectorIsNull_Test, TTemplateTypes )
{
    // [Preparation]
    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>::GetUnitCube();

    const float_z NULL_VECTOR_COMPONENTS[] = {SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1};
    const T COORDINATE_ORIGIN = T(NULL_VECTOR_COMPONENTS);

    const float_z SCALE_X = SFloat::_0;
    const float_z SCALE_Y = SFloat::_0;
    const float_z SCALE_Z = SFloat::_0;

	// [Execution]
    Hexahedron<T> returnedHexahedron = HEXAHEDRON.Scale(SCALE_X, SCALE_Y, SCALE_Z);

    // [Verification]
    BOOST_CHECK(returnedHexahedron.A == COORDINATE_ORIGIN);
    BOOST_CHECK(returnedHexahedron.B == COORDINATE_ORIGIN);
    BOOST_CHECK(returnedHexahedron.C == COORDINATE_ORIGIN);
    BOOST_CHECK(returnedHexahedron.D == COORDINATE_ORIGIN);
    BOOST_CHECK(returnedHexahedron.E == COORDINATE_ORIGIN);
    BOOST_CHECK(returnedHexahedron.F == COORDINATE_ORIGIN);
    BOOST_CHECK(returnedHexahedron.G == COORDINATE_ORIGIN);
    BOOST_CHECK(returnedHexahedron.H == COORDINATE_ORIGIN);
}

/// <summary>
/// Checks that a common hexahedron is correctly scaled using common scaling vector.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot1_CommonHexahedronIsCorrectlyScaledWhenUsingCommonVector_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1,  SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3,  SFloat::_4, SFloat::_2, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_2,  SFloat::_3, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_D[] = { SFloat::_4,  SFloat::_5, SFloat::_6, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_E[] = { SFloat::_3,  SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_F[] = { SFloat::_4,  SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_G[] = { -SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_H[] = { SFloat::_0,  SFloat::_1, SFloat::_4, SFloat::_1 };

    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>(T(VECTOR_COMPONENTS_A),
                                                     T(VECTOR_COMPONENTS_B),
                                                     T(VECTOR_COMPONENTS_C),
                                                     T(VECTOR_COMPONENTS_D),
                                                     T(VECTOR_COMPONENTS_E),
                                                     T(VECTOR_COMPONENTS_F),
                                                     T(VECTOR_COMPONENTS_G),
                                                     T(VECTOR_COMPONENTS_H));

    const float_z EXPECTED_VECTOR_COMPONENTS_A[] = { SFloat::_1,  SFloat::_2,  SFloat::_3,   SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_B[] = { SFloat::_3,  SFloat::_6,  SFloat::_0,   SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_C[] = { SFloat::_2,  SFloat::_4,  SFloat::_3,   SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_D[] = { SFloat::_4,  SFloat::_8, (float_z)12.0, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_E[] = { SFloat::_3,  SFloat::_2,  SFloat::_3,   SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_F[] = { SFloat::_4,  SFloat::_0,  SFloat::_3,   SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_G[] = { -SFloat::_1, SFloat::_2,  SFloat::_6, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_H[] = { SFloat::_0,  SFloat::_0,  SFloat::_6, SFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(EXPECTED_VECTOR_COMPONENTS_C);
    const T EXPECTED_VALUE_FOR_D(EXPECTED_VECTOR_COMPONENTS_D);
    const T EXPECTED_VALUE_FOR_E(EXPECTED_VECTOR_COMPONENTS_E);
    const T EXPECTED_VALUE_FOR_F(EXPECTED_VECTOR_COMPONENTS_F);
    const T EXPECTED_VALUE_FOR_G(EXPECTED_VECTOR_COMPONENTS_G);
    const T EXPECTED_VALUE_FOR_H(EXPECTED_VECTOR_COMPONENTS_H);

    const Vector3 SCALE = Vector3(SFloat::_1, SFloat::_2, SFloat::_3);

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// [Execution]
    Hexahedron<T> returnedHexahedron = HEXAHEDRON.ScaleWithPivot(SCALE, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that a hexahedron is not scaled when scale is a vector of ones.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot1_HexahedronIsNotScaledWhenVectorComponentsEqualOne_Test, TTemplateTypes )
{
    // [Preparation]
    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>::GetUnitCube();

    const T EXPECTED_VALUE_FOR_A = HEXAHEDRON.A;
    const T EXPECTED_VALUE_FOR_B = HEXAHEDRON.B;
    const T EXPECTED_VALUE_FOR_C = HEXAHEDRON.C;
    const T EXPECTED_VALUE_FOR_D = HEXAHEDRON.D;
    const T EXPECTED_VALUE_FOR_E = HEXAHEDRON.E;
    const T EXPECTED_VALUE_FOR_F = HEXAHEDRON.F;
    const T EXPECTED_VALUE_FOR_G = HEXAHEDRON.G;
    const T EXPECTED_VALUE_FOR_H = HEXAHEDRON.H;

    const Vector3 SCALE = Vector3::GetVectorOfOnes();

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// [Execution]
    Hexahedron<T> returnedHexahedron = HEXAHEDRON.ScaleWithPivot(SCALE, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that the vertices of the hexahedron are moved to the coordinate origin when the vector is null.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot1_VerticesAreMovedToCoordinateOriginWhenVectorIsNull_Test, TTemplateTypes )
{
    // [Preparation]
    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>::GetUnitCube();

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const Vector3 SCALE = Vector3::GetNullVector();

	// [Execution]
    Hexahedron<T> returnedHexahedron = HEXAHEDRON.ScaleWithPivot(SCALE, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedHexahedron.A == PIVOT_POINT);
    BOOST_CHECK(returnedHexahedron.B == PIVOT_POINT);
    BOOST_CHECK(returnedHexahedron.C == PIVOT_POINT);
    BOOST_CHECK(returnedHexahedron.D == PIVOT_POINT);
    BOOST_CHECK(returnedHexahedron.E == PIVOT_POINT);
    BOOST_CHECK(returnedHexahedron.F == PIVOT_POINT);
    BOOST_CHECK(returnedHexahedron.G == PIVOT_POINT);
    BOOST_CHECK(returnedHexahedron.H == PIVOT_POINT);
}

/// <summary>
/// Checks that a common hexahedron is correctly scaled using common scaling vector.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot2_CommonHexahedronIsCorrectlyScaledWhenUsingCommonVector_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1,  SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3,  SFloat::_4, SFloat::_2, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_2,  SFloat::_3, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_D[] = { SFloat::_4,  SFloat::_5, SFloat::_6, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_E[] = { SFloat::_3,  SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_F[] = { SFloat::_4,  SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_G[] = { -SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_H[] = { SFloat::_0,  SFloat::_1, SFloat::_4, SFloat::_1 };

    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>(T(VECTOR_COMPONENTS_A),
                                                     T(VECTOR_COMPONENTS_B),
                                                     T(VECTOR_COMPONENTS_C),
                                                     T(VECTOR_COMPONENTS_D),
                                                     T(VECTOR_COMPONENTS_E),
                                                     T(VECTOR_COMPONENTS_F),
                                                     T(VECTOR_COMPONENTS_G),
                                                     T(VECTOR_COMPONENTS_H));

    const float_z EXPECTED_VECTOR_COMPONENTS_A[] = { SFloat::_1,  SFloat::_2,  SFloat::_3,   SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_B[] = { SFloat::_3,  SFloat::_6,  SFloat::_0,   SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_C[] = { SFloat::_2,  SFloat::_4,  SFloat::_3,   SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_D[] = { SFloat::_4,  SFloat::_8, (float_z)12.0, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_E[] = { SFloat::_3,  SFloat::_2,  SFloat::_3,   SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_F[] = { SFloat::_4,  SFloat::_0,  SFloat::_3,   SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_G[] = { -SFloat::_1, SFloat::_2,  SFloat::_6, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_H[] = { SFloat::_0,  SFloat::_0,  SFloat::_6, SFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(EXPECTED_VECTOR_COMPONENTS_C);
    const T EXPECTED_VALUE_FOR_D(EXPECTED_VECTOR_COMPONENTS_D);
    const T EXPECTED_VALUE_FOR_E(EXPECTED_VECTOR_COMPONENTS_E);
    const T EXPECTED_VALUE_FOR_F(EXPECTED_VECTOR_COMPONENTS_F);
    const T EXPECTED_VALUE_FOR_G(EXPECTED_VECTOR_COMPONENTS_G);
    const T EXPECTED_VALUE_FOR_H(EXPECTED_VECTOR_COMPONENTS_H);

    const float_z SCALE_X = SFloat::_1;
    const float_z SCALE_Y = SFloat::_2;
    const float_z SCALE_Z = SFloat::_3;

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// [Execution]
    Hexahedron<T> returnedHexahedron = HEXAHEDRON.ScaleWithPivot(SCALE_X, SCALE_Y, SCALE_Z, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that a hexahedron is not scaled when scale is a vector of ones.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot2_HexahedronIsNotScaledWhenVectorComponentsEqualOne_Test, TTemplateTypes )
{
    // [Preparation]
    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>::GetUnitCube();

    const T EXPECTED_VALUE_FOR_A = HEXAHEDRON.A;
    const T EXPECTED_VALUE_FOR_B = HEXAHEDRON.B;
    const T EXPECTED_VALUE_FOR_C = HEXAHEDRON.C;
    const T EXPECTED_VALUE_FOR_D = HEXAHEDRON.D;
    const T EXPECTED_VALUE_FOR_E = HEXAHEDRON.E;
    const T EXPECTED_VALUE_FOR_F = HEXAHEDRON.F;
    const T EXPECTED_VALUE_FOR_G = HEXAHEDRON.G;
    const T EXPECTED_VALUE_FOR_H = HEXAHEDRON.H;

    const float_z SCALE_X = SFloat::_1;
    const float_z SCALE_Y = SFloat::_1;
    const float_z SCALE_Z = SFloat::_1;

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// [Execution]
    Hexahedron<T> returnedHexahedron = HEXAHEDRON.ScaleWithPivot(SCALE_X, SCALE_Y, SCALE_Z, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that the vertices of the hexahedron are moved to the coordinate origin when the vector is null.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot2_VerticesAreMovedToCoordinateOriginWhenVectorIsNull_Test, TTemplateTypes )
{
    // [Preparation]
    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>::GetUnitCube();

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const float_z SCALE_X = SFloat::_0;
    const float_z SCALE_Y = SFloat::_0;
    const float_z SCALE_Z = SFloat::_0;

	// [Execution]
    Hexahedron<T> returnedHexahedron = HEXAHEDRON.ScaleWithPivot(SCALE_X, SCALE_Y, SCALE_Z, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedHexahedron.A == PIVOT_POINT);
    BOOST_CHECK(returnedHexahedron.B == PIVOT_POINT);
    BOOST_CHECK(returnedHexahedron.C == PIVOT_POINT);
    BOOST_CHECK(returnedHexahedron.D == PIVOT_POINT);
    BOOST_CHECK(returnedHexahedron.E == PIVOT_POINT);
    BOOST_CHECK(returnedHexahedron.F == PIVOT_POINT);
    BOOST_CHECK(returnedHexahedron.G == PIVOT_POINT);
    BOOST_CHECK(returnedHexahedron.H == PIVOT_POINT);
}

/// <summary>
/// Checks that it returns the expected list of planes from a common hexahedron.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetPlanes_ReturnsExpectedPlanesFromCommonHexahedron_Test, TTemplateTypes )
{
    //    A --- D
    //   /|    /|
    //  B --- C |
    //  | E --| F
    //  |/    |/
    //  H --- G


    // [Preparation]
    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>::GetUnitCube();

    const Plane EXPECTED_PLANE_ABCD = Plane(SFloat::_0,  SFloat::_1,  SFloat::_0, -SFloat::_0_5);
    const Plane EXPECTED_PLANE_EFGH = Plane(SFloat::_0,  -SFloat::_1, SFloat::_0, -SFloat::_0_5);
    const Plane EXPECTED_PLANE_AEFD = Plane(SFloat::_0,  SFloat::_0,  SFloat::_1, -SFloat::_0_5);
    const Plane EXPECTED_PLANE_ABHE = Plane(-SFloat::_1, SFloat::_0,  SFloat::_0, -SFloat::_0_5);
    const Plane EXPECTED_PLANE_BCGH = Plane(SFloat::_0,  SFloat::_0, -SFloat::_1, -SFloat::_0_5);
    const Plane EXPECTED_PLANE_CDFG = Plane(SFloat::_1,  SFloat::_0,  SFloat::_0, -SFloat::_0_5);

	// [Execution]
    Plane arOutputPlanes[6];
    HEXAHEDRON.GetPlanes(arOutputPlanes);

    // [Verification]
    BOOST_CHECK(arOutputPlanes[0] == EXPECTED_PLANE_ABCD);
    BOOST_CHECK(arOutputPlanes[1] == EXPECTED_PLANE_EFGH);
    BOOST_CHECK(arOutputPlanes[2] == EXPECTED_PLANE_AEFD);
    BOOST_CHECK(arOutputPlanes[3] == EXPECTED_PLANE_ABHE);
    BOOST_CHECK(arOutputPlanes[4] == EXPECTED_PLANE_BCGH);
    BOOST_CHECK(arOutputPlanes[5] == EXPECTED_PLANE_CDFG);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when all the vertices of the hexahedron coincide.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetPlanes_AssertionFailsWhenAllVerticesCoincide_Test, TTemplateTypes )
{

    // [Preparation]
    const float_z POINT_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4 };
    const T POINT = T(POINT_COMPONENTS);
    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>(POINT, POINT, POINT, POINT, POINT, POINT, POINT, POINT);
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;
    Plane arOutputPlanes[6];

    try
    {
        HEXAHEDRON.GetPlanes(arOutputPlanes);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the list of planes is null.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetPlanes_AssertionFailsWhenListOfPlanesIsNull_Test, TTemplateTypes )
{

    // [Preparation]
    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>::GetUnitCube();
    const bool ASSERTION_FAILED = true;
    Plane* pNullList = null_z;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        HEXAHEDRON.GetPlanes(pNullList);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that it returns True when a common point is inside the hexahedron.
/// </summary>
ZTEST_CASE_TEMPLATE ( Contains_ReturnsTrueWhenCommonPointIsInsideTheHexahedron_Test, TTemplateTypes )
{
    //    A --- D
    //   /|    /|
    //  B --- C |
    //  | E --| F
    //  |/    |/
    //  H --- G

    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_2, SFloat::_3, SFloat::_2, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_4, SFloat::_3, SFloat::_2, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_D[] = { SFloat::_4, SFloat::_4, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_E[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_F[] = { SFloat::_4, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_G[] = { SFloat::_4, SFloat::_1, SFloat::_1, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_H[] = { SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_1 };

    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>(T(VECTOR_COMPONENTS_A),
                                                     T(VECTOR_COMPONENTS_B),
                                                     T(VECTOR_COMPONENTS_C),
                                                     T(VECTOR_COMPONENTS_D),
                                                     T(VECTOR_COMPONENTS_E),
                                                     T(VECTOR_COMPONENTS_F),
                                                     T(VECTOR_COMPONENTS_G),
                                                     T(VECTOR_COMPONENTS_H));

    const T POINT = HEXAHEDRON.A.Lerp(SFloat::_0_5, HEXAHEDRON.G);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = HEXAHEDRON.Contains(POINT);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True the point belongs to one of the faces of the hexahedron.
/// </summary>
ZTEST_CASE_TEMPLATE ( Contains_ReturnsTrueWhenPointBelongsToAFaceOfHexahedron_Test, TTemplateTypes )
{
    //    A --- D
    //   /|    /|
    //  B --- C |
    //  | E --| F
    //  |/    |/
    //  H --- G

    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_2, SFloat::_3, SFloat::_2, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_4, SFloat::_3, SFloat::_2, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_D[] = { SFloat::_4, SFloat::_4, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_E[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_F[] = { SFloat::_4, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_G[] = { SFloat::_4, SFloat::_1, SFloat::_1, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_H[] = { SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_1 };

    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>(T(VECTOR_COMPONENTS_A),
                                                     T(VECTOR_COMPONENTS_B),
                                                     T(VECTOR_COMPONENTS_C),
                                                     T(VECTOR_COMPONENTS_D),
                                                     T(VECTOR_COMPONENTS_E),
                                                     T(VECTOR_COMPONENTS_F),
                                                     T(VECTOR_COMPONENTS_G),
                                                     T(VECTOR_COMPONENTS_H));

    const T POINT_ABCD = HEXAHEDRON.A.Lerp(SFloat::_0_5, HEXAHEDRON.C);
    const T POINT_EFGH = HEXAHEDRON.E.Lerp(SFloat::_0_5, HEXAHEDRON.G);
    const T POINT_AEFD = HEXAHEDRON.A.Lerp(SFloat::_0_5, HEXAHEDRON.F);
    const T POINT_ABHE = HEXAHEDRON.A.Lerp(SFloat::_0_5, HEXAHEDRON.H);
    const T POINT_BCGH = HEXAHEDRON.B.Lerp(SFloat::_0_5, HEXAHEDRON.G);
    const T POINT_CDFG = HEXAHEDRON.C.Lerp(SFloat::_0_5, HEXAHEDRON.F);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultABCD = HEXAHEDRON.Contains(POINT_ABCD);
    bool bResultEFGH = HEXAHEDRON.Contains(POINT_EFGH);
    bool bResultAEFD = HEXAHEDRON.Contains(POINT_AEFD);
    bool bResultABHE = HEXAHEDRON.Contains(POINT_ABHE);
    bool bResultBCGH = HEXAHEDRON.Contains(POINT_BCGH);
    bool bResultCDFG = HEXAHEDRON.Contains(POINT_CDFG);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultABCD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultEFGH, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultAEFD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultABHE, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultBCGH, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultCDFG, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True the point belongs to one of the edges of the hexahedron.
/// </summary>
ZTEST_CASE_TEMPLATE ( Contains_ReturnsTrueWhenPointBelongsToAnEdgeOfHexahedron_Test, TTemplateTypes )
{
    //    A --- D
    //   /|    /|
    //  B --- C |
    //  | E --| F
    //  |/    |/
    //  H --- G

    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_2, SFloat::_3, SFloat::_2, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_4, SFloat::_3, SFloat::_2, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_D[] = { SFloat::_4, SFloat::_3, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_E[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_F[] = { SFloat::_4, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_G[] = { SFloat::_4, SFloat::_1, SFloat::_0, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_H[] = { SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_1 };

    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>(T(VECTOR_COMPONENTS_A),
                                                     T(VECTOR_COMPONENTS_B),
                                                     T(VECTOR_COMPONENTS_C),
                                                     T(VECTOR_COMPONENTS_D),
                                                     T(VECTOR_COMPONENTS_E),
                                                     T(VECTOR_COMPONENTS_F),
                                                     T(VECTOR_COMPONENTS_G),
                                                     T(VECTOR_COMPONENTS_H));

    const T POINT_AB = HEXAHEDRON.A.Lerp(SFloat::_0_5, HEXAHEDRON.B);
    const T POINT_BC = HEXAHEDRON.B.Lerp(SFloat::_0_5, HEXAHEDRON.C);
    const T POINT_CD = HEXAHEDRON.C.Lerp(SFloat::_0_5, HEXAHEDRON.D);
    const T POINT_DA = HEXAHEDRON.D.Lerp(SFloat::_0_5, HEXAHEDRON.A);
    const T POINT_EF = HEXAHEDRON.E.Lerp(SFloat::_0_5, HEXAHEDRON.F);
    const T POINT_FG = HEXAHEDRON.F.Lerp(SFloat::_0_5, HEXAHEDRON.G);
    const T POINT_GH = HEXAHEDRON.G.Lerp(SFloat::_0_5, HEXAHEDRON.H);
    const T POINT_HE = HEXAHEDRON.H.Lerp(SFloat::_0_5, HEXAHEDRON.E);
    const T POINT_AE = HEXAHEDRON.A.Lerp(SFloat::_0_5, HEXAHEDRON.E);
    const T POINT_DF = HEXAHEDRON.D.Lerp(SFloat::_0_5, HEXAHEDRON.F);
    const T POINT_BH = HEXAHEDRON.B.Lerp(SFloat::_0_5, HEXAHEDRON.H);
    const T POINT_CG = HEXAHEDRON.C.Lerp(SFloat::_0_5, HEXAHEDRON.G);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultAB = HEXAHEDRON.Contains(POINT_AB);
    bool bResultBC = HEXAHEDRON.Contains(POINT_BC);
    bool bResultCD = HEXAHEDRON.Contains(POINT_CD);
    bool bResultDA = HEXAHEDRON.Contains(POINT_DA);
    bool bResultEF = HEXAHEDRON.Contains(POINT_EF);
    bool bResultFG = HEXAHEDRON.Contains(POINT_FG);
    bool bResultGH = HEXAHEDRON.Contains(POINT_GH);
    bool bResultHE = HEXAHEDRON.Contains(POINT_HE);
    bool bResultAE = HEXAHEDRON.Contains(POINT_AE);
    bool bResultDF = HEXAHEDRON.Contains(POINT_DF);
    bool bResultBH = HEXAHEDRON.Contains(POINT_BH);
    bool bResultCG = HEXAHEDRON.Contains(POINT_CG);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultAB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultBC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultCD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultDA, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultEF, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultFG, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultGH, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultHE, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultAE, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultDF, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultBH, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultCG, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when a common point is outside the hexahedron.
/// </summary>
ZTEST_CASE_TEMPLATE ( Contains_ReturnsFalseWhenCommonPointIsOutsideTheHexahedron_Test, TTemplateTypes )
{
    //    A --- D
    //   /|    /|
    //  B --- C |
    //  | E --| F
    //  |/    |/
    //  H --- G

    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_2, SFloat::_3, SFloat::_2, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_4, SFloat::_3, SFloat::_2, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_D[] = { SFloat::_4, SFloat::_3, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_E[] = { SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_F[] = { SFloat::_4, SFloat::_1, SFloat::_0, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_G[] = { SFloat::_4, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_H[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_1 };

    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>(T(VECTOR_COMPONENTS_A),
                                                     T(VECTOR_COMPONENTS_B),
                                                     T(VECTOR_COMPONENTS_C),
                                                     T(VECTOR_COMPONENTS_D),
                                                     T(VECTOR_COMPONENTS_E),
                                                     T(VECTOR_COMPONENTS_F),
                                                     T(VECTOR_COMPONENTS_G),
                                                     T(VECTOR_COMPONENTS_H));

    const T POINT = HEXAHEDRON.A.Lerp(SFloat::_2, HEXAHEDRON.G);
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = HEXAHEDRON.Contains(POINT);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True the point coincides with a vertex of the hexahedron.
/// </summary>
ZTEST_CASE_TEMPLATE ( Contains_ReturnsTrueWhenPointCoincidesWithVertex_Test, TTemplateTypes )
{
    //    A --- D
    //   /|    /|
    //  B --- C |
    //  | E --| F
    //  |/    |/
    //  H --- G

    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_2, SFloat::_3, SFloat::_2, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_4, SFloat::_3, SFloat::_2, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_D[] = { SFloat::_4, SFloat::_3, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_E[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_F[] = { SFloat::_4, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_G[] = { SFloat::_4, SFloat::_1, SFloat::_0, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_H[] = { SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_1 };

    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>(T(VECTOR_COMPONENTS_A),
                                                     T(VECTOR_COMPONENTS_B),
                                                     T(VECTOR_COMPONENTS_C),
                                                     T(VECTOR_COMPONENTS_D),
                                                     T(VECTOR_COMPONENTS_E),
                                                     T(VECTOR_COMPONENTS_F),
                                                     T(VECTOR_COMPONENTS_G),
                                                     T(VECTOR_COMPONENTS_H));

    const T POINT_A = HEXAHEDRON.A;
    const T POINT_B = HEXAHEDRON.B;
    const T POINT_C = HEXAHEDRON.C;
    const T POINT_D = HEXAHEDRON.D;
    const T POINT_E = HEXAHEDRON.E;
    const T POINT_F = HEXAHEDRON.F;
    const T POINT_G = HEXAHEDRON.G;
    const T POINT_H = HEXAHEDRON.H;

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultA = HEXAHEDRON.Contains(POINT_A);
    bool bResultB = HEXAHEDRON.Contains(POINT_B);
    bool bResultC = HEXAHEDRON.Contains(POINT_C);
    bool bResultD = HEXAHEDRON.Contains(POINT_D);
    bool bResultE = HEXAHEDRON.Contains(POINT_E);
    bool bResultF = HEXAHEDRON.Contains(POINT_F);
    bool bResultG = HEXAHEDRON.Contains(POINT_G);
    bool bResultH = HEXAHEDRON.Contains(POINT_H);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultA, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultE, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultF, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultG, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH, EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when all the vertices of the hexahedron coincide.
/// </summary>
ZTEST_CASE_TEMPLATE ( Contains_AssertionFailsWhenAllVerticesCoincide_Test, TTemplateTypes )
{

    // [Preparation]
    const float_z POINT_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4 };
    const T POINT = T(POINT_COMPONENTS);
    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>(POINT, POINT, POINT, POINT, POINT, POINT, POINT, POINT);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        HEXAHEDRON.Contains(POINT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that it returns "both sides" when the hexahedron and the plane intersect.
/// </summary>
ZTEST_CASE_TEMPLATE ( SpaceRelation_ReturnsBothSidesWhenHexahedronAndPlaneIntersect_Test, TTemplateTypes )
{

    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_2, SFloat::_3, SFloat::_2, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_4, SFloat::_3, SFloat::_2, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_D[] = { SFloat::_4, SFloat::_3, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_E[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_F[] = { SFloat::_4, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_G[] = { SFloat::_4, SFloat::_1, SFloat::_1, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_H[] = { SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_1 };

    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>(T(VECTOR_COMPONENTS_A),
                                                     T(VECTOR_COMPONENTS_B),
                                                     T(VECTOR_COMPONENTS_C),
                                                     T(VECTOR_COMPONENTS_D),
                                                     T(VECTOR_COMPONENTS_E),
                                                     T(VECTOR_COMPONENTS_F),
                                                     T(VECTOR_COMPONENTS_G),
                                                     T(VECTOR_COMPONENTS_H));

    const BasePlane PLANE = BasePlane(SFloat::_0, SFloat::_1, SFloat::_0, -SFloat::_2);

    const ESpaceRelation EXPECTED_RESULT = ESpaceRelation::E_BothSides;

	// [Execution]
    ESpaceRelation eResult = HEXAHEDRON.SpaceRelation(PLANE);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "positive side" when the hexahedron is completely in the positive side of the plane.
/// </summary>
ZTEST_CASE_TEMPLATE ( SpaceRelation_ReturnsPositiveSideWhenHexahedronIsInPositiveSide_Test, TTemplateTypes )
{

    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_2, SFloat::_3, SFloat::_2, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_4, SFloat::_3, SFloat::_2, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_D[] = { SFloat::_4, SFloat::_4, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_E[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_F[] = { SFloat::_4, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_G[] = { SFloat::_4, SFloat::_1, SFloat::_1, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_H[] = { SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_1 };

    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>(T(VECTOR_COMPONENTS_A),
                                                     T(VECTOR_COMPONENTS_B),
                                                     T(VECTOR_COMPONENTS_C),
                                                     T(VECTOR_COMPONENTS_D),
                                                     T(VECTOR_COMPONENTS_E),
                                                     T(VECTOR_COMPONENTS_F),
                                                     T(VECTOR_COMPONENTS_G),
                                                     T(VECTOR_COMPONENTS_H));

    const BasePlane PLANE = BasePlane(SFloat::_0, SFloat::_1, SFloat::_0, SFloat::_2);

    const ESpaceRelation EXPECTED_RESULT = ESpaceRelation::E_PositiveSide;

	// [Execution]
    ESpaceRelation eResult = HEXAHEDRON.SpaceRelation(PLANE);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "negative side" when the hexahedron is completely in the negtive side of the plane.
/// </summary>
ZTEST_CASE_TEMPLATE ( SpaceRelation_ReturnsNegativeSideWhenHexahedronIsInNegativeSide_Test, TTemplateTypes )
{

    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_2, SFloat::_3, SFloat::_2, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_4, SFloat::_3, SFloat::_2, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_D[] = { SFloat::_4, SFloat::_4, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_E[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_F[] = { SFloat::_4, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_G[] = { SFloat::_4, SFloat::_1, SFloat::_1, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_H[] = { SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_1 };

    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>(T(VECTOR_COMPONENTS_A),
                                                     T(VECTOR_COMPONENTS_B),
                                                     T(VECTOR_COMPONENTS_C),
                                                     T(VECTOR_COMPONENTS_D),
                                                     T(VECTOR_COMPONENTS_E),
                                                     T(VECTOR_COMPONENTS_F),
                                                     T(VECTOR_COMPONENTS_G),
                                                     T(VECTOR_COMPONENTS_H));

    const BasePlane PLANE = BasePlane(SFloat::_0, SFloat::_1, SFloat::_0, -SFloat::_10);

    const ESpaceRelation EXPECTED_RESULT = ESpaceRelation::E_NegativeSide;

	// [Execution]
    ESpaceRelation eResult = HEXAHEDRON.SpaceRelation(PLANE);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "contained" when the hexahedron is completely contained in the plane.
/// </summary>
ZTEST_CASE_TEMPLATE ( SpaceRelation_ReturnsContainedWhenHexahedronBelongsToPlane_Test, TTemplateTypes )
{

    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_2, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_2, SFloat::_1, SFloat::_2, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_4, SFloat::_1, SFloat::_2, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_D[] = { SFloat::_4, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_E[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_F[] = { SFloat::_4, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_G[] = { SFloat::_4, SFloat::_1, SFloat::_1, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_H[] = { SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_1 };

    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>(T(VECTOR_COMPONENTS_A),
                                                     T(VECTOR_COMPONENTS_B),
                                                     T(VECTOR_COMPONENTS_C),
                                                     T(VECTOR_COMPONENTS_D),
                                                     T(VECTOR_COMPONENTS_E),
                                                     T(VECTOR_COMPONENTS_F),
                                                     T(VECTOR_COMPONENTS_G),
                                                     T(VECTOR_COMPONENTS_H));

    const BasePlane PLANE = BasePlane(SFloat::_0, SFloat::_1, SFloat::_0, -SFloat::_1);

    const ESpaceRelation EXPECTED_RESULT = ESpaceRelation::E_Contained;

	// [Execution]
    ESpaceRelation eResult = HEXAHEDRON.SpaceRelation(PLANE);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "positive side" when some part of the hexahedron belongs to the plane and the rest belongs to the positive side.
/// </summary>
ZTEST_CASE_TEMPLATE ( SpaceRelation_ReturnsPositiveSideWhenSomePartOfTheHexahedronBelongsToPlaneAndTheRestToPositiveSide_Test, TTemplateTypes )
{

    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_2, SFloat::_5, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_2, SFloat::_5, SFloat::_2, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_4, SFloat::_5, SFloat::_2, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_D[] = { SFloat::_4, SFloat::_5, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_E[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_F[] = { SFloat::_4, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_G[] = { SFloat::_4, SFloat::_1, SFloat::_1, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_H[] = { SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_1 };

    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>(T(VECTOR_COMPONENTS_A),
                                                     T(VECTOR_COMPONENTS_B),
                                                     T(VECTOR_COMPONENTS_C),
                                                     T(VECTOR_COMPONENTS_D),
                                                     T(VECTOR_COMPONENTS_E),
                                                     T(VECTOR_COMPONENTS_F),
                                                     T(VECTOR_COMPONENTS_G),
                                                     T(VECTOR_COMPONENTS_H));

    const BasePlane PLANE = BasePlane(SFloat::_0, SFloat::_1, SFloat::_0, -SFloat::_1);

    const ESpaceRelation EXPECTED_RESULT = ESpaceRelation::E_PositiveSide;

	// [Execution]
    ESpaceRelation eResult = HEXAHEDRON.SpaceRelation(PLANE);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "negative side" when some part of the hexahedron belongs to the plane and the rest belongs to the negative side.
/// </summary>
ZTEST_CASE_TEMPLATE ( SpaceRelation_ReturnsNegativeSideWhenSomePartOfTheHexahedronBelongsToPlaneAndTheRestToNegativeSide_Test, TTemplateTypes )
{

    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_2, SFloat::_0, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_2, SFloat::_0, SFloat::_2, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_4, SFloat::_0, SFloat::_2, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_D[] = { SFloat::_4, SFloat::_0, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_E[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_F[] = { SFloat::_4, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_G[] = { SFloat::_4, SFloat::_1, SFloat::_1, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_H[] = { SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_1 };

    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>(T(VECTOR_COMPONENTS_A),
                                                     T(VECTOR_COMPONENTS_B),
                                                     T(VECTOR_COMPONENTS_C),
                                                     T(VECTOR_COMPONENTS_D),
                                                     T(VECTOR_COMPONENTS_E),
                                                     T(VECTOR_COMPONENTS_F),
                                                     T(VECTOR_COMPONENTS_G),
                                                     T(VECTOR_COMPONENTS_H));

    const BasePlane PLANE = BasePlane(SFloat::_0, SFloat::_1, SFloat::_0, -SFloat::_1);

    const ESpaceRelation EXPECTED_RESULT = ESpaceRelation::E_NegativeSide;

	// [Execution]
    ESpaceRelation eResult = HEXAHEDRON.SpaceRelation(PLANE);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when all the vertices of the hexahedron coincide.
/// </summary>
ZTEST_CASE_TEMPLATE ( SpaceRelation_AssertionFailsWhenAllVerticesCoincide_Test, TTemplateTypes )
{
    // [Preparation]
    const BasePlane PLANE = BasePlane(SFloat::_0, SFloat::_1, SFloat::_0, -SFloat::_1);
    const float_z POINT_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4 };
    const T POINT = T(POINT_COMPONENTS);
    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>(POINT, POINT, POINT, POINT, POINT, POINT, POINT, POINT);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        HEXAHEDRON.SpaceRelation(PLANE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the plane is null.
/// </summary>
ZTEST_CASE_TEMPLATE ( SpaceRelation_AssertionFailsWhenThePlaneIsNull_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_2, SFloat::_0, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_2, SFloat::_0, SFloat::_2, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_4, SFloat::_0, SFloat::_2, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_D[] = { SFloat::_4, SFloat::_0, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_E[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_F[] = { SFloat::_4, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_G[] = { SFloat::_4, SFloat::_1, SFloat::_1, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_H[] = { SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_1 };

    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>(T(VECTOR_COMPONENTS_A),
                                                     T(VECTOR_COMPONENTS_B),
                                                     T(VECTOR_COMPONENTS_C),
                                                     T(VECTOR_COMPONENTS_D),
                                                     T(VECTOR_COMPONENTS_E),
                                                     T(VECTOR_COMPONENTS_F),
                                                     T(VECTOR_COMPONENTS_G),
                                                     T(VECTOR_COMPONENTS_H));

    const BasePlane PLANE = BasePlane(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        HEXAHEDRON.SpaceRelation(PLANE);
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
/// Checks that a correct result is returned even when all the vertices of the hexahedron coincide.
/// </summary>
ZTEST_CASE_TEMPLATE ( SpaceRelation_CorrectResultIsReturnedWhenAllVerticesCoincide_Test, TTemplateTypes )
{
    // Note: This is a special test that checks too many things (which is incorrect in a unit test) just to assure that the 
    //       method behaves as expected when assertions are disabled.


    // [Preparation]
    const BasePlane PLANE = BasePlane(SFloat::_0, SFloat::_1, SFloat::_0, -SFloat::_1);

    const float_z POINT_COMPONENTS_POSITIVE[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4 };
    const T POINT_POSITIVE = T(POINT_COMPONENTS_POSITIVE);
    const Hexahedron<T> HEXAHEDRON_POSITIVE  = Hexahedron<T>(POINT_POSITIVE, POINT_POSITIVE, POINT_POSITIVE, POINT_POSITIVE, POINT_POSITIVE, POINT_POSITIVE, POINT_POSITIVE, POINT_POSITIVE);

    const float_z POINT_COMPONENTS_NEGATIVE[] = { -SFloat::_1, -SFloat::_2, -SFloat::_3, -SFloat::_4 };
    const T POINT_NEGATIVE = T(POINT_COMPONENTS_NEGATIVE);
    const Hexahedron<T> HEXAHEDRON_NEGATIVE  = Hexahedron<T>(POINT_NEGATIVE, POINT_NEGATIVE, POINT_NEGATIVE, POINT_NEGATIVE, POINT_NEGATIVE, POINT_NEGATIVE, POINT_NEGATIVE, POINT_NEGATIVE);

    const float_z POINT_COMPONENTS_CONTAINED[] = { SFloat::_0, SFloat::_1, SFloat::_0, SFloat::_4 };
    const T POINT_CONTAINED = T(POINT_COMPONENTS_CONTAINED);
    const Hexahedron<T> HEXAHEDRON_CONTAINED = Hexahedron<T>(POINT_CONTAINED, POINT_CONTAINED, POINT_CONTAINED, POINT_CONTAINED, POINT_CONTAINED, POINT_CONTAINED, POINT_CONTAINED, POINT_CONTAINED);

    const ESpaceRelation EXPECTED_RESULT_POSITIVE = ESpaceRelation::E_PositiveSide;
    const ESpaceRelation EXPECTED_RESULT_NEGATIVE = ESpaceRelation::E_NegativeSide;
    const ESpaceRelation EXPECTED_RESULT_CONTAINED = ESpaceRelation::E_Contained;

	// [Execution]
    ESpaceRelation eResultPositive  = HEXAHEDRON_POSITIVE.SpaceRelation(PLANE);
    ESpaceRelation eResultNegative  = HEXAHEDRON_NEGATIVE.SpaceRelation(PLANE);
    ESpaceRelation eResultContained = HEXAHEDRON_CONTAINED.SpaceRelation(PLANE);

    // [Verification]
    BOOST_CHECK(eResultPositive == EXPECTED_RESULT_POSITIVE);
    BOOST_CHECK(eResultNegative == EXPECTED_RESULT_NEGATIVE);
    BOOST_CHECK(eResultContained == EXPECTED_RESULT_CONTAINED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the hexahedron is correctly transformed by an arbitrary rotation matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( Rotate2_HexahedronIsCorrectlyTransformedByCommonRotationMatrix_Test, TTemplateTypes )
{
    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z EULER_ANGLE_X = SAngle::_HalfPi;
    const float_z EULER_ANGLE_Y = SAngle::_Pi;
    const float_z EULER_ANGLE_Z = SAngle::_QuarterPi;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z EULER_ANGLE_X = SAngle::_90;
    const float_z EULER_ANGLE_Y = SAngle::_180;
    const float_z EULER_ANGLE_Z = SAngle::_45;
#endif

    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);

    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>::GetUnitCube();

    const float_z EXPECTED_VECTOR_COMPONENTS_A[] = { (float_z)0.70710678118654746, (float_z)-0.5, (float_z)2.4894981252573997e-017, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_B[] = { (float_z)0.70710678118654746, (float_z)0.5, (float_z)8.6127321209941663e-017, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_C[] = { (float_z)5.5511151231257821e-017, (float_z)0.5, (float_z)-0.70710678118654746, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_D[] = { (float_z)5.5511151231257827e-017, (float_z)-0.49999999999999994, (float_z)-0.70710678118654746, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_E[] = { (float_z)-5.5511151231257821e-017, (float_z)-0.5, (float_z)0.70710678118654746, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_F[] = { (float_z)-0.70710678118654746, (float_z)-0.5, (float_z)-8.6127321209941663e-017, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_G[] = { (float_z)-0.70710678118654746, (float_z)0.5, (float_z)-2.4894981252573997e-017, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_H[] = { (float_z)-5.5511151231257827e-017, (float_z)0.49999999999999994, (float_z)0.70710678118654746, SFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(EXPECTED_VECTOR_COMPONENTS_C);
    const T EXPECTED_VALUE_FOR_D(EXPECTED_VECTOR_COMPONENTS_D);
    const T EXPECTED_VALUE_FOR_E(EXPECTED_VECTOR_COMPONENTS_E);
    const T EXPECTED_VALUE_FOR_F(EXPECTED_VECTOR_COMPONENTS_F);
    const T EXPECTED_VALUE_FOR_G(EXPECTED_VECTOR_COMPONENTS_G);
    const T EXPECTED_VALUE_FOR_H(EXPECTED_VECTOR_COMPONENTS_H);

	// [Execution]
    Hexahedron<T> returnedHexahedron = HEXAHEDRON.Rotate(ROTATION);

    // [Verification]
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that a hexahedron is not rotated when the matrix equals identity.
/// </summary>
ZTEST_CASE_TEMPLATE ( Rotate2_HexahedronIsNotRotatedWhenMatrixEqualsIdentity_Test, TTemplateTypes )
{
    // [Preparation]
    const RotationMatrix3x3 ROTATION = Matrix3x3::GetIdentity();

    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>::GetUnitCube();

    const T EXPECTED_VALUE_FOR_A = HEXAHEDRON.A;
    const T EXPECTED_VALUE_FOR_B = HEXAHEDRON.B;
    const T EXPECTED_VALUE_FOR_C = HEXAHEDRON.C;
    const T EXPECTED_VALUE_FOR_D = HEXAHEDRON.D;
    const T EXPECTED_VALUE_FOR_E = HEXAHEDRON.E;
    const T EXPECTED_VALUE_FOR_F = HEXAHEDRON.F;
    const T EXPECTED_VALUE_FOR_G = HEXAHEDRON.G;
    const T EXPECTED_VALUE_FOR_H = HEXAHEDRON.H;

	// [Execution]
    Hexahedron<T> returnedHexahedron = HEXAHEDRON.Rotate(ROTATION);

    // [Verification]
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that the vertices of the hexahedron are moved to the coordinate origin when the matrix equals zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( Rotate2_VerticesAreMovedToCoordinateOriginWhenMatrixEqualsZero_Test, TTemplateTypes )
{
    // [Preparation]
    const RotationMatrix3x3 ROTATION = Matrix3x3::GetNullMatrix();

    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>::GetUnitCube();

    const float_z NULL_VECTOR_COMPONENTS[] = {SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1};

    const T EXPECTED_VALUE_FOR_A = T(NULL_VECTOR_COMPONENTS);
    const T EXPECTED_VALUE_FOR_B = T(NULL_VECTOR_COMPONENTS);
    const T EXPECTED_VALUE_FOR_C = T(NULL_VECTOR_COMPONENTS);
    const T EXPECTED_VALUE_FOR_D = T(NULL_VECTOR_COMPONENTS);
    const T EXPECTED_VALUE_FOR_E = T(NULL_VECTOR_COMPONENTS);
    const T EXPECTED_VALUE_FOR_F = T(NULL_VECTOR_COMPONENTS);
    const T EXPECTED_VALUE_FOR_G = T(NULL_VECTOR_COMPONENTS);
    const T EXPECTED_VALUE_FOR_H = T(NULL_VECTOR_COMPONENTS);

	// [Execution]
    Hexahedron<T> returnedHexahedron = HEXAHEDRON.Rotate(ROTATION);

    // [Verification]
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that the hexahedron is correctly transformed by an arbitrary rotation matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( RotateWithPivot2_HexahedronIsCorrectlyTransformedByCommonRotationMatrix_Test, TTemplateTypes )
{
    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z EULER_ANGLE_X = SAngle::_HalfPi;
    const float_z EULER_ANGLE_Y = SAngle::_Pi;
    const float_z EULER_ANGLE_Z = SAngle::_QuarterPi;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z EULER_ANGLE_X = SAngle::_90;
    const float_z EULER_ANGLE_Y = SAngle::_180;
    const float_z EULER_ANGLE_Z = SAngle::_45;
#endif

    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);

    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>::GetUnitCube();

    const float_z EXPECTED_VECTOR_COMPONENTS_A[] = { (float_z)0.99999999999999978, (float_z)4.5, (float_z)5.1213203435596428, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_B[] = { (float_z)0.99999999999999978, (float_z)5.5, (float_z)5.1213203435596428, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_C[] = { (float_z)0.29289321881345232, (float_z)5.5, (float_z)4.4142135623730949, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_D[] = { (float_z)0.29289321881345232, (float_z)4.5, (float_z)4.4142135623730949, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_E[] = { (float_z)0.29289321881345232, (float_z)4.5, (float_z)5.8284271247461898, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_F[] = { (float_z)-0.41421356237309515, (float_z)4.5, (float_z)5.1213203435596419, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_G[] = { (float_z)-0.41421356237309515, (float_z)5.5, (float_z)5.1213203435596419, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_H[] = { (float_z)0.29289321881345232, (float_z)5.5, (float_z)5.8284271247461898, SFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(EXPECTED_VECTOR_COMPONENTS_C);
    const T EXPECTED_VALUE_FOR_D(EXPECTED_VECTOR_COMPONENTS_D);
    const T EXPECTED_VALUE_FOR_E(EXPECTED_VECTOR_COMPONENTS_E);
    const T EXPECTED_VALUE_FOR_F(EXPECTED_VECTOR_COMPONENTS_F);
    const T EXPECTED_VALUE_FOR_G(EXPECTED_VECTOR_COMPONENTS_G);
    const T EXPECTED_VALUE_FOR_H(EXPECTED_VECTOR_COMPONENTS_H);

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// [Execution]
    Hexahedron<T> returnedHexahedron = HEXAHEDRON.RotateWithPivot(ROTATION, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that a hexahedron is not rotated when the matrix equals identity.
/// </summary>
ZTEST_CASE_TEMPLATE ( RotateWithPivot2_HexahedronIsNotRotatedWhenMatrixEqualsIdentity_Test, TTemplateTypes )
{
    // [Preparation]
    const RotationMatrix3x3 ROTATION = Matrix3x3::GetIdentity();

    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>::GetUnitCube();

    const T EXPECTED_VALUE_FOR_A = HEXAHEDRON.A;
    const T EXPECTED_VALUE_FOR_B = HEXAHEDRON.B;
    const T EXPECTED_VALUE_FOR_C = HEXAHEDRON.C;
    const T EXPECTED_VALUE_FOR_D = HEXAHEDRON.D;
    const T EXPECTED_VALUE_FOR_E = HEXAHEDRON.E;
    const T EXPECTED_VALUE_FOR_F = HEXAHEDRON.F;
    const T EXPECTED_VALUE_FOR_G = HEXAHEDRON.G;
    const T EXPECTED_VALUE_FOR_H = HEXAHEDRON.H;

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// [Execution]
    Hexahedron<T> returnedHexahedron = HEXAHEDRON.RotateWithPivot(ROTATION, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that the vertices of the hexahedron are moved to the position of the pivot point when the matrix equals zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( RotateWithPivot2_VerticesAreMovedToPivotPointWhenMatrixEqualsZero_Test, TTemplateTypes )
{
    // [Preparation]
    const RotationMatrix3x3 ROTATION = Matrix3x3::GetNullMatrix();

    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>::GetUnitCube();

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const T EXPECTED_VALUE_FOR_A = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_B = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_C = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_D = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_E = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_F = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_G = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_H = PIVOT_POINT;

	// [Execution]
    Hexahedron<T> returnedHexahedron = HEXAHEDRON.RotateWithPivot(ROTATION, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Template method used by Translate3_CommonHexahedronIsCorrectlyTranslatedWhenUsingCommonTranslationMatrix_Test to test
/// using different template parameters for class TranslationMatrix.
/// </summary>
template<class T, class MatrixType>
void Translate3_CommonHexahedronIsCorrectlyTranslatedWhenUsingCommonTranslationMatrix_Template()
{

    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_D[] = { SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_E[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_F[] = { SFloat::_4, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_G[] = { -SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_H[] = { SFloat::_0, SFloat::_1, SFloat::_4, SFloat::_1 };

    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>(T(VECTOR_COMPONENTS_A),
                                                     T(VECTOR_COMPONENTS_B),
                                                     T(VECTOR_COMPONENTS_C),
                                                     T(VECTOR_COMPONENTS_D),
                                                     T(VECTOR_COMPONENTS_E),
                                                     T(VECTOR_COMPONENTS_F),
                                                     T(VECTOR_COMPONENTS_G),
                                                     T(VECTOR_COMPONENTS_H));

    const float_z EXPECTED_VECTOR_COMPONENTS_A[] = { SFloat::_2, SFloat::_4, SFloat::_7, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_B[] = { SFloat::_4, SFloat::_3, SFloat::_7, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_C[] = { SFloat::_3, SFloat::_5, SFloat::_6, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_D[] = { SFloat::_5, SFloat::_7, SFloat::_9, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_E[] = { SFloat::_4, SFloat::_4, SFloat::_6, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_F[] = { SFloat::_5, SFloat::_3, SFloat::_6, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_G[] = { SFloat::_0, SFloat::_4, SFloat::_7, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_H[] = { SFloat::_1, SFloat::_3, SFloat::_7, SFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(EXPECTED_VECTOR_COMPONENTS_C);
    const T EXPECTED_VALUE_FOR_D(EXPECTED_VECTOR_COMPONENTS_D);
    const T EXPECTED_VALUE_FOR_E(EXPECTED_VECTOR_COMPONENTS_E);
    const T EXPECTED_VALUE_FOR_F(EXPECTED_VECTOR_COMPONENTS_F);
    const T EXPECTED_VALUE_FOR_G(EXPECTED_VECTOR_COMPONENTS_G);
    const T EXPECTED_VALUE_FOR_H(EXPECTED_VECTOR_COMPONENTS_H);

    const TranslationMatrix<MatrixType> TRANSLATION = TranslationMatrix<MatrixType>(SFloat::_1, SFloat::_2, SFloat::_3);

	// [Execution]
    Hexahedron<T> returnedHexahedron = HEXAHEDRON.Translate(TRANSLATION);

    // [Verification]
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that a common hexahedron is correctly translated using common translation matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( Translate3_CommonHexahedronIsCorrectlyTranslatedWhenUsingCommonTranslationMatrix_Test, TTemplateTypes )
{

    BOOST_TEST_MESSAGE("MatrixType=Matrix4x3");
    Translate3_CommonHexahedronIsCorrectlyTranslatedWhenUsingCommonTranslationMatrix_Template<T, Matrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=Matrix4x4");
    Translate3_CommonHexahedronIsCorrectlyTranslatedWhenUsingCommonTranslationMatrix_Template<T, Matrix4x4>();
}

/// <summary>
/// Template method used by Translate3_HexahedronIsNotTranslatedWhenTranslationIsZero_Test to test
/// using different template parameters for class TranslationMatrix.
/// </summary>
template<class T, class MatrixType>
void Translate3_HexahedronIsNotTranslatedWhenTranslationIsZero_Template()
{

    // [Preparation]
    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>::GetUnitCube();

    const T EXPECTED_VALUE_FOR_A = HEXAHEDRON.A;
    const T EXPECTED_VALUE_FOR_B = HEXAHEDRON.B;
    const T EXPECTED_VALUE_FOR_C = HEXAHEDRON.C;
    const T EXPECTED_VALUE_FOR_D = HEXAHEDRON.D;
    const T EXPECTED_VALUE_FOR_E = HEXAHEDRON.E;
    const T EXPECTED_VALUE_FOR_F = HEXAHEDRON.F;
    const T EXPECTED_VALUE_FOR_G = HEXAHEDRON.G;
    const T EXPECTED_VALUE_FOR_H = HEXAHEDRON.H;

    const TranslationMatrix<MatrixType> TRANSLATION = MatrixType::GetNullMatrix();

	// [Execution]
    Hexahedron<T> returnedHexahedron = HEXAHEDRON.Translate(TRANSLATION);

    // [Verification]
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that a hexahedron is not translated when translation is zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( Translate3_HexahedronIsNotTranslatedWhenTranslationIsZero_Test, TTemplateTypes )
{

    BOOST_TEST_MESSAGE("MatrixType=Matrix4x3");
    Translate3_HexahedronIsNotTranslatedWhenTranslationIsZero_Template<T, Matrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=Matrix4x4");
    Translate3_HexahedronIsNotTranslatedWhenTranslationIsZero_Template<T, Matrix4x4>();
}

/// <summary>
/// Template method used by Translate3_HexahedronIsNotTranslatedWhenTranslationMatrixEqualsIdentity_Test to test
/// using different template parameters for class TranslationMatrix.
/// </summary>
template<class T, class MatrixType>
void Translate3_HexahedronIsNotTranslatedWhenTranslationMatrixEqualsIdentity_Template()
{

    // [Preparation]
    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>::GetUnitCube();

    const T EXPECTED_VALUE_FOR_A = HEXAHEDRON.A;
    const T EXPECTED_VALUE_FOR_B = HEXAHEDRON.B;
    const T EXPECTED_VALUE_FOR_C = HEXAHEDRON.C;
    const T EXPECTED_VALUE_FOR_D = HEXAHEDRON.D;
    const T EXPECTED_VALUE_FOR_E = HEXAHEDRON.E;
    const T EXPECTED_VALUE_FOR_F = HEXAHEDRON.F;
    const T EXPECTED_VALUE_FOR_G = HEXAHEDRON.G;
    const T EXPECTED_VALUE_FOR_H = HEXAHEDRON.H;

    const TranslationMatrix<MatrixType> TRANSLATION = MatrixType::GetIdentity();

	// [Execution]
    Hexahedron<T> returnedHexahedron = HEXAHEDRON.Translate(TRANSLATION);

    // [Verification]
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that a hexahedron is not translated when matrix equals identity.
/// </summary>
ZTEST_CASE_TEMPLATE ( Translate3_HexahedronIsNotTranslatedWhenTranslationMatrixEqualsIdentity_Test, TTemplateTypes )
{

    BOOST_TEST_MESSAGE("MatrixType=Matrix4x3");
    Translate3_HexahedronIsNotTranslatedWhenTranslationMatrixEqualsIdentity_Template<T, Matrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=Matrix4x4");
    Translate3_HexahedronIsNotTranslatedWhenTranslationMatrixEqualsIdentity_Template<T, Matrix4x4>();
}

/// <summary>
/// Checks that a common hexahedron is correctly scaled using common scaling matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( Scale3_CommonHexahedronIsCorrectlyScaledWhenUsingCommonScalingMatrix_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1,  SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3,  SFloat::_4, SFloat::_2, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_2,  SFloat::_3, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_D[] = { SFloat::_4,  SFloat::_5, SFloat::_6, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_E[] = { SFloat::_3,  SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_F[] = { SFloat::_4,  SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_G[] = { -SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_H[] = { SFloat::_0,  SFloat::_1, SFloat::_4, SFloat::_1 };

    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>(T(VECTOR_COMPONENTS_A),
                                                     T(VECTOR_COMPONENTS_B),
                                                     T(VECTOR_COMPONENTS_C),
                                                     T(VECTOR_COMPONENTS_D),
                                                     T(VECTOR_COMPONENTS_E),
                                                     T(VECTOR_COMPONENTS_F),
                                                     T(VECTOR_COMPONENTS_G),
                                                     T(VECTOR_COMPONENTS_H));

    const float_z EXPECTED_VECTOR_COMPONENTS_A[] = { SFloat::_1,  SFloat::_4,  SFloat::_9,   SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_B[] = { SFloat::_3,  SFloat::_8,  SFloat::_6,   SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_C[] = { SFloat::_2,  SFloat::_6,  SFloat::_9,   SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_D[] = { SFloat::_4,  SFloat::_10, (float_z)18.0, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_E[] = { SFloat::_3,  SFloat::_4,  SFloat::_9,   SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_F[] = { SFloat::_4,  SFloat::_2,  SFloat::_9,   SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_G[] = { -SFloat::_1, SFloat::_4,  (float_z)12.0, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_H[] = { SFloat::_0,  SFloat::_2,  (float_z)12.0, SFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(EXPECTED_VECTOR_COMPONENTS_C);
    const T EXPECTED_VALUE_FOR_D(EXPECTED_VECTOR_COMPONENTS_D);
    const T EXPECTED_VALUE_FOR_E(EXPECTED_VECTOR_COMPONENTS_E);
    const T EXPECTED_VALUE_FOR_F(EXPECTED_VECTOR_COMPONENTS_F);
    const T EXPECTED_VALUE_FOR_G(EXPECTED_VECTOR_COMPONENTS_G);
    const T EXPECTED_VALUE_FOR_H(EXPECTED_VECTOR_COMPONENTS_H);

    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3(SFloat::_1, SFloat::_2, SFloat::_3);

	// [Execution]
    Hexahedron<T> returnedHexahedron = HEXAHEDRON.Scale(SCALE);

    // [Verification]
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that a hexahedron is not translated when the matrix equals identity.
/// </summary>
ZTEST_CASE_TEMPLATE ( Scale3_HexahedronIsNotTranslatedWhenMatrixEqualsIdentity_Test, TTemplateTypes )
{
    // [Preparation]
    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>::GetUnitCube();

    const T EXPECTED_VALUE_FOR_A = HEXAHEDRON.A;
    const T EXPECTED_VALUE_FOR_B = HEXAHEDRON.B;
    const T EXPECTED_VALUE_FOR_C = HEXAHEDRON.C;
    const T EXPECTED_VALUE_FOR_D = HEXAHEDRON.D;
    const T EXPECTED_VALUE_FOR_E = HEXAHEDRON.E;
    const T EXPECTED_VALUE_FOR_F = HEXAHEDRON.F;
    const T EXPECTED_VALUE_FOR_G = HEXAHEDRON.G;
    const T EXPECTED_VALUE_FOR_H = HEXAHEDRON.H;

    const ScalingMatrix3x3 SCALE = Matrix3x3::GetIdentity();

	// [Execution]
    Hexahedron<T> returnedHexahedron = HEXAHEDRON.Scale(SCALE);

    // [Verification]
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that the vertices of the hexahedron are moved to the coordinate origin when the matrix equals zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( Scale3_VerticesAreMovedToCoordinateOriginWhenMatrixEqualsZero_Test, TTemplateTypes )
{
    // [Preparation]
    const ScalingMatrix3x3 SCALE = Matrix3x3::GetNullMatrix();

    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>::GetUnitCube();

    const float_z NULL_VECTOR_COMPONENTS[] = {SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1};
    const T COORDINATE_ORIGIN = T(NULL_VECTOR_COMPONENTS);

	// [Execution]
    Hexahedron<T> returnedHexahedron = HEXAHEDRON.Scale(SCALE);

    // [Verification]
    BOOST_CHECK(returnedHexahedron.A == COORDINATE_ORIGIN);
    BOOST_CHECK(returnedHexahedron.B == COORDINATE_ORIGIN);
    BOOST_CHECK(returnedHexahedron.C == COORDINATE_ORIGIN);
    BOOST_CHECK(returnedHexahedron.D == COORDINATE_ORIGIN);
    BOOST_CHECK(returnedHexahedron.E == COORDINATE_ORIGIN);
    BOOST_CHECK(returnedHexahedron.F == COORDINATE_ORIGIN);
    BOOST_CHECK(returnedHexahedron.G == COORDINATE_ORIGIN);
    BOOST_CHECK(returnedHexahedron.H == COORDINATE_ORIGIN);
}

/// <summary>
/// Checks that a common hexahedron is correctly scaled using common scaling vector.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot3_CommonHexahedronIsCorrectlyScaledWhenUsingCommonVector_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1,  SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3,  SFloat::_4, SFloat::_2, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_2,  SFloat::_3, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_D[] = { SFloat::_4,  SFloat::_5, SFloat::_6, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_E[] = { SFloat::_3,  SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_F[] = { SFloat::_4,  SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_G[] = { -SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_H[] = { SFloat::_0,  SFloat::_1, SFloat::_4, SFloat::_1 };

    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>(T(VECTOR_COMPONENTS_A),
                                                     T(VECTOR_COMPONENTS_B),
                                                     T(VECTOR_COMPONENTS_C),
                                                     T(VECTOR_COMPONENTS_D),
                                                     T(VECTOR_COMPONENTS_E),
                                                     T(VECTOR_COMPONENTS_F),
                                                     T(VECTOR_COMPONENTS_G),
                                                     T(VECTOR_COMPONENTS_H));

    const float_z EXPECTED_VECTOR_COMPONENTS_A[] = { SFloat::_1,  SFloat::_2,  SFloat::_3,   SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_B[] = { SFloat::_3,  SFloat::_6,  SFloat::_0,   SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_C[] = { SFloat::_2,  SFloat::_4,  SFloat::_3,   SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_D[] = { SFloat::_4,  SFloat::_8, (float_z)12.0, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_E[] = { SFloat::_3,  SFloat::_2,  SFloat::_3,   SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_F[] = { SFloat::_4,  SFloat::_0,  SFloat::_3,   SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_G[] = { -SFloat::_1, SFloat::_2,  SFloat::_6, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_H[] = { SFloat::_0,  SFloat::_0,  SFloat::_6, SFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(EXPECTED_VECTOR_COMPONENTS_C);
    const T EXPECTED_VALUE_FOR_D(EXPECTED_VECTOR_COMPONENTS_D);
    const T EXPECTED_VALUE_FOR_E(EXPECTED_VECTOR_COMPONENTS_E);
    const T EXPECTED_VALUE_FOR_F(EXPECTED_VECTOR_COMPONENTS_F);
    const T EXPECTED_VALUE_FOR_G(EXPECTED_VECTOR_COMPONENTS_G);
    const T EXPECTED_VALUE_FOR_H(EXPECTED_VECTOR_COMPONENTS_H);

    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3(SFloat::_1, SFloat::_2, SFloat::_3);

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// [Execution]
    Hexahedron<T> returnedHexahedron = HEXAHEDRON.ScaleWithPivot(SCALE, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that a hexahedron is not scaled when scale is a vector of ones.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot3_HexahedronIsNotScaledWhenVectorComponentsEqualOne_Test, TTemplateTypes )
{
    // [Preparation]
    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>::GetUnitCube();

    const T EXPECTED_VALUE_FOR_A = HEXAHEDRON.A;
    const T EXPECTED_VALUE_FOR_B = HEXAHEDRON.B;
    const T EXPECTED_VALUE_FOR_C = HEXAHEDRON.C;
    const T EXPECTED_VALUE_FOR_D = HEXAHEDRON.D;
    const T EXPECTED_VALUE_FOR_E = HEXAHEDRON.E;
    const T EXPECTED_VALUE_FOR_F = HEXAHEDRON.F;
    const T EXPECTED_VALUE_FOR_G = HEXAHEDRON.G;
    const T EXPECTED_VALUE_FOR_H = HEXAHEDRON.H;

    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3::GetIdentity();

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// [Execution]
    Hexahedron<T> returnedHexahedron = HEXAHEDRON.ScaleWithPivot(SCALE, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that the vertices of the hexahedron are moved to the coordinate origin when the vector is null.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot3_VerticesAreMovedToCoordinateOriginWhenVectorIsNull_Test, TTemplateTypes )
{
    // [Preparation]
    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>::GetUnitCube();

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3::GetNullMatrix();

	// [Execution]
    Hexahedron<T> returnedHexahedron = HEXAHEDRON.ScaleWithPivot(SCALE, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedHexahedron.A == PIVOT_POINT);
    BOOST_CHECK(returnedHexahedron.B == PIVOT_POINT);
    BOOST_CHECK(returnedHexahedron.C == PIVOT_POINT);
    BOOST_CHECK(returnedHexahedron.D == PIVOT_POINT);
    BOOST_CHECK(returnedHexahedron.E == PIVOT_POINT);
    BOOST_CHECK(returnedHexahedron.F == PIVOT_POINT);
    BOOST_CHECK(returnedHexahedron.G == PIVOT_POINT);
    BOOST_CHECK(returnedHexahedron.H == PIVOT_POINT);
}

/// <summary>
/// Template method used by Transform1_CommonHexahedronIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Test to test
/// using different template parameters for class TransformationMatrix.
/// </summary>
template<class T, class MatrixType>
void Transform1_CommonHexahedronIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Template()
{
    // [Preparation]
    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>::GetUnitCube();

    const float_z EXPECTED_VECTOR_COMPONENTS_A[] = { (float_z)3.1490485194281401, (float_z)4.5, (float_z)-6.9722718241315027, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_B[] = { (float_z)3.1490485194281401, (float_z)3.5, (float_z)-6.9722718241315027, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_C[] = { (float_z)2.9722718241315027, (float_z)3.5, (float_z)-7.1490485194281401, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_D[] = { (float_z)2.9722718241315027, (float_z)4.5, (float_z)-7.1490485194281401, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_E[] = { (float_z)1.0277281758684971, (float_z)4.5, (float_z)-4.8509514805718599, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_F[] = { (float_z)0.8509514805718601, (float_z)4.5, (float_z)-5.0277281758684973, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_G[] = { (float_z)0.8509514805718601, (float_z)3.5, (float_z)-5.0277281758684973, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_H[] = { (float_z)1.0277281758684971, (float_z)3.5, (float_z)-4.8509514805718599, SFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(EXPECTED_VECTOR_COMPONENTS_C);
    const T EXPECTED_VALUE_FOR_D(EXPECTED_VECTOR_COMPONENTS_D);
    const T EXPECTED_VALUE_FOR_E(EXPECTED_VECTOR_COMPONENTS_E);
    const T EXPECTED_VALUE_FOR_F(EXPECTED_VECTOR_COMPONENTS_F);
    const T EXPECTED_VALUE_FOR_G(EXPECTED_VECTOR_COMPONENTS_G);
    const T EXPECTED_VALUE_FOR_H(EXPECTED_VECTOR_COMPONENTS_H);

#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z EULER_ANGLE_X = SAngle::_HalfPi;
    const float_z EULER_ANGLE_Y = SAngle::_Pi;
    const float_z EULER_ANGLE_Z = SAngle::_QuarterPi;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z EULER_ANGLE_X = SAngle::_90;
    const float_z EULER_ANGLE_Y = SAngle::_180;
    const float_z EULER_ANGLE_Z = SAngle::_45;
#endif

    const TranslationMatrix<MatrixType> TRANSLATION = TranslationMatrix<MatrixType>(SFloat::_2, SFloat::_4, -SFloat::_6);
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);
    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3(SFloat::_0_25, SFloat::_3, -SFloat::_1);

    const TransformationMatrix<MatrixType> TRANSFORMATION = TransformationMatrix<MatrixType>(TRANSLATION, ROTATION, SCALE);

	// [Execution]
    Hexahedron<T> returnedHexahedron = HEXAHEDRON.Transform(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that a common hexahedron is correctly transformed using common transformation matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( Transform1_CommonHexahedronIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Test, TTemplateTypes )
{

    BOOST_TEST_MESSAGE("MatrixType=Matrix4x3");
    Transform1_CommonHexahedronIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Template<T, Matrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=Matrix4x4");
    Transform1_CommonHexahedronIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Template<T, Matrix4x4>();
}

/// <summary>
/// Template method used by Transform1_HexahedronVerticesAreMovedToCoordinateOriginWhenTransformationIsZero_Test to test
/// using different template parameters for class TransformationMatrix.
/// </summary>
template<class T, class MatrixType>
void Transform1_HexahedronVerticesAreMovedToCoordinateOriginWhenTransformationIsZero_Template()
{
    // [Preparation]
    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>::GetUnitCube();

    const float_z NULL_VECTOR_COMPONENTS[] = {SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1};

    const T EXPECTED_VALUE_FOR_A = T(NULL_VECTOR_COMPONENTS);
    const T EXPECTED_VALUE_FOR_B = T(NULL_VECTOR_COMPONENTS);
    const T EXPECTED_VALUE_FOR_C = T(NULL_VECTOR_COMPONENTS);
    const T EXPECTED_VALUE_FOR_D = T(NULL_VECTOR_COMPONENTS);
    const T EXPECTED_VALUE_FOR_E = T(NULL_VECTOR_COMPONENTS);
    const T EXPECTED_VALUE_FOR_F = T(NULL_VECTOR_COMPONENTS);
    const T EXPECTED_VALUE_FOR_G = T(NULL_VECTOR_COMPONENTS);
    const T EXPECTED_VALUE_FOR_H = T(NULL_VECTOR_COMPONENTS);

    const TransformationMatrix<MatrixType> TRANSFORMATION = MatrixType::GetNullMatrix();

	// [Execution]
    Hexahedron<T> returnedHexahedron = HEXAHEDRON.Transform(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that all the vertices of the hexahedron are moved to the coordinate origin when transformation is zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( Transform1_HexahedronVerticesAreMovedToCoordinateOriginWhenTransformationIsZero_Test, TTemplateTypes )
{

    BOOST_TEST_MESSAGE("MatrixType=Matrix4x3");
    Transform1_HexahedronVerticesAreMovedToCoordinateOriginWhenTransformationIsZero_Template<T, Matrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=Matrix4x4");
    Transform1_HexahedronVerticesAreMovedToCoordinateOriginWhenTransformationIsZero_Template<T, Matrix4x4>();
}

/// <summary>
/// Template method used by Transform1_HexahedronIsNotTransformedWhenTransformationMatrixEqualsIdentity_Test to test
/// using different template parameters for class TransformationMatrix.
/// </summary>
template<class T, class MatrixType>
void Transform1_HexahedronIsNotTransformedWhenTransformationMatrixEqualsIdentity_Template()
{
    // [Preparation]
    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>::GetUnitCube();

    const T EXPECTED_VALUE_FOR_A = HEXAHEDRON.A;
    const T EXPECTED_VALUE_FOR_B = HEXAHEDRON.B;
    const T EXPECTED_VALUE_FOR_C = HEXAHEDRON.C;
    const T EXPECTED_VALUE_FOR_D = HEXAHEDRON.D;
    const T EXPECTED_VALUE_FOR_E = HEXAHEDRON.E;
    const T EXPECTED_VALUE_FOR_F = HEXAHEDRON.F;
    const T EXPECTED_VALUE_FOR_G = HEXAHEDRON.G;
    const T EXPECTED_VALUE_FOR_H = HEXAHEDRON.H;

    const TransformationMatrix<MatrixType> TRANSFORMATION = MatrixType::GetIdentity();

	// [Execution]
    Hexahedron<T> returnedHexahedron = HEXAHEDRON.Transform(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that a hexahedron is not transformed when matrix equals identity.
/// </summary>
ZTEST_CASE_TEMPLATE ( Transform1_HexahedronIsNotTransformedWhenTransformationMatrixEqualsIdentity_Test, TTemplateTypes )
{

    BOOST_TEST_MESSAGE("MatrixType=Matrix4x3");
    Transform1_HexahedronIsNotTransformedWhenTransformationMatrixEqualsIdentity_Template<T, Matrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=Matrix4x4");
    Transform1_HexahedronIsNotTransformedWhenTransformationMatrixEqualsIdentity_Template<T, Matrix4x4>();
}

/// <summary>
/// Checks that the hexahedron is correctly transformed by an arbitrary space conversion matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( Transform2_IsCorrectlyTransformedByCommonSpaceConversionMatrix_Test, TTemplateTypes )
{
    // [Preparation]
    SpaceConversionMatrix CONVERSION = SpaceConversionMatrix();
    CONVERSION.SetViewSpaceMatrix(Vector3(SFloat::_1, SFloat::_2, SFloat::_3),
                                  Vector3(SFloat::_0, SFloat::_0, SFloat::_1),
                                  Vector3(SFloat::_0, SFloat::_1, SFloat::_0));

    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>::GetUnitCube();

    
    const float_z EXPECTED_VECTOR_COMPONENTS_A[] = { (float_z)0.22360679774997894, (float_z)0.81989159174992277, (float_z)3.1666666666666665, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_B[] = { (float_z)-0.22360679774997902, (float_z)1.4161763857498666, (float_z)3.833333333333333, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_C[] = { (float_z)-1.1180339887498949, (float_z)1.1180339887498947, (float_z)3.5, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_D[] = { (float_z)-0.67082039324993692, (float_z)0.52174919474995085, (float_z)2.833333333333333, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_E[] = { (float_z)0.22360679774997894, (float_z)0.074535599249992979, (float_z)3.833333333333333, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_F[] = { (float_z)-0.67082039324993692, (float_z)-0.22360679774997894, (float_z)3.5, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_G[] = { (float_z)-1.1180339887498949, (float_z)0.37267799624996489, (float_z)4.1666666666666661, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_H[] = { (float_z)-0.22360679774997902, (float_z)0.67082039324993681, (float_z)4.5, SFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(EXPECTED_VECTOR_COMPONENTS_C);
    const T EXPECTED_VALUE_FOR_D(EXPECTED_VECTOR_COMPONENTS_D);
    const T EXPECTED_VALUE_FOR_E(EXPECTED_VECTOR_COMPONENTS_E);
    const T EXPECTED_VALUE_FOR_F(EXPECTED_VECTOR_COMPONENTS_F);
    const T EXPECTED_VALUE_FOR_G(EXPECTED_VECTOR_COMPONENTS_G);
    const T EXPECTED_VALUE_FOR_H(EXPECTED_VECTOR_COMPONENTS_H);

    const Hexahedron<T> EXPECTED_HEXAHEDRON = Hexahedron<T>(EXPECTED_VALUE_FOR_A,
                                                              EXPECTED_VALUE_FOR_B,
                                                              EXPECTED_VALUE_FOR_C,
                                                              EXPECTED_VALUE_FOR_D,
                                                              EXPECTED_VALUE_FOR_E,
                                                              EXPECTED_VALUE_FOR_F,
                                                              EXPECTED_VALUE_FOR_G,
                                                              EXPECTED_VALUE_FOR_H);

	// [Execution]
    Hexahedron<T> hexahedron = HEXAHEDRON.Transform(CONVERSION);
    	
    // [Verification]
    BOOST_CHECK(hexahedron == EXPECTED_HEXAHEDRON);
}

/// <summary>
/// Checks that the line segment doesn't change when it's transformed by an identity matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( Transform2_LineSegmentDoesNotChangeWhenTransformedByIdentityMatrix_Test, TTemplateTypes )
{
    // [Preparation]
    const SpaceConversionMatrix IDENTITY_MATRIX = SpaceConversionMatrix::GetIdentity();

    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>::GetUnitCube();

    const Hexahedron<T> EXPECTED_HEXAHEDRON = HEXAHEDRON;

	// [Execution]
    Hexahedron<T> hexahedron = HEXAHEDRON.Transform(IDENTITY_MATRIX);

    // [Verification]
    BOOST_CHECK(hexahedron == EXPECTED_HEXAHEDRON);
}

/// <summary>
/// Checks that the line segment is nullified when the matrix equals zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( Transform2_EndpointsAreNullifiedWhenMatrixIsZero_Test, TTemplateTypes )
{
    // [Preparation]
    const SpaceConversionMatrix NULL_MATRIX = Matrix4x4::GetNullMatrix();

    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>::GetUnitCube();

    const Hexahedron<T> EXPECTED_HEXAHEDRON = Hexahedron<T>(T::GetNullVector(), T::GetNullVector());

	// [Execution]
    Hexahedron<T> hexahedron = HEXAHEDRON.Transform(NULL_MATRIX);

    // [Verification]
    BOOST_CHECK(hexahedron == EXPECTED_HEXAHEDRON);
}

/// <summary>
/// Template method used by TransformWithPivot_CommonHexahedronIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Test to test
/// using different template parameters for class TransformationMatrix.
/// </summary>
template<class T, class MatrixType>
void TransformWithPivot_CommonHexahedronIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Template()
{
    // [Preparation]
    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>::GetUnitCube();

    const float_z EXPECTED_VECTOR_COMPONENTS_A[] = { (float_z)0.083184527605490999, (float_z)3.5, (float_z)0.44714555828441904, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_B[] = { (float_z)0.083184527605490999, (float_z)2.5, (float_z)0.44714555828441904, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_C[] = { (float_z)-0.093592167691145978, (float_z)2.5, (float_z)0.27036886298778207, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_D[] = { (float_z)-0.093592167691145978, (float_z)3.5, (float_z)0.27036886298778207, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_E[] = { (float_z)-2.0381358159541509, (float_z)3.4999999999999996, (float_z)2.5684659018440614, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_F[] = { (float_z)-2.2149125112507884, (float_z)3.4999999999999996, (float_z)2.391689206547424, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_G[] = { (float_z)-2.2149125112507884, (float_z)2.4999999999999996, (float_z)2.391689206547424, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_H[] = { (float_z)-2.0381358159541509, (float_z)2.4999999999999996, (float_z)2.5684659018440614, SFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(EXPECTED_VECTOR_COMPONENTS_C);
    const T EXPECTED_VALUE_FOR_D(EXPECTED_VECTOR_COMPONENTS_D);
    const T EXPECTED_VALUE_FOR_E(EXPECTED_VECTOR_COMPONENTS_E);
    const T EXPECTED_VALUE_FOR_F(EXPECTED_VECTOR_COMPONENTS_F);
    const T EXPECTED_VALUE_FOR_G(EXPECTED_VECTOR_COMPONENTS_G);
    const T EXPECTED_VALUE_FOR_H(EXPECTED_VECTOR_COMPONENTS_H);

#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z EULER_ANGLE_X = SAngle::_HalfPi;
    const float_z EULER_ANGLE_Y = SAngle::_Pi;
    const float_z EULER_ANGLE_Z = SAngle::_QuarterPi;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z EULER_ANGLE_X = SAngle::_90;
    const float_z EULER_ANGLE_Y = SAngle::_180;
    const float_z EULER_ANGLE_Z = SAngle::_45;
#endif

    const TranslationMatrix<MatrixType> TRANSLATION = TranslationMatrix<MatrixType>(SFloat::_2, SFloat::_4, -SFloat::_6);
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);
    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3(SFloat::_0_25, SFloat::_3, -SFloat::_1);

    const TransformationMatrix<MatrixType> TRANSFORMATION = TransformationMatrix<MatrixType>(TRANSLATION, ROTATION, SCALE);

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// [Execution]
    Hexahedron<T> returnedHexahedron = HEXAHEDRON.TransformWithPivot(TRANSFORMATION, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that a common hexahedron is correctly transformed using common transformation matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( TransformWithPivot_CommonHexahedronIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Test, TTemplateTypes )
{

    BOOST_TEST_MESSAGE("MatrixType=Matrix4x3");
    TransformWithPivot_CommonHexahedronIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Template<T, Matrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=Matrix4x4");
    TransformWithPivot_CommonHexahedronIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Template<T, Matrix4x4>();
}

/// <summary>
/// Template method used by TransformWithPivot_HexahedronVerticesAreMovedToCoordinateOriginWhenTransformationIsZero_Test to test
/// using different template parameters for class TransformationMatrix.
/// </summary>
template<class T, class MatrixType>
void TransformWithPivot_HexahedronVerticesAreMovedToCoordinateOriginWhenTransformationIsZero_Template()
{
    // [Preparation]
    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>::GetUnitCube();

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const T EXPECTED_VALUE_FOR_A = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_B = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_C = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_D = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_E = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_F = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_G = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_H = PIVOT_POINT;

    const TransformationMatrix<MatrixType> TRANSFORMATION = MatrixType::GetNullMatrix();

	// [Execution]
    Hexahedron<T> returnedHexahedron = HEXAHEDRON.TransformWithPivot(TRANSFORMATION, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that all the vertices of the hexahedron are moved to the coordinate origin when transformation is zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( TransformWithPivot_HexahedronVerticesAreMovedToCoordinateOriginWhenTransformationIsZero_Test, TTemplateTypes )
{

    BOOST_TEST_MESSAGE("MatrixType=Matrix4x3");
    TransformWithPivot_HexahedronVerticesAreMovedToCoordinateOriginWhenTransformationIsZero_Template<T, Matrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=Matrix4x4");
    TransformWithPivot_HexahedronVerticesAreMovedToCoordinateOriginWhenTransformationIsZero_Template<T, Matrix4x4>();
}

/// <summary>
/// Template method used by TransformWithPivot_HexahedronIsNotTransformedWhenTransformationMatrixEqualsIdentity_Test to test
/// using different template parameters for class TransformationMatrix.
/// </summary>
template<class T, class MatrixType>
void TransformWithPivot_HexahedronIsNotTransformedWhenTransformationMatrixEqualsIdentity_Template()
{
    // [Preparation]
    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>::GetUnitCube();

    const T EXPECTED_VALUE_FOR_A = HEXAHEDRON.A;
    const T EXPECTED_VALUE_FOR_B = HEXAHEDRON.B;
    const T EXPECTED_VALUE_FOR_C = HEXAHEDRON.C;
    const T EXPECTED_VALUE_FOR_D = HEXAHEDRON.D;
    const T EXPECTED_VALUE_FOR_E = HEXAHEDRON.E;
    const T EXPECTED_VALUE_FOR_F = HEXAHEDRON.F;
    const T EXPECTED_VALUE_FOR_G = HEXAHEDRON.G;
    const T EXPECTED_VALUE_FOR_H = HEXAHEDRON.H;

    const TransformationMatrix<MatrixType> TRANSFORMATION = MatrixType::GetIdentity();

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// [Execution]
    Hexahedron<T> returnedHexahedron = HEXAHEDRON.TransformWithPivot(TRANSFORMATION, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_VALUE_FOR_D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_VALUE_FOR_E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_VALUE_FOR_F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_VALUE_FOR_G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_VALUE_FOR_H);
}

/// <summary>
/// Checks that a hexahedron is not transformed when matrix equals identity.
/// </summary>
ZTEST_CASE_TEMPLATE ( TransformWithPivot_HexahedronIsNotTransformedWhenTransformationMatrixEqualsIdentity_Test, TTemplateTypes )
{

    BOOST_TEST_MESSAGE("MatrixType=Matrix4x3");
    TransformWithPivot_HexahedronIsNotTransformedWhenTransformationMatrixEqualsIdentity_Template<T, Matrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=Matrix4x4");
    TransformWithPivot_HexahedronIsNotTransformedWhenTransformationMatrixEqualsIdentity_Template<T, Matrix4x4>();
}

/// <summary>
/// Checks that it returns true when the hexahedrons share one vertex.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection_ReturnsTrueWhenHexahedronsShareVertex_Test, TTemplateTypes )
{
    // Explanation: Let's say we have a cube compound of 19 smaller cubes (every face is made of 9 smaller faces).
    //              We take the central cube as the operand 1.
    //              The operand 2 will be one of the other cubes that only shares one vertex with the central one.
    //              So we have 8 cubes that can act as the operand 2, at the corners of the main cube.
    //              This way we can test for the intersection of the shared vertices.
    //              To test all the possible vertex intersections between operands 2 and operand 1, we can
    //              rotate every operand 2 eight times, once for every vertex, keeping the operand 1 fixed.
    //              Since it's a commutative operation, we can skip calculations for 4 of the operands 2. Notice
    //              that inverting the operands we are testing the same case as if we used the opposite small cube.

    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z QUARTER_ROTATION = SAngle::_90;
    const float_z HALF_ROTATION = SAngle::_180;
    const float_z THREEQUARTERS_ROTATION = SAngle::_270;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z QUARTER_ROTATION = SAngle::_HalfPi;
    const float_z HALF_ROTATION = SAngle::_Pi;
    const float_z THREEQUARTERS_ROTATION = SAngle::_3HalfsPi;
#endif

    const Hexahedron<T> HEXAHEDRON2 = Hexahedron<T>::GetUnitCube();
    const Hexahedron<T> HEXAHEDRON1 = HEXAHEDRON2;

    const Vector3 TRANSLATION_POS1 = Vector3(-SFloat::_1, SFloat::_1, SFloat::_1);
    const Vector3 TRANSLATION_POS2 = Vector3(-SFloat::_1, -SFloat::_1, SFloat::_1);
    const Vector3 TRANSLATION_POS3 = Vector3(-SFloat::_1, SFloat::_1, -SFloat::_1);
    const Vector3 TRANSLATION_POS4 = Vector3(-SFloat::_1, -SFloat::_1, -SFloat::_1);

    const Hexahedron<T> HEXAHEDRON1_POS1_ROT1 = HEXAHEDRON1.Translate(TRANSLATION_POS1);
    const Hexahedron<T> HEXAHEDRON1_POS1_ROT2 = HEXAHEDRON1.Rotate(Quaternion(QUARTER_ROTATION, SFloat::_0, SFloat::_0)).Translate(TRANSLATION_POS1);
    const Hexahedron<T> HEXAHEDRON1_POS1_ROT3 = HEXAHEDRON1.Rotate(Quaternion(HALF_ROTATION, SFloat::_0, SFloat::_0)).Translate(TRANSLATION_POS1);
    const Hexahedron<T> HEXAHEDRON1_POS1_ROT4 = HEXAHEDRON1.Rotate(Quaternion(THREEQUARTERS_ROTATION, SFloat::_0, SFloat::_0)).Translate(TRANSLATION_POS1);
    const Hexahedron<T> HEXAHEDRON1_POS1_ROT5 = HEXAHEDRON1.Rotate(Quaternion(SFloat::_0, QUARTER_ROTATION, SFloat::_0)).Translate(TRANSLATION_POS1);
    const Hexahedron<T> HEXAHEDRON1_POS1_ROT6 = HEXAHEDRON1.Rotate(Quaternion(SFloat::_0, HALF_ROTATION, SFloat::_0)).Translate(TRANSLATION_POS1);
    const Hexahedron<T> HEXAHEDRON1_POS1_ROT7 = HEXAHEDRON1.Rotate(Quaternion(QUARTER_ROTATION, QUARTER_ROTATION, SFloat::_0)).Translate(TRANSLATION_POS1);
    const Hexahedron<T> HEXAHEDRON1_POS1_ROT8 = HEXAHEDRON1.Rotate(Quaternion(-QUARTER_ROTATION, HALF_ROTATION, SFloat::_0)).Translate(TRANSLATION_POS1);

    const Hexahedron<T> HEXAHEDRON1_POS2_ROT1 = HEXAHEDRON1.Translate(TRANSLATION_POS2);
    const Hexahedron<T> HEXAHEDRON1_POS2_ROT2 = HEXAHEDRON1.Rotate(Quaternion(QUARTER_ROTATION, SFloat::_0, SFloat::_0)).Translate(TRANSLATION_POS2);
    const Hexahedron<T> HEXAHEDRON1_POS2_ROT3 = HEXAHEDRON1.Rotate(Quaternion(HALF_ROTATION, SFloat::_0, SFloat::_0)).Translate(TRANSLATION_POS2);
    const Hexahedron<T> HEXAHEDRON1_POS2_ROT4 = HEXAHEDRON1.Rotate(Quaternion(THREEQUARTERS_ROTATION, SFloat::_0, SFloat::_0)).Translate(TRANSLATION_POS2);
    const Hexahedron<T> HEXAHEDRON1_POS2_ROT5 = HEXAHEDRON1.Rotate(Quaternion(SFloat::_0, QUARTER_ROTATION, SFloat::_0)).Translate(TRANSLATION_POS2);
    const Hexahedron<T> HEXAHEDRON1_POS2_ROT6 = HEXAHEDRON1.Rotate(Quaternion(SFloat::_0, HALF_ROTATION, SFloat::_0)).Translate(TRANSLATION_POS2);
    const Hexahedron<T> HEXAHEDRON1_POS2_ROT7 = HEXAHEDRON1.Rotate(Quaternion(QUARTER_ROTATION, QUARTER_ROTATION, SFloat::_0)).Translate(TRANSLATION_POS2);
    const Hexahedron<T> HEXAHEDRON1_POS2_ROT8 = HEXAHEDRON1.Rotate(Quaternion(-QUARTER_ROTATION, HALF_ROTATION, SFloat::_0)).Translate(TRANSLATION_POS2);

    const Hexahedron<T> HEXAHEDRON1_POS3_ROT1 = HEXAHEDRON1.Translate(TRANSLATION_POS3);
    const Hexahedron<T> HEXAHEDRON1_POS3_ROT2 = HEXAHEDRON1.Rotate(Quaternion(QUARTER_ROTATION, SFloat::_0, SFloat::_0)).Translate(TRANSLATION_POS3);
    const Hexahedron<T> HEXAHEDRON1_POS3_ROT3 = HEXAHEDRON1.Rotate(Quaternion(HALF_ROTATION, SFloat::_0, SFloat::_0)).Translate(TRANSLATION_POS3);
    const Hexahedron<T> HEXAHEDRON1_POS3_ROT4 = HEXAHEDRON1.Rotate(Quaternion(THREEQUARTERS_ROTATION, SFloat::_0, SFloat::_0)).Translate(TRANSLATION_POS3);
    const Hexahedron<T> HEXAHEDRON1_POS3_ROT5 = HEXAHEDRON1.Rotate(Quaternion(SFloat::_0, QUARTER_ROTATION, SFloat::_0)).Translate(TRANSLATION_POS3);
    const Hexahedron<T> HEXAHEDRON1_POS3_ROT6 = HEXAHEDRON1.Rotate(Quaternion(SFloat::_0, HALF_ROTATION, SFloat::_0)).Translate(TRANSLATION_POS3);
    const Hexahedron<T> HEXAHEDRON1_POS3_ROT7 = HEXAHEDRON1.Rotate(Quaternion(QUARTER_ROTATION, QUARTER_ROTATION, SFloat::_0)).Translate(TRANSLATION_POS3);
    const Hexahedron<T> HEXAHEDRON1_POS3_ROT8 = HEXAHEDRON1.Rotate(Quaternion(-QUARTER_ROTATION, HALF_ROTATION, SFloat::_0)).Translate(TRANSLATION_POS3);

    const Hexahedron<T> HEXAHEDRON1_POS4_ROT1 = HEXAHEDRON1.Translate(TRANSLATION_POS4);
    const Hexahedron<T> HEXAHEDRON1_POS4_ROT2 = HEXAHEDRON1.Rotate(Quaternion(QUARTER_ROTATION, SFloat::_0, SFloat::_0)).Translate(TRANSLATION_POS4);
    const Hexahedron<T> HEXAHEDRON1_POS4_ROT3 = HEXAHEDRON1.Rotate(Quaternion(HALF_ROTATION, SFloat::_0, SFloat::_0)).Translate(TRANSLATION_POS4);
    const Hexahedron<T> HEXAHEDRON1_POS4_ROT4 = HEXAHEDRON1.Rotate(Quaternion(THREEQUARTERS_ROTATION, SFloat::_0, SFloat::_0)).Translate(TRANSLATION_POS4);
    const Hexahedron<T> HEXAHEDRON1_POS4_ROT5 = HEXAHEDRON1.Rotate(Quaternion(SFloat::_0, QUARTER_ROTATION, SFloat::_0)).Translate(TRANSLATION_POS4);
    const Hexahedron<T> HEXAHEDRON1_POS4_ROT6 = HEXAHEDRON1.Rotate(Quaternion(SFloat::_0, HALF_ROTATION, SFloat::_0)).Translate(TRANSLATION_POS4);
    const Hexahedron<T> HEXAHEDRON1_POS4_ROT7 = HEXAHEDRON1.Rotate(Quaternion(QUARTER_ROTATION, QUARTER_ROTATION, SFloat::_0)).Translate(TRANSLATION_POS4);
    const Hexahedron<T> HEXAHEDRON1_POS4_ROT8 = HEXAHEDRON1.Rotate(Quaternion(-QUARTER_ROTATION, HALF_ROTATION, SFloat::_0)).Translate(TRANSLATION_POS4);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultP1R1 = HEXAHEDRON1_POS1_ROT1.Intersection(HEXAHEDRON2);
    bool bResultP1R2 = HEXAHEDRON1_POS1_ROT2.Intersection(HEXAHEDRON2);
    bool bResultP1R3 = HEXAHEDRON1_POS1_ROT3.Intersection(HEXAHEDRON2);
    bool bResultP1R4 = HEXAHEDRON1_POS1_ROT4.Intersection(HEXAHEDRON2);
    bool bResultP1R5 = HEXAHEDRON1_POS1_ROT5.Intersection(HEXAHEDRON2);
    bool bResultP1R6 = HEXAHEDRON1_POS1_ROT6.Intersection(HEXAHEDRON2);
    bool bResultP1R7 = HEXAHEDRON1_POS1_ROT7.Intersection(HEXAHEDRON2);
    bool bResultP1R8 = HEXAHEDRON1_POS1_ROT8.Intersection(HEXAHEDRON2);

    bool bResultP2R1 = HEXAHEDRON1_POS2_ROT1.Intersection(HEXAHEDRON2);
    bool bResultP2R2 = HEXAHEDRON1_POS2_ROT2.Intersection(HEXAHEDRON2);
    bool bResultP2R3 = HEXAHEDRON1_POS2_ROT3.Intersection(HEXAHEDRON2);
    bool bResultP2R4 = HEXAHEDRON1_POS2_ROT4.Intersection(HEXAHEDRON2);
    bool bResultP2R5 = HEXAHEDRON1_POS2_ROT5.Intersection(HEXAHEDRON2);
    bool bResultP2R6 = HEXAHEDRON1_POS2_ROT6.Intersection(HEXAHEDRON2);
    bool bResultP2R7 = HEXAHEDRON1_POS2_ROT7.Intersection(HEXAHEDRON2);
    bool bResultP2R8 = HEXAHEDRON1_POS2_ROT8.Intersection(HEXAHEDRON2);

    bool bResultP3R1 = HEXAHEDRON1_POS3_ROT1.Intersection(HEXAHEDRON2);
    bool bResultP3R2 = HEXAHEDRON1_POS3_ROT2.Intersection(HEXAHEDRON2);
    bool bResultP3R3 = HEXAHEDRON1_POS3_ROT3.Intersection(HEXAHEDRON2);
    bool bResultP3R4 = HEXAHEDRON1_POS3_ROT4.Intersection(HEXAHEDRON2);
    bool bResultP3R5 = HEXAHEDRON1_POS3_ROT5.Intersection(HEXAHEDRON2);
    bool bResultP3R6 = HEXAHEDRON1_POS3_ROT6.Intersection(HEXAHEDRON2);
    bool bResultP3R7 = HEXAHEDRON1_POS3_ROT7.Intersection(HEXAHEDRON2);
    bool bResultP3R8 = HEXAHEDRON1_POS3_ROT8.Intersection(HEXAHEDRON2);

    bool bResultP4R1 = HEXAHEDRON1_POS4_ROT1.Intersection(HEXAHEDRON2);
    bool bResultP4R2 = HEXAHEDRON1_POS4_ROT2.Intersection(HEXAHEDRON2);
    bool bResultP4R3 = HEXAHEDRON1_POS4_ROT3.Intersection(HEXAHEDRON2);
    bool bResultP4R4 = HEXAHEDRON1_POS4_ROT4.Intersection(HEXAHEDRON2);
    bool bResultP4R5 = HEXAHEDRON1_POS4_ROT5.Intersection(HEXAHEDRON2);
    bool bResultP4R6 = HEXAHEDRON1_POS4_ROT6.Intersection(HEXAHEDRON2);
    bool bResultP4R7 = HEXAHEDRON1_POS4_ROT7.Intersection(HEXAHEDRON2);
    bool bResultP4R8 = HEXAHEDRON1_POS4_ROT8.Intersection(HEXAHEDRON2);

    bool bResultP5R1 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS1_ROT1);
    bool bResultP5R2 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS1_ROT2);
    bool bResultP5R3 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS1_ROT3);
    bool bResultP5R4 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS1_ROT4);
    bool bResultP5R5 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS1_ROT5);
    bool bResultP5R6 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS1_ROT6);
    bool bResultP5R7 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS1_ROT7);
    bool bResultP5R8 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS1_ROT8);

    bool bResultP6R1 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS2_ROT1);
    bool bResultP6R2 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS2_ROT2);
    bool bResultP6R3 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS2_ROT3);
    bool bResultP6R4 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS2_ROT4);
    bool bResultP6R5 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS2_ROT5);
    bool bResultP6R6 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS2_ROT6);
    bool bResultP6R7 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS2_ROT7);
    bool bResultP6R8 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS2_ROT8);

    bool bResultP7R1 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS3_ROT1);
    bool bResultP7R2 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS3_ROT2);
    bool bResultP7R3 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS3_ROT3);
    bool bResultP7R4 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS3_ROT4);
    bool bResultP7R5 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS3_ROT5);
    bool bResultP7R6 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS3_ROT6);
    bool bResultP7R7 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS3_ROT7);
    bool bResultP7R8 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS3_ROT8);

    bool bResultP8R1 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS4_ROT1);
    bool bResultP8R2 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS4_ROT2);
    bool bResultP8R3 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS4_ROT3);
    bool bResultP8R4 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS4_ROT4);
    bool bResultP8R5 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS4_ROT5);
    bool bResultP8R6 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS4_ROT6);
    bool bResultP8R7 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS4_ROT7);
    bool bResultP8R8 = HEXAHEDRON2.Intersection(HEXAHEDRON1_POS4_ROT8);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultP1R1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP1R2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP1R3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP1R4, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP1R5, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP1R6, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP1R7, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP1R8, EXPECTED_RESULT);

    BOOST_CHECK_EQUAL(bResultP2R1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP2R2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP2R3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP2R4, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP2R5, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP2R6, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP2R7, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP2R8, EXPECTED_RESULT);

    BOOST_CHECK_EQUAL(bResultP3R1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP3R2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP3R3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP3R4, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP3R5, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP3R6, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP3R7, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP3R8, EXPECTED_RESULT);

    BOOST_CHECK_EQUAL(bResultP4R1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP4R2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP4R3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP4R4, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP4R5, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP4R6, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP4R7, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP4R8, EXPECTED_RESULT);

    BOOST_CHECK_EQUAL(bResultP5R1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP5R2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP5R3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP5R4, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP5R5, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP5R6, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP5R7, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP5R8, EXPECTED_RESULT);

    BOOST_CHECK_EQUAL(bResultP6R1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP6R2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP6R3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP6R4, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP6R5, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP6R6, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP6R7, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP6R8, EXPECTED_RESULT);

    BOOST_CHECK_EQUAL(bResultP7R1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP7R2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP7R3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP7R4, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP7R5, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP7R6, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP7R7, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP7R8, EXPECTED_RESULT);

    BOOST_CHECK_EQUAL(bResultP8R1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP8R2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP8R3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP8R4, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP8R5, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP8R6, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP8R7, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultP8R8, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the hexahedrons coincide.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection_ReturnsTrueWhenHexahedronsCoincide_Test, TTemplateTypes )
{
    // [Preparation]
    const Hexahedron<T> HEXAHEDRON1 = Hexahedron<T>::GetUnitCube();
    const Hexahedron<T> HEXAHEDRON2 = HEXAHEDRON1;

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = HEXAHEDRON1.Intersection(HEXAHEDRON2);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when one of the hexahedrons in inside the other.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection_ReturnsTrueWhenOneHexahedronsIsInsideTheOther_Test, TTemplateTypes )
{
    // [Preparation]
    const Hexahedron<T> HEXAHEDRON1 = Hexahedron<T>::GetUnitCube();
    const Hexahedron<T> HEXAHEDRON2 = HEXAHEDRON1.Scale(SFloat::_0_5, SFloat::_0_5, SFloat::_0_5);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = HEXAHEDRON1.Intersection(HEXAHEDRON2);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when one of the hexahedrons intersect.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection_ReturnsTrueWhenHexahedronsIntersect_Test, TTemplateTypes )
{
    // [Preparation]
    const Hexahedron<T> HEXAHEDRON1 = Hexahedron<T>::GetUnitCube();
    const Hexahedron<T> HEXAHEDRON2 = HEXAHEDRON1.Translate(SFloat::_0_5, SFloat::_0_5, SFloat::_0_5);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = HEXAHEDRON1.Intersection(HEXAHEDRON2);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the hexahedrons don't intersect.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection_ReturnsFalseWhenHexahedronsDoNotIntersect_Test, TTemplateTypes )
{
    // [Preparation]
    const Hexahedron<T> HEXAHEDRON1 = Hexahedron<T>::GetUnitCube();
    const Hexahedron<T> HEXAHEDRON2 = HEXAHEDRON1.Translate(SFloat::_10, SFloat::_0, SFloat::_0);

    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = HEXAHEDRON1.Intersection(HEXAHEDRON2);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the the face of one hexahedron is pierced by a corner of the other hexahedron.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection_ReturnsTrueWhenTheFaceOfOneHexahedronIsPiercedByACornerOfTheOther_Test, TTemplateTypes )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z QUARTER_ROTATION = SAngle::_90;
    const float_z HALF_ROTATION = SAngle::_180;
    const float_z THREEQUARTERS_ROTATION = SAngle::_270;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z QUARTER_ROTATION = SAngle::_HalfPi;
    const float_z HALF_ROTATION = SAngle::_Pi;
    const float_z THREEQUARTERS_ROTATION = SAngle::_3HalfsPi;
#endif

    const Hexahedron<T> HEXAHEDRON2 = Hexahedron<T>::GetUnitCube();
    const Hexahedron<T> HEXAHEDRON1 = Hexahedron<T>::GetUnitCube().Rotate(Quaternion(SAngle::_QuarterPi, SAngle::_QuarterPi, SFloat::_0));

    // Faces
    const Vector3 TRANSLATION = Vector3(SFloat::_1, SFloat::_0, SFloat::_0);
    const Hexahedron<T> HEXAHEDRON1_ROT1 = HEXAHEDRON1.Translate(TRANSLATION);
    const Hexahedron<T> HEXAHEDRON1_ROT2 = HEXAHEDRON1.Rotate(Quaternion(SFloat::_0, QUARTER_ROTATION, SFloat::_0)).Translate(TRANSLATION);
    const Hexahedron<T> HEXAHEDRON1_ROT3 = HEXAHEDRON1.Rotate(Quaternion(SFloat::_0, HALF_ROTATION, SFloat::_0)).Translate(TRANSLATION);
    const Hexahedron<T> HEXAHEDRON1_ROT4 = HEXAHEDRON1.Rotate(Quaternion(SFloat::_0, -QUARTER_ROTATION, SFloat::_0)).Translate(TRANSLATION);
    const Hexahedron<T> HEXAHEDRON1_ROT5 = HEXAHEDRON1.Rotate(Quaternion(SFloat::_0, SFloat::_0, QUARTER_ROTATION)).Translate(TRANSLATION);
    const Hexahedron<T> HEXAHEDRON1_ROT6 = HEXAHEDRON1.Rotate(Quaternion(SFloat::_0, SFloat::_0, -QUARTER_ROTATION)).Translate(TRANSLATION);

    // Corners
    const Hexahedron<T> HEXAHEDRON2_ROT1 = HEXAHEDRON2;
    const Hexahedron<T> HEXAHEDRON2_ROT2 = HEXAHEDRON2.Rotate(Quaternion(QUARTER_ROTATION, SFloat::_0, SFloat::_0));
    const Hexahedron<T> HEXAHEDRON2_ROT3 = HEXAHEDRON2.Rotate(Quaternion(HALF_ROTATION, SFloat::_0, SFloat::_0));
    const Hexahedron<T> HEXAHEDRON2_ROT4 = HEXAHEDRON2.Rotate(Quaternion(THREEQUARTERS_ROTATION, SFloat::_0, SFloat::_0));
    const Hexahedron<T> HEXAHEDRON2_ROT5 = HEXAHEDRON2.Rotate(Quaternion(SFloat::_0, QUARTER_ROTATION, SFloat::_0));
    const Hexahedron<T> HEXAHEDRON2_ROT6 = HEXAHEDRON2.Rotate(Quaternion(SFloat::_0, HALF_ROTATION, SFloat::_0));
    const Hexahedron<T> HEXAHEDRON2_ROT7 = HEXAHEDRON2.Rotate(Quaternion(QUARTER_ROTATION, QUARTER_ROTATION, SFloat::_0));
    const Hexahedron<T> HEXAHEDRON2_ROT8 = HEXAHEDRON2.Rotate(Quaternion(-QUARTER_ROTATION, HALF_ROTATION, SFloat::_0));

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultH1R1_H2R1 = HEXAHEDRON1_ROT1.Intersection(HEXAHEDRON2_ROT1);
    bool bResultH1R2_H2R1 = HEXAHEDRON1_ROT2.Intersection(HEXAHEDRON2_ROT1);
    bool bResultH1R3_H2R1 = HEXAHEDRON1_ROT3.Intersection(HEXAHEDRON2_ROT1);
    bool bResultH1R4_H2R1 = HEXAHEDRON1_ROT4.Intersection(HEXAHEDRON2_ROT1);
    bool bResultH1R5_H2R1 = HEXAHEDRON1_ROT5.Intersection(HEXAHEDRON2_ROT1);
    bool bResultH1R6_H2R1 = HEXAHEDRON1_ROT6.Intersection(HEXAHEDRON2_ROT1);

    bool bResultH1R1_H2R2 = HEXAHEDRON1_ROT1.Intersection(HEXAHEDRON2_ROT2);
    bool bResultH1R2_H2R2 = HEXAHEDRON1_ROT2.Intersection(HEXAHEDRON2_ROT2);
    bool bResultH1R3_H2R2 = HEXAHEDRON1_ROT3.Intersection(HEXAHEDRON2_ROT2);
    bool bResultH1R4_H2R2 = HEXAHEDRON1_ROT4.Intersection(HEXAHEDRON2_ROT2);
    bool bResultH1R5_H2R2 = HEXAHEDRON1_ROT5.Intersection(HEXAHEDRON2_ROT2);
    bool bResultH1R6_H2R2 = HEXAHEDRON1_ROT6.Intersection(HEXAHEDRON2_ROT2);

    bool bResultH1R1_H2R3 = HEXAHEDRON1_ROT1.Intersection(HEXAHEDRON2_ROT3);
    bool bResultH1R2_H2R3 = HEXAHEDRON1_ROT2.Intersection(HEXAHEDRON2_ROT3);
    bool bResultH1R3_H2R3 = HEXAHEDRON1_ROT3.Intersection(HEXAHEDRON2_ROT3);
    bool bResultH1R4_H2R3 = HEXAHEDRON1_ROT4.Intersection(HEXAHEDRON2_ROT3);
    bool bResultH1R5_H2R3 = HEXAHEDRON1_ROT5.Intersection(HEXAHEDRON2_ROT3);
    bool bResultH1R6_H2R3 = HEXAHEDRON1_ROT6.Intersection(HEXAHEDRON2_ROT3);

    bool bResultH1R1_H2R4 = HEXAHEDRON1_ROT1.Intersection(HEXAHEDRON2_ROT4);
    bool bResultH1R2_H2R4 = HEXAHEDRON1_ROT2.Intersection(HEXAHEDRON2_ROT4);
    bool bResultH1R3_H2R4 = HEXAHEDRON1_ROT3.Intersection(HEXAHEDRON2_ROT4);
    bool bResultH1R4_H2R4 = HEXAHEDRON1_ROT4.Intersection(HEXAHEDRON2_ROT4);
    bool bResultH1R5_H2R4 = HEXAHEDRON1_ROT5.Intersection(HEXAHEDRON2_ROT4);
    bool bResultH1R6_H2R4 = HEXAHEDRON1_ROT6.Intersection(HEXAHEDRON2_ROT4);

    bool bResultH1R1_H2R5 = HEXAHEDRON1_ROT1.Intersection(HEXAHEDRON2_ROT5);
    bool bResultH1R2_H2R5 = HEXAHEDRON1_ROT2.Intersection(HEXAHEDRON2_ROT5);
    bool bResultH1R3_H2R5 = HEXAHEDRON1_ROT3.Intersection(HEXAHEDRON2_ROT5);
    bool bResultH1R4_H2R5 = HEXAHEDRON1_ROT4.Intersection(HEXAHEDRON2_ROT5);
    bool bResultH1R5_H2R5 = HEXAHEDRON1_ROT5.Intersection(HEXAHEDRON2_ROT5);
    bool bResultH1R6_H2R5 = HEXAHEDRON1_ROT6.Intersection(HEXAHEDRON2_ROT5);

    bool bResultH1R1_H2R6 = HEXAHEDRON1_ROT1.Intersection(HEXAHEDRON2_ROT6);
    bool bResultH1R2_H2R6 = HEXAHEDRON1_ROT2.Intersection(HEXAHEDRON2_ROT6);
    bool bResultH1R3_H2R6 = HEXAHEDRON1_ROT3.Intersection(HEXAHEDRON2_ROT6);
    bool bResultH1R4_H2R6 = HEXAHEDRON1_ROT4.Intersection(HEXAHEDRON2_ROT6);
    bool bResultH1R5_H2R6 = HEXAHEDRON1_ROT5.Intersection(HEXAHEDRON2_ROT6);
    bool bResultH1R6_H2R6 = HEXAHEDRON1_ROT6.Intersection(HEXAHEDRON2_ROT6);

    bool bResultH1R1_H2R7 = HEXAHEDRON1_ROT1.Intersection(HEXAHEDRON2_ROT7);
    bool bResultH1R2_H2R7 = HEXAHEDRON1_ROT2.Intersection(HEXAHEDRON2_ROT7);
    bool bResultH1R3_H2R7 = HEXAHEDRON1_ROT3.Intersection(HEXAHEDRON2_ROT7);
    bool bResultH1R4_H2R7 = HEXAHEDRON1_ROT4.Intersection(HEXAHEDRON2_ROT7);
    bool bResultH1R5_H2R7 = HEXAHEDRON1_ROT5.Intersection(HEXAHEDRON2_ROT7);
    bool bResultH1R6_H2R7 = HEXAHEDRON1_ROT6.Intersection(HEXAHEDRON2_ROT7);

    bool bResultH1R1_H2R8 = HEXAHEDRON1_ROT1.Intersection(HEXAHEDRON2_ROT8);
    bool bResultH1R2_H2R8 = HEXAHEDRON1_ROT2.Intersection(HEXAHEDRON2_ROT8);
    bool bResultH1R3_H2R8 = HEXAHEDRON1_ROT3.Intersection(HEXAHEDRON2_ROT8);
    bool bResultH1R4_H2R8 = HEXAHEDRON1_ROT4.Intersection(HEXAHEDRON2_ROT8);
    bool bResultH1R5_H2R8 = HEXAHEDRON1_ROT5.Intersection(HEXAHEDRON2_ROT8);
    bool bResultH1R6_H2R8 = HEXAHEDRON1_ROT6.Intersection(HEXAHEDRON2_ROT8);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultH1R1_H2R1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R2_H2R1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R3_H2R1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R4_H2R1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R5_H2R1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R6_H2R1, EXPECTED_RESULT);

    BOOST_CHECK_EQUAL(bResultH1R1_H2R2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R2_H2R2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R3_H2R2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R4_H2R2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R5_H2R2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R6_H2R2, EXPECTED_RESULT);

    BOOST_CHECK_EQUAL(bResultH1R1_H2R3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R2_H2R3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R3_H2R3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R4_H2R3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R5_H2R3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R6_H2R3, EXPECTED_RESULT);

    BOOST_CHECK_EQUAL(bResultH1R1_H2R4, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R2_H2R4, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R3_H2R4, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R4_H2R4, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R5_H2R4, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R6_H2R4, EXPECTED_RESULT);

    BOOST_CHECK_EQUAL(bResultH1R1_H2R5, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R2_H2R5, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R3_H2R5, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R4_H2R5, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R5_H2R5, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R6_H2R5, EXPECTED_RESULT);

    BOOST_CHECK_EQUAL(bResultH1R1_H2R6, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R2_H2R6, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R3_H2R6, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R4_H2R6, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R5_H2R6, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R6_H2R6, EXPECTED_RESULT);

    BOOST_CHECK_EQUAL(bResultH1R1_H2R7, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R2_H2R7, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R3_H2R7, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R4_H2R7, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R5_H2R7, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R6_H2R7, EXPECTED_RESULT);

    BOOST_CHECK_EQUAL(bResultH1R1_H2R8, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R2_H2R8, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R3_H2R8, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R4_H2R8, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R5_H2R8, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R6_H2R8, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when one hexahedron is pierced by an edge of the other hexahedron.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection_ReturnsTrueWhenTheOneHexahedronIsPiercedByAnEdgeOfTheOther_Test, TTemplateTypes )
{
    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const Quaternion INITIAL_ROTATION = Quaternion(SAngle::_45, SAngle::_45, SFloat::_0);
    const float_z QUARTER_ROTATION = SAngle::_90;
    const float_z HALF_ROTATION = SAngle::_180;
    const float_z THREEQUARTERS_ROTATION = SAngle::_270;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const Quaternion INITIAL_ROTATION = Quaternion(SAngle::_QuarterPi, SAngle::_QuarterPi, SFloat::_0);
    const float_z QUARTER_ROTATION = SAngle::_HalfPi;
    const float_z HALF_ROTATION = SAngle::_Pi;
    const float_z THREEQUARTERS_ROTATION = SAngle::_3HalfsPi;
#endif

    const Hexahedron<T> HEXAHEDRON2 = Hexahedron<T>::GetUnitCube();
    const Hexahedron<T> HEXAHEDRON1 = Hexahedron<T>::GetUnitCube().Rotate(INITIAL_ROTATION);
    
    // Faces
    const Vector3 TRANSLATION = Vector3((float_z)0.6, (float_z)1.0, SFloat::_0);
    const Hexahedron<T> HEXAHEDRON1_ROT1 = HEXAHEDRON1.Translate(TRANSLATION);
    const Hexahedron<T> HEXAHEDRON1_ROT2 = HEXAHEDRON1.Rotate(Quaternion(SFloat::_0, QUARTER_ROTATION, SFloat::_0)).Translate(TRANSLATION);
    const Hexahedron<T> HEXAHEDRON1_ROT3 = HEXAHEDRON1.Rotate(Quaternion(SFloat::_0, HALF_ROTATION, SFloat::_0)).Translate(TRANSLATION);
    const Hexahedron<T> HEXAHEDRON1_ROT4 = HEXAHEDRON1.Rotate(Quaternion(SFloat::_0, -QUARTER_ROTATION, SFloat::_0)).Translate(TRANSLATION);
    const Hexahedron<T> HEXAHEDRON1_ROT5 = HEXAHEDRON1.Rotate(Quaternion(SFloat::_0, SFloat::_0, QUARTER_ROTATION)).Translate(TRANSLATION);
    const Hexahedron<T> HEXAHEDRON1_ROT6 = HEXAHEDRON1.Rotate(Quaternion(SFloat::_0, SFloat::_0, -QUARTER_ROTATION)).Translate(TRANSLATION);

    // Corners
    const Hexahedron<T> HEXAHEDRON2_ROT1 = HEXAHEDRON2;
    const Hexahedron<T> HEXAHEDRON2_ROT2 = HEXAHEDRON2.Rotate(Quaternion(QUARTER_ROTATION, SFloat::_0, SFloat::_0));
    const Hexahedron<T> HEXAHEDRON2_ROT3 = HEXAHEDRON2.Rotate(Quaternion(HALF_ROTATION, SFloat::_0, SFloat::_0));
    const Hexahedron<T> HEXAHEDRON2_ROT4 = HEXAHEDRON2.Rotate(Quaternion(THREEQUARTERS_ROTATION, SFloat::_0, SFloat::_0));
    const Hexahedron<T> HEXAHEDRON2_ROT5 = HEXAHEDRON2.Rotate(Quaternion(SFloat::_0, QUARTER_ROTATION, SFloat::_0));
    const Hexahedron<T> HEXAHEDRON2_ROT6 = HEXAHEDRON2.Rotate(Quaternion(SFloat::_0, HALF_ROTATION, SFloat::_0));
    const Hexahedron<T> HEXAHEDRON2_ROT7 = HEXAHEDRON2.Rotate(Quaternion(QUARTER_ROTATION, QUARTER_ROTATION, SFloat::_0));
    const Hexahedron<T> HEXAHEDRON2_ROT8 = HEXAHEDRON2.Rotate(Quaternion(-QUARTER_ROTATION, HALF_ROTATION, SFloat::_0));

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultH1R1_H2R1 = HEXAHEDRON1_ROT1.Intersection(HEXAHEDRON2_ROT1);
    bool bResultH1R2_H2R1 = HEXAHEDRON1_ROT2.Intersection(HEXAHEDRON2_ROT1);
    bool bResultH1R3_H2R1 = HEXAHEDRON1_ROT3.Intersection(HEXAHEDRON2_ROT1);
    bool bResultH1R4_H2R1 = HEXAHEDRON1_ROT4.Intersection(HEXAHEDRON2_ROT1);
    bool bResultH1R5_H2R1 = HEXAHEDRON1_ROT5.Intersection(HEXAHEDRON2_ROT1);
    bool bResultH1R6_H2R1 = HEXAHEDRON1_ROT6.Intersection(HEXAHEDRON2_ROT1);

    bool bResultH1R1_H2R2 = HEXAHEDRON1_ROT1.Intersection(HEXAHEDRON2_ROT2);
    bool bResultH1R2_H2R2 = HEXAHEDRON1_ROT2.Intersection(HEXAHEDRON2_ROT2);
    bool bResultH1R3_H2R2 = HEXAHEDRON1_ROT3.Intersection(HEXAHEDRON2_ROT2);
    bool bResultH1R4_H2R2 = HEXAHEDRON1_ROT4.Intersection(HEXAHEDRON2_ROT2);
    bool bResultH1R5_H2R2 = HEXAHEDRON1_ROT5.Intersection(HEXAHEDRON2_ROT2);
    bool bResultH1R6_H2R2 = HEXAHEDRON1_ROT6.Intersection(HEXAHEDRON2_ROT2);

    bool bResultH1R1_H2R3 = HEXAHEDRON1_ROT1.Intersection(HEXAHEDRON2_ROT3);
    bool bResultH1R2_H2R3 = HEXAHEDRON1_ROT2.Intersection(HEXAHEDRON2_ROT3);
    bool bResultH1R3_H2R3 = HEXAHEDRON1_ROT3.Intersection(HEXAHEDRON2_ROT3);
    bool bResultH1R4_H2R3 = HEXAHEDRON1_ROT4.Intersection(HEXAHEDRON2_ROT3);
    bool bResultH1R5_H2R3 = HEXAHEDRON1_ROT5.Intersection(HEXAHEDRON2_ROT3);
    bool bResultH1R6_H2R3 = HEXAHEDRON1_ROT6.Intersection(HEXAHEDRON2_ROT3);

    bool bResultH1R1_H2R4 = HEXAHEDRON1_ROT1.Intersection(HEXAHEDRON2_ROT4);
    bool bResultH1R2_H2R4 = HEXAHEDRON1_ROT2.Intersection(HEXAHEDRON2_ROT4);
    bool bResultH1R3_H2R4 = HEXAHEDRON1_ROT3.Intersection(HEXAHEDRON2_ROT4);
    bool bResultH1R4_H2R4 = HEXAHEDRON1_ROT4.Intersection(HEXAHEDRON2_ROT4);
    bool bResultH1R5_H2R4 = HEXAHEDRON1_ROT5.Intersection(HEXAHEDRON2_ROT4);
    bool bResultH1R6_H2R4 = HEXAHEDRON1_ROT6.Intersection(HEXAHEDRON2_ROT4);

    bool bResultH1R1_H2R5 = HEXAHEDRON1_ROT1.Intersection(HEXAHEDRON2_ROT5);
    bool bResultH1R2_H2R5 = HEXAHEDRON1_ROT2.Intersection(HEXAHEDRON2_ROT5);
    bool bResultH1R3_H2R5 = HEXAHEDRON1_ROT3.Intersection(HEXAHEDRON2_ROT5);
    bool bResultH1R4_H2R5 = HEXAHEDRON1_ROT4.Intersection(HEXAHEDRON2_ROT5);
    bool bResultH1R5_H2R5 = HEXAHEDRON1_ROT5.Intersection(HEXAHEDRON2_ROT5);
    bool bResultH1R6_H2R5 = HEXAHEDRON1_ROT6.Intersection(HEXAHEDRON2_ROT5);

    bool bResultH1R1_H2R6 = HEXAHEDRON1_ROT1.Intersection(HEXAHEDRON2_ROT6);
    bool bResultH1R2_H2R6 = HEXAHEDRON1_ROT2.Intersection(HEXAHEDRON2_ROT6);
    bool bResultH1R3_H2R6 = HEXAHEDRON1_ROT3.Intersection(HEXAHEDRON2_ROT6);
    bool bResultH1R4_H2R6 = HEXAHEDRON1_ROT4.Intersection(HEXAHEDRON2_ROT6);
    bool bResultH1R5_H2R6 = HEXAHEDRON1_ROT5.Intersection(HEXAHEDRON2_ROT6);
    bool bResultH1R6_H2R6 = HEXAHEDRON1_ROT6.Intersection(HEXAHEDRON2_ROT6);

    bool bResultH1R1_H2R7 = HEXAHEDRON1_ROT1.Intersection(HEXAHEDRON2_ROT7);
    bool bResultH1R2_H2R7 = HEXAHEDRON1_ROT2.Intersection(HEXAHEDRON2_ROT7);
    bool bResultH1R3_H2R7 = HEXAHEDRON1_ROT3.Intersection(HEXAHEDRON2_ROT7);
    bool bResultH1R4_H2R7 = HEXAHEDRON1_ROT4.Intersection(HEXAHEDRON2_ROT7);
    bool bResultH1R5_H2R7 = HEXAHEDRON1_ROT5.Intersection(HEXAHEDRON2_ROT7);
    bool bResultH1R6_H2R7 = HEXAHEDRON1_ROT6.Intersection(HEXAHEDRON2_ROT7);

    bool bResultH1R1_H2R8 = HEXAHEDRON1_ROT1.Intersection(HEXAHEDRON2_ROT8);
    bool bResultH1R2_H2R8 = HEXAHEDRON1_ROT2.Intersection(HEXAHEDRON2_ROT8);
    bool bResultH1R3_H2R8 = HEXAHEDRON1_ROT3.Intersection(HEXAHEDRON2_ROT8);
    bool bResultH1R4_H2R8 = HEXAHEDRON1_ROT4.Intersection(HEXAHEDRON2_ROT8);
    bool bResultH1R5_H2R8 = HEXAHEDRON1_ROT5.Intersection(HEXAHEDRON2_ROT8);
    bool bResultH1R6_H2R8 = HEXAHEDRON1_ROT6.Intersection(HEXAHEDRON2_ROT8);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultH1R1_H2R1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R2_H2R1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R3_H2R1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R4_H2R1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R5_H2R1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R6_H2R1, EXPECTED_RESULT);

    BOOST_CHECK_EQUAL(bResultH1R1_H2R2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R2_H2R2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R3_H2R2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R4_H2R2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R5_H2R2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R6_H2R2, EXPECTED_RESULT);

    BOOST_CHECK_EQUAL(bResultH1R1_H2R3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R2_H2R3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R3_H2R3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R4_H2R3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R5_H2R3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R6_H2R3, EXPECTED_RESULT);

    BOOST_CHECK_EQUAL(bResultH1R1_H2R4, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R2_H2R4, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R3_H2R4, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R4_H2R4, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R5_H2R4, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R6_H2R4, EXPECTED_RESULT);

    BOOST_CHECK_EQUAL(bResultH1R1_H2R5, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R2_H2R5, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R3_H2R5, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R4_H2R5, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R5_H2R5, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R6_H2R5, EXPECTED_RESULT);

    BOOST_CHECK_EQUAL(bResultH1R1_H2R6, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R2_H2R6, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R3_H2R6, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R4_H2R6, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R5_H2R6, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R6_H2R6, EXPECTED_RESULT);

    BOOST_CHECK_EQUAL(bResultH1R1_H2R7, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R2_H2R7, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R3_H2R7, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R4_H2R7, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R5_H2R7, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R6_H2R7, EXPECTED_RESULT);

    BOOST_CHECK_EQUAL(bResultH1R1_H2R8, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R2_H2R8, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R3_H2R8, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R4_H2R8, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R5_H2R8, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultH1R6_H2R8, EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when all the vertices of the hexahedron coincide.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection_AssertionFailsWhenAllVerticesCoincide_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z POINT_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4 };
    const T POINT = T(POINT_COMPONENTS);
    const Hexahedron<T> HEXAHEDRON1 = Hexahedron<T>(POINT, POINT, POINT, POINT, POINT, POINT, POINT, POINT);
    const Hexahedron<T> HEXAHEDRON2 = Hexahedron<T>::GetUnitCube();

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        HEXAHEDRON1.Intersection(HEXAHEDRON2);
    }
    catch(const AssertException&)
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        HEXAHEDRON2.Intersection(HEXAHEDRON1);
    }
    catch(const AssertException&)
    {
        bAssertionFailed2 = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the hexahedron is correctly projected to a plane when they intersect.
/// </summary>
ZTEST_CASE_TEMPLATE ( ProjectToPlane_IsCorrectlyProjectedWhenHexahedronAndPlaneIntersect_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_2, SFloat::_3, SFloat::_2, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_4, SFloat::_3, SFloat::_2, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_D[] = { SFloat::_4, SFloat::_3, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_E[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_F[] = { SFloat::_4, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_G[] = { SFloat::_4, SFloat::_1, SFloat::_1, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_H[] = { SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_1 };

    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>(T(VECTOR_COMPONENTS_A),
                                                     T(VECTOR_COMPONENTS_B),
                                                     T(VECTOR_COMPONENTS_C),
                                                     T(VECTOR_COMPONENTS_D),
                                                     T(VECTOR_COMPONENTS_E),
                                                     T(VECTOR_COMPONENTS_F),
                                                     T(VECTOR_COMPONENTS_G),
                                                     T(VECTOR_COMPONENTS_H));

    const BasePlane PLANE = BasePlane(SFloat::_0, SFloat::_1, SFloat::_0, -SFloat::_2);

    const float_z EXPECTED_VECTOR_COMPONENTS_A[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_B[] = { SFloat::_2, SFloat::_2, SFloat::_2, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_C[] = { SFloat::_4, SFloat::_2, SFloat::_2, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_D[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_E[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_F[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_G[] = { SFloat::_4, SFloat::_2, SFloat::_1, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_H[] = { SFloat::_1, SFloat::_2, SFloat::_0, SFloat::_1 };

    const Hexahedron<T> EXPECTED_RESULT = Hexahedron<T>(T(EXPECTED_VECTOR_COMPONENTS_A),
                                                          T(EXPECTED_VECTOR_COMPONENTS_B),
                                                          T(EXPECTED_VECTOR_COMPONENTS_C),
                                                          T(EXPECTED_VECTOR_COMPONENTS_D),
                                                          T(EXPECTED_VECTOR_COMPONENTS_E),
                                                          T(EXPECTED_VECTOR_COMPONENTS_F),
                                                          T(EXPECTED_VECTOR_COMPONENTS_G),
                                                          T(EXPECTED_VECTOR_COMPONENTS_H));

	// [Execution]
    Hexahedron<T> returnedHexahedron = HEXAHEDRON.ProjectToPlane(PLANE);

    // [Verification]
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_RESULT.A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_RESULT.B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_RESULT.C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_RESULT.D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_RESULT.E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_RESULT.F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_RESULT.G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_RESULT.H);
}

/// <summary>
/// Checks that the hexahedron is correctly projected to a plane when it's in the positive side.
/// </summary>
ZTEST_CASE_TEMPLATE ( ProjectToPlane_IsCorrectlyProjectedWhenHexahedronIsInPositiveSide_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_2, SFloat::_3, SFloat::_2, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_4, SFloat::_3, SFloat::_2, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_D[] = { SFloat::_4, SFloat::_4, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_E[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_F[] = { SFloat::_4, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_G[] = { SFloat::_4, SFloat::_1, SFloat::_1, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_H[] = { SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_1 };

    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>(T(VECTOR_COMPONENTS_A),
                                                     T(VECTOR_COMPONENTS_B),
                                                     T(VECTOR_COMPONENTS_C),
                                                     T(VECTOR_COMPONENTS_D),
                                                     T(VECTOR_COMPONENTS_E),
                                                     T(VECTOR_COMPONENTS_F),
                                                     T(VECTOR_COMPONENTS_G),
                                                     T(VECTOR_COMPONENTS_H));

    const BasePlane PLANE = BasePlane(SFloat::_0, SFloat::_1, SFloat::_0, SFloat::_2);

    const float_z EXPECTED_VECTOR_COMPONENTS_A[] = { SFloat::_2, -SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_B[] = { SFloat::_2, -SFloat::_2, SFloat::_2, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_C[] = { SFloat::_4, -SFloat::_2, SFloat::_2, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_D[] = { SFloat::_4, -SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_E[] = { SFloat::_1, -SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_F[] = { SFloat::_4, -SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_G[] = { SFloat::_4, -SFloat::_2, SFloat::_1, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_H[] = { SFloat::_1, -SFloat::_2, SFloat::_0, SFloat::_1 };

    const Hexahedron<T> EXPECTED_RESULT = Hexahedron<T>(T(EXPECTED_VECTOR_COMPONENTS_A),
                                                          T(EXPECTED_VECTOR_COMPONENTS_B),
                                                          T(EXPECTED_VECTOR_COMPONENTS_C),
                                                          T(EXPECTED_VECTOR_COMPONENTS_D),
                                                          T(EXPECTED_VECTOR_COMPONENTS_E),
                                                          T(EXPECTED_VECTOR_COMPONENTS_F),
                                                          T(EXPECTED_VECTOR_COMPONENTS_G),
                                                          T(EXPECTED_VECTOR_COMPONENTS_H));

	// [Execution]
    Hexahedron<T> returnedHexahedron = HEXAHEDRON.ProjectToPlane(PLANE);

    // [Verification]
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_RESULT.A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_RESULT.B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_RESULT.C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_RESULT.D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_RESULT.E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_RESULT.F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_RESULT.G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_RESULT.H);
}

/// <summary>
/// Checks that the hexahedron is correctly projected to a plane when it's in the negative side.
/// </summary>
ZTEST_CASE_TEMPLATE ( ProjectToPlane_IsCorrectlyProjectedWhenHexahedronIsInNegativeSide_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_2, SFloat::_3, SFloat::_2, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_4, SFloat::_3, SFloat::_2, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_D[] = { SFloat::_4, SFloat::_4, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_E[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_F[] = { SFloat::_4, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_G[] = { SFloat::_4, SFloat::_1, SFloat::_1, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_H[] = { SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_1 };

    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>(T(VECTOR_COMPONENTS_A),
                                                     T(VECTOR_COMPONENTS_B),
                                                     T(VECTOR_COMPONENTS_C),
                                                     T(VECTOR_COMPONENTS_D),
                                                     T(VECTOR_COMPONENTS_E),
                                                     T(VECTOR_COMPONENTS_F),
                                                     T(VECTOR_COMPONENTS_G),
                                                     T(VECTOR_COMPONENTS_H));

    const BasePlane PLANE = BasePlane(SFloat::_0, SFloat::_1, SFloat::_0, -SFloat::_10);

    const float_z EXPECTED_VECTOR_COMPONENTS_A[] = { SFloat::_2, SFloat::_10, SFloat::_3, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_B[] = { SFloat::_2, SFloat::_10, SFloat::_2, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_C[] = { SFloat::_4, SFloat::_10, SFloat::_2, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_D[] = { SFloat::_4, SFloat::_10, SFloat::_3, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_E[] = { SFloat::_1, SFloat::_10, SFloat::_3, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_F[] = { SFloat::_4, SFloat::_10, SFloat::_3, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_G[] = { SFloat::_4, SFloat::_10, SFloat::_1, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_H[] = { SFloat::_1, SFloat::_10, SFloat::_0, SFloat::_1 };

    const Hexahedron<T> EXPECTED_RESULT = Hexahedron<T>(T(EXPECTED_VECTOR_COMPONENTS_A),
                                                          T(EXPECTED_VECTOR_COMPONENTS_B),
                                                          T(EXPECTED_VECTOR_COMPONENTS_C),
                                                          T(EXPECTED_VECTOR_COMPONENTS_D),
                                                          T(EXPECTED_VECTOR_COMPONENTS_E),
                                                          T(EXPECTED_VECTOR_COMPONENTS_F),
                                                          T(EXPECTED_VECTOR_COMPONENTS_G),
                                                          T(EXPECTED_VECTOR_COMPONENTS_H));

	// [Execution]
    Hexahedron<T> returnedHexahedron = HEXAHEDRON.ProjectToPlane(PLANE);

    // [Verification]
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_RESULT.A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_RESULT.B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_RESULT.C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_RESULT.D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_RESULT.E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_RESULT.F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_RESULT.G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_RESULT.H);
}

/// <summary>
/// Checks that the hexahedron doesn't change when it already belongs to the plane.
/// </summary>
ZTEST_CASE_TEMPLATE ( ProjectToPlane_ItDoesNotChangeWhenItAlreadyBelongsToPlane_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_2, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_2, SFloat::_1, SFloat::_2, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_4, SFloat::_1, SFloat::_2, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_D[] = { SFloat::_4, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_E[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_F[] = { SFloat::_4, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_G[] = { SFloat::_4, SFloat::_1, SFloat::_1, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_H[] = { SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_1 };

    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>(T(VECTOR_COMPONENTS_A),
                                                     T(VECTOR_COMPONENTS_B),
                                                     T(VECTOR_COMPONENTS_C),
                                                     T(VECTOR_COMPONENTS_D),
                                                     T(VECTOR_COMPONENTS_E),
                                                     T(VECTOR_COMPONENTS_F),
                                                     T(VECTOR_COMPONENTS_G),
                                                     T(VECTOR_COMPONENTS_H));

    const BasePlane PLANE = BasePlane(SFloat::_0, SFloat::_1, SFloat::_0, -SFloat::_1);

    const Hexahedron<T> EXPECTED_RESULT = HEXAHEDRON;

	// [Execution]
    Hexahedron<T> returnedHexahedron = HEXAHEDRON.ProjectToPlane(PLANE);

    // [Verification]
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_RESULT.A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_RESULT.B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_RESULT.C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_RESULT.D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_RESULT.E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_RESULT.F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_RESULT.G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_RESULT.H);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when all the vertices of the hexahedron coincide.
/// </summary>
ZTEST_CASE_TEMPLATE ( ProjectToPlane_AssertionFailsWhenAllVerticesCoincide_Test, TTemplateTypes )
{

    // [Preparation]
    const Plane PLANE = Plane(SFloat::_0, SFloat::_1, SFloat::_0, -SFloat::_1);
    const float_z POINT_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4 };
    const T POINT = T(POINT_COMPONENTS);
    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>(POINT, POINT, POINT, POINT, POINT, POINT, POINT, POINT);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        HEXAHEDRON.ProjectToPlane(PLANE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the plane is null.
/// </summary>
ZTEST_CASE_TEMPLATE ( ProjectToPlane_AssertionFailsWhenThePlaneIsNull_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_2, SFloat::_0, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_2, SFloat::_0, SFloat::_2, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_4, SFloat::_0, SFloat::_2, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_D[] = { SFloat::_4, SFloat::_0, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_E[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_F[] = { SFloat::_4, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_G[] = { SFloat::_4, SFloat::_1, SFloat::_1, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_H[] = { SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_1 };

    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>(T(VECTOR_COMPONENTS_A),
                                                     T(VECTOR_COMPONENTS_B),
                                                     T(VECTOR_COMPONENTS_C),
                                                     T(VECTOR_COMPONENTS_D),
                                                     T(VECTOR_COMPONENTS_E),
                                                     T(VECTOR_COMPONENTS_F),
                                                     T(VECTOR_COMPONENTS_G),
                                                     T(VECTOR_COMPONENTS_H));

    const BasePlane PLANE = BasePlane(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        HEXAHEDRON.ProjectToPlane(PLANE);
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
/// Checks that the hexahedron is correctly projected to a plane when all vertices of the hexahedron coincide.
/// </summary>
ZTEST_CASE_TEMPLATE ( ProjectToPlane_IsCorrectlyProjectedWhenAllVerticesCoincide_Test, TTemplateTypes )
{
    // [Preparation]
    const BasePlane PLANE = BasePlane(SFloat::_0, SFloat::_1, SFloat::_0, -SFloat::_1);
    const float_z POINT_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4 };
    const T POINT = T(POINT_COMPONENTS);
    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>(POINT, POINT, POINT, POINT, POINT, POINT, POINT, POINT);

    const float_z EXPECTED_VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_4 };
    const float_z EXPECTED_VECTOR_COMPONENTS_B[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_4 };
    const float_z EXPECTED_VECTOR_COMPONENTS_C[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_4 };
    const float_z EXPECTED_VECTOR_COMPONENTS_D[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_4 };
    const float_z EXPECTED_VECTOR_COMPONENTS_E[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_4 };
    const float_z EXPECTED_VECTOR_COMPONENTS_F[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_4 };
    const float_z EXPECTED_VECTOR_COMPONENTS_G[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_4 };
    const float_z EXPECTED_VECTOR_COMPONENTS_H[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_4 };

    const Hexahedron<T> EXPECTED_RESULT = Hexahedron<T>(T(EXPECTED_VECTOR_COMPONENTS_A),
                                                          T(EXPECTED_VECTOR_COMPONENTS_B),
                                                          T(EXPECTED_VECTOR_COMPONENTS_C),
                                                          T(EXPECTED_VECTOR_COMPONENTS_D),
                                                          T(EXPECTED_VECTOR_COMPONENTS_E),
                                                          T(EXPECTED_VECTOR_COMPONENTS_F),
                                                          T(EXPECTED_VECTOR_COMPONENTS_G),
                                                          T(EXPECTED_VECTOR_COMPONENTS_H));

	// [Execution]
    Hexahedron<T> returnedHexahedron = HEXAHEDRON.ProjectToPlane(PLANE);

    // [Verification]
    BOOST_CHECK(returnedHexahedron.A == EXPECTED_RESULT.A);
    BOOST_CHECK(returnedHexahedron.B == EXPECTED_RESULT.B);
    BOOST_CHECK(returnedHexahedron.C == EXPECTED_RESULT.C);
    BOOST_CHECK(returnedHexahedron.D == EXPECTED_RESULT.D);
    BOOST_CHECK(returnedHexahedron.E == EXPECTED_RESULT.E);
    BOOST_CHECK(returnedHexahedron.F == EXPECTED_RESULT.F);
    BOOST_CHECK(returnedHexahedron.G == EXPECTED_RESULT.G);
    BOOST_CHECK(returnedHexahedron.H == EXPECTED_RESULT.H);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the expected output string is returned.
/// </summary>
ZTEST_CASE_TEMPLATE ( ToString_ExpectedOutputIsReturned_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_8 };
    float_z VECTOR_COMPONENTS_C[] = { SFloat::_9, SFloat::_0, SFloat::_0_5, SFloat::_0_25 };
    float_z VECTOR_COMPONENTS_D[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7 };
    float_z VECTOR_COMPONENTS_E[] = { SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_8 };
    float_z VECTOR_COMPONENTS_F[] = { SFloat::_9, SFloat::_0, SFloat::_0_5, SFloat::_0_25 };
    float_z VECTOR_COMPONENTS_G[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7 };
    float_z VECTOR_COMPONENTS_H[] = { SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_8 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T VALUE_FOR_C(VECTOR_COMPONENTS_C);
    const T VALUE_FOR_D(VECTOR_COMPONENTS_D);
    const T VALUE_FOR_E(VECTOR_COMPONENTS_E);
    const T VALUE_FOR_F(VECTOR_COMPONENTS_F);
    const T VALUE_FOR_G(VECTOR_COMPONENTS_G);
    const T VALUE_FOR_H(VECTOR_COMPONENTS_H);

    const Hexahedron<T> HEXAHEDRON = Hexahedron<T>(VALUE_FOR_A, VALUE_FOR_B, VALUE_FOR_C, VALUE_FOR_D,
                                                     VALUE_FOR_E, VALUE_FOR_F, VALUE_FOR_G, VALUE_FOR_H);

    const string_z A_STRING = VALUE_FOR_A.ToString();
    const string_z B_STRING = VALUE_FOR_B.ToString();
    const string_z C_STRING = VALUE_FOR_C.ToString();
    const string_z D_STRING = VALUE_FOR_D.ToString();
    const string_z E_STRING = VALUE_FOR_E.ToString();
    const string_z F_STRING = VALUE_FOR_F.ToString();
    const string_z G_STRING = VALUE_FOR_G.ToString();
    const string_z H_STRING = VALUE_FOR_H.ToString();

    const string_z EXPECTED_STRING = string_z("HX(a(") + A_STRING + Z_L("),b(") + B_STRING + Z_L("),c(") + C_STRING + Z_L("),d(") + D_STRING + Z_L("),") +
                                         Z_L(   "e(") + E_STRING + Z_L("),f(") + F_STRING + Z_L("),g(") + G_STRING + Z_L("),h(") + H_STRING + Z_L("))");

	// [Execution]
    string_z strReturnedString = HEXAHEDRON.ToString();

    // [Verification]
    BOOST_CHECK(strReturnedString == EXPECTED_STRING);
}

// End - Test Suite: Hexahedron
ZTEST_SUITE_END()
