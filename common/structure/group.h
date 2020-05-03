#ifndef GROUP_H
#define GROUP_H
using namespace std;

#include <string>
#include <vector>
#include <structure/face.h>
#include <structure/material.h>

class Group {
    public:
        string* name;
        Material* material = nullptr;
        vector<Face*>* faces;
        vector<GLfloat>* vboVector;
        VaoConfig* vao;
        VboConfig* vbo;

        Group(){
            this -> faces = new vector<Face*>();
        }

        Group(string name){
            this -> faces = new vector<Face*>();
            this -> name = &name;
        }

        void setMaterial(string materialName, vector<Material*>* materials) {
            for (auto &material : *materials){
                if(material -> name == materialName){
                    this -> material = material;
                    return;
                }
            }
            this -> material = NULL;
            return;
        }

        void insertFace(Face* face){
            this -> faces -> push_back(face);
        }

        int hasFaces(){
            return this->faces != nullptr && !this -> faces -> empty();
        }

        bool hasMaterials(){
		    if (this->material != NULL)
			    return true;
		    else
			    return false;
        }
};
#endif