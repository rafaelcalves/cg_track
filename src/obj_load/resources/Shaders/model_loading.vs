#version 330 core
layout ( location = 0 ) in vec3 vPosition;
layout ( location = 1 ) in vec3 vColors;

uniform mat4 view, projection, model;
out vec3 color;

void main()
{
	color = vColors;
	gl_Position = projection * view * model * vec4(vPosition, 1.0);
}