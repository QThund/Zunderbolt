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

#ifndef __HEXAHEDRON__
#define __HEXAHEDRON__

#include "ZMath/BaseHexahedron.h"
#include "ZMath/SPoint.h"
#include "ZMath/Quaternion.h"
#include "ZMath/Plane.h"
#include "ZMath/LineSegment3D.h"
#include "ZMath/Vector3.h"
#include "ZMath/Vector4.h"



namespace z
{

/// <summary>
/// Class which represents a hexahedron in the space. The hexahedron is defined by its eight vertices.
/// </summary>
/// <remarks>
/// It's supossed that ABCD defines a face of the hexahedron (eventually the top face) and
/// EFGH defines the opposite face (eventually the bottom one).<br/>
/// The six faces are defined by the followings vertices: ABCD, EFGH, AEFD, ABHE, BCGH, CDFG.<br/>
/// The twelve edges are AB, BC, CD, DA, EF, FG, GH, HE, AE, BH, CG, DF.
/// </remarks>
/// <typeparam name="VectorT">Allowed types: BaseVector3, BaseVector4, Vector3, Vector4.</typeparam>
template <class VectorT>
class Hexahedron : public BaseHexahedron<VectorT>
{
    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor.
    /// </summary>
    Hexahedron()
    {
    }

    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="hexahedron">[IN] The hexahedron from which we want to create a copy in the resident hexahedron.</param>
    Hexahedron(const Hexahedron<VectorT> &hexahedron) : BaseHexahedron<VectorT>(hexahedron)
    {
    }

    /// <summary>
    /// Base type constructor.
    /// </summary>
    /// <param name="hexahedron">[IN] The hexahedron in which we want resident hexahedron to be based.</param>
    Hexahedron(const BaseHexahedron<VectorT> &hexahedron) : BaseHexahedron<VectorT>(hexahedron)
    {
    }

    /// <summary>
    /// Constructor from eight vectors, one for each vertex.
    /// </summary>
    /// <param name="vA">[IN] Vector to define vertex A.</param>
    /// <param name="vB">[IN] Vector to define vertex B.</param>
    /// <param name="vC">[IN] Vector to define vertex C.</param>
    /// <param name="vD">[IN] Vector to define vertex D.</param>
    /// <param name="vE">[IN] Vector to define vertex E.</param>
    /// <param name="vF">[IN] Vector to define vertex F.</param>
    /// <param name="vG">[IN] Vector to define vertex G.</param>
    /// <param name="vH">[IN] Vector to define vertex H.</param>
    Hexahedron(const VectorT &vA, const VectorT &vB, const VectorT &vC, const VectorT &vD,
                       const VectorT &vE, const VectorT &vF, const VectorT &vG, const VectorT &vH) :
                           BaseHexahedron<VectorT>(vA, vB, vC, vD, vE, vF, vG, vH)
    {
    }

    /// <summary>
    /// Constructor from two vectors which defines two opposite vertices, with no common faces between them
    /// (the ends of any inner diagonals).
    /// </summary>
    /// <param name="vA">[IN] Vector which defines one vertex of a inner diagonal (it will be used to initialize A).</param>
    /// <param name="vG">[IN] Vector which defines the other vertex of the inner diagonal (it Will be used to initialized G).</param>
    Hexahedron(const VectorT &vA, const VectorT &vG) : BaseHexahedron<VectorT>(vA, vG)
    {
    }

    /// <summary>
    /// Constructor from a vector which defines the gravity center of the box and three floating
    /// points values which defines its height (Y), width (X) and depth (Z).
    /// </summary>
    /// <remarks>
    /// It's supossed that all edges are parallel to one of the axis.
    /// </remarks>
    /// <param name="vCenter">[IN] Center point of the box.</param>
    /// <param name="fLengthX">[IN] Length of an edge parallel to X axis (width).</param>
    /// <param name="fLengthY">[IN] Length of an edge parallel to Y axis (height).</param>
    /// <param name="fLengthZ">[IN] Length of an edge parallel to Z axis (depth).</param>
    Hexahedron(const VectorT &vCenter, const float_z &fLengthX, const float_z &fLengthY, const float_z &fLengthZ) :
                           BaseHexahedron<VectorT>(vCenter, fLengthX, fLengthY, fLengthZ)
    {
    }


    // PROPERTIES
    // ---------------
public:

    /// <summary>
    /// Gets an hexahedron that defines a cube whose egdes are 1 unit length, centered in the coordinate origin, and with all edges parallel
    /// to coordinate axis.
    /// </summary>
    /// <returns>
    /// A "unit cube".
    /// </returns>
    static const Hexahedron<VectorT>& GetUnitCube()
    {
        static const float_z POINT_COMPONENTS_A[] = {-SFloat::_0_5,  SFloat::_0_5,  SFloat::_0_5, SFloat::_1 };
        static const float_z POINT_COMPONENTS_B[] = {-SFloat::_0_5,  SFloat::_0_5, -SFloat::_0_5, SFloat::_1 };
        static const float_z POINT_COMPONENTS_C[] = { SFloat::_0_5,  SFloat::_0_5, -SFloat::_0_5, SFloat::_1 };
        static const float_z POINT_COMPONENTS_D[] = { SFloat::_0_5,  SFloat::_0_5,  SFloat::_0_5, SFloat::_1 };
        static const float_z POINT_COMPONENTS_E[] = {-SFloat::_0_5, -SFloat::_0_5,  SFloat::_0_5, SFloat::_1 };
        static const float_z POINT_COMPONENTS_F[] = { SFloat::_0_5, -SFloat::_0_5,  SFloat::_0_5, SFloat::_1 };
        static const float_z POINT_COMPONENTS_G[] = { SFloat::_0_5, -SFloat::_0_5, -SFloat::_0_5, SFloat::_1 };
        static const float_z POINT_COMPONENTS_H[] = {-SFloat::_0_5, -SFloat::_0_5, -SFloat::_0_5, SFloat::_1 };

        static const Hexahedron<VectorT> UNITCUBE = Hexahedron<VectorT>(  VectorT(POINT_COMPONENTS_A),
                                                                            VectorT(POINT_COMPONENTS_B),
                                                                            VectorT(POINT_COMPONENTS_C),
                                                                            VectorT(POINT_COMPONENTS_D),
                                                                            VectorT(POINT_COMPONENTS_E),
                                                                            VectorT(POINT_COMPONENTS_F),
                                                                            VectorT(POINT_COMPONENTS_G),
                                                                            VectorT(POINT_COMPONENTS_H));
        return UNITCUBE;
    }


    // METHODS
    // ---------------
public:

    /// <summary>
    /// Assignation operator.
    /// </summary>
    /// <param name="hexahedron">[IN] The hexahedron to be copied from.</param>
    /// <returns>
    /// A reference to the modified hexahedron.
    /// </returns>
    Hexahedron& operator=(const BaseHexahedron<VectorT>& hexahedron)
    {
        BaseHexahedron<VectorT>::operator=(hexahedron);
        return *this;
    }

    /// <summary>
    /// This method applies to the resident hexahedron the rotation defined by the provided quaternion
    /// around the coordinate axis centre.
    /// </summary>
    /// <param name="qRotation">[IN] Quaternion which contais the rotation to be applied.</param>
    /// <returns>
    /// The rotated hexahedron.
    /// </returns>
    Hexahedron<VectorT> Rotate(const Quaternion &qRotation) const
    {
        Hexahedron<VectorT> auxHexahedron = *this;
        SPoint::Rotate(qRotation, rcast_z(&auxHexahedron, VectorT*), 8);
        return auxHexahedron;
    }

    /// <summary>
    /// This method transforms the resident hexahedron by applying the rotation contained in the provided quaternion
    /// around a pivot point (which acts as center of rotation).
    /// </summary>
    /// <param name="qRotation">[IN] Quaternion which contains the rotation to be applied.</param>
    /// <param name="vPivot">[IN] The pivot point which the rotation will be accomplished around.</param>
    /// <returns>
    /// The rotated hexahedron.
    /// </returns>
    Hexahedron<VectorT> RotateWithPivot(const Quaternion &qRotation, const VectorT &vPivot) const
    {
        Hexahedron<VectorT> auxHexahedron = *this;
        SPoint::RotateWithPivot(qRotation, vPivot, rcast_z(&auxHexahedron, VectorT*), 8);
        return auxHexahedron;
    }

    /// <summary>
    /// This method performs a translation of the resident hexahedron given by the provided vector.
    /// </summary>
    /// <param name="vTranslation">[IN] Vector which contains the translation to be applied.</param>
    /// <returns>
    /// The translated hexahedron.
    /// </returns>
    Hexahedron<VectorT> Translate(const BaseVector3 &vTranslation) const
    {
        Hexahedron<VectorT> auxHexahedron = *this;
        SPoint::Translate(vTranslation, rcast_z(&auxHexahedron, VectorT*), 8);
        return auxHexahedron;
    }

    /// <summary>
    /// This method performs a translation of the resident hexahedron given by the provided amounts for every axis.
    /// </summary>
    /// <param name="fTranslationX">[IN] The amount of translation to be applied in X direction.</param>
    /// <param name="fTranslationY">[IN] The amount of translation to be applied in Y direction.</param>
    /// <param name="fTranslationZ">[IN] The amount of translation to be applied in Z direction.</param>
    /// <returns>
    /// The translated hexahedron.
    /// </returns>
    Hexahedron<VectorT> Translate(const float_z fTranslationX, const float_z fTranslationY, const float_z fTranslationZ) const
    {
        Hexahedron<VectorT> auxHexahedron = *this;
        SPoint::Translate(fTranslationX, fTranslationY, fTranslationZ, rcast_z(&auxHexahedron, VectorT*), 8);
        return auxHexahedron;
    }

    /// <summary>
    /// This method scales the resident hexahedron by the scale contained in the provided vector.
    /// </summary>
    /// <param name="vScale">[IN] Vector which contains the scale to be applied in every axis.</param>
    /// <returns>
    /// The scaled hexahedron.
    /// </returns>
    Hexahedron<VectorT> Scale(const BaseVector3 &vScale) const
    {
        Hexahedron<VectorT> auxHexahedron = *this;
        SPoint::Scale(vScale, rcast_z(&auxHexahedron, VectorT*), 8);
        return auxHexahedron;
    }

    /// <summary>
    /// This method scales the resident hexahedron by the provided amounts for every axis.
    /// </summary>
    /// <param name="fScaleX">[IN] The scale to be applied in X direction.</param>
    /// <param name="fScaleY">[IN] The scale to be applied in Y direction.</param>
    /// <param name="fScaleZ">[IN] The scale to be applied in Z direction.</param>
    /// <returns>
    /// The scaled hexahedron.
    /// </returns>
    Hexahedron<VectorT> Scale(const float_z fScaleX, const float_z fScaleY, const float_z fScaleZ) const
    {
        Hexahedron<VectorT> auxHexahedron = *this;
        SPoint::Scale(fScaleX, fScaleY, fScaleZ, rcast_z(&auxHexahedron, VectorT*), 8);
        return auxHexahedron;
    }

    /// <summary>
    /// This method scales the resident hexahedron by the scale contained in the provided vector,
    /// acting the other provided vector as pivot of scale.
    /// </summary>
    /// <param name="vScale">[IN] Vector which contains the scale to be applied in every axis.</param>
    /// <param name="vPivot">[IN] The point which acts as pivot of the scale.</param>
    /// <returns>
    /// The scaled hexahedron.
    /// </returns>
    Hexahedron<VectorT> ScaleWithPivot(const BaseVector3 &vScale, const VectorT &vPivot) const
    {
        Hexahedron<VectorT> auxHexahedron = *this;
        SPoint::ScaleWithPivot(vScale, vPivot, rcast_z(&auxHexahedron, VectorT*), 8);
        return auxHexahedron;
    }

    /// <summary>
    /// This method scales the resident hexahedron by the provided amounts for every axis,
    /// acting the provided vector as pivot of scale.
    /// </summary>
    /// <param name="fScaleX">[IN] The scale to be applied in X direction.</param>
    /// <param name="fScaleY">[IN] The scale to be applied in Y direction.</param>
    /// <param name="fScaleZ">[IN] The scale to be applied in Z direction.</param>
    /// <param name="vPivot">[IN] The point which acts as pivot of the scale.</param>
    /// <returns>
    /// The scaled hexahedron.
    /// </returns>
    Hexahedron<VectorT> ScaleWithPivot(const float_z fScaleX, const float_z fScaleY, const float_z fScaleZ, const VectorT &vPivot) const
    {
        Hexahedron<VectorT> auxHexahedron = *this;
        SPoint::ScaleWithPivot(fScaleX, fScaleY, fScaleZ, vPivot, rcast_z(&auxHexahedron, VectorT*), 8);
        return auxHexahedron;
    }

    /// <summary>
    /// This method store in the output parameter the six planes which defines the hexahedron.
    /// </summary>
    /// <remarks>
    /// The six planes are:<br/>
    /// <br/>
    /// <ul>
    /// <li>plane A, B, C -> ABCD face, stored in element 0 of the array</li>
    /// <li>plane E, F, G -> EFGH face, stored in element 1 of the array</li>
    /// <li>plane A, E, F -> AEFD face, stored in element 2 of the array</li>
    /// <li>plane A, B, H -> ABHE face, stored in element 3 of the array</li>
    /// <li>plane B, C, G -> BCGH face, stored in element 4 of the array</li>
    /// <li>plane C, D, F -> CDFG face, stored in element 5 of the array</li>
    /// </ul>
    /// All returned planes are normalized.<br/>
    /// Vertices of every face must be coplanar to obtain correct results.<br/>
    /// If two or more vertices of the hexahedron coincide, the result is undefined.
    /// </remarks>
    /// <param name="arPlanes">[OUT] An array where to store the six planes. It must have at least six elements. If the pointer
    /// is null, the behavior is undefined.</param>
    void GetPlanes(Plane *arPlanes) const
    {
        // The parameter shouldn't be null
        Z_ASSERT_ERROR(arPlanes != null_z, "Input array must not be null");

        arPlanes[0] = Plane(this->A, this->D, this->C); // ABCD face
        arPlanes[1] = Plane(this->E, this->H, this->G); // EFGH face
        arPlanes[2] = Plane(this->A, this->E, this->F); // AEFD face
        arPlanes[3] = Plane(this->A, this->B, this->H); // ABHE face
        arPlanes[4] = Plane(this->B, this->C, this->G); // BCGH face
        arPlanes[5] = Plane(this->C, this->D, this->F); // CDFG face
    }

    /// <summary>
    /// Checks if a point is inside or outside resident hexahedron.
    /// </summary>
    /// <remarks>
    /// Points in the surface of the hexahedron are considered inside it. The hexahedron is supposed to be convex; 
    /// otherwise, the result is undefined.<br/>
    /// Vertices of every face must be coplanar to obtain correct results.<br/>
    /// If two or more vertices of the hexahedron coincide, the result is undefined.
    /// </remarks>
    /// <param name="vPoint">[IN] Point which is being checked.</param>
    /// <returns>
    /// True if the point is inside hexahedron, false otherwise.
    /// </returns>
    bool Contains(const VectorT &vPoint) const
    {
        return ( PointsInSameSideOfPlane(vPoint, this->E, this->A, this->B, this->C) &&
                 PointsInSameSideOfPlane(vPoint, this->A, this->E, this->F, this->G) &&
                 PointsInSameSideOfPlane(vPoint, this->C, this->A, this->B, this->H) &&
                 PointsInSameSideOfPlane(vPoint, this->A, this->B, this->C, this->G) &&
                 PointsInSameSideOfPlane(vPoint, this->C, this->A, this->D, this->F) &&
                 PointsInSameSideOfPlane(vPoint, this->A, this->C, this->D, this->F) );
    }

    /// <summary>
    /// Checks the relation between resident hexahedron and the provided plane.
    /// </summary>
    /// <remarks>
    /// Since a plane divides space into two parts, we can check if the "distances" (allowing distances having sign) from
    /// the plane to all vertices of hexahedron have diferent sign, in which case the segment crosses the plane.<br/>
    /// If distances from plane to all vertices have the same sign, all hexahedron is in the same
    /// side of the space.<br/>
    /// Note that if a vertex of the resident hexahedron lies on the plane, we don't consider that it is
    /// crossing the plane.
    /// </remarks>
    /// <param name="plane">[IN] The plane the relation with resident hexahedron will be check. If the plane is null,
    /// the behavior is undefined.</param>
    /// <returns>
    /// An enumerated value indicating the space relation:<br/>
    /// - Contained: All hexahedron lies on the plane.
    /// - Positive Side: The hexahedron is fully contained in the positive side of the space defined by the plane.
    /// - Negative Side: The hexahedron is fully contained in the negative side of the space defined by the plane.
    /// - BothSides: The hexahedron crosses the plane.
    /// <br/>
    /// We consider "positive part of the space" the locus of points which verifies \f$ Ax + By + Cz + D > 0 \f$.
    /// </returns>
    ESpaceRelation SpaceRelation(const BasePlane &plane) const
    {
        // If all the vertices of the hexahedron coincide, it might be an erroneous figure
        Z_ASSERT_WARNING(this->A != this->B || this->A != this->C || this->A != this->D || this->A != this->E || this->A != this->F || this->A != this->G || this->A != this->G || this->A != this->H ||
                          this->B != this->C || this->B != this->D || this->B != this->E || this->B != this->F || this->B != this->G || this->B != this->G || this->B != this->H ||
                          this->C != this->D || this->C != this->E || this->C != this->F || this->C != this->G || this->C != this->G || this->C != this->H ||
                          this->D != this->E || this->D != this->F || this->D != this->G || this->D != this->G || this->D != this->H ||
                          this->E != this->F || this->E != this->G || this->E != this->G || this->E != this->H ||
                          this->F != this->G || this->F != this->H ||
                          this->G != this->H, "All the vertices of the hexahedron coincide, it might be an erroneous figure");

        // The plane must not be null
        Z_ASSERT_WARNING(SFloat::IsNotZero(plane.a) || SFloat::IsNotZero(plane.b) || SFloat::IsNotZero(plane.c), "The input plane should not be null");

        const float_z& DIST_A = plane.a * this->A.x + plane.b * this->A.y + plane.c * this->A.z + plane.d;
        const float_z& DIST_B = plane.a * this->B.x + plane.b * this->B.y + plane.c * this->B.z + plane.d;
        const float_z& DIST_C = plane.a * this->C.x + plane.b * this->C.y + plane.c * this->C.z + plane.d;
        const float_z& DIST_D = plane.a * this->D.x + plane.b * this->D.y + plane.c * this->D.z + plane.d;
        const float_z& DIST_E = plane.a * this->E.x + plane.b * this->E.y + plane.c * this->E.z + plane.d;
        const float_z& DIST_F = plane.a * this->F.x + plane.b * this->F.y + plane.c * this->F.z + plane.d;
        const float_z& DIST_G = plane.a * this->G.x + plane.b * this->G.y + plane.c * this->G.z + plane.d;
        const float_z& DIST_H = plane.a * this->H.x + plane.b * this->H.y + plane.c * this->H.z + plane.d;

        if (SFloat::IsZero(DIST_A) && SFloat::IsZero(DIST_B) && SFloat::IsZero(DIST_C) && SFloat::IsZero(DIST_D) &&
            SFloat::IsZero(DIST_E) && SFloat::IsZero(DIST_F) && SFloat::IsZero(DIST_G) && SFloat::IsZero(DIST_H) )
            return ESpaceRelation::E_Contained;
        else if ( SFloat::IsGreaterOrEquals(DIST_A, SFloat::_0) && SFloat::IsGreaterOrEquals(DIST_B, SFloat::_0) && SFloat::IsGreaterOrEquals(DIST_C, SFloat::_0) &&
                  SFloat::IsGreaterOrEquals(DIST_D, SFloat::_0) && SFloat::IsGreaterOrEquals(DIST_E, SFloat::_0) && SFloat::IsGreaterOrEquals(DIST_F, SFloat::_0) &&
                  SFloat::IsGreaterOrEquals(DIST_G, SFloat::_0) && SFloat::IsGreaterOrEquals(DIST_H, SFloat::_0) )
            return ESpaceRelation::E_PositiveSide;
        else if ( SFloat::IsLessOrEquals(DIST_A, SFloat::_0) && SFloat::IsLessOrEquals(DIST_B, SFloat::_0) &&
                  SFloat::IsLessOrEquals(DIST_C, SFloat::_0) && SFloat::IsLessOrEquals(DIST_D, SFloat::_0) &&
                  SFloat::IsLessOrEquals(DIST_E, SFloat::_0) && SFloat::IsLessOrEquals(DIST_F, SFloat::_0) &&
                  SFloat::IsLessOrEquals(DIST_G, SFloat::_0) && SFloat::IsLessOrEquals(DIST_H, SFloat::_0) )
            return ESpaceRelation::E_NegativeSide;
        else
            return ESpaceRelation::E_BothSides;
    }

    /// <summary>
    /// This method applies to the resident hexahedron the rotation defined by the provided rotation matrix
    /// around the coordinate axis centre.
    /// </summary>
    /// <param name="rotation">[IN] Rotation matrix which contais the rotation to be applied.</param>
    /// <returns>
    /// The rotated hexahedron.
    /// </returns>
    Hexahedron<VectorT> Rotate(const RotationMatrix3x3 &rotation) const
    {
        Hexahedron<VectorT> auxHexahedron = *this;
        SPoint::Rotate(rotation, rcast_z(&auxHexahedron, VectorT*), 8);
        return auxHexahedron;
    }

    /// <summary>
    /// This method transforms the resident hexahedron by applying the rotation contained in the
    /// provided rotation matrix around a pivot point (which acts as center of rotation).
    /// </summary>
    /// <param name="rotation">[IN] Rotation matrix which contains the rotation to be applied.</param>
    /// <param name="vPivot">[IN] The pivot point which the rotation will be accomplished around.</param>
    /// <returns>
    /// The rotated hexahedron.
    /// </returns>
    Hexahedron<VectorT> RotateWithPivot(const RotationMatrix3x3 &rotation, const VectorT &vPivot) const
    {
        Hexahedron<VectorT> auxHexahedron = *this;
        SPoint::RotateWithPivot(rotation, vPivot, rcast_z(&auxHexahedron, VectorT*), 8);
        return auxHexahedron;
    }

    /// <summary>
    /// This method performs a translation of the resident hexahedron given by the provided translation matrix.
    /// </summary>
    /// <param name="translation">[IN] Matrix which contains the translation to be applied.</param>
    /// <returns>
    /// The translated hexahedron.
    /// </returns>
    Hexahedron<VectorT> Translate(const TranslationMatrix<Matrix4x3> &translation) const
    {
        Hexahedron<VectorT> auxHexahedron = *this;
        SPoint::Translate(translation, rcast_z(&auxHexahedron, VectorT*), 8);
        return auxHexahedron;
    }

    /// <summary>
    /// This method performs a translation of the resident hexahedron given by the provided translation matrix.
    /// </summary>
    /// <param name="translation">[IN] Matrix which contains the translation to be applied.</param>
    /// <returns>
    /// The translated hexahedron.
    /// </returns>
    Hexahedron<VectorT> Translate(const TranslationMatrix<Matrix4x4> &translation) const
    {
        Hexahedron<VectorT> auxHexahedron = *this;
        SPoint::Translate(translation, rcast_z(&auxHexahedron, VectorT*), 8);
        return auxHexahedron;
    }

    /// <summary>
    /// This method scales the resident hexahedron by the scale contained in the provided scale matrix.
    /// </summary>
    /// <param name="scale">[IN] Matrix which contains the scale to be applied.</param>
    /// <returns>
    /// The scaled hexahedron.
    /// </returns>
    Hexahedron<VectorT> Scale(const ScalingMatrix3x3 &scale) const
    {
        Hexahedron<VectorT> auxHexahedron = *this;
        SPoint::Scale(scale, rcast_z(&auxHexahedron, VectorT*), 8);
        return auxHexahedron;
    }

    /// <summary>
    /// This method scales the resident hexahedron by the scale contained in the provided matrix,
    /// acting the provided vector as pivot of scale.
    /// </summary>
    /// <param name="scale">[IN] Matrix which contains the scale to be applied.</param>
    /// <param name="vPivot">[IN] The point which acts as pivot of the scale.</param>
    /// <returns>
    /// The scaled hexahedron.
    /// </returns>
    Hexahedron<VectorT> ScaleWithPivot(const ScalingMatrix3x3 &scale, const VectorT &vPivot) const
    {
        Hexahedron<VectorT> auxHexahedron = *this;
        SPoint::ScaleWithPivot(scale, vPivot, rcast_z(&auxHexahedron, VectorT*), 8);
        return auxHexahedron;
    }

    /// <summary>
    /// This method transforms the resident hexahedron applying the provided transformation matrix.
    /// </summary>
    /// <param name="transformation">[IN] Matrix which contains the transformation to be applied.</param>
    /// <returns>
    /// The transformed hexahedron.
    /// </returns>
    Hexahedron<VectorT> Transform(const TransformationMatrix<Matrix4x3> &transformation) const
    {
        Hexahedron<VectorT> auxHexahedron = *this;
        SPoint::Transform(transformation, rcast_z(&auxHexahedron, VectorT*), 8);
        return auxHexahedron;
    }

    /// <summary>
    /// This method transforms the resident hexahedron applying the provided transformation matrix.
    /// </summary>
    /// <param name="transformation">[IN] Matrix which contains the transformation to be applied.</param>
    /// <returns>
    /// The transformed hexahedron.
    /// </returns>
    Hexahedron<VectorT> Transform(const TransformationMatrix<Matrix4x4> &transformation) const
    {
        Hexahedron<VectorT> auxHexahedron = *this;
        SPoint::Transform(transformation, rcast_z(&auxHexahedron, VectorT*), 8);
        return auxHexahedron;
    }

    /// <summary>
    /// This method transforms the resident hexahedron applying the provided space conversion matrix.
    /// </summary>
    /// <param name="spaceConversion">[IN] Matrix which contains the space conversion transformation to be applied.</param>
    /// <returns>
    /// The converted hexahedron.
    /// </returns>
    Hexahedron<VectorT> Transform(const SpaceConversionMatrix &spaceConversion) const
    {
        Hexahedron<VectorT> auxHexahedron = *this;
        SPoint::Transform(spaceConversion, rcast_z(&auxHexahedron, VectorT*), 8);
        return auxHexahedron;
    }

    /// <summary>
    /// This method transforms the resident hexahedron applying the provided transformation matrix,
    /// acting the provided vector as pivot of transformation.
    /// </summary>
    /// <remarks>
    /// When using 4D vectors, the W component of the pivot point doesn't affect the result.
    /// </remarks>
    /// <param name="transformation">[IN] Matrix which contains the transformation to be applied.</param>
    /// <param name="vPivot">[IN] The point which acts as pivot of the transformation.</param>
    /// <returns>
    /// The transformed hexahedron.
    /// </returns>
    Hexahedron<VectorT> TransformWithPivot(const TransformationMatrix<Matrix4x3> &transformation, const VectorT &vPivot) const
    {
        Hexahedron<VectorT> auxHexahedron = *this;
        SPoint::TransformWithPivot(transformation, vPivot, rcast_z(&auxHexahedron, VectorT*), 8);
        return auxHexahedron;
    }

    /// <summary>
    /// This method transforms the resident hexahedron applying the provided transformation matrix,
    /// acting the provided vector as pivot of transformation.
    /// </summary>
    /// <remarks>
    /// When using 4D vectors, the W component of the pivot point doesn't affect the result.
    /// </remarks>
    /// <param name="transformation">[IN] Matrix which contains the transformation to be applied.</param>
    /// <param name="vPivot">[IN] The point which acts as pivot of the transformation.</param>
    /// <returns>
    /// A reference to the transformed hexahedron.
    /// </returns>
    Hexahedron<VectorT> TransformWithPivot(const TransformationMatrix<Matrix4x4> &transformation, const VectorT &vPivot) const
    {
        Hexahedron<VectorT> auxHexahedron = *this;
        SPoint::TransformWithPivot(transformation, vPivot, rcast_z(&auxHexahedron, VectorT*), 8);
        return auxHexahedron;
    }

    /// <summary>
    /// Checks if resident hexahedron intersects a given hexahedron.
    /// </summary>
    /// <remarks>
    /// If two or more vertices of an hexahedron concide (which would be a malformed hexahedron), the result is undefined.
    /// </remarks>
    /// <param name="hexahedron">[IN] Hexahedron which intersections with resident hexahedron will be checked.</param>
    /// <returns>
    /// A boolean value that indicates whether the hexahedron intersect or not.<br/>
    /// <br/>
    /// <b>True</b><br/>
    /// The hexahedrons intersect, including the following cases:
    /// - The hexahedrons coincide totally.
    /// - The hexahedrons share one vertex.
    /// - One hexahedron is contained in the other.
    /// - A vertex of one hexahedron is contained in the other hexahedron.
    /// - An edge of one hexahedron pierces the other hexahedron.
    ///
    /// <b>False</b><br/>
    /// The hexahedrons do not intersect.
    /// </returns>
    bool Intersection(const BaseHexahedron<VectorT> &hexahedron) const
    {
        // If all the vertices of the hexahedron coincide, it might be an erroneous figure
        Z_ASSERT_WARNING(this->A != this->B || this->A != this->C || this->A != this->D || this->A != this->E || this->A != this->F || this->A != this->G || this->A != this->G || this->A != this->H ||
                          this->B != this->C || this->B != this->D || this->B != this->E || this->B != this->F || this->B != this->G || this->B != this->H ||
                          this->C != this->D || this->C != this->E || this->C != this->F || this->C != this->G || this->C != this->H ||
                          this->D != this->E || this->D != this->F || this->D != this->G || this->D != this->H ||
                          this->E != this->F || this->E != this->G || this->E != this->H ||
                          this->F != this->G || this->F != this->H ||
                          this->G != this->H, "All the vertices of the hexahedron coincide, it might be an erroneous figure");
        Z_ASSERT_WARNING(hexahedron.A != hexahedron.B || hexahedron.A != hexahedron.C || hexahedron.A != hexahedron.D || hexahedron.A != hexahedron.E || hexahedron.A != hexahedron.F || hexahedron.A != hexahedron.G || hexahedron.A != hexahedron.H ||
                          hexahedron.B != hexahedron.C || hexahedron.B != hexahedron.D || hexahedron.B != hexahedron.E || hexahedron.B != hexahedron.F || hexahedron.B != hexahedron.G || hexahedron.B != hexahedron.H ||
                          hexahedron.C != hexahedron.D || hexahedron.C != hexahedron.E || hexahedron.C != hexahedron.F || hexahedron.C != hexahedron.G || hexahedron.C != hexahedron.H ||
                          hexahedron.D != hexahedron.E || hexahedron.D != hexahedron.F || hexahedron.D != hexahedron.G || hexahedron.D != hexahedron.H ||
                          hexahedron.E != hexahedron.F || hexahedron.E != hexahedron.G || hexahedron.E != hexahedron.H ||
                          hexahedron.F != hexahedron.G || hexahedron.F != hexahedron.H ||
                          hexahedron.G != hexahedron.H, "All the vertices of the input hexahedron coincide, it might be an erroneous figure");

        return ( this->Contains(hexahedron.A) || this->Contains(hexahedron.B) || this->Contains(hexahedron.C) || this->Contains(hexahedron.D) ||
                 this->Contains(hexahedron.E) || this->Contains(hexahedron.F) || this->Contains(hexahedron.G) || this->Contains(hexahedron.H) ||
                 LineSegment3D<VectorT>(this->A, this->B).Intersection(hexahedron) ||
                 LineSegment3D<VectorT>(this->B, this->C).Intersection(hexahedron) ||
                 LineSegment3D<VectorT>(this->C, this->D).Intersection(hexahedron) ||
                 LineSegment3D<VectorT>(this->D, this->A).Intersection(hexahedron) ||
                 LineSegment3D<VectorT>(this->E, this->F).Intersection(hexahedron) ||
                 LineSegment3D<VectorT>(this->F, this->G).Intersection(hexahedron) ||
                 LineSegment3D<VectorT>(this->G, this->H).Intersection(hexahedron) ||
                 LineSegment3D<VectorT>(this->H, this->E).Intersection(hexahedron) ||
                 LineSegment3D<VectorT>(this->A, this->E).Intersection(hexahedron) ||
                 LineSegment3D<VectorT>(this->B, this->H).Intersection(hexahedron) ||
                 LineSegment3D<VectorT>(this->C, this->G).Intersection(hexahedron) ||
                 LineSegment3D<VectorT>(this->D, this->F).Intersection(hexahedron) );
    }

    /// <summary>
    /// Projects resident hexahedron over a given plane, storing the resultant hexahedron in the provided one.
    /// </summary>
    /// <param name="plane">[IN] Plane where project resident hexahedron to. It must be normalized to obtain a correct result.
    /// If it is null, the behavior is undefined.</param>
    /// <returns>
    /// The projected hexahedron.
    /// </returns>
    Hexahedron<VectorT> ProjectToPlane(const Plane &plane) const
    {
        // If all the vertices of the hexahedron coincide, it might be an erroneous figure
        Z_ASSERT_WARNING(this->A != this->B || this->A != this->C || this->A != this->D || this->A != this->E || this->A != this->F || this->A != this->G || this->A != this->H ||
                          this->B != this->C || this->B != this->D || this->B != this->E || this->B != this->F || this->B != this->G || this->B != this->H ||
                          this->C != this->D || this->C != this->E || this->C != this->F || this->C != this->G || this->C != this->H ||
                          this->D != this->E || this->D != this->F || this->D != this->G || this->D != this->H ||
                          this->E != this->F || this->E != this->G || this->E != this->H ||
                          this->F != this->G || this->F != this->H ||
                          this->G != this->H, "All the vertices of the hexahedron coincide, it might be an erroneous figure");

        // The plane must not be null
        Z_ASSERT_WARNING(SFloat::IsNotZero(plane.a) || SFloat::IsNotZero(plane.b) || SFloat::IsNotZero(plane.c), "Input plane should not be null");

        return Hexahedron<VectorT>(   plane.PointProjection(this->A),
                                       plane.PointProjection(this->B),
                                       plane.PointProjection(this->C),
                                       plane.PointProjection(this->D),
                                       plane.PointProjection(this->E),
                                       plane.PointProjection(this->F),
                                       plane.PointProjection(this->G),
                                       plane.PointProjection(this->H));
    }

    /// <summary>
    /// Converts hexahedron into a string.
    /// </summary>
    /// <remarks>
    /// The format of the string is:<br/>
    /// "HX(a($A),b($B),c($C),d($D),e($E),f($F),g($G),h($H))".<br/>
    /// Where "$" means "string representation of attribute".
    /// </remarks>
    /// <returns>The string with the specified format.</returns>
    string_z ToString() const
    {
        return string_z("HX(a(") + this->A.ToString() + Z_L("),b(") + this->B.ToString() + Z_L("),c(") +
                                   this->C.ToString() + Z_L("),d(") + this->D.ToString() + Z_L("),e(") +
                                   this->E.ToString() + Z_L("),f(") + this->F.ToString() + Z_L("),g(") +
                                   this->G.ToString() + Z_L("),h(") + this->H.ToString() + Z_L("))");
    }


protected:

    /// <summary>
    /// Calculates if two points are in the same side of a plane defined by 3 points.
    /// </summary>
    /// <typeparam name="VectorParamT">Allowed types: BaseVector3, BaseVector4, Vector3, Vector4.</typeparam>
    /// <param name="vP1">[IN] The first point to check.</param>
    /// <param name="vP2">[IN] The second point to check.</param>
    /// <param name="vA">[IN] The first of the points that define the plane that will divide the space.</param>
    /// <param name="vB">[IN] The second of the points that define the plane that will divide the space.</param>
    /// <param name="vC">[IN] The third of the points that define the plane that will divide the space.</param>
    /// <returns>True if the two points belong to the same side; False otherwise.</returns>
    template <class VectorParamT>
    bool PointsInSameSideOfPlane(const VectorParamT &vP1, const VectorParamT &vP2,
                                        const VectorParamT &vA, const VectorParamT &vB, const VectorParamT &vC) const
    {
        Plane p(vA, vB, vC);

        const float_z &DIST_P1 = p.a * vP1.x + p.b * vP1.y + p.c * vP1.z + p.d;
        const float_z &DIST_P2 = p.a * vP2.x + p.b * vP2.y + p.c * vP2.z + p.d;

        return !SFloat::IsNegative(DIST_P1 * DIST_P2);
    }
};


// SPECIALIZATION EXPORTATIONS
// -----------------------------
#ifdef Z_MATH_MODULE_TEMPLATE_SPECIALIZATION_SYMBOLS

template class Z_MATH_MODULE_SYMBOLS Hexahedron<Vector3>;
template class Z_MATH_MODULE_SYMBOLS Hexahedron<Vector4>;

#endif // Z_MATH_MODULE_TEMPLATE_SPECIALIZATION_SYMBOLS

} // namespace z


#endif // __HEXAHEDRON__
