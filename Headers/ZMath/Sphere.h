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

#ifndef __SPHERE__
#define __SPHERE__

#include "ZMath/Orb.h"
#include "ZMath/Vector3.h"
#include "ZMath/Vector4.h"
#include "ZMath/Quaternion.h"
#include "ZMath/SPoint.h"
#include "ZMath/EIntersections.h"
#include "ZMath/ESpaceRelation.h"
#include "ZMath/Plane.h"



namespace z
{

/// <summary>
/// Class which represents a sphere in space.
/// </summary>
/// <remarks>
/// A sphere is the collection of all points that are equidistant from other point known as "Center".
/// </remarks>
/// <typeparam name="VectorT">Allowed types: Vector2, Vector3, Vector4.</typeparam>
template <class VectorT>
class Sphere : public Orb<VectorT>
{

    // BASE CLASS USINGS
    // -------------------
public:

    using Orb<VectorT>::Center;
    using Orb<VectorT>::Radius;


    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor.
    /// </summary>
    Sphere()
    {
    }

    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="sphere">[IN] The sphere from which we want to create a copy in the resident sphere.</param>
    Sphere(const Sphere<VectorT> &sphere) : Orb<VectorT>(sphere)
    {
    }

    /// <summary>
    /// Base type constructor.
    /// </summary>
    /// <param name="orb">[IN] The sphere in which we want resident sphere to be based.</param>
    Sphere(const BaseOrb<VectorT> &orb) : Orb<VectorT>(orb)
    {
    }

    /// <summary>
    /// Constructor from a point as center of the sphere and its radius.
    /// </summary>
    /// <param name="vCenter">[IN] Vector that defines the center of the sphere.</param>
    /// <param name="fRadius">[IN] A floating point value to define the radius.</param>
    Sphere(const VectorT &vCenter, const float_z fRadius) : Orb<VectorT>(vCenter, fRadius)
    {
    }


    // PROPERTIES
    // ---------------
public:

    /// <summary>
    /// Gets a "unit sphere" placed in the center of coordinates and whose radius equals to 1.
    /// </summary>
    /// <returns>
    /// A "unit sphere".
    /// </returns>
    static const Sphere<VectorT>& GetUnitSphere()
    {
        static const Sphere<VectorT> UNITSPHERE(VectorT::GetNullVector(), SFloat::_1);
        return UNITSPHERE;
    }


    // METHODS
    // ---------------
public:

    /// <summary>
    /// Assignation operator.
    /// </summary>
    /// <param name="sphere">[IN] The orb to be copied from.</param>
    /// <returns>
    /// A reference to the modified orb.
    /// </returns>
    Sphere<VectorT>& operator=(const BaseOrb<VectorT> &sphere)
    {
        BaseOrb<VectorT>::operator=(sphere);
        return *this;
    }

    /// <summary>
    /// Translates the sphere.
    /// </summary>
    /// <param name="vTranslation">[IN] Vector that contains the translation to be applied.</param>
    /// <returns>
    /// The translated sphere.
    /// </returns>
    Sphere<VectorT> Translate(const Vector3 &vTranslation) const
    {
        Sphere<VectorT> auxSphere = *this;
        SPoint::Translate(vTranslation, &auxSphere.Center, 1);
        return auxSphere;
    }

    /// <summary>
    /// Translates the sphere.
    /// </summary>
    /// <param name="fTranslationX">[IN] Scalar that contains the translation on X axis.</param>
    /// <param name="fTranslationY">[IN] Scalar that contains the translation on Y axis.</param>
    /// <param name="fTranslationZ">[IN] Scalar that contains the translation on Z axis.</param>
    /// <returns>
    /// The translated sphere.
    /// </returns>
    Sphere<VectorT> Translate(const float_z fTranslationX, const float_z fTranslationY, const float_z fTranslationZ) const
    {
        Sphere<VectorT> auxSphere = *this;
        SPoint::Translate(fTranslationX, fTranslationY, fTranslationZ, &auxSphere.Center, 1);
        return auxSphere;
    }

    /// <summary>
    /// Rotates the sphere.
    /// </summary>
    /// <param name="qRotation">[IN] Quaternion that represents the rotation.</param>
    /// <returns>
    /// The rotated sphere.
    /// </returns>
    Sphere<VectorT> Rotate(const Quaternion &qRotation) const
    {
        Sphere<VectorT> auxSphere = *this;
        SPoint::Rotate(qRotation, &auxSphere.Center, 1);
        return auxSphere;
    }

    /// <summary>
    /// Rotates the sphere using a pivot.
    /// </summary>
    /// <param name="qRotation">[IN] Quaternion that represents the rotation.</param>
    /// <param name="vPivot">[IN] Vector used as pivot for the rotation.</param>
    /// <returns>
    /// The rotated sphere.
    /// </returns>
    Sphere<VectorT> RotateWithPivot(const Quaternion &qRotation, const VectorT &vPivot) const
    {
        Sphere<VectorT> auxSphere = *this;
        SPoint::RotateWithPivot(qRotation, vPivot, &auxSphere.Center, 1);
        return auxSphere;
    }

     /// <summary>
    /// Scales the sphere.
    /// </summary>
    /// <param name="vScale">[IN] Vector that contains the scale to be applied.</param>
    /// <param name="fRadiusScale">[IN] Multiplying factor to scale the sphere's radius.</param>
    /// <returns>
    /// The scaled sphere.
    /// </returns>
    Sphere<VectorT> Scale(const Vector3 &vScale, const float_z fRadiusScale) const
    {
        Sphere<VectorT> auxSphere = *this;
        SPoint::Scale(vScale, &auxSphere.Center, 1);
        return Sphere<VectorT>(auxSphere.Center, auxSphere.Radius * fRadiusScale);
    }

     /// <summary>
    /// Scales the sphere.
    /// </summary>
    /// <param name="fScaleX">[IN] Scalar that contains the scale on X axis.</param>
    /// <param name="fScaleY">[IN] Scalar that contains the scale on Y axis.</param>
    /// <param name="fScaleZ">[IN] Scalar that contains the scale on Z axis.</param>
    /// <param name="fRadiusScale">[IN] Multiplying factor to scale the sphere's radius.</param>
    /// <returns>
    /// The scaled sphere.
    /// </returns>
    Sphere<VectorT> Scale(const float_z fScaleX, const float_z fScaleY, const float_z fScaleZ, const float_z fRadiusScale) const
    {
        Sphere<VectorT> auxSphere = *this;
        SPoint::Scale(fScaleX, fScaleY, fScaleZ, &auxSphere.Center, 1);
        return Sphere<VectorT>(auxSphere.Center, auxSphere.Radius * fRadiusScale);
    }

     /// <summary>
    /// Scales the sphere using a pivot.
    /// </summary>
    /// <param name="vScale">[IN] Vector that contains the scale to be applied.</param>
    /// <param name="fRadiusScale">[IN] Multiplying factor to scale the sphere's radius.</param>
    /// <param name="vPivot">[IN] Vector used as pivot for the scale.</param>
    /// <returns>
    /// The scaled sphere.
    /// </returns>
    Sphere<VectorT> ScaleWithPivot(const Vector3 &vScale, const float_z fRadiusScale, const VectorT &vPivot) const
    {
        Sphere<VectorT> auxSphere = *this;
        SPoint::ScaleWithPivot(vScale, vPivot, &auxSphere.Center, 1);
        return Sphere<VectorT>(auxSphere.Center, auxSphere.Radius * fRadiusScale);
    }

     /// <summary>
    /// Scales the sphere using a pivot.
    /// </summary>
    /// <param name="fScaleX">[IN] Scalar that contains the scale on X axis.</param>
    /// <param name="fScaleY">[IN] Scalar that contains the scale on Y axis.</param>
    /// <param name="fScaleZ">[IN] Scalar that contains the scale on Z axis.</param>
    /// <param name="fRadiusScale">[IN] Multiplying factor to scale the sphere's radius.</param>
    /// <param name="vPivot">[IN] Vector used as pivot for the scale.</param>
    /// <returns>
    /// The scaled sphere.
    /// </returns>
    Sphere<VectorT> ScaleWithPivot(const float_z fScaleX, const float_z fScaleY, const float_z fScaleZ, const float_z fRadiusScale,
                               const VectorT &vPivot) const
    {
        Sphere<VectorT> auxSphere = *this;
        SPoint::ScaleWithPivot(fScaleX, fScaleY, fScaleZ, vPivot, &auxSphere.Center, 1);
        return Sphere<VectorT>(auxSphere.Center, auxSphere.Radius * fRadiusScale);
    }

    /// <summary>
    /// This method applies to the resident sphere the rotation defined by the provided rotation matrix
    /// around the coordinate axis centre.
    /// </summary>
    /// <param name="rotation">[IN] Rotation matrix which contais the rotation to be applied.</param>
    /// <returns>
    /// The rotated sphere.
    /// </returns>
    Sphere<VectorT> Rotate(const RotationMatrix3x3 &rotation) const
    {
        Sphere<VectorT> auxSphere = *this;
        SPoint::Rotate(rotation, &auxSphere.Center, 1);
        return auxSphere;
    }

    /// <summary>
    /// This method transforms the resident sphere by applying the rotation contained in the
    /// provided rotation matrix around a pivot point (which acts as center of rotation).
    /// </summary>
    /// <param name="rotation">[IN] Rotation matrix which contains the rotation to be applied.</param>
    /// <param name="vPivot">[IN] The pivot point which the rotation will be accomplished around.</param>
    /// <returns>
    /// The rotated sphere.
    /// </returns>
    Sphere<VectorT> RotateWithPivot(const RotationMatrix3x3 &rotation, const VectorT &vPivot) const
    {
        Sphere<VectorT> auxSphere = *this;
        SPoint::RotateWithPivot(rotation, vPivot, &auxSphere.Center, 1);
        return auxSphere;
    }

    /// <summary>
    /// This method performs a translation of the resident sphere given by the provided translation matrix.
    /// </summary>
    /// <param name="translation">[IN] Matrix which contains the translation to be applied.</param>
    /// <returns>
    /// The translated sphere.
    /// </returns>
    Sphere<VectorT> Translate(const TranslationMatrix<Matrix4x3> &translation) const
    {
        Sphere<VectorT> auxSphere = *this;
        SPoint::Translate(translation, &auxSphere.Center, 1);
        return auxSphere;
    }

    /// <summary>
    /// This method performs a translation of the resident sphere given by the provided translation matrix.
    /// </summary>
    /// <param name="translation">[IN] Matrix which contains the translation to be applied.</param>
    /// <returns>
    /// The translated sphere.
    /// </returns>
    Sphere<VectorT> Translate(const TranslationMatrix<Matrix4x4> &translation) const
    {
        Sphere<VectorT> auxSphere = *this;
        SPoint::Translate(translation, &auxSphere.Center, 1);
        return auxSphere;
    }

    /// <summary>
    /// This method scales the resident sphere by the scale contained in the provided scale matrix.
    /// </summary>
    /// <param name="scale">[IN] Matrix which contains the scale to be applied.</param>
    /// <param name="fRadiusScale">[IN] Multiplying factor to scale the sphere's radius.</param>
    /// <returns>
    /// The scaled sphere.
    /// </returns>
    Sphere<VectorT> Scale(const ScalingMatrix3x3 &scale, const float_z fRadiusScale) const
    {
        Sphere<VectorT> auxSphere = *this;
        SPoint::Scale(scale, &auxSphere.Center, 1);
        return Sphere<VectorT>(auxSphere.Center, auxSphere.Radius * fRadiusScale);
    }

    /// <summary>
    /// This method scales the resident sphere by the scale contained in the provided matrix,
    /// acting the provided vector as pivot of scale.
    /// </summary>
    /// <param name="scale">[IN] Matrix which contains the scale to be applied.</param>
    /// <param name="fRadiusScale">[IN] Multiplying factor to scale the sphere's radius.</param>
    /// <param name="vPivot">[IN] The point which acts as pivot of the scale.</param>
    /// <returns>
    /// The scaled sphere.
    /// </returns>
    Sphere<VectorT> ScaleWithPivot(const ScalingMatrix3x3 &scale, const float_z fRadiusScale, const VectorT &vPivot) const
    {
        Sphere<VectorT> auxSphere = *this;
        SPoint::ScaleWithPivot(scale, vPivot, &auxSphere.Center, 1);
        return Sphere<VectorT>(auxSphere.Center, auxSphere.Radius * fRadiusScale);
    }

    /// <summary>
    /// This method transforms the resident sphere applying the provided transformation matrix.
    /// </summary>
    /// <param name="transformation">[IN] Matrix which contains the transformation to be applied.</param>
    /// <param name="fRadiusScale">[IN] Multiplying factor to scale the sphere's radius.</param>
    /// <returns>
    /// The transformed sphere.
    /// </returns>
    Sphere<VectorT> Transform(const TransformationMatrix<Matrix4x3> &transformation, const float_z fRadiusScale) const
    {
        Sphere<VectorT> auxSphere = *this;
        SPoint::Transform(transformation, &auxSphere.Center, 1);
        return Sphere<VectorT>(auxSphere.Center, auxSphere.Radius * fRadiusScale);
    }

    /// <summary>
    /// This method transforms the resident sphere applying the provided transformation matrix.
    /// </summary>
    /// <param name="transformation">[IN] Matrix which contains the transformation to be applied.</param>
    /// <param name="fRadiusScale">[IN] Multiplying factor to scale the sphere's radius.</param>
    /// <returns>
    /// The transformed sphere.
    /// </returns>
    Sphere<VectorT> Transform(const TransformationMatrix<Matrix4x4> &transformation, const float_z fRadiusScale) const
    {
        Sphere<VectorT> auxSphere = *this;
        SPoint::Transform(transformation, &auxSphere.Center, 1);
        return Sphere<VectorT>(auxSphere.Center, auxSphere.Radius * fRadiusScale);
    }

    /// <summary>
    /// This method transforms the resident sphere applying the provided space conversion matrix.
    /// </summary>
    /// <remarks>
    /// Only the center of sphere is affected by this transformation.
    /// </remarks>
    /// <param name="spaceConversion">[IN] Matrix which contains the space conversion transformation to be applied.</param>
    /// <returns>
    /// The transformed sphere.
    /// </returns>
    Sphere<VectorT> Transform(const SpaceConversionMatrix &spaceConversion) const
    {
        Sphere<VectorT> auxSphere = *this;
        SPoint::Transform(spaceConversion, &auxSphere.Center, 1);
        return auxSphere;
    }

    /// <summary>
    /// This method transforms the resident sphere applying the provided transformation matrix,
    /// acting the provided vector as pivot of transformation.
    /// </summary>
    /// <remarks>
    /// When using 4D vectors, the W component of the pivot point doesn't affect the result.
    /// </remarks>
    /// <param name="transformation">[IN] Matrix which contains the transformation to be applied.</param>
    /// <param name="fRadiusScale">[IN] Multiplying factor to scale the sphere's radius.</param>
    /// <param name="vPivot">[IN] The point which acts as pivot of the transformation.</param>
    /// <returns>
    /// The transformed sphere.
    /// </returns>
    Sphere<VectorT> TransformWithPivot(const TransformationMatrix<Matrix4x3> &transformation, const float_z fRadiusScale,
                                   const VectorT &vPivot) const
    {
        Sphere<VectorT> auxSphere = *this;
        SPoint::TransformWithPivot(transformation, vPivot, &auxSphere.Center, 1);
        return Sphere<VectorT>(auxSphere.Center, auxSphere.Radius * fRadiusScale);
    }

    /// <summary>
    /// This method transforms the resident sphere applying the provided transformation matrix,
    /// acting the provided vector as pivot of transformation.
    /// </summary>
    /// <remarks>
    /// When using 4D vectors, the W component of the pivot point doesn't affect the result.
    /// </remarks>
    /// <param name="transformation">[IN] Matrix which contains the transformation to be applied.</param>
    /// <param name="fRadiusScale">[IN] Multiplying factor to scale the sphere's radius.</param>
    /// <param name="vPivot">[IN] The point which acts as pivot of the transformation.</param>
    /// <returns>
    /// The transformed sphere.
    /// </returns>
    Sphere<VectorT> TransformWithPivot(const TransformationMatrix<Matrix4x4> &transformation, const float_z fRadiusScale,
                                   const VectorT &vPivot) const
    {
        Sphere<VectorT> auxSphere = *this;
        SPoint::TransformWithPivot(transformation, vPivot, &auxSphere.Center, 1);
        return Sphere<VectorT>(auxSphere.Center, auxSphere.Radius * fRadiusScale);
    }

    /// <summary>
    /// Checks the space relation between current sphere and a plane received as parameter.
    /// </summary>
    /// <remarks>
    /// Space relation means that the sphere is in the positive side of the space divided by the plane (subspace pointed by plane´s normal),
    /// in the negative side or in both sides (intersection).
    /// </remarks>
    /// <param name="plane">[IN] The plane we want check the relation with current sphere. It must be normalized to obtain correct result. 
    /// If it is null, the result is undefined.</param>
    /// <returns>
    /// An enumerated value like follows:
    /// - Positive Side
    /// - Negative Side
    /// - Both Sides (intersects with the plane).
    /// </returns>
    ESpaceRelation SpaceRelation(const BasePlane &plane) const
    {
        // The plane should not be null
        Z_ASSERT_WARNING( !(SFloat::IsZero(plane.a) && SFloat::IsZero(plane.b) && SFloat::IsZero(plane.c)), "The plane should not be null" );

        // The radius should not equal zero
        Z_ASSERT_WARNING( SFloat::IsNotZero(this->Radius), "The radius should not equal zero" );

        const float_z &DIST_P = plane.a * this->Center.x + plane.b * this->Center.y + plane.c * this->Center.z + plane.d;

        if (SFloat::IsZero(DIST_P))
        {
            return ESpaceRelation::E_BothSides;
        }
        else
        {
            const float_z &ABS_DIST_P = SFloat::Abs(DIST_P);

            if (SFloat::IsLessThan(ABS_DIST_P, Radius))
                return ESpaceRelation::E_BothSides;
            else if (SFloat::IsNegative(DIST_P))
                return ESpaceRelation::E_NegativeSide;
            else
                return ESpaceRelation::E_PositiveSide;
        }
    }

    /// <summary>
    /// Projects the sphere to a plane perpendicularly.
    /// </summary>
    /// <remarks>
    /// Only the center point of the sphere is projected. Radius keeps its original value. 
    /// </remarks>
    /// <param name="plane">[IN] Plane where current sphere will be projected. It must be normalized to obtain correct result. 
    /// If it is null, the result is undefined.</param>
    /// <returns>
    /// The projected sphere.
    /// </returns>
    Sphere<VectorT> ProjectToPlane(const Plane &plane) const
    {
        // The plane should not be null
        Z_ASSERT_WARNING( !(SFloat::IsZero(plane.a) && SFloat::IsZero(plane.b) && SFloat::IsZero(plane.c)), "The input plane should not be null" );

        return Sphere<VectorT>(plane.PointProjection(this->Center), this->Radius);
    }
};


// SPECIALIZATION EXPORTATIONS
// -----------------------------
#ifdef Z_MATH_MODULE_TEMPLATE_SPECIALIZATION_SYMBOLS

template class Z_MATH_MODULE_SYMBOLS Sphere<Vector3>;
template class Z_MATH_MODULE_SYMBOLS Sphere<Vector4>;

#endif // Z_MATH_MODULE_TEMPLATE_SPECIALIZATION_SYMBOLS

} // namespace z


#endif // __SPHERE__
