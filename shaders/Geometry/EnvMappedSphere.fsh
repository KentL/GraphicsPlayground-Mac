#version 150
out vec4 PixelColor;
in vec3 Normal;
in vec3 Position;

uniform vec3 cameraPos;
uniform samplerCube envMap;

void main()
{             
    vec3 I = normalize(Position - cameraPos);
    vec3 R = reflect(I, normalize(Normal));
    PixelColor = vec4(texture(envMap, R).rgb, 1.0);
}
