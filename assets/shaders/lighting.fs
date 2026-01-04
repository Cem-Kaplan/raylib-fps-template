#version 330

in vec3 fragPos;
in vec3 normal;

out vec4 finalColor;

uniform vec3 lightDir;
uniform vec3 lightColor;
uniform vec3 viewPos;

void main() {
    vec3 norm = normalize(normal);
    vec3 light = normalize(-lightDir);

    float diff = max(dot(norm, light), 0.0);

    vec3 diffuse = diff * lightColor;
    vec3 ambient = 0.25 * lightColor;

    vec3 color = ambient + diffuse;
    finalColor = vec4(color, 1.0);
}
