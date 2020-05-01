#ifndef GLEW_CONFIG_H
#define GLEW_CONFIG_H

#include <external/glew/include/GL/glew.h>
#include <common/controls.hpp>

class GlewConfig {
    public:

    int init(){
        glewExperimental = GL_TRUE;
        const char* errorMessage = "Failed to initialize GLEW\n";
        int expectedResult = glewInit() == GLEW_OK;
        return handleClosingError(expectedResult, errorMessage);
    }
};
#endif