#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <common/controls.hpp>

class GladConfig {
    public:
        int init() {
            // glad: load all OpenGL function pointers
            // ---------------------------------------
            int result = !gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
            const char* errorMessage = "Failed to initialize GLAD";
            return handleClosingError(result, errorMessage);
        }
};