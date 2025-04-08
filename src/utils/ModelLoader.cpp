#define TINYOBJLOADER_IMPLEMENTATION

#include "../../external/tiny_obj_loader.h"
#include "../../includes/utils/ModelLoader.h"

bool ModelLoader::loadOBJ(const std::string &path, std::vector<float> &vertices, std::vector<unsigned int> &indices) {
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;

    bool success = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path.c_str());

    if (!warn.empty()) std::cout << "[TinyObjLoader] Warning: " << warn << std::endl;
    if (!err.empty()) std::cerr << "[TinyObjLoader] Error: " << err << std::endl;
    if (!success) return false;

    std::unordered_map<int, unsigned int> indexCache;

    for (const auto& shape : shapes) {
        for (const auto& index : shape.mesh.indices) {
            int vertexIndex = index.vertex_index;

            if (indexCache.count(vertexIndex) == 0) {
                float vx = attrib.vertices[3 * vertexIndex + 0];
                float vy = attrib.vertices[3 * vertexIndex + 1];
                float vz = attrib.vertices[3 * vertexIndex + 2];

                vertices.push_back(vx);
                vertices.push_back(vy);
                vertices.push_back(vz);

                indexCache[vertexIndex] = (unsigned int)(vertices.size() / 3 - 1);
            }

            indices.push_back(indexCache[vertexIndex]);
        }
    }

    return true;
}