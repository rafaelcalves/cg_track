#ifndef MESH_H
#define MESH_H
using namespace std;

#include <glm/glm.hpp>
#include <vector>
#include <mesh/group.h>
#include <mesh/material.h>

class Mesh {
    public:
        Mesh(){
            this -> vertices = new vector<glm::vec3>();
            this -> normals = new vector<glm::vec3>();
            this -> mappings = new vector<glm::vec2>();
            this -> groups = new vector<Group*>();
        }
        void insertVertex(glm::vec3 vertex){
            this -> vertices -> push_back(vertex);
        }
        void insertMapping(glm::vec2 mapping){
            this -> mappings -> push_back(mapping);
        }
        void insertNormal(glm::vec3 normal){
            this -> normals -> push_back(normal);
        }
        void insertGroup(Group* group){
            this -> groups -> push_back(group);
        }
        void setMaterialLib(string materialLibPath){
            this -> materialLibPath = materialLibPath;
        }
    private:
        vector<glm::vec3>* vertices;
        vector<glm::vec3>* normals;
        vector<glm::vec2>* mappings;
        vector<Group*>* groups;
        string materialLibPath;
};
#endif