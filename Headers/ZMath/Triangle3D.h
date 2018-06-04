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

#ifndef __TRIANGLE3D__
#define __TRIANGLE3D__

#include "ESpaceRelation.h"
#include "Triangle.h"
#include "ZMath/Vector3.h"
#include "ZMath/Vector4.h"
#include "ZMath/Quaternion.h"
#include "Plane.h"
#include "SPoint.h"



namespace z
{
namespace Internals
{

/// <summary>
/// Class which represents a triangle in 3D.
/// </summary>
/// <typeparam name="VectorT">Allowed types: Vector3, Vector4.</typeparam>
template <class VectorT>
class Triangle3D : public Triangle<VectorT>
{

    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor. It is an empty constructor, it does not assign any value.
    /// </summary>
    Triangle3D()
    {
    }

    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="triangle">[IN] The 3D triangle from which we want to create a copy in the resident 3D triangle.</param>
    Triangle3D(const Triangle3D<VectorT> &triangle) : Triangle<VectorT>(triangle)
    {
    }

    /// <summary>
    /// Base type constructor.
    /// </summary>
    /// <param name="triangle">[IN] The 3D triangle in which we want resident 3D triangle to be based.</param>
    Triangle3D(const Triangle<VectorT> &triangle) : Triangle<VectorT>(triangle)
    {
    }

    /// <summary>
    /// Constructor from three vector types, one for each vertex.
    /// </summary>
    /// <param name="vA">[IN] Vector types which defines vertex A.</param>
    /// <param name="vB">[IN] Vector types which defines vertex B.</param>
    /// <param name="vC">[IN] Vector types which defines vertex C.</param>
    Triangle3D(const VectorT &vA, const VectorT &vB, const VectorT &vC) : Triangle<VectorT>(vA, vB, vC)
    {
    }

    /// <summary>
    /// Constructor from three pointer-to-float type, one for each vertex.
    /// </summary>
    /// <remarks>
    /// Each pointer references to an array which has at least three or four elements.
    /// </remarks>
    /// <param name="arValuesA">[IN] Array of components of the vertex A. If it is null, the behavior is undefined.</param>
    /// <param name="arValuesB">[IN] Array of components of the vertex B. If it is null, the behavior is undefined.</param>
    /// <param name="arValuesC">[IN] Array of components of the vertex C. If it is null, the behavior is undefined.</param>
    Triangle3D(const float_z* arValuesA, const float_z* arValuesB, const float_z* arValuesC) :
                           Triangle<VectorT>(arValuesA, arValuesB, arValuesC)
    {
    }

    /// <summary>
    /// Constructor from three 4x32 packed floating point values, one for each vertex.
    /// </summary>
    /// <param name="valueA">[IN] 4x32 packed value which defines vertex A.</param>
    /// <param name="valueB">[IN] 4x32 packed value which defines vertex B.</param>
    /// <param name="valueC">[IN] 4x32 packed value which defines vertex C.</param>
    Triangle3D(const vf32_z valueA, const vf32_z valueB, const vf32_z valueC) :
                           Triangle<VectorT>(valueA, valueB, valueC)
    {
    }


    // METHODS
    // ---------------
public:

    /// <summary>
    /// Assignation operator. Assigns the provided triangle to the resident triangle.
    /// </summary>
    /// <param name="triangle">[IN] 3D triangle that is assigned to current triangle.</param>
    /// <returns>
    /// A reference to the triangle.
    /// </returns>
    Triangle3D<VectorT>& operator=(const Triangle<VectorT> &triangle)
    {
        Triangle<VectorT>::operator=(triangle);
        return *this;
    }

    /// <summary>
    /// Calculates the triangle's normal vector.
    /// </summary>
    /// <remarks>
    /// The resultant vector can be deduced by imagining that the triangle is facing the screen; if the vertices are traversed in alphabetical order (A, B, C then A again),
    /// clockwise, the vector points toward the outside of the screen. If the turn direction is counter-clockwise, the vector points toward the interior of the screen.<br/>
    /// If any of the vertices of the triangle coincide or if they are colinear, the result is undefined.
    /// </remarks>
    /// <returns>
    /// The normal vector.
    /// </returns>
    Vector3 GetNormal() const
    {
        const Vector3 A_TO_B = Vector3(this->B - this->A);
        const Vector3 B_TO_C = Vector3(this->C - this->B);

        return A_TO_B.CrossProduct(B_TO_C).Normalize();
    }

    /// <summary>
    /// Calculates triangle's circumcenter.
    /// </summary>
    /// <remarks>
    /// If any of the vertices of the triangle coincide or if they are colinear, the result is undefined.
    /// </remarks>
    /// <returns>
    /// The triangle's circumcenter.
    /// </returns>
    VectorT GetCircumcenter() const
    {
        // Vertices shouldn't coincide
        Z_ASSERT_WARNING( this->A != this->B && this->B != this->C && this->C != this->A, "Vertices shouldn't coincide, this may cause a division by zero" );

        // More information: https://www.box.net/shared/9736bjiyq1

        //STEP 1: Calculate all previous stuff
        const VectorT A_TO_B(this->B - this->A);
        const VectorT B_TO_C(this->C - this->B);
        const VectorT C_TO_A(this->A - this->C);

        // Triangle´s semiperimeter
        const float_z SEMIPERIMETER = (A_TO_B.GetLength() + B_TO_C.GetLength() + C_TO_A.GetLength()) * SFloat::_0_5;
        // Triangle´s area
        const float_z AREA = sqrt_z(SEMIPERIMETER * (SEMIPERIMETER - A_TO_B.GetLength()) * (SEMIPERIMETER - B_TO_C.GetLength()) * (SEMIPERIMETER - C_TO_A.GetLength()));

        const VectorT CROSS_PRODUCT_AB_BC = A_TO_B.CrossProduct(B_TO_C);
        const VectorT CROSS_PRODUCT_CA_AB_BC = C_TO_A.CrossProduct(CROSS_PRODUCT_AB_BC);

        //STEP 2: Calculate circumcenter
        return ((this->A + this->C) * SFloat::_0_5) + (A_TO_B.DotProduct(B_TO_C) / (SFloat::_8 * AREA * AREA)) * CROSS_PRODUCT_CA_AB_BC;
    }

    /// <summary>
    /// This method performs a translation of the resident triangle given by the provided vector.
    /// </summary>
    /// <param name="vTranslation">[IN] Vector which contains the translation to be applied.</param>
    /// <returns>
    /// The translated triangle.
    /// </returns>
    Triangle3D<VectorT> Translate(const Vector3 &vTranslation) const
    {
        Triangle3D<VectorT> auxTriangle = *this;
        SPoint::Translate(vTranslation, rcast_z(&auxTriangle, VectorT*), 3);
        return auxTriangle;
    }

    /// <summary>
    /// This method performs a translation of the resident triangle given by the provided amounts for every axis.
    /// </summary>
    /// <param name="fTranslationX">[IN] Scalar value that contains the translation on X axis.</param>
    /// <param name="fTranslationY">[IN] Scalar value that contains the translation on Y axis.</param>
    /// <param name="fTranslationZ">[IN] Scalar value that contains the translation on Z axis.</param>
    /// <returns>
    /// The translated triangle.
    /// </returns>
    Triangle3D<VectorT> Translate(const float_z fTranslationX, const float_z fTranslationY, const float_z fTranslationZ) const
    {
        Triangle3D<VectorT> auxTriangle = *this;
        SPoint::Translate(fTranslationX, fTranslationY, fTranslationZ, rcast_z(&auxTriangle, VectorT*), 3);
        return auxTriangle;
    }

    /// <summary>
    /// Translates the triangle applying a [4x3] translation matrix.
    /// </summary>
    /// <param name="translation">[IN] The [4x3] translation matrix to be applied.</param>
    /// <returns>
    /// The translated triangle.
    /// </returns>
    Triangle3D<VectorT> Translate(const TranslationMatrix<Matrix4x3> &translation) const
    {
        Triangle3D<VectorT> auxTriangle = *this;
        SPoint::Translate(translation, rcast_z(&auxTriangle, VectorT*), 3);
        return auxTriangle;
    }

    /// <summary>
    /// Translates the triangle applying a [4x4] translation matrix.
    /// </summary>
    /// <param name="translation">[IN] The [4x4] translation matrix to be applied.</param>
    /// <returns>
    /// The translated triangle.
    /// </returns>
    Triangle3D<VectorT> Translate(const TranslationMatrix<Matrix4x4> &translation) const
    {
        Triangle3D<VectorT> auxTriangle = *this;
        SPoint::Translate(translation, rcast_z(&auxTriangle, VectorT*), 3);
        return auxTriangle;
    }

    /// <summary>
    /// This method applies to the resident triangle the rotation defined by the provided quaternion
    /// around the coordinate axis centre.
    /// </summary>
    /// <param name="qRotation">[IN] Quaternion which contais the rotation to be applied.</param>
    /// <returns>
    /// The rotated triangle.
    /// </returns>
    Triangle3D<VectorT> Rotate(const Quaternion &qRotation) const
    {
        Triangle3D<VectorT> auxTriangle = *this;
        SPoint::Rotate(qRotation, rcast_z(&auxTriangle, VectorT*), 3);
        return auxTriangle;
    }

    /// <summary>
    /// Rotates the triangle applying the provided rotation matrix.
    /// </summary>
    /// <param name="rotation">[IN] Rotation matrix to be applied.</param>
    /// <returns>
    /// The rotated triangle.
    /// </returns>
    Triangle3D<VectorT> Rotate(const RotationMatrix3x3 &rotation) const
    {
        Triangle3D<VectorT> auxTriangle = *this;
        SPoint::Rotate(rotation, rcast_z(&auxTriangle, VectorT*), 3);
        return auxTriangle;
    }

    /// <summary>
    /// This method applies to the resident triangle the rotation defined by the provided quaternion
    /// around a point which acts as pivot of rotation.
    /// </summary>
    /// <param name="qRotation">[IN] Quaternion which contais the rotation to be applied.</param>
    /// <param name="vPivot">[IN] The pivot point which the rotation will be accomplished around.</param>
    /// <returns>
    /// The rotated triangle.
    /// </returns>
    Triangle3D<VectorT> RotateWithPivot(const Quaternion &qRotation, const VectorT &vPivot) const
    {
        Triangle3D<VectorT> auxTriangle = *this;
        SPoint::RotateWithPivot(qRotation, vPivot, rcast_z(&auxTriangle, VectorT*), 3);
        return auxTriangle;
    }

    /// <summary>
    /// This method scales the resident triangle by the scale contained in the provided vector.
    /// </summary>
    /// <param name="vScale">[IN] Vector which contains the scale to be applied in every axis.</param>
    /// <returns>
    /// The scaled triangle.
    /// </returns>
    Triangle3D<VectorT> Scale(const Vector3 &vScale) const
    {
        Triangle3D<VectorT> auxTriangle = *this;
        SPoint::Scale(vScale, rcast_z(&auxTriangle, VectorT*), 3);
        return auxTriangle;
    }

    /// <summary>
    /// This method scales the resident triangle by the provided amounts for every axis.
    /// </summary>
    /// <param name="fScaleX">[IN] Scalar value that contains the scale on X axis.</param>
    /// <param name="fScaleY">[IN] Scalar value that contains the scale on Y axis.</param>
    /// <param name="fScaleZ">[IN] Scalar value that contains the scale on Z axis.</param>
    /// <returns>
    /// The scaled triangle.
    /// </returns>
    Triangle3D<VectorT> Scale(const float_z fScaleX, const float_z fScaleY, const float_z fScaleZ) const
    {
        Triangle3D<VectorT> auxTriangle = *this;
        SPoint::Scale(fScaleX, fScaleY, fScaleZ, rcast_z(&auxTriangle, VectorT*), 3);
        return auxTriangle;
    }

    /// <summary>
    /// Scales the triangle applying a scale matrix.
    /// </summary>
    /// <param name="scale">[IN] Scale matrix to be applied.</param>
    /// <returns>
    ///The scaled triangle.
    /// </returns>
    Triangle3D<VectorT> Scale(const ScalingMatrix3x3 &scale) const
    {
        Triangle3D<VectorT> auxTriangle = *this;
        SPoint::Scale(scale, rcast_z(&auxTriangle, VectorT*), 3);
        return auxTriangle;
    }

    /// <summary>
    /// This method scales the resident triangle by the scale contained in the provided vector using the
    /// provided point as pivot of scale.
    /// </summary>
    /// <param name="vScale">[IN] Vector which contains the scale to be applied in every axis.</param>
    /// <param name="vPivot">[IN] The point which acts as pivot of the scale.</param>
    /// <returns>
    /// The scaled triangle.
    /// </returns>
    Triangle3D<VectorT> ScaleWithPivot(const Vector3 &vScale, const VectorT &vPivot) const
    {
        Triangle3D<VectorT> auxTriangle = *this;
        SPoint::ScaleWithPivot(vScale, vPivot, rcast_z(&auxTriangle, VectorT*), 3);
        return auxTriangle;
    }

    /// <summary>
    /// This method scales the resident triangle by the provided amounts for every axis using the
    /// provided point as pivot of scale.
    /// </summary>
    /// <param name="fScaleX">[IN] Scalar value that contains the scale on X axis.</param>
    /// <param name="fScaleY">[IN] Scalar value that contains the scale on Y axis.</param>
    /// <param name="fScaleZ">[IN] Scalar value that contains the scale on Z axis.</param>
    /// <param name="vPivot">[IN] The point which acts as pivot of the scale.</param>
    /// <returns>
    /// The scaled triangle.
    /// </returns>
    Triangle3D<VectorT> ScaleWithPivot(const float_z fScaleX, const float_z fScaleY, const float_z fScaleZ, const VectorT& vPivot) const
    {
        Triangle3D<VectorT> auxTriangle = *this;
        SPoint::ScaleWithPivot(fScaleX, fScaleY, fScaleZ, vPivot, rcast_z(&auxTriangle, VectorT*), 3);
        return auxTriangle;
    }

    /// <summary>
    /// Transforms the resident triangle applying the [4x3] transformation matrix provided.
    /// </summary>
    /// <param name="transformation">[IN] A [4x3] transformation matrix to be applied.</param>
    /// <returns>
    /// The transformed triangle.
    /// </returns>
    Triangle3D<VectorT> Transform(const TransformationMatrix<Matrix4x3> &transformation) const
    {
        Triangle3D<VectorT> auxTriangle = *this;
        SPoint::Transform(transformation, rcast_z(&auxTriangle, VectorT*), 3);
        return auxTriangle;
    }

    /// <summary>
    /// Transforms the resident triangle applying the [4x4] transformation matrix provided.
    /// </summary>
    /// <param name="transformation">[IN] A [4x4] transformation matrix to be applied.</param>
    /// <returns>
    /// The transformed triangle.
    /// </returns>
    Triangle3D<VectorT> Transform(const TransformationMatrix<Matrix4x4> &transformation) const
    {
        Triangle3D<VectorT> auxTriangle = *this;
        SPoint::Transform(transformation, rcast_z(&auxTriangle, VectorT*), 3);
        return auxTriangle;
    }

    /// <summary>
    /// This method transforms the resident triangle by applying the rotation contained in the
    /// provided rotation matrix around a pivot point (which acts as center of rotation).
    /// </summary>
    /// <param name="rotation">[IN] Rotation matrix which contains the rotation to be applied.</param>
    /// <param name="vPivot">[IN] The pivot point which the rotation will be accomplished around.</param>
    /// <returns>
    /// The rotated triangle.
    /// </returns>
    Triangle3D<VectorT> RotateWithPivot(const RotationMatrix3x3 &rotation, const VectorT &vPivot) const
    {
        Triangle3D<VectorT> auxTriangle = *this;
        SPoint::RotateWithPivot(rotation, vPivot, rcast_z(&auxTriangle, VectorT*), 3);
        return auxTriangle;
    }

    /// <summary>
    /// This method scales the resident triangle by the scale contained in the provided matrix,
    /// acting the provided vector as pivot of scale.
    /// </summary>
    /// <param name="scale">[IN] Matrix which contains the scale to be applied.</param>
    /// <param name="vPivot">[IN] The point which acts as pivot of the scale.</param>
    /// <returns>
    /// The scalde triangle.
    /// </returns>
    Triangle3D<VectorT> ScaleWithPivot(const ScalingMatrix3x3 &scale, const VectorT &vPivot) const
    {
        Triangle3D<VectorT> auxTriangle = *this;
        SPoint::ScaleWithPivot(scale, vPivot, rcast_z(&auxTriangle, VectorT*), 3);
        return auxTriangle;
    }

    /// <summary>
    /// This method transforms the resident triangle applying the provided transformation matrix,
    /// acting the provided vector as pivot of transformation.
    /// </summary>
    /// <remarks>
    /// When using 4D vectors, the W component of the pivot point doesn't affect the result.
    /// </remarks>
    /// <param name="transformation">[IN] Matrix which contains the transformation to be applied.</param>
    /// <param name="vPivot">[IN] The point which acts as pivot of the transformation.</param>
    /// <returns>
    /// The transformed triangle.
    /// </returns>
    Triangle3D<VectorT> TransformWithPivot(const TransformationMatrix<Matrix4x3> &transformation, const VectorT &vPivot) const
    {
        Triangle3D<VectorT> auxTriangle = *this;
        SPoint::TransformWithPivot(transformation, vPivot, rcast_z(&auxTriangle, VectorT*), 3);
        return auxTriangle;
    }

    /// <summary>
    /// This method transforms the resident triangle applying the provided transformation matrix,
    /// acting the provided vector as pivot of transformation.
    /// </summary>
    /// <remarks>
    /// When using 4D vectors, the W component of the pivot point doesn't affect the result.
    /// </remarks>
    /// <param name="transformation">[IN] Matrix which contains the transformation to be applied.</param>
    /// <param name="vPivot">[IN] The point which acts as pivot of the transformation.</param>
    /// <returns>
    /// The transformed triangle.
    /// </returns>
    Triangle3D<VectorT> TransformWithPivot(const TransformationMatrix<Matrix4x4> &transformation, const VectorT &vPivot) const
    {
        Triangle3D<VectorT> auxTriangle = *this;
        SPoint::TransformWithPivot(transformation, vPivot, rcast_z(&auxTriangle, VectorT*), 3);
        return auxTriangle;
    }
    
    /// <summary>
    /// This method transforms the resident triangle applying the provided space conversion matrix.
    /// </summary>
    /// <param name="spaceConversion">[IN] Matrix which contains the space conversion transformation to be applied.</param>
    /// <returns>
    /// The converted triangle.
    /// </returns>
    Triangle<VectorT> Transform(const SpaceConversionMatrix &spaceConversion) const
    {
        Triangle<VectorT> auxTriangle = *this;
        SPoint::Transform(spaceConversion, rcast_z(&auxTriangle, VectorT*), 3);
        return auxTriangle;
    }

    /// <summary>
    /// Checks the space relation between the triangle and a plane received as parameter.
    /// </summary>
    /// <remarks>
    /// Space relation means that the triangle is in the positive side of the space divided by the plane, 
    /// in the negative side, in both sides (intersection) or even the triangle is contained in the plane.<br/>
    /// If one or two vertices belong to the plane, the third vertex will determine whether the triangle
    /// is in the positive or negative side.
    /// </remarks>
    /// <param name="plane">[IN] The plane we want check the relation with current triangle. If it is null, the result is undefined.</param>
    /// <returns>
    /// An enumerated value like follows:<br/>
    /// - Contained in the plane
    /// - Positive Side
    /// - Negative Side
    /// - Both Sides (intersects the plane).
    /// </returns>
    ESpaceRelation SpaceRelation(const Plane &plane) const
    {
        // The plane should not be null
        Z_ASSERT_WARNING( !(SFloat::IsZero(plane.a) && SFloat::IsZero(plane.b) && SFloat::IsZero(plane.c)), "Input plane should not be null" );

        const float_z &DIST_TO_A = plane.a * this->A.x + plane.b * this->A.y + plane.c * this->A.z + plane.d;
        const float_z &DIST_TO_B = plane.a * this->B.x + plane.b * this->B.y + plane.c * this->B.z + plane.d;
        const float_z &DIST_TO_C = plane.a * this->C.x + plane.b * this->C.y + plane.c * this->C.z + plane.d;

        if ( SFloat::IsZero(DIST_TO_A) && SFloat::IsZero(DIST_TO_B) && SFloat::IsZero(DIST_TO_C) )
            return ESpaceRelation::E_Contained;
        else if ( SFloat::IsGreaterOrEquals(DIST_TO_A, SFloat::_0) && SFloat::IsGreaterOrEquals(DIST_TO_B, SFloat::_0) && SFloat::IsGreaterOrEquals(DIST_TO_C, SFloat::_0) )
            return ESpaceRelation::E_PositiveSide;
        else if ( SFloat::IsLessOrEquals(DIST_TO_A, SFloat::_0) && SFloat::IsLessOrEquals(DIST_TO_B, SFloat::_0) &&
                  SFloat::IsLessOrEquals(DIST_TO_C, SFloat::_0) )
            return ESpaceRelation::E_NegativeSide;
        else
            return ESpaceRelation::E_BothSides;
    }

    /// <summary>
    /// Moves the triangle along its normal vector the units indicated by a scalar value.
    /// </summary>
    /// <remarks>
    /// If any of the vertices of the triangle coincide or if they are colinear, the result is undefined.
    /// </remarks>
    /// <param name="fAmount">[IN] The amount of movement.</param>
    /// <returns>
    /// The extruded triangle.
    /// </returns>
    Triangle3D<VectorT> Extrude(const float_z fAmount) const
    {
        VectorT vLangthenedNormalVector = VectorT(this->GetNormal() * fAmount);

        return Triangle3D<VectorT>(this->A + vLangthenedNormalVector,
                                       this->B + vLangthenedNormalVector,
                                       this->C + vLangthenedNormalVector);
    }

    /// <summary>
    /// Calculates triangle's orthocenter.
    /// </summary>
    /// <remarks>
    /// When using 4D vectors, the W component of the resultant point will depend on the W component of the
    /// vertices of the triangle.<br/>
    /// If any of the vertices of the triangle coincide, the result is undefined.
    /// </remarks>
    /// <returns>
    /// The orthocenter.
    /// </returns>
    VectorT GetOrthocenter() const
    {
        // Method from here: http://descartes.cnice.mec.es/materiales_didacticos/OrtoCircun/Ortocentro.htm

        const VectorT &AB = this->B - this->A;
        const VectorT &BC = this->C - this->B;
        const VectorT &CA = this->A - this->C;

        // Normal to BC in ABC plane
        const VectorT &NORMAL_TO_BC = ( BC.CrossProduct(AB) ).CrossProduct(BC);

        // NORMAL_TO_BC and AB can't be perpendicular, but we ensure it:
        const float_z &DOT = NORMAL_TO_BC.DotProduct(AB);

        Z_ASSERT_WARNING(DOT != SFloat::_0, "\"NORMAL_TO_BC\" and \"AB\" can't be perpendicular");

        return this->A - ( CA.DotProduct(AB) / DOT ) * NORMAL_TO_BC;
    }

    /// <summary>
    /// Projects resident triangle over a given plane, storing the resultant triangle in the provided one.
    /// </summary>
    /// <remarks>
    /// The plane must be normalized to obtain correct result.
    /// </remarks>
    /// <param name="plane">[IN] Plane where to project the resident triangle. If it is null, the result is undefined.</param>
    /// <returns>
    /// The projected triangle.
    /// </returns>
    Triangle3D<VectorT> ProjectToPlane(const Plane &plane) const
    {
        return Triangle3D<VectorT>(plane.PointProjection(this->A),
                                       plane.PointProjection(this->B),
                                       plane.PointProjection(this->C));
    }

};


// SPECIALIZATION EXPORTATIONS
// -----------------------------
#ifdef Z_MATH_MODULE_TEMPLATE_SPECIALIZATION_SYMBOLS

template class Z_MATH_MODULE_SYMBOLS Triangle3D<Vector3>;
template class Z_MATH_MODULE_SYMBOLS Triangle3D<Vector4>;

#endif // Z_MATH_MODULE_TEMPLATE_SPECIALIZATION_SYMBOLS

} // namespace Internals


// TYPEDEFS
// ----------
typedef Internals::Triangle<Vector3> Triangle3;
typedef Internals::Triangle<Vector4> Triangle4;

} // namespace z


#endif // __TRIANGLE3D__
