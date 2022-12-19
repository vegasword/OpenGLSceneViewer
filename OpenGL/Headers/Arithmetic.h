#pragma once

namespace Core::Maths
{
    
    int RoundInt(const float& val);   // Rounds the given value to the nearest int.
    int FloorInt(const float& val);   // Rounds down the given value.
    int CeilInt(const float& val);    // Rounds up the given value.
    float Sqpow(const float& val);    // Returns the sqare power of the given value.
    int SignOf(const float& val);     // Returns 1 if the given value is positive or null, and -1 if it is negative.
    float DegToRad(const float& deg); // Converts the given angle from degrees to radians.
    float RadToDeg(const float& rad); // Converts the given angle from radians to degrees.

    float Clamp(float val, const float& min, const float& max); // Clamps the given value between a minimum and maximum value.
    float ClampUnder(float val, const float& max);              // Clamps the given value to be inferior or equal to the maximum value.
    float ClampAbove(float val, const float& min);              // Clamps the given value to be superior or equal to the minimum value.

    float Lerp(const float& val, const float& start, const float& end);    // Compute linear interpolation between start and end for the parameter val.
    float GetLerp(const float& val, const float& start, const float& end); // Compute the linear interpolation factor that returns val when lerping between start and end.
    float Remap(const float& val, const float& iStart, const float& iEnd, const float& oStart, const float& oEnd); // Remaps the given value from one range to another.

    bool IsPowerOf2(const int& val); // Returns true if the given number is a power of 2.
    int GetPowerOf2Under(const int& val); // Returns the closest power of 2 that is inferior or equal to val.
    int GetPowerOf2Above(const int& val); // Returns the closest power of 2 that is superior or equal to val.
}