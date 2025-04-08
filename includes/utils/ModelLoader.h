#ifndef INC_3D_SCENE_VIEWER_MODELLOADER_H
#define INC_3D_SCENE_VIEWER_MODELLOADER_H

#include <iostream>
#include <vector>
#include <unordered_map>

class ModelLoader {
public:
    static bool loadOBJ(
            const std::string &path,
            std::vector<float> &vertices,
            std::vector<unsigned int> &indices
    );
};

#endif //INC_3D_SCENE_VIEWER_MODELLOADER_H
