#include <GL/glew.h>
class VaoConfig {
    public:
        VaoConfig(){
            glGenVertexArrays(1, &id);
            glBindVertexArray(id);
        }

        void bind(int attribute){
            glEnableVertexAttribArray(attribute);
            glVertexAttribPointer(attribute, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        }

        int getId(){
            return id;
        }
    private:
        GLuint id;
};