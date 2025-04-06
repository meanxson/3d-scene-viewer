#ifndef INC_3D_SCENE_VIEWER_MESH_H
#define INC_3D_SCENE_VIEWER_MESH_H

#include <glad/glad.h>
#include <vector>

class Mesh {
private:
    unsigned int VAO, VBO, EBO;
    std::vector<float> m_vertices;
    std::vector<unsigned int> m_indices;

public:
    Mesh(const std::vector<float> &vertices, const std::vector<unsigned int> &indices);

    ~Mesh();

    void draw() const;
};

#endif //INC_3D_SCENE_VIEWER_MESH_H
