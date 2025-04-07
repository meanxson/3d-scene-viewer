#ifndef INC_3D_SCENE_VIEWER_EXITCOMMAND_H
#define INC_3D_SCENE_VIEWER_EXITCOMMAND_H

#include "Command.h"
#include <GLFW/glfw3.h>

class ExitCommand : public Command {
private:
    GLFWwindow *m_window;

public:
    ExitCommand(GLFWwindow *window);
    virtual void execute();
};

#endif //INC_3D_SCENE_VIEWER_EXITCOMMAND_H
