#ifndef INC_3D_SCENE_VIEWER_SHADER_H
#define INC_3D_SCENE_VIEWER_SHADER_H

#include <glad/glad.h>
#include <iostream>
#include <unordered_map>
#include <string>
#include "../math/mat4.h"

class Shader {
private:
    GLuint m_id;
    mutable std::unordered_map<std::string, GLint> m_uniformCache;

    GLint getUniformLocation(const std::string &name) const;

public:
    Shader(const char *vertexSrc, const char *fragmentSrc);

    ~Shader();

    void use();

    void setBool(const char *name, bool value) const;

    void setInt(const char *name, int value) const;

    void setFloat(const char *name, float value) const;

    void setMat4(const char *name, const mat4 &value) const;

};

#endif //INC_3D_SCENE_VIEWER_SHADER_H
