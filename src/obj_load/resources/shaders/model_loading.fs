#version 410 core

in vec2 texCoord;
in vec3 positionEye, normalEye;

out vec4 color;
uniform sampler2D textureId;
uniform float ambientIntensity, colorPercentage, lightIntensity;
uniform vec3 camera, ambient, diffuse;

void main(){
    vec3 ambientLight = ambientIntensity * ambient;

    vec3 lightDirection = normalize(camera - positionEye);
    float diffuseIntensity = max(dot(lightDirection, normalEye), 0.0f);
    vec3 diffuseLight = lightIntensity * diffuse * diffuseIntensity;

    float distanceToLight = length(camera - positionEye);
    float attenuation = 1.0f / pow(distanceToLight, 2);

    vec3 light = ambientLight + attenuation*diffuseLight;

    vec4 tex = texture( textureId, texCoord );
    color = vec4(light, 1.0f) * tex;
}