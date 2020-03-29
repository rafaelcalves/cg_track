#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <GLFW/glfw3.h>
#include "controls.hpp"
int handleClosingError(int isOk, std::string message){
    if(!isOk){
		fprintf(stderr, "%s", message.c_str());
		getchar();
		glfwTerminate();
		return 0;
    }
    return 1;
}