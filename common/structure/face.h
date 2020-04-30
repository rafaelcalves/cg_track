#ifndef FACE_H
#define FACE_H
using namespace std;

#include <vector>
class Face {
    public:
        Face(){
            this -> vertices = new vector<int>();
            this -> textures = new vector<int>();
            this -> normals = new vector<int>();
        }
        void insertVertex(int vertexIndex){
            this -> vertices -> push_back(vertexIndex);
        }
        void insertTexture(int textureIndex){
            this -> textures -> push_back(textureIndex);
        }
        void insertNormal(int normalIndex){
            this -> normals -> push_back(normalIndex);
        }

        vector<int>* getVertices(){
            return this -> vertices;
        }

        vector<int>* getTextures(){
            return this -> textures;
        }

        vector<int>* getNormals(){
            return this -> normals;
        }
    private:
        vector<int>* vertices;
        vector<int>* textures;
        vector<int>* normals;
};
#endif