#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdio.h>
#include <math.h>
#include <map>
#include <vector>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <common/glew_config.h>
#include <common/glfw_config.h>
#include <common/shaders.h>
#include <common/vaoConfig.h>
#include <common/vboConfig.h>
#include <common/reflection.h>

#include <structure/objReader.h>
#include <structure/group.h>
#include <structure/material.h>
#include <structure/Obj3D.h>

#define OBJ_AL "resources/al/al.obj"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
void readCurvePoints(const GLchar* path);
void scaleCurvePoints(std::vector<glm::vec3*>* points, float factor);
float calculateAngle(int indexA, int indexB);

int textureNum = 0;
float scaleFactor = 45.0f;

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

const glm::vec2 SCREEN_SIZE(WIDTH, HEIGHT);

Camera camera(glm::vec3(0.0f, 7.0f, 10.0f));
float lastX = WIDTH / 2.0f;
float lastY = HEIGHT / 2.0f; 
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

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

    VaoConfig vao;
    // VboConfig pointsVbo(points, 9 * sizeof(GLfloat));
    // vao.bind(0, 3);
    // VboConfig colorsVbo(colors, 9 * sizeof(GLfloat));
    // vao.bind(1, 3);

    Reflection reflection (.5f, .6f, .01f);
	ourShader.use();

	vector<Group*>* currentGroup = nullptr;
	std::vector<Mesh*>* meshVec = new std::vector<Mesh*>();

    glm::mat4 projection(1);

	while (!glfwWindowShouldClose (glfw.getWindow())) {

	    ourShader.use();
        matrix = reflection.calculateReflectedMatrix(matrix);
        ourShader.setMat4("matrix",matrix);
        glEnable(GL_DEPTH_TEST);


		glClearColor(0.6f, 0.6f, 0.6f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 model(1);
		glm::mat4 view(1);

		projection = glm::perspective(glm::radians(camera.Zoom), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
		view = camera.getViewMatrix();
		
		//  vao.bind();
		//  glDrawArrays (GL_TRIANGLES, 0, 3);
		
        objShader.use();

		ObjReader objReader("al/al.obj");
    	Mesh *AL = objReader.read();
		//Adicionar escala e posição no Obj3D antes do push_back

		meshVec -> push_back(AL);
		AL -> draw(objShader);

		glfwPollEvents ();
		glfwSwapBuffers (glfw.getWindow());
	}	
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		camera.processKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		camera.processKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		camera.processKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		camera.processKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}