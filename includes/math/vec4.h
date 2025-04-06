#ifndef INC_3D_SCENE_VIEWER_VEC4_H
#define INC_3D_SCENE_VIEWER_VEC4_H

#include "vec3.h"
#include "mat4.h"

struct vec4 {
    float x, y, z, w;

    vec4() {

    }

    vec4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {

    }

    vec4(const vec3 &_v, float _w) : x(_v.x), y(_v.y), z(_v.z), w(_w) {

    }

};


vec4 operator*(const mat4 &m, const vec4 &v) {
    vec4 res;

    res.x = m.data[0] * v.x + m.data[4] * v.y + m.data[8] * v.z + m.data[12] * v.w;
    res.y = m.data[1] * v.x + m.data[5] * v.y + m.data[9] * v.z + m.data[13] * v.w;
    res.z = m.data[2] * v.x + m.data[6] * v.y + m.data[10] * v.z + m.data[14] * v.w;
    res.w = m.data[3] * v.x + m.data[7] * v.y + m.data[11] * v.z + m.data[15] * v.w;

    return res;
}

#endif //INC_3D_SCENE_VIEWER_VEC4_H
