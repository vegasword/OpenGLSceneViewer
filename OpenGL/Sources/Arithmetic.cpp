#include <cmath>

#include <Debug.h>
#include <Constants.h>
#include <Arithmetic.h>

// Rounds the given value to the nearest int.
int Core::Maths::RoundInt(const float& val) { return (int)round(val); }

// Rounds down the given value.
int Core::Maths::FloorInt(const float& val) { return (int)floor(val); }

// Rounds up the given value.
int Core::Maths::CeilInt(const float& val) { return (int)ceil(val); }

// Returns the sqare power of the given value.
float Core::Maths::Sqpow(const float& val) { return val * val; }

// Returns 1 if the given value is positive or null, and -1 if it is negative.
int Core::Maths::SignOf(const float& val) { if (val == 0) return 1; return (int)(val / abs((int)val)); }

// Converts the given angle from degrees to radians.
float Core::Maths::DegToRad(const float& deg) { return deg * (PI / 180.0f); }

// Converts the given angle from radians to degrees.
float Core::Maths::RadToDeg(const float& rad) { return rad * (180.0f / PI); }

// Clamps the given value to be superior or equal to the minimum value and inferior or equal to the maximum value.
float Core::Maths::Clamp(float val, const float& min, const float& max)
{
    Assert(min <= max, "Minimum should'nt be superior to maximum."); 
    if (val < min) val = min;
    if (val > max) val = max;
    return val;
}

// Clamps the given value to be inferior or equal to the maximum value.
float Core::Maths::ClampUnder(float val, const float& max) { if (val > max) val = max; return val; }

// Clamps the given value to be superior or equal to the minimum value.
float Core::Maths::ClampAbove(float val, const float& min) { if (val < min) val = min; return val; }

// Compute linear interpolation between start and end for the parameter val.
float Core::Maths::Lerp(const float& val, const float& start, const float& end) { return start + val * (end - start); }

// Compute the linear interpolation factor that returns val when lerping between start and end.
float Core::Maths::GetLerp(const float& val, const float& start, const float& end)
{
    if (end - start != 0) return (val - start) / (end - start);
    return 0;
}

// Remaps the given value from one range to another.
float Core::Maths::Remap(const float& val, const float& inputStart, const float& inputEnd, const float& outputStart, const float& outputEnd)
{
    return outputStart + (val - inputStart) * (outputEnd - outputStart) / (inputEnd - inputStart);
}

// Returns true if the given number is a power of 2.
bool Core::Maths::IsPowerOf2(const int& val)
{
    return val == (int)pow(2, (int)(log(val)/log(2)));
}

// Returns the closest power of 2 that is inferior or equal to val.
int Core::Maths::GetPowerOf2Under(const int& val)
{
    return (int)pow(2, (int)(log(val)/log(2)));
}

// Returns the closest power of 2 that is superior or equal to val.
int Core::Maths::GetPowerOf2Above(const int& val)
{
    if (IsPowerOf2(val))
        return (int)pow(2, (int)(log(val)/log(2)));
    else
        return (int)pow(2, (int)(log(val)/log(2)) + 1);
} 