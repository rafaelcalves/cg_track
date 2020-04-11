#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <math.h>
#include <common/glew_config.h>
#include <common/glfw_config.h>
#include <common/shaders.h>
#include <common/vaoConfig.h>
#include <common/vboConfig.h>
#include <common/reflection.h>

const glm::vec2 SCREEN_SIZE(800, 600);

int main () {
    GLfloat points[]={
         0.0f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f
    };
	
	GLfloat colors[]={
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
	};

	glm::mat4 matrix (
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );

    GlfwConfig glfw;
    glfw.init(SCREEN_SIZE);

    GlewConfig glew;
    glew.init();

    Shader ourShader("shader.vs", "shader.fs");
    
    VaoConfig vao;
    VboConfig pointsVbo(points);
    vao.bind(0);
    VboConfig colorsVbo(colors);
    vao.bind(1);

    Reflection reflection (.5f, .6f);
	ourShader.use();
	while (!glfwWindowShouldClose (glfw.getWindow())) {
	
        static double previousSeconds = glfwGetTime();
        double currentSeconds = glfwGetTime();
        double elapsedSeconds = currentSeconds - previousSeconds;
        if(elapsedSeconds > 0) {
            previousSeconds = currentSeconds;
            matrix = reflection.calculateReflectedMatrix(matrix,elapsedSeconds);
        }

        ourShader.setMat4("matrix",matrix);
	
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glBindVertexArray (vao.getId());
		glDrawArrays (GL_TRIANGLES, 0, 3);

		glfwPollEvents ();
		glfwSwapBuffers (glfw.getWindow());
	}
	glfwTerminate();
	return 0;
}