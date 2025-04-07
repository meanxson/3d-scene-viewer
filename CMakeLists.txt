cmake_minimum_required(VERSION 3.25)
project(3d_scene_viewer)

set(CMAKE_CXX_STANDARD 17)

add_executable(3d_scene_viewer main.cpp includes/render/shader.h src/render/shader.cpp includes/math/vec3.h includes/math/mat4.h includes/math/vec4.h src/mesh/Mesh.cpp includes/mesh/Mesh.h)

add_subdirectory(external/glfw ${CMAKE_CURRENT_BINARY_DIR}/glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

add_subdirectory(external/glad ${CMAKE_CURRENT_BINARY_DIR}/glad)
target_link_libraries(${PROJECT_NAME} PRIVATE glad)

set(IMGUI_INCLUDES
        ./external/ImGui/imgui.h
        ./external/ImGui/backends/imgui_impl_glfw.h
        ./external/ImGui/backends/imgui_impl_opengl3.h)

set(IMGUI_SOURCES
        ./external/ImGui/imgui.cpp
        ./external/ImGui/backends/imgui_impl_glfw.cpp
        ./external/ImGui/backends/imgui_impl_opengl3.cpp
        ./external/ImGui/imgui_draw.cpp
        ./external/ImGui/imgui_tables.cpp
        ./external/ImGui/imgui_widgets.cpp
        ./external/ImGui/imgui_demo.cpp includes/render/Window.h src/render/Window.cpp src/command/ExitCommand.cpp includes/command/Command.h includes/command/ExitCommand.h)

add_library(ImGui STATIC
        ${IMGUI_INCLUDES}
        ${IMGUI_SOURCES})

target_include_directories(ImGui PUBLIC ./external)
target_include_directories(ImGui PUBLIC ./external/ImGui)
target_link_libraries(ImGui PRIVATE glad glfw)

target_link_libraries(${PROJECT_NAME} PRIVATE ImGui)