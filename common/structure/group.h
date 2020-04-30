#ifndef GROUP_H
#define GROUP_H
using namespace std;

#include <string>
#include <vector>
#include <structure/face.h>
#include <structure/material.h>

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
            return !this -> faces -> empty();
        }

        vector<Face*>* getFaces(){
            return this -> faces;
        }

        Material* getMaterial(){
            return this -> material;
        }
    private:
        string name;
        Material* material = NULL;
        vector<Face*>* faces;
};
#endif