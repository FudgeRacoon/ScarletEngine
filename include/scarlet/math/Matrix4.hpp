#ifndef MATRIX4_HPP
#define MATRIX4_HPP

#include <math.h>

#include "scarlet/common/Types.hpp"

#include "scarlet/math/Math.hpp"
#include "scarlet/math/Vector4.hpp"
using namespace scarlet;

class Matrix4
{
private:
    float n[4][4];

public:
    Matrix4()
    {
        this->n[0][0] = 0; this->n[0][1] = 0; this->n[0][2] = 0; this->n[0][3] = 0;
        this->n[1][0] = 0; this->n[1][1] = 0; this->n[1][2] = 0; this->n[1][3] = 0;
        this->n[2][0] = 0; this->n[2][1] = 0; this->n[2][2] = 0; this->n[2][3] = 0;
        this->n[3][0] = 0; this->n[3][1] = 0; this->n[3][2] = 0; this->n[3][3] = 0;
    }
    Matrix4(float n00, float n01, float n02, float n03,
            float n10, float n11, float n12, float n13,
            float n20, float n21, float n22, float n23,
            float n30, float n31, float n32, float n33)
    {
        this->n[0][0] = n00; this->n[0][1] = n01; this->n[0][2] = n02; this->n[0][3] = n03;
        this->n[1][0] = n10; this->n[1][1] = n11; this->n[1][2] = n12; this->n[1][3] = n13;
        this->n[2][0] = n20; this->n[2][1] = n21; this->n[2][2] = n22; this->n[2][3] = n23;
        this->n[3][0] = n30; this->n[3][1] = n31; this->n[3][2] = n32; this->n[3][3] = n33;
    }
    Matrix4(Vector4& v1, Vector4& v2, Vector4& v3, Vector4& v4)
    {
        this->n[0][0] = v1.x; this->n[0][1] = v1.y; this->n[0][2] = v1.z; this->n[0][3] = v1.w;
        this->n[1][0] = v2.x; this->n[1][1] = v2.y; this->n[1][2] = v2.z; this->n[1][3] = v2.w;
        this->n[2][0] = v3.x; this->n[2][1] = v3.y; this->n[2][2] = v3.z; this->n[2][3] = v3.w;
        this->n[3][0] = v4.x; this->n[3][1] = v4.y; this->n[3][2] = v4.z; this->n[3][3] = v4.w;
    }

public:
    float operator ()(int row, int column)
    {
        return this->n[row][column];
    }
    Matrix4 operator +(Matrix4 m)
    {
        return Matrix4
        (
            this->n[0][0] + m.n[0][0], this->n[0][1] + m.n[0][1], this->n[0][2] + m.n[0][2], this->n[0][3] + m.n[0][3],
            this->n[1][0] + m.n[1][0], this->n[1][1] + m.n[1][1], this->n[1][2] + m.n[1][2], this->n[1][3] + m.n[1][3],
            this->n[2][0] + m.n[2][0], this->n[2][1] + m.n[2][1], this->n[2][2] + m.n[2][2], this->n[2][3] + m.n[2][3],
            this->n[3][0] + m.n[3][0], this->n[3][1] + m.n[3][1], this->n[3][2] + m.n[3][2], this->n[3][3] + m.n[3][3]
        );
    }
    Matrix4 operator -(Matrix4 m)
    {
        return Matrix4
        (
            this->n[0][0] - m.n[0][0], this->n[0][1] - m.n[0][1], this->n[0][2] - m.n[0][2], this->n[0][3] - m.n[0][3],
            this->n[1][0] - m.n[1][0], this->n[1][1] - m.n[1][1], this->n[1][2] - m.n[1][2], this->n[1][3] - m.n[1][3],
            this->n[2][0] - m.n[2][0], this->n[2][1] - m.n[2][1], this->n[2][2] - m.n[2][2], this->n[2][3] - m.n[2][3],
            this->n[3][0] - m.n[3][0], this->n[3][1] - m.n[3][1], this->n[3][2] - m.n[3][2], this->n[3][3] - m.n[3][3]
        );
    }
    Matrix4 operator *(Matrix4 m)
    {
        return Matrix4
        (
            this->n[0][0] * m.n[0][0] + this->n[0][1] * m.n[1][0] + this->n[0][2] * m.n[2][0] + this->n[0][3] * m.n[3][0],
            this->n[0][0] * m.n[0][1] + this->n[0][1] * m.n[1][1] + this->n[0][2] * m.n[2][1] + this->n[0][3] * m.n[3][1],
            this->n[0][0] * m.n[0][2] + this->n[0][1] * m.n[1][2] + this->n[0][2] * m.n[2][2] + this->n[0][3] * m.n[3][2],
            this->n[0][0] * m.n[0][3] + this->n[0][1] * m.n[1][3] + this->n[0][2] * m.n[2][3] + this->n[0][3] * m.n[3][3],

            this->n[1][0] * m.n[0][0] + this->n[1][1] * m.n[1][0] + this->n[1][2] * m.n[2][0] + this->n[1][3] * m.n[3][0],
            this->n[1][0] * m.n[0][1] + this->n[1][1] * m.n[1][1] + this->n[1][2] * m.n[2][1] + this->n[1][3] * m.n[3][1],
            this->n[1][0] * m.n[0][2] + this->n[1][1] * m.n[1][2] + this->n[1][2] * m.n[2][2] + this->n[1][3] * m.n[3][2],
            this->n[1][0] * m.n[0][3] + this->n[1][1] * m.n[1][3] + this->n[1][2] * m.n[2][3] + this->n[1][3] * m.n[3][3],

            this->n[2][0] * m.n[0][0] + this->n[2][1] * m.n[1][0] + this->n[2][2] * m.n[2][0] + this->n[2][3] * m.n[3][0],
            this->n[2][0] * m.n[0][1] + this->n[2][1] * m.n[1][1] + this->n[2][2] * m.n[2][1] + this->n[2][3] * m.n[3][1],
            this->n[2][0] * m.n[0][2] + this->n[2][1] * m.n[1][2] + this->n[2][2] * m.n[2][2] + this->n[2][3] * m.n[3][2],
            this->n[2][0] * m.n[0][3] + this->n[2][1] * m.n[1][3] + this->n[2][2] * m.n[2][3] + this->n[2][3] * m.n[3][3],

            this->n[3][0] * m.n[0][0] + this->n[3][1] * m.n[1][0] + this->n[3][2] * m.n[2][0] + this->n[3][3] * m.n[3][0],
            this->n[3][0] * m.n[0][1] + this->n[3][1] * m.n[1][1] + this->n[3][2] * m.n[2][1] + this->n[3][3] * m.n[3][1],
            this->n[3][0] * m.n[0][2] + this->n[3][1] * m.n[1][2] + this->n[3][2] * m.n[2][2] + this->n[3][3] * m.n[3][2],
            this->n[3][0] * m.n[0][3] + this->n[3][1] * m.n[1][3] + this->n[3][2] * m.n[2][3] + this->n[3][3] * m.n[3][3]
        );
    }
    Vector4 operator * (Vector4 v)
    {
        return Vector4
        (
            this->n[0][0] * v.x + this->n[0][1] * v.y + this->n[0][2] * v.z + this->n[0][3] * v.w,
            this->n[1][0] * v.x + this->n[1][1] * v.y + this->n[1][2] * v.z + this->n[1][3] * v.w,
            this->n[2][0] * v.x + this->n[2][1] * v.y + this->n[2][2] * v.z + this->n[2][3] * v.w,
            this->n[3][0] * v.x + this->n[3][1] * v.y + this->n[3][2] * v.z + this->n[3][3] * v.w
        );
    }

public:
    const float* GetValuePointer()
    {
        return &n[0][0];
    }

public:
    static Matrix4 Identity()
    {
        return Matrix4
        (
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        );
    }
    static Matrix4 Transalte(Vector3 translate)
    {
        Matrix4 m = Identity();

        m.n[0][3] = translate.x;
        m.n[1][3] = translate.y;
        m.n[2][3] = translate.z;

        return m;
    }
    static Matrix4 Scale(Vector3 scale)
    {
        Matrix4 m = Identity();

        m.n[0][0] = scale.x;
        m.n[1][1] = scale.y;
        m.n[2][2] = scale.z;

        return m;
    }
    static Matrix4 Rotate(float angle, Vector3 axis)
    {
        Matrix4 m = Identity();

        if(axis.x == 1.0f && axis.y == 0.0f && axis.z == 0.0f)
        {
            m.n[1][1] = cos(angle);
            m.n[1][2] = sin(angle);
            m.n[2][1] = -sin(angle);
            m.n[2][2] = cos(angle);
        }
        else if(axis.x == 0.0f && axis.y == 1.0f && axis.z == 0.0f)
        {
            m.n[0][0] = cos(angle);
            m.n[0][2] = -sin(angle);
            m.n[2][0] = sin(angle);
            m.n[2][2] = cos(angle);
        }
        else if(axis.x == 0.0f && axis.y == 0.0f, axis.z == -1.0f)
        {
            m.n[0][0] = cos(angle);
            m.n[0][1] = -sin(angle);
            m.n[1][0] = sin(angle);
            m.n[1][1] = cos(angle);
        }

        return m;
    }
    static Matrix4 LookAt(Vector3 position, Vector3 target, Vector3 up)
    {
        Vector3 z = Vector3::Normalize(target - position);
        Vector3 x = Vector3::Normalize(Vector3::Cross(z, up));
        Vector3 y = Vector3::Normalize(Vector3::Cross(x, z));

        z = -z;

        return Matrix4
        (
            x.x, x.y, x.z, -Vector3::Dot(x, position),
            y.x, y.y, y.z, -Vector3::Dot(y, position),
            z.x, z.y, z.z, -Vector3::Dot(z, position),
            0  , 0  , 0  , 1
        );  
    }
    static Matrix4 Orthographic(float left, float right, float bottom, float top, float nearr, float farr)
    {   
        // | xOut   0      0      tx |
        // | 0     yOut    0      ty |
        // | 0      0     zOut    tz |
        // | 0      0      0       1 |

        Matrix4 m = Identity();

        float xOut = 2 / (right - left);
        float yOut = 2 / (top - bottom);
        float zOut = 2 / (farr - nearr);

        float tx = -(right + left) / (right - left);
        float ty = -(top + bottom) / (top - bottom);
        float tz = -(farr + nearr) / (farr - nearr);

        m.n[0][0] = xOut;
        m.n[1][1] = yOut;
        m.n[2][2] = zOut;
        m.n[0][3] = tx;
        m.n[1][3] = ty;
        m.n[2][3] = tz;

        return m;
    }

public:
    static Matrix4 Inverse(Matrix4 m)
    {
        Matrix4 mat = Identity();

        for(uint32 column = 0; column < 4; column++) 
        { 
            if(m(column,column) == 0) 
            { 
                uint32 big = column; 

                for(uint32 row = 0; row < 4; row++)
                    if(Math::Abs(m(row,column)) > Math::Abs(m(big,column))) 
                        big = row;
                
                if(big != column)
                    for(uint32 j = 0; j < 4; ++j)
                    {
                        Math::Swap<float>(&m.n[column][j], &m.n[big][j]); 
                        Math::Swap<float>(&mat.n[column][j], &mat.n[big][j]);
                    } 
            }  
        
            for (uint32 row = 0; row < 4; row++) 
            { 
                if(row != column) 
                { 
                    float coeff = m(row,column) / m(column,column); 

                    if (coeff != 0) 
                    { 
                        for (uint32 j = 0; j < 4; j++) 
                        { 
                            m.n[row][j] -= coeff * m(column,j); 
                            mat.n[row][j] -= coeff * mat(column,j); 
                        } 
                        
                        m.n[row][column] = 0; 
                    } 
                } 
            }
        } 
    
        for(uint32 row = 0; row < 4; row++) 
            for(uint32 column = 0; column < 4; column++) 
                mat.n[row][column] /= m(row,row);

        return mat;          
    }
};

#endif