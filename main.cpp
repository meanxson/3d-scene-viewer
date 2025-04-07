#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "includes/render/shader.h"
#include "includes/math/vec3.h"
#include "includes/math/mat4.h"
#include "includes/mesh/Mesh.h"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "includes/command/Command.h"
#include "includes/command/ExitCommand.h"
#include "includes/render/Window.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const char *WINDOW_TITLE = "3D Scene Viewer";
const float PI = 3.14;

Command *exitCommand;

const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "uniform mat4 MVP;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = MVP * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
                                   "}\n\0";


void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        exitCommand->execute();
    }
}

int main() {
    Window window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

    exitCommand = new ExitCommand(window.getRawWindow());

    vec3 cubePosition1(0.0f, 0.0f, 0.0f);
    vec3 cubePosition2(0.0f, 0.0f, 0.0f);

    std::vector<float> cubeVertices = {
            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, 0.5f, -0.5f,
            -0.5f, 0.5f, -0.5f,

            -0.5f, -0.5f, 0.5f,
            0.5f, -0.5f, 0.5f,
            0.5f, 0.5f, 0.5f,
            -0.5f, 0.5f, 0.5f
    };


    std::vector<unsigned int> cubeIndices = {
            0, 1, 2, 2, 3, 0,
            4, 5, 6, 6, 7, 4,
            4, 0, 3, 3, 7, 4,
            1, 5, 6, 6, 2, 1,
            4, 5, 1, 1, 0, 4,
            3, 2, 6, 6, 7, 3
    };

    Shader shader(vertexShaderSource, fragmentShaderSource);
    Mesh cube(cubeVertices, cubeIndices);

    while (!window.shouldClose()) {
        float time = glfwGetTime();
        processInput(window.getRawWindow());
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mat4 model = mat4().identity()
                .translate(cubePosition1)
                .rotate(time, vec3(0, 1, 0));

        mat4 view = mat4().lookAt(vec3(0, 0, 3), vec3(0, 0, 0), vec3(0, 1, 0));
        mat4 projection = mat4().perspective(PI / 2, window.getAspectRatio(), 0.5f, 1000.0f);
        mat4 MVP = projection * view * model;

        mat4 model2 = mat4().identity()
                .translate(cubePosition2)
                .rotate(time, vec3(0, 1, 0));

        mat4 MVP2 = projection * view * model2;

        shader.use();

        shader.setMat4("MVP", MVP);
        cube.draw();

        shader.setMat4("MVP", MVP2);
        cube.draw();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Debug Control");
        ImGui::SliderFloat3("1 cube Transform", &cubePosition1.x, -5.0f, 5.0f);

        ImGui::SliderFloat3("2 Cube Transform", &cubePosition2.x, -5.0f, 5.0f);
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        window.update();
    }

    delete exitCommand;

    return 0;
}