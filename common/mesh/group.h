#ifndef GROUP_H
#define GROUP_H
using namespace std;

#include <string>
#include <vector>
#include <mesh/face.h>
#include <mesh/material.h>

class Group {
    public:
        Group(){
            this -> faces = new vector<Face*>();
        }
        Group(string name){
            this -> faces = new vector<Face*>();
            this -> name = name;
        }
        void setName(string name){
            this -> name = name;
        }
        void setMaterial(string materialName, vector<Material*>* materials) {
            for (auto &material : *materials){
                if(material -> getName() == materialName){
                    this -> material = material;
                }
            }
        }
        void insertFace(Face* face){
            this -> faces -> push_back(face);
        }
        int hasFaces(){
            return !this -> faces -> empty();
        }

        vector<Face*>* getFaces(){
            return this -> faces;
        }
    private:
        string name;
        Material* material;
        vector<Face*>* faces;
};
#endif