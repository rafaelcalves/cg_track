#include <glad/glad.h>
#include <GLFW/glfw3.h> /* GLFW helper library */
#include <stdio.h>
#include <math.h>
#include <common/glfw_config.hpp>
#include <common/glew_config.hpp>
#include <common/shaders.h>

const glm::vec2 SCREEN_SIZE(800, 600);

int main () {
	const GLubyte* renderer;
	const GLubyte* version;
	GLuint vao, vao2;
	GLuint vbo, vbo2;
	/* geometry to use. these are 3 xyz points (9 floats total) to make a triangle
	*/
	
	typedef struct Vertex {
		GLfloat coords[3];
	} VecXYZ;
	
	VecXYZ points[3];
	points[0].coords[0]=0.0f;
	points[0].coords[1]=0.75f;
	points[0].coords[2]=0.0f;
	points[1].coords[0]=0.5f;
	points[1].coords[1]=-0.5f;
	points[1].coords[2]=0.0f;
	points[2].coords[0]=-0.5f;
	points[2].coords[1]=-0.5f;
	points[2].coords[2]=0.0f;
	
	GLfloat colors[]={
	  1.0f, 0.0f, 0.0f,
	  0.0f, 1.0f, 0.0f,
	  0.0f, 0.0f, 1.0f
	};

	glm::mat4 matrix(
		0.707106781186548f, -0.707106781186548f, 0.0f, 0.0f,
		0.707106781186548f, 0.707106781186548f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.1f, 0.0f, 0.0f, 1.0f
    );

    if(!initGLFW()) return -1;
    GLFWwindow* window = startWindow(SCREEN_SIZE);
    if(!isWindowOk(window)) return -1;

    if(!initGlew()) return -1;
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Shader ourShader("shader.vs", "shader.fs");

	/* get version info */
	renderer = glGetString (GL_RENDERER); /* get renderer string */
	version = glGetString (GL_VERSION); /* version as a string */
	printf ("Renderer: %s\n", renderer);
	printf ("OpenGL version supported %s\n", version);

	/* tell GL to only draw onto a pixel if the shape is closer to the viewer */
	glEnable (GL_DEPTH_TEST); /* enable depth-testing */
	glDepthFunc (GL_LESS);/*depth-testing interprets a smaller value as "closer"*/

	/* a vertex buffer object (VBO) is created here. this stores an array of data
	on the graphics adapter's memory. in our case - the vertex points */
	glGenBuffers (1, &vbo);
	glBindBuffer (GL_ARRAY_BUFFER, vbo);
	glBufferData (GL_ARRAY_BUFFER, 9 * sizeof (GLfloat), points, GL_STATIC_DRAW);
	
	
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0); // habilitado primeiro atributo do vbo bound atual
    glBindBuffer(GL_ARRAY_BUFFER, vbo); // identifica vbo atual
    // associação do vbo atual com primeiro atributo
    // 0 identifica que o primeiro atributo está sendo definido
    // 3, GL_FLOAT identifica que dados são vec3 e estão a cada 3 float.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    // é possível associar outros atributos, como normais, mapeamento e cores
    // lembre-se: um por vértice!
    GLuint colorsVBO;
        glGenBuffers (1, &colorsVBO);
        glBindBuffer (GL_ARRAY_BUFFER, colorsVBO);
        glBufferData (GL_ARRAY_BUFFER, 9 * sizeof (GLfloat), colors, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
    // note que agora o atributo 1 está definido
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(1); // habilitado segundo atributo do vbo bound atual
		
	/* here we copy the shader strings into GL shaders, and compile them. we then
	create an executable shader 'program' and attach both of the compiled shaders.
	we link this, which matches the outputs of the vertex shader to the inputs of
	the fragment shader, etc. and it is then ready to use */

	glClearColor(0.6f, 0.6f, 0.8f, 1.0f);
	
	/* this loop clears the drawing surface, then draws the geometry described by
	the VAO onto the drawing surface. we 'poll events' to see if the window was
	closed, etc. finally, we 'swap the buffers' which displays our drawing surface
	onto the view area. we use a double-buffering system which means that we have
	a 'currently displayed' surface, and 'currently being drawn' surface. hence
	the 'swap' idea. in a single-buffering system we would see stuff being drawn
	one-after-the-other */
	
	float speed = 1.0f;
	float lastPosition = 0.0f;
	ourShader.use();
	while (!glfwWindowShouldClose (window)) {
	
		static double previousSeconds = glfwGetTime();
		double currentSeconds = glfwGetTime();
		double elapsedSeconds = currentSeconds - previousSeconds;
		if(elapsedSeconds > 0) {
			previousSeconds = currentSeconds;
			if(fabs(lastPosition) > 1.0f){
				speed = -speed;
			}
			matrix[3][0] = elapsedSeconds * speed + lastPosition;
			lastPosition = matrix[3][0];
		}
		
        ourShader.setMat4("matrix",matrix);
	
		/* wipe the drawing surface clear */
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//		glUseProgram (shader_programme);
		
		glBindVertexArray (vao);
		/* draw points 0-3 from the currently bound VAO with current in-use shader*/
		glDrawArrays (GL_TRIANGLES, 0, 3);

		/* update other events like input handling */
		glfwPollEvents ();
		/* put the stuff we've been drawing onto the display */
		glfwSwapBuffers (window);
		if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE)){
			glfwSetWindowShouldClose(window, 1);
		}
	}
	
	/* close GL context and any other GLFW resources */
	glfwTerminate();
	return 0;
}