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


#include "ZMath/LineSegment2D.h"

#include "ZCommon/Assertions.h"
#include "ZMath/BaseTriangle.h"
#include "ZMath/BaseQuadrilateral.h"
#include "ZMath/SPoint.h"
#include "ZMath/TransformationMatrix3x3.h"



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

LineSegment2D::LineSegment2D()
{
}

LineSegment2D::LineSegment2D(const LineSegment2D &segment) : LineSegment<Vector2>(segment.A, segment.B)
{
}

LineSegment2D::LineSegment2D(const BaseLineSegment<Vector2> &segment) : LineSegment<Vector2>(segment.A, segment.B)
{
}

LineSegment2D::LineSegment2D(const Vector2& vA, const Vector2& vB) : LineSegment<Vector2>(vA,vB)
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

LineSegment2D& LineSegment2D::operator=(const BaseLineSegment<Vector2> &segment)
{
    BaseLineSegment<Vector2>::operator=(segment);
    return *this;
}

bool LineSegment2D::Intersection (const BaseTriangle<Vector2>& triangle) const
{
    // The endpoints of the line shouldn't coincide
    Z_ASSERT_WARNING(this->A != this->B, "The endpoints of the line shouldn't coincide");

    // The vertices of the triangle shouldn't coincide
    Z_ASSERT_WARNING(triangle.A != triangle.B && triangle.B != triangle.C && triangle.C != triangle.A, "The vertices of the triangle shouldn't coincide");

    // Just checking if the segment instersects with any edge of the triangle.

    if ( this->Intersection(LineSegment2D(triangle.A, triangle.B)) ||
         this->Intersection(LineSegment2D(triangle.B, triangle.C)) ||
         this->Intersection(LineSegment2D(triangle.C, triangle.A)) )
        return true;
    else if (this->PointInsideTriangle(triangle, this->A))
        return true;
    else
        return false;
}

bool LineSegment2D::Intersection (const BaseQuadrilateral& quad) const
{
    // The endpoints of the line shouldn't coincide
    Z_ASSERT_WARNING(this->A != this->B, "The endpoints of the line shouldn't coincide");

    // The vertices of the quadrilateral shouldn't coincide
    Z_ASSERT_WARNING(quad.A != quad.B && quad.A != quad.C && quad.A != quad.D && 
              quad.B != quad.C && quad.B != quad.D &&
              quad.C != quad.D, "The vertices of the quadrilateral shouldn't coincide");

    if ( this->Intersection(LineSegment2D(quad.A, quad.B)) ||
         this->Intersection(LineSegment2D(quad.B, quad.C)) ||
         this->Intersection(LineSegment2D(quad.C, quad.D)) ||
         this->Intersection(LineSegment2D(quad.D, quad.A)))
        return true;
    else if (this->PointInsideQuadrilateral(quad, this->A))
        return true;
    else
        return false;
}

LineSegment2D LineSegment2D::Rotate(const float_z fRotationAngle) const
{
    LineSegment2D auxLineSegment = *this;
    SPoint::Rotate(fRotationAngle, rcast_z(&auxLineSegment, Vector2*), 2);
    return auxLineSegment;
}

LineSegment2D LineSegment2D::Translate(const BaseVector2 &vTranslation) const
{
    LineSegment2D auxLineSegment = *this;
    SPoint::Translate(vTranslation, rcast_z(&auxLineSegment, Vector2*), 2);
    return auxLineSegment;
}

LineSegment2D LineSegment2D::Translate(const float_z fTranslationX, const float_z fTranslationY) const
{
    LineSegment2D auxLineSegment = *this;
    SPoint::Translate(fTranslationX, fTranslationY, rcast_z(&auxLineSegment, Vector2*), 2);
    return auxLineSegment;
}

LineSegment2D LineSegment2D::Scale(const BaseVector2 &vScale) const
{
    LineSegment2D auxLineSegment = *this;
    SPoint::Scale(vScale, rcast_z(&auxLineSegment, Vector2*), 2);
    return auxLineSegment;
}

LineSegment2D LineSegment2D::Scale(const float_z fScaleX, const float_z fScaleY) const
{
    LineSegment2D auxLineSegment = *this;
    SPoint::Scale(fScaleX, fScaleY, rcast_z(&auxLineSegment, Vector2*), 2);
    return auxLineSegment;
}

LineSegment2D LineSegment2D::Transform(const TransformationMatrix3x3 &transformation) const
{
    LineSegment2D auxLineSegment = *this;
    SPoint::Transform(transformation, rcast_z(&auxLineSegment, Vector2*), 2);
    return auxLineSegment;
}

LineSegment2D LineSegment2D::RotateWithPivot(const float_z fRotationAngle, const Vector2 &vPivot) const
{
    LineSegment2D auxLineSegment = *this;
    SPoint::RotateWithPivot(fRotationAngle, vPivot, rcast_z(&auxLineSegment, Vector2*), 2);
    return auxLineSegment;
}

LineSegment2D LineSegment2D::ScaleWithPivot(const BaseVector2 &vScale, const BaseVector2 &vPivot) const
{
    LineSegment2D auxLineSegment = *this;
    SPoint::ScaleWithPivot(vScale, vPivot, rcast_z(&auxLineSegment, Vector2*), 2);
    return auxLineSegment;
}

LineSegment2D LineSegment2D::ScaleWithPivot(const float_z fScaleX, const float_z fScaleY, const BaseVector2 &vPivot) const
{
    LineSegment2D auxLineSegment = *this;
    SPoint::ScaleWithPivot(fScaleX, fScaleY, vPivot, rcast_z(&auxLineSegment, Vector2*), 2);
    return auxLineSegment;
}

LineSegment2D LineSegment2D::TransformWithPivot(const TransformationMatrix3x3 &transformation, const BaseVector2 &vPivot) const
{
    LineSegment2D auxLineSegment = *this;
    SPoint::TransformWithPivot(transformation, vPivot, rcast_z(&auxLineSegment, Vector2*), 2);
    return auxLineSegment;
}

EIntersections LineSegment2D::IntersectionPoint(const BaseTriangle<Vector2> &triangle, BaseVector2 &vIntersection) const
{
    BaseVector2 vAux;
    return this->IntersectionPoint(triangle, vIntersection, vAux);
}

EIntersections LineSegment2D::IntersectionPoint(const BaseTriangle<Vector2>& triangle, BaseVector2& vIntersection1, BaseVector2& vIntersection2) const
{
    // The endpoints of the line shouldn't coincide
    Z_ASSERT_WARNING(this->A != this->B, "The endpoints of the line shouldn't coincide");

    // The vertices of the triangle shouldn't coincide
    Z_ASSERT_WARNING(triangle.A != triangle.B && triangle.B != triangle.C && triangle.C != triangle.A, "The vertices of the triangle shouldn't coincide");

    const bool &A_IS_INSIDE = PointInsideTriangle(triangle, this->A);
    const bool &B_IS_INSIDE = PointInsideTriangle(triangle, this->B);

    if (A_IS_INSIDE && B_IS_INSIDE) // Both line segment end points are inside triangle.
    {
        // A or B are vertex
        const bool &A_IS_VERTEX = (this->A == triangle.A || this->A == triangle.B || this->A == triangle.C);
        const bool &B_IS_VERTEX = (this->B == triangle.A || this->B == triangle.B || this->B == triangle.C);

        if (A_IS_VERTEX && B_IS_VERTEX) // Both endpoints are vertices of triangle
        {
            if(this->A == this->B)
            {
                // The endpoints of the line shouldn't coincide
                vIntersection1 = this->A;
                return EIntersections::E_One;
            }
            else
            {
                vIntersection1 = this->A;
                vIntersection2 = this->B;
                return EIntersections::E_Two;
            }
        }
        else if (A_IS_VERTEX) // Only A endpoint is a vertex of triangle
        {
            vIntersection1 = this->A;

            if (SFloat::IsZero(LineSegment2D(triangle.A, triangle.B).MinDistance(this->B))) // B is in AB triangle edge
            {
                if (this->A == triangle.A || this->A == triangle.B) // A and B are in the same edge
                    return EIntersections::E_One;
                else
                {
                    vIntersection2 = this->B;
                    return EIntersections::E_Two;
                }
            }
            else if (SFloat::IsZero(LineSegment2D(triangle.B, triangle.C).MinDistance(this->B))) // B is in BC triangle edge
            {
                if (this->A == triangle.B || this->A == triangle.C) // A and B are in the same edge
                    return EIntersections::E_One;
                else
                {
                    vIntersection2 = this->B;
                    return EIntersections::E_Two;
                }
            }
            else if (SFloat::IsZero(LineSegment2D(triangle.C, triangle.A).MinDistance(this->B))) // B is in CA triangle edge
            {
                if (this->A == triangle.C || this->A == triangle.A) // A and B are in the same edge
                    return EIntersections::E_One;
                else
                {
                    vIntersection2 = this->B;
                    return EIntersections::E_Two;
                }
            }
            else // B is not in an edge
            {
                vIntersection1 = this->A;
                return EIntersections::E_One;
            }
        }
        else if (B_IS_VERTEX)
        {
            if (SFloat::IsZero(LineSegment2D(triangle.A, triangle.B).MinDistance(this->A))) // A is in AB triangle edge
            {
                if (this->B == triangle.A || this->B == triangle.B) // A and B are in the same edge
                {
                    vIntersection1 = this->B;
                    return EIntersections::E_One;
                }
                else
                {
                    vIntersection1 = this->A;
                    vIntersection2 = this->B;
                    return EIntersections::E_Two;
                }
            }
            else if (SFloat::IsZero(LineSegment2D(triangle.B, triangle.C).MinDistance(this->A))) // B is in BC triangle edge
            {
                if (this->B == triangle.B || this->B == triangle.C) // A and B are in the same edge
                {
                    vIntersection1 = this->B;
                    return EIntersections::E_One;
                }
                else
                {
                    vIntersection1 = this->A;
                    vIntersection2 = this->B;
                    return EIntersections::E_Two;
                }
            }
            else if (SFloat::IsZero(LineSegment2D(triangle.C, triangle.A).MinDistance(this->A))) // B is in CA triangle edge
            {
                if (this->B == triangle.C || this->B == triangle.A) // A and B are in the same edge
                {
                    vIntersection1 = this->B;
                    return EIntersections::E_One;
                }
                else
                {
                    vIntersection1 = this->A;
                    vIntersection2 = this->B;
                    return EIntersections::E_Two;
                }
            }
            else
            {
                vIntersection1 = this->B;
                return EIntersections::E_One;
            }
        }
        else // Neither A or B are vertices of triangle
        {
            if (SFloat::IsZero(LineSegment2D(triangle.A, triangle.B).MinDistance(this->A))) // A is in AB triangle edge (but not a vertex)
            {
                if (SFloat::IsZero(LineSegment2D(triangle.A, triangle.B).MinDistance(this->B)) || // B is in AB triangle edge (but not a vertex)
                    SFloat::IsZero(LineSegment2D(triangle.B, triangle.C).MinDistance(this->B)) || // B is in other edge (but not a vertex)
                    SFloat::IsZero(LineSegment2D(triangle.C, triangle.A).MinDistance(this->B)) )
                {
                    vIntersection1 = this->A;
                    vIntersection2 = this->B;
                    return EIntersections::E_Two;
                }
                else // B is not in an edge
                {
                    vIntersection1 = this->A;
                    return EIntersections::E_One;
                }
            }
            else if (SFloat::IsZero(LineSegment2D(triangle.B, triangle.C).MinDistance(this->A))) // A is in BC triangle edge (but not a vertex)
            {
                if (SFloat::IsZero(LineSegment2D(triangle.B, triangle.C).MinDistance(this->B)) || // B is in BC triangle edge (but not a vertex)
                    SFloat::IsZero(LineSegment2D(triangle.A, triangle.B).MinDistance(this->B)) || // B is in other edge (but not a vertex)
                    SFloat::IsZero(LineSegment2D(triangle.C, triangle.A).MinDistance(this->B)) )
                {
                    vIntersection1 = this->A;
                    vIntersection2 = this->B;
                    return EIntersections::E_Two;
                }
                else // B is not in an edge
                {
                    vIntersection1 = this->A;
                    return EIntersections::E_One;
                }
            }
            else if (SFloat::IsZero(LineSegment2D(triangle.C, triangle.A).MinDistance(this->A))) // A is in CA triangle edge (but not a vertex)
            {
                if (SFloat::IsZero(LineSegment2D(triangle.C, triangle.A).MinDistance(this->B)) || // B is in CA triangle edge (but not a vertex)
                    SFloat::IsZero(LineSegment2D(triangle.A, triangle.B).MinDistance(this->B)) || // B is in other edge (but not a vertex)
                    SFloat::IsZero(LineSegment2D(triangle.B, triangle.C).MinDistance(this->B)) )
                {
                    vIntersection1 = this->A;
                    vIntersection2 = this->B;
                    return EIntersections::E_Two;
                }
                else // B is not in an edge
                {
                    vIntersection1 = this->A;
                    return EIntersections::E_One;
                }
            }
            else // A is not in an edge
            {
                if ( SFloat::IsZero(LineSegment2D(triangle.A, triangle.B).MinDistance(this->B)) || // B is in an edge (but not a vertex)
                     SFloat::IsZero(LineSegment2D(triangle.B, triangle.C).MinDistance(this->B)) ||
                     SFloat::IsZero(LineSegment2D(triangle.C, triangle.A).MinDistance(this->B)) )
                {
                    vIntersection1 = this->B;
                    return EIntersections::E_One;
                }
                else // B is not in an edge
                    return EIntersections::E_Infinite;
            }
        }
    }
    else if (!A_IS_INSIDE && !B_IS_INSIDE) // Both line segments' end points are outside triangle.
    {
        Vector2 vPointAB, vPointBC, vPointCA;

        EIntersections value2AB = this->IntersectionPoint(LineSegment2D(triangle.A, triangle.B), vPointAB);

        if (value2AB == EIntersections::E_Infinite) // Line segment contains AB edge of triangle
        {
            if  ( (triangle.A - this->A).GetSquaredLength() < (triangle.B - this->A).GetSquaredLength() ) // Returns closest point to A end point of line segment
            {
                vIntersection1 = triangle.A;
                vIntersection2 = triangle.B;
            }
            else
            {
                vIntersection1 = triangle.B;
                vIntersection2 = triangle.A;
            }
            return EIntersections::E_Two;
        }

        // Line segment contains BC edge of triangle
        EIntersections value2BC = this->IntersectionPoint(LineSegment2D(triangle.B, triangle.C), vPointBC);
        if (value2BC == EIntersections::E_Infinite)
        {
            if  ( (triangle.B - this->A).GetSquaredLength() < (triangle.C - this->A).GetSquaredLength() ) // Returns closest point to A end point of line segment
            {
                vIntersection1 = triangle.B;
                vIntersection2 = triangle.C;
            }
            else
            {
                vIntersection1 = triangle.C;
                vIntersection2 = triangle.B;
            }
            return EIntersections::E_Two;
        }

        // Line segment contains CA edge of triangle
        EIntersections value2CA = this->IntersectionPoint(LineSegment2D(triangle.C, triangle.A), vPointCA);
        if (value2CA == EIntersections::E_Infinite)
        {
            if  ( (triangle.C - this->A).GetSquaredLength() < (triangle.A - this->A).GetSquaredLength() ) // Returns closest point to A end point of line segment
            {
                vIntersection1 = triangle.C;
                vIntersection2 = triangle.A;
            }
            else
            {
                vIntersection1 = triangle.A;
                vIntersection2 = triangle.C;
            }
            return EIntersections::E_Two;
        }

        if (value2AB ==EIntersections::E_One) // Line segment intersects AB edge of triangle
        {
            if (value2BC ==EIntersections::E_One) // Line segment intersects BC edge of triangle
            {
                if (vPointAB == vPointBC) // Are the same point (B vertex of triangle)
                {
                    if (value2CA ==EIntersections::E_One) // Line segment intersects CA edge of triangle
                    {
                        if  ( (vPointAB - this->A).GetSquaredLength() < (vPointCA - this->A).GetSquaredLength() ) // Returns closest point to A end point of line segment
                        {
                            vIntersection1 = vPointAB;
                            vIntersection2 = vPointCA;
                        }
                        else
                        {
                            vIntersection1 = vPointCA;
                            vIntersection2 = vPointAB;
                        }
                        return EIntersections::E_Two;
                    }
                    else
                    {
                        vIntersection1 = vPointAB;
                        return EIntersections::E_One;
                    }
                }
                else
                {
                    if  ( (vPointAB - this->A).GetSquaredLength() < (vPointBC - this->A).GetSquaredLength() ) // Returns closest point to A end point of line segment
                    {
                        vIntersection1 = vPointAB;
                        vIntersection2 = vPointBC;
                    }
                    else
                    {
                        vIntersection1 = vPointBC;
                        vIntersection2 = vPointAB;
                    }
                    return EIntersections::E_Two;
                }
            }
            else if (value2CA ==EIntersections::E_One) // Line segment intersects CA edge of triangle
            {
                if (vPointAB == vPointCA) // Are the same point
                {
                    vIntersection1 = vPointAB;
                    return EIntersections::E_One;
                }
                else
                {
                    // Returns closest point to A end point of line segment
                    if  ( (vPointAB - this->A).GetSquaredLength() < (vPointCA - this->A).GetSquaredLength() )
                    {
                        vIntersection1 = vPointAB;
                        vIntersection2 = vPointCA;
                    }
                    else
                    {
                        vIntersection1 = vPointCA;
                        vIntersection2 = vPointAB;
                    }

                    return EIntersections::E_Two;
                }
            }
            else                                                                                                   // Something is wrong: if end points of line segment are outside triangle,
                Z_ASSERT_WARNING(false, "Something really wrong is happening, this code branch should never be reached");  // line segment must intersects none or two edges, never only one.
        }
        else if (value2BC ==EIntersections::E_One) // Line segment intersects BC edge of triangle
        {
            if (value2CA ==EIntersections::E_One) // Line segment intersects CA edge of triangle
            {
                if (vPointBC == vPointCA) // Are the same point
                {
                    vIntersection1 = vPointBC;
                    return EIntersections::E_One;
                }
                else
                {
                    // Returns closest point to A end point of line segment
                    if  ( (vPointBC - this->A).GetSquaredLength() < (vPointCA - this->A).GetSquaredLength() )
                    {
                        vIntersection1 = vPointBC;
                        vIntersection2 = vPointCA;
                    }
                    else
                    {
                        vIntersection1 = vPointCA;
                        vIntersection2 = vPointBC;
                    }

                    return EIntersections::E_Two;
                }
            }
            else                                                                                                    // Something is wrong: if end points of line segment are outside triangle,
                Z_ASSERT_WARNING(false, "Something really wrong is happening, this code branch should never be reached");  // line segment must intersects none or two, never only one.
        }

        // Line segment don't intersects triangle
        if (value2AB == EIntersections::E_None && value2BC == EIntersections::E_None && value2CA == EIntersections::E_None)
            return EIntersections::E_None;
    }
    else // one line segment end point is inside and the other one is outside triangle.
    {
        Vector2 vAux; // To store intersection points

        if (A_IS_INSIDE) // this->A is inside triangle
        {
            if (this->A == triangle.A) // this->A is A triangle vertex
            {
                vIntersection1 = this->A;

                EIntersections value2 = this->IntersectionPoint(LineSegment2D(triangle.B, triangle.C), vAux);
                if (value2 == EIntersections::E_One) // ls intersects opposite edge
                {
                    vIntersection2 = vAux;
                    return EIntersections::E_Two;
                }
                else
                    return EIntersections::E_One; // ls only intersects triangle in A vertex
            }
            else if (this->A == triangle.B) // this->A is B triangle vertex
            {
                vIntersection1 = this->A;

                EIntersections value2 = this->IntersectionPoint(LineSegment2D(triangle.C, triangle.A), vAux);
                if (value2 == EIntersections::E_One) // ls intersects opposite edge
                {
                    vIntersection2 = vAux;
                    return EIntersections::E_Two;
                }
                else
                    return EIntersections::E_One; // ls only intersects triangle in B vertex
            }
            else if (this->A == triangle.C) // this->A is C triangle vertex
            {
                vIntersection1 = this->A;

                EIntersections value2 = this->IntersectionPoint(LineSegment2D(triangle.B, triangle.A), vAux);
                if (value2 == EIntersections::E_One) // ls intersects opposite edge
                {
                    vIntersection2 = vAux;
                    return EIntersections::E_Two;
                }
                else
                    return EIntersections::E_One;  // ls only intersects triangle in C vertex
            }
            else if (SFloat::IsZero(LineSegment2D(triangle.A, triangle.B).MinDistance(this->A))) // this->A is in AB triangle edge (but not a vertex)
            {
                vIntersection1 = this->A;

                // ls intersects other edges
                EIntersections value2 = this->IntersectionPoint(LineSegment2D(triangle.B, triangle.C), vAux);
                if (value2 == EIntersections::E_One)
                {
                    if (vAux == triangle.B || vAux == triangle.C) // Both intersections are in the same edge
                        return EIntersections::E_One;

                    vIntersection2 = vAux;
                    return EIntersections::E_Two;
                }
                else if ((value2 = this->IntersectionPoint(LineSegment2D(triangle.C, triangle.A), vAux)) == EIntersections::E_One)
                {
                    if (vAux == triangle.C || vAux == triangle.A) // Both intersections are in the same edge
                        return EIntersections::E_One;

                    vIntersection2 = vAux;
                    return EIntersections::E_Two;
                }
                else
                    return EIntersections::E_One;
            }
            else if (SFloat::IsZero(LineSegment2D(triangle.B, triangle.C).MinDistance(this->A))) // this->A is in BC triangle edge (but not a vertex)
            {
                vIntersection1 = this->A;

                 // ls intersects other edges
                EIntersections value2 = this->IntersectionPoint(LineSegment2D(triangle.A, triangle.B), vAux);
                if (value2 == EIntersections::E_One)
                {
                    if (vAux == triangle.A || vAux == triangle.B) // Both intersections are in the same edge
                        return EIntersections::E_One;

                    vIntersection2 = vAux;
                    return EIntersections::E_Two;
                }
                else if ((value2 = this->IntersectionPoint(LineSegment2D(triangle.C, triangle.A), vAux)) == EIntersections::E_One)
                {
                    if (vAux == triangle.C || vAux == triangle.A) // Both intersections are in the same edge
                        return EIntersections::E_One;

                    vIntersection2 = vAux;
                    return EIntersections::E_Two;
                }
                else
                    return EIntersections::E_One;
            }
            else if (SFloat::IsZero(LineSegment2D(triangle.C, triangle.A).MinDistance(this->A))) // this->A is in CA triangle edge (but not a vertex)
            {
                vIntersection1 = this->A;

                 // ls intersects other edges
                EIntersections value2 = this->IntersectionPoint(LineSegment2D(triangle.B, triangle.C), vAux);
                if (value2 == EIntersections::E_One)
                {
                    if (vAux == triangle.B || vAux == triangle.C) // Both intersections are in the same edge
                        return EIntersections::E_One;

                    vIntersection2 = vAux;
                    return EIntersections::E_Two;
                }
                else if ((value2 = this->IntersectionPoint(LineSegment2D(triangle.A, triangle.B), vAux)) == EIntersections::E_One)
                {
                    if (vAux == triangle.A || vAux == triangle.B) // Both intersections are in the same edge
                        return EIntersections::E_One;

                    vIntersection2 = vAux;
                    return EIntersections::E_Two;
                }
                else
                    return EIntersections::E_One;
            }
            else // this->A is strictly inside triangle: is not in a vertex or edge.
            {
                EIntersections value2 = this->IntersectionPoint(LineSegment2D(triangle.A, triangle.B), vAux);
                if (value2 == EIntersections::E_One)
                    vIntersection1 = vAux;
                else if ((value2 = this->IntersectionPoint(LineSegment2D(triangle.B, triangle.C), vAux)) == EIntersections::E_One)
                    vIntersection1 = vAux;
                else if ((value2 = this->IntersectionPoint(LineSegment2D(triangle.C, triangle.A), vAux)) == EIntersections::E_One)
                    vIntersection1 = vAux;
                else                                                                                                    // Something is wrong, if one point is inside and the other is outside,
                    Z_ASSERT_WARNING(false, "Something really wrong is happening, this code branch should never be reached");  // there must be intersections.

                return EIntersections::E_One;
            }
        }
        else // this->B is inside triangle (A is outside)
        {
            if (this->B == triangle.A) // this->B is triangle.A vertex
            {

                EIntersections value2 = this->IntersectionPoint(LineSegment2D(triangle.B, triangle.C), vAux);
                if (value2 == EIntersections::E_One) // ls intersects opposite edge
                {
                    vIntersection1 = vAux;
                    vIntersection2 = this->B;
                    return EIntersections::E_Two;
                }
                else // ls only intersects in A vertex
                {
                    vIntersection1 = this->B;
                    return EIntersections::E_One;
                }
            }
            else if (this->B == triangle.B) // this->B is triangle.B vertex
            {
                EIntersections value2 = this->IntersectionPoint(LineSegment2D(triangle.C, triangle.A), vAux);
                if (value2 == EIntersections::E_One) // ls intersects opposite edge
                {
                    vIntersection1 = vAux;
                    vIntersection2 = this->B;
                    return EIntersections::E_Two;
                }
                else // ls only intersects in B vertex
                {
                    vIntersection1 = this->B;
                    return EIntersections::E_One;
                }
            }
            else if (this->B == triangle.C) // this->B is triangle.C vertex
            {
                EIntersections value2 = this->IntersectionPoint(LineSegment2D(triangle.A, triangle.B), vAux);
                if (value2 == EIntersections::E_One) // ls intersects opposite edge
                {
                    vIntersection1 = vAux;
                    vIntersection2 = this->B;
                    return EIntersections::E_Two;
                }
                else // ls only intersects in C vertex
                {
                    vIntersection1 = this->B;
                    return EIntersections::E_One;
                }
            }
            else if (SFloat::IsZero(LineSegment2D(triangle.A, triangle.B).MinDistance(this->B))) // this->B is in AB triangle edge (but not a vertex)
            {
                // ls intersects the other edges
                EIntersections value2 = this->IntersectionPoint(LineSegment2D(triangle.B, triangle.C), vAux);
                if (value2 == EIntersections::E_One)
                {
                    vIntersection1 = vAux;

                    if (vAux == triangle.B || vAux == triangle.C) // Both intersections are in the same edge
                        return EIntersections::E_One;

                    vIntersection2 = this->B;
                    return EIntersections::E_Two;
                }
                else if ((value2 = this->IntersectionPoint(LineSegment2D(triangle.C, triangle.A), vAux)) == EIntersections::E_One)
                {
                    vIntersection1 = vAux;

                    if (vAux == triangle.C || vAux == triangle.A) // Both intersections are in the same edge
                        return EIntersections::E_One;

                    vIntersection2 = this->B;
                    return EIntersections::E_Two;
                }
                else // There is no other intersection
                {
                    vIntersection1 = this->B;
                    return EIntersections::E_One;
                }
            }
            else if (SFloat::IsZero(LineSegment2D(triangle.B, triangle.C).MinDistance(this->B))) // this->B is in BC triangle edge (but not a vertex)
            {
                // ls intersects the other edges
                EIntersections value2 = this->IntersectionPoint(LineSegment2D(triangle.A, triangle.B), vAux);
                if (value2 == EIntersections::E_One)
                {
                    vIntersection1 = vAux;

                    if (vAux == triangle.A || vAux == triangle.B) // Both intersections are in the same edge
                        return EIntersections::E_One;

                    vIntersection2 = this->B;
                    return EIntersections::E_Two;
                }
                else if ((value2 = this->IntersectionPoint(LineSegment2D(triangle.C, triangle.A), vAux)) == EIntersections::E_One)
                {
                    vIntersection1 = vAux;
                    vIntersection2 = this->B;
                    return EIntersections::E_Two;
                }
                else // There is no other intersection
                {
                    vIntersection1 = this->B;
                    return EIntersections::E_One;
                }
            }
            else if (SFloat::IsZero(LineSegment2D(triangle.C, triangle.A).MinDistance(this->B))) // this->B is in CA triangle edge (but not a vertex)
            {
                // ls intersects the other edges
                EIntersections value2 = this->IntersectionPoint(LineSegment2D(triangle.B, triangle.C), vAux);
                if (value2 == EIntersections::E_One)
                {
                    vIntersection1 = vAux;

                    if (vAux == triangle.B || vAux == triangle.C) // Both intersections are in the same edge
                        return EIntersections::E_One;

                    vIntersection2 = this->B;
                    return EIntersections::E_Two;
                }
                else if ((value2 = this->IntersectionPoint(LineSegment2D(triangle.A, triangle.B), vAux)) == EIntersections::E_One)
                {
                    vIntersection1 = vAux;

                    if (vAux == triangle.A || vAux == triangle.B) // Both intersections are in the same edge
                        return EIntersections::E_One;

                    vIntersection2 = this->B;
                    return EIntersections::E_Two;
                }
                else // There is no other intersection
                {
                    vIntersection1 = this->B;
                    return EIntersections::E_One;
                }
            }
            else // this->B is strictly inside triangle: is not in a vertex or edge.
            {
                EIntersections value2 = this->IntersectionPoint(LineSegment2D(triangle.A, triangle.B), vAux);
                if (value2 == EIntersections::E_One)
                    vIntersection1 = vAux;
                else if ((value2 = this->IntersectionPoint(LineSegment2D(triangle.B, triangle.C), vAux)) == EIntersections::E_One)
                    vIntersection1 = vAux;
                else if ((value2 = this->IntersectionPoint(LineSegment2D(triangle.C, triangle.A), vAux)) == EIntersections::E_One)
                    vIntersection1 = vAux;
                else                                                                                                    // Something is wrong, if one point is inside and the other is outside,
                    Z_ASSERT_WARNING(false, "Something really wrong is happening, this code branch should never be reached");  // there must be intersections.

                return EIntersections::E_One;
            }
        }
    }
    return EIntersections::E_None;
}

EIntersections LineSegment2D::IntersectionPoint(const BaseQuadrilateral& quad, BaseVector2& vIntersection1, BaseVector2& vIntersection2) const
{
    // The endpoints of the line shouldn't coincide
    Z_ASSERT_WARNING(this->A != this->B, "The endpoints of the line shouldn't coincide");

    // The vertices of the quadrilateral shouldn't coincide
    Z_ASSERT_WARNING(quad.A != quad.B && quad.A != quad.C && quad.A != quad.D && 
              quad.B != quad.C && quad.B != quad.D &&
              quad.C != quad.D, "The vertices of the quadrilateral shouldn't coincide");

    const bool &A_IS_INSIDE = PointInsideQuadrilateral(quad, this->A);
    const bool &B_IS_INSIDE = PointInsideQuadrilateral(quad, this->B);

    if (A_IS_INSIDE && B_IS_INSIDE) // Both line segment end points are inside quadrilateral.
    {
        // A or B are vertex
        const bool &A_IS_VERTEX = (this->A == quad.A || this->A == quad.B || this->A == quad.C || this->A == quad.D);
        const bool &B_IS_VERTEX = (this->B == quad.A || this->B == quad.B || this->B == quad.C || this->B == quad.D);

        if (A_IS_VERTEX && B_IS_VERTEX) // Both endpoints are vertices of quadrilateral
        {
            vIntersection1 = this->A;
            vIntersection2 = this->B;
            return EIntersections::E_Two;
        }
        else if (A_IS_VERTEX) // Only A endpoint is a vertex of quadrilateral
        {
            if (SFloat::IsZero(LineSegment2D(quad.A, quad.B).MinDistance(this->B))) // B is in AB quad edge
            {
                if (this->A == quad.A || this->A == quad.B) // A and B are in the same edge
                {
                    vIntersection1 = this->A;
                    return EIntersections::E_One;
                }
                else
                {
                    vIntersection1 = this->A;
                    vIntersection2 = this->B;
                    return EIntersections::E_Two;
                }
            }
            else if (SFloat::IsZero(LineSegment2D(quad.B, quad.C).MinDistance(this->B))) // B is in BC quad edge
            {
                if (this->A == quad.B || this->A == quad.C) // A and B are in the same edge
                {
                    vIntersection1 = this->A;
                    return EIntersections::E_One;
                }
                else
                {
                    vIntersection1 = this->A;
                    vIntersection2 = this->B;
                    return EIntersections::E_Two;
                }
            }
            else if (SFloat::IsZero(LineSegment2D(quad.C, quad.D).MinDistance(this->B))) // B is in CD quad edge
            {
                if (this->A == quad.C || this->A == quad.D) // A and B are in the same edge
                {
                    vIntersection1 = this->A;
                    return EIntersections::E_One;
                }
                else
                {
                    vIntersection1 = this->A;
                    vIntersection2 = this->B;
                    return EIntersections::E_Two;
                }
            }
            else if (SFloat::IsZero(LineSegment2D(quad.D, quad.A).MinDistance(this->B))) // B is in DA quad edge
            {
                if (this->A == quad.D || this->A == quad.A) // A and B are in the same edge
                {
                    vIntersection1 = this->A;
                    return EIntersections::E_One;
                }
                else
                {
                    vIntersection1 = this->A;
                    vIntersection2 = this->B;
                    return EIntersections::E_Two;
                }
            }
            else // B is not in an edge
            {
                vIntersection1 = this->A;
                return EIntersections::E_One;
            }
        }
        else if (B_IS_VERTEX)
        {
            if (SFloat::IsZero(LineSegment2D(quad.A, quad.B).MinDistance(this->A))) // A is in AB quad edge
            {
                if (this->B == quad.A || this->B == quad.B) // A and B are in the same edge
                {
                    vIntersection1 = this->B;
                    return EIntersections::E_One;
                }
                else
                {
                    vIntersection1 = this->A;
                    vIntersection2 = this->B;
                    return EIntersections::E_Two;
                }
            }
            else if (SFloat::IsZero(LineSegment2D(quad.B, quad.C).MinDistance(this->A))) // B is in BC quad edge
            {
                if (this->B == quad.B || this->B == quad.C) // A and B are in the same edge
                {
                    vIntersection1 = this->B;
                    return EIntersections::E_One;
                }
                else
                {
                    vIntersection1 = this->A;
                    vIntersection2 = this->B;
                    return EIntersections::E_Two;
                }
            }
            else if (SFloat::IsZero(LineSegment2D(quad.C, quad.D).MinDistance(this->A))) // B is in CD quad edge
            {
                if (this->B == quad.C || this->B == quad.D) // A and B are in the same edge
                {
                    vIntersection1 = this->B;
                    return EIntersections::E_One;
                }
                else
                {
                    vIntersection1 = this->A;
                    vIntersection2 = this->B;
                    return EIntersections::E_Two;
                }
            }
            else if (SFloat::IsZero(LineSegment2D(quad.D, quad.A).MinDistance(this->A))) // B is in DA quad edge
            {
                if (this->B == quad.D || this->B == quad.A) // A and B are in the same edge
                {
                    vIntersection1 = this->B;
                    return EIntersections::E_One;
                }
                else
                {
                    vIntersection1 = this->A;
                    vIntersection2 = this->B;
                    return EIntersections::E_Two;
                }
            }
            else
            {
                vIntersection1 = this->B;
                return EIntersections::E_One;
            }
        }
        else // Neither A or B are vertices of quadrilateral
        {
            if (SFloat::IsZero(LineSegment2D(quad.A, quad.B).MinDistance(this->A))) // A is in AB quad edge (but not a vertex)
            {
                if (SFloat::IsZero(LineSegment2D(quad.A, quad.B).MinDistance(this->B)) || // B is in AB quad edge (but not a vertex)
                    SFloat::IsZero(LineSegment2D(quad.B, quad.C).MinDistance(this->B)) || // B is in other edge (but not a vertex)
                    SFloat::IsZero(LineSegment2D(quad.C, quad.D).MinDistance(this->B)) ||
                    SFloat::IsZero(LineSegment2D(quad.D, quad.A).MinDistance(this->B)))
                {
                    vIntersection1 = this->A;
                    vIntersection2 = this->B;
                    return EIntersections::E_Two;
                }
                else // B is not in an edge
                {
                    vIntersection1 = this->A;
                    return EIntersections::E_One;
                }
            }
            else if (SFloat::IsZero(LineSegment2D(quad.B, quad.C).MinDistance(this->A))) // A is in BC quad edge (but not a vertex)
            {
                if (SFloat::IsZero(LineSegment2D(quad.B, quad.C).MinDistance(this->B)) || // B is in BC quad edge (but not a vertex)
                    SFloat::IsZero(LineSegment2D(quad.A, quad.B).MinDistance(this->B)) || // B is in other edge (but not a vertex)
                    SFloat::IsZero(LineSegment2D(quad.C, quad.D).MinDistance(this->B)) ||
                    SFloat::IsZero(LineSegment2D(quad.D, quad.A).MinDistance(this->B)))
                {
                    vIntersection1 = this->A;
                    vIntersection2 = this->B;
                    return EIntersections::E_Two;
                }
                else // B is not in an edge
                {
                    vIntersection1 = this->A;
                    return EIntersections::E_One;
                }
            }
            else if (SFloat::IsZero(LineSegment2D(quad.C, quad.D).MinDistance(this->A))) // A is in CD quad edge (but not a vertex)
            {
                if (SFloat::IsZero(LineSegment2D(quad.C, quad.D).MinDistance(this->B)) || // B is in CD quad edge (but not a vertex)
                    SFloat::IsZero(LineSegment2D(quad.A, quad.B).MinDistance(this->B)) || // B is in other edge (but not a vertex)
                    SFloat::IsZero(LineSegment2D(quad.B, quad.C).MinDistance(this->B)) ||
                    SFloat::IsZero(LineSegment2D(quad.D, quad.A).MinDistance(this->B)))
                {
                    vIntersection1 = this->A;
                    vIntersection2 = this->B;
                    return EIntersections::E_Two;
                }
                else // B is not in an edge
                {
                    vIntersection1 = this->A;
                    return EIntersections::E_One;
                }
            }
            else if (SFloat::IsZero(LineSegment2D(quad.D, quad.A).MinDistance(this->A))) // A is in DA quad edge (but not a vertex)
            {
                if (SFloat::IsZero(LineSegment2D(quad.D, quad.A).MinDistance(this->B)) || // B is in DA quad edge (but not a vertex)
                    SFloat::IsZero(LineSegment2D(quad.A, quad.B).MinDistance(this->B)) || // B is in other edge (but not a vertex)
                    SFloat::IsZero(LineSegment2D(quad.B, quad.C).MinDistance(this->B)) ||
                    SFloat::IsZero(LineSegment2D(quad.C, quad.D).MinDistance(this->B)))
                {
                    vIntersection1 = this->A;
                    vIntersection2 = this->B;
                    return EIntersections::E_Two;
                }
                else // B is not in an edge
                {
                    vIntersection1 = this->A;
                    return EIntersections::E_One;
                }
            }
            else // A is not in an edge
            {
                if (SFloat::IsZero(LineSegment2D(quad.A, quad.B).MinDistance(this->B)) || // B is in an edge (but not a vertex)
                    SFloat::IsZero(LineSegment2D(quad.B, quad.C).MinDistance(this->B)) ||
                    SFloat::IsZero(LineSegment2D(quad.C, quad.D).MinDistance(this->B)) ||
                    SFloat::IsZero(LineSegment2D(quad.D, quad.A).MinDistance(this->B)))
                {
                    vIntersection1 = this->B;
                    return EIntersections::E_One;
                }
                else // B is not in an edge
                    return EIntersections::E_Infinite;
            }
        }
    }
    else if (!A_IS_INSIDE && !B_IS_INSIDE) // Both line segment end points are outside quadrilateral.
    {
        Vector2 vPointAB, vPointBC, vPointCD, vPointDA;

        EIntersections value2AB = this->IntersectionPoint(LineSegment2D(quad.A, quad.B), vPointAB);

        if (value2AB == EIntersections::E_Infinite) // Line segment contains AB edge of quadrilateral
        {
            if  ( (quad.A - this->A).GetSquaredLength() < (quad.B - this->A).GetSquaredLength() ) // Returns closest point to A end point of line segment
            {
                vIntersection1 = quad.A;
                vIntersection2 = quad.B;
            }
            else
            {
                vIntersection1 = quad.B;
                vIntersection2 = quad.A;
            }
            return EIntersections::E_Two;
        }

        // Line segment contains BC edge of quadrilateral
        EIntersections value2BC = this->IntersectionPoint(LineSegment2D(quad.B, quad.C), vPointBC);
        if (value2BC == EIntersections::E_Infinite)
        {
            if  ( (quad.B - this->A).GetSquaredLength() < (quad.C - this->A).GetSquaredLength() ) // Returns closest point to A end point of line segment
            {
                vIntersection1 = quad.B;
                vIntersection2 = quad.C;
            }
            else
            {
                vIntersection1 = quad.C;
                vIntersection2 = quad.B;
            }
            return EIntersections::E_Two;
        }

        // Line segment contains CA edge of quadrilateral
        EIntersections value2CD = this->IntersectionPoint(LineSegment2D(quad.C, quad.D), vPointCD);
        if (value2CD == EIntersections::E_Infinite)
        {
            if  ( (quad.C - this->A).GetSquaredLength() < (quad.D - this->A).GetSquaredLength() ) // Returns closest point to A end point of line segment
            {
                vIntersection1 = quad.C;
                vIntersection2 = quad.D;
            }
            else
            {
                vIntersection1 = quad.D;
                vIntersection2 = quad.C;
            }
            return EIntersections::E_Two;
        }

        // Line segment contains DA edge of quadrilateral
        EIntersections value2DA = this->IntersectionPoint(LineSegment2D(quad.D, quad.A), vPointDA);
        if (value2DA == EIntersections::E_Infinite)
        {
            if  ( (quad.D - this->A).GetSquaredLength() < (quad.A - this->A).GetSquaredLength() ) // Returns closest point to A end point of line segment
            {
                vIntersection1 = quad.D;
                vIntersection2 = quad.A;
            }
            else
            {
                vIntersection1 = quad.A;
                vIntersection2 = quad.D;
            }
            return EIntersections::E_Two;
        }

        if (value2AB == EIntersections::E_One) // Line segment intersects AB edge of quadrilateral
        {
            if (value2BC == EIntersections::E_One) // Line segment intersects BC edge of quadrilateral
            {
                if (vPointAB == vPointBC) // Are the same point (B vertex of quadrilateral)
                {
                    if (value2CD == EIntersections::E_One) // Line segment intersects CD edge of quadrilateral
                    {
                        // Returns closest point to A end point of line segment
                        if  ( (vPointAB - this->A).GetSquaredLength() < (vPointCD - this->A).GetSquaredLength() )
                        {
                            vIntersection1 = vPointAB;
                            vIntersection2 = vPointCD;
                        }
                        else
                        {
                            vIntersection1 = vPointCD;
                            vIntersection2 = vPointAB;
                        }

                        return EIntersections::E_Two;
                    }
                    else if (value2DA == EIntersections::E_One) // Line segment intersects DA edge of quadrilateral
                    {
                        // Returns closest point to A end point of line segment
                        if  ( (vPointAB - this->A).GetSquaredLength() < (vPointDA - this->A).GetSquaredLength() )
                        {
                            vIntersection1 = vPointAB;
                            vIntersection2 = vPointDA;
                        }
                        else
                        {
                            vIntersection1 = vPointDA;
                            vIntersection2 = vPointAB;
                        }

                        return EIntersections::E_Two;
                    }
                    else
                    {
                        vIntersection1 = vPointAB;
                        return EIntersections::E_One;
                    }
                }
                else
                {
                    if  ( (vPointAB - this->A).GetSquaredLength() < (vPointBC - this->A).GetSquaredLength() ) // Returns closest point to A end point of line segment
                    {
                        vIntersection1 = vPointAB;
                        vIntersection2 = vPointBC;
                    }
                    else
                    {
                        vIntersection1 = vPointBC;
                        vIntersection2 = vPointAB;
                    }
                    return EIntersections::E_Two;
                }
            }
            else if (value2CD == EIntersections::E_One) // Line segment intersects CD edge of quadrilateral
            {
                // Returns closest point to A end point of line segment
                if  ( (vPointAB - this->A).GetSquaredLength() < (vPointCD - this->A).GetSquaredLength() )
                {
                    vIntersection1 = vPointAB;
                    vIntersection2 = vPointCD;
                }
                else
                {
                    vIntersection1 = vPointCD;
                    vIntersection2 = vPointAB;
                }

                return EIntersections::E_Two;
            }
            else if (value2DA == EIntersections::E_One) // Line segment intersects DA edge of quadrilateral
            {
                if (vPointAB == vPointDA) // Are the same point
                {
                    vIntersection1 = vPointAB;
                    return EIntersections::E_One;
                }
                else
                {
                    // Returns closest point to A end point of line segment
                    if  ( (vPointAB - this->A).GetSquaredLength() < (vPointDA - this->A).GetSquaredLength() )
                    {
                        vIntersection1 = vPointAB;
                        vIntersection2 = vPointDA;
                    }
                    else
                    {
                        vIntersection1 = vPointDA;
                        vIntersection2 = vPointAB;
                    }

                    return EIntersections::E_Two;
                }
            }
        }
        else if (value2BC == EIntersections::E_One) // Line segment intersects BC edge of quadrilateral
        {
            if (value2CD == EIntersections::E_One) // Line segment intersects CA edge of quadrilateral
            {
                if (vPointBC == vPointCD) // Are the same point (C vertex of quadrilateral)
                {
                    if (value2DA == EIntersections::E_One) // Line segment intersects DA edge of quadrilateral
                    {
                        // Returns closest point to A end point of line segment
                        if  ( (vPointBC - this->A).GetSquaredLength() < (vPointDA - this->A).GetSquaredLength() )
                        {
                            vIntersection1 = vPointBC;
                            vIntersection2 = vPointDA;
                        }
                        else
                        {
                            vIntersection1 = vPointDA;
                            vIntersection2 = vPointBC;
                        }

                        return EIntersections::E_Two;
                    }
                    else
                    {
                        vIntersection1 = vPointBC;
                        return EIntersections::E_One;
                    }
                }
                else
                {
                    // Returns closest point to A end point of line segment
                    if  ( (vPointBC - this->A).GetSquaredLength() < (vPointCD - this->A).GetSquaredLength() )
                    {
                        vIntersection1 = vPointBC;
                        vIntersection2 = vPointCD;
                    }
                    else
                    {
                        vIntersection1 = vPointCD;
                        vIntersection2 = vPointBC;
                    }

                    return EIntersections::E_Two;
                }
            }
            else if (value2DA == EIntersections::E_One)
            {
                // Returns closest point to A end point of line segment
                if  ( (vPointBC - this->A).GetSquaredLength() < (vPointDA - this->A).GetSquaredLength() )
                {
                    vIntersection1 = vPointBC;
                    vIntersection2 = vPointDA;
                }
                else
                {
                    vIntersection1 = vPointDA;
                    vIntersection2 = vPointBC;
                }

                return EIntersections::E_Two;
            }
        }
        else if (value2CD ==EIntersections::E_One) // Line segment intersects CD edge of quadrilateral
        {
            if (value2DA == EIntersections::E_One) // Line segment intersects DA edge of quadrilateral
            {
                if (vPointCD == vPointDA) // Are the same point (D vertex of quadrilateral)
                {
                    vIntersection1 = vPointCD;
                    return EIntersections::E_One;
                }
                else
                {
                    // Returns closest point to A end point of line segment
                    if  ( (vPointCD - this->A).GetSquaredLength() < (vPointDA - this->A).GetSquaredLength() )
                    {
                        vIntersection1 = vPointCD;
                        vIntersection2 = vPointDA;
                    }
                    else
                    {
                        vIntersection1 = vPointDA;
                        vIntersection2 = vPointCD;
                    }

                    return EIntersections::E_Two;
                }
            }
        }
        else
            return EIntersections::E_None; // There are no intersections.
    }
    else // one line segment end point is inside and the other one is outside triangle.
    {
        Vector2 vAux; // To store intersection points

        if (A_IS_INSIDE) // this->A is inside quadrilateral
        {
            if (this->A == quad.A) // this->A is quad.A vertex
            {
                vIntersection1 = this->A;

                // ls intersects opposite edges
                EIntersections value2 = this->IntersectionPoint(LineSegment2D(quad.B, quad.C), vAux);
                if (value2 == EIntersections::E_One)
                {
                    vIntersection2 = vAux;
                    return EIntersections::E_Two;
                }
                else if ((value2 = this->IntersectionPoint(LineSegment2D(quad.C, quad.D), vAux)) == EIntersections::E_One)
                {
                    vIntersection2 = vAux;
                    return EIntersections::E_Two;
                }
                else
                    return EIntersections::E_One;
            }
            else if (this->A == quad.B) // this->A is quad.B vertex
            {
                vIntersection1 = this->A;

                // ls intersects opposite edges
                EIntersections value2 = this->IntersectionPoint(LineSegment2D(quad.C, quad.D), vAux);
                if (value2 == EIntersections::E_One)
                {
                    vIntersection2 = vAux;
                    return EIntersections::E_Two;
                }
                else if ((value2 = this->IntersectionPoint(LineSegment2D(quad.D, quad.A), vAux)) == EIntersections::E_One)
                {
                    vIntersection2 = vAux;
                    return EIntersections::E_Two;
                }
                else
                    return EIntersections::E_One;
            }
            else if (this->A == quad.C) // this->A is quad.C vertex
            {
                vIntersection1 = this->A;

                // ls intersects opposite edges
                EIntersections value2 = this->IntersectionPoint(LineSegment2D(quad.D, quad.A), vAux);
                if (value2 == EIntersections::E_One)
                {
                    vIntersection2 = vAux;
                    return EIntersections::E_Two;
                }
                else if ((value2 = this->IntersectionPoint(LineSegment2D(quad.A, quad.B), vAux)) == EIntersections::E_One)
                {
                    vIntersection2 = vAux;
                    return EIntersections::E_Two;
                }
                else
                    return EIntersections::E_One;
            }
            else if (this->A == quad.D) // this->A is quad.D vertex
            {
                vIntersection1 = this->A;

                // ls intersects opposite edges
                EIntersections value2 = this->IntersectionPoint(LineSegment2D(quad.A, quad.B), vAux);
                if (value2 == EIntersections::E_One)
                {
                    vIntersection2 = vAux;
                    return EIntersections::E_Two;
                }
                else if ((value2 = this->IntersectionPoint(LineSegment2D(quad.B, quad.C), vAux)) == EIntersections::E_One)
                {
                    vIntersection2 = vAux;
                    return EIntersections::E_Two;
                }
                else
                    return EIntersections::E_One;
            }
            else if (SFloat::IsZero(LineSegment2D(quad.A, quad.B).MinDistance(this->A))) // this->A is in AB quad edge (but not a vertex)
            {
                vIntersection1 = this->A;

                // ls intersects other edges
                EIntersections value2 = this->IntersectionPoint(LineSegment2D(quad.B, quad.C), vAux);
                if (value2 == EIntersections::E_One)
                {
                    if (vAux == quad.B || vAux == quad.C) // Both intersections are in the same edge
                        return EIntersections::E_One;

                    vIntersection2 = vAux;
                    return EIntersections::E_Two;
                }
                else if ((value2 = this->IntersectionPoint(LineSegment2D(quad.C, quad.D), vAux)) == EIntersections::E_One)
                {
                    if (vAux == quad.C || vAux == quad.D) // Both intersections are in the same edge
                        return EIntersections::E_One;

                    vIntersection2 = vAux;
                    return EIntersections::E_Two;
                }
                else if ((value2 = this->IntersectionPoint(LineSegment2D(quad.D, quad.A), vAux)) == EIntersections::E_One)
                {
                    if (vAux == quad.D || vAux == quad.A) // Both intersections are in the same edge
                        return EIntersections::E_One;

                    vIntersection2 = vAux;
                    return EIntersections::E_Two;
                }
                else
                    return EIntersections::E_One;
            }
            else if (SFloat::IsZero(LineSegment2D(quad.B, quad.C).MinDistance(this->A))) // this->A is in BC quad edge (but not a vertex)
            {
                vIntersection1 = this->A;

                 // ls intersects other edges
                EIntersections value2 = this->IntersectionPoint(LineSegment2D(quad.A, quad.B), vAux);
                if (value2 == EIntersections::E_One)
                {
                    if (vAux == quad.A || vAux == quad.B) // Both intersections are in the same edge
                        return EIntersections::E_One;

                    vIntersection2 = vAux;
                    return EIntersections::E_Two;
                }
                else if ((value2 = this->IntersectionPoint(LineSegment2D(quad.C, quad.D), vAux)) == EIntersections::E_One)
                {
                    if (vAux == quad.C || vAux == quad.D) // Both intersections are in the same edge
                        return EIntersections::E_One;

                    vIntersection2 = vAux;
                    return EIntersections::E_Two;
                }
                else if ((value2 = this->IntersectionPoint(LineSegment2D(quad.D, quad.A), vAux)) == EIntersections::E_One)
                {
                    if (vAux == quad.D || vAux == quad.A) // Both intersections are in the same edge
                        return EIntersections::E_One;

                    vIntersection2 = vAux;
                    return EIntersections::E_Two;
                }
                else
                    return EIntersections::E_One;
            }
            else if (SFloat::IsZero(LineSegment2D(quad.C, quad.D).MinDistance(this->A))) // this->A is in CD quad edge (but not a vertex)
            {
                vIntersection1 = this->A;

                 // ls intersects other edges
                EIntersections value2 = this->IntersectionPoint(LineSegment2D(quad.B, quad.C), vAux);
                if (value2 == EIntersections::E_One)
                {
                    if (vAux == quad.B || vAux == quad.C) // Both intersections are in the same edge
                        return EIntersections::E_One;

                    vIntersection2 = vAux;
                    return EIntersections::E_Two;
                }
                else if ((value2 = this->IntersectionPoint(LineSegment2D(quad.A, quad.B), vAux)) == EIntersections::E_One)
                {
                    if (vAux == quad.A || vAux == quad.B) // Both intersections are in the same edge
                        return EIntersections::E_One;

                    vIntersection2 = vAux;
                    return EIntersections::E_Two;
                }
                else if ((value2 = this->IntersectionPoint(LineSegment2D(quad.D, quad.A), vAux)) == EIntersections::E_One)
                {
                    if (vAux == quad.D || vAux == quad.A) // Both intersections are in the same edge
                        return EIntersections::E_One;

                    vIntersection2 = vAux;
                    return EIntersections::E_Two;
                }
                else
                    return EIntersections::E_One;
            }
            else if (SFloat::IsZero(LineSegment2D(quad.D, quad.A).MinDistance(this->A))) // this->A is in DA quad edge (but not a vertex)
            {
                vIntersection1 = this->A;

                 // ls intersects other edges
                EIntersections value2 = this->IntersectionPoint(LineSegment2D(quad.B, quad.C), vAux);
                if (value2 == EIntersections::E_One)
                {
                    if (vAux == quad.B || vAux == quad.C) // Both intersections are in the same edge
                        return EIntersections::E_One;

                    vIntersection2 = vAux;
                    return EIntersections::E_Two;
                }
                else if ((value2 = this->IntersectionPoint(LineSegment2D(quad.C, quad.D), vAux)) == EIntersections::E_One)
                {
                    if (vAux == quad.C || vAux == quad.D) // Both intersections are in the same edge
                        return EIntersections::E_One;

                    vIntersection2 = vAux;
                    return EIntersections::E_Two;
                }
                else if ((value2 = this->IntersectionPoint(LineSegment2D(quad.A, quad.B), vAux)) == EIntersections::E_One)
                {
                    if (vAux == quad.A || vAux == quad.B) // Both intersections are in the same edge
                        return EIntersections::E_One;

                    vIntersection2 = vAux;
                    return EIntersections::E_Two;
                }
                else
                    return EIntersections::E_One;
            }
            else // this->A is strictly inside quadrilateral: is not in a vertex or edge.
            {
                EIntersections value2 = this->IntersectionPoint(LineSegment2D(quad.A, quad.B), vAux);
                if (value2 == EIntersections::E_One)
                    vIntersection1 = vAux;
                else if ((value2 = this->IntersectionPoint(LineSegment2D(quad.B, quad.C), vAux)) == EIntersections::E_One)
                    vIntersection1 = vAux;
                else if ((value2 = this->IntersectionPoint(LineSegment2D(quad.C, quad.D), vAux)) == EIntersections::E_One)
                    vIntersection1 = vAux;
                else if ((value2 = this->IntersectionPoint(LineSegment2D(quad.D, quad.A), vAux)) == EIntersections::E_One)
                    vIntersection1 = vAux;

                return EIntersections::E_One;
            }
        }
        else // this->B is inside quadrilateral (A is outside)
        {
            if (this->B == quad.A) // this->B is quad.A vertex
            {
                // ls intersects opposite edges
                EIntersections value2 = this->IntersectionPoint(LineSegment2D(quad.B, quad.C), vAux);
                if (value2 == EIntersections::E_One)
                {
                    vIntersection1 = vAux;
                    vIntersection2 = this->B;
                    return EIntersections::E_Two;
                }
                else if ((value2 = this->IntersectionPoint(LineSegment2D(quad.C, quad.D), vAux)) == EIntersections::E_One)
                {
                    vIntersection1 = vAux;
                    vIntersection2 = this->B;
                    return EIntersections::E_Two;
                }
                else
                {
                    vIntersection1 = this->B;
                    return EIntersections::E_One;
                }
            }
            else if (this->B == quad.B) // this->B is quad.B vertex
            {
                // ls intersects opposite edges
                EIntersections value2 = this->IntersectionPoint(LineSegment2D(quad.C, quad.D), vAux);
                if (value2 == EIntersections::E_One)
                {
                    vIntersection1 = vAux;
                    vIntersection2 = this->B;
                    return EIntersections::E_Two;
                }
                else if ((value2 = this->IntersectionPoint(LineSegment2D(quad.D, quad.A), vAux)) == EIntersections::E_One)
                {
                    vIntersection1 = vAux;
                    vIntersection2 = this->B;
                    return EIntersections::E_Two;
                }
                else
                {
                    vIntersection1 = this->B;
                    return EIntersections::E_One;
                }
            }
            else if (this->B == quad.C) // this->B is quad.C vertex
            {
                // ls intersects opposite edges
                EIntersections value2 = this->IntersectionPoint(LineSegment2D(quad.D, quad.A), vAux);
                if (value2 == EIntersections::E_One)
                {
                    vIntersection1 = vAux;
                    vIntersection2 = this->B;
                    return EIntersections::E_Two;
                }
                else if ((value2 = this->IntersectionPoint(LineSegment2D(quad.A, quad.B), vAux)) == EIntersections::E_One)
                {
                    vIntersection1 = vAux;
                    vIntersection2 = this->B;
                    return EIntersections::E_Two;
                }
                else
                {
                    vIntersection1 = this->B;
                    return EIntersections::E_One;
                }
            }
            else if (this->B == quad.D) // this->B is quad.B vertex
            {
                // ls intersects opposite edges
                EIntersections value2 = this->IntersectionPoint(LineSegment2D(quad.A, quad.B), vAux);
                if (value2 == EIntersections::E_One)
                {
                    vIntersection1 = vAux;
                    vIntersection2 = this->B;
                    return EIntersections::E_Two;
                }
                else if ((value2 = this->IntersectionPoint(LineSegment2D(quad.B, quad.C), vAux)) == EIntersections::E_One)
                {
                    vIntersection1 = vAux;
                    vIntersection2 = this->B;
                    return EIntersections::E_Two;
                }
                else
                {
                    vIntersection1 = this->B;
                    return EIntersections::E_One;
                }
            }
            else if (SFloat::IsZero(LineSegment2D(quad.A, quad.B).MinDistance(this->B))) // this->B is in AB quad edge (but not a vertex)
            {
                // ls intersects the other edges
                EIntersections value2 = this->IntersectionPoint(LineSegment2D(quad.B, quad.C), vAux);
                if (value2 == EIntersections::E_One)
                {
                    vIntersection1 = vAux;

                    if (vAux == quad.B || vAux == quad.C) // Both intersections are in the same edge
                        return EIntersections::E_One;

                    vIntersection2 = this->B;
                    return EIntersections::E_Two;
                }
                else if ((value2 = this->IntersectionPoint(LineSegment2D(quad.C, quad.D), vAux)) == EIntersections::E_One)
                {
                    vIntersection1 = vAux;

                    if (vAux == quad.C || vAux == quad.D) // Both intersections are in the same edge
                        return EIntersections::E_One;

                    vIntersection2 = this->B;
                    return EIntersections::E_Two;
                }
                else if ((value2 = this->IntersectionPoint(LineSegment2D(quad.D, quad.A), vAux)) == EIntersections::E_One)
                {
                    vIntersection1 = vAux;

                    if (vAux == quad.D || vAux == quad.A) // Both intersections are in the same edge
                        return EIntersections::E_One;

                    vIntersection2 = this->B;
                    return EIntersections::E_Two;
                }
                else // There is no other intersection
                {
                    vIntersection1 = this->B;
                    return EIntersections::E_One;
                }
            }
            else if (SFloat::IsZero(LineSegment2D(quad.B, quad.C).MinDistance(this->B))) // this->B is in BC quad edge (but not a vertex)
            {
                // ls intersects the other edges
                EIntersections value2 = this->IntersectionPoint(LineSegment2D(quad.A, quad.B), vAux);
                if (value2 == EIntersections::E_One)
                {
                    vIntersection1 = vAux;

                    if (vAux == quad.A || vAux == quad.B) // Both intersections are in the same edge
                        return EIntersections::E_One;

                    vIntersection2 = this->B;
                    return EIntersections::E_Two;
                }
                else if ((value2 = this->IntersectionPoint(LineSegment2D(quad.C, quad.D), vAux)) == EIntersections::E_One)
                {
                    vIntersection1 = vAux;

                    if (vAux == quad.C || vAux == quad.D) // Both intersections are in the same edge
                        return EIntersections::E_One;

                    vIntersection2 = this->B;
                    return EIntersections::E_Two;
                }
                else if ((value2 = this->IntersectionPoint(LineSegment2D(quad.D, quad.A), vAux)) == EIntersections::E_One)
                {
                    vIntersection1 = vAux;

                    if (vAux == quad.D || vAux == quad.A) // Both intersections are in the same edge
                        return EIntersections::E_One;

                    vIntersection2 = this->B;
                    return EIntersections::E_Two;
                }
                else // There is no other intersection
                {
                    vIntersection1 = this->B;
                    return EIntersections::E_One;
                }
            }
            else if (SFloat::IsZero(LineSegment2D(quad.C, quad.D).MinDistance(this->B))) // this->B is in CD quad edge (but not a vertex)
            {
                // ls intersects the other edges
                EIntersections value2 = this->IntersectionPoint(LineSegment2D(quad.B, quad.C), vAux);
                if (value2 == EIntersections::E_One)
                {
                    vIntersection1 = vAux;

                    if (vAux == quad.B || vAux == quad.C) // Both intersections are in the same edge
                        return EIntersections::E_One;

                    vIntersection2 = this->B;
                    return EIntersections::E_Two;
                }
                else if ((value2 = this->IntersectionPoint(LineSegment2D(quad.A, quad.B), vAux)) == EIntersections::E_One)
                {
                    vIntersection1 = vAux;

                    if (vAux == quad.A || vAux == quad.B) // Both intersections are in the same edge
                        return EIntersections::E_One;

                    vIntersection2 = this->B;
                    return EIntersections::E_Two;
                }
                else if ((value2 = this->IntersectionPoint(LineSegment2D(quad.D, quad.A), vAux)) == EIntersections::E_One)
                {
                    vIntersection1 = vAux;

                    if (vAux == quad.D || vAux == quad.A) // Both intersections are in the same edge
                        return EIntersections::E_One;

                    vIntersection2 = this->B;
                    return EIntersections::E_Two;
                }
                else // There is no other intersection
                {
                    vIntersection1 = this->B;
                    return EIntersections::E_One;
                }
            }
            else if (SFloat::IsZero(LineSegment2D(quad.D, quad.A).MinDistance(this->B))) // this->B is in DA quad edge (but not a vertex)
            {
                // ls intersects the other edges
                EIntersections value2 = this->IntersectionPoint(LineSegment2D(quad.B, quad.C), vAux);
                if (value2 == EIntersections::E_One)
                {
                    vIntersection1 = vAux;

                    if (vAux == quad.B || vAux == quad.C) // Both intersections are in the same edge
                        return EIntersections::E_One;

                    vIntersection2 = this->B;
                    return EIntersections::E_Two;
                }
                else if ((value2 = this->IntersectionPoint(LineSegment2D(quad.C, quad.D), vAux)) == EIntersections::E_One)
                {
                    vIntersection1 = vAux;

                    if (vAux == quad.C || vAux == quad.D) // Both intersections are in the same edge
                        return EIntersections::E_One;

                    vIntersection2 = this->B;
                    return EIntersections::E_Two;
                }
                else if ((value2 = this->IntersectionPoint(LineSegment2D(quad.A, quad.B), vAux)) == EIntersections::E_One)
                {
                    vIntersection1 = vAux;

                    if (vAux == quad.A || vAux == quad.B) // Both intersections are in the same edge
                        return EIntersections::E_One;

                    vIntersection2 = this->B;
                    return EIntersections::E_Two;
                }
                else // There is no other intersection
                {
                    vIntersection1 = this->B;
                    return EIntersections::E_One;
                }
            }
            else // this->B is strictly inside quadrilateral: is not in a vertex or edge.
            {
                EIntersections value2 = this->IntersectionPoint(LineSegment2D(quad.A, quad.B), vAux);
                if (value2 == EIntersections::E_One)
                    vIntersection1 = vAux;
                else if ((value2 = this->IntersectionPoint(LineSegment2D(quad.B, quad.C), vAux)) == EIntersections::E_One)
                    vIntersection1 = vAux;
                else if ((value2 = this->IntersectionPoint(LineSegment2D(quad.C, quad.D), vAux)) == EIntersections::E_One)
                    vIntersection1 = vAux;
                else if ((value2 = this->IntersectionPoint(LineSegment2D(quad.D, quad.A), vAux)) == EIntersections::E_One)
                    vIntersection1 = vAux;

                return EIntersections::E_One;
            }
        }
    }

    // Something went wrong, this line should never be reached
    Z_ASSERT_WARNING(false, "Something really wrong is happening, this code branch should never be reached");

    return EIntersections::E_None;
}

EIntersections LineSegment2D::IntersectionPoint(const BaseQuadrilateral &quad, BaseVector2 &vIntersection) const
{
    BaseVector2 vAux;
    return this->IntersectionPoint(quad, vIntersection, vAux);
}

bool LineSegment2D::PointInsideTriangle(const BaseTriangle<Vector2>& triangle, const Vector2& vPoint) const
{
    return ( PointsInSameSideOfLine(vPoint, triangle.A, triangle.B, triangle.C) &&
                PointsInSameSideOfLine(vPoint, triangle.B, triangle.C, triangle.A) &&
                PointsInSameSideOfLine(vPoint, triangle.C, triangle.A, triangle.B) );
}

bool LineSegment2D::PointsInSameSideOfLine(const Vector2 &vP1, const Vector2 &vP2, const Vector2 &vLine1, const Vector2 &vLine2) const
{
    const float_z &ORIENTATION1 = (vLine1.x - vP1.x)*(vLine2.y - vP1.y) - (vLine1.y - vP1.y)*(vLine2.x - vP1.x);
    const float_z &ORIENTATION2 = (vLine1.x - vP2.x)*(vLine2.y - vP2.y) - (vLine1.y - vP2.y)*(vLine2.x - vP2.x);

    if ( SFloat::IsZero(ORIENTATION1) || SFloat::IsZero(ORIENTATION2) )
        return true;
    else if ( SFloat::IsNegative(ORIENTATION1) == SFloat::IsNegative(ORIENTATION2) )
        return true;
    else
        return false;
}

bool LineSegment2D::PointInsideQuadrilateral(const BaseQuadrilateral& quad, const Vector2& vPoint) const
{
    return ( PointsInSameSideOfLine(vPoint, quad.C, quad.A, quad.B) &&
                PointsInSameSideOfLine(vPoint, quad.A, quad.B, quad.C) &&
                PointsInSameSideOfLine(vPoint, quad.A, quad.C, quad.D) &&
                PointsInSameSideOfLine(vPoint, quad.C, quad.D, quad.A) );
}

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |         PROPERTIES         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

const LineSegment2D& LineSegment2D::GetUnitLine()
{
    static const LineSegment2D UNITLINE(Vector2::GetNullVector(), Vector2::GetUnitVectorX());
    return UNITLINE;
}

const LineSegment2D& LineSegment2D::GetLineZero()
{
    static const LineSegment2D LINEZERO(Vector2::GetNullVector(), Vector2::GetNullVector());
    return LINEZERO;
}


} // namespace z
