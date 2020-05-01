#ifndef MATERIAL_H
#define MATERIAL_H
using namespace std;

#include <external/glm/glm/glm.hpp>

class Material {
    public:
        Material(string name){
            this -> name = name;
            hasTexture = false;
        }
        Material() {}

        int hasName(){
            return !name.empty();
        }
        void setName(string name){
            this -> name = name;
        }

        std::string GetName() { 
            return this->name; 
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
            this -> hasTexture = true;
        }
        void setId(int textureId){
            this -> textureId = textureId;
        }
        string getName(){
            return this -> name;
        }
        int getId(){
            return this -> textureId;
        }
        bool GetHasTexture() {
		    if (this->hasTexture)
			    return true;
		    else
			    return false;
	    }

    private:
        string name;
        glm::vec3 ambient;  //Ka
        glm::vec3 diffuse;  //Kd
        glm::vec3 specular; //Ks
        float exponent;     //Ns
        string mapKdPath;   //map_Kd
        int textureId;      //tid
        bool hasTexture;


};
#endif