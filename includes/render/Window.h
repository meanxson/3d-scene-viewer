#ifndef INC_3D_SCENE_VIEWER_WINDOW_H
#define INC_3D_SCENE_VIEWER_WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

class Window {
private:
    GLFWwindow *m_window;

public:
    Window(int width, int height, const char *title);

    ~Window();

    void update();

    bool shouldClose() const;

    float getAspectRatio() const;

    GLFWwindow *getRawWindow();
};

#endif //INC_3D_SCENE_VIEWER_WINDOW_H
