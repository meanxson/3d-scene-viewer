#ifndef INC_3D_SCENE_VIEWER_MAT4_H
#define INC_3D_SCENE_VIEWER_MAT4_H

#include "vec3.h"

struct mat4 {
    float data[16];

    mat4() {
        for (float &i: data) i = 0.0f;
    }

    mat4 &identity() {
        for (float &i: data) i = 0.0f;

        for (int i = 0; i < 16; ++i) {
            if (i % 5 == 0) {
                data[i] = 1;
            }
        }

        return *this;
    }

    mat4 &translate(const vec3 &offset) {
        mat4 translationMatrix;
        translationMatrix.identity();
        translationMatrix.data[12] = offset.x;
        translationMatrix.data[13] = offset.y;
        translationMatrix.data[14] = offset.z;
        *this = *this * translationMatrix;
        return *this;
    }

    mat4 &scale(const vec3 &scale) {
        mat4 scaleMatrix;
        scaleMatrix.identity();
        scaleMatrix.data[0] = scale.x;
        scaleMatrix.data[5] = scale.y;
        scaleMatrix.data[10] = scale.z;
        *this = *this * scaleMatrix;
        return *this;
    }

    mat4 &rotate(float angleRadians, const vec3 &axis) {
        mat4 rotationMatrix;
        vec3 n = axis.normalize();

        float x = n.x, y = n.y, z = n.z;

        float c = cosf(angleRadians);

        float s = sinf(angleRadians);

        float t = 1.0f - c;

        rotationMatrix.data[0] = t * x * x + c;
        rotationMatrix.data[1] = t * x * y - z * s;
        rotationMatrix.data[2] = t * x * z + y * s;

        rotationMatrix.data[4] = t * x * y + z * s;
        rotationMatrix.data[5] = t * y * y + c;
        rotationMatrix.data[6] = t * y * z + x * s;

        rotationMatrix.data[8] = t * x * z - y * s;
        rotationMatrix.data[9] = t * y * z + x * s;
        rotationMatrix.data[10] = t * z * z + c;
        rotationMatrix.data[15] = 1.0f;


        *this = *this * rotationMatrix;
        return *this;
    }

    mat4 &lookAt(const vec3 &eye, const vec3 &target, const vec3 &up) {
        mat4 view;

        vec3 forward = (eye - target).normalize();
        vec3 right = up.cross(forward).normalize();
        vec3 camUp = forward.cross(right);

        view.data[0] = right.x;
        view.data[1] = camUp.x;
        view.data[2] = forward.x;
        view.data[3] = 0.0f;

        view.data[4] = right.y;
        view.data[5] = camUp.y;
        view.data[6] = forward.y;
        view.data[7] = 0.0f;

        view.data[8] = right.z;
        view.data[9] = camUp.z;
        view.data[10] = forward.z;
        view.data[11] = 0.0f;

        view.data[12] = -right.dot(eye);
        view.data[13] = -camUp.dot(eye);
        view.data[14] = -forward.dot(eye);
        view.data[15] = 1.0f;

        *this = view;
        return *this;
    }

    mat4 &perspective(float fovRadians, float aspect, float near, float far) {
        mat4 matFov;
        float f = 1 / tanf(fovRadians / 2);

        matFov.data[0] = f / aspect;
        matFov.data[5] = f;
        matFov.data[10] = (far + near) / (near - far);
        matFov.data[11] = (2 * far * near) / (near - far);
        matFov.data[14] = -1.0f;

        *this = matFov;
        return *this;
    }


    mat4 operator*(const mat4 &other) const {
        mat4 result;
        for (int row = 0; row < 4; ++row) {
            for (int col = 0; col < 4; ++col) {
                result.data[row + col * 4] =
                        this->data[row + 0 * 4] * other.data[0 + col * 4] +
                        this->data[row + 1 * 4] * other.data[1 + col * 4] +
                        this->data[row + 2 * 4] * other.data[2 + col * 4] +
                        this->data[row + 3 * 4] * other.data[3 + col * 4];
            }
        }

        return result;
    }
};

#endif //INC_3D_SCENE_VIEWER_MAT4_H
