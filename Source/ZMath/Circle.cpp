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

#include "ZMath/Circle.h"

#include "ZMath/SVectorArray.h"
#include "ZMath/MathDefinitions.h"

namespace z
{

    
//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |       CONSTRUCTORS         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

Circle::Circle()
{
}

Circle::Circle(const Circle &circle) : Internals::Orb<Vector2>(circle)
{
}

Circle::Circle(const Internals::Orb<Vector2> &orb) : Internals::Orb<Vector2>(orb)
{
}

Circle::Circle(const Vector2 &vCenter, const float_z fRadius) : Internals::Orb<Vector2>(vCenter, fRadius)
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

Circle& Circle::operator=(const Internals::Orb<Vector2> &orb)
{
    Internals::Orb<Vector2>::operator=(orb);
    return *this;
}

Circle Circle::Translate(const Vector2 &vTranslation) const
{
    Circle auxCircle = *this;
    SVectorArray::Translate(vTranslation, &auxCircle.Center, 1);
    return auxCircle;
}

Circle Circle::Translate(const float_z fTranslationX, const float_z fTranslationY) const
{
    Circle auxCircle = *this;
    SVectorArray::Translate(fTranslationX, fTranslationY, &auxCircle.Center, 1);
    return auxCircle;
}

Circle Circle::Rotate(const float_z fRotationAngle) const
{
    Circle auxCircle = *this;
    SVectorArray::Rotate(fRotationAngle, &auxCircle.Center, 1);
    return auxCircle;
}

Circle Circle::RotateWithPivot(const float_z fRotationAngle, const Vector2 &vPivot) const
{
    Circle auxCircle = *this;
    SVectorArray::RotateWithPivot(fRotationAngle, vPivot, &auxCircle.Center, 1);
    return auxCircle;
}

Circle Circle::Scale(const Vector2 &vScale, const float_z fRadiusScale) const
{
    Circle auxCircle = *this;
    SVectorArray::Scale(vScale, &auxCircle.Center, 1);
    auxCircle.Radius *= fRadiusScale;
    return auxCircle;
}

Circle Circle::Scale(const float_z fScaleX, const float_z fScaleY, const float_z fRadiusScale) const
{
    Circle auxCircle = *this;
    SVectorArray::Scale(fScaleX, fScaleY, &auxCircle.Center, 1);
    auxCircle.Radius *= fRadiusScale;
    return auxCircle;
}

Circle Circle::ScaleWithPivot(const Vector2 &vScale, const float_z fRadiusScale, const Vector2 &vPivot) const
{
    Circle auxCircle = *this;
    SVectorArray::ScaleWithPivot(vScale, vPivot, &auxCircle.Center, 1);
    auxCircle.Radius *= fRadiusScale;
    return auxCircle;
}

Circle Circle::ScaleWithPivot(const float_z fScaleX, const float_z fScaleY, const float_z fRadiusScale, const Vector2 &vPivot) const
{
    Circle auxCircle = *this;
    SVectorArray::ScaleWithPivot(fScaleX, fScaleY, vPivot, &auxCircle.Center, 1);
    auxCircle.Radius *= fRadiusScale;
    return auxCircle;
}

Circle Circle::Transform(const TransformationMatrix3x3 &transformation, const float_z fRadiusScale) const
{
    Circle auxCircle = *this;
    SVectorArray::Transform(transformation, &auxCircle.Center, 1);
    auxCircle.Radius *= fRadiusScale;
    return auxCircle;
}

Circle Circle::TransformWithPivot(const TransformationMatrix3x3 &transformation, const float_z fRadiusScale, const Vector2 &vPivot) const
{
    Circle auxCircle = *this;
    SVectorArray::TransformWithPivot(transformation, vPivot, &auxCircle.Center, 1);
    auxCircle.Radius *= fRadiusScale;
    return auxCircle;
}

EIntersections Circle::IntersectionPoint(const Orb<Vector2> &circle, Vector2 &vIntersection1, Vector2 &vIntersection2) const
{
    // More information: http://mathforum.org/library/drmath/view/51710.html

    Vector2 vFirstI(vIntersection1);
    Vector2 vSecondI(vIntersection2);

    //STEP 1: Obtain V1, a unit vector that points from the first circle's center to second circle's center, and the distance between both centers.
    Vector2 vV1 = circle.Center - this->Center;
    float_z fDistance = vV1.GetLength();

    if (SFloat::IsNotZero(fDistance))
    {
        vV1 = vV1.Normalize();

        //STEP 2: Obtain V2, a normal vector to V1.
        Vector2 vV2(vV1.y, -vV1.x);

        //STEP 3: Obtain the angle between V1 and V3. V3 is a vector that points from first circle's center to one of the intersection points.
        float_z fAngle = acos_z((this->Radius * this->Radius + fDistance * fDistance - circle.Radius * circle.Radius) / (SFloat::_2 * this->Radius * fDistance));

        //STEP 4: If the equation above gives a value different of NaN, then circles intersect. Intersection points are calculated.
        if (!SFloat::IsNaN(fAngle))
        {
            vFirstI = this->Center + vV1 * (this->Radius * cos_z(fAngle)) + vV2 * (this->Radius * sin_z(fAngle));
            vSecondI = this->Center + vV1 * (this->Radius * cos_z(fAngle)) - vV2 * (this->Radius * sin_z(fAngle));

            if (SFloat::AreEqual(vFirstI.x, vSecondI.x) && SFloat::AreEqual(vFirstI.y, vSecondI.y))
            {
                float_z fRadiusAddition = this->Radius + circle.Radius;

                if (fRadiusAddition > fDistance)
                {
                    //One circle is contained into another.
                    return EIntersections::E_Infinite;
                }
                else
                {
                    vIntersection1 = vFirstI;

                    //Circles intersect in one point.
                    return EIntersections::E_One;
                }

            }
            else
            {
                vIntersection1 = vFirstI;
                vIntersection2 = vSecondI;

                //Circles intersect in two points.
                return EIntersections::E_Two;
            }
        }
    }

    //STEP 5: Checks if one circle is contained or not into the other (circles may even have the same center point). Otherwise, circles don't intersect.
    if (Intersection(circle))
    {
        //One of the circles is contained into the other.
        return EIntersections::E_Infinite;
    }

    //Circles don't intersect.
    return EIntersections::E_None;
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |         PROPERTIES         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

const Circle& Circle::GetUnitCircle()
{
    static const Circle UNITCIRCLE(Vector2::GetNullVector(), SFloat::_1);
    return UNITCIRCLE;
}


} // namespace z
