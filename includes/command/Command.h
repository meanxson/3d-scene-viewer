#ifndef INC_3D_SCENE_VIEWER_COMMAND_H
#define INC_3D_SCENE_VIEWER_COMMAND_H

class Command {
public:
    virtual ~Command() {};

    virtual void execute() = 0;
};

#endif //INC_3D_SCENE_VIEWER_COMMAND_H
