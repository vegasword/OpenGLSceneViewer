#include <cmath>
#include <string>

#include <Vector2.h>

using namespace std;
using namespace Core::Maths;

// ===================================================================
// Vector2 constructors.
// ===================================================================

// Default constructor.
Vector2::Vector2() 
	    : x(0),  y(0)
{ }

// Coordinates constructor.
Vector2::Vector2(const float& _x, const float& _y)
		: x(_x), y(_y)
{ }

// Vector2 from two points constructor.
Vector2::Vector2(const Vector2& a, const Vector2& b)
	    : x(b.x - a.x), y(b.y - a.y)
{ }

// Vector2 polar coordinates constructor.
Vector2::Vector2(const float& rad, const float& lenght, const bool isPolar)
	    : x(cosf(rad) * lenght), y(sinf(rad) * lenght)
{ }

// ===================================================================
// Vector2 operators.
// ===================================================================

// Copy operators.
void Vector2::operator=(const Vector2& other) { x = other.x; y = other.y; }

// Dot product operator.
float Vector2::operator&(const Vector2& val) const { return (x * val.x) + (y * val.y); }

// Cross product operator.
float Vector2::operator^(const Vector2& val) const { return (x * val.y) - (y * val.x); }

// Negation operator.
Vector2 Vector2::operator-() const { return { -x, -y }; }

// Comparaison operators.
bool Vector2::operator== (const Vector2& val) const { return (x == val.x && y == val.y); }
bool Vector2::operator!= (const Vector2& val) const { return (x != val.x || y != val.y); }

// Operation operators.
Vector2 Vector2::operator+ (const Vector2& val) const { return Vector2(x + val.x, y + val.y); }
Vector2 Vector2::operator- (const Vector2& val) const { return Vector2(x - val.x, y - val.y); }
Vector2 Vector2::operator* (const Vector2& val) const { return Vector2(x * val.x, y * val.y); }
Vector2 Vector2::operator* (const float& val)   const { return Vector2(x * val,   y * val)  ; }
Vector2 Vector2::operator/ (const Vector2& val) const { return Vector2(x / val.x, y / val.y); }
Vector2 Vector2::operator/ (const float& val)   const { return Vector2(x / val,   y / val)  ; }

// Asgniments operators.
void Vector2::operator+= (const Vector2& val) { x += val.x; y += val.y; }
void Vector2::operator+= (const float&   val) { x += val;   y += val;   }
void Vector2::operator-= (const Vector2& val) { x -= val.x; y -= val.y; }
void Vector2::operator-= (const float&   val) { x -= val;   y -= val;   }
void Vector2::operator*= (const Vector2& val) { x *= val.x; y *= val.y; }
void Vector2::operator*= (const float&   val) { x *= val;   y *= val;   }
void Vector2::operator/= (const Vector2& val) { x /= val.x; y /= val.y; }
void Vector2::operator/= (const float&   val) { x /= val;   y /= val;   }

// ===================================================================
// Vector2 methods.
// ===================================================================

// Returns the middle of the given vector.
Vector2 Vector2::GetMiddle() const
{
    return Vector2(x / 2, y / 2);
}

// Returns the length of the given vector.
float Vector2::GetLength() const
{
    return sqrtf(powf(x, 2) + powf(y, 2));
}

// Returns the normal of a given vector.
Vector2 Vector2::GetNormal() const
{
    return Vector2(-y, x);
}

// Normalizes the given vector so that its length is 1.
Vector2 Vector2::GetNormalized() const
{
    return Vector2(x / GetLength(), y / GetLength());
}

// Copies the signs from the source vector to the destination vector.
Vector2 Vector2::GetCopiedSign(const Vector2& source) const
{
    return Vector2(copysign(x, source.x), copysign(y, source.y));
}

// Interprets the vector as a point and returns the distance to another point.
float Vector2::GetDistanceFromPoint(const Vector2& p) const
{
    return Vector2(*this, p).GetLength();
}

// Returns the angle (in radians) of the given vector.
float Vector2::GetAngle() const
{
    return copysign(acos(GetNormalized().x), asin(GetNormalized().y));
}

// Returns the angle (in radians) between two vectors.
float Vector2::GetAngleWithVector2(const Vector2& v)  const
{
    float this_angle = GetAngle();
    float v_angle    = v.GetAngle();
    return (this_angle >= v_angle ? (this_angle - v_angle) : (v_angle - this_angle));
}

// Modifies the length of the given vector to correspond to the given scalar.
void Vector2::SetLength(const float& length)
{
    *(this) = Vector2(GetAngle(), length);
}

// Normalizes the given vector so that its length is 1.
void Vector2::Normalize()
{
    x /= GetLength(); y /= GetLength();
}

// Negates both of the coordinates of the given vector.
void Vector2::Negate()
{
    *(this) = Vector2(-x, -y);
}

// Copies the signs from the source vector to the destination vector.
void Vector2::Copysign(const Vector2& source)
{
    *(this) = Vector2(copysign(x, source.x), copysign(y, source.y));
}

// Rotates the given vector by the given angle.
void Vector2::Rotate(const float& angle)
{
    float this_length = GetLength();
    float this_angle  = GetAngle();
    *(this) = Vector2(this_angle + angle, this_length, true);
}

// Debug string output.
const string Vector2::Debug()
{
    return string("x: ") + to_string(x) + ", y: " + to_string(y);
}