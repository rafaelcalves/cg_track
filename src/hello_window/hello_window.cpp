#include <stdio.h>
#include <stdlib.h>

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
using namespace glm;

#include <common/glfw_config.hpp>
#include <common/glew_config.hpp>

const glm::vec2 SCREEN_SIZE(800, 600);

int main()
{
    if(!initGLFW()) return -1;
    GLFWwindow* window = startWindow(SCREEN_SIZE);
    if(!isWindowOk(window)) return -1;

    if(!initGlew()) return -1;

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
		// Clear the screen
		glClear( GL_COLOR_BUFFER_BIT );
        // input
        // -----
        processEscInput(window);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}