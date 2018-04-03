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

#include "ZMath/LineSegment2D.h"
#include "ZMath/BaseTriangle.h"
#include "ZMath/BaseQuadrilateral.h"
#include "ZMath/TransformationMatrix3x3.h"
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

Ray2D::Ray2D()
{
}

Ray2D::Ray2D(const Ray2D &ray) : Ray<Vector2, Vector2>(ray)
{
}

Ray2D::Ray2D(const BaseRay<Vector2, Vector2> &ray) : Ray<Vector2, Vector2>(ray)
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

Ray2D& Ray2D::operator=(const BaseRay<Vector2, Vector2> &ray)
{
    BaseRay<Vector2, Vector2>::operator=(ray);
    return *this;
}

bool Ray2D::Intersection(const Ray2D &ray) const
{
    // Direction vector of rays should not be null
    Z_ASSERT_WARNING( !ray.Direction.IsZero() && !this->Direction.IsZero(), "Direction vector of rays should not be null" );

    const float_z &DENOMINATOR = this->Direction.x * ray.Direction.y - this->Direction.y * ray.Direction.x;

    if ( SFloat::IsZero(DENOMINATOR) ) // Both directions are parallels
    {
        if ( this->Contains(ray.Origin) )
            return true;
        else
            return ray.Contains(this->Origin);
    }
    else // rays are not parallel
    {
        const float_z &NUMERATOR1 = this->Direction.x * (this->Origin.y - ray.Origin.y) + this->Direction.y * (ray.Origin.x - this->Origin.x);
        if ((SFloat::IsNegative(DENOMINATOR) == SFloat::IsNegative(NUMERATOR1)) || SFloat::IsZero(NUMERATOR1))
        {
            const float_z &NUMERATOR2 = ray.Direction.x * (this->Origin.y - ray.Origin.y) + ray.Direction.y * (ray.Origin.x - this->Origin.x);

            return (SFloat::IsNegative(DENOMINATOR) == SFloat::IsNegative(NUMERATOR2)) || SFloat::IsZero(NUMERATOR2);
        }
        else
            return false;
    }
}

bool Ray2D::Intersection(const BaseTriangle<Vector2> &triangle) const
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

EIntersections Ray2D::IntersectionPoint(const Ray2D &ray, BaseVector2 &vIntersection) const
{
    // Direction vector of rays should not be null
    Z_ASSERT_WARNING( !ray.Direction.IsZero() && !this->Direction.IsZero(), "Direction vector of rays should not be null" );

    const float_z &DENOMINATOR = this->Direction.x * ray.Direction.y - this->Direction.y * ray.Direction.x;

    if ( SFloat::IsZero(DENOMINATOR) ) // Both directions are parallels
    {
        if (this->Origin == ray.Origin)
        {
            if ( (this->Direction + ray.Direction) == Vector2::GetNullVector() ) // Directions are opposite (are supossed normalized)
            {
                vIntersection = this->Origin;
                return EIntersections::E_One;
            }
            else
                return EIntersections::E_Infinite; //Both rays are the same
        }
        else if(this->Contains(ray.Origin))
        {
            if(ray.Contains(this->Origin))
            {
                vIntersection = this->Origin;
                return EIntersections::E_Two;
            }
            else
            {
                vIntersection = ray.Origin;
                return EIntersections::E_One;
            }
        }
        else if(ray.Contains(this->Origin))
        {
            vIntersection = this->Origin;
            return EIntersections::E_One;
        }
        else
            return EIntersections::E_None;
    }
    else
    {
        const float_z &NUMERATOR1 = this->Direction.x * (this->Origin.y - ray.Origin.y) +
                                    this->Direction.y * (ray.Origin.x - this->Origin.x);

        // Forces first parameter to be greater o equal to 0
        if ((SFloat::IsNegative(DENOMINATOR) == SFloat::IsNegative(NUMERATOR1)) || SFloat::IsZero(NUMERATOR1))
        {
            const float_z &NUMERATOR2 = ray.Direction.x * (this->Origin.y - ray.Origin.y) + ray.Direction.y * (ray.Origin.x - this->Origin.x);

            // Forces second parameter to be greater o equal to 0
            if ( (SFloat::IsNegative(DENOMINATOR) == SFloat::IsNegative(NUMERATOR2)) || SFloat::IsZero(NUMERATOR2) )
            {
                vIntersection = this->Origin + (NUMERATOR2/DENOMINATOR) * this->Direction;
                return EIntersections::E_One;
            }
            else
                return EIntersections::E_None;
        }
        else
            return EIntersections::E_None;
    }
}

EIntersections Ray2D::IntersectionPoint(const BaseTriangle<Vector2> &triangle, BaseVector2 &vIntersection) const
{
    BaseVector2 vAux;
    return this->IntersectionPoint(triangle, vIntersection, vAux);
}

EIntersections Ray2D::IntersectionPoint(const BaseTriangle<Vector2> &triangle, BaseVector2 &vIntersection1, BaseVector2 &vIntersection2) const
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

EIntersections Ray2D::IntersectionPoint(const BaseQuadrilateral &quad, BaseVector2 &vIntersection) const
{
    BaseVector2 vAux;
    return this->IntersectionPoint(quad, vIntersection, vAux);
}

EIntersections Ray2D::IntersectionPoint(const BaseQuadrilateral &quad, BaseVector2 &vIntersection1, BaseVector2 &vIntersection2) const
{
    Vector2 vAux;

    if ( PointInsideQuadrilateral(quad, this->Origin) ) // Ray end point is inside quadrilateral
    {
        if (this->Origin == quad.A) // Ray end point is A quadrilateral vertex
        {
            vIntersection1 = this->Origin;

            // Checks intersection with opposite edges
            if (this->IntersectionPoint(BaseLineSegment<Vector2>(quad.B, quad.C), vAux) == EIntersections::E_One) // Intersection found
            {
                vIntersection2 = vAux;
                return EIntersections::E_Two;
            }
            else if (this->IntersectionPoint(BaseLineSegment<Vector2>(quad.C, quad.D), vAux) == EIntersections::E_One) // Intersection found
            {
                vIntersection2 = vAux;
                return EIntersections::E_Two;
            }
            else // No intersection found
                return EIntersections::E_One;
        }
        else if (this->Origin == quad.B) // Ray end point is B quadrilateral vertex
        {
            vIntersection1 = this->Origin;

           // Checks intersection with opposite edges
            if (this->IntersectionPoint(BaseLineSegment<Vector2>(quad.C, quad.D), vAux) == EIntersections::E_One) // Intersection found
            {
                vIntersection2 = vAux;
                return EIntersections::E_Two;
            }
            else if (this->IntersectionPoint(BaseLineSegment<Vector2>(quad.D, quad.A), vAux) == EIntersections::E_One) // Intersection found
            {
                vIntersection2 = vAux;
                return EIntersections::E_Two;
            }
            else // No intersection found
                return EIntersections::E_One;
        }
        else if (this->Origin == quad.C) // Ray end point is C quadrilateral vertex
        {
            vIntersection1 = this->Origin;

            // Checks intersection with opposite edges
            if (this->IntersectionPoint(BaseLineSegment<Vector2>(quad.D, quad.A), vAux) == EIntersections::E_One) // Intersection found
            {
                vIntersection2 = vAux;
                return EIntersections::E_Two;
            }
            else if (this->IntersectionPoint(BaseLineSegment<Vector2>(quad.A, quad.B), vAux) == EIntersections::E_One) // Intersection found
            {
                vIntersection2 = vAux;
                return EIntersections::E_Two;
            }
            else // No intersection found
                return EIntersections::E_One;
        }
        else if (this->Origin == quad.D) // Ray end point is D quadrilateral vertex
        {
            vIntersection1 = this->Origin;

            // Checks intersection with opposite edges
            if (this->IntersectionPoint(BaseLineSegment<Vector2>(quad.A, quad.B), vAux) == EIntersections::E_One) // Intersection found
            {
                vIntersection2 = vAux;
                return EIntersections::E_Two;
            }
            else if (this->IntersectionPoint(BaseLineSegment<Vector2>(quad.B, quad.C), vAux) == EIntersections::E_One) // Intersection found
            {
                vIntersection2 = vAux;
                return EIntersections::E_Two;
            }
            else // No intersection found
                return EIntersections::E_One;
        }
        else if (SFloat::IsZero(LineSegment2D(quad.A, quad.B).MinDistance(this->Origin))) // Ray end point is in AB quadrilateral edge
        {
            if (this->IntersectionPoint(BaseLineSegment<Vector2>(quad.B, quad.C), vAux) == EIntersections::E_One) // Ray intersects other edge
            {
                // Origin belongs to AB edge and ray cuts BC
                vIntersection1 = this->Origin;
                vIntersection2 = vAux;
                return EIntersections::E_Two;
            }
            else if (this->IntersectionPoint(BaseLineSegment<Vector2>(quad.C, quad.D), vAux) == EIntersections::E_One) // Ray intersects other edge
            {
                // Origin belongs to AB edge and ray cuts to CD
                vIntersection1 = this->Origin;
                vIntersection2 = vAux;
                return EIntersections::E_Two;
            }
            else if (this->IntersectionPoint(BaseLineSegment<Vector2>(quad.D, quad.A), vAux) == EIntersections::E_One) // Ray intersects other edge
            {
                // Origin belongs to AB edge and ray cuts to DA
                vIntersection1 = this->Origin;
                vIntersection2 = vAux;
                return EIntersections::E_Two;
            }
            else // Ray don't intersects other edge
            {
                vIntersection1 = this->Origin;
                return EIntersections::E_One;
            }
        }
        else if (SFloat::IsZero(LineSegment2D(quad.B, quad.C).MinDistance(this->Origin))) // Ray end point is in BC quadrilateral edge
        {
            if (this->IntersectionPoint(BaseLineSegment<Vector2>(quad.C, quad.D), vAux) == EIntersections::E_One) // Ray intersects other edge
            {
                // Origin belongs to BC edge and ray cuts to CD
                vIntersection1 = this->Origin;
                vIntersection2 = vAux;
                return EIntersections::E_Two;
            }
            else if (this->IntersectionPoint(BaseLineSegment<Vector2>(quad.D, quad.A), vAux) == EIntersections::E_One) // Ray intersects other edge
            {
                // Origin belongs to BC edge and ray cuts to DA
                vIntersection1 = this->Origin;
                vIntersection2 = vAux;
                return EIntersections::E_Two;
            }
            if (this->IntersectionPoint(BaseLineSegment<Vector2>(quad.A, quad.B), vAux) == EIntersections::E_One) // Ray intersects other edge
            {
                // Origin belongs to BC edge and ray cuts to AB
                vIntersection1 = this->Origin;
                vIntersection2 = vAux;
                return EIntersections::E_Two;
            }
            else // Ray don't intersects other edge
            {
                vIntersection1 = this->Origin;
                return EIntersections::E_One;
            }
        }
        else if (SFloat::IsZero(LineSegment2D(quad.C, quad.D).MinDistance(this->Origin))) // Ray end point is in CD quadrilateral edge
        {
            if (this->IntersectionPoint(BaseLineSegment<Vector2>(quad.D, quad.A), vAux) == EIntersections::E_One) // Ray intersects other edge
            {
                // Origin belongs to CD edge and ray cuts to DA
                vIntersection1 = this->Origin;
                vIntersection2 = vAux;
                return EIntersections::E_Two;
            }
            else if (this->IntersectionPoint(BaseLineSegment<Vector2>(quad.A, quad.B), vAux) == EIntersections::E_One) // Ray intersects other edge
            {
                // Origin belongs to CD edge and ray cuts to AB
                vIntersection1 = this->Origin;
                vIntersection2 = vAux;
                return EIntersections::E_Two;
            }
            if (this->IntersectionPoint(BaseLineSegment<Vector2>(quad.B, quad.C), vAux) == EIntersections::E_One) // Ray intersects other edge
            {
                // Origin belongs to CD edge and ray cuts to BC
                vIntersection1 = this->Origin;
                vIntersection2 = vAux;
                return EIntersections::E_Two;
            }
            else // Ray don't intersects other edge
            {
                vIntersection1 = this->Origin;
                return EIntersections::E_One;
            }
        }
        else if (SFloat::IsZero(LineSegment2D(quad.D, quad.A).MinDistance(this->Origin))) // Ray end point is in DA quadrilateral edge
        {
            if (this->IntersectionPoint(BaseLineSegment<Vector2>(quad.A, quad.B), vAux) == EIntersections::E_One) // Ray intersects other edge
            {
                // Origin belongs to DA edge and ray cuts to AB
                vIntersection1 = this->Origin;
                vIntersection2 = vAux;
                return EIntersections::E_Two;
            }
            else if (this->IntersectionPoint(BaseLineSegment<Vector2>(quad.B, quad.C), vAux) == EIntersections::E_One) // Ray intersects other edge
            {
                // Origin belongs to DA edge and ray cuts to BC
                vIntersection1 = this->Origin;
                vIntersection2 = vAux;
                return EIntersections::E_Two;
            }
            if (this->IntersectionPoint(BaseLineSegment<Vector2>(quad.C, quad.D), vAux) == EIntersections::E_One) // Ray intersects other edge
            {
                // Origin belongs to DA edge and ray cuts to CD
                vIntersection1 = this->Origin;
                vIntersection2 = vAux;
                return EIntersections::E_Two;
            }
            else // Ray don't intersects other edge
            {
                vIntersection1 = this->Origin;
                return EIntersections::E_One;
            }
        }
        else // Ray end point is strictly inside quadrilateral (is not in a vertex or an edge)
        {
            if (this->IntersectionPoint(BaseLineSegment<Vector2>(quad.A, quad.B), vAux) == EIntersections::E_One)
                vIntersection1 = vAux;
            else if (this->IntersectionPoint(BaseLineSegment<Vector2>(quad.B, quad.C), vAux) == EIntersections::E_One)
                vIntersection1 = vAux;
            else if (this->IntersectionPoint(BaseLineSegment<Vector2>(quad.C, quad.D), vAux) == EIntersections::E_One)
                vIntersection1 = vAux;
            else if (this->IntersectionPoint(BaseLineSegment<Vector2>(quad.D, quad.A), vAux) == EIntersections::E_One)
                vIntersection1 = vAux;
            else
                Z_ASSERT_WARNING(false, "Something went very wrong, this code branch must never be reached");  // Something is wrong, if ray point is interior, it must be ONE intersection with a edge.

            return EIntersections::E_One;
        }
    }
    else // Ray end point is outside quadrilateral
    {
        Vector2 vPrevInt;
        bool bPrevInt = false;

        Vector2 vAuxAB;
        EIntersections numIntAB = this->IntersectionPoint(BaseLineSegment<Vector2>(quad.A, quad.B), vAuxAB); // Checks intersection with AB edge
        if (numIntAB == EIntersections::E_Infinite) // Ray contains AB edge
        {
            // Looks for closest point to ray end point
            if  ( (quad.A - this->Origin).GetSquaredLength() < (quad.B - this->Origin).GetSquaredLength() )
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

        Vector2 vAuxBC;
        EIntersections numIntBC = this->IntersectionPoint(BaseLineSegment<Vector2>(quad.B, quad.C), vAuxBC); // Checks intersection with BC edge
        if (numIntBC == EIntersections::E_Infinite) // Ray contains BC edge
        {
            // Looks for closest point to ray end point
            if  ( (quad.B - this->Origin).GetSquaredLength() < (quad.C - this->Origin).GetSquaredLength() )
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

        Vector2 vAuxCD;
        EIntersections numIntCD = this->IntersectionPoint(BaseLineSegment<Vector2>(quad.C, quad.D), vAuxCD); // Checks intersection with CD edge
        if (numIntCD == EIntersections::E_Infinite) // Ray contains CD edge
        {
            // Looks for closest point to ray end point
            if  ( (quad.C - this->Origin).GetSquaredLength() < (quad.D - this->Origin).GetSquaredLength() )
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

        Vector2 vAuxDA;
        EIntersections numIntDA = this->IntersectionPoint(BaseLineSegment<Vector2>(quad.D, quad.A), vAuxDA); // Checks intersection with DA edge
        if (numIntDA == EIntersections::E_Infinite) // Ray contains DA edge
        {
            // Looks for closest point to ray end point
            if  ( (quad.D - this->Origin).GetSquaredLength() < (quad.A - this->Origin).GetSquaredLength() )
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

        if (numIntAB == EIntersections::E_One) // Ray has ONE intersection with AB edge
        {
            bPrevInt = true;
            vPrevInt = vAuxAB;
        }

        if (numIntBC == EIntersections::E_One) // Ray has ONE intersection with BC edge
        {
            if (bPrevInt) // There is a previous intersection with an edge
            {
                if (vPrevInt != vAuxBC) // There are not the same point (a common vertex)
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

        if (numIntCD == EIntersections::E_One)
        {
            if (bPrevInt) // There is a previous intersection with an edge
            {
                if (vPrevInt != vAuxCD) // There are not the same point (a common vertex)
                {
                    // Looks for closest point to ray end point
                    if  ( (vAuxCD - this->Origin).GetSquaredLength() < (vPrevInt - this->Origin).GetSquaredLength() )
                    {
                        vIntersection1 = vAuxCD;
                        vIntersection2 = vPrevInt;
                    }
                    else
                    {
                        vIntersection1 = vPrevInt;
                        vIntersection2 = vAuxCD;
                    }
                    return EIntersections::E_Two;
                }
            }
            else // Its the first intersection found
            {
                bPrevInt = true;
                vPrevInt = vAuxCD;
            }
        }

        if (numIntDA == EIntersections::E_One)
        {
            if (bPrevInt) // There is a previous intersection with an edge
            {
                if (vPrevInt != vAuxDA) // There are not the same point (a common vertex)
                {
                    // Looks for closest point to ray end point
                    if  ( (vAuxDA - this->Origin).GetSquaredLength() < (vPrevInt - this->Origin).GetSquaredLength() )
                    {
                        vIntersection1 = vAuxDA;
                        vIntersection2 = vPrevInt;
                    }
                    else
                    {
                        vIntersection1 = vPrevInt;
                        vIntersection2 = vAuxDA;
                    }
                    return EIntersections::E_Two;
                }
            }
            else // Its the first intersection found
                Z_ASSERT_WARNING(false, "Something went very wrong, this code branch must never be reached");  // Something is wrong
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

bool Ray2D::Intersection(const BaseLineSegment<Vector2> &segment) const
{
    // Direction vector of ray should not be null and the length of the segment should be greater than zero
    Z_ASSERT_WARNING( segment.A != segment.B && !this->Direction.IsZero(), "Direction vector of ray should not be null and the length of the segment should be greater than zero" );

    Vector2 vAux(segment.B - segment.A);

    const float_z &DENOMINATOR = this->Direction.x * vAux.y - this->Direction.y * vAux.x;

    if ( SFloat::IsZero(DENOMINATOR) ) // Both directions are parallels
    {
        if ( this->Contains(segment.A) )
            return true;
        else if ( this->Contains(segment.B) )
            return true;
        else
            return false;
    }
    else
    {
        const float_z &NUMERATOR1 = vAux.x * (this->Origin.y - segment.A.y) + vAux.y * (segment.A.x - this->Origin.x);
        if ((SFloat::IsNegative(DENOMINATOR) == SFloat::IsNegative(NUMERATOR1)) || SFloat::IsZero(NUMERATOR1))
        {
            const float_z &NUMERATOR2 = this->Direction.x * (this->Origin.y - segment.A.y) + this->Direction.y * (segment.A.x - this->Origin.x);
            if ( ( SFloat::IsNegative(DENOMINATOR) == SFloat::IsNegative(NUMERATOR2) &&
                   SFloat::IsGreaterOrEquals(SFloat::Abs(DENOMINATOR), SFloat::Abs(NUMERATOR2)) ) || SFloat::IsZero(NUMERATOR2) )
                return true;
            else
                return false;
        }
        else
            return false;
    }
}

EIntersections Ray2D::IntersectionPoint(const BaseLineSegment<Vector2> &segment, BaseVector2 &vIntersection) const
{
    // Direction vector of ray should not be null and the length of the segment should be greater than zero
    Z_ASSERT_WARNING( segment.A != segment.B && !this->Direction.IsZero(), "Direction vector of ray should not be null and the length of the segment should be greater than zero" );

    Vector2 vAux(segment.B - segment.A);

    const float_z &DENOMINATOR = this->Direction.x * vAux.y - this->Direction.y * vAux.x;

    if ( SFloat::IsZero(DENOMINATOR) ) // Both directions are parallels
    {
        const bool &A_IS_IN_RAY = this->Contains(segment.A);
        const bool &B_IS_IN_RAY = this->Contains(segment.B);

        if ( A_IS_IN_RAY && B_IS_IN_RAY )
        {
            if(this->Origin == segment.A)
            {
                vIntersection = segment.A;
            }
            else if(this->Origin == segment.B)
            {
                vIntersection = segment.B;
            }
            else if(SFloat::IsNegative( (segment.B - segment.A).DotProduct(segment.B - this->Origin) ))// To know which endpoint is closer to the origin of the ray...
            {
                vIntersection = segment.A;
            }
            else
            {
                vIntersection = segment.B;
            }

            return EIntersections::E_Two;
        }
        else if ( A_IS_IN_RAY )
        {
            if (segment.A == this->Origin)
            {
                vIntersection = this->Origin;
                return EIntersections::E_One;
            }
            else
            {
                vIntersection = this->Origin;
                return EIntersections::E_Two;
            }
        }
        else if ( B_IS_IN_RAY )
        {
            if (segment.B == this->Origin)
            {
                vIntersection = this->Origin;
                return EIntersections::E_One;
            }
            else
            {
                vIntersection = this->Origin;
                return EIntersections::E_Two;
            }
        }
        else
            return EIntersections::E_None;
    }
    else
    {
        const float_z &NUMERATOR1 = vAux.x * (this->Origin.y - segment.A.y) + vAux.y * (segment.A.x - this->Origin.x);
        if ((SFloat::IsNegative(DENOMINATOR) == SFloat::IsNegative(NUMERATOR1)) || SFloat::IsZero(NUMERATOR1))
        {
            const float_z &NUMERATOR2 = this->Direction.x * (this->Origin.y - segment.A.y) + this->Direction.y * (segment.A.x - this->Origin.x);
            if ( ( SFloat::IsNegative(DENOMINATOR) == SFloat::IsNegative(NUMERATOR2) &&
                   SFloat::IsGreaterOrEquals(SFloat::Abs(DENOMINATOR), SFloat::Abs(NUMERATOR2)) ) || SFloat::IsZero(NUMERATOR2) )
            {
                vIntersection = this->Origin + (NUMERATOR1/DENOMINATOR) * this->Direction;
                return EIntersections::E_One;
            }
            else
                return EIntersections::E_None;
        }
        else
            return EIntersections::E_None;
    }
}

EIntersections Ray2D::IntersectionPoint(const BaseLineSegment<Vector2> &segment, BaseVector2 &vIntersection1, BaseVector2 &vIntersection2) const
{
    // Direction vector of ray should not be null and the length of the segment should be greater than zero
    Z_ASSERT_WARNING( segment.A != segment.B && !this->Direction.IsZero(), "Direction vector of ray should not be null and the length of the segment should be greater than zero" );

    Vector2 vAux(segment.B - segment.A);

    const float_z &DENOMINATOR = this->Direction.x * vAux.y - this->Direction.y * vAux.x;

    if ( SFloat::IsZero(DENOMINATOR) ) // Both directions are parallels
    {
        const bool &A_IS_IN_RAY = this->Contains(segment.A);
        const bool &B_IS_IN_RAY = this->Contains(segment.B);

        if ( A_IS_IN_RAY && B_IS_IN_RAY )
        {
            if(this->Origin == segment.A)
            {
                vIntersection1 = segment.A;
                vIntersection2 = segment.B;
            }
            else if(this->Origin == segment.B)
            {
                vIntersection1 = segment.B;
                vIntersection2 = segment.A;
            }
            else if(SFloat::IsNegative( (segment.B - segment.A).DotProduct(segment.B - this->Origin) ))// To know which endpoint is closer to the origin of the ray...
            {
                vIntersection1 = segment.A;
                vIntersection2 = segment.B;
            }
            else
            {
                vIntersection1 = segment.B;
                vIntersection2 = segment.A;
            }

            return EIntersections::E_Two;
        }
        else if ( A_IS_IN_RAY )
        {
            vIntersection1 = this->Origin;

            if (segment.A == this->Origin)
            {
                return EIntersections::E_One;
            }
            else
            {
                vIntersection2 = segment.A;
                return EIntersections::E_Two;
            }
        }
        else if ( B_IS_IN_RAY )
        {
            vIntersection1 = this->Origin;

            if (segment.B == this->Origin)
            {
                return EIntersections::E_One;
            }
            else
            {
                vIntersection2 = segment.B;
                return EIntersections::E_Two;
            }
        }
        else
            return EIntersections::E_None;
    }
    else
    {
        const float_z &NUMERATOR1 = vAux.x * (this->Origin.y - segment.A.y) + vAux.y * (segment.A.x - this->Origin.x);
        if ((SFloat::IsNegative(DENOMINATOR) == SFloat::IsNegative(NUMERATOR1)) || SFloat::IsZero(NUMERATOR1))
        {
            const float_z &NUMERATOR2 = this->Direction.x * (this->Origin.y - segment.A.y) + this->Direction.y * (segment.A.x - this->Origin.x);
            if ( ( SFloat::IsNegative(DENOMINATOR) == SFloat::IsNegative(NUMERATOR2) &&
                   SFloat::IsGreaterOrEquals(SFloat::Abs(DENOMINATOR), SFloat::Abs(NUMERATOR2)) ) || SFloat::IsZero(NUMERATOR2) )
            {
                vIntersection1 = this->Origin + (NUMERATOR1/DENOMINATOR) * this->Direction;
                return EIntersections::E_One;
            }
            else
                return EIntersections::E_None;
        }
        else
            return EIntersections::E_None;
    }
}

void Ray2D::Reflection(const BaseLineSegment<Vector2> &segment, BaseRay<Vector2, Vector2> &ray) const
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

void Ray2D::Reflection(const BaseLineSegment<Vector2> &segment, BaseVector2 &vDirection) const
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

Ray2D Ray2D::Transform(const TransformationMatrix3x3 &transformation) const
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
    SPoint::Rotate(fRotationAngle, rcast_z(&auxRay, Vector2*), 2);
    return auxRay;
}

Ray2D Ray2D::RotateWithPivot(const float_z fRotationAngle, const BaseVector2 &vPivot) const
{
    Ray2D auxRay = *this;
    SPoint::RotateWithPivot(fRotationAngle, vPivot, &auxRay.Origin, 1);
    SPoint::Rotate(fRotationAngle, &auxRay.Direction, 1);
    return auxRay;
}

Ray2D Ray2D::Translate(const BaseVector2 &vTranslation) const
{
    Ray2D auxRay = *this;
    SPoint::Translate(vTranslation, &auxRay.Origin, 1);
    return auxRay;
}

Ray2D Ray2D::Translate(const float_z fTranslationX, const float_z fTranslationY) const
{
    Ray2D auxRay = *this;
    SPoint::Translate(fTranslationX, fTranslationY, &auxRay.Origin, 1);
    return auxRay;
}

Ray2D Ray2D::Scale(const BaseVector2 &vScale) const
{
    Ray2D auxRay = *this;
    SPoint::Scale(vScale, rcast_z(&auxRay, Vector2*), 2);
    return Ray2D(auxRay.Origin, auxRay.Direction.Normalize());
}

Ray2D Ray2D::Scale(const float_z vScaleX, const float_z vScaleY) const
{
    Ray2D auxRay = *this;
    SPoint::Scale(vScaleX, vScaleY, rcast_z(&auxRay, Vector2*), 2);
    return Ray2D(auxRay.Origin, auxRay.Direction.Normalize());
}

Ray2D Ray2D::ScaleWithPivot(const BaseVector2 &vScale, const BaseVector2 &vPivot) const
{
    Ray2D auxRay = *this;
    SPoint::ScaleWithPivot(vScale, vPivot, &auxRay.Origin, 1);
    SPoint::Scale(vScale, &auxRay.Direction, 1);
    return Ray2D(auxRay.Origin, auxRay.Direction.Normalize());
}

Ray2D Ray2D::ScaleWithPivot(const float_z vScaleX, const float_z vScaleY, const BaseVector2 &vPivot) const
{
    Ray2D auxRay = *this;
    SPoint::ScaleWithPivot(vScaleX, vScaleY, vPivot, &auxRay.Origin, 1);
    SPoint::Scale(vScaleX, vScaleY, &auxRay.Direction, 1);
    return Ray2D(auxRay.Origin, auxRay.Direction.Normalize());
}

Ray2D Ray2D::TransformWithPivot(const TransformationMatrix3x3 &transformation, const BaseVector2 &vPivot) const
{
    Ray2D auxRay = *this;
    SPoint::TransformWithPivot(transformation, vPivot, &auxRay.Origin, 1);

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

bool Ray2D::PointInsideTriangle(const BaseTriangle<Vector2>& triangle, const Vector2& vPoint) const
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

bool Ray2D::PointInsideQuadrilateral(const BaseQuadrilateral& quad, const Vector2& vPoint) const
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


} // namespace z
