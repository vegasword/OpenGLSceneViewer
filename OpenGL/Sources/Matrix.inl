#include <sstream>
#include <string>

#include <Debug.h>
#include <Vector3.h>
#include <Matrix.h>

using namespace std;
using namespace Core::Maths;

// ===================================================================
// Matrix constructors.
// ===================================================================

// Identity matrix constructor.
template<int R, int C> Matrix<R,C>::Matrix(bool identity) 
{ 
    Assert(R >= 2 && C >= 2, "Matrix dimension must be higher or equal than 2.");

    if (!identity)
    {
        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++)
                m[i][j] = 0;
    }
    else
    {
        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++)
                if (i == j) m[i][j] = 1;
                else        m[i][j] = 0;
    }
}

// Copy constructor.
template<int R, int C> Matrix<R,C>::Matrix(const Matrix<R,C>& matrix)
{
    Assert(R >= 2 && C >= 2, "Matrix dimension must be higher or equal than 2.");

    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            m[i][j] = matrix[i][j];
}

// Matrix 2X2.
template<int R, int C> Matrix<R,C>::Matrix(const float& a, const float& b, const float& c, const float& d)
{
    Assert(R == 2 && C == 2, "Matrix dimension must be equal to 2.");

    m[0][0] = a; m[0][1] = b;
    m[1][0] = c; m[1][1] = d;
}

// Matrix 3X3.
template<int R, int C> Matrix<R,C>::Matrix(const float& a, const float& b, const float& c,
                                           const float& d, const float& e, const float& f,
                                           const float& g, const float& h, const float& i)
{
    Assert(R == 3 && C == 3, "Matrix dimension must be equal to 3.");

    m[0][0] = a; m[0][1] = b; m[0][2] = c;
    m[1][0] = d; m[1][1] = e; m[1][2] = f;
    m[2][0] = g; m[2][1] = h; m[2][2] = i;
}

// Matrix 4X4.
template<int R, int C> Matrix<R,C>::Matrix(const float& a, const float& b, const float& c, const float& d,
                                           const float& e, const float& f, const float& g, const float& h,
                                           const float& i, const float& j, const float& k, const float& l,
                                           const float& M, const float& n, const float& o, const float& p)
{
    Assert(R == 4 && C == 4, "Matrix dimension must be equal to 4.");

    m[0][0] = a; m[0][1] = b; m[0][2] = c; m[0][3] = d;
    m[1][0] = e; m[1][1] = f; m[1][2] = g; m[1][3] = h;
    m[2][0] = i; m[2][1] = j; m[2][2] = k; m[2][3] = l;
    m[3][0] = M; m[3][1] = n; m[3][2] = o; m[3][3] = p;
}

// Matrix 4x4 (from 2x2 matrices).
template<int R, int C> Matrix<R,C>::Matrix(const Matrix2& a, const Matrix2& b, const Matrix2& c, const Matrix2& d)
{
    Assert(R == 4 && C == 4, "Matrix dimension must be equal to 4.");

    m[0][0] = a[0][0]; m[0][1] = a[0][1]; m[0][2] = b[0][0]; m[0][3] = b[0][1];
    m[1][0] = a[1][0]; m[1][1] = a[1][1]; m[1][2] = b[1][0]; m[1][3] = b[1][1];
    m[2][0] = c[0][0]; m[2][1] = c[0][1]; m[2][2] = d[0][0]; m[2][3] = d[0][1];
    m[3][0] = c[1][0]; m[3][1] = c[1][1]; m[3][2] = d[1][0]; m[3][3] = d[1][1];
}
        
// Bi-dimensional array initialization.
template<int R, int C> Matrix<R,C>::Matrix(const float matrix[R][C])
{
    Assert(R > 4 && C > 4, "Matrix dimension must be higher than 4.");

    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            m[i][j] = matrix[i][j];
}

// ===================================================================
// Matrix operators.
// ===================================================================

// Matrix bracket Matrix<R,C>::operators.
template<int R, int C> float*       Matrix<R,C>::operator[](int index)       { return m[index]; }
template<int R, int C> const float* Matrix<R,C>::operator[](int index) const { return m[index]; }

// Matrix copy.
template<int R, int C> Matrix<R,C> Matrix<R,C>::operator=(const Matrix<R,C>& matrix)
{
    if (&matrix == this) return *this;
            
    // Matrix content copy.
    for (int i = 0; i < R; i++) 
        for (int j = 0; j < C; j++)
            m[i][j] = matrix[i][j];
            
    return *this;
}

template<int R, int C> Matrix<R,C> Matrix<R,C>::operator=(float** matrix)
{
    Assert((sizeof(matrix) / sizeof(float) == R * C), "Copied array dimension must be equal to the source matrix.");

    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            m[i][j] = matrix[i][j];

    return *this;
}

// Matrix addition operators.
template<int R, int C> Matrix<R,C> Matrix<R,C>::operator+(const float& val) const
{
    Matrix<R,C> tmp;

    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            tmp[i][j] = m[i][j] + val;

    return tmp;
}

template<int R, int C> template<int _R, int _C>
Matrix<R,C> Matrix<R,C>::operator+(const Matrix<_R,_C>& matrix) const
{
    Assert(R == _R && C == _C, "Matrix dimension must be equal to the summed one."); // Matrix must have the same dimension
                
    Matrix<_R,_C> tmp;

    for(int i = 0; i < R; i++)
        for(int j = 0; j < C; j++)
            tmp[i][j] = m[i][j] + matrix[i][j];

    return tmp;
}

// Matrix substraction and inversion operators.
template<int R, int C> Matrix<R,C> Matrix<R,C>::operator-() 
{
    Matrix<R,C> tmp;

    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            tmp[i][j] = -m[i][j];

    return tmp;
}

template<int R, int C> Matrix<R,C> Matrix<R,C>::operator-(const float& val) const
{
    Matrix<R,C> tmp;
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            tmp[i][j] = m[i][j] - val;
    return tmp;
}

template<int R, int C> template<int _R, int _C>
Matrix<R,C> Matrix<R,C>::operator-(const Matrix<_R,_C>& matrix) const
{
    Assert(R == _R && C == _C, "Matrix dimension must be equal to the subtracted one.");

    Matrix<_R,_C> tmp;

    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            tmp[i][j] = m[i][j] - matrix[i][j];

    return tmp;
}


// Matrix multiplication operators.
template<int R, int C> Matrix<R,C> Matrix<R,C>::operator*(const float& val) const
{
    Matrix<R,C> tmp;

    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            tmp[i][j] = m[i][j] * val;

    return tmp;
}

template<int R, int C> template<int _R, int _C>
Matrix<(R > _R ? R : _R),(C > _C ? C : _C)> Matrix<R,C>::operator*(const Matrix<_R,_C>& matrix) const
{
    Assert(C == _R,  "The number of columns of the matrix 1 must be equal to the numbers of rows of the matrix 2.");

    Matrix<(R > _R ? R : _R),(C > _C ? C : _C)> result;

    for (int i = 0; i < R; i++)
        for (int j = 0; j < _C; j++)
        {
            result[i][j] = 0;
            for (int k = 0; k < _R; k++)
                result[i][j] += m[i][k] * matrix[k][j];
        }

    return result;
}

// Division by a scalar operator.
template<int R, int C> Matrix<R,C> Matrix<R,C>::operator/(const float& val) const
{
    Matrix<R,C> tmp;

    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            tmp[i][j] = m[i][j] / val;

    return tmp;
}

// addition assignement operators.
template<int R, int C> void Matrix<R,C>::operator+=(const float& val)
{
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            m[i][j] += val;
}

template<int R, int C> template<int _R, int _C>
void Matrix<R,C>::operator+=(const Matrix<_R,_C>& matrix)
{
    Assert(R == _R && C == _C, "Matrices dimensions must be the same.");

    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            m[i][j] += matrix[i][j];
}

// Matrix substraction assignement.
template<int R, int C> void Matrix<R,C>::operator-=(const float &val)
{
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            m[i][j] -= val;
}

template<int R, int C> template<int _R, int _C>
void Matrix<R,C>::operator-=(const Matrix<_R,_C>& matrix)
{
    Assert(R == _R && C == _C, "Matrices dimensions must be the same.");

    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            m[i][j] -= matrix[i][j];
}

// Multiplication assignement operators.
template<int R, int C> void Matrix<R,C>::operator*=(const float &val)
{
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            m[i][j] *= val;
}

// Matrix power operator.
template<int R, int C> Matrix<R,C> Matrix<R,C>::operator^(const float& n) const
{
    Matrix<R,C> tmp;

    for (int n0 = 0; n0 < n; n0++)
        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++)
                tmp[i][j] *= m[i][j];

    return tmp;
}

// ===================================================================
// Matrix methods.
// ===================================================================

// Getters.
template<int R, int C> int   Matrix<R,C>::GetRows()    { return R; }
template<int R, int C> int   Matrix<R,C>::GetColumns() { return C; }  
template<int R, int C> float Matrix<R,C>::GetMatrixValue(int i, int j) { return m[i][j]; }

// Arithmetic.
template<int R, int C> bool Matrix<R,C>::IsSquare() { return R == C; }

template<int R, int C> bool Matrix<R,C>::IsIdentity()
{
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            if ((i != j && m[i][j] != 0) || (i == j && m[i][j] != 1))
                return false;

    return true;
}

// Determinants.
template<int R, int C> float Matrix<R,C>::Det2() 
{ 
    return (m[0][0] * m[1][1]) - (m[0][1] * m[1][0]); 
}

template<int R, int C> float Matrix<R,C>::Det3()
{
    return m[0][0] * Matrix2{m[1][1], m[1][2], m[2][1], m[2][2]}.Det2() - 
            m[0][1] * Matrix2{m[1][0], m[1][2], m[2][0], m[2][2]}.Det2() + 
            m[0][2] * Matrix2{m[1][0], m[1][1], m[2][0], m[2][1]}.Det2();
}

template<int R, int C> float Matrix<R,C>::Det4()
{
    Matrix3 a(m[1][1], m[1][2], m[1][3], m[2][1], m[2][2], m[2][3], m[3][1], m[3][2], m[3][3]);
    Matrix3 b(m[1][0], m[1][2], m[1][3], m[2][0], m[2][2], m[2][3], m[3][0], m[3][2], m[3][3]);
    Matrix3 c(m[1][0], m[1][1], m[1][3], m[2][0], m[2][1], m[2][3], m[3][0], m[3][1], m[3][3]);
    Matrix3 d(m[1][0], m[1][1], m[1][2], m[2][0], m[2][1], m[2][2], m[3][0], m[3][1], m[3][2]);

    return (a.Det3() * m[0][0] - b.Det3() * m[0][1] + c.Det3() * m[0][2] - d.Det3() * m[0][3]);
}

// Inverses.
template<int R, int C> Matrix2 Matrix<R,C>::Inv2()
{
    Matrix2 val(m[1][1], -m[0][1], -m[1][0], m[0][0]);
    return val / val.Det2();
}

template<int R, int C> Matrix3 Matrix<R,C>::Inv3()
{
    Matrix4 val(m[0][0], m[0][1], m[0][2], 0,
                m[1][0], m[1][1], m[1][2], 0,
                m[2][0], m[2][1], m[2][2], 0,
                0,       0,       0,       1);

    val = val.Inv4();

    Matrix3 result(val.m[0][0], val.m[0][1], val.m[0][2],
                    val.m[1][0], val.m[1][1], val.m[1][2],
                    val.m[2][0], val.m[2][1], val.m[2][2]);

    return result;
}

template<int R, int C> Matrix4 Matrix<R,C>::Inv4()
{
    Matrix2 a(m[0][0], m[0][1], m[1][0], m[1][1]);
    Matrix2 b(m[0][2], m[0][3], m[1][2], m[1][3]);
    Matrix2 c(m[2][0], m[2][1], m[3][0], m[3][1]);
    Matrix2 d(m[2][2], m[2][3], m[3][2], m[3][3]);
            
    Matrix4 result =
    {
        (a - b * d.Inv2() * c).Inv2(), -(a - b * d.Inv2() * c).Inv2() * b * d.Inv2(),
       -(d - c * a.Inv2() * b).Inv2() * c * a.Inv2(),  (d - c * a.Inv2() * b).Inv2()
    };

    return result;
}

// Transposition.
template<int R, int C> Matrix<R, C> Matrix<R,C>::Transpose()
{
    Matrix<C, R> result;

    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            result[j][i] = m[i][j];

    return result;
}

// Debug output (to c_str into logger).
template<int R, int C> string Matrix<R,C>::Debug() const
{
    ostringstream tmp;

    tmp << "\n" << "Matrix<" << R << ", " << C << ">\n";

    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
            tmp << m[i][j] << " ";
        tmp << "\n";
    }
    tmp << "\n";

    return tmp.str();
}