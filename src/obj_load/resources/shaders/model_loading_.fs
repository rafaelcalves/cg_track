#version 410 core

in vec2 texCoord;
in vec3 positionEye, normalEye;

out vec4 color;

uniform sampler2D textureId;
uniform float colorPercentage, ambientIntensity, lightIntensity, shininess;
uniform vec3 camera, ambient, diffuse, specular;

void main(){
	vec3 ambientLight = ambientIntensity * ambient;

	float distanceToLight = length(camera - positionEye);
	vec3 lightDirection = normalize(camera - positionEye);
	float diffuseIntensity = max(dot(lightDirection, normalEye), 0.0f);
	vec3 diffuseLight = lightIntensity * diffuse * diffuseIntensity;

	float attenuation = 1 / pow(distanceToLight, 2);

	vec3 viewNormalized = normalize(-positionEye);
	vec3 reflectionEye = reflect(-lightDirection, normalize(normalEye));
	float dotProductSpecular = max(dot(reflectionEye, viewNormalized), 0.0f);
	float specularFactor = pow(dotProductSpecular, shininess);

	float specularLight = specular * specularFactor;

	float light = ambientLight + attenuation * (diffuseLight + specularLight);

    vec4 tex = texture( textureId, texCoord );
    color = light * mix(tex, vec4(0.0f, 0.0f, 1.0f, 0.0f), colorPercentage);
}