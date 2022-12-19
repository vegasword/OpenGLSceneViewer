#pragma once

#include <string>

namespace Core::Maths
{
    class Vector3;

    class Vector4
    {
    public:
        // Public properties.
        float x, y, z, w;

        // Constructors.
        Vector4();                                                                                               // Vector4 default declaration.
        Vector4(const float& _x, const float& _y, const float& _z, const float& _w);                             // Vector4 coordinates declaration.
        Vector4(const Vector4& p1, const Vector4& p2, const float& _w);                                          // Vector4 from two points declaration.
        Vector4(const float& theta, const float& phi, const float& length, const float& _w, const bool isPolar); // Vector4 polar coordinates declaration.
        
        // Operators.
        void    operator=(const Vector4& other);     // Vector4 copy constructor.
        float   operator&(const Vector4& val) const; // Dot product operator.
        Vector4 operator^(const Vector4& val) const; // Cross product operator.
        Vector4 operator-()                   const; // Negation operator.

        bool operator==(const Vector4& val) const; // Equal comparaison operator.
        bool operator!=(const Vector4& val) const; // Different comparaison operator.

        Vector4 operator+(const Vector4& val) const; // Addition operator.
        Vector4 operator-(const Vector4& val) const; // Substraction operator.
        Vector4 operator*(const Vector4& val) const; // Multiplication operator.
        Vector4 operator*(const float& val)   const; // Multiplication operator by a scalar.
        Vector4 operator/(const Vector4& val) const; // Division operator.
        Vector4 operator/(const float& val)   const; // Division operator by a scalar.

        void operator+=(const Vector4 &val); // Increment asignment.
        void operator+=(const float   &val); // Float scalar increment asignment.
        void operator-=(const Vector4 &val); // Decrement asigment.
        void operator-=(const float   &val); // Float scalar decrement asigment.
        void operator*=(const Vector4 &val); // Product asigment.
        void operator*=(const float   &val); // Float scalar product asigment.
        void operator/=(const Vector4 &val); // Division asigment.
        void operator/=(const float   &val); // Float scalar division asigment.

        // Public methods.
        Vector4 GetMiddle()                            const; // Returns the middle of this vector.
        Vector4 GetHomogenized()                       const; // Homogenizes the vector4 by dividing it by w.
        float   GetLength()                            const; // Returns the length of this vector.
        Vector4 GetNormalized()                        const; // Normalizes the given vector so that its length is 1.
        Vector4 GetCopiedSign(Vector4 source)          const; // Copies the signs from the source vector to the destination vector.
        float   GetDistanceFromPoint(const Vector4 &p) const; // Interprets the vector as a point and returns the distance to another point.
        float   GetAngleTheta()                        const; // Returns the angle (in radians) of this vector.
        float   GetAnglePhi()                          const; // Returns the angle (in radians) of this vector.
        float   GetAngleThetaWithVector4(Vector4 v)    const; // Returns the angle (in radians) between two vectors.
        float   GetAnglePhiWithVector4  (Vector4 v)    const; // Returns the angle (in radians) between two vectors.

        void SetLength(const float& length);               // Modifies the length of this vector to correspond to the given scalar.
        void Homogenize();                                 // Homogenizes the vector4 by dividing it by w.
        void Normalize();                                  // Normalizes the given vector so that its length is 1.
        void Negate();                                     // Negates both of the coordinates of this vector.
        void Copysign(Vector4 source);                     // Copies the signs from the source vector to the destination vector.
        void Rotate(const float& theta, const float& phi); // Rotates the given vector by the given angle.
        
        Vector3 ToVec3(bool homogenizeVec = false) const; // Convert to a Vector3.

        const std::string Debug(); // Debug string output.
    };
}