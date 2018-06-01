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

#ifndef __DUALQUATERNION__
#define __DUALQUATERNION__

#include "BaseDualQuaternion.h"

#include "ZCommon/DataTypes/SFloat.h"



namespace z
{

// Forward declarations
class BaseVector3;
class BaseVector4;


/// <summary>
/// Class which implements the basic functionality of a dual quaternion.
/// </summary>
/// <remarks>
/// A dual quaternion is a complex number with two components, a non-dual component and a dual one.<br/>
/// e.g. \f$ r + d\varepsilon \f$.<br/>
/// Both components (r and d) of a dual quaternion are (regular) quaternions.<br/>
/// The dual unit, called epsilon (\f$ \varepsilon \f$), verifies \f$ \varepsilon^2=0 \f$. Then, a full quaternion looks like:
/// <br/>
/// \f$ r_w + r_xi + r_yj + r_zk + (d_w + d_xi + d_yj + d_zk)\varepsilon\f$
/// <br/>
/// We'll normally employ it to represent and execute rigid transformations, that is, transformations which involves
/// one rotation and one translation, without deforming the transformed solid (which acts as a rigid solid).<br/>
/// This class has been included for experimental purposes only. Use it at your own risk.
/// </remarks>
class Z_MATH_MODULE_SYMBOLS DualQuaternion : public BaseDualQuaternion
{
    // FRIENDS
    // ---------------
public:

    /// <summary>
    /// Multiply by scalar operator. All dual quaternion components are multiplied by the scalar.
    /// </summary>
    /// <param name="fScalar">[IN] The scalar factor.</param>
    /// <param name="dualQuat">[IN] The dual quaternion factor.</param>
    /// <returns>
    /// The resultant dual quaternion.
    /// </returns>
    friend DualQuaternion Z_MATH_MODULE_SYMBOLS operator*(const float_z fScalar, const DualQuaternion &dualQuat);


    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor.
    /// </summary>
    DualQuaternion();

    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="dualQuat">[IN] The dual quaternion from which we want to create a copy in the resident dual quaternion.</param>
    DualQuaternion(const DualQuaternion &dualQuat);

    /// <summary>
    /// Base type constructor.
    /// </summary>
    /// <param name="dualQuat">[IN] The dual quaternion from which we want to create a copy in the resident dual quaternion.</param>
    DualQuaternion(const BaseDualQuaternion &dualQuat);

    /// <summary>
    /// Constructor from two regular quaternions.
    /// </summary>
    /// <param name="qReal">[IN] Regular quaternion to define non-dual part.</param>
    /// <param name="qDual">[IN] Regular quaternion to define dual part.</param>
    DualQuaternion(const BaseQuaternion &qReal, const BaseQuaternion &qDual);

    /// <summary>
    /// Constructor from a regular quaternion which represents a rotation and a vector which represents a translation.
    /// </summary>
    /// <remarks>
    /// The rotation regular quaternion is built from an angle (\f$\theta\f$) and a unit vector \f$\vec{n}(n_x, n_y, n_z)\f$
    /// in the direction of the rotation axis as follows:
    /// <br/>
    /// \f$ q(x, y, z, w) = (n_xsin(\frac{\theta}{2}), n_ysin(\frac{\theta}{2}), n_zsin(\frac{\theta}{2}), cos(\frac{\theta}{2}))\f$,
    /// <br/>
    /// and the dual quaternion will be:
    /// <br/>
    /// \f$\hat{q}_r = (n_xsin(\frac{\theta}{2}), n_ysin(\frac{\theta}{2}), n_zsin(\frac{\theta}{2}), cos(\frac{\theta}{2})) (0, 0, 0, 0)\f$.
    /// <br/>
    /// In the other side, the translation \f$(d_x, d_y, d_z)\f$ is directly converted to a dual quaternion as follows:
    /// <br/>
    /// \f$\hat{q}_d = (0, 0, 0, 1) (\frac{d_x}{2}, \frac{d_y}{2}, \frac{d_z}{2}, 0)\f$.
    /// <br/>
    /// Our transformation dual quaternion is given by the product of the translation dual quaternion by
    /// the rotation dual quaternion, taking into account that the transfomation is done as follows:<br/>
    /// FIRST ROTATION THEN TRANSLATION.
    /// </remarks>
    /// <param name="qRotation">[IN] The quaternion that keeps the rotation.</param>
    /// <param name="vTranslation">[IN] The vector which represents the translation.</param>
    DualQuaternion(const BaseQuaternion &qRotation, const BaseVector3 &vTranslation);

    /// <summary>
    /// Constructor from a regular quaternion which represents a rotation and a vector which represents a translation.
    /// </summary>
    /// <remarks>
    /// The rotation regular quaternion is built from an angle (\f$\theta\f$) and a unit vector \f$\vec{n}(n_x, n_y, n_z)\f$
    /// in the direction of the rotation axis as follows:
    /// <br/>
    /// \f$ q(x, y, z, w) = (n_xsin(\frac{\theta}{2}), n_ysin(\frac{\theta}{2}), n_zsin(\frac{\theta}{2}), cos(\frac{\theta}{2}))\f$,
    /// <br/>
    /// and the dual quaternion will be:
    /// <br/>
    /// \f$\hat{q}_r = (n_xsin(\frac{\theta}{2}), n_ysin(\frac{\theta}{2}), n_zsin(\frac{\theta}{2}), cos(\frac{\theta}{2})) (0, 0, 0, 0)\f$.
    /// <br/>
    /// In the other side, the translation \f$(d_x, d_y, d_z)\f$ is directly converted to a dual quaternion as follows:
    /// <br/>
    /// \f$\hat{q}_d = (0, 0, 0, 1) (\frac{d_x}{2}, \frac{d_y}{2}, \frac{d_z}{2}, 0)\f$.
    /// <br/>
    /// Our transformation dual quaternion is given by the product of the translation dual quaternion by
    /// the rotation dual quaternion, taking into account that the transfomation is done as follows:<br/>
    /// FIRST ROTATION THEN TRANSLATION.<br/>
    /// Remember that the quaternion must be normalized to represent the rotation properly.
    /// </remarks>
    /// <param name="qRotation">[IN] The quaternion that keeps the rotation.</param>
    /// <param name="vTranslation">[IN] The vector which represents the translation.</param>
    DualQuaternion(const BaseQuaternion &qRotation, const BaseVector4 &vTranslation);

    /// <summary>
    /// Constructor from a regular quaternion which represents a rotation and a vector which represents a translation.
    /// </summary>
    /// <remarks>
    /// The rotation regular quaternion is built from an angle (\f$\theta\f$) and a unit vector \f$\vec{n}(n_x, n_y, n_z)\f$
    /// in the direction of the rotation axis as follows:
    /// <br/>
    /// \f$ q(x, y, z, w) = (n_xsin(\frac{\theta}{2}), n_ysin(\frac{\theta}{2}), n_zsin(\frac{\theta}{2}), cos(\frac{\theta}{2}))\f$,
    /// <br/>
    /// and the dual quaternion will be:
    /// <br/>
    /// \f$\hat{q}_r = (n_xsin(\frac{\theta}{2}), n_ysin(\frac{\theta}{2}), n_zsin(\frac{\theta}{2}), cos(\frac{\theta}{2})) (0, 0, 0, 0)\f$.
    /// <br/>
    /// In the other side, the translation \f$(d_x, d_y, d_z)\f$ is directly converted to a dual quaternion as follows:
    /// <br/>
    /// \f$\hat{q}_d = (0, 0, 0, 1) (\frac{d_x}{2}, \frac{d_y}{2}, \frac{d_z}{2}, 0)\f$.
    /// <br/>
    /// Our transformation dual quaternion is given by the product of the rotation dual quaternion by
    /// the translation dual quaternion, taking into account that the transfomation is done as follows:<br/>
    /// FIRST TRANSLATION THEN ROTATION.<br/>
    /// Remember that the quaternion must be normalized to represent the rotation properly.
    /// </remarks>
    /// <param name="vTranslation">[IN] The vector which represents the translation.</param>
    /// <param name="qRotation">[IN] The quaternion that keeps the rotation.</param>
    DualQuaternion(const BaseVector3 &vTranslation, const BaseQuaternion &qRotation);

    /// <summary>
    /// Constructor from a regular quaternion which represents a rotation and a vector which represents a translation.
    /// </summary>
    /// <remarks>
    /// The rotation regular quaternion is built from an angle (\f$\theta\f$) and a unit vector \f$\vec{n}(n_x, n_y, n_z)\f$
    /// in the direction of the rotation axis as follows:
    /// <br/>
    /// \f$ q(x, y, z, w) = (n_xsin(\frac{\theta}{2}), n_ysin(\frac{\theta}{2}), n_zsin(\frac{\theta}{2}), cos(\frac{\theta}{2}))\f$,
    /// <br/>
    /// and the dual quaternion will be:
    /// <br/>
    /// \f$\hat{q}_r = (n_xsin(\frac{\theta}{2}), n_ysin(\frac{\theta}{2}), n_zsin(\frac{\theta}{2}), cos(\frac{\theta}{2})) (0, 0, 0, 0)\f$.
    /// <br/>
    /// In the other side, the translation \f$(d_x, d_y, d_z)\f$ is directly converted to a dual quaternion as follows:
    /// <br/>
    /// \f$\hat{q}_d = (0, 0, 0, 1) (\frac{d_x}{2}, \frac{d_y}{2}, \frac{d_z}{2}, 0)\f$.
    /// <br/>
    /// Our transformation dual quaternion is given by the product of the rotation dual quaternion by
    /// the translation dual quaternion, taking into account that the transfomation is done as follows:<br/>
    /// FIRST TRANSLATION THEN ROTATION.<br/>
    /// Remember that the quaternion must be normalized to represent the rotation properly.
    /// </remarks>
    /// <param name="vTranslation">[IN] The vector which represents the translation.</param>
    /// <param name="qRotation">[IN] The quaternion that keeps the rotation.</param>
    DualQuaternion(const BaseVector4 &vTranslation, const BaseQuaternion &qRotation);

    /// <summary>
    /// Constructor from two four components arrays of floating point values, one for each quaternion component.
    /// </summary>
    /// <param name="arValuesReal">[IN] Array of floating point values. It must have at least four elements. If the pointer is null, the behavior
    /// is undefined.</param>
    /// <param name="arValuesDual">[IN] Array of floating point values. It must have at least four elements. If the pointer is null, the behavior
    /// is undefined.</param>
    DualQuaternion(const float_z *arValuesReal, const float_z *arValuesDual);

private:

    /// <summary>
    /// Constructor from a regular quaternion which represents a rotation and a vector which represents a translation.
    /// </summary>
    /// <remarks>
    /// The rotation regular quaternion is built from an angle (\f$\theta\f$) and a unit vector \f$\vec{n}(n_x, n_y, n_z)\f$
    /// in the direction of the rotation axis as follows:<br/>
    /// \f$ q(x, y, z, w) = (n_xsin(\frac{\theta}{2}), n_ysin(\frac{\theta}{2}), n_zsin(\frac{\theta}{2}), cos(\frac{\theta}{2}))\f$,
    /// and the dual quaternion will be:<br/>
    /// \f$\hat{q}_r = (n_xsin(\frac{\theta}{2}), n_ysin(\frac{\theta}{2}), n_zsin(\frac{\theta}{2}), cos(\frac{\theta}{2})) (0, 0, 0, 0)\f$.<br/>
    /// In the other side, the translation \f$(d_x, d_y, d_z)\f$ is directly converted to a dual quaternion as follows:<br/>
    /// \f$\hat{q}_d = (0, 0, 0, 1) (\frac{d_x}{2}, \frac{d_y}{2}, \frac{d_z}{2}, 0)\f$.<br/>
    /// Our transformation dual quaternion is given by the product of the translation dual quaternion by
    /// the rotation dual quaternion, taking into account that the transfomation is done as follows:<br/>
    /// FIRST ROTATION THEN TRANSLATION.
    /// </remarks>
    /// <typeparam name="VectorT">Allowed types: BaseVector3, BaseVector4, Vector3, Vector4.</typeparam>
    /// <param name="qRotation">[IN] The quaternion that keeps the rotation.</param>
    /// <param name="vTranslation">[IN] The vector which represents the translation.</param>
    template <class VectorT>
    void DualQuaternionImp(const BaseQuaternion &qRotation, const VectorT &vTranslation);

    /// <summary>
    /// Constructor from a regular quaternion which represents a rotation and a vector which represents a translation.
    /// </summary>
    /// <remarks>
    /// The rotation regular quaternion is built from an angle (\f$\theta\f$) and a unit vector \f$\vec{n}(n_x, n_y, n_z)\f$
    /// in the direction of the rotation axis as follows:<br/>
    /// \f$ q(x, y, z, w) = (n_xsin(\frac{\theta}{2}), n_ysin(\frac{\theta}{2}), n_zsin(\frac{\theta}{2}), cos(\frac{\theta}{2}))\f$,
    /// and the dual quaternion will be:<br/>
    /// \f$\hat{q}_r = (n_xsin(\frac{\theta}{2}), n_ysin(\frac{\theta}{2}), n_zsin(\frac{\theta}{2}), cos(\frac{\theta}{2})) (0, 0, 0, 0)\f$.<br/>
    /// In the other side, the translation \f$(d_x, d_y, d_z)\f$ is directly converted to a dual quaternion as follows:<br/>
    /// \f$\hat{q}_d = (0, 0, 0, 1) (\frac{d_x}{2}, \frac{d_y}{2}, \frac{d_z}{2}, 0)\f$.<br/>
    /// Our transformation dual quaternion is given by the product of the rotation dual quaternion by
    /// the translation dual quaternion, taking into account that the transfomation is done as follows:<br/>
    /// FIRST TRANSLATION THEN ROTATION.
    /// </remarks>
    /// <typeparam name="VectorT">Allowed types: BaseVector3, BaseVector4, Vector3, Vector4.</typeparam>
    /// <param name="vTranslation">[IN] The vector which represents the translation.</param>
    /// <param name="qRotation">[IN] The quaternion that keeps the rotation.</param>
    template <class VectorT>
    void DualQuaternionImp(const VectorT &vTranslation, const BaseQuaternion &qRotation);


    // PROPERTIES
    // ---------------
public:

    /// <summary>
    /// Gets a dual quaternion that represents the identity dual quaternion. It's (0,0,0,1) (0,0,0,0).
    /// </summary>
    /// <returns>
    /// The identity dual quaternion.
    /// </returns>
    static const DualQuaternion& GetIdentity();


    // METHODS
    // ---------------
public:

    /// <summary>
    /// Dual quaternions addition: it's performed component by component.
    /// </summary>
    /// <param name="dualQuat">[IN] Adding dual quaternion.</param>
    /// <returns>
    /// A dual quaternion that is the result of the addition.
    /// </returns>
    DualQuaternion operator+(const BaseDualQuaternion &dualQuat) const;

    /// <summary>
    /// Dual quaternions subtraction: it's performed component by component.
    /// </summary>
    /// <param name="dualQuat">[IN] Subtracting dual quaternion.</param>
    /// <returns>
    /// A dual quaternion that is the result of the subtraction.
    /// </returns>
    DualQuaternion operator-(const BaseDualQuaternion &dualQuat) const;

    /// <summary>
    /// Dual quaternions product: it's performed as follows:
    /// <br/>
    /// \f$ q\cdot q' = r\cdot r' + (r\cdot d' + d\cdot r')\varepsilon\f$
    /// <br/>
    /// </summary>
    /// <remarks>
    /// Product between dual quaternions is not commutative.
    /// </remarks>
    /// <param name="dualQuat">[IN] Multiplying dual quaternion.</param>
    /// <returns>
    /// A dual quaternion that is the result of the product.
    /// </returns>
    DualQuaternion operator*(const BaseDualQuaternion &dualQuat) const;

    /// <summary>
    /// Multiply by scalar operator. Both quaternion components are multiplied by the scalar.
    /// </summary>
    /// <param name="fScalar">[IN] The scalar to multiply by.</param>
    /// <returns>
    /// The resultant dual quaternion.
    /// </returns>
    DualQuaternion operator*(const float_z fScalar) const;

    /// <summary>
    /// Product by a vector (multiplying to the dual quaternion by the right).
    /// </summary>
    /// <remarks>
    /// The vector is transformed into a dual quaternion, then is multiplied by the resident dual quaternion
    /// by the left and transformed back to a vector.<br/>
    /// If vector is \f$ \vec{v}=(x, y, z)\f$, it's transformed into \f$ \hat{Q}=(0, 0, 0, 1)(x, y, z, 0)\f$.
    /// </remarks>
    /// <param name="vVector">[IN] Multiplying vector.</param>
    /// <returns>
    /// A vector that is the result of the product.
    /// </returns>
    DualQuaternion operator*(const BaseVector3 &vVector) const;

    /// <summary>
    /// Product by a vector (multiplying to the dual quaternion by the right).
    /// </summary>
    /// <remarks>
    /// The vector is transformed into a dual quaternion,
    /// then is multiplied by the resident dual quaternion by the left and transformed back to a vector.<br/>
    /// If vector is \f$ \vec{v}=(x, y, z)\f$, it's transformed into \f$ \hat{Q}=(0, 0, 0, 1)(x, y, z, 0)\f$.
    /// </remarks>
    /// <param name="vVector">[IN] Multiplying vector.</param>
    /// <returns>
    /// A vector that is the result of the product.
    /// </returns>
    DualQuaternion operator*(const BaseVector4 &vVector) const;

    /// <summary>
    /// Divide by scalar operator. Both quaternion components are divided by the scalar.
    /// </summary>
    /// <param name="fScalar">[IN] The scalar to divide by. If this value equals zero, the result is undefined.</param>
    /// <returns>
    /// The resultant dual quaternion.
    /// </returns>
    DualQuaternion operator/(const float_z fScalar) const;

    /// <summary>
    /// Add and assign operator. Each input quaternion component is added to the corresponding quaternion
    /// of the resident dual quaternion.
    /// </summary>
    /// <param name="dualQuat">[IN] The dual quaternion that is Added.</param>
    /// <returns>
    /// The modified dual quaternion.
    /// </returns>
    DualQuaternion& operator+=(const BaseDualQuaternion &dualQuat);

    /// <summary>
    /// Subtract and assign operator. Each input quaternion component is subtracted to the corresponding quaternion
    /// of the resident dual quaternion.
    /// </summary>
    /// <param name="dualQuat">[IN] The dual quaternion that is subtracted.</param>
    /// <returns>
    /// The modified dual quaternion.
    /// </returns>
    DualQuaternion& operator-=(const BaseDualQuaternion &dualQuat);

    /// <summary>
    /// Multiply and assign operator. The resident dual quaternion is multiplied by the input one.
    /// </summary>
    /// <remarks>
    /// This is calculated as follows:
    /// <br/>
    /// \f$ q\cdot q' = r\cdot r' + (r\cdot d' + d\cdot r')\varepsilon\f$
    /// <br/>
    /// Note that quaternion multiplication is not conmutative.
    /// </remarks>
    /// <param name="dualQuat">[IN] The dual quaternion to multiply by.</param>
    /// <returns>
    /// The modified dual quaternion.
    /// </returns>
    DualQuaternion& operator*=(const BaseDualQuaternion &dualQuat);

    /// <summary>
    /// Multiply by a floating point value and assign operator. Each dual quaternion component is
    /// multiplied by the input floating point value.
    /// </summary>
    /// <param name="fScalar">[IN] The floating point value to multiply by.</param>
    /// <returns>
    /// The modified dual quaternion.
    /// </returns>
    DualQuaternion& operator*=(const float_z fScalar);

    /// <summary>
    /// Divide and assign operator. Each dual quaternion component is divided by the input floating point value.
    /// </summary>
    /// <param name="fScalar">[IN] The floating point value to divide by. If this value equals zero, the result is undefined.</param>
    /// <returns>
    /// The modified dual quaternion.
    /// </returns>
    DualQuaternion& operator/=(const float_z fScalar);

    /// <summary>
    /// Assignation operator. Assigns the provided dual quaternion to the resident dual quaternion.
    /// </summary>
    /// <param name="dualQuat">[IN] The dual quaternion to be assigned.</param>
    /// <returns>
    /// A reference to the modified dual quaternion.
    /// </returns>
    DualQuaternion& operator=(const BaseDualQuaternion &dualQuat);

    /// <summary>
    /// Resets to zero all components of both quaternions of the dual quaternion.
    /// </summary>
    void ResetToZero();

    /// <summary>
    /// Resets to identity the dual quaternion. This implies that de non-dual component is reset to identity
    /// and de dual component is reset to zero.
    /// </summary>
    void ResetToIdentity();

    /// <summary>
    /// Calculates the SINGLE dual quaternion's conjugate. It's calculated this way:
    /// <br/>
    /// \f$ Q^* = r^* + d^*\varepsilon\f$ .
    /// </summary>
    /// <returns>
    /// The single dual quaternion conjugate.
    /// </returns>
    DualQuaternion Conjugate() const;

    /// <summary>
    /// Calculates the DOUBLE dual quaternion's conjugate. It's calculated this way:
    /// <br/>
    /// \f$ Q^* = r^* - d^*\varepsilon\f$.
    /// </summary>
    /// <returns>
    /// The double dual quaternion conjugate.
    /// </returns>
    DualQuaternion DoubleConjugate() const;

    /// <summary>
    /// Calculates the length of the non-dual part of the resident dual quaternion. It is used to normalize
    /// an interpolated transformation. See Lerp method for further information.
    /// </summary>
    /// <returns>
    /// A floating point value that is the length of the non-dual part of the dual quaternion.
    /// </returns>
    float_z GetNonDualLength() const;

    /// <summary>
    /// Applies a transformation to the resident dual quaternion.
    /// </summary>
    /// <remarks>
    /// The transformation is performed as follows:
    /// <br/>
    ///     \f$ P' = T \cdot P \cdot T^*\f$, where
    /// <br/>
    ///     \f$ P'\f$: Transformed dual quaternion.<br/>
    ///     \f$ T \f$: Transformation applied.<br/>
    ///     \f$ P \f$: Dual quaternion which is transformed.<br/>
    ///     \f$ T^*\f$: Double conjugate of the transformation.
    /// </remarks>
    /// <param name="transformation">[IN] Transformation to be applied.</param>
    /// <returns>
    /// The transformed dual quaternion.
    /// </returns>
    DualQuaternion Transform(const DualQuaternion &transformation) const;

    /// <summary>
    /// Applies a transformation composed of a rotation and a translation, performing the rotation first and then the traslation.
    /// </summary>
    /// <param name="qRotation">[IN] Regular quaternion which defines the rotation.</param>
    /// <param name="vTranslation">[IN] Vector which defines the translation.</param>
    /// <returns>
    /// The transformed dual quaternion.
    /// </returns>
    DualQuaternion TransformRotationFirst(const BaseQuaternion &qRotation, const BaseVector3 &vTranslation) const;

    /// <summary>
    /// Applies a transformation composed of a rotation and a translation, performing the rotation first and then the traslation.
    /// </summary>
    /// <param name="qRotation">[IN] Regular quaternion which defines the rotation.</param>
    /// <param name="vTranslation">[IN] Vector which defines the translation.</param>
    /// <returns>
    /// The transformed dual quaternion.
    /// </returns>
    DualQuaternion TransformRotationFirst(const BaseQuaternion &qRotation, const BaseVector4 &vTranslation) const;

    /// <summary>
    /// Applies a transformation composed of a rotation and a translation, performing the traslation first and then the rotation.
    /// </summary>
    /// <param name="vTranslation">[IN] Vector which defines the translation.</param>
    /// <param name="qRotation">[IN] Regular quaternion which defines the rotation.</param>
    /// <returns>
    /// The transformed dual quaternion.
    /// </returns>
    DualQuaternion TransformTranslationFirst(const BaseVector3 &vTranslation, const BaseQuaternion &qRotation) const;

    /// <summary>
    /// Applies a transformation composed of a rotation and a translation, performing the traslation first and then the rotation.
    /// </summary>
    /// <param name="vTranslation">[IN] Vector which defines the translation.</param>
    /// <param name="qRotation">[IN] Regular quaternion which defines the rotation.</param>
    /// <returns>
    /// The transformed dual quaternion.
    /// </returns>
    DualQuaternion TransformTranslationFirst(const BaseVector4 &vTranslation, const BaseQuaternion &qRotation) const;

    /// <summary>
    /// Returns a dual quaternion, assuming current one is a transformation, which is a linear interpolation
    /// between it and a transformation provided, by a proportion also provided.<br/>
    /// Note that this isn't an interpolation between dual quaternions, only between unitary dual quaternions
    /// which contains transformations.
    /// </summary>
    /// <remarks>
    /// To take the transformed point or vector interpolating from a transformation,
    /// it's necessary to apply the resultant transformation of the lerp to the original point or vector,
    /// obtaining a point or vector in a status of transformation given by the proportion used.<br/>
    /// Lerp is obtained as follows:<br/>
    /// If Q1 is the original transformation, and Q2 is the transformation provided,
    /// the transformation Q' which give us the status of any point at a proportion t in [0, 1] is
    /// <br/>
    /// \f$ \hat{Q} (t) = \frac{(1 - t)\hat{Q}_1 + t  \hat{Q}_2}{\left|(1 - t)\hat{Q}_1 + t  \hat{Q}_2\right|} \f$
    /// <br/>
    /// Where Q'(0) = Q1 (first transformation); Q'(1) = Q2 (second transformation).
    /// </remarks>
    /// <param name="fProportion">[IN] Proportion with we want to calculate the interpolation.</param>
    /// <param name="dualQuat">[IN] The other transformation implied in the interpolation.</param>
    /// <returns>
    /// The "lerped" dual quaternion.
    /// </returns>
    DualQuaternion Lerp(const float_z fProportion, const DualQuaternion &dualQuat) const;

    /// <summary>
    /// Converts dual quaternion into a string.
    /// </summary>
    /// <remarks>
    /// The format of the string is:<br/>
    /// "DQ(r($r),d($d))".<br/>
    /// Where "$" means "string representation of attribute".
    /// </remarks>
    /// <returns>
    /// The std::string with the format specified.
    /// </returns>
    string_z ToString() const;

private:

    /// <summary>
    /// Applies a transformation composed of a rotation and a translation, performing the rotation first and then the traslation.
    /// </summary>
    /// <typeparam name="VectorT">Allowed types: BaseVector3, BaseVector4, Vector3, Vector4.</typeparam>
    /// <param name="qRotation">[IN] Regular quaternion which defines the rotation.</param>
    /// <param name="vTranslation">[IN] Vector which defines the translation.</param>
    /// <returns>
    /// The transformed dual quaternion.
    /// </returns>
    template <class VectorT>
    DualQuaternion TransformRotationFirstImp(const BaseQuaternion &qRotation, const VectorT &vTranslation) const;

    /// <summary>
    /// Applies a transformation composed of a rotation and a translation, performing the traslation first and then the rotation.
    /// </summary>
    /// <typeparam name="VectorT">Allowed types: BaseVector3, BaseVector4, Vector3, Vector4.</typeparam>
    /// <param name="vTranslation">[IN] Vector which defines the translation.</param>
    /// <param name="qRotation">[IN] Regular quaternion which defines the rotation.</param>
    /// <returns>
    /// The transformed dual quaternion.
    /// </returns>
    template <class VectorT>
    DualQuaternion TransformTranslationFirstImp(const VectorT &vTranslation, const BaseQuaternion &qRotation) const;

};

} // namespace z


#endif // __DUALQUATERNION__
