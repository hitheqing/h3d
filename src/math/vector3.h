
#pragma once


#include <cmath>
#include <ostream>
#include "vector2.h"
#include <climits>

namespace Hyhy {
    class Vector3 {
    public:

        union {
            struct {
                float x, y, z;
            };
            float data[3] = {};
        };


        //ctor
        Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
        explicit Vector3(float v = 0) : x(v), y(v), z(v) {}
        Vector3(const Vector2& v, float z) : x(v.x), y(v.y), z(z) {}
        Vector3(const Vector3& v) = default;


        //indexer
        float& operator[](int i) { return data[i]; }
        const float& operator[](int i) const { return data[i]; }

        //operator
        Vector3& operator+=(const Vector3& v) {
            x += v.x;
            y += v.y;
            z += v.z;
            return *this;
        }
        Vector3& operator-=(const Vector3& v) {
            x -= v.x;
            y -= v.y;
            z -= v.z;
            return *this;
        }
        Vector3& operator*=(const Vector3& v) {
            x *= v.x;
            y *= v.y;
            z *= v.z;
            return *this;
        }
        Vector3& operator/=(const Vector3& v) {
            x /= v.x;
            y /= v.y;
            z /= v.z;
            return *this;
        }

        Vector3 operator+(const Vector3& v) const { return Vector3(x + v.x, y + v.y, z + v.z); }
        Vector3 operator-(const Vector3& v) const { return Vector3(x - v.x, y - v.y, z - v.z); }
        Vector3 operator*(const Vector3& v) const { return Vector3(x * v.x, y * v.y, z * v.z); }
        Vector3 operator/(const Vector3& v) const { return Vector3(x / v.x, y / v.y, z / v.z); }

        Vector3& operator+=(float v) {
            x += v;
            y += v;
            z += v;
            return *this;
        }
        Vector3& operator-=(float v) {
            x -= v;
            y -= v;
            z -= v;
            return *this;
        }
        Vector3& operator*=(float v) {
            x *= v;
            y *= v;
            z *= v;
            return *this;
        }
        Vector3& operator/=(float v) {
            x /= v;
            y /= v;
            z /= v;
            return *this;
        }

        Vector3 operator-() const { return Vector3(-x, -y, -z); }

        //equals
        bool operator==(const Vector3& v) const { return x == v.x && y == v.y && z == v.z; }
        bool operator!=(const Vector3& v) const { return x != v.x || y != v.y || z != v.z; }


        //norm
        float norm_squared() const { return (x * x + y * y + z * z); }
        float norm() const { return sqrt(this->norm_squared()); }
        void normalize() {
            float inv = 1.0f / norm();
            *this *= inv;
        }
        Vector3 unit() const {
            Vector3 v(*this);
            v.normalize();
            return v;
        }

        // real number
        bool valid() const {
            return !(std::isnan(x) || std::isnan(y) || std::isnan(z)
                     || std::isinf(x) || std::isinf(y) || std::isinf(z));
        }

        Vector3 abs() const { return Vector3(std::abs(x), std::abs(y), std::abs(z)); }
        Vector2 xy() const { return Vector2(x, y); }
        Vector2 yz() const { return Vector2(y, z); }
        Vector2 zx() const { return Vector2(z, x); }

        // perspective division
        Vector2 project() const { return Vector2(x / z, y / z); }
    };

    // operator
    inline Vector3 operator*(const Vector3& v, float s) { return Vector3(v.x * s, v.y * s, v.z * s); }
    inline Vector3 operator*(float s, const Vector3& v) { return Vector3(v.x * s, v.y * s, v.z * s); }
    inline Vector3 operator/(const Vector3& v, float s) {
        Vector3 temp(v);
        temp /= s;
        return temp;
    }

    //dot
    inline float dot(const Vector3& l, const Vector3& r) { return l.x * r.x + l.y * r.y + l.z * r.z; }

    //cross
    inline Vector3 cross(const Vector3& l, const Vector3& r) {
        return Vector3(l.y * r.z - l.z * r.y, l.z * r.x - l.x * r.z, l.x * r.y - l.y * r.x);
    }

    //lerp
    inline Vector3 lerp(const Vector3& from, const Vector3& to, float t) {
        { return to * t + from * (1.0f - t); }
    }

    inline std::ostream& operator<<(std::ostream& os, const Vector3& v) {
        os << "{" << v.x << "," << v.y << "," << v.z << "}";
        return os;
    }
}

