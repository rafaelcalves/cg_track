#ifndef MATERIAL_H
#define MATERIAL_H
using namespace std;

#include <external/glm/glm/glm.hpp>

class Material {
    public:
        string name;
        glm::vec3 ambient;              //Ka
        glm::vec3 diffuse;              //Kd
        glm::vec3 specular;             //Ks
        float exponent;                 //Ns
        string mapKdPath;               //map_Kd
        int textureId;                  //tid
        int illumination;               //illum
        glm::vec3 transmissionFilter;   //Tf
        float opticalDensity;           //Ni

        Material(string name){
            this -> name = name;
        }
        Material() {}

        bool hasTexture() {
            if (mapKdPath.empty()){
                return false;
            }
            return true;
	    }
};
#endif