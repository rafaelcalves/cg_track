#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <common/controls.hpp>

#include "glfw_config.hpp"

const char* DEFAULT_WINDOW_TITLE = "LearnOpenGL";

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int initGLFW() {
    char* errorMessage = "Failed to initialize GLFW\n";
    int result = glfwInit();
	return handleClosingError(result, errorMessage);
}

void configureWindow() {
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
    #endif
}

GLFWwindow* createWindow(glm::vec2 screen_size) {
    // glfw window creation
    // --------------------
    if(!initGLFW()) return NULL;
    configureWindow();
    GLFWwindow* window = glfwCreateWindow((int)screen_size.x, (int)screen_size.y, DEFAULT_WINDOW_TITLE, NULL, NULL);
    char* errorMessage = "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n";
    int result = window == NULL;
    handleClosingError(result, errorMessage);
	return window;
}

int isWindowOk(GLFWwindow *window){
    if(window == NULL) return 0;
    return 1;
}

GLFWwindow* startWindow(glm::vec2 screen_size) {
    
    GLFWwindow* window = createWindow(screen_size);
    if(!isWindowOk(window)) return NULL;
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    return window;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processEscInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}