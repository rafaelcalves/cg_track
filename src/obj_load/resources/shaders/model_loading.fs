#version 410 core

in vec2 texCoord;
in vec3 positionEye, normalEye;

out vec4 color;
uniform sampler2D textureId;
uniform float ambientIntensity, diffuseIntensity, exponent, fogMaxDistance, fogMinDistance;
uniform vec3 camera, ambientK, diffuseK, specularK;
uniform vec4 fogColor;

vec3 getAmbientLight();
vec3 getDiffuseLight(vec3 lightDirection);
vec3 getSpecularLight(vec3 lightDirection);
float getLightAttenuation(float distanceToLight);
vec3 calculateLight(float distanceToLight);
float getFogFactor(float distanceToLight);

void main(){
    float distanceToLight = distance(camera, positionEye);
    float fogFactor = getFogFactor(distanceToLight);
    vec3 light = calculateLight(distanceToLight);

    vec4 tex = texture( textureId, texCoord );
    color = mix(mix(vec4(light, .7f),tex,.9f),fogColor,1-fogFactor);
}

vec3 getAmbientLight(){
    return ambientIntensity * ambientK;
}

vec3 getDiffuseLight(vec3 lightDirection){
    float diffuseFactor = max(dot(lightDirection, normalEye), 0.0f);
    return diffuseIntensity * diffuseK * diffuseFactor;
}

vec3 getSpecularLight(vec3 lightDirection){
    vec3 viewNormalized = normalize(positionEye);
    vec3 reflectionEye = reflect(-lightDirection, normalEye);
    float dotProductSpecular = max(dot(reflectionEye, viewNormalized), 0.0f);
    float specularFactor = dotProductSpecular * exponent;
    return specularK * specularFactor;
}

float getLightAttenuation(float distanceToLight){
    return 1.0f / pow(distanceToLight, 2);
}

vec3 calculateLight(float distanceToLight){
    vec3 lightDirection = normalize(camera - positionEye);

    vec3 ambientLight = getAmbientLight();
    vec3 diffuseLight = getDiffuseLight(lightDirection);
	vec3 specularLight = getSpecularLight(lightDirection);

    float attenuation = getLightAttenuation(distanceToLight);
    return ambientLight + attenuation*(specularLight + diffuseLight);
}

float getFogFactor(float distanceToLight){
    float fogFactor = (fogMaxDistance - distanceToLight) / (fogMaxDistance - fogMinDistance);
    return clamp(fogFactor, 0.0, 1.0);
}
