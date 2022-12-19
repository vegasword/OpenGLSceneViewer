#include <Debug.h>
#include <Vector3.h>
#include <Matrix.h>

using namespace std;
using namespace Core::Maths;

// ===================================================================
// Matrix transform realted getters.
// ===================================================================

Matrix4 Core::Maths::GetTranslationMatrix(const Vector3& translation)
{
    return Matrix4(1,              0,             0,               0,
                   0,              1,             0,               0,
                   0,              0,             1,               0,
                   translation.x,  translation.y, translation.z,   1);
}

Matrix4 Core::Maths::GetScaleMatrix(const Vector3& scale)
{
    return Matrix4(scale.x, 0,       0,       0,
                   0,       scale.y, 0,       0,
                   0,       0,       scale.z, 0,
                   0,       0,       0,       1);
}

Matrix4 Core::Maths::GetXRotationMatrix(float angle)
{
    return Matrix4(1, 0,            0,           0,
                   0, cosf(angle), -sinf(angle), 0,
                   0, sinf(angle),  cosf(angle), 0,
                   0, 0,            0,           1);
}

Matrix4 Core::Maths::GetYRotationMatrix(float angle)
{
    return Matrix4(cosf(angle),  0, sinf(angle), 0,
                   0,            1, 0,           0,
                   -sinf(angle), 0, cosf(angle), 0,
                   0,            0, 0,           1);
}

Matrix4 Core::Maths::GetZRotationMatrix(float angle)
{
    return Matrix4(cosf(angle), -sinf(angle),  0, 0,
                   sinf(angle),  cosf(angle),  0, 0,
                   0,            0,            1, 0,
                   0,            0,            0, 1 );
}

Matrix4 Core::Maths::GetTransformMatrix(const Vector3& position, const Vector3& rotation, const Vector3& scale, const bool& reverse)
{
    // For cameras.
    if (reverse)
    {
        return GetTranslationMatrix(position)   *
               GetYRotationMatrix  (rotation.y) *
               GetXRotationMatrix  (rotation.x) * 
               GetZRotationMatrix  (rotation.z) *
               GetScaleMatrix      (scale);
    }
    // For objects in world space.
    else
    {
        return GetScaleMatrix      (scale)      *
               GetZRotationMatrix  (rotation.z) *
               GetXRotationMatrix  (rotation.x) * 
               GetYRotationMatrix  (rotation.y) *
               GetTranslationMatrix(position);
    }
}