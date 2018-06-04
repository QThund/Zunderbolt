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

#include "ZMath/Triangle2D.h"

#include "ZCommon/Assertions.h"
#include "ZMath/TransformationMatrix3x3.h"
#include "ZMath/SPoint.h"



namespace z
{
namespace Internals
{
    
//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |       CONSTRUCTORS         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

Triangle2D::Triangle2D()
{
}

Triangle2D::Triangle2D(const Triangle2D &triangle) : Triangle<Vector2>(triangle)
{
}

Triangle2D::Triangle2D(const Triangle<Vector2> &triangle) : Triangle<Vector2>(triangle)
{
}

Triangle2D::Triangle2D(const Vector2 &vA, const Vector2 &vB, const Vector2 &vC) : Triangle<Vector2>(vA, vB, vC)
{
}

Triangle2D::Triangle2D(const float_z* arValuesA, const float_z* arValuesB, const float_z* arValuesC) :
                        Triangle<Vector2>(arValuesA, arValuesB, arValuesC)
{
}

Triangle2D::Triangle2D(const vf32_z valueA, const vf32_z valueB, const vf32_z valueC) : Triangle<Vector2>(valueA, valueB, valueC)
{
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

Triangle2D& Triangle2D::operator=(const Triangle<Vector2> &triangle)
{
    Triangle<Vector2>::operator=(triangle);
    return *this;
}

Triangle2D Triangle2D::Transform(const z::TransformationMatrix3x3 &transformation) const
{
    Triangle2D auxTriangle = *this;
    SPoint::Transform(transformation, rcast_z(&auxTriangle, Vector2*), 3);
    return auxTriangle;
}

Triangle2D Triangle2D::TransformWithPivot(const z::TransformationMatrix3x3 &transformation, const Vector2 &vPivot) const
{
    Triangle2D auxTriangle = *this;
    SPoint::TransformWithPivot(transformation, vPivot, rcast_z(&auxTriangle, Vector2*), 3);
    return auxTriangle;
}

Vector2 Triangle2D::GetCircumcenter() const
{
    // All the vertices shouldn't coincide
    Z_ASSERT_WARNING( !(this->A == this->B && this->B == this->C), "All the vertices shouldn't coincide" );

    //STEP 1: Obtain the gradient of height A.
    //
    // We can obtain the gradient of a line using this formula:
    // m = (y - y1) / (x - x1), where (x1, y1) is a point contained into the line
    const float_z gradientBC = (C.y - B.y) / (C.x - B.x);
    const float_z gradientHA = - SFloat::_1 / gradientBC;

    //STEP 1.1: Obtain middle point of side BC
    const Vector2 middlePointBC = (C + B) * SFloat::_0_5;

    //STEP 2: Obtain the gradient of height B.
    const float_z gradientAC = (C.y - A.y) / (C.x - A.x);
    const float_z gradientHB = - SFloat::_1 / gradientAC;

    //STEP 2.1: Obtain middle point of side AC
    const Vector2 middlePointAC = (C + A) * SFloat::_0_5;

    //STEP 3: Calculate the intersection of the perpendicular bisectors
    //
    // The gradient equations of the perpendicular bisectors are like this:
    // hA (identical) y - middlePointBC.y = m * (x - middlePointBC.x) -> y = m * x - m * middlePointBC.x + middlePointBC.y
    // hB (identical) y - middlePointAC.y = n * (x - middlePointAC.x) -> y = n * x - n * middlePointAC.x + middlePointAC.y
    //
    // The intersection point is that point where both formulas are equal.

    // Here we got x:
    // m * x - m * middlePointBC.x + middlePointBC.y = n * x - n * middlePointAC.x + middlePointAC.y
    // m * x - n * x = m * middlePointBC.x - middlePointBC.y - n * middlePointAC.x + middlePointAC.y
    // x = (m * middlePointBC.x - middlePointBC.y - n * middlePointAC.x + middlePointAC.y) / (m - n)
    Vector2 vCircumcenter;
    vCircumcenter.x = (gradientHA * middlePointBC.x - middlePointBC.y - gradientHB * middlePointAC.x + middlePointAC.y) / (gradientHA - gradientHB);

    // With x calculated we can now obtain y appliying the x to one of the equations explained before.
    vCircumcenter.y = gradientHA * vCircumcenter.x - gradientHA * middlePointBC.x + middlePointBC.y;

    return vCircumcenter;
}

Vector2 Triangle2D::GetOrthocenter() const
{
    // All the vertices shouldn't coincide
    Z_ASSERT_WARNING( !(this->A == this->B && this->B == this->C), "All the vertices shouldn't coincide" );

    //STEP 1: Obtain the gradient of height A.
    //
    // We can obtain the gradient of a line using this formula:
    // m = (y - y1) / (x - x1), where (x1, y1) is a point contained into the line
    float_z gradientBC = (C.y - B.y) / (C.x - B.x);
    float_z gradientHA = - SFloat::_1 / gradientBC;

    //STEP 2: Obtain the gradient of height B.
    float_z gradientAC = (C.y - A.y) / (C.x - A.x);
    float_z gradientHB = - SFloat::_1 / gradientAC;

    //STEP 3: Calculate the intersection of the heights
    //
    // The gradient equations of the heights are like this:
    // hA (identical) y - A.y = m * (x - A.x) -> y = m * x - m * A.x + A.y
    // hB (identical) y - B.y = n * (x - B.x) -> y = n * x - n * B.x + B.y
    //
    // The intersection point is that point where both formulas are equal.

    // Here we got x:
    // m * x - m * A.x + A.y = n * x - n * B.x + B.y
    // m * x - n * x = m * A.x - A.y - n * B.x + B.y
    // x = (m * A.x - A.y - n * B.x + B.y) / (m - n)
    Vector2 vOrthocenter;
    vOrthocenter.x = (gradientHA * A.x - A.y - gradientHB * B.x + B.y) / (gradientHA - gradientHB);

    // With x calculated we can now obtain y appliying the x to one of the equations explained before.
    vOrthocenter.y = gradientHA * vOrthocenter.x - gradientHA * A.x + A.y;

    return vOrthocenter;
}

Triangle2D Triangle2D::Translate(const Vector2 &vTranslation) const
{
    Triangle2D auxTriangle = *this;
    SPoint::Translate(vTranslation, rcast_z(&auxTriangle, Vector2*), 3);
    return auxTriangle;
}

Triangle2D Triangle2D::Translate(const float_z fTranslationX, const float_z fTranslationY) const
{
    Triangle2D auxTriangle = *this;
    SPoint::Translate(fTranslationX, fTranslationY, rcast_z(&auxTriangle, Vector2*), 3);
    return auxTriangle;
}

Triangle2D Triangle2D::Rotate(const float_z fRotationAngle) const
{
    Triangle2D auxTriangle = *this;
    SPoint::Rotate(fRotationAngle, rcast_z(&auxTriangle, Vector2*), 3);
    return auxTriangle;
}

Triangle2D Triangle2D::RotateWithPivot(const float_z fRotationAngle, const Vector2 &vPivot) const
{
    Triangle2D auxTriangle = *this;
    SPoint::RotateWithPivot(fRotationAngle, vPivot, rcast_z(&auxTriangle, Vector2*), 3);
    return auxTriangle;
}

Triangle2D Triangle2D::Scale(const Vector2 &vScale) const
{
    Triangle2D auxTriangle = *this;
    SPoint::Scale(vScale, rcast_z(&auxTriangle, Vector2*), 3);
    return auxTriangle;
}

Triangle2D Triangle2D::Scale(const float_z fScaleX, const float_z fScaleY) const
{
    Triangle2D auxTriangle = *this;
    SPoint::Scale(fScaleX, fScaleY, rcast_z(&auxTriangle, Vector2*), 3);
    return auxTriangle;
}

Triangle2D Triangle2D::ScaleWithPivot(const Vector2 &vScale, const Vector2 &vPivot) const
{
    Triangle2D auxTriangle = *this;
    SPoint::ScaleWithPivot(vScale, vPivot, rcast_z(&auxTriangle, Vector2*), 3);
    return auxTriangle;
}

Triangle2D Triangle2D::ScaleWithPivot(const float_z fScaleX, const float_z fScaleY, const Vector2 &vPivot) const
{
    Triangle2D auxTriangle = *this;
    SPoint::ScaleWithPivot(fScaleX, fScaleY, vPivot, rcast_z(&auxTriangle, Vector2*), 3);
    return auxTriangle;
}


} // namespace Internals
} // namespace z