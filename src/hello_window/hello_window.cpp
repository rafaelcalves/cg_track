#include <stdio.h>
#include <stdlib.h>

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
using namespace glm;

#include <common/glew_config.h>
#include <common/glfw_config.h>

const glm::vec2 SCREEN_SIZE(800, 600);

int main()
{
    GlfwConfig glfw;
    glfw.init(SCREEN_SIZE);

    GlewConfig glew;
    glew.init();
    
    // render loop
    // -----------
    while (!glfwWindowShouldClose(glfw.getWindow()))
    {
		// Clear the screen
		glClear( GL_COLOR_BUFFER_BIT );
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(glfw.getWindow());
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}