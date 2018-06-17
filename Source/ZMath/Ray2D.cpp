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

#include "ZMath/Ray2D.h"

#include "ZMath/Triangle.h"
#include "ZMath/TransformationMatrix3x3.h"
#include "ZMath/SVectorArray.h"



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

Ray2D::Ray2D()
{
}

Ray2D::Ray2D(const Ray2D &ray) : Ray<Vector2, Vector2>(ray)
{
}

Ray2D::Ray2D(const Ray<Vector2, Vector2> &ray) : Ray<Vector2, Vector2>(ray)
{
}

Ray2D::Ray2D(const Vector2 &vOrigin, const Vector2 &vDirection) : Ray<Vector2, Vector2>(vOrigin, vDirection)
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

Ray2D& Ray2D::operator=(const Ray<Vector2, Vector2> &ray)
{
    Ray<Vector2, Vector2>::operator=(ray);
    return *this;
}
/*
bool Ray2D::Intersection(const Triangle<Vector2> &triangle) const
{
    // Vertices of the triangle must not coincide
    Z_ASSERT_WARNING( triangle.A != triangle.B && 
               triangle.B != triangle.C &&
               triangle.C != triangle.A, "Vertices of the triangle must not coincide" );

    // The direction vector of the ray shouldn't be null
    Z_ASSERT_WARNING( !this->Direction.IsZero(), "The direction vector of the ray shouldn't be null" );

    return ( this->Intersection(BaseLineSegment<Vector2>(triangle.A, triangle.B)) ||
             this->Intersection(BaseLineSegment<Vector2>(triangle.B, triangle.C)) ||
             this->Intersection(BaseLineSegment<Vector2>(triangle.C, triangle.A)) );
}

bool Ray2D::Intersection(const BaseQuadrilateral &quad) const
{
    return ( this->Intersection(BaseLineSegment<Vector2>(quad.A, quad.B)) || this->Intersection(BaseLineSegment<Vector2>(quad.B, quad.C)) ||
             this->Intersection(BaseLineSegment<Vector2>(quad.C, quad.D)) || this->Intersection(BaseLineSegment<Vector2>(quad.D, quad.A)));
}
*/
/*
EIntersections Ray2D::IntersectionPoint(const Triangle<Vector2> &triangle, Vector2 &vIntersection) const
{
    Vector2 vAux;
    return this->IntersectionPoint(triangle, vIntersection, vAux);
}

EIntersections Ray2D::IntersectionPoint(const Triangle<Vector2> &triangle, Vector2 &vIntersection1, Vector2 &vIntersection2) const
{
    // Vertices of the triangle must not coincide
    Z_ASSERT_WARNING( triangle.A != triangle.B && 
               triangle.B != triangle.C &&
               triangle.C != triangle.A, "Vertices of the triangle must not coincide" );

    // The direction vector of the ray shouldn't be null
    Z_ASSERT_WARNING( !this->Direction.IsZero(), "The direction vector of the ray shouldn't be null" );

    Vector2 vAux;

    if ( PointInsideTriangle(triangle, this->Origin) ) // Ray end point is inside triangle
    {
        if (this->Origin == triangle.A) // Ray end point is A triangle vertex
        {
            vIntersection1 = this->Origin;

            // Checks intersection with opposite edge (it should not return E_Infinite, is the opposite edge)
            if (this->IntersectionPoint(BaseLineSegment<Vector2>(triangle.B, triangle.C), vAux) == EIntersections::E_None) // No intersection found
                return EIntersections::E_One;
            else // Intersection found
            {
                vIntersection2 = vAux;
                return EIntersections::E_Two;
            }
        }
        else if (this->Origin == triangle.B) // Ray end point is B triangle vertex
        {
            vIntersection1 = this->Origin;

           // Checks intersection with opposite edge
            if (this->IntersectionPoint(BaseLineSegment<Vector2>(triangle.C, triangle.A), vAux) == EIntersections::E_None) // No intersection found
                return EIntersections::E_One;
            else // Intersection found
            {
                vIntersection2 = vAux;
                return EIntersections::E_Two;
            }
        }
        else if (this->Origin == triangle.C) // Ray end point is C triangle vertex
        {
            vIntersection1 = this->Origin;

            // Checks intersection with opposite edge
            if (this->IntersectionPoint(BaseLineSegment<Vector2>(triangle.A, triangle.B), vAux) == EIntersections::E_None) // No intersection found
                return EIntersections::E_One;
            else // Intersection found
            {
                vIntersection2 = vAux;
                return EIntersections::E_Two;
            }
        }
        else if (SFloat::IsZero(LineSegment2D(triangle.A, triangle.B).MinDistance(this->Origin))) // Ray end point is in AB triangle edge
        {
            vIntersection1 = this->Origin;

            if (this->IntersectionPoint(BaseLineSegment<Vector2>(triangle.B, triangle.C), vAux) == EIntersections::E_One ||
                this->IntersectionPoint(BaseLineSegment<Vector2>(triangle.C, triangle.A), vAux) == EIntersections::E_One) // Ray intersects edge BC or CA
            {
                vIntersection2 = vAux;
                return EIntersections::E_Two;
            }
            else // Ray doesn't intersect with other edge
            {
                return EIntersections::E_One;
            }
        }
        else if (SFloat::IsZero(LineSegment2D(triangle.B, triangle.C).MinDistance(this->Origin))) // Ray end point is in BC triangle edge
        {
            vIntersection1 = this->Origin;

            if (this->IntersectionPoint(BaseLineSegment<Vector2>(triangle.C, triangle.A), vAux) == EIntersections::E_One ||
                this->IntersectionPoint(BaseLineSegment<Vector2>(triangle.A, triangle.B), vAux) == EIntersections::E_One) // Ray intersects edge AB or CA
            {
                vIntersection2 = vAux;
                return EIntersections::E_Two;
            }
            else // Ray doesn't intersect with other edge
            {
                return EIntersections::E_One;
            }
        }
        else if (SFloat::IsZero(LineSegment2D(triangle.C, triangle.A).MinDistance(this->Origin))) // Ray end point is in CA triangle edge
        {
            vIntersection1 = this->Origin;

            if (this->IntersectionPoint(BaseLineSegment<Vector2>(triangle.B, triangle.C), vAux) == EIntersections::E_One ||
                this->IntersectionPoint(BaseLineSegment<Vector2>(triangle.A, triangle.B), vAux) == EIntersections::E_One) // Ray intersects edge AB or BC
            {
                vIntersection2 = vAux;
                return EIntersections::E_Two;
            }
            else // Ray doesn't intersect with other edge
            {
                return EIntersections::E_One;
            }
        }
        else // Ray end point is strictly inside triangle (is not in a vertex or an edge
        {
            if (this->IntersectionPoint(BaseLineSegment<Vector2>(triangle.A, triangle.B), vAux) == EIntersections::E_One)
                vIntersection1 = vAux;
            else if (this->IntersectionPoint(BaseLineSegment<Vector2>(triangle.B, triangle.C), vAux) == EIntersections::E_One)
                vIntersection1 = vAux;
            else if (this->IntersectionPoint(BaseLineSegment<Vector2>(triangle.C, triangle.A), vAux) == EIntersections::E_One)
                vIntersection1 = vAux;
            else
                Z_ASSERT_WARNING(false, "Something went very wrong, this code branch must never be reached");  // Something is wrong, if ray point is interior, it must be ONE intersection with a edge.

            return EIntersections::E_One;
        }
    }
    else // Ray end point is outside triangle
    {
        Vector2 vPrevInt;
        bool bPrevInt = false;

        Vector2 vAuxAB;
        EIntersections numIntAB = this->IntersectionPoint(BaseLineSegment<Vector2>(triangle.A, triangle.B), vAuxAB); // Checks intersection with AB edge
        if (numIntAB == EIntersections::E_Infinite) // Ray contains AB edge
        {
            // Looks for closest point to ray end point
            if  ( (triangle.A - this->Origin).GetSquaredLength() < (triangle.B - this->Origin).GetSquaredLength() )
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

        Vector2 vAuxBC;
        EIntersections numIntBC = this->IntersectionPoint(BaseLineSegment<Vector2>(triangle.B, triangle.C), vAuxBC); // Checks intersection with BC edge
        if (numIntBC == EIntersections::E_Infinite) // Ray contains BC edge
        {
            // Looks for closest point to ray end point
            if  ( (triangle.B - this->Origin).GetSquaredLength() < (triangle.C - this->Origin).GetSquaredLength() )
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

        Vector2 vAuxCA;
        EIntersections numIntCA = this->IntersectionPoint(BaseLineSegment<Vector2>(triangle.C, triangle.A), vAuxCA); // Checks intersection with BC edge
        if (numIntCA == EIntersections::E_Infinite) // Ray contains CA edge
        {
            // Looks for closest point to ray end point
            if  ( (triangle.C - this->Origin).GetSquaredLength() < (triangle.A - this->Origin).GetSquaredLength() )
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

        if (numIntAB == EIntersections::E_One) // Ray has ONE intersection with AB edge
        {
            bPrevInt = true;
            vPrevInt = vAuxAB;
        }

        if (numIntBC == EIntersections::E_One) // Ray has ONE intersection with BC edge
        {
            if (bPrevInt) // There is a previous intersection with an edge
            {
                if (vAuxBC != vPrevInt)
                {
                    // Looks for closest point to ray end point
                    if  ( (vAuxBC - this->Origin).GetSquaredLength() < (vPrevInt - this->Origin).GetSquaredLength() )
                    {
                        vIntersection1 = vAuxBC;
                        vIntersection2 = vPrevInt;
                    }
                    else
                    {
                        vIntersection1 = vPrevInt;
                        vIntersection2 = vAuxBC;
                    }
                    return EIntersections::E_Two;
                }
            }
            else // Its the first intersection found
            {
                bPrevInt = true;
                vPrevInt = vAuxBC;
            }
        }

        if (numIntCA == EIntersections::E_One)
        {
            if (bPrevInt) // There is a previous intersection with an edge
            {
                if (vAuxCA != vPrevInt)
                {
                    // Looks for closest point to ray end point
                    if  ( (vAuxCA - this->Origin).GetSquaredLength() < (vPrevInt - this->Origin).GetSquaredLength() )
                    {
                        vIntersection1 = vAuxCA;
                        vIntersection2 = vPrevInt;
                    }
                    else
                    {
                        vIntersection1 = vPrevInt;
                        vIntersection2 = vAuxCA;
                    }
                    return EIntersections::E_Two;
                }
            }
            else
                Z_ASSERT_WARNING(false, "Something went very wrong, this code branch must never be reached");  // Something is wrong, there is ONE intersection and is not a vertex
        }

        if (bPrevInt)
        {
            vIntersection1 = vPrevInt;
            return EIntersections::E_One;
        }
        else
            return EIntersections::E_None;
    }
}
*/
/*
void Ray2D::Reflection(const BaseLineSegment<Vector2> &segment, Ray<Vector2, Vector2> &ray) const
{
    // The direction vector of the ray must not be null
    Z_ASSERT_WARNING( !this->Direction.IsZero(), "The direction vector of the ray must not be null" );

    // The endpoints of the line segment shouldn't coincide
    Z_ASSERT_WARNING( segment.A != segment.B, "The endpoints of the line segment must not coincide" );

    // Method based in this: http://www.inmensia.com/articulos/raytracing/mecanismosluz.html

    Vector2 vAtoB = Vector2(segment.B - segment.A).Normalize();

    ray = *this;

    // Avoiding cases where ray and line segment are parallels or coincident.
    if (vAtoB != this->Direction && vAtoB != -this->Direction)
    {
        Vector2 vPoint;
        EIntersections numInt = this->IntersectionPoint(segment, vPoint);
        if (numInt == EIntersections::E_One)
        {
            // If the origin coincides with the intersection point, the ray is not reflexted
            if(ray.Origin != vPoint)
            {
                // Reflected origin is the intersection point
                ray.Origin = vPoint;

                // Calculates normal to line segment (is normalized like vAux)
                Vector2 vNorm = vAtoB.GetPerpendicular();

                // Calculates reflected direction
                ray.Direction -= SFloat::_2 * (this->Direction.DotProduct(vNorm)) * vNorm;
            }
        }
    }
}

void Ray2D::Reflection(const BaseLineSegment<Vector2> &segment, Vector2 &vDirection) const
{
    // The direction vector of the ray must not be null
    Z_ASSERT_WARNING( !this->Direction.IsZero(), "The direction vector of the ray must not be null" );

    // The endpoints of the line segment shouldn't coincide
    Z_ASSERT_WARNING( segment.A != segment.B, "The endpoints of the line segment must not coincide" );

    // Method based in this: http://www.inmensia.com/articulos/raytracing/mecanismosluz.html

    Vector2 vAtoB = Vector2(segment.B - segment.A).Normalize();

    vDirection = this->Direction;

    if (vAtoB != this->Direction && vAtoB != -this->Direction && // Avoiding cases where ray and line segment are parallels or coincident.
        segment.A != this->Origin && segment.B != this->Origin && // No reflection if the origin belongs to the line
        this->Intersection(segment))
    {
        // If the origin of the ray does not belong to the line
        const Vector2& vAtoOrigin = (this->Origin - segment.A).Normalize();
        const bool& bOriginBelongsToLine = SFloat::AreEqual(vAtoB.DotProduct(vAtoOrigin), SFloat::_1);

        if(!bOriginBelongsToLine)
        {
            // Calculates normal to line segment (is normalized like vAtoB)
            Vector2 vNorm = vAtoB.GetPerpendicular();

            // Calculates reflected direction
            vDirection = this->Direction - SFloat::_2 * (this->Direction.DotProduct(vNorm)) * vNorm;
        }
    }
}
*/
Ray2D Ray2D::Transform(const z::TransformationMatrix3x3 &transformation) const
{
    Ray2D auxRay = *this;
    auxRay.Origin = auxRay.Origin.Transform(transformation);

    // Direction is transformed without translation. The calculation takes into account only the submatrix that contains
    // the rotation and the scale.
    const float_z NEW_X = this->Direction.x * transformation.ij[0][0] + this->Direction.y * transformation.ij[1][0];
    const float_z NEW_Y = this->Direction.x * transformation.ij[0][1] + this->Direction.y * transformation.ij[1][1];

    auxRay.Direction = Vector2(NEW_X, NEW_Y).Normalize();

    return auxRay;
}

Ray2D Ray2D::Rotate(const float_z fRotationAngle) const
{
    Ray2D auxRay = *this;
    SVectorArray::Rotate(fRotationAngle, rcast_z(&auxRay, Vector2*), 2);
    return auxRay;
}

Ray2D Ray2D::RotateWithPivot(const float_z fRotationAngle, const Vector2 &vPivot) const
{
    Ray2D auxRay = *this;
    SVectorArray::RotateWithPivot(fRotationAngle, vPivot, &auxRay.Origin, 1);
    SVectorArray::Rotate(fRotationAngle, &auxRay.Direction, 1);
    return auxRay;
}

Ray2D Ray2D::Translate(const Vector2 &vTranslation) const
{
    Ray2D auxRay = *this;
    SVectorArray::Translate(vTranslation, &auxRay.Origin, 1);
    return auxRay;
}

Ray2D Ray2D::Translate(const float_z fTranslationX, const float_z fTranslationY) const
{
    Ray2D auxRay = *this;
    SVectorArray::Translate(fTranslationX, fTranslationY, &auxRay.Origin, 1);
    return auxRay;
}

Ray2D Ray2D::Scale(const Vector2 &vScale) const
{
    Ray2D auxRay = *this;
    SVectorArray::Scale(vScale, rcast_z(&auxRay, Vector2*), 2);
    return Ray2D(auxRay.Origin, auxRay.Direction.Normalize());
}

Ray2D Ray2D::Scale(const float_z vScaleX, const float_z vScaleY) const
{
    Ray2D auxRay = *this;
    SVectorArray::Scale(vScaleX, vScaleY, rcast_z(&auxRay, Vector2*), 2);
    return Ray2D(auxRay.Origin, auxRay.Direction.Normalize());
}

Ray2D Ray2D::ScaleWithPivot(const Vector2 &vScale, const Vector2 &vPivot) const
{
    Ray2D auxRay = *this;
    SVectorArray::ScaleWithPivot(vScale, vPivot, &auxRay.Origin, 1);
    SVectorArray::Scale(vScale, &auxRay.Direction, 1);
    return Ray2D(auxRay.Origin, auxRay.Direction.Normalize());
}

Ray2D Ray2D::ScaleWithPivot(const float_z vScaleX, const float_z vScaleY, const Vector2 &vPivot) const
{
    Ray2D auxRay = *this;
    SVectorArray::ScaleWithPivot(vScaleX, vScaleY, vPivot, &auxRay.Origin, 1);
    SVectorArray::Scale(vScaleX, vScaleY, &auxRay.Direction, 1);
    return Ray2D(auxRay.Origin, auxRay.Direction.Normalize());
}

Ray2D Ray2D::TransformWithPivot(const z::TransformationMatrix3x3 &transformation, const Vector2 &vPivot) const
{
    Ray2D auxRay = *this;
    SVectorArray::TransformWithPivot(transformation, vPivot, &auxRay.Origin, 1);

    const float_z NEW_X = this->Direction.x * transformation.ij[0][0] + this->Direction.y * transformation.ij[1][0];
    const float_z NEW_Y = this->Direction.x * transformation.ij[0][1] + this->Direction.y * transformation.ij[1][1];

    auxRay.Direction = Vector2(NEW_X, NEW_Y).Normalize();

    return auxRay;
}

bool Ray2D::Contains(const Vector2 &vPoint) const
{
    if (this->Origin == vPoint)
        return true;
    else if ( SFloat::IsZero(this->Direction.x) )
    {
        if ( SFloat::AreNotEqual(vPoint.x, this->Origin.x) )
            return false;
        if ( SFloat::IsNegative(vPoint.y - this->Origin.y) == SFloat::IsNegative(this->Direction.y) )
            return true;
        else
            return false;
    }
    else if ( SFloat::IsZero(this->Direction.y) )
    {
        if ( SFloat::AreNotEqual(vPoint.y, this->Origin.y) )
            return false;
        if ( SFloat::IsNegative(vPoint.x - this->Origin.x) == SFloat::IsNegative(this->Direction.x) )
            return true;
        else
            return false;
    }
    else
    {
        const float_z &PARAM_X = (vPoint.x - this->Origin.x)/this->Direction.x;
        const float_z &PARAM_Y = (vPoint.y - this->Origin.y)/this->Direction.y;

        if ( SFloat::AreNotEqual(PARAM_X, PARAM_Y) || SFloat::IsNegative(PARAM_X))
            return false;
        else
            return true;
    }

}

bool Ray2D::PointInsideTriangle(const Triangle<Vector2>& triangle, const Vector2& vPoint) const
{
    return ( PointsInSameSideOfLine(vPoint, triangle.A, triangle.B, triangle.C) &&
                PointsInSameSideOfLine(vPoint, triangle.B, triangle.C, triangle.A) &&
                PointsInSameSideOfLine(vPoint, triangle.C, triangle.A, triangle.B) );
}

bool Ray2D::PointsInSameSideOfLine(const Vector2 &vP1, const Vector2 &vP2, const Vector2 &vLine1, const Vector2 &vLine2) const
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


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |         PROPERTIES         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

const Ray2D& Ray2D::GetNullRay()
{
    static const Ray2D NULLRAY(Vector2::GetNullVector(), Vector2::GetNullVector());
    return NULLRAY;
}

const Ray2D& Ray2D::GetRayX()
{
    static const Ray2D RAYX(Vector2::GetNullVector(), Vector2::GetUnitVectorX());
    return RAYX;
}

const Ray2D& Ray2D::GetRayY()
{
    static const Ray2D RAYY(Vector2::GetNullVector(), Vector2::GetUnitVectorY());
    return RAYY;
}


} // namespace Internals
} // namespace z
