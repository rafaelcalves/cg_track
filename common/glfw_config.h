#ifndef GLFW_CONFIG_H
#define GLFW_CONFIG_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <common/controls.hpp>

#define DEFAULT_WINDOW_TITLE "Trabalho GA"

class GlfwConfig {
    public:

        int init(glm::vec2 screen_size) {
            const char* errorMessage = "Failed to initialize GLFW\n";
            int result = glfwInit();
            if(!result) return handleClosingError(result, errorMessage);
            setScreenSize(screen_size);
            setWindowTitle(DEFAULT_WINDOW_TITLE);
            result = startWindow();
            return 0;
        }
        
        GLFWwindow* getWindow(){
            return window;
        }

    private:
        GLFWwindow* window;
        glm::vec2 screen_size;
        const char* window_title;

        int startWindow() {
            window = createWindow(screen_size);
            if(!isWindowOk()) return 0;
            glfwMakeContextCurrent(window);
            // Ensure we can capture the escape key being pressed below
            glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
            // Gray background
            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
            return 1;
        }

        GLFWwindow* createWindow(glm::vec2 screen_size) {
            configureWindow();
            window = glfwCreateWindow((int)screen_size.x, (int)screen_size.y, window_title, NULL, NULL);
            const char* errorMessage = "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n";
            int expectedResult = window != NULL;
            handleClosingError(expectedResult, errorMessage);
            return window;
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

        int isWindowOk(){
            if(window == NULL) return 0;
            return 1;
        }

        // process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
        // ---------------------------------------------------------------------------------------------------------
        void processEscInput(GLFWwindow *window)
        {
            if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
                glfwSetWindowShouldClose(window, true);
        }

        void setScreenSize(glm::vec2 screen_size) {
            this->screen_size = screen_size;
        }

        void setWindowTitle(const char* window_title) {
            this->window_title = window_title;
        }
};
#endif