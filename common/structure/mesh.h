#ifndef MESH_H
#define MESH_H
using namespace std;

#include <GL/glew.h>
#include <vector>
#include <structure/group.h>
#include <structure/model.h>

class Mesh {
    public:
        vector<glm::vec3>* vertices;
        vector<glm::vec3>* normals;
        vector<glm::vec2>* mappings;
        vector<Group*>* groups;
        string* materialLibPath;
        Model model;

        Mesh(){
            initAttributes();
        }

        Mesh(Model* model) {
            initAttributes();
            this -> model = *model;
        }

        void copy(Mesh* origin) {
            this->vertices = origin->vertices;
            this->normals = origin->normals;
            this->mappings = origin->mappings;
            this->groups = origin->groups;
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
            for (auto &group : *groups){
                vector<GLfloat>* vboVector = new vector<GLfloat>();
                for (auto &face : *group -> faces){
                    for (int i = 0; i < face -> getVertices() -> size(); i++) {
                        int index = face->getVertices() -> at(i) -1;
                        push3DAttributeToVector(vboVector,index, this -> vertices);
                        
                        if(!face->getTextures() -> empty()){
                            index = face->getTextures() -> at(i) -1;
                            push2DAttributeToVector(vboVector,index, this -> mappings);
                        } else {
                            vboVector -> push_back(.0);
                            vboVector -> push_back(.0);
                        }

                        if(!face->getNormals() -> empty()){
                            index = face->getNormals() -> at(i) -1;
                            push3DAttributeToVector(vboVector,index, this -> normals);
                        }
                    }
                }
                VaoConfig* vao = new VaoConfig();
                group -> vboVector = vboVector;
                group -> vao = vao;
                bindVbo(vboVector, group);
            }
        }

        void draw(Shader shader) {
            for (auto &group : *groups){
                group -> vao -> bind();
                Material* material = group-> material;
                glEnable(GL_TEXTURE_2D);
                if(material){
                    glActiveTexture(GL_TEXTURE0 + *material->textureId);
                    shader.setInt("diffuse",*material->textureId);
                    glBindTexture(GL_TEXTURE_2D, *material->textureId);
                }
                glDrawArrays(GL_TRIANGLES, 0, group -> fullSize);
                glDisable(GL_TEXTURE_2D);
            }
        }

    private:

        void initAttributes(){
            this -> vertices = new vector<glm::vec3>();
            this -> normals = new vector<glm::vec3>();
            this -> mappings = new vector<glm::vec2>();
            this -> groups = new vector<Group*>();
        }

        void bindVbo(vector<GLfloat>* vboVector, Group* group){
            VboConfig* vbo = new VboConfig(vboVector -> data(), vboVector -> size());

            group -> vao -> bind(0, 3, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
            group -> vao -> bind(1, 2, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
            group -> vao -> bind(2, 3, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
            group -> vbo = vbo;
        }
};
#endif