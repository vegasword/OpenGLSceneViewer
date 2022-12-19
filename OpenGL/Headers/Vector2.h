#pragma once

#include <string>

namespace Core::Maths
{
	class Vector2
	{
	public:
        // Properties.
		float x, y;

		// Constructors.
		Vector2();										                  // Vector2 default declaration.
		Vector2(const float& _x,  const float& y);	                      // Vector2 coordinates declaration.
		Vector2(const Vector2& a, const Vector2& b);	                  // Vector2 from two points declaration.
        Vector2(const float& rad, const float& lenght, const bool isPolar); // Vector2 polar coordinates declaration.
        
        // Operators.
	    void    operator= (const Vector2& v);       // Vector2 copy operator.
        float   operator& (const Vector2& v) const; // Dot product operator.
        float   operator^ (const Vector2& v) const; // Cross product operator.
        Vector2 operator- ()                 const; // Negation operator.

        bool operator==(const Vector2& val) const; // Equal comparaison operator.
        bool operator!=(const Vector2& val) const; // Different comparaison operator.

        Vector2 operator+(const Vector2& val) const; // Addition operator.
        Vector2 operator-(const Vector2& val) const; // Substraction operator.
        Vector2 operator*(const Vector2& val) const; // Multiplication operator.
        Vector2 operator*(const float& val)   const; // Multiplication operator by a scalar.
        Vector2 operator/(const Vector2& val) const; // Division operator.
        Vector2 operator/(const float& val)   const; // Division operator by a scalar.

        void operator+=(const Vector2 &val); // Increment asignment.
        void operator+=(const float   &val); // Float scalar increment asignment.
        void operator-=(const Vector2 &val); // Decrement asigment.
        void operator-=(const float   &val); // Float scalar decrement asigment.
        void operator*=(const Vector2 &val); // Product asigment.
        void operator*=(const float   &val); // Float scalar product asigment.
        void operator/=(const Vector2 &val); // Division asigment.
        void operator/=(const float   &val); // Float scalar division asigment.

        // Public methods.
        Vector2 GetMiddle() const;                            // Returns the middle of the given vector
        float   GetLength() const;                            // Returns the length of the given vector.
        float   GetDistanceFromPoint(const Vector2 &p) const; // Interprets the vector as a point and returns the distance to another point.
        Vector2 GetNormal()     const;                        // Returns the normal of a given vector.
        Vector2 GetNormalized() const;                        // Normalizes the given vector so that its length is 1.
        Vector2 GetCopiedSign(const Vector2& source) const;   // Copies the signs from the source vector to the destination vector.
        float   GetAngle() const;                             // Returns the angle (in radians) of the given vector
        float   GetAngleWithVector2(const Vector2& v) const;  // Returns the angle (in radians) between two vectors.
        
        void    SetLength(const float& length);  // Modifies the length of the given vector to correspond to the given scalar.
        void    Normalize();                     // Normalizes the given vector so that its length is 1.
        void    Negate();                        // Negates both of the coordinates of the given vector.
        void    Copysign(const Vector2& source); // Copies the signs from the source vector to the destination vector.
        void    Rotate(const float& angle);      // Rotates the given vector by the given angle.

        const std::string Debug(); // Debug string output.
	};
}