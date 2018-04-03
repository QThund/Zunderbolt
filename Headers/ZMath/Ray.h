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

#ifndef __RAY__
#define __RAY__

#include "ZMath/MathDefinitions.h"
#include "BaseRay.h"
#include "BaseOrb.h"
#include "EIntersections.h"
#include "ZMath/Vector2.h"
#include "ZMath/Vector3.h"
#include "ZMath/Vector4.h"



namespace z
{

/// <summary>
/// Represents a ray in the space, which consists of a origin point, or position, and a direction.
/// </summary>
/// <remarks>
/// The direction symbolizes a line with only one end (which coincides with the origin) and that extends to the infinite.
/// </remarks>
/// <typeparam name="VectorTOrigin">Allowed types: Vector2, Vector3, Vector4.</typeparam>
/// <typeparam name="VectorTDirection">Allowed types: Vector2 (when VectorTOrigin is Vector2), Vector3 (when VectorTOrigin is Vector3 or Vector4).</typeparam>
template<class VectorTOrigin, class VectorTDirection>
class Ray : public BaseRay<VectorTOrigin, VectorTDirection>
{

    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor.
    /// </summary>
    Ray()
    {
    }

    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="ray">[IN] The ray from which we want to create a copy in the resident ray.</param>
    Ray(const Ray<VectorTOrigin, VectorTDirection> &ray) : BaseRay<VectorTOrigin, VectorTDirection>(ray)
    {
    }

    /// <summary>
    /// Base type constructor.
    /// </summary>
    /// <param name="ray">[IN] The ray in which we want resident ray to be based.</param>
    Ray(const BaseRay<VectorTOrigin, VectorTDirection> &ray) : BaseRay<VectorTOrigin, VectorTDirection>(ray)
    {
    }

    /// <summary>
    /// Constructor that receives the ray's position and direction.
    /// </summary>
    /// <remarks>
    /// The direction vector must be normalized to construct the ray properly.
    /// </remarks>
    /// <param name="vOrigin">[IN] Ray's position.</param>
    /// <param name="vDirection">[IN] Ray's direction.</param>
    Ray(const VectorTOrigin &vOrigin, const VectorTDirection &vDirection) : BaseRay<VectorTOrigin, VectorTDirection>(vOrigin, vDirection)
    {
    }


    // PROPERTIES
    // ---------------
public:

    /// <summary>
    /// Gets a ray placed at the coordinate origin and whose direction vector is null.
    /// </summary>
    /// <returns>
    /// The null ray.
    /// </returns>
    static const Ray<VectorTOrigin, VectorTDirection>& GetNullRay()
    {
        static const Ray<VectorTOrigin, VectorTDirection> NULLRAY(VectorTOrigin::GetNullVector(), VectorTDirection::GetNullVector());
        return NULLRAY;
    }


    // METHODS
    // ---------------
public:

    /// <summary>
    /// Assignation operator that receives another ray.
    /// </summary>
    /// <param name="ray">[IN] An existing ray.</param>
    /// <returns>
    /// A reference to this ray, after assignation.
    /// </returns>
    Ray<VectorTOrigin, VectorTDirection>& operator=(const BaseRay<VectorTOrigin, VectorTDirection> &ray)
    {
        BaseRay<VectorTOrigin, VectorTDirection>::operator=(ray);
        return *this;
    }

    /// <summary>
    /// Converts the ray's direction in its opposite.
    /// </summary>
    /// <returns>
    /// The inverse of the ray.
    /// </returns>
    Ray<VectorTOrigin, VectorTDirection> Invert() const
    {
        return Ray<VectorTOrigin, VectorTDirection>(this->Origin, -this->Direction);
    }

    /// <summary>
    /// Normalizes the ray, converting its direction in a unit vector.
    /// </summary>
    /// <returns>
    /// The normalized ray.
    /// </returns>
    Ray<VectorTOrigin, VectorTDirection> Normalize() const
    {
        return Ray<VectorTOrigin, VectorTDirection>(this->Origin, this->Direction.Normalize());
    }

    /// <summary>
    /// Calculates any point that belongs to the ray, based on the distance to the ray's position.
    /// </summary>
    /// <remarks>
    /// The ray must be normalized to obtain a correct result.
    /// </remarks>
    /// <param name="fDistance">[IN] Distance from the point which is to be found to the ray's position.</param>
    /// <returns>
    /// A point of the ray.
    /// </returns>
    VectorTOrigin GetPoint(const float_z fDistance) const
    {
        // The direction vector must be normalized
        Z_ASSERT_WARNING( SFloat::AreEqual(this->Direction.GetLength(), SFloat::_1), "The direction vector must be normalized" );

        // It's assumed that the ray's direction vector is normalized
        return this->Origin + this->Direction * fDistance;
    }

    /// <summary>
    /// Checks if resident ray intersects with the provided orb.
    /// </summary>
    /// <remarks>
    /// If the direction of the ray is null, the result is undefined.
    /// </remarks>
    /// <param name="orb">[IN] The orb whose intersection with the ray will be checked.</param>
    /// <returns>
    /// A boolean value that indicates whether the ray and the orb intersect or not.<br/>
    /// <br/>
    /// <b>True</b><br/>
    /// The ray and the orb intersect, including the following cases:
    /// - The ray intersects the orb in two points.
    /// - The origin of the ray lays on the surface / perimeter of the orb (and the ray does not point to the orb).
    /// - The origin of the ray is contained in the orb.
    /// - The ray is tangent to the orb.
    ///
    /// <b>False</b><br/>
    /// The ray and the orb do not intersect.
    /// </returns>
    bool Intersection(const BaseOrb<VectorTOrigin> &orb) const
    {
        // [TODO] Thund: This method is easy to optimize.

        // The direction vector shouldn't be null and the radius of the orb shouldn't equal zero
        Z_ASSERT_WARNING( SFloat::IsNotZero(this->Direction.GetLength()) && SFloat::IsNotZero(orb.Radius), 
                   "The direction vector shouldn't be null and the radius of the orb shouldn't equal zero" );

        // The direction vector must be normalized
        Z_ASSERT_WARNING( SFloat::AreEqual(this->Direction.GetLength(), SFloat::_1), "The direction vector must be normalized" );
        
        // Converts all vectors to VectorTDirection, that always will be Vector2 or Vector3
        VectorTDirection vNewRayOrigin(this->Origin - orb.Center);

        //  B/2 (instead of B) is calculed here to optimize comparison.
        const float_z &fB = vNewRayOrigin.DotProduct(this->Direction);

        // Since ray is normalized, A = 1.
        //const float_z &fA = this->Direction.DotProduct(this->Direction);

        const float_z &fC = vNewRayOrigin.DotProduct(vNewRayOrigin) - orb.Radius * orb.Radius;

        // Discriminant: B^2 - 4AC
        const float_z fD = fB*fB - fC;

        if (SFloat::IsNegative(fD)) // D = B^2 - 4AC < 0 => 0 intersections
            return false;
        else if ( SFloat::IsZero(fD) ) // D = B^2 - 4AC = 0 => 1 intersection
        {
            if ( SFloat::IsGreaterOrEquals(-fB, SFloat::_0) ) // T = -B/2A -> must be >= 0
                return true;
            else
                return false;
        }
        else
            return SFloat::IsLessOrEquals(fB, sqrt_z(fD));

            // Explanation:

            // In this case, there are two posible intersections:
            //    T1 = -fB - sqrt(fD)   from (-B - sqrt(B*B - 4AC))/2A, where A = 1, B = 2*fB
            //    T2 = -fB + sqrt(fD)   from (-B + sqrt(B*B - 4AC))/2A, where A = 1, B = 2*fB
            //
            // One of T1 and T2 must be positive:
            // T1 >= 0  => fB <= -sqrt(fD)
            //    OR
            // T2 >= 0 => fB <= sqrt(fD)
            //
            // That is, is sufficient that fB <= sqrt(fD)
    }

    /// <summary>
    /// This method receives an orb, and computes the point where the resident ray intersects with it,
    /// if it exists.
    /// </summary>
    /// <remarks>
    /// The ray must be normalized to obtain a correct result.<br/>
    /// If the direction of the ray is null, the result is undefined.<br/>
    /// If there's no intersection point, the output parameter used for storing the point won't be modified.
    /// </remarks>
    /// <param name="orb">[IN] The orb whose intersections with the ray we want to check.</param>
    /// <param name="vIntersection">[OUT] A vector where to store the closest intersection point to the origin of the ray.</param>
    /// <returns>
    /// An enumerated value that indicates how many intersections were found:<br/>
    /// <br/>
    /// <b>None</b><br/>
    /// There are no intersections.<br/>
    ///
    /// <b>One</b><br/>
    /// There is one intersection.<br/>
    /// - The origin of the ray lays on the surface / perimeter of the orb and the ray does not point to the orb.
    /// - The origin of the ray is contained in the orb.
    /// - The ray is tangent to the orb.
    ///
    /// <b>Two</b><br/>
    /// There are two intersections.<br/>
    /// - The ray intersects with the orb in two points.
    /// - The origin of the ray lays on the surface / perimeter of the orb and the ray points to the orb.
    /// </returns>
    EIntersections IntersectionPoint(const BaseOrb<VectorTOrigin> &orb, VectorTOrigin &vIntersection) const
    {
        VectorTOrigin vAux;
        return this->IntersectionPoint(orb, vIntersection, vAux);
    }


    /// <summary>
    /// Computes the intersection point between the ray and provided orb, if it exists.
    /// </summary>
    /// <remarks>
    /// The ray must be normalized to obtain a correct result.<br/>
    /// If there's no intersection point, the output parameters won't be modified.<br/>
    /// Neither the length of the direction vector nor the radius of the orb should equal zero.
    /// </remarks>
    /// <param name="orb">[IN] The orb whose intersection with the ray will be checked.</param>
    /// <param name="vIntersection1">[OUT] A vector where to store the closest intersection point to the origin of the ray.</param>
    /// <param name="vIntersection2">[OUT] A vector where to store the furthest intersection point to the origin of the ray.</param>
    /// <returns>
    /// An enumerated value that indicates how many intersections were found:<br/>
    /// <br/>
    /// <b>None</b><br/>
    /// There are no intersections.<br/>
    ///
    /// <b>One</b><br/>
    /// There is one intersection.<br/>
    /// - The origin of the ray lays on the surface / perimeter of the orb and the ray does not point to the orb.
    /// - The origin of the ray is contained in the orb.
    /// - The ray is tangent to the orb.
    ///
    /// <b>Two</b><br/>
    /// There are two intersections.<br/>
    /// - The ray intersects with the orb in two points.
    /// - The origin of the ray lays on the surface / perimeter of the orb and the ray points to the orb.
    /// </returns>
    EIntersections IntersectionPoint(const BaseOrb<VectorTOrigin> &orb, VectorTOrigin &vIntersection1, VectorTOrigin &vIntersection2) const
    {
        // The direction vector shouldn't be null and the radius of the orb shouldn't equal zero
        Z_ASSERT_WARNING( SFloat::IsNotZero(this->Direction.GetLength()) && SFloat::IsNotZero(orb.Radius), 
                   "The direction vector shouldn't be null and the radius of the orb shouldn't equal zero" );

        // The direction vector must be normalized
        Z_ASSERT_WARNING( SFloat::AreEqual(this->Direction.GetLength(), SFloat::_1), "The direction vector must be normalized" );

        // We set all vectors to the same type that output parameters to allow operations
        const VectorTDirection &DIRECTION(this->Direction);

        // We reduce ray and orb to origin, in order to simplify orb equation, and we calculate
        // the new ray origin point
        const VectorTOrigin &NEW_RAY_ORIGIN(this->Origin - orb.Center);

        // We replace then in the orb equation to force it to verify the ray equation
        // DIRECTION^2*T^2 + 2*vNewA*DIRECTION*T + vNewA^2 - r^2 = 0
        // The intersections with ray follows this rules (extracted from quadratic ecuation):
        //       D = B^2 - 4AC = 0 => 1 intersection
        //       D = B^2 - 4AC < 0 => 0 intersections
        //       D = B^2 - 4AC > 0 => 2 intersections

        // Since ray is normalized, A = 1
        // const float_z &fA = this->Direction.DotProduct(this->Direction);

        const float_z &fB = SFloat::_2 * VectorTDirection(NEW_RAY_ORIGIN).DotProduct(DIRECTION);
        const float_z &fC = NEW_RAY_ORIGIN.DotProduct(NEW_RAY_ORIGIN) - orb.Radius * orb.Radius;

        // Remember that a = 1 -> D = B^2 - 4AC = B^2 - 4C
        const float_z &fD = fB * fB - SFloat::_4 * fC;


        if (SFloat::IsNegative(fD)) // D = B^2 - 4AC < 0 => 0 intersections
            return EIntersections::E_None;
        else if (SFloat::IsZero(fD)) // D = B^2 - 4AC = 0 => 1 intersection
        {
            // T = -B/2A -> Remember that a=1
            const float_z &fT = -fB*SFloat::_0_5;

            // The intersection is backwards the ray origin
            if (SFloat::IsNegative(fT))
                return EIntersections::E_None;
            else
            {
                vIntersection1 = NEW_RAY_ORIGIN + fT * DIRECTION + orb.Center;
                return EIntersections::E_One;
            }
        }
        else // D = B^2 - 4AC > 0 => 2 intersections
        {
            const float_z &SRT_D = sqrt_z(fD);

            // Closest intersection to ls.A. T1 = (-B - sqrt(D))/2A -> Remember that A = 1
            const float_z &fT1 = -(fB + SRT_D)*SFloat::_0_5;

            // Farthest intersection to ls.A. T2 = (-B + sqrt(D))/2A -> Remember that A = 1
            const float_z &fT2 = (-fB + SRT_D)*SFloat::_0_5;

            // Prevent rays with origin point inside orb, which must have only one intersection.
            const bool &T1_FAILS = SFloat::IsNegative(fT1);
            const bool &T2_FAILS = SFloat::IsNegative(fT2);

            if (T1_FAILS && T2_FAILS)
                return EIntersections::E_None; // Shouldn't happen this :(
            else if (T1_FAILS)  // One parameter is negative, there is only one intersection
            {
                vIntersection1 = NEW_RAY_ORIGIN + fT2 * DIRECTION + orb.Center;
                return EIntersections::E_One;
            }
            else if (T2_FAILS) // One parameter is negative, there is only one intersection
            {
                vIntersection1 = NEW_RAY_ORIGIN + fT1 * DIRECTION + orb.Center;
                return EIntersections::E_One;
            }
            else // Most of the cases: two intersections.
            {
                vIntersection1 = NEW_RAY_ORIGIN + fT1 * DIRECTION + orb.Center;
                vIntersection2 = NEW_RAY_ORIGIN + fT2 * DIRECTION + orb.Center;
                return EIntersections::E_Two;
            }
        }
    }

    /// <summary>
    /// Converts ray into a string.
    /// </summary>
    /// <remarks>
    /// The format of the string is:<br/>
    /// "RY(o($Origin),d($Direction))".<br/>
    /// Where "$" means "string representation of attribute".
    /// </summary>
    /// <returns>
    /// The string representation with the format specified.
    /// </returns>
    string_z ToString() const
    {
        return string_z("RY(o(") + this->Origin.ToString() + Z_L("),d(") + this->Direction.ToString() + Z_L("))");
    }

};


// SPECIALIZATION EXPORTATIONS
// -----------------------------
#ifdef Z_MATH_TEMPLATE_SPECIALIZATION_SYMBOLS

template class Z_LAYER_MATH_SYMBOLS Ray<Vector2, Vector2>;
template class Z_LAYER_MATH_SYMBOLS Ray<Vector3, Vector3>;
template class Z_LAYER_MATH_SYMBOLS Ray<Vector4, Vector3>;

#endif // Z_MATH_TEMPLATE_SPECIALIZATION_SYMBOLS

} // namespace z


#endif // __RAY__
