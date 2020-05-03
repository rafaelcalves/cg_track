#version 410
layout(location=0) in vec3 vertice;
layout (location = 1) in vec3 normal;
void main () {
	gl_Position = vec4 (vertice, 1.0);
}