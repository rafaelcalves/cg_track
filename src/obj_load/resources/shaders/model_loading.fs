#version 410 core

in vec2 texCoord;
out vec4 color;
uniform sampler2D textureId;

void main(){
    vec4 tex = texture( textureId, texCoord );
    color = tex;
}