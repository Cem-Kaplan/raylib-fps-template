#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec3 fragPosition;
in vec3 fragNormal;

// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;

// Lighting uniforms
uniform vec3 lightDir;
uniform vec3 lightColor;
uniform vec3 viewPos;

// Output fragment color
out vec4 finalColor;

void main() {
    // Texel color fetching from texture sampler
    vec4 texelColor = texture(texture0, fragTexCoord);
    vec3 lightDot = vec3(0.0);
    vec3 normal = normalize(fragNormal);
    vec3 viewD = normalize(viewPos - fragPosition);
    vec3 specular = vec3(0.0);

    // Diffuse lighting
    vec3 lightDirNorm = normalize(lightDir);
    float NdotL = max(dot(normal, -lightDirNorm), 0.0);
    lightDot += lightColor * NdotL;

    // Specular lighting (basic)
    vec3 reflectDir = reflect(lightDirNorm, normal);
    specular += lightColor * pow(max(dot(viewD, reflectDir), 0.0), 16.0) * 0.5;

    // Combine lighting with texture color
    finalColor = (texelColor * ((colDiffuse + vec4(lightDot, 1.0)) + vec4(specular, 1.0)));
    finalColor.a = colDiffuse.a * texelColor.a;
}
