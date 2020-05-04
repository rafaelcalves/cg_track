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


    glm::vec3 getCenter(){
        return *position;
    }

};

#endif