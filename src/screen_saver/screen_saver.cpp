#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <math.h>
#include <common/glew_config.h>
#include <common/glfw_config.h>
#include <common/shaders.h>
#include <common/vaoConfig.h>
#include <common/vboConfig.h>
#include <common/reflection.h>

const glm::vec2 SCREEN_SIZE(800, 600);

int main () {
    vector<GLfloat> pointsV ={
            0.0f,  0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f
    };
    vector<GLfloat>* points = new vector<GLfloat>(pointsV);

    vector<GLfloat> colorsV={
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f
    };
    vector<GLfloat>* colors= new vector<GLfloat>(colorsV);

    vector<GLfloat> oneV ={
            0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f
    };
    vector<GLfloat>* one = new vector<GLfloat>(oneV);

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
    //VboConfig pointsVbo(points -> data(), points -> size());
    //vao.bind(0, 3);
    //VboConfig colorsVbo(colors -> data(), colors -> size());
    //vao.bind(1, 3);

    VboConfig oneVbo(one -> data(), one -> size());
    vao.bind(0, 3, 6 * sizeof(GLfloat), NULL);
    vao.bind(1, 3, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));

    Reflection reflection (.5f, .6f, .01f);
    ourShader.use();
    while (!glfwWindowShouldClose (glfw.getWindow())) {
        matrix = reflection.calculateReflectedMatrix(matrix);
        ourShader.setMat4("matrix",matrix);

        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        vao.bind();
        glDrawArrays (GL_TRIANGLES, 0, one->size()/6);

        glfwPollEvents ();
        glfwSwapBuffers (glfw.getWindow());
    }
    glfwTerminate();
    return 0;
}