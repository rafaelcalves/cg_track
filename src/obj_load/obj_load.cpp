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

//#include <common/glew_config.h>
//#include <common/glfw_config.h>
//#include <common/shaders.h>
#include <common/vaoConfig.h>
#include <common/vboConfig.h>
#include <common/configuration.h>

#include <structure/objReader.h>
#include <structure/material.h>
#include <structure/camera.h>
//#include <structure/scene.h>

#define OBJ_CUBE "cube/cube.obj"

void onResize(GLFWwindow* window, int width, int height);
void onMouse(GLFWwindow* window, double xpos, double ypos);
void onZoom(GLFWwindow* window, double xoffset, double yoffset);
void onKeyPress();
void configureShader(glm::mat4* model);
void shot();
void drawObject(Mesh *shot);

bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

vector<Mesh*>* shots = new vector<Mesh*>();
Configuration configuration;
Scene* scene;

int main () {
    scene = configuration.init("teste");

    glfwSetCursorPosCallback(scene -> window, onMouse);
    glfwSetScrollCallback(scene -> window, onZoom);

    while (!glfwWindowShouldClose (scene -> window)) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        onKeyPress();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (auto &object : *scene -> objects) {
            if(object -> model.visible) {
                drawObject(object);
            }
        }

        for (auto &shot : *shots) {
            if(shot -> model.visible) {
                shot->model.move(deltaTime);
                for (auto &object : *scene -> objects) {
                    if(shot -> handleCollision(object, scene -> camera)) break;
                }
                drawObject(shot);
            }
        }
        glfwPollEvents();
		glfwSwapBuffers(scene -> window);
	}	
	glfwTerminate();
	return 0;
}

void drawObject(Mesh *shot) {
    shot -> setup();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, shot->model.translate);
    model = glm::rotate(model, glm::radians(*shot->model.rotation), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(*shot->model.scale, *shot->model.scale, *shot->model.scale));
    configureShader(&model);
    shot -> draw(scene -> shader);
}

void configureShader(glm::mat4* model){
    glm::mat4 projection = glm::perspective(glm::radians(scene -> camera -> Zoom), (float)scene -> screenSize -> x / (float)scene -> screenSize -> y, 0.1f, 100.0f);
    glm::mat4 view = scene -> camera -> getViewMatrix();
    scene -> shader -> setMat4("projection", projection);
    scene -> shader -> setMat4("view", view);
    scene -> shader -> setMat4("model", *model);
}

void onKeyPress() {
    if (glfwGetKey(scene -> window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(scene -> window, true);
    if (glfwGetKey(scene -> window, GLFW_KEY_UP) == GLFW_PRESS)
        scene -> camera -> processKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(scene -> window, GLFW_KEY_DOWN) == GLFW_PRESS)
        scene -> camera -> processKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(scene -> window, GLFW_KEY_LEFT) == GLFW_PRESS)
        scene -> camera -> processKeyboard(LEFT, deltaTime);
    if (glfwGetKey(scene -> window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        scene -> camera -> processKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(scene -> window, GLFW_KEY_SPACE) == GLFW_PRESS)
        shot();
}

void shot(){
    Model* shotModel = new Model(0.0f, 0.80f, scene -> camera -> Position, scene -> camera -> Front);
    ObjReader shotReader(OBJ_CUBE);
    Mesh* shot = shotReader.read(shotModel);
    shot -> model = *shotModel;
    shots->push_back(shot);
}

void onResize(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void onMouse(GLFWwindow* window, double xPosition, double yPosition) {
    if (firstMouse) {
        scene -> camera -> lastX = xPosition;
        scene -> camera -> lastY = yPosition;
        firstMouse = false;
    }

    float xOffset = xPosition - scene -> camera -> lastX;
    float yOffset = scene -> camera -> lastY - yPosition;

    scene -> camera -> lastX = xPosition;
    scene -> camera -> lastY = yPosition;

    scene -> camera -> ProcessMouseScroll(xOffset, yOffset);
}

void onZoom(GLFWwindow* window, double xoffset, double yoffset) {
    scene -> camera -> ProcessMouseZoom(yoffset);
}