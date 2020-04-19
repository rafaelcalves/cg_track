#ifndef MATERIAL_H
#define MATERIAL_H
using namespace std;

#include <glm/glm.hpp>
class Material {
    public:
        Material(string name){
            this -> name = name;
        }
        int hasName(){
            return !name.empty();
        }
        void setName(string name){
            this -> name = name;
        }
        void setAmbient(glm::vec3 ambient){
            this -> ambient = ambient;
        }
        void setDiffuse(glm::vec3 diffuse){
            this -> diffuse = diffuse;
        }
        void setSpecular(glm::vec3 specular){
            this -> specular = specular;
        }
        void setExponent(float exponent){
            this -> exponent =exponent;
        }
        void setMapKdPath(string mapKdPath){
            this -> mapKdPath = mapKdPath;
        }
        void setId(int textureId){
            this -> textureId = textureId;
        }
        string getName(){
            return this -> name;
        }
    private:
        string name;
        glm::vec3 ambient;  //Ka
        glm::vec3 diffuse;  //Kd
        glm::vec3 specular; //Ks
        float exponent;     //Ns
        string mapKdPath;      //map_Kd
        int textureId;      //tid


};
#endif