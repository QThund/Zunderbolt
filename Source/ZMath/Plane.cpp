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

#include "ZMath/Plane.h"

#include "ZMath/Vector3.h"
#include "ZMath/Vector4.h"
#include "ZMath/Matrix3x4.h"
#include "ZMath/Matrix4x3.h"
#include "ZMath/TranslationMatrix.h"
#include "ZMath/RotationMatrix3x3.h"
#include "ZMath/ScalingMatrix3x3.h"
#include "ZMath/TransformationMatrix.h"
#include "ZMath/SpaceConversionMatrix.h"
#include "ZMath/SAngle.h"
#include "ZMath/MathDefinitions.h"
#include "ZCommon/DataTypes/SVF32.h"


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
    
Plane::Plane()
{
}

Plane::Plane(const float_z fValueA, const float_z fValueB, const float_z fValueC, const float_z fValueD) : 
                                            a(fValueA), b(fValueB), c(fValueC), d(fValueD)
{
}

Plane::Plane(const float_z fValueAll) : a(fValueAll), b(fValueAll), c(fValueAll), d(fValueAll)
{
}

Plane::Plane(float_z* arValues)
{
    // Null pointer checkout
    Z_ASSERT_ERROR(arValues != null_z, "The input array must not be null");

    // Assignments
    this->a = arValues[0];
    this->b = arValues[1];
    this->c = arValues[2];
    this->d = arValues[3];
}

Plane::Plane(const vf32_z value)
{
    SVF32::Unpack(value, this->a, this->b, this->c, this->d);
}

Plane::Plane(const Vector3 &vPoint1, const Vector3 &vPoint2, const Vector3 &vPoint3)
{
    this->PlaneImp(vPoint1, vPoint2, vPoint3);
}

Plane::Plane(const Vector4 &vPoint1, const Vector4 &vPoint2, const Vector4 &vPoint3)
{
    this->PlaneImp(vPoint1, vPoint2, vPoint3);
}

template <class VectorT>
void Plane::PlaneImp(const VectorT &vPoint1, const VectorT &vPoint2, const VectorT &vPoint3)
{
    // If points coincide, the plane can't be determined
    Z_ASSERT_WARNING( vPoint1 != vPoint2 && vPoint2 != vPoint3 && vPoint3 != vPoint1, "Input points must not coincide");

    // Creates two vectors, to obtain the direction vector of the plane via cross product
    VectorT vAux1 = ( vPoint1 - vPoint2 ).CrossProduct( vPoint1 - vPoint3 );;

    // Checkout to avoid the possibility of tree colinear points.
    Z_ASSERT_WARNING(!vAux1.IsZero(), "Input points must not be colinear");

    // Plane equation
    *this = Plane( vAux1.x, vAux1.y, vAux1.z, -vAux1.DotProduct(vPoint1) ).Normalize();
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

bool Plane::operator==(const Plane &plane) const
{
    return ( SFloat::AreEqual(plane.a, this->a) && SFloat::AreEqual(plane.b, this->b) &&
                SFloat::AreEqual(plane.c, this->c) && SFloat::AreEqual(plane.d, this->d) );
}

bool Plane::operator!=(const Plane &plane) const
{
    return !(*this == plane);
}

Plane Plane::operator*(const float_z fScalar) const
{
    return Plane(this->a * fScalar, this->b * fScalar, this->c * fScalar, this->d * fScalar);
}

// Left float product
Plane operator*(const float_z fScalar, const Plane &plane)
{
    return Plane(plane.a * fScalar, plane.b * fScalar, plane.c * fScalar, plane.d * fScalar);
}

Plane Plane::operator/(const float_z fScalar) const
{
    Z_ASSERT_WARNING(fScalar != SFloat::_0, "Input value must not equal zero");

    const float_z &DIVISOR = SFloat::_1/fScalar;

    return Plane(this->a * DIVISOR, this->b * DIVISOR, this->c * DIVISOR, this->d * DIVISOR);
}

Plane& Plane::operator*=(const float_z fScalar)
{
    this->a *= fScalar;
    this->b *= fScalar;
    this->c *= fScalar;
    this->d *= fScalar;

    return *this;
}

Plane& Plane::operator/=(const float_z fScalar)
{
    // Checkout to avoid division by 0
    Z_ASSERT_WARNING(fScalar != SFloat::_0, "Input value must not equal zero");

    const float_z &DIVISOR = SFloat::_1/fScalar;

    this->a *= DIVISOR;
    this->b *= DIVISOR;
    this->c *= DIVISOR;
    this->d *= DIVISOR;

    return *this;
}

Plane Plane::operator-() const
{
    return Plane(-this->a, -this->b, -this->c, this->d);
}

Plane Plane::Normalize() const
{
    // Checkout to avoid division by zero.
    Z_ASSERT_WARNING(this->GetLength() != SFloat::_0, "A plane whose length equals zero cannot be normalized, this will produce a division by zero");

    float_z fInvDivisor = SFloat::_1 / this->GetLength();

    return Plane(this->a * fInvDivisor, this->b * fInvDivisor, this->c * fInvDivisor, this->d * fInvDivisor);
}

float_z Plane::DotProduct(const Vector3 &vVector) const
{
    return this->DotProductImp(vVector);
}

float_z Plane::DotProduct(const Vector4 &vVector) const
{
    return this->DotProductImp(vVector);
}

float_z Plane::DotProduct(const Plane &plane) const
{
    return plane.a * this->a + plane.b * this->b + plane.c * this->c;
}

float_z Plane::AngleBetween(const Vector3 &vVector) const
{
    return this->AngleBetweenImp(vVector);
}

float_z Plane::AngleBetween(const Vector4 &vVector) const
{
    return this->AngleBetweenImp(vVector);
}

float_z Plane::AngleBetween(const Plane &plane) const
{
    // When the length of a plane equals zero, the calculated angle is not correct
    Z_ASSERT_WARNING( SFloat::IsNotZero(this->GetSquaredLength()) && !(SFloat::IsZero(plane.a) && SFloat::IsZero(plane.b) && SFloat::IsZero(plane.c)), 
               "When the length of a plane equals zero, the calculated angle is not correct" );

    float_z DOT = this->DotProduct(plane);

    // Sometimes the result of the dot product is not accurate and must be clampped [-1, 1]
    if(DOT > SFloat::_1)
        DOT = SFloat::_1;
    else if(DOT < -SFloat::_1)
        DOT = -SFloat::_1;

    float_z fAngle = acos_z(DOT);

    Z_ASSERT_WARNING( !SFloat::IsNaN(fAngle), "The resultant angle is NAN" );
    
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        // If angles are specified in degrees, then converts angle to degrees
        fAngle = SAngle::RadiansToDegrees(fAngle);
    #endif

    return fAngle;
}

Vector3 Plane::PointProjection(const Vector3 &vPoint) const
{
    return this->PointProjectionImp(vPoint);
}

Vector4 Plane::PointProjection(const Vector4 &vPoint) const
{
    Vector4 vAux = this->PointProjectionImp(vPoint);
    vAux.w = vPoint.w;
    return vAux;
}

bool Plane::Contains(const Vector3 &vPoint) const
{
    return this->ContainsImp(vPoint);
}

bool Plane::Contains(const Vector4 &vPoint) const
{
    return this->ContainsImp(vPoint);
}

float_z Plane::GetLength() const
{
    return sqrt_z(this->a * this->a + this->b * this->b + this->c * this->c);
}

float_z Plane::GetSquaredLength() const
{
    return this->a * this->a + this->b * this->b + this->c * this->c;
}

Vector3 Plane::GetNormal() const
{
    return Vector3(this->a, this->b, this->c);
}

float_z Plane::PointDistance(const Vector3 &vPoint) const
{
    return PointDistanceImp(vPoint);
}

float_z Plane::PointDistance(const Vector4 &vPoint) const
{
    return PointDistanceImp(vPoint);
}

EIntersections Plane::IntersectionPoint(const Plane &plane1, const Plane &plane2, Vector3 &vIntersection) const
{
    return IntersectionPointImp(plane1, plane2, vIntersection);
}

EIntersections Plane::IntersectionPoint(const Plane &plane1, const Plane &plane2, Vector4 &vIntersection) const
{
    EIntersections eNumIntersections = IntersectionPointImp(plane1, plane2, vIntersection);
    return eNumIntersections;
}

ESpaceRelation Plane::SpaceRelation(const Plane &plane) const
{
    // It's impossible to calculate the spacial relation for a null plane
    Z_ASSERT_WARNING( !(SFloat::IsZero(this->a) && SFloat::IsZero(this->b) && SFloat::IsZero(this->c)), "It's impossible to calculate the spacial relation for a null plane" );
    Z_ASSERT_WARNING( !(SFloat::IsZero(plane.a) && SFloat::IsZero(plane.b) && SFloat::IsZero(plane.c)), "It's impossible to calculate the spacial relation for a null plane" );

    // Cross product: checks if planes are parallel or coincident
    if (SFloat::IsZero(plane.b * this->c - plane.c * this->b) &&
        SFloat::IsZero(plane.c * this->a - plane.a * this->c) &&
        SFloat::IsZero(plane.a * this->b - plane.b * this->a))
    {
        if (plane == *this) // They are the same plane.
            return ESpaceRelation::E_Contained;
        else if (SFloat::IsNegative(plane.d - this->d))
            return ESpaceRelation::E_NegativeSide;
        else
            return ESpaceRelation::E_PositiveSide;
    }
    else // Are not parallel
        return ESpaceRelation::E_BothSides;
}

Plane Plane::Rotate(const RotationMatrix3x3 &rotation) const
{
    Vector3 vAux = this->GetNormal().Transform(rotation);

    return Plane(vAux.x, vAux.y, vAux.z, this->d);
}

Plane Plane::Rotate(const Quaternion &qRotation) const
{
    Vector3 vAux = this->GetNormal().Transform(qRotation);

    return Plane(vAux.x, vAux.y, vAux.z, this->d);
}

Plane Plane::Scale(const ScalingMatrix3x3 &scale) const
{
    // None of the scale values should equal zero
    Z_ASSERT_WARNING( scale.ij[0][0] != SFloat::_0 && scale.ij[1][1] != SFloat::_0 && scale.ij[2][2] != SFloat::_0, "None of the scale values should equal zero, this will cause a division by zero" );

    return Plane(this->a / scale.ij[0][0], this->b / scale.ij[1][1], this->c / scale.ij[2][2], this->d)
            .Normalize();
}

Plane Plane::Scale(const Vector3 &vScale) const
{
    // None of the scale values should equal zero
    Z_ASSERT_WARNING( vScale.x != SFloat::_0 && vScale.y != SFloat::_0 && vScale.z != SFloat::_0, "None of the scale values should equal zero, this will cause a division by zero" );

    return Plane(this->a / vScale.x, this->b / vScale.y, this->c / vScale.z, this->d)
            .Normalize();
}

Plane Plane::Scale(const float_z fScaleX, const float_z fScaleY, const float_z fScaleZ) const
{
    // None of the scale values should equal zero
    Z_ASSERT_WARNING( fScaleX != SFloat::_0 && fScaleY != SFloat::_0 && fScaleZ != SFloat::_0, "None of the scale values should equal zero, this will cause a division by zero" );

    return Plane(this->a / fScaleX, this->b / fScaleY, this->c / fScaleZ, this->d)
            .Normalize();
}

Plane Plane::Translate(const TranslationMatrix4x3 &translation) const
{
    return Plane(this->a,
                 this->b,
                 this->c,
                 this->d - (this->a * translation.ij[3][0] + this->b * translation.ij[3][1] + this->c * translation.ij[3][2]));
}

Plane Plane::Translate(const TranslationMatrix4x4 &translation) const
{
    return Plane(this->a,
                 this->b,
                 this->c,
                 this->d - (this->a * translation.ij[3][0] + this->b * translation.ij[3][1] + this->c * translation.ij[3][2]));
}

Plane Plane::Translate(const Vector3 &vTranslation) const
{
    return Plane(this->a,
                 this->b,
                 this->c,
                 this->d - (this->a * vTranslation.x + this->b * vTranslation.y + this->c * vTranslation.z));
}

Plane Plane::Translate(const Vector4 &vTranslation) const
{
    return Plane(this->a,
                 this->b,
                 this->c,
                 this->d - (this->a * vTranslation.x + this->b * vTranslation.y + this->c * vTranslation.z));
}

Plane Plane::Translate(const float_z fTranslationX, const float_z fTranslationY, const float_z fTranslationZ) const
{
    return Plane(this->a,
                 this->b,
                 this->c,
                 this->d - (this->a * fTranslationX + this->b * fTranslationY + this->c * fTranslationZ));
}

Plane Plane::Transform(const TransformationMatrix4x3 &transformation) const
{
    // Explanation:
    //
    // Let it be P a plane and A a point of the plane so the cartesian equation of the plane would be: PxAx + PyAy + PzAz + PwAw = 0.
    //
    // We can write it as vectors: P * A = 0
    // Or as matrices: P * At = 0 (note that the matrix A must be transposed to be multiplied by the matrix P, so they are 1x4 * 4x1)
    //
    //                  [Ax]
    //  [Px Py Pz Pw] * [Ay] = 0
    //                  [Az]
    //                  [Aw]
    //
    // Note: If you change the order of the operands and transpose P instead of A, it doesn't affect the result because, in the end,
    //       the only change is that the transformation matrix is inverted and transposed in the opposite order, which doesn't affect
    //       invertible matrices (as affine transformation matrices are).
    //
    // Now we want to find a plane P', which results of transforming P by a transformation matrix M, for which every point A transformed
    // by M fulfils the equation:
    //
    // P' * (A * M)t = 0
    //
    // So using both equations:
    //
    // P' * (A * M)t == 0 == P * At     -->    P' * (A * M)t == P * At
    //
    // And expanding the transposition (note that transposing a product of matrices inverts the operands' order):
    //
    // P' * Mt * At == P * At    -->    P' * Mt == P    -->    P' == P * Mt^-1
    //
    // Finally we have that P' equals P multiplied by the inverse of the transpose of the original transformation matrix
    // See also: http://www.opengl.org/discussion_boards/showthread.php/159564-Clever-way-to-transform-plane-by-matrix

    Matrix4x3 inverse = transformation.Invert();

    // The product is implemented using the transpose of the inverted transformation
    return Plane(this->a * inverse.ij[0][0] + this->b * inverse.ij[0][1] + this->c * inverse.ij[0][2],
                 this->a * inverse.ij[1][0] + this->b * inverse.ij[1][1] + this->c * inverse.ij[1][2],
                 this->a * inverse.ij[2][0] + this->b * inverse.ij[2][1] + this->c * inverse.ij[2][2],
                 this->a * inverse.ij[3][0] + this->b * inverse.ij[3][1] + this->c * inverse.ij[3][2] + this->d)
                  .Normalize();
}

Plane Plane::Transform(const TransformationMatrix4x4 &transformation) const
{
    // Explanation:
    //
    // Let it be P a plane and A a point of the plane so the cartesian equation of the plane would be: PxAx + PyAy + PzAz + PwAw = 0.
    //
    // We can write it as vectors: P * A = 0
    // Or as matrices: P * At = 0 (note that the matrix A must be transposed to be multiplied by the matrix P, so they are 1x4 * 4x1)
    //
    //                  [Ax]
    //  [Px Py Pz Pw] * [Ay] = 0
    //                  [Az]
    //                  [Aw]
    //
    // Note: If you change the order of the operands and transpose P instead of A, it doesn't affect the result because, in the end,
    //       the only change is that the transformation matrix is inverted and transposed in the opposite order, which doesn't affect
    //       invertible matrices (as affine transformation matrices are).
    //
    // Now we want to find a plane P', which results of transforming P by a transformation matrix M, for which every point A transformed
    // by M fulfils the equation:
    //
    // P' * (A * M)t = 0
    //
    // So using both equations:
    //
    // P' * (A * M)t == 0 == P * At     -->    P' * (A * M)t == P * At
    //
    // And expanding the transposition (note that transposing a product of matrices inverts the operands' order):
    //
    // P' * Mt * At == P * At    -->    P' * Mt == P    -->    P' == P * Mt^-1
    //
    // Finally we have that P' equals P multiplied by the inverse of the transpose of the original transformation matrix
    // See also: http://www.opengl.org/discussion_boards/showthread.php/159564-Clever-way-to-transform-plane-by-matrix

    Matrix4x4 inverse = transformation.Invert();

    // The product is implemented using the transpose of the inverted transformation
    return Plane(this->a * inverse.ij[0][0] + this->b * inverse.ij[0][1] + this->c * inverse.ij[0][2],
                 this->a * inverse.ij[1][0] + this->b * inverse.ij[1][1] + this->c * inverse.ij[1][2],
                 this->a * inverse.ij[2][0] + this->b * inverse.ij[2][1] + this->c * inverse.ij[2][2],
                 this->a * inverse.ij[3][0] + this->b * inverse.ij[3][1] + this->c * inverse.ij[3][2] + this->d)
                 .Normalize();
}

Plane Plane::Transform(const SpaceConversionMatrix &spaceConversion) const
{
    Matrix4x4 inverse = spaceConversion.Invert();

    // The product is implemented using the transpose of m
    return Plane(this->a * inverse.ij[0][0] + this->b * inverse.ij[0][1] + this->c * inverse.ij[0][2] + this->d * inverse.ij[0][3],
                 this->a * inverse.ij[1][0] + this->b * inverse.ij[1][1] + this->c * inverse.ij[1][2] + this->d * inverse.ij[1][3],
                 this->a * inverse.ij[2][0] + this->b * inverse.ij[2][1] + this->c * inverse.ij[2][2] + this->d * inverse.ij[2][3],
                 this->a * inverse.ij[3][0] + this->b * inverse.ij[3][1] + this->c * inverse.ij[3][2] + this->d * inverse.ij[3][3])
                 .Normalize();
}

Plane Plane::RotateWithPivot(const Quaternion &qRotation, const Vector3 &vPivot) const
{
    return this->RotateWithPivotImp(qRotation, vPivot);
}

Plane Plane::RotateWithPivot(const Quaternion &qRotation, const Vector4 &vPivot) const
{
    return this->RotateWithPivotImp(qRotation, vPivot);
}

Plane Plane::RotateWithPivot(const RotationMatrix3x3 &rotation, const Vector3 &vPivot) const
{
    return this->RotateWithPivotImp(rotation, vPivot);
}

Plane Plane::RotateWithPivot(const RotationMatrix3x3 &rotation, const Vector4 &vPivot) const
{
    return this->RotateWithPivotImp(rotation, vPivot);
}

Plane Plane::ScaleWithPivot(const Vector3 &vScale, const Vector3 &vPivot) const
{
    return this->ScaleWithPivotImp(vScale, vPivot);
}

Plane Plane::ScaleWithPivot(const Vector3 &vScale, const Vector4 &vPivot) const
{
    return this->ScaleWithPivotImp(vScale, vPivot);
}

Plane Plane::ScaleWithPivot(const float_z fScaleX, const float_z fScaleY, const float_z fScaleZ, const Vector3 &vPivot) const
{
    return this->ScaleWithPivotImp(fScaleX, fScaleY, fScaleZ, vPivot);
}

Plane Plane::ScaleWithPivot(const float_z fScaleX, const float_z fScaleY, const float_z fScaleZ, const Vector4 &vPivot) const
{
    return this->ScaleWithPivotImp(fScaleX, fScaleY, fScaleZ, vPivot);
}

Plane Plane::ScaleWithPivot(const ScalingMatrix3x3 &scale, const Vector3 &vPivot) const
{
    return this->ScaleWithPivotImp(scale, vPivot);
}

Plane Plane::ScaleWithPivot(const ScalingMatrix3x3 &scale, const Vector4 &vPivot) const
{
    return this->ScaleWithPivotImp(scale, vPivot);
}

Plane Plane::TransformWithPivot(const TransformationMatrix4x3 &transformation, const Vector3 &vPivot) const
{
    return this->TransformWithPivotImp(transformation, vPivot);
}

Plane Plane::TransformWithPivot(const TransformationMatrix4x3 &transformation, const Vector4 &vPivot) const
{
    return this->TransformWithPivotImp(transformation, vPivot);
}

Plane Plane::TransformWithPivot(const TransformationMatrix4x4 &transformation, const Vector3 &vPivot) const
{
    return this->TransformWithPivotImp(transformation, vPivot);
}

Plane Plane::TransformWithPivot(const TransformationMatrix4x4 &transformation, const Vector4 &vPivot) const
{
    return this->TransformWithPivotImp(transformation, vPivot);
}

string_z Plane::ToString() const
{
    static const string_z STRING_PREFIX("PL(");
    static const string_z STRING_COMMA(",");
    static const string_z STRING_END(")");

    string_z strOutput = STRING_PREFIX;
    strOutput.Append(this->a);
    strOutput.Append(STRING_COMMA);
    strOutput.Append(this->b);
    strOutput.Append(STRING_COMMA);
    strOutput.Append(this->c);
    strOutput.Append(STRING_COMMA);
    strOutput.Append(this->d);
    strOutput.Append(STRING_END);

    return strOutput;
}

template <class VectorT>
float_z Plane::DotProductImp(const VectorT &vVector) const
{
    return vVector.x * this->a + vVector.y * this->b + vVector.z * this->c;
}

template <class VectorT>
float_z Plane::AngleBetweenImp(const VectorT &vVector) const
{
    // When the length of either the plane or the vector equals zero, the calculated angle is not correct
    Z_ASSERT_WARNING( SFloat::IsNotZero(this->GetSquaredLength()) && !(SFloat::IsZero(vVector.x) && SFloat::IsZero(vVector.y) && SFloat::IsZero(vVector.z)), 
               "When the length of either the plane or the vector equals zero, the calculated angle is not correct" );

    // Length of plane equals one due to plane is supposed to be normalized.
    const float_z &DOT_LENGTH = sqrt_z(vVector.x*vVector.x + vVector.y*vVector.y + vVector.z*vVector.z);

    // Checkout to avoid division by zero.
    Z_ASSERT_WARNING(DOT_LENGTH != SFloat::_0, "Input vector must not be null, this will produce a division by zero");

    float_z DOT = this->DotProduct(vVector)/DOT_LENGTH;

    // Sometimes the result of the dot product is not accurate and must be clampped [-1, 1]
    if(DOT > SFloat::_1)
        DOT = SFloat::_1;
    else if(DOT < -SFloat::_1)
        DOT = -SFloat::_1;

    float_z fAngle = acos_z(DOT);

    Z_ASSERT_WARNING( !SFloat::IsNaN(fAngle), "The resultant angle is NAN" );

    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        // If angles are specified in degrees, then converts angle to degrees
        fAngle = SAngle::RadiansToDegrees(fAngle);
    #endif

    return fAngle;
}

template <class VectorT>
Plane Plane::RotateWithPivotImp(const Quaternion &qRotation, const VectorT &vPivot) const
{
    return this->Translate(-vPivot)
                .Rotate(qRotation)
                .Translate(vPivot);
}

template <class VectorT>
Plane Plane::RotateWithPivotImp(const RotationMatrix3x3 &rotation, const VectorT &vPivot) const
{
    return this->Translate(-vPivot)
                .Rotate(rotation)
                .Translate(vPivot);
}

template <class VectorT>
Plane Plane::ScaleWithPivotImp(const Vector3 &vScale, const VectorT &vPivot) const
{
    return this->Translate(-vPivot)
                .Scale(vScale)
                .Translate(vPivot);
}

template <class VectorT>
Plane Plane::ScaleWithPivotImp(const float_z fScaleX, const float_z fScaleY, const float_z fScaleZ, const VectorT &vPivot) const
{
    return this->Translate(-vPivot)
                .Scale(fScaleX, fScaleY, fScaleZ)
                .Translate(vPivot);
}

template <class VectorT>
Plane Plane::ScaleWithPivotImp(const ScalingMatrix3x3 &scale, const VectorT &vPivot) const
{
    return this->Translate(-vPivot)
                .Scale(scale)
                .Translate(vPivot);
}

template <class MatrixT, class VectorT>
Plane Plane::TransformWithPivotImp(const MatrixT &transformation, const VectorT &vPivot) const
{
    return this->Translate(-vPivot)
                .Transform(transformation)
                .Translate(vPivot);
}

template <class VectorT>
VectorT Plane::PointProjectionImp(const VectorT &vPoint) const
{
    // The plane shouldn't be null
    Z_ASSERT_WARNING( !(SFloat::IsZero(this->a) && SFloat::IsZero(this->b) && SFloat::IsZero(this->c)), "The plane should not be null, the result will be incorrect" );
        
    // [SMELL] Thund: Can this line be replaced with a dot product + d?
    const float_z &PROJ = -(this->a * vPoint.x + this->b * vPoint.y + this->c * vPoint.z + this->d);

    // [SMELL] Thund: Can this line contain all the operations so no 2 constructor calls are performed?
    VectorT vProjection;
    vProjection.x = PROJ * this->a  + vPoint.x;
    vProjection.y = PROJ * this->b  + vPoint.y;
    vProjection.z = PROJ * this->c  + vPoint.z;

    return vProjection;
}

template <class VectorT>
bool Plane::ContainsImp(const VectorT &vPoint) const
{
    // The plane should not be null
    Z_ASSERT_WARNING( !(SFloat::IsZero(this->a) && SFloat::IsZero(this->b) && SFloat::IsZero(this->c)), "The plane should not be null, the result will be incorrect" );

    return SFloat::IsZero(this->a * vPoint.x + this->b * vPoint.y + this->c * vPoint.z + this->d);
}

template <class VectorT>
float_z Plane::PointDistanceImp(const VectorT &vPoint) const
{
    // The plane should not be null
    Z_ASSERT_WARNING( !(SFloat::IsZero(this->a) && SFloat::IsZero(this->b) && SFloat::IsZero(this->c)), "The plane should not be null, the result will be incorrect" );

    return SFloat::Abs(this->a * vPoint.x + this->b * vPoint.y + this->c * vPoint.z + this->d);
}

template <class VectorT>
EIntersections Plane::IntersectionPointImp(const Plane &plane1, const Plane &plane2, VectorT &vIntersection) const
{
    // None of the planes should be null
    Z_ASSERT_WARNING( !(SFloat::IsZero(this->a) && SFloat::IsZero(this->b) && SFloat::IsZero(this->c)), "The plane should not be null, the result will be incorrect" );
    Z_ASSERT_WARNING( !(SFloat::IsZero(plane1.a) && SFloat::IsZero(plane1.b) && SFloat::IsZero(plane1.c)), "Input planes should not be null, the result will be incorrect" );
    Z_ASSERT_WARNING( !(SFloat::IsZero(plane2.a) && SFloat::IsZero(plane2.b) && SFloat::IsZero(plane2.c)), "Input planes should not be null, the result will be incorrect" );

    // Solved by Cramer method.
    const float_z& DET_C = this->a * plane1.b * plane2.c + this->b * plane1.c * plane2.a + this->c * plane1.a * plane2.b -
                          (this->c * plane1.b * plane2.a + this->a * plane1.c * plane2.b + this->b * plane1.a * plane2.c);
    const float_z& DET_X = this->c * plane1.b * plane2.d + this->d * plane1.c * plane2.b + this->b * plane1.d * plane2.c -
                          (this->d * plane1.b * plane2.c + this->b * plane1.c * plane2.d + this->c * plane1.d * plane2.b);
    const float_z& DET_Y = this->c * plane1.d * plane2.a + this->a * plane1.c * plane2.d + this->d * plane1.a * plane2.c -
                          (this->a * plane1.d * plane2.c + this->d * plane1.c * plane2.a + this->c * plane1.a * plane2.d);
    const float_z& DET_Z = this->d * plane1.b * plane2.a + this->a * plane1.d * plane2.b + this->b * plane1.a * plane2.d -
                          (this->a * plane1.b * plane2.d + this->b * plane1.d * plane2.a + this->d * plane1.a * plane2.b);

    if (!SFloat::IsZero(DET_C)) // A range = 3, A* range = 3: Compatible system
    {
        const float_z& INV_DET_C = SFloat::_1/DET_C;

        vIntersection.x = DET_X * INV_DET_C;
        vIntersection.y = DET_Y * INV_DET_C;
        vIntersection.z = DET_Z * INV_DET_C;

        return EIntersections::E_One;
    }
    else if (SFloat::IsZero(DET_X) && SFloat::IsZero(DET_Y) && SFloat::IsZero(DET_Z)) // A range < 3, A* range < 3
    {
        // A range = 2, A* range < 3: Undetermined compatible system
        if (SFloat::IsNotZero(this->a  * plane1.b - this->b  * plane1.a) ||
            SFloat::IsNotZero(this->a  * plane1.c - this->c  * plane1.a) ||
            SFloat::IsNotZero(this->a  * plane2.b - this->b  * plane2.a) ||
            SFloat::IsNotZero(this->a  * plane2.c - this->c  * plane2.a) ||
            SFloat::IsNotZero(this->b  * plane1.c - this->c  * plane1.b) ||
            SFloat::IsNotZero(this->b  * plane2.c - this->c  * plane2.b) ||
            SFloat::IsNotZero(plane1.a * plane2.b - plane1.b * plane2.a) ||
            SFloat::IsNotZero(plane1.a * plane2.c - plane1.c * plane2.a) ||
            SFloat::IsNotZero(plane1.b * plane2.c - plane1.c * plane2.b))

            return EIntersections::E_Infinite;
        else //// A range = 1, A* range < 3
        {
            if (*this == plane1 && *this == plane2) // Coincident planes (A* range = 1)
                return EIntersections::E_Infinite;
            else // Incompatible system (A* range = 2)
                return EIntersections::E_None;
        }
    }
    else // A range < 3, A* range = 3: Incompatible system
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

const Plane& Plane::GetNullPlane()
{
    static const Plane NULLPLANE(SFloat::_0,  SFloat::_0,  SFloat::_0,  SFloat::_0);
    return NULLPLANE;
}

const Plane& Plane::GetPlaneZX()
{
    static const Plane PLANEZX(SFloat::_0,  SFloat::_1,  SFloat::_0,  SFloat::_0);
    return PLANEZX;
}

const Plane& Plane::GetPlaneXY()
{
    static const Plane PLANEXY(SFloat::_0,  SFloat::_0,  SFloat::_1,  SFloat::_0);
    return PLANEXY;
}

const Plane& Plane::GetPlaneYZ()
{
    static const Plane PLANEYZ(SFloat::_1,  SFloat::_0,  SFloat::_0,  SFloat::_0);
    return PLANEYZ;
}

} // namespace z
