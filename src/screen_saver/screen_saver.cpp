#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <math.h>
#include <common/glew_config.h>
#include <common/glfw_config.h>
#include <common/shaders.h>
#include <common/vaoConfig.h>
#include <common/vboConfig.h>

const glm::vec2 SCREEN_SIZE(800, 600);

int main () {
	const GLubyte* renderer;
	const GLubyte* version;
	GLuint vbo, colorsVBO;
	
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

	glClearColor(0.6f, 0.6f, 0.8f, 1.0f);

	float speed = 1.0f;
	float lastPosition = 0.0f;
	ourShader.use();
	while (!glfwWindowShouldClose (glfw.getWindow())) {
	
		static double previousSeconds = glfwGetTime();
		double currentSeconds = glfwGetTime();
		double elapsedSeconds = currentSeconds - previousSeconds;
		if(elapsedSeconds > 0) {
			previousSeconds = currentSeconds;
			if(fabs(lastPosition) > 1.0f){
				speed = -speed;
			}
			matrix[3][0] = elapsedSeconds * speed + lastPosition;
			lastPosition = matrix[3][0];
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