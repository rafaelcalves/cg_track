#ifndef CG_TRACK_SCENE_H
#define CG_TRACK_SCENE_H
using namespace std;

#include <structure/mesh.h>

class Scene {
public:
    Scene(){
        initAttributes();
    };
    void initShader(string vertexPath, string fragmentPath){
        shader = new Shader(vertexPath.c_str(), fragmentPath.c_str());
        shader -> use();
    }

    Shader* shader;
    vector<Mesh*>* objects;
    Camera* camera;
    GLFWwindow* window;
    glm::vec2* screenSize;
private:
    void initAttributes(){
        shader = nullptr;
        objects = new vector<Mesh*>();
        camera = nullptr;
    }
};


#endif //CG_TRACK_SCENE_H
