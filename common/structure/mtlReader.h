#ifndef MTLREADER_H
#define MTLREADER_H
using namespace std;

#include <stb/stb_image.h>
#include <structure/material.h>
#include <structure/streamReader.h>
#include <structure/fileReader.h>

class MtlReader : public FileReader<vector<Material*>*>{
    public:
        MtlReader(string filePath) : FileReader(filePath) {
            
        }
        vector<Material*>* read(){
            this -> materials = new vector<Material*>;
            this -> currentMaterial = nullptr;
            FileReader::processFile();

            this -> materials -> push_back(this -> currentMaterial);
            return materials;
        }

    private:
        vector<Material*>* materials;
        Material* currentMaterial;

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
            this -> currentMaterial -> ambient = ambient;
        }

        void handleDiffuse(stringstream* stream){
            glm::vec3 diffuse = vec3Reader.read(stream);
            currentMaterial -> diffuse = diffuse;
        }

        void handleSpecular(stringstream* stream){
            glm::vec3 specular = vec3Reader.read(stream);
            currentMaterial -> specular = specular;
        }

        void handleExponent(stringstream* stream){
            float exponent = floatReader.read(stream);
            currentMaterial -> exponent = exponent;
        }

        void handleMapKdPath(stringstream* stream){
            string mapKdPath = stringReader.read(stream);
            currentMaterial -> mapKdPath = mapKdPath;
            int textureId = loadTexturesFromFile(mapKdPath);
            currentMaterial -> textureId = textureId;
        }

        unsigned int loadTexturesFromFile(string &fileName) {
            string fileDirectory = getFileDirectory();
            string fullPath = fileDirectory + '/' + fileName;

            unsigned int textureID;
            glGenTextures(1, &textureID);

            int width, height, nrComponents;
            unsigned char *data = stbi_load(fullPath.c_str(), &width, &height, &nrComponents, 0);

            if (data) {
                glBindTexture(GL_TEXTURE_2D, textureID);

                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

                if (getFileExtension(fileName) == ".png"){
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
                }else{
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                }
                glGenerateMipmap(GL_TEXTURE_2D);

                stbi_image_free(data);
            }
            else {
                std::cout << "Texture failed to load at path: " << fileName << std::endl;
                stbi_image_free(data);
            }

            return textureID;
        }
};
#endif