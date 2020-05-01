#ifndef OBJ3D
#define OBJ3D
using namespace std;

#include "camera.h"

class Obj3D {
public:
    Mesh* mesh;

    float scale;
    glm::vec3* position = new glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3* direction;

    bool invisible = false;
    bool canBeDestroyed = true;
    bool staticObj = false;

    void draw(Camera *camera, Shader *shader){

        if (invisible){
            return;
        }

        glm::mat4 projection = camera->getProjectionMatrix();
        glm::mat4 view = camera->getViewMatrix();
        shader->setMat4("projection", projection);
        shader->setMat4("view", view);
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, *position);
        model = glm::scale(model, glm::vec3(scale, scale, scale));
        shader->setMat4("model", model);

        //Talvez adicionar o draw arrays aqui
    }

    glm::vec3 getCenter(){
        return *position;
    }

};

#endif