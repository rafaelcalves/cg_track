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

    float distanceToLight = distance(camera, positionEye);
    float attenuation = 1.0f / pow(distanceToLight, 2);

    // Fog parameters, could make them uniforms and pass them into the fragment shader
    float fog_maxdist = 100.0;
    float fog_mindist = 0.1;
    vec4  fog_colour = vec4(0.0f, 0.3f, 0.6f, 1.0f);

    // Calculate fog
    float fog_factor = (fog_maxdist - distanceToLight) / (fog_maxdist - fog_mindist);
    fog_factor = clamp(fog_factor, 0.0, 1.0);

    vec3 light = ambientLight + attenuation*(specularLight + diffuseLight);

    vec4 tex = texture( textureId, texCoord );
    color = mix(mix(vec4(light, .7f),tex,.9f),fog_colour,1-fog_factor);
}