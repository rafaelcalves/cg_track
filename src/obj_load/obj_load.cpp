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

#define OBJ_MESA "mesa/mesa01.obj"
#define OBJ_PAINTBALL "paintball/cenaPaintball.obj"
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

    Shader ourShader("shaders/model_loading.vs", "shaders/model_loading.fs");
	ourShader.use();

//    glfwSetCursorPosCallback(glfw.getWindow(), onMouse);
    glfwSetScrollCallback(glfw.getWindow(), onZoom);
//
    Model* model = new Model(0.0f, 0.66f, new glm::vec3(2.16f, 3.16f, -7.68f));
    ObjReader tableReader(OBJ_MESA);
    Mesh* table = tableReader.read(model);
    table -> model = *model;
    objects->push_back(table);

    model = new Model( 0.0f, 0.66f, new glm::vec3(7.16f, 3.16f, -7.68f) );
    createObject(model, table);

    Model* modelPaintball = new Model(0.0f, 0.9f, new glm::vec3(0.00f, 0.0f, -2.68f));
    ObjReader paintballReader(OBJ_PAINTBALL);
    Mesh* paintball = paintballReader.read(modelPaintball);
    paintball -> model = *modelPaintball;
    objects->push_back(paintball);

    while (!glfwWindowShouldClose (glfw.getWindow())) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        onKeyPress();


        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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