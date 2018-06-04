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

#ifndef __ORB__
#define __ORB__

#include "ZCommon/Assertions.h"
#include "ZMath/MathModuleDefinitions.h"
#include "ZMath/Vector2.h"
#include "ZMath/Vector3.h"
#include "ZMath/Vector4.h"
#include "ZCommon/DataTypes/SFloat.h"



namespace z
{
namespace Internals
{

/// <summary>
/// Class which represents an orb in the space, defined by its center point and radius.
/// </summary>
/// <remarks>
/// Center point may be expressed as 2D or 3D point or vector, depending on the parameter of the template,
/// which may be 2D vector, 3D vector or 4D vector.<br/>
/// Radius is expressed as a floating point value which is always nonnegative.<br/>
/// Remember that an orb is the sum of equidistant points from a given one.
/// </remarks>
/// <typeparam name="VectorT">Allowed types: Vector3, Vector4.</typeparam>
template <class VectorT>
class Orb
{
    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor. It is an empty constructor, it does not assign any value.
    /// </summary>
    Orb()
    {
    }

    /// <summary>
    /// Constructor from a vector which defines the center point and a floating point value which
    /// defines the radius for the orb.
    /// </summary>
    /// <param name="vCenter">[IN] Vector to define the center of the orb.</param>
    /// <param name="fRadius">[IN] A floating point value to define the radius.</param>
    Orb(const VectorT &vCenter, const float_z fRadius) : Center(vCenter), Radius(fRadius)
    {
    }


    // PROPERTIES
    // ---------------
public:

    /// <summary>
    /// Gets a "unit orb" placed in the center of coordinates and whose radius equals to 1.
    /// </summary>
    /// <returns>
    /// A unit orb.
    /// </returns>
    static const Orb<VectorT>& GetUnitOrb()
    {
        static const Orb<VectorT> UNITORB(VectorT::GetNullVector(), SFloat::_1);
        return UNITORB;
    }


    // METHODS
    // ---------------
public:
    
    /// <summary>
    /// Equality operator. Compares two orbs.
    /// </summary>
    /// <param name="orb">[IN] Orb with which to compare.</param>
    /// <returns>
    /// True if orbs are the same, false otherwise.
    /// </returns>
    bool operator== (const Orb<VectorT> &orb) const
    {
        return this->Center == orb.Center && SFloat::AreEqual(this->Radius, orb.Radius);
    }

    /// <summary>
    /// Inequality operator. Compares two orbs.
    /// </summary>
    /// <param name="orb">[IN] Orb with which to compare.</param>
    /// <returns>
    /// True if orbs are not the same, false otherwise.
    /// </returns>
    bool operator!= (const Orb<VectorT> &orb) const
    {
        return !(*this == orb);
    }

    /// <summary>
    /// This method receives a point and determines if the point is contained into the orb.
    /// </summary>
    /// <remarks>
    /// If the radius of the orb equals zero, the orb will be considered as a point (which is wrong).
    /// </remarks>
    /// <param name="vPoint">[IN] The point to be tested.</param>
    /// <returns>
    /// True if the point is inside the orb (or if it belongs to its bounds). Otherwise returns false.
    /// </returns>
    bool Contains(const VectorT &vPoint) const
    {
        // If the radius of the orb equals zero, it doesn't exist
        Z_ASSERT_WARNING( SFloat::IsNotZero(this->Radius), "The radius of the orb must not equal zero to exist" );

        // The point is inside the orb whenever the minimum squared distance between the point and
        // the center point of the orb is lower or equals the whole square radius of the orb.
        VectorT vDistance(vPoint - this->Center);
        return SFloat::IsLessOrEquals(vDistance.GetSquaredLength(), Radius * Radius);
    }

    /// <summary>
    /// Receives another orb and computes whether this orb intersects with the resident one or not.
    /// </summary>
    /// <remarks>
    /// If the radius of the orb equals zero, the orb will be considered as a point (which is wrong).
    /// </remarks>
    /// <param name="orb">[IN] The orb to be checked for intersections.</param>
    /// <returns>
    /// A boolean value that indicates whether the orbs intersect or not.<br/>
    /// <br/>
    /// <b>True</b><br/>
    /// The orbs intersect, including the following cases:
    /// - The orbs intersect partially.
    /// - The orbs are tangent.
    /// - The orbs coincide completely.
    /// - One orb is contained in the other.
    ///
    /// <b>False</b><br/>
    /// The orbs do not intersect.
    /// </returns>
    bool Intersection(const Orb<VectorT> &orb) const
    {
        // If the radius of the orb equals zero, it doesn't exist
        Z_ASSERT_WARNING( SFloat::IsNotZero(this->Radius) && SFloat::IsNotZero(orb.Radius), "The radius of the orbs must not equal zero to exist" );

        // An intersection between the two orbs is considered if the minimum squared distance
        // between their center points is lower or equals the square sum of their radius.
        VectorT vDistance(orb.Center - this->Center);
        float_z fRadiusSum = Radius + orb.Radius;
        return SFloat::IsLessOrEquals(vDistance.GetSquaredLength(), fRadiusSum * fRadiusSum);
    }

    /// <summary>
    /// Converts the orb into a string.
    /// </summary>
    /// <remarks>
    /// The format of the string is:<br/>
    /// "OB(c($Center),r($Radius))".<br/>
    /// Where "$" means "string representation of attribute".
    /// </remarks>
    /// <returns>
    /// The string with the specified format.
    /// </returns>
    string_z ToString() const
    {
        return string_z("OB(c(") + this->Center.ToString() + Z_L("),r(") + string_z::FromFloat(this->Radius) + Z_L("))");
    }
    

    // ATTRIBUTES
    // ---------------
public:

    /// <summary>
    /// Vector which represents the center point of orb.
    /// </summary>
    VectorT Center;

    /// <summary>
    /// Floating point value representig the radius of the orb.
    /// </summary>
    float_z Radius;
};


// SPECIALIZATION EXPORTATIONS
// -----------------------------
#ifdef Z_MATH_MODULE_TEMPLATE_SPECIALIZATION_SYMBOLS

template class Z_MATH_MODULE_SYMBOLS Orb<Vector2>;
template class Z_MATH_MODULE_SYMBOLS Orb<Vector3>;
template class Z_MATH_MODULE_SYMBOLS Orb<Vector4>;

#endif // Z_MATH_MODULE_TEMPLATE_SPECIALIZATION_SYMBOLS


} // namespace Internals
} // namespace z


#endif // __ORB__
