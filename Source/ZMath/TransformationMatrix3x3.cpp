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

#include "ZMath/TransformationMatrix3x3.h"

#include "ZCommon/Assertions.h"
#include "ZMath/Vector2.h"
#include "ZMath/SAngle.h"
#include "ZCommon/DataTypes/SFloat.h"
#include "ZMath/MathDefinitions.h"



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

TransformationMatrix3x3::TransformationMatrix3x3()
{
}

TransformationMatrix3x3::TransformationMatrix3x3(const TransformationMatrix3x3 &transformation) : Matrix3x3(transformation)
{
}

TransformationMatrix3x3::TransformationMatrix3x3(const Matrix3x3 &transformation) : Matrix3x3(transformation)
{
}

TransformationMatrix3x3::TransformationMatrix3x3(const Vector2 &vTranslation, const float_z fRotationAngle, const Vector2 &vScale)
{
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        // If angles are specified in degrees, then converts it to radians
        const float_z &ROT_RAD = SAngle::DegreesToRadians(fRotationAngle);

        const float_z& fA   = cos_z(ROT_RAD);
        const float_z& fB   = sin_z(ROT_RAD);
    #else
        const float_z& fA   = cos_z(fRotationAngle);
        const float_z& fB   = sin_z(fRotationAngle);
    #endif

    this->ij[0][0] =  vScale.x * fA;
    this->ij[0][1] =  vScale.x * fB;
    this->ij[0][2] =  SFloat::_0;

    this->ij[1][0] =  vScale.y * -fB;
    this->ij[1][1] =  vScale.y * fA;
    this->ij[1][2] =  SFloat::_0;

    this->ij[2][0] =  vTranslation.x;
    this->ij[2][1] =  vTranslation.y;
    this->ij[2][2] =  SFloat::_1;

}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |            METHODS         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

TransformationMatrix3x3& TransformationMatrix3x3::operator=(const Matrix3x3 &matrix)
{
    Matrix3x3::operator=(matrix);
    return *this;
}

void TransformationMatrix3x3::Decompose(Vector2 &vOutDisp, float_z &fOutRot, Vector2 &vOutScale) const
{
    vOutDisp.x = this->ij[2][0];
    vOutDisp.y = this->ij[2][1];

    vOutScale.x = hypot_z(this->ij[0][0], this->ij[0][1]);
    vOutScale.y = hypot_z(this->ij[1][0], this->ij[1][1]);

    // Checkout to avoid division by zero.
    Z_ASSERT_WARNING(vOutScale.x != SFloat::_0, "The scale in the X axis must not equal zero, this will cause a division by zero");

    float_z COS_ROT = this->ij[0][0] / vOutScale.x;

    // Sometimes the result of the dot product is not accurate and must be clampped [-1, 1]
    if(COS_ROT > SFloat::_1)
        COS_ROT = SFloat::_1;
    else if(COS_ROT < -SFloat::_1)
        COS_ROT = -SFloat::_1;

    fOutRot = acos_z(COS_ROT);

    Z_ASSERT_WARNING( !SFloat::IsNaN(fOutRot), "The resultant rotation angle is NAN" );

    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        // If angles must be specified in degrees, then converts it.
        fOutRot = SAngle::RadiansToDegrees(fOutRot);
    #endif
}

void TransformationMatrix3x3::GetTranslation(Vector2 &vTranslation) const
{
    vTranslation.x = this->ij[2][0];
    vTranslation.y = this->ij[2][1];
}

void TransformationMatrix3x3::GetRotation(float_z &fRotationAngle) const
{
    const float_z &SCALE = hypot_z(this->ij[0][0], this->ij[0][1]);

    // Checkout to avoid division by zero.
    Z_ASSERT_WARNING(SCALE != SFloat::_0, "The scale must not be null, this will produce a division by zero");

    float_z COS_ROT = this->ij[0][0] / SCALE;

    // Sometimes the result of the dot product is not accurate and must be clampped [-1, 1]
    if(COS_ROT > SFloat::_1)
        COS_ROT = SFloat::_1;
    else if(COS_ROT < -SFloat::_1)
        COS_ROT = -SFloat::_1;

    fRotationAngle = acos_z(COS_ROT);

    Z_ASSERT_WARNING( !SFloat::IsNaN(fRotationAngle), "The obtained rotation angle is NAN" );
      
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        // If angles must be specified in degrees, then converts it.
        fRotationAngle = SAngle::RadiansToDegrees(fRotationAngle);
    #endif
}

void TransformationMatrix3x3::GetScale(Vector2 &vScale) const
{
    vScale.x = hypot_z(this->ij[0][0], this->ij[0][1]);
    vScale.y = hypot_z(this->ij[1][0], this->ij[1][1]);
}

TransformationMatrix3x3 TransformationMatrix3x3::SwitchHandConvention() const
{
    TransformationMatrix3x3 switchedMatrix = *this;
    switchedMatrix.ij[0][1] = -this->ij[0][1];
    switchedMatrix.ij[1][0] = -this->ij[1][0];
    return switchedMatrix;
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |         PROPERTIES         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

const TransformationMatrix3x3& TransformationMatrix3x3::GetIdentity()
{
    static const TransformationMatrix3x3 IDENTITY(Matrix3x3::GetIdentity());
    return IDENTITY;
}


} // namespace z
