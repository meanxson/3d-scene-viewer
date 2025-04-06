#include "../../includes/shader/shader.h"

Shader::Shader(const char *vertexSrc, const char *fragmentSrc) {
    int success;
    char infoLog[512];

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSrc, nullptr);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSrc, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    m_id = glCreateProgram();
    glAttachShader(m_id, vertexShader);
    glAttachShader(m_id, fragmentShader);
    glLinkProgram(m_id);
    glGetProgramiv(m_id, GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(m_id, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader() {
    glDeleteProgram(m_id);
}

void Shader::use() {
    glUseProgram(m_id);
}

void Shader::setBool(const char *name, bool value) const {
    GLint location = getUniformLocation(name);
    glUniform1i(location, value);
}

void Shader::setInt(const char *name, int value) const {
    GLint location = getUniformLocation(name);
    glUniform1i(location, value);
}

void Shader::setFloat(const char *name, float value) const {
    GLint location = getUniformLocation(name);
    glUniform1f(location, value);
}

void Shader::setMat4(const char *name, const mat4 &value) const {
    GLint location = getUniformLocation(name);
    glUniformMatrix4fv(location, 1, GL_FALSE, value.data);

}

GLint Shader::getUniformLocation(const std::string &name) const {
    if (m_uniformCache.find(name) != m_uniformCache.end())
        return m_uniformCache[name];

    GLint location = glGetUniformLocation(m_id, name.c_str());
    m_uniformCache[name] = location;
    return location;
}
