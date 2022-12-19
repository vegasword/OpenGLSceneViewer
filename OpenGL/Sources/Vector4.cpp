#include <cmath>
#include <string>

#include <Vector3.h>
#include <Vector4.h>
#include <Constants.h>

using namespace std;
using namespace Core::Maths;

// ===================================================================
// Vector4 constructors.
// ===================================================================

// Vector4 default declaration.
Vector4::Vector4()
       : x(0), y(0), z(0), w(1) 
{ }

// Vector4 coordinates declaration.
Vector4::Vector4(const float& _x, const float& _y, const float& _z, const float& _w)
        : x(_x), y(_y), z(_z), w(_w)
{ }

// Vector4 from two points declaration.
Vector4::Vector4(const Vector4& p1, const Vector4& p2, const float& _w) 
        : x(p2.x - p1.x), y(p2.y - p1.y), z(p2.z - p1.z), w(_w)
{ }

// Vector4 polar coordinates declaration.
Vector4::Vector4(const float& theta, const float& phi, const float& length, const float& _w, const bool isPolar)
{
    x = length * sinf(theta) * cosf(phi);
    y = length * cosf(theta);
    z = length * sinf(theta) * sinf(phi);
    w = _w;
}

// ===================================================================
// Vector4 operators.
// ===================================================================

// Copy constructors.
void Vector4::operator=(const Vector4& v) { x = v.x; y = v.y; z = v.z; w = v.w; }

// Dot product operator.
float Vector4::operator&(const Vector4& v) const { return (x * v.x) + (y * v.y) + (z * v.z); }

// Cross product operator.
Vector4 Vector4::operator^(const Vector4& v) const
{ return Vector4((y * v.z - z * v.y), (z * v.x - x * v.z), (x * v.y - y * v.x), 1); }

// Negation operator.
Vector4 Vector4::operator-() const { return { -x, -y, -z, w }; }

// Comparaison operators.
bool Vector4::operator== (const Vector4& val) const { return (x == val.x && y == val.y && z == val.z && w == val.w); }
bool Vector4::operator!= (const Vector4& val) const { return (x != val.x || y != val.y || z != val.z || w != val.w); }

// Operation operators.
Vector4 Vector4::operator+ (const Vector4& val) const { return Vector4(x + val.x, y + val.y, z + val.z, w + val.w); }
Vector4 Vector4::operator- (const Vector4& val) const { return Vector4(x - val.x, y - val.y, z - val.z, w - val.w); }
Vector4 Vector4::operator* (const Vector4& val) const { return Vector4(x * val.x, y * val.y, z * val.z, w * val.w); }
Vector4 Vector4::operator* (const float& val)   const { return Vector4(x * val,   y * val,   z * val,   w * val  ); }
Vector4 Vector4::operator/ (const Vector4& val) const { return Vector4(x / val.x, y / val.y, z / val.z, w / val.w); }
Vector4 Vector4::operator/ (const float& val)   const { return Vector4(x / val,   y / val,   z / val,   w / val  ); }

// Asgniments operators.
void Vector4::operator+= (const Vector4& val) { x += val.x; y += val.y; z += val.z; w += val.w; }
void Vector4::operator+= (const float&   val) { x += val;   y += val;   z += val;   w += val;   }
void Vector4::operator-= (const Vector4& val) { x -= val.x; y -= val.y; z -= val.z; w -= val.w; }
void Vector4::operator-= (const float&   val) { x -= val;   y -= val;   z -= val;   w -= val;   }
void Vector4::operator*= (const Vector4& val) { x *= val.x; y *= val.y; z *= val.z; w *= val.w; }
void Vector4::operator*= (const float&   val) { x *= val;   y *= val;   z *= val;   w *= val;   }
void Vector4::operator/= (const Vector4& val) { x /= val.x; y /= val.y; z /= val.z; w /= val.w; }
void Vector4::operator/= (const float&   val) { x /= val;   y /= val;   z /= val;   w /= val;   }

// ===================================================================
// Vector4 methods.
// ===================================================================

// Returns the middle of the given vector.
Vector4 Vector4::GetMiddle() const { return Vector4(x / 2, y / 2, z / 2, w); }

// Returns the length of the given vector.
float Vector4::GetLength() const { return sqrtf(powf(x, 2) + powf(y, 2) + powf(z, 2)); }

// Homogenizes the vector4 by dividing it by w.
Vector4 Vector4::GetHomogenized() const { return Vector4(x/w, y/w, z/w, w/w); }

// Normalizes the given vector so that its length is 1.
Vector4 Vector4::GetNormalized() const { float length = GetLength(); return Vector4(x / length, y / length, z / length, w); }

// Copies the signs from the source vector to the destination vector.
Vector4 Vector4::GetCopiedSign(Vector4 source) const { return Vector4(copysignf(x, source.x), copysignf(y, source.y), copysignf(z, source.z), w); }

// Interprets the vector as a point and returns the distance to another point.
float Vector4::GetDistanceFromPoint(const Vector4& p) const { return Vector4(*this, p, w).GetLength(); }

// Returns the angle (in radians) of the given vector.
float Vector4::GetAngleTheta() const  { return acosf(z / GetLength()); }

float Vector4::GetAnglePhi() const 
{ 
    if (x > 0) return atanf(y / x);
    if (x < 0) return atanf(y / x) + PI;
    return PI / 2;
}

// Returns the angle (in radians) between two vectors.
float Vector4::GetAngleThetaWithVector4(Vector4 v) const
{
    float this_angle =   GetAngleTheta();
    float v_angle    = v.GetAngleTheta();
    return (this_angle >= v_angle ? (this_angle - v_angle) : (v_angle - this_angle));
}
float Vector4::GetAnglePhiWithVector4(Vector4 v) const
{
    float this_angle =   GetAnglePhi();
    float v_angle    = v.GetAnglePhi();
    return (this_angle >= v_angle ? (this_angle - v_angle) : (v_angle - this_angle));
}

// Modifies the length of the given vector to correspond to the given scalar.
void Vector4::SetLength(const float& length) { *(this) = Vector4(GetAngleTheta(), GetAnglePhi(), length, 1, true); }

// Homogenizes the vector4 by dividing it by w.
void Vector4::Homogenize() { *(this) = Vector4(x / w, y / w, z / w, w / w); }

// Normalizes the given vector so that its length is 1.
void Vector4::Normalize()  { float length = GetLength(); x /= length; y /= length; z /= length; }

// Negates both of the coordinates of the given vector.
void Vector4::Negate() { *(this) = Vector4(-x, -y, -z, w); }

// Copies the signs from the source vector to the destination vector.
void Vector4::Copysign(Vector4 source) { *(this) = Vector4(copysignf(x, source.x), copysignf(y, source.y), copysignf(z, source.z), w); }

// Rotates the given vector by the given angle.
void Vector4::Rotate(const float& theta, const float& phi)  { *(this) = Vector4(GetAngleTheta() + theta, GetAnglePhi() + phi, GetLength(), w, true); }

// Convert to a Vector3.
Vector3 Vector4::ToVec3(bool homogenizeVec) const
{
    if (homogenizeVec) return Vector3(x / w, y / w, z / w);
    else               return Vector3(x, y, z);
}

// Debug string output.
const string Vector4::Debug()
{
    return string("x: ") + to_string(x)
               + ", y: " + to_string(y)
               + ", z: " + to_string(z)
               + ", w: " + to_string(w);
}