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

        void push3DAttributeToVector(vector<GLfloat>* vec, int index){
            vec -> push_back(this -> vertices -> at(index).x);
            vec -> push_back(this -> vertices -> at(index).y);
            vec -> push_back(this -> vertices -> at(index).z);
        }
        void push2DAttributeToVector(vector<GLfloat>* vec, int index){
            vec -> push_back(this -> vertices -> at(index).x);
            vec -> push_back(this -> vertices -> at(index).y);
        }

        void setup(){
            VaoConfig vao;
            this -> vao = vao;
            this -> vbos = new vector<VboConfig*>();

            for (auto &group : *groups){
                vector<GLfloat> vboVector;
                for (auto &face : *group -> getFaces()){
                    for (int i = 0; i < face -> getVertices() -> size(); i++) {
                        int index = face->getVertices() -> at(i);
                        push3DAttributeToVector(&vboVector,index);
                        
                        if(!face->getTextures() -> empty()){
                            index = face->getTextures() -> at(i);
                            push3DAttributeToVector(&vboVector,index);
                        }

                        if(!face->getNormals() -> empty()){
                            index = face->getNormals() -> at(i);
                            push3DAttributeToVector(&vboVector,index);
                        }
                    }
                }
                vboVector = vboVector;
            }
        }


        //     for (vector<Group*>::iterator group = groups->begin(); group != groups->end(); ++group) {
		// 	vector<GLfloat> vboVector;
		// 	for (vector<Face*>::iterator face = (*group)->faces->begin(); face != (*group)->faces->end(); ++face) {
		// 		for (
		// 			int vIndex = 0, tIndex = 0, nIndex = 0;
		// 			vIndex < (*face)->vertices.size();
		// 			vIndex++, tIndex++, nIndex++
		// 			) {

		// 			auto index = (*face)->vertices[vIndex];
		// 			finalVector.push_back(vertices->at(index)->x);
		// 			finalVector.push_back(vertices->at(index)->y);
		// 			finalVector.push_back(vertices->at(index)->z);

		// 			index = (*face)->textures[tIndex];
		// 			finalVector.push_back(textures->at(index)->x);
		// 			finalVector.push_back(textures->at(index)->y);

		// 			index = (*face)->normals[nIndex];
		// 			finalVector.push_back(normals->at(index)->x);
		// 			finalVector.push_back(normals->at(index)->y);
		// 			finalVector.push_back(normals->at(index)->z);
		// 		}
		// 	}
		// 	(*group)->setup(finalVector, shader);
		// }

        
    private:
        vector<glm::vec3>* vertices;
        vector<glm::vec3>* normals;
        vector<glm::vec2>* mappings;
        vector<Group*>* groups;
        string materialLibPath;
        VaoConfig vao;
        vector<VboConfig*>* vbos;

        void bindVbo(const void *data, GLsizeiptr totalSize, int dataSize){
            VboConfig* vbo = new VboConfig(data, totalSize);
            this -> vbos -> push_back(vbo);
            vao.bind(this -> vbos -> size(),dataSize);
        }
};
#endif