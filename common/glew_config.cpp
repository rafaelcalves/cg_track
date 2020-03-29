#include <stdio.h>
#include <stdlib.h>

#include <iostream>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <common/controls.hpp>

#include "glew_config.hpp"

int initGlew(){
	// Initialize GLEW
    char* errorMessage = "Failed to initialize GLEW\n";
    int result = glewInit() != GLEW_OK;
    return handleClosingError(result, errorMessage);
}