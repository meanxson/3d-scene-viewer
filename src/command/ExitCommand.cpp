#include "../../includes/command/ExitCommand.h"

ExitCommand::ExitCommand(GLFWwindow *window) : m_window(window) {

}

void ExitCommand::execute() {
    glfwSetWindowShouldClose(m_window, true);
}
