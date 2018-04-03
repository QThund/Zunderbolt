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

#include "ZMath/Quadrilateral.h"

#include "ZMath/LineSegment2D.h"
#include "ZMath/SAngle.h"
#include "ZMath/SPoint.h"



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

Quadrilateral::Quadrilateral()
{
}

Quadrilateral::Quadrilateral(const Quadrilateral &quad) : BaseQuadrilateral(quad)
{
}

Quadrilateral::Quadrilateral(const BaseQuadrilateral &quad) : BaseQuadrilateral(quad)
{
}

Quadrilateral::Quadrilateral(const Vector2 &vA, const Vector2 &vB, const Vector2 &vC, const Vector2 &vD ) :
                                    BaseQuadrilateral(vA, vB, vC, vD)
{
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |            METHODS         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

Quadrilateral& Quadrilateral::operator=(const BaseQuadrilateral &quad)
{
    BaseQuadrilateral::operator=(quad);
    return *this;
}

bool Quadrilateral::Contains (const BaseVector2 &vPoint) const
{
    if (this->IsConvex()) // Its convex
    {
        return (PointsInSameSideOfLine(vPoint, this->C, this->A, this->B) &&
                PointsInSameSideOfLine(vPoint, this->D, this->B, this->C) &&
                PointsInSameSideOfLine(vPoint, this->A, this->C, this->D) &&
                PointsInSameSideOfLine(vPoint, this->B, this->D, this->A));
    }
    else if (this->IsComplex()) // Its crossed
    {
        LineSegment2D ls1(this->A, this->D), ls2(this->B, this->C);
        Vector2 vAux;

        if (ls1.IntersectionPoint(ls2, vAux) == EIntersections::E_One) // Check if AD and BC edges cross themselves
        {
            // It checks both triangles (ABvAux and CDvAux)
            return (( PointsInSameSideOfLine(vPoint, vAux, this->A, this->B) &&
                      PointsInSameSideOfLine(vPoint, this->A, this->B, vAux) &&
                      PointsInSameSideOfLine(vPoint, this->B, vAux, this->A) ) ||
                    ( PointsInSameSideOfLine(vPoint, this->C, vAux, this->D) &&
                      PointsInSameSideOfLine(vPoint, vAux, this->D, this->C) &&
                      PointsInSameSideOfLine(vPoint, this->D, this->C, vAux) ));
        }
        else // AB and CD edges must cross themselves
        {
            // It checks both triangles (ADvAux and BCvAux)
            return (( PointsInSameSideOfLine(vPoint, this->A, vAux, this->D) &&
                  PointsInSameSideOfLine(vPoint, vAux, this->D, this->A) &&
                  PointsInSameSideOfLine(vPoint, this->D, this->A, vAux) ) ||
                ( PointsInSameSideOfLine(vPoint, this->B, this->C, vAux) &&
                  PointsInSameSideOfLine(vPoint, this->C, vAux, this->B) &&
                  PointsInSameSideOfLine(vPoint, vAux, this->B, this->C) ));
        }
    }
    else if (this->IsReflexAngle(this->A, this->B, this->D, this->C)) // Its concave in A vertex
    {
        // We check the two triangles around A vertex
        return (( PointsInSameSideOfLine(vPoint, this->C, this->A, this->B) &&
                  PointsInSameSideOfLine(vPoint, this->A, this->B, this->C) &&
                  PointsInSameSideOfLine(vPoint, this->B, this->C, this->A) ) ||
                ( PointsInSameSideOfLine(vPoint, this->C, this->A, this->D) &&
                  PointsInSameSideOfLine(vPoint, this->A, this->D, this->C) &&
                  PointsInSameSideOfLine(vPoint, this->D, this->C, this->A) ));
    }
    else if (this->IsReflexAngle(this->B, this->A, this->C, this->D)) // Its concave in B vertex
    {
        // We check the two triangles around B vertex
        return (( PointsInSameSideOfLine(vPoint, this->D, this->B, this->C) &&
                  PointsInSameSideOfLine(vPoint, this->B, this->C, this->D) &&
                  PointsInSameSideOfLine(vPoint, this->C, this->D, this->B) ) ||
                ( PointsInSameSideOfLine(vPoint, this->A, this->B, this->D) &&
                  PointsInSameSideOfLine(vPoint, this->B, this->D, this->A) &&
                  PointsInSameSideOfLine(vPoint, this->D, this->A, this->B) ));
    }
    else if (this->IsReflexAngle(this->C, this->B, this->D, this->A)) // Its concave in C vertex
    {
        // We check the two triangles around C vertex
        return (( PointsInSameSideOfLine(vPoint, this->A, this->C, this->D) &&
                  PointsInSameSideOfLine(vPoint, this->C, this->D, this->A) &&
                  PointsInSameSideOfLine(vPoint, this->D, this->A, this->C) ) ||
                ( PointsInSameSideOfLine(vPoint, this->B, this->C, this->A) &&
                  PointsInSameSideOfLine(vPoint, this->C, this->A, this->B) &&
                  PointsInSameSideOfLine(vPoint, this->A, this->B, this->C) ));
    }
    else // It must be concave in D vertex
    {
        // We check the two triangles around D vertex
        return (( PointsInSameSideOfLine(vPoint, this->B, this->D, this->A) &&
                  PointsInSameSideOfLine(vPoint, this->D, this->A, this->B) &&
                  PointsInSameSideOfLine(vPoint, this->A, this->B, this->D) ) ||
                ( PointsInSameSideOfLine(vPoint, this->C, this->D, this->B) &&
                  PointsInSameSideOfLine(vPoint, this->D, this->B, this->C) &&
                  PointsInSameSideOfLine(vPoint, this->B, this->C, this->D) ));
    }
}

bool Quadrilateral::Intersection(const BaseQuadrilateral &quad) const
{

    // Checks if any edge of resident quadrilateral intersects with q
    LineSegment2D ls1(this->A, this->B);
    if ( ls1.Intersection(quad) )
        return true;

    ls1 = LineSegment2D(this->B, this->C);
    if ( ls1.Intersection(quad) )
        return true;

    ls1 = LineSegment2D(this->C, this->D);
    if ( ls1.Intersection(quad) )
        return true;

    ls1 = LineSegment2D(this->D, this->A);
    if ( ls1.Intersection(quad) )
        return true;

    // q may be contained by resident quadrilateral, we check it.
    if ( this->Contains(quad.A) )
        return true;

    return false;
}

bool Quadrilateral::IsComplex() const
{
    return ( ( !PointsInSameSideOfLine(this->A, this->D, this->B, this->C) &&
               !PointsInSameSideOfLine(this->C, this->B, this->A, this->D) ) ||
             ( !PointsInSameSideOfLine(this->A, this->B, this->D, this->C) &&
               !PointsInSameSideOfLine(this->C, this->D, this->A, this->B) ) );
}

bool Quadrilateral::IsConvex() const
{
    LineSegment2D ls1(this->A, this->C);
    LineSegment2D ls2(this->B, this->D);

    return ls1.Intersection(ls2);
}

bool Quadrilateral::IsConcave() const
{
    return !this->IsConvex();
}

float_z Quadrilateral::GetAngleA() const
{
    // Contiguous vertices shouldn't coincide
    Z_ASSERT_WARNING(this->A != this->B && this->A != this->D, "Contiguous vertices shouldn't coincide");

    const float_z &ANGLE = (this->D - this->A).AngleBetween(this->B - this->A);

    if (this->IsReflexAngle(this->A, this->B, this->D, this->C))
    {
        #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
            return SAngle::_360 - ANGLE;
        #else
            return SAngle::_2Pi - ANGLE;
        #endif
    }
    else
        return ANGLE;
}

float_z Quadrilateral::GetAngleB() const
{
    // Contiguous vertices shouldn't coincide
    Z_ASSERT_WARNING(this->B != this->A && this->B != this->C, "Contiguous vertices shouldn't coincide");

    const float_z &ANGLE = (this->A - this->B).AngleBetween(this->C - this->B);

    if (this->IsReflexAngle(this->B, this->A, this->C, this->D))
    {
        #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
            return SAngle::_360 - ANGLE;
        #else
            return SAngle::_2Pi - ANGLE;
        #endif
    }
    else
        return ANGLE;
}

float_z Quadrilateral::GetAngleC() const
{
    // Contiguous vertices shouldn't coincide
    Z_ASSERT_WARNING(this->C != this->B && this->C != this->D, "Contiguous vertices shouldn't coincide");

    const float_z &ANGLE = (this->B - this->C).AngleBetween(this->D - this->C);

    if (this->IsReflexAngle(this->C, this->B, this->D, this->A))
    {
        #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
            return SAngle::_360 - ANGLE;
        #else
            return SAngle::_2Pi - ANGLE;
        #endif
    }
    else
        return ANGLE;
}

float_z Quadrilateral::GetAngleD() const
{
    // Contiguous vertices shouldn't coincide
    Z_ASSERT_WARNING(this->D != this->A && this->D != this->C, "Contiguous vertices shouldn't coincide");

    const float_z &ANGLE = (this->C - this->D).AngleBetween(this->A - this->D);

    if (this->IsReflexAngle(this->D, this->A, this->C, this->B))
    {
        #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
            return SAngle::_360 - ANGLE;
        #else
            return SAngle::_2Pi - ANGLE;
        #endif
    }
    else
        return ANGLE;
}

Quadrilateral Quadrilateral::Rotate(const float_z fRotationAngle) const
{
    Quadrilateral auxQuadrilateral = *this;
    SPoint::Rotate(fRotationAngle, rcast_z(&auxQuadrilateral, Vector2*), 4);
    return auxQuadrilateral;
}

Quadrilateral Quadrilateral::Translate(const BaseVector2 &vTranslation) const
{
    Quadrilateral auxQuadrilateral = *this;
    SPoint::Translate(vTranslation, rcast_z(&auxQuadrilateral, Vector2*), 4);
    return auxQuadrilateral;
}

Quadrilateral Quadrilateral::Translate(const float_z fTranslationX, const float_z fTranslationY) const
{
    Quadrilateral auxQuadrilateral = *this;
    SPoint::Translate(fTranslationX, fTranslationY, rcast_z(&auxQuadrilateral, Vector2*), 4);
    return auxQuadrilateral;
}

Quadrilateral Quadrilateral::Scale(const BaseVector2 &vScale) const
{
    Quadrilateral auxQuadrilateral = *this;
    SPoint::Scale(vScale, rcast_z(&auxQuadrilateral, Vector2*), 4);
    return auxQuadrilateral;
}

Quadrilateral Quadrilateral::Scale(const float_z fScaleX, const float_z fScaleY) const
{
    Quadrilateral auxQuadrilateral = *this;
    SPoint::Scale(fScaleX, fScaleY, rcast_z(&auxQuadrilateral, Vector2*), 4);
    return auxQuadrilateral;
}

Quadrilateral Quadrilateral::Transform(const TransformationMatrix3x3 &transformation) const
{
    Quadrilateral auxQuadrilateral = *this;
    SPoint::Transform(transformation, rcast_z(&auxQuadrilateral, Vector2*), 4);
    return auxQuadrilateral;
}

Quadrilateral Quadrilateral::RotateWithPivot(const float_z fRotationAngle, const Vector2 &vPivot) const
{
    Quadrilateral auxQuadrilateral = *this;
    SPoint::RotateWithPivot(fRotationAngle, vPivot, rcast_z(&auxQuadrilateral, Vector2*), 4);
    return auxQuadrilateral;
}

Quadrilateral Quadrilateral::ScaleWithPivot(const BaseVector2 &vScale, const BaseVector2 &vPivot) const
{
    Quadrilateral auxQuadrilateral = *this;
    SPoint::ScaleWithPivot(vScale, vPivot, rcast_z(&auxQuadrilateral, Vector2*), 4);
    return auxQuadrilateral;
}

Quadrilateral Quadrilateral::ScaleWithPivot(const float_z fScaleX, const float_z fScaleY, const BaseVector2 &vPivot) const
{
    Quadrilateral auxQuadrilateral = *this;
    SPoint::ScaleWithPivot(fScaleX, fScaleY, vPivot, rcast_z(&auxQuadrilateral, Vector2*), 4);
    return auxQuadrilateral;
}

Quadrilateral Quadrilateral::TransformWithPivot(const TransformationMatrix3x3 &transformation, const BaseVector2 &vPivot) const
{
    Quadrilateral auxQuadrilateral = *this;
    SPoint::TransformWithPivot(transformation, vPivot, rcast_z(&auxQuadrilateral, Vector2*), 4);
    return auxQuadrilateral;
}

string_z Quadrilateral::ToString() const
{
    return string_z("QL(a(") + this->A.ToString() + Z_L("),b(") +
                               this->B.ToString() + Z_L("),c(") +
                               this->C.ToString() + Z_L("),d(") +
                               this->D.ToString() + Z_L("))");
}

bool Quadrilateral::PointsInSameSideOfLine(const BaseVector2 &vPoint1, const BaseVector2 &vPoint2,
                                            const BaseVector2 &vLine1, const BaseVector2 &vLine2) const
{

    const float_z &ORIENTATION1 = (vLine1.x - vPoint1.x)*(vLine2.y - vPoint1.y) - (vLine1.y - vPoint1.y)*(vLine2.x - vPoint1.x);
    const float_z &ORIENTATION2 = (vLine1.x - vPoint2.x)*(vLine2.y - vPoint2.y) - (vLine1.y - vPoint2.y)*(vLine2.x - vPoint2.x);

    if ( SFloat::IsZero(ORIENTATION1) || SFloat::IsZero(ORIENTATION2) )
        return true;
    else
        return ( SFloat::IsNegative(ORIENTATION1) == SFloat::IsNegative(ORIENTATION2) );
}


bool Quadrilateral::IsReflexAngle(const Vector2 &vAngleVertex, const Vector2 &vContiguousVertex1,
                                   const Vector2 &vContiguousVertex2, const Vector2 &vOppositeVertex) const
{
    if (this->IsConvex() || this->IsComplex()) // There isn't a concave angle.
        return false;
    else if ( !PointsInSameSideOfLine(vOppositeVertex, vAngleVertex, vContiguousVertex1, vContiguousVertex2) )
        return false; // The outer diagonal should not divide quadrilateral
    else
    {
        LineSegment2D ls(vContiguousVertex1, vContiguousVertex2);

        // Angle vertex must be the closest to outer diagonal
        return ( ls.MinDistance(vAngleVertex) < ls.MinDistance(vOppositeVertex) );
    }
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |         PROPERTIES         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

const Quadrilateral& Quadrilateral::GetUnitSquare()
{
    static const Quadrilateral UNITSQUARE(Vector2(-SFloat::_0_5,   SFloat::_0_5),
                                           Vector2( SFloat::_0_5,   SFloat::_0_5),
                                           Vector2( SFloat::_0_5,  -SFloat::_0_5),
                                           Vector2(-SFloat::_0_5,  -SFloat::_0_5));
    return UNITSQUARE;
}


} // namespace z
