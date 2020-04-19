#ifndef MTLREADER_H
#define MTLREADER_H
using namespace std;

#include <mesh/material.h>
#include <mesh/streamReader.h>
#include <mesh/fileReader.h>

class MtlReader : public FileReader<vector<Material*>*>{
    public:
        MtlReader(string filePath) : FileReader(filePath) {
            
        }
        vector<Material*>* read(){
            this -> materials = new vector<Material*>;
            FileReader::processFile();
            return materials;
        }

    private:
        vector<Material*>* materials;
        Material* currentMaterial = NULL;

        StringStreamReader stringReader;
        Vec3StreamReader vec3Reader;
        FloatStreamReader floatReader;

        void handleToken(stringstream* stream){
            string token = stringReader.read(stream);

            if(token == "newmtl"){
                handleNewMtl(stream);
            } else if (token == "Ka") {
                handleAmbient(stream);
            } else if (token == "Kd") {
                handleDiffuse(stream);
            } else if (token == "Ks") {
                handleSpecular(stream);
            } else if (token == "Ns") {
                handleExponent(stream);
            } else if (token == "map_Kd") {
                handleMapKdPath(stream);
            }
        }

        void handleNewMtl(stringstream* stream){
            string name = stringReader.read(stream);
            if(this -> currentMaterial){
                materials -> push_back(this -> currentMaterial);
            }
            this -> currentMaterial = new Material(name);
        }

        void handleAmbient(stringstream* stream){
            glm::vec3 ambient = vec3Reader.read(stream);
            this -> currentMaterial -> setAmbient(ambient);
        }

        void handleDiffuse(stringstream* stream){
            glm::vec3 diffuse = vec3Reader.read(stream);
            currentMaterial -> setDiffuse(diffuse);
        }

        void handleSpecular(stringstream* stream){
            glm::vec3 specular = vec3Reader.read(stream);
            currentMaterial -> setSpecular(specular);
        }

        void handleExponent(stringstream* stream){
            float exponent = floatReader.read(stream);
            currentMaterial -> setExponent(exponent);
        }

        void handleMapKdPath(stringstream* stream){
            string mapKdPath = stringReader.read(stream);
            currentMaterial -> setMapKdPath(mapKdPath);
        }
};
#endif