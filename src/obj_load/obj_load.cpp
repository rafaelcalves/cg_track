#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

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


#define OBJ_AL "al/al.obj"
#define OBJ_MESA "mesa/mesa01.obj"
#define OBJ_CUBE "cube/cube.obj"

void onResize(GLFWwindow* window, int width, int height);
void onMouse(GLFWwindow* window, double xpos, double ypos);
void onZoom(GLFWwindow* window, double xoffset, double yoffset);
void onKeyPress();

int textureNum = 0;
float scaleFactor = 45.0f;

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

const glm::vec2 SCREEN_SIZE(WIDTH, HEIGHT);

GlfwConfig glfw;
GlewConfig glew;


Camera camera(glm::vec3(1.0f, 7.0f, 10.0f));
float lastX = WIDTH / 2.0f;
float lastY = HEIGHT / 2.0f; 
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;
float translation = -1.0f;

vector<Mesh*>* objects = new vector<Mesh*>();
int selectedObject = -1;

void createObject(Model* modelData, Mesh *origin) {
    Mesh* newMesh = new Mesh(modelData);
    newMesh->copy(origin);
    objects->push_back(newMesh);
}

int main () {
    glfw.init(SCREEN_SIZE);
    glew.init();

    Shader ourShader("Shaders/model_loading.vs", "shader.fs");
	ourShader.use();

    glfwSetCursorPosCallback(glfw.getWindow(), onMouse);
    Model* model = new Model(0.0f, 0.66f, new glm::vec3(0.16f, 2.83f, -9.68f));
    ObjReader cubeReader(OBJ_CUBE);
    Mesh* cubo = cubeReader.read(model);
    cubo -> model = *model;
    objects->push_back(cubo);

    ourShader.setFloat("ambientIntensity", 0.8f);
    ourShader.setFloat("lightIntensity", 0.8f);

    while (!glfwWindowShouldClose (glfw.getWindow())) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        onKeyPress();

        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ourShader.setVec3("camera", camera.Position.x, camera.Position.y, camera.Position.z);
        for (auto &object : *objects) {
            object->setup();
            glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
            glm::mat4 view = camera.getViewMatrix();
            ourShader.setMat4("projection", projection);
            ourShader.setMat4("view", view);

            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, *object->model.translate);
            model = glm::rotate(model, glm::radians(*object -> model.rotation), glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::scale(model, glm::vec3(*object -> model.scale, *object -> model.scale, *object -> model.scale));
            ourShader.setMat4("model", model);
            ourShader.setFloat("colorPercentage",0.2f); //selectedObject == i ? 0.2f : 0.0f

            object -> draw(ourShader);
        }

        glfwPollEvents();
		glfwSwapBuffers (glfw.getWindow());
	}	
	glfwTerminate();
	return 0;
}

void onKeyPress() {
     if (glfwGetKey(glfw.getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
     	glfwSetWindowShouldClose(glfw.getWindow(), true);
     if (glfwGetKey(glfw.getWindow(), GLFW_KEY_UP) == GLFW_PRESS)
     	camera.processKeyboard(FORWARD, deltaTime);
     if (glfwGetKey(glfw.getWindow(), GLFW_KEY_DOWN) == GLFW_PRESS)
     	camera.processKeyboard(BACKWARD, deltaTime);
     if (glfwGetKey(glfw.getWindow(), GLFW_KEY_LEFT) == GLFW_PRESS)
     	camera.processKeyboard(LEFT, deltaTime);
     if (glfwGetKey(glfw.getWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS)
     	camera.processKeyboard(RIGHT, deltaTime);
}

void onResize(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void onMouse(GLFWwindow* window, double xPosition, double yPosition) {
    if (firstMouse) {
        lastX = xPosition;
        lastY = yPosition;
        firstMouse = false;
    }

    float xOffset = xPosition - lastX;
    float yOffset = lastY - yPosition;

    lastX = xPosition;
    lastY = yPosition;

    camera.ProcessMouseScroll(xOffset, yOffset);
}

void onZoom(GLFWwindow* window, double xoffset, double yoffset) {
    camera.ProcessMouseZoom(yoffset);
}