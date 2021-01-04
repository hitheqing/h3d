//
// Created by heqhe on 2021/1/4.
//

#ifndef H3D_SRC_MATH_MATRIX4X4_H
#define H3D_SRC_MATH_MATRIX4X4_H

#pragma once

#include "vector4.h"

#define PI_F 3.14159265358979323846264338327950288f
#define Radians(v) ((v) * (PI_F / 180.0f))

namespace Hyhy {
    /*
     * 列矩阵
     */
    class Matrix44 {
    public:
        union {
            Vector4 cols[4];
            float data[16] = {};
        };


        Matrix44() {}

        // 构造正交矩阵
        Matrix44(float v) {
            data[0] = data[5] = data[10] = data[15] = v;
        }
        Matrix44(const Matrix44&) = default;
        Matrix44& operator=(const Matrix44&) = default;

        // 从列向量构造矩阵
        Matrix44(const Vector4& col1, const Vector4& col2, const Vector4& col3, const Vector4& col4) {
            cols[0] = col1;
            cols[1] = col1;
            cols[2] = col2;
            cols[3] = col3;
        }


        friend bool operator==(const Matrix44& l, const Matrix44& r) {
            for (int i = 0; i < 16; i++)
                if (l.data[i] != r.data[i])
                    return false;
            return true;
        }

        friend bool operator!=(const Matrix44& lhs, const Matrix44& rhs) { return !(lhs == rhs); }

        // 列矩阵索引
        Vector4& operator[](int idx) {
//			assert(idx >= 0 && idx <= 3);
            return cols[idx];
        }
        Vector4 operator[](int idx) const {
//			assert(idx >= 0 && idx <= 3);
            return cols[idx];
        }

        // operators +-*/
        Matrix44 operator+=(const Matrix44& m) {
            for (int i = 0; i < 4; i++)
                cols[i] += m.cols[i];
            return *this;
        }
        Matrix44 operator-=(const Matrix44& m) {
            for (int i = 0; i < 4; i++)
                cols[i] -= m.cols[i];
            return *this;
        }

        Matrix44 operator+=(float s) {
            for (auto& col : cols)
                col += s;
            return *this;
        }
        Matrix44 operator-=(float s) {
            for (auto& col : cols)
                col -= s;
            return *this;
        }
        Matrix44 operator*=(float s) {
            for (auto& col : cols)
                col *= s;
            return *this;
        }
        Matrix44 operator/=(float s) {
            for (auto& col : cols)
                col /= s;
            return *this;
        }

        Matrix44 operator+(const Matrix44& m) const {
            Matrix44 r;
            for (int i = 0; i < 4; i++)
                r.cols[i] = cols[i] + m.cols[i];
            return r;
        }
        Matrix44 operator-(const Matrix44& m) const {
            Matrix44 r;
            for (int i = 0; i < 4; i++)
                r.cols[i] = cols[i] - m.cols[i];
            return r;
        }

        Matrix44 operator+(float s) const {
            Matrix44 r;
            for (int i = 0; i < 4; i++)
                r.cols[i] = cols[i] + s;
            return r;
        }
        Matrix44 operator-(float s) const {
            Matrix44 r;
            for (int i = 0; i < 4; i++)
                r.cols[i] = cols[i] - s;
            return r;
        }
        Matrix44 operator*(float s) const {
            Matrix44 r;
            for (int i = 0; i < 4; i++)
                r.cols[i] = cols[i] * s;
            return r;
        }
        Matrix44 operator/(float s) const {
            Matrix44 r;
            for (int i = 0; i < 4; i++)
                r.cols[i] = cols[i] / s;
            return r;
        }

        Matrix44 operator*=(const Matrix44& v) {
            *this = *this * v;
            return *this;
        }
        Matrix44 operator*(const Matrix44& m) const {
            Matrix44 ret;
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    ret[i][j] = 0.0f;
                    for (int k = 0; k < 4; k++) {
                        ret[i][j] += m[i][k] * cols[k][j];
                    }
                }
            }
            return ret;
        }

        // Returns determinant(brute force).
        float det() const {
            return
                    cols[0][3] * cols[1][2] * cols[2][1] * cols[3][0] -
                    cols[0][2] * cols[1][3] * cols[2][1] * cols[3][0] -
                    cols[0][3] * cols[1][1] * cols[2][2] * cols[3][0] +
                    cols[0][1] * cols[1][3] * cols[2][2] * cols[3][0] +
                    cols[0][2] * cols[1][1] * cols[2][3] * cols[3][0] -
                    cols[0][1] * cols[1][2] * cols[2][3] * cols[3][0] -
                    cols[0][3] * cols[1][2] * cols[2][0] * cols[3][1] +
                    cols[0][2] * cols[1][3] * cols[2][0] * cols[3][1] +
                    cols[0][3] * cols[1][0] * cols[2][2] * cols[3][1] -
                    cols[0][0] * cols[1][3] * cols[2][2] * cols[3][1] -
                    cols[0][2] * cols[1][0] * cols[2][3] * cols[3][1] +
                    cols[0][0] * cols[1][2] * cols[2][3] * cols[3][1] +
                    cols[0][3] * cols[1][1] * cols[2][0] * cols[3][2] -
                    cols[0][1] * cols[1][3] * cols[2][0] * cols[3][2] -
                    cols[0][3] * cols[1][0] * cols[2][1] * cols[3][2] +
                    cols[0][0] * cols[1][3] * cols[2][1] * cols[3][2] +
                    cols[0][1] * cols[1][0] * cols[2][3] * cols[3][2] -
                    cols[0][0] * cols[1][1] * cols[2][3] * cols[3][2] -
                    cols[0][2] * cols[1][1] * cols[2][0] * cols[3][3] +
                    cols[0][1] * cols[1][2] * cols[2][0] * cols[3][3] +
                    cols[0][2] * cols[1][0] * cols[2][1] * cols[3][3] -
                    cols[0][0] * cols[1][2] * cols[2][1] * cols[3][3] -
                    cols[0][1] * cols[1][0] * cols[2][2] * cols[3][3] +
                    cols[0][0] * cols[1][1] * cols[2][2] * cols[3][3];
        }

        Vector4 mul(const Vector4& v) const {
            return v[0] * cols[0] + v[1] * cols[1] + v[2] * cols[2] + v[3] * cols[3];
        }

        // 对向量进行变换
        Vector3 mul(const Vector3& v) const { return mul(Vector4(v, 1.0f)).project(); }

        // 单位正交矩阵
        static Matrix44 identity();

        // 转置矩阵
        static Matrix44 transpose(const Matrix44& m);

        //逆矩阵
        static Matrix44 inverse(const Matrix44& m);

        // 平移变换矩阵
        static Matrix44 translate(Vector3 t);

        // 绕轴旋转矩阵，phi为角度（degree）
        static Matrix44 rotate(const Vector3& axis, float phi);

        // 缩放矩阵
        static Matrix44 scale(const Vector3& scale);

        // 站在pos朝向target看，向上为up
        static Matrix44 lookat(const Vector3& pos, const Vector3& target, const Vector3& up = Vector3(0, 1, 0));

        //正交变换矩阵
        static Matrix44 ortho(float l, float r, float b, float t, float n, float f);

        //透视变换矩阵
        static Matrix44 perspective(float fov, float ar, float n);
    };

    inline Matrix44 Matrix44::identity() {
        return Matrix44(1.f);
    }

    inline Matrix44 Matrix44::transpose(const Matrix44& m) {
        Matrix44 r;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                r[i][j] = m[j][i];
            }
        }
        return r;
    }

    inline Matrix44 Matrix44::inverse(const Matrix44& m) {
        Matrix44 r;
        r[0][0] = m[1][2] * m[2][3] * m[3][1] - m[1][3] * m[2][2] * m[3][1] +
                  m[1][3] * m[2][1] * m[3][2] - m[1][1] * m[2][3] * m[3][2] -
                  m[1][2] * m[2][1] * m[3][3] + m[1][1] * m[2][2] * m[3][3];
        r[0][1] = m[0][3] * m[2][2] * m[3][1] - m[0][2] * m[2][3] * m[3][1] -
                  m[0][3] * m[2][1] * m[3][2] + m[0][1] * m[2][3] * m[3][2] +
                  m[0][2] * m[2][1] * m[3][3] - m[0][1] * m[2][2] * m[3][3];
        r[0][2] = m[0][2] * m[1][3] * m[3][1] - m[0][3] * m[1][2] * m[3][1] +
                  m[0][3] * m[1][1] * m[3][2] - m[0][1] * m[1][3] * m[3][2] -
                  m[0][2] * m[1][1] * m[3][3] + m[0][1] * m[1][2] * m[3][3];
        r[0][3] = m[0][3] * m[1][2] * m[2][1] - m[0][2] * m[1][3] * m[2][1] -
                  m[0][3] * m[1][1] * m[2][2] + m[0][1] * m[1][3] * m[2][2] +
                  m[0][2] * m[1][1] * m[2][3] - m[0][1] * m[1][2] * m[2][3];
        r[1][0] = m[1][3] * m[2][2] * m[3][0] - m[1][2] * m[2][3] * m[3][0] -
                  m[1][3] * m[2][0] * m[3][2] + m[1][0] * m[2][3] * m[3][2] +
                  m[1][2] * m[2][0] * m[3][3] - m[1][0] * m[2][2] * m[3][3];
        r[1][1] = m[0][2] * m[2][3] * m[3][0] - m[0][3] * m[2][2] * m[3][0] +
                  m[0][3] * m[2][0] * m[3][2] - m[0][0] * m[2][3] * m[3][2] -
                  m[0][2] * m[2][0] * m[3][3] + m[0][0] * m[2][2] * m[3][3];
        r[1][2] = m[0][3] * m[1][2] * m[3][0] - m[0][2] * m[1][3] * m[3][0] -
                  m[0][3] * m[1][0] * m[3][2] + m[0][0] * m[1][3] * m[3][2] +
                  m[0][2] * m[1][0] * m[3][3] - m[0][0] * m[1][2] * m[3][3];
        r[1][3] = m[0][2] * m[1][3] * m[2][0] - m[0][3] * m[1][2] * m[2][0] +
                  m[0][3] * m[1][0] * m[2][2] - m[0][0] * m[1][3] * m[2][2] -
                  m[0][2] * m[1][0] * m[2][3] + m[0][0] * m[1][2] * m[2][3];
        r[2][0] = m[1][1] * m[2][3] * m[3][0] - m[1][3] * m[2][1] * m[3][0] +
                  m[1][3] * m[2][0] * m[3][1] - m[1][0] * m[2][3] * m[3][1] -
                  m[1][1] * m[2][0] * m[3][3] + m[1][0] * m[2][1] * m[3][3];
        r[2][1] = m[0][3] * m[2][1] * m[3][0] - m[0][1] * m[2][3] * m[3][0] -
                  m[0][3] * m[2][0] * m[3][1] + m[0][0] * m[2][3] * m[3][1] +
                  m[0][1] * m[2][0] * m[3][3] - m[0][0] * m[2][1] * m[3][3];
        r[2][2] = m[0][1] * m[1][3] * m[3][0] - m[0][3] * m[1][1] * m[3][0] +
                  m[0][3] * m[1][0] * m[3][1] - m[0][0] * m[1][3] * m[3][1] -
                  m[0][1] * m[1][0] * m[3][3] + m[0][0] * m[1][1] * m[3][3];
        r[2][3] = m[0][3] * m[1][1] * m[2][0] - m[0][1] * m[1][3] * m[2][0] -
                  m[0][3] * m[1][0] * m[2][1] + m[0][0] * m[1][3] * m[2][1] +
                  m[0][1] * m[1][0] * m[2][3] - m[0][0] * m[1][1] * m[2][3];
        r[3][0] = m[1][2] * m[2][1] * m[3][0] - m[1][1] * m[2][2] * m[3][0] -
                  m[1][2] * m[2][0] * m[3][1] + m[1][0] * m[2][2] * m[3][1] +
                  m[1][1] * m[2][0] * m[3][2] - m[1][0] * m[2][1] * m[3][2];
        r[3][1] = m[0][1] * m[2][2] * m[3][0] - m[0][2] * m[2][1] * m[3][0] +
                  m[0][2] * m[2][0] * m[3][1] - m[0][0] * m[2][2] * m[3][1] -
                  m[0][1] * m[2][0] * m[3][2] + m[0][0] * m[2][1] * m[3][2];
        r[3][2] = m[0][2] * m[1][1] * m[3][0] - m[0][1] * m[1][2] * m[3][0] -
                  m[0][2] * m[1][0] * m[3][1] + m[0][0] * m[1][2] * m[3][1] +
                  m[0][1] * m[1][0] * m[3][2] - m[0][0] * m[1][1] * m[3][2];
        r[3][3] = m[0][1] * m[1][2] * m[2][0] - m[0][2] * m[1][1] * m[2][0] +
                  m[0][2] * m[1][0] * m[2][1] - m[0][0] * m[1][2] * m[2][1] -
                  m[0][1] * m[1][0] * m[2][2] + m[0][0] * m[1][1] * m[2][2];
        r /= m.det();
        return r;
    }

    inline Matrix44 Matrix44::translate(Vector3 t) {
        Matrix44 r(1);
        r.cols[3] = Vector4(t, 1);
        return r;
    }

    inline Matrix44 Matrix44::rotate(const Vector3& axis, float phi) {
        Matrix44 r;
        float c = std::cos(Radians(phi));
        float s = std::sin(Radians(phi));
        Vector3 au = axis.unit();
        Vector3 temp = au * (1.0f - c);
        r[0][0] = c + temp[0] * au[0];
        r[0][1] = temp[0] * au[1] + s * au[2];
        r[0][2] = temp[0] * au[2] - s * au[1];
        r[1][0] = temp[1] * au[0] - s * au[2];
        r[1][1] = c + temp[1] * au[1];
        r[1][2] = temp[1] * au[2] + s * au[0];
        r[2][0] = temp[2] * au[0] + s * au[1];
        r[2][1] = temp[2] * au[1] - s * au[0];
        r[2][2] = c + temp[2] * au[2];
        return r;
    }

    inline Matrix44 Matrix44::scale(const Vector3& scale) {
        Matrix44 r;
        r[0][0] = scale.x;
        r[1][1] = scale.y;
        r[2][2] = scale.z;
        return r;
    }

    inline Matrix44 Matrix44::lookat(const Vector3& pos, const Vector3& target, const Vector3& up) {
        Matrix44 r;
        Vector3 F = (target - pos).unit();
        Vector3 S = cross(F, up).unit();
        Vector3 U = cross(S, F).unit();
        r[0][0] = S.x;
        r[0][1] = U.x;
        r[0][2] = -F.x;
        r[1][0] = S.y;
        r[1][1] = U.y;
        r[1][2] = -F.y;
        r[2][0] = S.z;
        r[2][1] = U.z;
        r[2][2] = -F.z;
        r[3][0] = -dot(S, pos);
        r[3][1] = -dot(U, pos);
        r[3][2] = dot(F, pos);
        r[3][3] = 1.0f;
        return r;
    }

    inline Matrix44 Matrix44::ortho(float l, float r, float b, float t, float n, float f) {
        Matrix44 rs;
        rs[0][0] = 2.0f / (r - l);
        rs[1][1] = 2.0f / (t - b);
        rs[2][2] = 2.0f / (n - f);
        rs[3][0] = (-l - r) / (r - l);
        rs[3][1] = (-b - t) / (t - b);
        rs[3][2] = -n / (f - n);
        return rs;
    }

    inline Matrix44 Matrix44::perspective(float fov, float ar, float n) {
        float f = 1.0f / std::tan(Radians(fov) / 2.0f);
        Matrix44 r;
        r[0][0] = f / ar;
        r[1][1] = f;
        r[2][2] = 0.0f;
        r[3][3] = 0.0f;
        r[3][2] = n;
        r[2][3] = -1.0f;
        return r;
    }


}


#endif //H3D_SRC_MATH_MATRIX4X4_H
