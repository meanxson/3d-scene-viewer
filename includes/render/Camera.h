#ifndef INC_3D_SCENE_VIEWER_CAMERA_H
#define INC_3D_SCENE_VIEWER_CAMERA_H

#include "../math/vec3.h"
#include "../math/mat4.h"

class Camera {
public:
    mat4 getViewMatrix() const;

    void processMouseMovement(float dx, float dy);

    void processScroll(float yOffset);

private:
    float m_radius;
    float m_theta;
    float m_phi;
    vec3 m_target;
    vec3 m_up;
};


#endif //INC_3D_SCENE_VIEWER_CAMERA_H
