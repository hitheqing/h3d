#pragma once

#include <cmath>
#include <ostream>
#include "vector3.h"

namespace Hyhy {
    class Vector4 {
    public:

        union {
            struct {
                float x, y, z, w;
            };
            float data[4] = {};
        };


        //ctor
        Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

        // 当ctor参数只有1个，或者后面的都是默认参数时。explicit 关键字禁止ctor隐式自动转换
        explicit Vector4(float v = 0) : x(v), y(v), z(v), w(v) {}

        Vector4(const Vector3& v, float w) : x(v.x), y(v.y), z(v.z), w(w) {}
        Vector4(const Vector4& v) = default;

        //indexer
        float& operator[](int i) { return data[i]; }
        const float& operator[](int i) const { return data[i]; }


        //operator
        Vector4& operator+=(const Vector4& v) {
            x += v.x;
            y += v.y;
            z += v.z;
            w += v.w;
            return *this;
        }

        Vector4& operator-=(const Vector4& v) {
            x -= v.x;
            y -= v.y;
            z -= v.z;
            w -= v.w;
            return *this;
        }

        Vector4& operator*=(const Vector4& v) {
            x *= v.x;
            y *= v.y;
            z *= v.z;
            w *= v.w;
            return *this;
        }

        Vector4& operator/=(const Vector4& v) {
            x /= v.x;
            y /= v.y;
            z /= v.z;
            w /= v.w;
            return *this;
        }

        Vector4 operator+(const Vector4& v) const { return Vector4(x + v.x, y + v.y, z + v.z, w + v.w); }
        Vector4 operator-(const Vector4& v) const { return Vector4(x - v.x, y - v.y, z - v.z, w - v.w); }
        Vector4 operator*(const Vector4& v) const { return Vector4(x * v.x, y * v.y, z * v.z, w * v.w); }
        Vector4 operator/(const Vector4& v) const { return Vector4(x / v.x, y / v.y, z / v.z, w / v.w); }

        Vector4 operator+(float v) const { return Vector4(x + v, y + v, z + v, w + v); }
        Vector4 operator-(float v) const { return Vector4(x - v, y - v, z - v, w - v); }
        Vector4 operator*(float v) const { return Vector4(x * v, y * v, z * v, w * v); }
        Vector4 operator/(float v) const { return Vector4(x / v, y / v, z / v, w / v); }

        Vector4& operator+=(float v) {
            x += v;
            y += v;
            z += v;
            w += v;
            return *this;
        }

        Vector4& operator-=(float v) {
            x -= v;
            y -= v;
            z -= v;
            w -= v;
            return *this;
        }

        Vector4& operator*=(float v) {
            x *= v;
            y *= v;
            z *= v;
            w *= v;
            return *this;
        }

        Vector4& operator/=(float v) {
            x /= v;
            y /= v;
            z /= v;
            w /= v;
            return *this;
        }

        Vector4 operator-() const { return Vector4(-x, -y, -z, -w); }

        //equals
        bool operator==(const Vector4& v) const { return x == v.x && y == v.y && z == v.z && w == v.w; }

        bool operator!=(const Vector4& v) const { return x != v.x || y != v.y || z != v.z || w != v.w; }


        //norm
        float norm_squared() const { return (x * x + y * y + z * z + w * w); }

        float norm() const { return sqrt(this->norm_squared()); }

        void normalize() {
            float inv = 1.0f / norm();
            *this *= inv;
        }

        Vector4 unit() const {
            Vector4 v(*this);
            v.normalize();
            return v;
        }

        // real number
        bool valid() const {
            return !(std::isnan(x) || std::isnan(y) || std::isnan(z) || std::isnan(w)
                     || std::isinf(x) || std::isinf(y) || std::isinf(z) || std::isinf(w));
        }

        Vector4 abs() const { return Vector4(std::abs(x), std::abs(y), std::abs(z), std::abs(w)); }

        // perspective division
        Vector3 project() const { return Vector3(x / w, y / w, z / w); }

        Vector3 xyz() const { return Vector3(x, y, z); }
    };

    inline Vector4 operator*(float s, const Vector4& v) { return Vector4(v.x * s, v.y * s, v.z * s, v.w * s); }

    //dot
    inline float dot(const Vector4& l, const Vector4& r) { return l.x * r.x + l.y * r.y + l.z * r.z + l.w * r.w; }

    //lerp
    inline Vector4 lerp(const Vector4& from, const Vector4& to, float t) {
        { return to * t + from * (1.0f - t); }
    }

    inline std::ostream& operator<<(std::ostream& os, const Vector4& v) {
        os << "{" << v.x << "," << v.y << "," << v.z << "," << v.w << "}";
        return os;
    }
}



