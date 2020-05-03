#version 410 core

in vec2 texCoord;
out vec4 color;
uniform sampler2D diffuse;

void main(){
    vec4 tex = texture( diffuse, texCoord );
    color = tex;
}