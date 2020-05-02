#ifndef STREAMREADER_H
#define STREAMREADER_H
using namespace std;

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <structure/face.h>


template <typename T>
class StreamReader{
    public:
        T read(stringstream* stream);
};

class FloatStreamReader : public StreamReader<string>{
    public:
        float read(stringstream* stream){
            float number;
            *stream >> number;
            return number;
        }
};

class StringStreamReader : public StreamReader<string>{
    public:
        string read(stringstream* stream){
            string string;
            *stream >> string;
            return string;
        }
};

class Vec3StreamReader : public StreamReader<glm::vec3>{
    public:
        glm::vec3 read(stringstream* stream){
             glm::vec3 vec;
            *stream >> vec.x >> vec.y >> vec.z;
            return vec;
        }
};
        
class Vec2StreamReader : public StreamReader<glm::vec2>{
    public:
        glm::vec2 read(stringstream* stream){
             glm::vec2 vec;
            *stream >> vec.x >> vec.y;
            return vec;
        }
};

class FaceStreamReader : public StreamReader<Face*>{
    public:
        Face* read(stringstream* stream){
            string column;
            Face* face = new Face();
            while (hasInformationToRead(stream)){
                *stream >> column;
                stringstream columnStream;
                columnStream << column;
                string aux;
                getline(columnStream, aux, '/');
                int vertexIndex = stoi(aux);
                face -> insertVertex(vertexIndex);
                aux = "";
                getline(columnStream, aux, '/');
                if (!aux.empty()){
                    int textureIndex = stoi(aux);
                    face -> insertTexture(textureIndex);
                }

                if (hasInformationToRead(&columnStream)) {
                    getline(columnStream, aux, '/');
                    int normalIndex = stoi(aux);
                    face -> insertNormal(normalIndex);
                }
            }
            return face;
        }
    private:
        int hasInformationToRead(stringstream* line){
            return line->rdbuf()->in_avail();
        }
};
#endif