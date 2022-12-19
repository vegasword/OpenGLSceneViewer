#pragma once

#include <string>

namespace Core::Maths
{
    class Vector4;

    class Vector3
    {
    public :
        // Public properties.
        float x, y, z;

        // Constructors.
        Vector3();                                                                               // Vector3 default declaration.
        Vector3(const float& _x, const float& _y, const float& _z);                              // Vector3 coordinates declaration.
        Vector3(const Vector3& p1,  const Vector3& p2);                                          // Vector3 from two points declaration.
        Vector3(const float& pitch, const float& yaw, const float& length, const bool& isAngle); // Vector3 angle declaration.
            
        // Operators.
        void    operator=(const Vector3& other);     // Vector3 copy operator.
        float   operator&(const Vector3& val) const; // Dot product operator.
        Vector3 operator^(const Vector3& val) const; // Cross product operator.
        Vector3 operator-()                   const; // Negation operator.

        bool operator==(const Vector3& val) const; // Equal comparaison operator.
        bool operator!=(const Vector3& val) const; // Different comparaison operator.

        Vector3 operator+(const Vector3& val) const; // Addition operator.
        Vector3 operator-(const Vector3& val) const; // Substraction operator.
        Vector3 operator*(const Vector3& val) const; // Multiplication operator.
        Vector3 operator*(const float& val)   const; // Multiplication operator by a scalar.
        Vector3 operator/(const Vector3& val) const; // Division operator.
        Vector3 operator/(const float& val)   const; // Division operator by a scalar.

        void operator+=(const Vector3 &val); // Increment asignment.
        void operator+=(const float   &val); // Float scalar increment asignment.
        void operator-=(const Vector3 &val); // Decrement asigment.
        void operator-=(const float   &val); // Float scalar decrement asigment.
        void operator*=(const Vector3 &val); // Product asigment.
        void operator*=(const float   &val); // Float scalar product asigment.
        void operator/=(const Vector3 &val); // Division asigment.
        void operator/=(const float   &val); // Float scalar division asigment.

        // Public methods.
        Vector3 GetMiddle()                            const; // Returns the middle of the given vector.
        float   GetLength()                            const; // Returns the length of the given vector.
        Vector3 GetNormalized()                        const; // Normalizes the given vector so that its length is 1.
        Vector3 GetCopiedSign(const Vector3& source)   const; // Copies the signs from the source vector to the destination vector.
        float   GetDistanceFromPoint(const Vector3 &p) const; // Interprets the vector as a point and returns the distance to another point.
            
        // Returns the angle (in radians) of the given vector.
        float GetAngleTheta() const;
        float GetAnglePhi()   const;

        // Returns the angle (in radians) between two vectors.
        float GetAngleThetaWithVector3(const Vector3& v) const; 
        float GetAnglePhiWithVector3  (const Vector3& v) const;

        void SetLength(const float& length);               // Modifies the length of the given vector to correspond to the given scalar.
        void Normalize();                                  // Normalizes the given vector so that its length is 1.
        void Negate();                                     // Negates both of the coordinates of the given vector.
        void Copysign(const Vector3& source);              // Copies the signs from the source vector to the destination vector.
        void Rotate(const float& theta, const float& phi); // Rotates the given vector by the given angle.

        Vector4 ToVec4(); // Convert to a Vector4.

        const std::string Debug(); // Debug string output.
    };

    Vector3 GetSphericalCoords(const float& r, const float& theta, const float& phi);
}