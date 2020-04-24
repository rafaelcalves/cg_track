#include <GL/glew.h>
class VboConfig {
    public:
        GLuint id;
        VboConfig(const void * data, GLsizeiptr size){
            glGenBuffers (1, &id);
            glBindBuffer (GL_ARRAY_BUFFER, id);
            glBufferData (GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, id);
        }
    private:
};