#ifndef GLFW_CONFIG_HPP
#define GLFW_CONFIG_HPP

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

int initGLFW();
void configureWindow();
GLFWwindow* createWindow(glm::vec2 screen_size);
int isWindowOk(GLFWwindow *window);
GLFWwindow* startWindow(glm::vec2 screen_size);
void processEscInput(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

#endif