cmake_minimum_required(VERSION 3.25)
project(3d_scene_viewer)

set(CMAKE_CXX_STANDARD 17)

add_executable(3d_scene_viewer main.cpp)

add_subdirectory(external/glfw ${CMAKE_CURRENT_BINARY_DIR}/glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

add_subdirectory(external/glad ${CMAKE_CURRENT_BINARY_DIR}/glad)
target_link_libraries(${PROJECT_NAME} PRIVATE glad)