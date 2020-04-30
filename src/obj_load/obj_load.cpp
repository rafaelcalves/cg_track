#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <math.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <common/glew_config.h>
#include <common/glfw_config.h>
#include <common/shaders.h>
#include <common/vaoConfig.h>
#include <common/vboConfig.h>
#include <common/reflection.h>

#include <mesh/objReader.h>

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
    Shader objShader("Shaders/Core/core.vert", "Shaders/Core/core.frag");
    
    ObjReader objReader("al/al.obj");
    Mesh* mesh = objReader.read();
    mesh -> setup();

    VaoConfig vao;
    VboConfig pointsVbo(points, 9 * sizeof(GLfloat));
    vao.bind(0, 3);
    VboConfig colorsVbo(colors, 9 * sizeof(GLfloat));
    vao.bind(1, 3);

    Reflection reflection (.5f, .6f, .01f);
	ourShader.use();
	while (!glfwWindowShouldClose (glfw.getWindow())) {

	    ourShader.use();
        matrix = reflection.calculateReflectedMatrix(matrix);
        ourShader.setMat4("matrix",matrix);
        glEnable(GL_DEPTH_TEST);
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		vao.bind();
		glDrawArrays (GL_TRIANGLES, 0, 3);


        objShader.use();
        mesh -> draw(objShader);

		glfwPollEvents ();
		glfwSwapBuffers (glfw.getWindow());
	}
	glfwTerminate();
	return 0;
}