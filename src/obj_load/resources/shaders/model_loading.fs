#version 410 core

in vec2 texCoord;
in vec3 positionEye, normalEye;

out vec4 color;
uniform sampler2D textureId;
uniform float ambientIntensity, colorPercentage, lightIntensity, exponent;
uniform vec3 camera, ambient, diffuse, specular;

void main(){
    vec3 ambientLight = ambientIntensity * ambient;

    vec3 lightDirection = normalize(camera - positionEye);
    float diffuseIntensity = max(dot(lightDirection, normalEye), 0.0f);
    vec3 diffuseLight = lightIntensity * diffuse * diffuseIntensity;

    vec3 viewNormalized = normalize(positionEye);
    vec3 reflectionEye = reflect(-lightDirection, normalEye);
    float dotProductSpecular = max(dot(reflectionEye, viewNormalized), 0.0f);
    float specularFactor = dotProductSpecular * exponent;
	vec3 specularLight = specular * specularFactor;

    float distanceToLight = length(camera - positionEye);
    float attenuation = 1.0f / pow(distanceToLight, 2);

    vec3 light = ambientLight + attenuation*(specularLight + diffuseLight);

    vec4 tex = texture( textureId, texCoord );
    color = vec4(light, 1.0f) * tex;
}