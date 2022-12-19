#pragma once

#include <iostream>
#include <string>

namespace Core::Maths
{
    class Vector3;
    template<int R, int C> class Matrix;

    typedef Matrix<2,2> Matrix2;
    typedef Matrix<3,3> Matrix3;
    typedef Matrix<4,4> Matrix4;

    template<int R, int C>
    class Matrix
    {
        public:
            float m[R][C];
            float* ptr = &m[0][0];

            Matrix(bool identity = false);
            Matrix(const Matrix<R,C>& matrix);

            // Matrix 2X2.
            Matrix(const float& a, const float& b, const float& c, const float& d);

            // Matrix 3X3.
            Matrix(const float& a, const float& b, const float& c,
                   const float& d, const float& e, const float& f,
                   const float& g, const float& h, const float& i);

            // Matrix 4X4.
            Matrix(const float& a, const float& b, const float& c, const float& d,
                   const float& e, const float& f, const float& g, const float& h,
                   const float& i, const float& j, const float& k, const float& l,
                   const float& M, const float& n, const float& o, const float& p);

            Matrix(const Matrix2& a, const Matrix2& b, const Matrix2& c, const Matrix2& d);
        
            Matrix(const float matrix[R][C]);

            float*       operator[](int index);    
            const float* operator[](int index) const;
            void         operator+=(const float& val);
            void         operator-=(const float &val);
            void         operator*=(const float &val);

            Matrix<R,C> operator=(const Matrix<R,C>& matrix);
            Matrix<R,C> operator=(float** matrix);
            Matrix<R,C> operator+(const float& val) const;
            Matrix<R,C> operator-();
            Matrix<R,C> operator-(const float& val) const;
            Matrix<R,C> operator*(const float& val) const;
            Matrix<R,C> operator/(const float& val) const;
            Matrix<R,C> operator^(const float& n) const;

            template<int _R, int _C> Matrix<R,C> operator+(const Matrix<_R,_C>& matrix) const;
            template<int _R, int _C> Matrix<R,C> operator-(const Matrix<_R,_C>& matrix) const;
            template<int _R, int _C> Matrix<(R > _R ? R : _R),(C > _C ? C : _C)> operator*(const Matrix<_R,_C>& matrix) const;
            template<int _R, int _C> void operator+=(const Matrix<_R,_C>& matrix);
            template<int _R, int _C> void operator-=(const Matrix<_R,_C>& matrix);

            int   GetRows();
            int   GetColumns();
            float GetMatrixValue(int i, int j);

            bool IsSquare();
            bool IsIdentity();

            float Det2();
            float Det3();
            float Det4();

            Matrix2 Inv2();
            Matrix3 Inv3();
            Matrix4 Inv4();

            Matrix<R, C> Transpose();

            std::string Debug() const;
    };

    // Matrix transform related getters.
    Matrix4 GetTranslationMatrix(const Vector3& translation);
    Matrix4 GetScaleMatrix      (const Vector3& scale);
    Matrix4 GetXRotationMatrix  (float angle);
    Matrix4 GetYRotationMatrix  (float angle);
    Matrix4 GetZRotationMatrix  (float angle);
    Matrix4 GetTransformMatrix  (const Vector3& position, const Vector3& rotation, const Vector3& scale, const bool& reverse);
}

#include "Matrix.inl"