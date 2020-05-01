#ifndef VBOCONFIG_H
#define VBOCONFIG_H

using namespace std;

#include <vector>
#include <GL/glew.h>
class VboConfig {
    public:
        GLuint id;
        VboConfig(const void * data, GLsizeiptr size){
            this -> setup(data, size);
        }
        VboConfig(vector<GLfloat> * data){
            setup(data, data -> size() * sizeof(GLfloat));
        }
        VboConfig(vector<glm::vec3> * data){
            setup(data, data -> size() * sizeof(glm::vec3));
        }
        VboConfig(vector<glm::vec2> * data){
            setup(data, data -> size() * sizeof(glm::vec2));
        }

    private:
        void setup(const void * data, GLsizeiptr size){
            glGenBuffers (1, &id);
            glBindBuffer (GL_ARRAY_BUFFER, id);
            glBufferData (GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, id);
        }
};
#endif