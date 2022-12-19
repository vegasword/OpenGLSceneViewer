#include <cmath>
#include <string>

#include <Vector2.h>
#include <Vector3.h>
#include <Vector4.h>
#include <Constants.h>

using namespace std;
using namespace Core::Maths;

// ===================================================================
// Vector3 constructors.
// ===================================================================

// Vector3 default declaration.
Vector3::Vector3()
        : x(0), y(0), z(0)
{ }; 

// Vector3 coordinates declaration.
Vector3::Vector3(const float& _x, const float& _y, const float& _z)
        : x(_x), y(_y), z(_z)
{ }

// Vector3 from two points declaration.
Vector3::Vector3(const Vector3& p1, const Vector3& p2)
        : x(p2.x - p1.x), y(p2.y - p1.y), z(p2.z - p1.z)
{ }

// Vector3 polar coordinates declaration.
Vector3::Vector3(const float& pitch, const float& yaw, const float& length, const bool& isAngle) // Vector from angle (useless bool).
{
    float offsetPitch = (2 * PI - pitch) - 2 * PI + PI/2;
    float offsetYaw   = fmod(2 * PI - yaw + PI / 2, 2 * PI);

    x = length * sinf(offsetYaw) * cosf(offsetPitch);
    y = length * cosf(offsetYaw);
    z = length * sinf(offsetYaw) * sinf(offsetPitch);
}

// ===================================================================
// Vector3 operators.
// ===================================================================

// Copy constructors.
void Vector3::operator=(const Vector3& v) { x = v.x; y = v.y; z = v.z; }

// Dot product operator.
float Vector3::operator&(const Vector3& v)   const { return (x * v.x) + (y * v.y) + (z * v.z); }

// Cross product operator.
Vector3 Vector3::operator^(const Vector3& v) const { return Vector3((y * v.z - z * v.y), (z * v.x - x * v.z), (x * v.y - y * v.x)); }

// Negation operator.
Vector3 Vector3::operator-() const { return { -x, -y, -z }; }

// Comparaison operators.
bool Vector3::operator== (const Vector3& val) const { return (x == val.x && y == val.y && z == val.z); }
bool Vector3::operator!= (const Vector3& val) const { return (x != val.x || y != val.y || z != val.z); }

// Operation operators.
Vector3 Vector3::operator+ (const Vector3& val) const { return Vector3(x + val.x, y + val.y, z + val.z); }
Vector3 Vector3::operator- (const Vector3& val) const { return Vector3(x - val.x, y - val.y, z - val.z); }
Vector3 Vector3::operator* (const Vector3& val) const { return Vector3(x * val.x, y * val.y, z * val.z); }
Vector3 Vector3::operator* (const float&   val) const { return Vector3(x * val,   y * val,   z * val  ); }
Vector3 Vector3::operator/ (const Vector3& val) const { return Vector3(x / val.x, y / val.y, z / val.z); }
Vector3 Vector3::operator/ (const float&   val) const { return Vector3(x / val,   y / val,   z / val  ); }

// Asgniments operators.
void Vector3::operator+= (const Vector3& val) { x += val.x; y += val.y; z += val.z; }
void Vector3::operator+= (const float&   val) { x += val;   y += val;   z += val;   }
void Vector3::operator-= (const Vector3& val) { x -= val.x; y -= val.y; z -= val.z; }
void Vector3::operator-= (const float&   val) { x -= val;   y -= val;   z -= val;   }
void Vector3::operator*= (const Vector3& val) { x *= val.x; y *= val.y; z *= val.z; }
void Vector3::operator*= (const float&   val) { x *= val;   y *= val;   z *= val;   }
void Vector3::operator/= (const Vector3& val) { x /= val.x; y /= val.y; z /= val.z; }
void Vector3::operator/= (const float&   val) { x /= val;   y /= val;   z /= val;   }

// ===================================================================
// Vector3 public methods.
// ===================================================================

// Returns the middle of the given vector.
Vector3 Vector3::GetMiddle() const { return Vector3(x / 2, y / 2, z / 2); }

// Returns the length of the given vector.
float Vector3::GetLength() const { return powf(x, 2) + powf(y, 2) + powf(z, 2); }

// Normalizes the given vector so that its length is 1.
Vector3 Vector3::GetNormalized() const 
{ 
    float length = GetLength();
    return Vector3(x / length, y / length, z / length); 
}

// Copies the signs from the source vector to the destination vector.
Vector3 Vector3::GetCopiedSign(const Vector3& source) const { return Vector3(copysign(x, source.x), copysign(y, source.y), copysign(z, source.z)); }

// Interprets the vector as a point and returns the distance to another point.
float Vector3::GetDistanceFromPoint(const Vector3& p) const { return Vector3(*this, p).GetLength(); }

// Returns the angle (in radians) of the given vector.
float Vector3::GetAngleTheta() const { return fmod(2 * PI - Vector2(x, z).GetAngle() + PI/2,   2*PI);                 }
float Vector3::GetAnglePhi()   const { return     (2 * PI - Vector2(Vector2(x, z).GetLength(), y).GetAngle()) - 2*PI; }

// Returns the angle (in radians) between two vectors.
float Vector3::GetAngleThetaWithVector3(const Vector3& v) const
{
    float this_angle =   GetAngleTheta();
    float v_angle    = v.GetAngleTheta();
    return (this_angle >= v_angle ? (this_angle - v_angle) : (v_angle - this_angle));
}

float Vector3::GetAnglePhiWithVector3(const Vector3& v) const
{
    float this_angle =   GetAnglePhi();
    float v_angle    = v.GetAnglePhi();
    return (this_angle >= v_angle ? (this_angle - v_angle) : (v_angle - this_angle));
}

// Modifies the length of the given vector to correspond to the given scalar.
void Vector3::SetLength(const float& length) { Normalize(); (*this) *= length; }

// Normalizes the given vector so that its length is 1.
void Vector3::Normalize() 
{
    float length = GetLength();
    x /= length; 
    y /= length; 
    z /= length; 
}

// Negates both of the coordinates of the given vector.
void Vector3::Negate() { *(this) = Vector3(-x, -y, -z); }

// Copies the signs from the source vector to the destination vector.
void Vector3::Copysign(const Vector3& source) { *(this) = Vector3(copysign(x, source.x), copysign(y, source.y), copysign(z, source.z)); }

// Rotates the given vector by the given angle.
void Vector3::Rotate(const float& theta, const float& phi)  { *(this) + Vector3(GetAngleTheta() + theta, GetAnglePhi() + phi, GetLength(), true); }

// Convert to a Vector4.
Vector4 Vector3::ToVec4() { return Vector4(x, y, z, 1); }

// Debug string output.
const string Vector3::Debug()
{
    return string("x: ") + to_string(x)
               + ", y: " + to_string(y)
               + ", z: " + to_string(z);
}

// ===================================================================
// Vector3 outside methods.
// ===================================================================

// Returns the coordinates of a point on a sphere of radius r, using the given angles.
Vector3 Core::Maths::GetSphericalCoords(const float& r, const float& theta, const float& phi)
{
    return { r * sinf(theta) * cosf(phi),
             r * cosf(theta),
             r * sinf(theta) * sinf(phi) };
}