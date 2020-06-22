#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <map>

#define STB_IMAGE_IMPLEMENTATION

#include <structure/cfgReader.h>
#include <structure_curve/txtReader.h>
#include <zconf.h>

#define OBJ_CUBE "cube/cube.obj"
#define OBJ_CAR "car/Van_Delivery.obj"

void onResize(GLFWwindow* window, int width, int height);
void onMouse(GLFWwindow* window, double xpos, double ypos);
void onZoom(GLFWwindow* window, double xoffset, double yoffset);
void onKeyPress();
void configureShader(glm::mat4* model);
void shot();
void newCar();
void drawObject(Mesh *mesh);
void scaleCurve(vector<glm::vec3>* points, float factor);

bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

vector<Mesh*>* shots = new vector<Mesh*>();
vector<Mesh*>* cars = new vector<Mesh*>();
Scene* scene;
vector<glm::vec3>* route;

int main () {
    CfgReader config("resources/config/curve.cfg");
    scene = config.read();

    TxtReader curveReader("curve/ourCurve.txt");
    route = curveReader.read();
    scaleCurve(route,50);

    glfwSetCursorPosCallback(scene -> window, onMouse);
    glfwSetScrollCallback(scene -> window, onZoom);

    scene->shader->setFloat("ambientIntensity", .8f);
    scene->shader->setFloat("lightIntensity", .2f);

    while (!glfwWindowShouldClose (scene -> window)) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        onKeyPress();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        scene -> shader -> setVec3("camera", scene->camera->Front);

        for (auto &object : *scene -> objects) {
            if(object -> model.visible) {
                drawObject(object);
            }
        }
        for (auto &car : *cars) {
            if(car -> model.visible) {
                car->model.move(deltaTime);
                drawObject(car);
            }
        }

        for (auto &shot : *shots) {
            if(shot -> model.visible) {
                shot->model.move(deltaTime);
                for (auto &object : *scene -> objects) {
                    if(shot -> handleCollision(object)) break;
                }
                for (auto &object : *cars) {
                    if(shot -> handleCollision(object)) break;
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

void scaleCurve(vector<glm::vec3>* points, float factor) {
    vector<glm::vec3>* scaledCurvePoints = new vector<glm::vec3>();

    for (int i = 0; i < points->size(); i++) {
        scaledCurvePoints->push_back(glm::vec3(points->at(i).x * factor, points->at(i).y, points->at(i).z * factor));
    }
    route = scaledCurvePoints;
}

void drawObject(Mesh *mesh) {
    mesh -> setup();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, mesh->model.translate);
    model = glm::rotate(model, *mesh->model.rotation,  glm::vec3(0.0f,1.0f,0.0f));
    model = glm::scale(model, glm::vec3(*mesh->model.scale, *mesh->model.scale, *mesh->model.scale));
    configureShader(&model);
    mesh -> draw(scene -> shader);
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
    if (glfwGetKey(scene -> window, GLFW_KEY_ENTER) == GLFW_PRESS)
        newCar();
}

void shot(){
    Model* shotModel = new Model(0, 0.80f, scene -> camera -> Position, scene -> camera -> Front);
    ObjReader shotReader(OBJ_CUBE);
    Mesh* shot = shotReader.read(shotModel);
    shot -> model = *shotModel;
    shots->push_back(shot);
    usleep(200000);
}

void newCar(){
    Model* carModel = new Model(0.0f, 0.03f, route->at(0));
    ObjReader carReader(OBJ_CAR);
    Mesh* car = carReader.read(carModel);
    car -> model = *carModel;
    car -> model.route = route;
    car -> model.dynamic = true;
    cars->push_back(car);
    usleep(200000);
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