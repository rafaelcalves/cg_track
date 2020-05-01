#ifndef MESH_H
#define MESH_H
using namespace std;

#include <external/glew/include/GL/glew.h>
#include <vector>
#include <structure/group.h>
#include <structure/material.h>

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

        void push3DAttributeToVector(vector<GLfloat>* vec, int index, vector<glm::vec3>* vec3){
            vec -> push_back(vec3 -> at(index).x);
            vec -> push_back(vec3 -> at(index).y);
            vec -> push_back(vec3 -> at(index).z);
        }
        void push2DAttributeToVector(vector<GLfloat>* vec, int index, vector<glm::vec2>* vec2){
            vec -> push_back(vec2 -> at(index).x);
            vec -> push_back(vec2 -> at(index).y);
        }

        void setup(){
            VaoConfig vao;
            this -> vao = vao;
            this -> vbos = new vector<VboConfig*>();

            for (auto &group : *groups){
                vector<GLfloat>* vboVector = new vector<GLfloat>();
                for (auto &face : *group -> getFaces()){
                    for (int i = 0; i < face -> getVertices() -> size(); i++) {
                        int index = face->getVertices() -> at(i) -1;
                        push3DAttributeToVector(vboVector,index, this -> vertices);
                        
                        if(!face->getTextures() -> empty()){
                            index = face->getTextures() -> at(i) -1;
                            push2DAttributeToVector(vboVector,index, this -> mappings);
                        }

                        if(!face->getNormals() -> empty()){
                            index = face->getNormals() -> at(i) -1;
                            push3DAttributeToVector(vboVector,index, this -> normals);
                        }
                    }
                }
                bindVbo(vboVector);
            }
        }

        void draw(Shader shader) {
            for (vector<Group*>::iterator group = groups->begin(); group != groups->end(); ++group) {
                vao.bind();
                Material* material = (*group)->getMaterial();
                glEnable(GL_TEXTURE_2D);
                if(material){
                    glActiveTexture(GL_TEXTURE0 + material->getId());
                    shader.setInt("texture_diffuse1",material->getId());
                    glBindTexture(GL_TEXTURE_2D, material->getId());
                }
                glDrawArrays(GL_TRIANGLES, 0, (*group)->getFaces()->size() * 3);
                glDisable(GL_TEXTURE_2D);
            }
        }



    private:
        vector<glm::vec3>* vertices;
        vector<glm::vec3>* normals;
        vector<glm::vec2>* mappings;
        vector<Group*>* groups;
        string materialLibPath;
        VaoConfig vao;
        vector<VboConfig*>* vbos;

        void bindVbo(vector<GLfloat>* vboVector){
            VboConfig* vbo = new VboConfig(vboVector);
            this -> vbos -> push_back(vbo);
            this -> vao.bindGroup(0,3,0);
            this -> vao.bindGroup(1,2,3);
            this -> vao.bindGroup(2,3,5);
        }
};
#endif