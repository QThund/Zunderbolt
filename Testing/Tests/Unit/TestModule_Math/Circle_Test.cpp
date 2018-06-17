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

#include "ZMath/Circle.h"

#include "ZMath/TransformationMatrix3x3.h"
#include "ZMath/SVectorArray.h"
#include "ZMath/SAngle.h"
#include "ZCommon/Exceptions/AssertException.h"

ZTEST_SUITE_BEGIN( Circle_TestSuite )


/// <summary>
/// Checks if copy constructor sets circle components properly.
/// </summary>
ZTEST_CASE ( Constructor2_ValuesAreCopiedProperly_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_VALUE_FOR_CENTER = Vector2(SFloat::_5, SFloat::_6);
    const float_z EXPECTED_VALUE_FOR_RADIUS = SFloat::_4;

    const Circle CIRCLE_TO_COPY = Circle(EXPECTED_VALUE_FOR_CENTER,
                                         EXPECTED_VALUE_FOR_RADIUS);

	// [Execution]
    Circle circleUT(CIRCLE_TO_COPY);
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(circleUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks if base type constructor sets circle components properly.
/// </summary>
ZTEST_CASE ( Constructor3_ValuesAreCopiedProperly_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_VALUE_FOR_CENTER = Vector2(SFloat::_8, SFloat::_9);
    const float_z EXPECTED_VALUE_FOR_RADIUS = SFloat::_3;

    const Internals::Orb<Vector2> ORB_TO_COPY = Internals::Orb<Vector2>(EXPECTED_VALUE_FOR_CENTER,
                                                                        EXPECTED_VALUE_FOR_RADIUS);

	// [Execution]
    Circle circleUT(ORB_TO_COPY);
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(circleUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks that every value is set to correct component.
/// </summary>
ZTEST_CASE ( Constructor4_ValuesAreCorrectlySet_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_VALUE_FOR_CENTER = Vector2(SFloat::_1, SFloat::_5);
    const float_z EXPECTED_VALUE_FOR_RADIUS = SFloat::_4;

	// [Execution]
    Circle circleUT = Circle(EXPECTED_VALUE_FOR_CENTER, EXPECTED_VALUE_FOR_RADIUS);
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(circleUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks that the returned unit circle has not changed since the last time the test was executed.
/// </summary>
ZTEST_CASE ( GetUnitCircle_ValueHasNotChanged_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_VALUE_FOR_CENTER = Vector2(SFloat::_0, SFloat::_0);
    const float_z EXPECTED_VALUE_FOR_RADIUS = SFloat::_1;

	// [Execution]
    Circle circleUT = Circle::GetUnitCircle();
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(circleUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks that a circle is correctly assigned to another circle.
/// </summary>
ZTEST_CASE ( OperatorAssignation_CircleIsAssignedProperlyToAnother_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_VALUE_FOR_CENTER = Vector2(SFloat::_2, SFloat::_3);
    const float_z EXPECTED_VALUE_FOR_RADIUS = SFloat::_8;
    const Circle CIRCLE_TO_COPY = Circle(EXPECTED_VALUE_FOR_CENTER,
                                         EXPECTED_VALUE_FOR_RADIUS);

	// [Execution]
    Circle circleUT;
    circleUT = CIRCLE_TO_COPY;
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(circleUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks that a circle is correctly translated.
/// </summary>
ZTEST_CASE ( Translate1_CircleIsCorrectlyTranslated_Test )
{
    // [Preparation]
    const Vector2 INIT_CENTER_POS = Vector2(SFloat::_2, SFloat::_4);
    const Vector2 TRANSLATION_VECTOR = Vector2(SFloat::_3, SFloat::_7);
    const float_z EXPECTED_VALUE_FOR_RADIUS = SFloat::_1;

    Vector2 vExpectedValueForCenter = Vector2(INIT_CENTER_POS);
    SVectorArray::Translate(TRANSLATION_VECTOR, &vExpectedValueForCenter,1);

	// [Execution]
    Circle circleUT= Circle(INIT_CENTER_POS, EXPECTED_VALUE_FOR_RADIUS);
    circleUT = circleUT.Translate(TRANSLATION_VECTOR);
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == vExpectedValueForCenter);
    BOOST_CHECK(circleUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks that a circle is not translated if traslation is zero.
/// </summary>
ZTEST_CASE ( Translate1_CircleIsNotTranslatedWhenTranslationIsZero_Test )
{
    // [Preparation]
    const Vector2 INIT_CENTER_POS = Vector2(SFloat::_2, SFloat::_4);
    const Vector2 TRANSLATION_VECTOR = Vector2(SFloat::_0, SFloat::_0);
    const float_z EXPECTED_VALUE_FOR_RADIUS = SFloat::_1;
    const Vector2 EXPECTED_VALUE_FOR_CENTER = Vector2(INIT_CENTER_POS);

	// [Execution]
    Circle circleUT= Circle(INIT_CENTER_POS, EXPECTED_VALUE_FOR_RADIUS);
    circleUT = circleUT.Translate(TRANSLATION_VECTOR);
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(circleUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks that a circle is correctly translated.
/// </summary>
ZTEST_CASE ( Translate2_CircleIsCorrectlyTranslated_Test )
{
    // [Preparation]
    const Vector2 INIT_CENTER_POS = Vector2(SFloat::_2, SFloat::_4);
    const Vector2 TRANSLATION_VECTOR = Vector2(SFloat::_3, SFloat::_7);
    const float_z EXPECTED_VALUE_FOR_RADIUS = SFloat::_1;

    Vector2 vExpectedValueForCenter = Vector2(INIT_CENTER_POS);
    SVectorArray::Translate(TRANSLATION_VECTOR, &vExpectedValueForCenter,1);

	// [Execution]
    Circle circleUT= Circle(INIT_CENTER_POS, EXPECTED_VALUE_FOR_RADIUS);
    circleUT = circleUT.Translate(TRANSLATION_VECTOR.x, TRANSLATION_VECTOR.y);
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == vExpectedValueForCenter);
    BOOST_CHECK(circleUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks that a circle is not translated if components of traslation are zero.
/// </summary>
ZTEST_CASE ( Translate2_CircleIsNotTranslatedWhenTranslationIsZero_Test )
{
    // [Preparation]
    const Vector2 INIT_CENTER_POS = Vector2(SFloat::_2, SFloat::_4);
    const Vector2 TRANSLATION_VECTOR = Vector2(SFloat::_0, SFloat::_0);
    const float_z EXPECTED_VALUE_FOR_RADIUS = SFloat::_1;
    const Vector2 EXPECTED_VALUE_FOR_CENTER = Vector2(INIT_CENTER_POS);

	// [Execution]
    Circle circleUT= Circle(INIT_CENTER_POS, EXPECTED_VALUE_FOR_RADIUS);
    circleUT = circleUT.Translate(TRANSLATION_VECTOR.x, TRANSLATION_VECTOR.y);
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(circleUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks that a circle is correctly rotated.
/// </summary>
ZTEST_CASE ( Rotate_CircleIsCorrectlyRotated_Test )
{
    // [Preparation]
    const Vector2 INIT_CENTER_POS = Vector2(SFloat::_2, SFloat::_4);

    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z ANGLE = SAngle::_90;
    #else
        const float_z ANGLE = SAngle::_Pi;
    #endif
    
    const float_z EXPECTED_VALUE_FOR_RADIUS = SFloat::_1;

    Vector2 vExpectedValueForCenter = Vector2(INIT_CENTER_POS);
    SVectorArray::Rotate(ANGLE, &vExpectedValueForCenter, 1);

	// [Execution]
    Circle circleUT= Circle(INIT_CENTER_POS, EXPECTED_VALUE_FOR_RADIUS);
    circleUT = circleUT.Rotate(ANGLE);
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == vExpectedValueForCenter);
    BOOST_CHECK(circleUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks that a circle is not rotated if angle is zero.
/// </summary>
ZTEST_CASE ( Rotate_CircleIsNotRotatedWhenAngleIsZero_Test )
{
    // [Preparation]
    const Vector2 INIT_CENTER_POS = Vector2(SFloat::_2, SFloat::_4);
    const float_z ANGLE = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_RADIUS = SFloat::_1;
    const Vector2 EXPECTED_VALUE_FOR_CENTER = INIT_CENTER_POS;

	// [Execution]
    Circle circleUT= Circle(INIT_CENTER_POS, EXPECTED_VALUE_FOR_RADIUS);
    circleUT = circleUT.Rotate(ANGLE);
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(circleUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks that a circle is correctly rotated with a pivot point.
/// </summary>
ZTEST_CASE ( RotateWithPivot_CircleIsCorrectlyRotated_Test )
{
    // [Preparation]
    const Vector2 INIT_CENTER_POS = Vector2(SFloat::_2, SFloat::_4);
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z ANGLE = SAngle::_90;
    #else
        const float_z ANGLE = SAngle::_Pi;
    #endif
    const float_z EXPECTED_VALUE_FOR_RADIUS = SFloat::_1;
    const Vector2 PIVOT_POINT = Vector2(SFloat::_6, SFloat::_7);

    Vector2 vExpectedValueForCenter = Vector2(INIT_CENTER_POS);
    SVectorArray::RotateWithPivot(ANGLE, PIVOT_POINT, &vExpectedValueForCenter, 1);

	// [Execution]
    Circle circleUT= Circle(INIT_CENTER_POS, EXPECTED_VALUE_FOR_RADIUS);
    circleUT = circleUT.RotateWithPivot(ANGLE, PIVOT_POINT);
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == vExpectedValueForCenter);
    BOOST_CHECK(circleUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks that a circle not rotated if angle is zero.
/// </summary>
ZTEST_CASE ( RotateWithPivot_CircleIsNotRotatedWhenAngleIsZero_Test )
{
    // [Preparation]
    const Vector2 INIT_CENTER_POS = Vector2(SFloat::_2, SFloat::_4);
    const float_z ANGLE = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_RADIUS = SFloat::_1;
    const Vector2 PIVOT_POINT = Vector2(SFloat::_1, SFloat::_9);
    const Vector2 EXPECTED_VALUE_FOR_CENTER = INIT_CENTER_POS;

	// [Execution]
    Circle circleUT= Circle(INIT_CENTER_POS, EXPECTED_VALUE_FOR_RADIUS);
    circleUT = circleUT.RotateWithPivot(ANGLE, PIVOT_POINT);
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(circleUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks that a circle is correctly rotated with a pivot point in its center.
/// </summary>
ZTEST_CASE ( RotateWithPivot_CircleIsCorrectlyRotatedWithPivotInCenter_Test )
{
    // [Preparation]
    const Vector2 INIT_CENTER_POS = Vector2(SFloat::_2, SFloat::_4);
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z ANGLE = SAngle::_90;
    #else
        const float_z ANGLE = SAngle::_Pi;
    #endif
    const float_z EXPECTED_VALUE_FOR_RADIUS = SFloat::_1;
    const Vector2 PIVOT_POINT = INIT_CENTER_POS;

    Vector2 vExpectedValueForCenter = Vector2(INIT_CENTER_POS);
    SVectorArray::RotateWithPivot(ANGLE, PIVOT_POINT, &vExpectedValueForCenter, 1);

	// [Execution]
    Circle circleUT= Circle(INIT_CENTER_POS, EXPECTED_VALUE_FOR_RADIUS);
    circleUT = circleUT.RotateWithPivot(ANGLE, PIVOT_POINT);
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == vExpectedValueForCenter);
    BOOST_CHECK(circleUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks that a circle is correctly scaled.
/// </summary>
ZTEST_CASE ( Scale1_CircleIsCorrectlyScaled_Test )
{
    // [Preparation]
    const Vector2 INIT_CENTER_POS = Vector2(SFloat::_2, SFloat::_4);
    const float_z INIT_RADIUS = SFloat::_2;
    const Vector2 SCALE_VECTOR = Vector2(SFloat::_2, SFloat::_2);
    const float_z SCALE_RADIUS = SFloat::_3;

    float_z fExpectedValueForRadius = INIT_RADIUS;
    Vector2 vExpectedValueForCenter = Vector2(INIT_CENTER_POS);

    fExpectedValueForRadius *= SCALE_RADIUS; 
    SVectorArray::Scale(SCALE_VECTOR, &vExpectedValueForCenter, 1);

	// [Execution]
    Circle circleUT= Circle(INIT_CENTER_POS, INIT_RADIUS);
    circleUT = circleUT.Scale(SCALE_VECTOR, SCALE_RADIUS);
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == vExpectedValueForCenter);
    BOOST_CHECK(circleUT.Radius == fExpectedValueForRadius);
}

/// <summary>
/// Checks that a circle is not scaled if scalation is one.
/// </summary>
ZTEST_CASE ( Scale1_CircleIsNotScaledWhenScalationIsOne_Test )
{
    // [Preparation]
    const Vector2 INIT_CENTER_POS = Vector2(SFloat::_2, SFloat::_4);
    const float_z INIT_RADIUS = SFloat::_2;
    const Vector2 SCALE_VECTOR = Vector2(SFloat::_1, SFloat::_1);
    const float_z SCALE_RADIUS = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_RADIUS = INIT_RADIUS;
    const Vector2 EXPECTED_VALUE_FOR_CENTER = INIT_CENTER_POS;

	// [Execution]
    Circle circleUT= Circle(INIT_CENTER_POS, INIT_RADIUS);
    circleUT = circleUT.Scale(SCALE_VECTOR, SCALE_RADIUS);
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(circleUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks that a the circle is correctly scaled by zero.
/// </summary>
ZTEST_CASE ( Scale1_CircleRadiusEqualsZeroWhenIsScaledByZero_Test )
{
    // [Preparation]
    const Vector2 INIT_CENTER_POS = Vector2(SFloat::_2, SFloat::_4);
    const float_z INIT_RADIUS = SFloat::_2;
    const Vector2 SCALE_VECTOR = Vector2(SFloat::_0, SFloat::_0);
    const float_z SCALE_RADIUS = SFloat::_0;
    const Vector2 EXPECTED_VALUE_FOR_CENTER = Vector2(SFloat::_0, SFloat::_0);
    const float_z EXPECTED_VALUE_FOR_RADIUS = SFloat::_0;

	// [Execution]
    Circle circleUT= Circle(INIT_CENTER_POS, INIT_RADIUS);
    circleUT = circleUT.Scale(SCALE_VECTOR, SCALE_RADIUS);
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(circleUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks that a the circle with zero radius is correctly scaled.
/// </summary>
ZTEST_CASE ( Scale1_CircleWidthZeroRadiusIsCorrectlyScaled_Test )
{
    // [Preparation]
    const Vector2 INIT_CENTER_POS = Vector2(SFloat::_2, SFloat::_4);
    const float_z INIT_RADIUS = SFloat::_0;
    const Vector2 SCALE_VECTOR = Vector2(SFloat::_4, SFloat::_4);
    const float_z SCALE_RADIUS = SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_RADIUS = INIT_RADIUS;

    Vector2 vExpectedValueForCenter = Vector2(INIT_CENTER_POS);
    SVectorArray::Scale(SCALE_VECTOR, &vExpectedValueForCenter, 1);

	// [Execution]
    Circle circleUT= Circle(INIT_CENTER_POS, INIT_RADIUS);
    circleUT = circleUT.Scale(SCALE_VECTOR, SCALE_RADIUS);
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == vExpectedValueForCenter);
    BOOST_CHECK(circleUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks that a circle is correctly scaled.
/// </summary>
ZTEST_CASE ( Scale2_CircleIsCorrectlyScaled_Test )
{
    // [Preparation]
    const Vector2 INIT_CENTER_POS = Vector2(SFloat::_2, SFloat::_4);
    const float_z INIT_RADIUS = SFloat::_2;
    const Vector2 SCALE_VECTOR = Vector2(SFloat::_2, SFloat::_2);
    const float_z SCALE_RADIUS = SFloat::_3;

    float_z fExpectedValueForRadius = INIT_RADIUS;
    Vector2 vExpectedValueForCenter = Vector2(INIT_CENTER_POS);

    fExpectedValueForRadius *= SCALE_RADIUS; 
    SVectorArray::Scale(SCALE_VECTOR.x, SCALE_VECTOR.y, &vExpectedValueForCenter, 1);

	// [Execution]
    Circle circleUT= Circle(INIT_CENTER_POS, INIT_RADIUS);
    circleUT = circleUT.Scale(SCALE_VECTOR.x, SCALE_VECTOR.y, SCALE_RADIUS);
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == vExpectedValueForCenter);
    BOOST_CHECK(circleUT.Radius == fExpectedValueForRadius);
}

/// <summary>
/// Checks that a circle is not scaled if scalation is one.
/// </summary>
ZTEST_CASE ( Scale2_CircleIsNotScaledWhenScalationIsOne_Test )
{
    // [Preparation]
    const Vector2 INIT_CENTER_POS = Vector2(SFloat::_2, SFloat::_4);
    const float_z INIT_RADIUS = SFloat::_2;
    const Vector2 SCALE_VECTOR = Vector2(SFloat::_1, SFloat::_1);
    const float_z SCALE_RADIUS = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_RADIUS = INIT_RADIUS;
    const Vector2 EXPECTED_VALUE_FOR_CENTER = INIT_CENTER_POS;

	// [Execution]
    Circle circleUT= Circle(INIT_CENTER_POS, INIT_RADIUS);
    circleUT = circleUT.Scale(SCALE_VECTOR.x, SCALE_VECTOR.y, SCALE_RADIUS);
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(circleUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks that a the circle is correctly scaled by zero.
/// </summary>
ZTEST_CASE ( Scale2_CircleRadiusEqualsZeroWhenIsScaledByZero_Test )
{
    // [Preparation]
    const Vector2 INIT_CENTER_POS = Vector2(SFloat::_2, SFloat::_4);
    const float_z INIT_RADIUS = SFloat::_2;
    const Vector2 SCALE_VECTOR = Vector2(SFloat::_0, SFloat::_0);
    const float_z SCALE_RADIUS = SFloat::_0;
    const Vector2 EXPECTED_VALUE_FOR_CENTER = Vector2(SFloat::_0, SFloat::_0);
    const float_z EXPECTED_VALUE_FOR_RADIUS = SFloat::_0;

	// [Execution]
    Circle circleUT= Circle(INIT_CENTER_POS, INIT_RADIUS);
    circleUT = circleUT.Scale(SCALE_VECTOR.x, SCALE_VECTOR.y, SCALE_RADIUS);
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(circleUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks that a the circle with zero radius is correctly scaled.
/// </summary>
ZTEST_CASE ( Scale2_CircleWidthRadiusEqualsToZeroIsCorrectlyScaled_Test )
{
    // [Preparation]
    const Vector2 INIT_CENTER_POS = Vector2(SFloat::_2, SFloat::_4);
    const float_z INIT_RADIUS = SFloat::_0;
    const Vector2 SCALE_VECTOR = Vector2(SFloat::_4, SFloat::_4);
    const float_z SCALE_RADIUS = SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_RADIUS = INIT_RADIUS;

    Vector2 vExpectedValueForCenter = Vector2(INIT_CENTER_POS);
    SVectorArray::Scale(SCALE_VECTOR, &vExpectedValueForCenter, 1);

	// [Execution]
    Circle circleUT= Circle(INIT_CENTER_POS, INIT_RADIUS);
    circleUT = circleUT.Scale(SCALE_VECTOR.x, SCALE_VECTOR.y, SCALE_RADIUS);
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == vExpectedValueForCenter);
    BOOST_CHECK(circleUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks that a circle is correctly scaled with a pivot point.
/// </summary>
ZTEST_CASE ( ScaleWithPivot1_CircleIsCorrectlyScaled_Test )
{
    // [Preparation]
    const Vector2 INIT_CENTER_POS = Vector2(SFloat::_2, SFloat::_4);
    const float_z INIT_RADIUS = SFloat::_2;
    const Vector2 SCALE_VECTOR = Vector2(SFloat::_2, SFloat::_2);
    const float_z SCALE_RADIUS = SFloat::_3;
    const Vector2 PIVOT_POINT = Vector2(SFloat::_6, SFloat::_7);

    float_z fExpectedValueForRadius = INIT_RADIUS;
    Vector2 vExpectedValueForCenter = Vector2(INIT_CENTER_POS);

    fExpectedValueForRadius *= SCALE_RADIUS; 
    SVectorArray::ScaleWithPivot(SCALE_VECTOR, PIVOT_POINT, &vExpectedValueForCenter, 1);

	// [Execution]
    Circle circleUT= Circle(INIT_CENTER_POS, INIT_RADIUS);
    circleUT = circleUT.ScaleWithPivot(SCALE_VECTOR, SCALE_RADIUS, PIVOT_POINT);
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == vExpectedValueForCenter);
    BOOST_CHECK(circleUT.Radius == fExpectedValueForRadius);
}

/// <summary>
/// Checks that a circle is not scaled if scalation is one.
/// </summary>
ZTEST_CASE ( ScaleWithPivot1_CircleIsNotScaledWhenScalationIsOne_Test )
{
    // [Preparation]
    const Vector2 INIT_CENTER_POS = Vector2(SFloat::_2, SFloat::_4);
    const float_z INIT_RADIUS = SFloat::_3;
    const Vector2 SCALE_VECTOR = Vector2(SFloat::_1, SFloat::_1);
    const float_z SCALE_RADIUS = SFloat::_1;
    const Vector2 PIVOT_POINT = Vector2(SFloat::_6, SFloat::_7);
    const Vector2 EXPECTED_VALUE_FOR_CENTER = INIT_CENTER_POS;
    const float_z EXPECTED_VALUE_FOR_RADIUS = INIT_RADIUS;

	// [Execution]
    Circle circleUT= Circle(INIT_CENTER_POS, INIT_RADIUS);
    circleUT = circleUT.ScaleWithPivot(SCALE_VECTOR, SCALE_RADIUS, PIVOT_POINT);
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(circleUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks that a circle is correctly scaled by zero with a pivot point.
/// </summary>
ZTEST_CASE ( ScaleWithPivot1_CircleRadiusEqualsZeroWhenIsScaledByZero_Test )
{
    // [Preparation]
    const Vector2 INIT_CENTER_POS = Vector2(SFloat::_2, SFloat::_4);
    const float_z INIT_RADIUS = SFloat::_3;
    const Vector2 SCALE_VECTOR = Vector2(SFloat::_0, SFloat::_0);
    const float_z SCALE_RADIUS = SFloat::_0;
    const Vector2 PIVOT_POINT = Vector2(SFloat::_6, SFloat::_7);
    const Vector2 EXPECTED_VALUE_FOR_CENTER = PIVOT_POINT;
    const float_z EXPECTED_VALUE_FOR_RADIUS = SFloat::_0;

	// [Execution]
    Circle circleUT= Circle(INIT_CENTER_POS, INIT_RADIUS);
    circleUT = circleUT.ScaleWithPivot(SCALE_VECTOR, SCALE_RADIUS, PIVOT_POINT);
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(circleUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks that a circle is correctly scaled with a pivot point.
/// </summary>
ZTEST_CASE ( ScaleWithPivot2_CircleIsCorrectlyScaled_Test )
{
    // [Preparation]
    const Vector2 INIT_CENTER_POS = Vector2(SFloat::_2, SFloat::_4);
    const float_z INIT_RADIUS = SFloat::_2;
    const Vector2 SCALE_VECTOR = Vector2(SFloat::_2, SFloat::_2);
    const float_z SCALE_RADIUS = SFloat::_3;
    const Vector2 PIVOT_POINT = Vector2(SFloat::_6, SFloat::_7);

    float_z fExpectedValueForRadius = INIT_RADIUS;
    Vector2 vExpectedValueForCenter = Vector2(INIT_CENTER_POS);

    fExpectedValueForRadius *= SCALE_RADIUS; 
    SVectorArray::ScaleWithPivot(SCALE_VECTOR, PIVOT_POINT, &vExpectedValueForCenter, 1);

	// [Execution]
    Circle circleUT= Circle(INIT_CENTER_POS, INIT_RADIUS);
    circleUT = circleUT.ScaleWithPivot(SCALE_VECTOR.x, SCALE_VECTOR.y, SCALE_RADIUS, PIVOT_POINT);
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == vExpectedValueForCenter);
    BOOST_CHECK(circleUT.Radius == fExpectedValueForRadius);
}

/// <summary>
/// Checks that a circle is not scaled if scalation is one.
/// </summary>
ZTEST_CASE ( ScaleWithPivot2_CircleIsNotScaledWhenScalationIsOne_Test )
{
    // [Preparation]
    const Vector2 INIT_CENTER_POS = Vector2(SFloat::_2, SFloat::_4);
    const float_z INIT_RADIUS = SFloat::_3;
    const Vector2 SCALE_VECTOR = Vector2(SFloat::_1, SFloat::_1);
    const float_z SCALE_RADIUS = SFloat::_1;
    const Vector2 PIVOT_POINT = Vector2(SFloat::_6, SFloat::_7);
    const Vector2 EXPECTED_VALUE_FOR_CENTER = INIT_CENTER_POS;
    const float_z EXPECTED_VALUE_FOR_RADIUS = INIT_RADIUS;

	// [Execution]
    Circle circleUT= Circle(INIT_CENTER_POS, INIT_RADIUS);
    circleUT = circleUT.ScaleWithPivot(SCALE_VECTOR.x, SCALE_VECTOR.y, SCALE_RADIUS, PIVOT_POINT);
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(circleUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks that a circle is correctly scaled by zero with a pivot point.
/// </summary>
ZTEST_CASE ( ScaleWithPivot2_CircleRadiusEqualsZeroWhenIsScaledByZero_Test )
{
    // [Preparation]
    const Vector2 INIT_CENTER_POS = Vector2(SFloat::_2, SFloat::_4);
    const float_z INIT_RADIUS = SFloat::_3;
    const Vector2 SCALE_VECTOR = Vector2(SFloat::_0, SFloat::_0);
    const float_z SCALE_RADIUS = SFloat::_0;
    const Vector2 PIVOT_POINT = Vector2(SFloat::_6, SFloat::_7);
    const Vector2 EXPECTED_VALUE_FOR_CENTER = PIVOT_POINT;
    const float_z EXPECTED_VALUE_FOR_RADIUS = SFloat::_0;

	// [Execution]
    Circle circleUT= Circle(INIT_CENTER_POS, INIT_RADIUS);
    circleUT = circleUT.ScaleWithPivot(SCALE_VECTOR.x, SCALE_VECTOR.y, SCALE_RADIUS, PIVOT_POINT);
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(circleUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks that a circle is correctly transformed.
/// </summary>
ZTEST_CASE ( Transform_CircleIsCorrectlyTransformed_Test )
{
    // [Preparation]
    const Vector2 INIT_CENTER_POS = Vector2(SFloat::_2, SFloat::_4);
    const float_z INIT_RADIUS = SFloat::_1;
    const float_z SCALE_RADIUS = SFloat::_3;
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z ANGLE = SAngle::_90;
    #else
        const float_z ANGLE = SAngle::_Pi;
    #endif

    const TransformationMatrix3x3 TRANSFORMATION_MATRIX =
            TransformationMatrix3x3(Vector2(SFloat::_2, SFloat::_3),
            ANGLE,
            Vector2(SFloat::_4, SFloat::_6));

    float_z fExpectedValueForRadius = INIT_RADIUS;
    Vector2 vExpectedValueForCenter = Vector2(INIT_CENTER_POS);

    fExpectedValueForRadius *= SCALE_RADIUS; 
    SVectorArray::Transform(TRANSFORMATION_MATRIX, &vExpectedValueForCenter,1);

	// [Execution]
    Circle circleUT= Circle(INIT_CENTER_POS, INIT_RADIUS);
    circleUT = circleUT.Transform(TRANSFORMATION_MATRIX, SCALE_RADIUS);
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == vExpectedValueForCenter);
    BOOST_CHECK(circleUT.Radius == fExpectedValueForRadius);
}

/// <summary>
/// Checks that a circle is not transformed when matrix is identity.
/// </summary>
ZTEST_CASE ( Transform_CircleIsNotTransformedWhenTransformationIsIdentity_Test )
{
    // [Preparation]
    const Vector2 INIT_CENTER_POS = Vector2(SFloat::_2, SFloat::_4);
    const float_z INIT_RADIUS = SFloat::_1;
    const float_z SCALE_RADIUS = SFloat::_1;
    const TransformationMatrix3x3 TRANSFORMATION_MATRIX = TransformationMatrix3x3::GetIdentity();
    const float_z EXPECTED_VALUE_FOR_RADIUS = INIT_RADIUS;
    const Vector2 EXPECTED_VALUE_FOR_CENTER = INIT_CENTER_POS;

	// [Execution]
    Circle circleUT= Circle(INIT_CENTER_POS, INIT_RADIUS);
    circleUT = circleUT.Transform(TRANSFORMATION_MATRIX, SCALE_RADIUS);
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(circleUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks that a circle is correctly transformed with a pivot point.
/// </summary>
ZTEST_CASE ( TransformWithPivot_CircleIsCorrectlyTransformed_Test )
{
    // [Preparation]
    const Vector2 INIT_CENTER_POS = Vector2(SFloat::_2, SFloat::_4);
    const float_z INIT_RADIUS = SFloat::_1;
    const float_z SCALE_RADIUS = SFloat::_3;
    const Vector2 PIVOT_POINT = Vector2(SFloat::_6, SFloat::_7);

    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z ANGLE = SAngle::_90;
    #else
        const float_z ANGLE = SAngle::_Pi;
    #endif

    const TransformationMatrix3x3 TRANSFORMATION_MATRIX =
            TransformationMatrix3x3(Vector2(SFloat::_2, SFloat::_3),
            ANGLE,
            Vector2(SFloat::_4, SFloat::_6));

    float_z fExpectedValueForRadius = INIT_RADIUS;
    Vector2 vExpectedValueForCenter = Vector2(INIT_CENTER_POS);

    fExpectedValueForRadius *= SCALE_RADIUS; 
    SVectorArray::TransformWithPivot(TRANSFORMATION_MATRIX, PIVOT_POINT, &vExpectedValueForCenter,1);

	// [Execution]
    Circle circleUT= Circle(INIT_CENTER_POS, INIT_RADIUS);
    circleUT = circleUT.TransformWithPivot(TRANSFORMATION_MATRIX, SCALE_RADIUS, PIVOT_POINT);
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == vExpectedValueForCenter);
    BOOST_CHECK(circleUT.Radius == fExpectedValueForRadius);
}

/// <summary>
/// Checks that a circle is not transformed when matrix is identity.
/// </summary>
ZTEST_CASE ( TransformWithPivot_CircleIsNotTransformedWhenTransformationIsIdentity_Test )
{
    // [Preparation]
    const Vector2 INIT_CENTER_POS = Vector2(SFloat::_2, SFloat::_4);
    const float_z INIT_RADIUS = SFloat::_1;
    const float_z SCALE_RADIUS = SFloat::_1;
    const Vector2 PIVOT_POINT = Vector2(SFloat::_6, SFloat::_7);
    const float_z EXPECTED_VALUE_FOR_RADIUS = INIT_RADIUS;
    const Vector2 EXPECTED_VALUE_FOR_CENTER = INIT_CENTER_POS;

    const TransformationMatrix3x3 TRANSFORMATION_MATRIX = TransformationMatrix3x3::GetIdentity();

	// [Execution]
    Circle circleUT= Circle(INIT_CENTER_POS, INIT_RADIUS);
    circleUT = circleUT.TransformWithPivot(TRANSFORMATION_MATRIX, SCALE_RADIUS, PIVOT_POINT);
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(circleUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks that the returned value is none when the two circles are not intersecting.
/// </summary>
ZTEST_CASE ( IntersectionPoint_ReturnsNoneWhenCirclesNotIntersecting_Test )
{
    // [Preparation]
    const EIntersections EXPECTED_VALUE_FOR_INTERSECTION = EIntersections::E_None;
    const Circle CIRCLE_ONE = Circle(Vector2(SFloat::_0, SFloat::_0), SFloat::_1);
    const Circle CIRCLE_TWO = Circle(Vector2(SFloat::_3, SFloat::_0), SFloat::_1);

	// [Execution]
    Vector2 intersection1 = Vector2();
    Vector2 intersection2 = Vector2();
    EIntersections intersectionUT = CIRCLE_ONE.IntersectionPoint(CIRCLE_TWO, intersection1, intersection2);
    
    // [Verification]
    BOOST_CHECK(intersectionUT == EXPECTED_VALUE_FOR_INTERSECTION);
}

/// <summary>
/// Checks that the returned value is one when circles are intersecting in one point (tangent).
/// </summary>
ZTEST_CASE ( IntersectionPoint_ReturnsOneWhenCirclesAreIntersectingInOnePoint_Test )
{
    // [Preparation]
    const EIntersections EXPECTED_VALUE_FOR_INTERSECTION = EIntersections::E_One;
    const Circle CIRCLE_ONE = Circle(Vector2(SFloat::_0, SFloat::_0), SFloat::_1);
    const Circle CIRCLE_TWO = Circle(Vector2(SFloat::_2, SFloat::_0), SFloat::_1);

	// [Execution]
    Vector2 intersection1 = Vector2();
    Vector2 intersection2 = Vector2();
    EIntersections intersection1UT = CIRCLE_ONE.IntersectionPoint(CIRCLE_TWO, intersection1, intersection2);
    EIntersections intersection2UT = CIRCLE_TWO.IntersectionPoint(CIRCLE_ONE, intersection1, intersection2);
    
    // [Verification]
    BOOST_CHECK(intersection1UT == EXPECTED_VALUE_FOR_INTERSECTION);
    BOOST_CHECK(intersection2UT == EXPECTED_VALUE_FOR_INTERSECTION);
}

/// <summary>
/// Checks that the returned value is two when circles are intersecting in two points.
/// </summary>
ZTEST_CASE ( IntersectionPoint_ReturnsTwoWhenCirclesAreIntersectingInTwoPoints_Test )
{
    // [Preparation]
    const EIntersections EXPECTED_VALUE_FOR_INTERSECTION = EIntersections::E_Two;
    const Circle CIRCLE_ONE = Circle(Vector2(SFloat::_0, SFloat::_0), SFloat::_1);
    const Circle CIRCLE_TWO = Circle(Vector2(SFloat::_1, SFloat::_0), SFloat::_1);

	// [Execution]
    Vector2 intersection1 = Vector2();
    Vector2 intersection2 = Vector2();
    EIntersections intersection1UT = CIRCLE_ONE.IntersectionPoint(CIRCLE_TWO, intersection1, intersection2);
    EIntersections intersection2UT = CIRCLE_TWO.IntersectionPoint(CIRCLE_ONE, intersection1, intersection2);
    
    // [Verification]
    BOOST_CHECK(intersection1UT == EXPECTED_VALUE_FOR_INTERSECTION);
    BOOST_CHECK(intersection2UT == EXPECTED_VALUE_FOR_INTERSECTION);
}

/// <summary>
/// Checks that the returned value is infinite when two circles are the same.
/// </summary>
ZTEST_CASE ( IntersectionPoint_ReturnsInfiniteWhenTwoCirclesAreTheSame_Test )
{
    // [Preparation]
    const EIntersections EXPECTED_VALUE_FOR_INTERSECTION = EIntersections::E_Infinite;
    const Circle CIRCLE_ONE = Circle(Vector2(SFloat::_0, SFloat::_0), SFloat::_1);
    const Circle CIRCLE_TWO = CIRCLE_ONE;

	// [Execution]
    Vector2 intersection1 = Vector2();
    Vector2 intersection2 = Vector2();
    EIntersections intersection1UT = CIRCLE_ONE.IntersectionPoint(CIRCLE_TWO, intersection1, intersection2);
    EIntersections intersection2UT = CIRCLE_TWO.IntersectionPoint(CIRCLE_ONE, intersection1, intersection2);
    
    // [Verification]
    BOOST_CHECK(intersection1UT == EXPECTED_VALUE_FOR_INTERSECTION);
    BOOST_CHECK(intersection2UT == EXPECTED_VALUE_FOR_INTERSECTION);
}

/// <summary>
/// Checks that the returned value is infinite when one circle is contained into the other.
/// </summary>
ZTEST_CASE ( IntersectionPoint_ReturnsInfiniteWhenOneCircleIsContainedIntoTheOther_Test )
{
    // [Preparation]
    const EIntersections EXPECTED_VALUE_FOR_INTERSECTION = EIntersections::E_Infinite;
    const Circle CIRCLE_ONE = Circle(Vector2(SFloat::_0, SFloat::_0), SFloat::_1);
    const Circle CIRCLE_TWO = Circle(Vector2(SFloat::_0, SFloat::_0), SFloat::_2);

	// [Execution]
    Vector2 intersection1 = Vector2();
    Vector2 intersection2 = Vector2();
    EIntersections intersection1UT = CIRCLE_ONE.IntersectionPoint(CIRCLE_TWO, intersection1, intersection2);
    EIntersections intersection2UT = CIRCLE_TWO.IntersectionPoint(CIRCLE_ONE, intersection1, intersection2);
    
    // [Verification]
    BOOST_CHECK(intersection1UT == EXPECTED_VALUE_FOR_INTERSECTION);
    BOOST_CHECK(intersection2UT == EXPECTED_VALUE_FOR_INTERSECTION);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the radius of one of the circles equals zero.
/// </summary>
ZTEST_CASE ( IntersectionPoint_AssertionFailsWhenRadiusEqualsZero_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;

    const Circle CIRCLE_ONE = Circle(Vector2(SFloat::_8, SFloat::_7), SFloat::_0);
    const Circle CIRCLE_TWO = Circle(Vector2(SFloat::_6, SFloat::_5), SFloat::_1);

	// [Execution]
    Vector2 intersection1 = Vector2();
    Vector2 intersection2 = Vector2();

    bool bAssertionFailed1 = false;
    try
    {
        CIRCLE_ONE.IntersectionPoint(CIRCLE_TWO, intersection1, intersection2);
    }
    catch(const AssertException&)
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;
    try
    {
        CIRCLE_TWO.IntersectionPoint(CIRCLE_ONE, intersection1, intersection2);
    }
    catch(const AssertException&)
    {
        bAssertionFailed2 = true;
    }
    
    // [Verification]
    BOOST_CHECK(bAssertionFailed1 == ASSERTION_FAILED);
    BOOST_CHECK(bAssertionFailed2 == ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

// End - Test Suite: Circle
ZTEST_SUITE_END()
