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

GLfloat getNormal(GLfloat lastPosition){
    return lastPosition > 0 ? 1 : -1;
}
GLfloat calculateReflection(GLfloat normal, GLfloat speed){
    return 2 * normal * (normal * - speed) + speed;
}

GLfloat calculateNextPosition(GLfloat elapsedSeconds, GLfloat speed, GLfloat lastPosition){
    return elapsedSeconds * speed + lastPosition;
}

GLfloat hasHitAWall(GLfloat lastPosition){
    return fabs(lastPosition) + 0.5f > 1.0f;
}

GLfloat getReflectionPosition(GLfloat lastPosition, GLfloat speed){
    if (hasHitAWall(lastPosition)) {
        GLfloat normal = getNormal(lastPosition);
        return calculateReflection(normal, speed);
    }
    return speed;
}

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
    
    VaoConfig vao;
    VboConfig pointsVbo(points);
    vao.bind(0);
    VboConfig colorsVbo(colors);
    vao.bind(1);

    glm::vec2 speed (.5f, .6f);
    glm::vec2 lastPosition (.0f, .0f);
	ourShader.use();
	while (!glfwWindowShouldClose (glfw.getWindow())) {
	
        static double previousSeconds = glfwGetTime();
        double currentSeconds = glfwGetTime();
        double elapsedSeconds = currentSeconds - previousSeconds;
        if(elapsedSeconds > 0) {
            previousSeconds = currentSeconds;
            speed.x = getReflectionPosition(lastPosition.x, speed.x);
            speed.y = getReflectionPosition(lastPosition.y, speed.y);

            matrix[3][0] = calculateNextPosition(elapsedSeconds, speed.x, lastPosition.x);
            matrix[3][1] = calculateNextPosition(elapsedSeconds, speed.y, lastPosition.y);
            lastPosition.x = matrix[3][0];
            lastPosition.y = matrix[3][1];
        }

        ourShader.setMat4("matrix",matrix);
	
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glBindVertexArray (vao.getId());
		glDrawArrays (GL_TRIANGLES, 0, 3);

		glfwPollEvents ();
		glfwSwapBuffers (glfw.getWindow());
	}
	glfwTerminate();
	return 0;
}