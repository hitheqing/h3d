#pragma once

#include <cmath>
#include <ostream>

namespace Hyhy {
    class Vector2 {
    public:

        union {
            struct {
                float x, y;
            };
            float data[2] = {};
        };


        //ctor
        Vector2(float x, float y) : x(x), y(y) {}
        explicit Vector2(float v = 0) : x(v), y(v) {}
        Vector2(const Vector2& v) = default;

        //indexer
        float& operator[](int i) { return data[i]; }
        const float& operator[](int i) const { return data[i]; }

        //operator
        Vector2& operator+=(const Vector2& v) {
            x += v.x;
            y += v.y;
            return *this;
        }
        Vector2& operator-=(const Vector2& v) {
            x -= v.x;
            y -= v.y;
            return *this;
        }
        Vector2& operator*=(const Vector2& v) {
            x *= v.x;
            y *= v.y;
            return *this;
        }
        Vector2& operator/=(const Vector2& v) {
            x /= v.x;
            y /= v.y;
            return *this;
        }

        Vector2 operator+(const Vector2& v) const { return Vector2(x + v.x, y + v.y); }
        Vector2 operator-(const Vector2& v) const { return Vector2(x - v.x, y - v.y); }
        Vector2 operator*(const Vector2& v) const { return Vector2(x * v.x, y * v.y); }
        Vector2 operator/(const Vector2& v) const { return Vector2(x / v.x, y / v.y); }

        Vector2& operator+=(float v) {
            x += v;
            y += v;
            return *this;
        }
        Vector2& operator-=(float v) {
            x -= v;
            y -= v;
            return *this;
        }
        Vector2& operator*=(float v) {
            x *= v;
            y *= v;
            return *this;
        }
        Vector2& operator/=(float v) {
            x /= v;
            y /= v;
            return *this;
        }

        Vector2 operator-() const { return Vector2(-x, -y); }

        bool operator==(const Vector2& v) const { return x == v.x && y == v.y; }
        bool operator!=(const Vector2& v) const { return x != v.x || y != v.y; }

        float norm_squared() const { return (x * x + y * y); }
        float norm() const { return sqrt(this->norm_squared()); }
        void normalize() {
            float inv = 1.0f / norm();
            *this *= inv;
        }
        Vector2 unit() const {
            Vector2 v(*this);
            v.normalize();
            return v;
        }

        // real number
        bool valid() const {
            return !(std::isnan(x) || std::isnan(y) || std::isinf(x) || std::isinf(y));
        }

        Vector2 abs() const { return Vector2(std::abs(x), std::abs(y)); }
    };

    // operator
    inline Vector2 operator*(const Vector2& v, float s) { return Vector2(v.x * s, v.y * s); }
    inline Vector2 operator*(float s, const Vector2& v) { return Vector2(v.x * s, v.y * s); }
    inline Vector2 operator/(const Vector2& v, float s) {
        Vector2 temp(v);
        temp /= s;
        return temp;
    }

    //dot
    inline float dot(const Vector2& l, const Vector2& r) { return l.x * r.x + l.y * r.y; }

    //cross
    inline float cross(const Vector2& l, const Vector2& r) { return (l.x * r.y - l.y * r.x); }

    //lerp
    inline Vector2 lerp(const Vector2& from, const Vector2& to, float t) {
        return to * t + from * (1.0f - t);
    }

    inline std::ostream& operator<<(std::ostream& os, const Vector2& v) {
        os << "{" << v.x << "," << v.y << "}";
        return os;
    }


}
