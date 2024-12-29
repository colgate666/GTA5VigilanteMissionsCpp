#pragma once

#include <corecrt_math_defines.h>
#include <cmath>
#include <random>
#include "inc/types.h"

namespace VECTORS {
    static float Length(const Vector3& v) {
        return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    }

    static void Normalize(Vector3& v) {
        if (const float length = Length(v); length > 0) {
            const float invLength = 1.0f / length;
            v.x *= invLength;
            v.y *= invLength;
            v.z *= invLength;
        }
    }

    static Vector3 RandomXY() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_real_distribution<float> dis(0, 2.0f * M_PI);

        const float radian = dis(gen);
        Vector3 v = {0, 0, 0};
        v.x = std::cos(radian);
        v.y = std::sin(radian);
        v.z = 0.0f;
        Normalize(v);
        return v;
    }

    static Vector3 Add(const Vector3& a, const Vector3& b) {
        Vector3 result = {0, 0, 0};
        result.x = a.x + b.x;
        result.y = a.y + b.y;
        result.z = a.z + b.z;
        return result;
    }

    static Vector3 Multiply(const Vector3& v, const float scalar) {
        Vector3 result = {0, 0 , 0};
        result.x = v.x * scalar;
        result.y = v.y * scalar;
        result.z = v.z * scalar;
        return result;
    }

    static Vector3 Around(const Vector3& pos, const float distance) {
        return Add(pos, Multiply(RandomXY(), distance));
    }
}