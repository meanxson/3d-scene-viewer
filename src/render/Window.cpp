#include "../../includes/render/Window.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

Window::Window(int width, int height, const char *title) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);

    if (m_window == nullptr) {
        std::cout << "[Window] Can't create m_window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(m_window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << " [GLAD] Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return;
    }

    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

    glEnable(GL_DEPTH_TEST);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

Window::~Window() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void Window::update() {
    glfwSwapBuffers(m_window);
    glfwPollEvents();
}

bool Window::shouldClose() const {
    return glfwWindowShouldClose(m_window);
}

float Window::getAspectRatio() const {
    int width, height;
    glfwGetFramebufferSize(m_window, &width, &height);
    return (float) width / (float) height;
}

GLFWwindow *Window::getRawWindow() {
    return m_window;
}


