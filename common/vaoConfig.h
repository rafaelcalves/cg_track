#include <GL/glew.h>
class VaoConfig {
    public:
        GLuint id;
        VaoConfig(){
            glGenVertexArrays(1, &id);
            glBindVertexArray(id);
        }
        
        void bind(int attribute, int size, GLsizei stride, void* pointer){
            glEnableVertexAttribArray(attribute);
            glVertexAttribPointer(attribute, size, GL_FLOAT, GL_FALSE, stride ,pointer);
        }

        void bind(int attribute, int size){
            this -> bind(attribute, size, 0, NULL);
        }
    private:
};