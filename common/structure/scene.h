//
// Created by Correa, Rafael on 19/05/20.
//

#ifndef CG_TRACK_SCENE_H
#define CG_TRACK_SCENE_H
using namespace std;

#include <structure/mesh.h>

class Scene {
public:
    Scene(){
        shader = nullptr;
        objects = nullptr;
        camera = nullptr;
    };
    Shader* shader;
    vector<Mesh*>* objects;
    Camera* camera;
    GLFWwindow* window;
    glm::vec2* screenSize;
};


#endif //CG_TRACK_SCENE_H
