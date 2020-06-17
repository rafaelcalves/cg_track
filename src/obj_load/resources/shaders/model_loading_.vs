#version 410 core
layout ( location = 0 ) in vec3 vertex;
layout ( location = 1 ) in vec2 texture;
layout ( location = 2 ) in vec3 normal;

uniform mat4 view, projection, model;
out vec2 texCoord;
out vec3 positionEye, normalEye;

void main()
{
	texCoord = texture;
	positionEye = vec3(view * model * vec4(vertex, 1.0));
	normalEye = vec3(view * model * vec4(normal, 0.0));
	gl_Position = projection * positionEye;
}