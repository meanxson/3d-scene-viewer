#ifndef INC_3D_SCENE_VIEWER_VEC3_H
#define INC_3D_SCENE_VIEWER_VEC3_H

#include <cmath>

struct vec3 {
    float x, y, z;

    vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {

    }

    vec3 operator+(const vec3 &other) const {
        return {x + other.x, y + other.y, z + other.z};
    }

    vec3 operator-(const vec3 &other) const {
        return {x - other.x, y - other.y, z - other.z};
    }

    vec3 operator*(const float scalar) const {
        return {x * scalar, y * scalar, z * scalar};
    }

    float length() const {
        return sqrtf(x * x + y * y + z * z);
    }

    vec3 normalize() const {
        return {x / length(), y / length(), z / length()};
    }

    float dot(const vec3 &other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    vec3 cross(const vec3 &other) const {
        return {y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x};
    }
};

#endif //INC_3D_SCENE_VIEWER_VEC3_H
