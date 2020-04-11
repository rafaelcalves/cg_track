#include <GL/glew.h>
class VboConfig {
    public:
        VboConfig(const void * data){
            glGenBuffers (1, &id);
            glBindBuffer (GL_ARRAY_BUFFER, id);
            glBufferData (GL_ARRAY_BUFFER, 9 * sizeof (GLfloat), data, GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, id);
        }
    private:
        GLuint id;
};