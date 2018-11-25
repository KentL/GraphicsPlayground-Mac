#version 150
out vec4 PixelColor;
in vec3 Normal;
in vec3 Position;

uniform vec3 cameraPos;
uniform samplerCube envMap;

void main()
{           
    float ratio = 1.00 / 1.52;
    vec3 I = normalize(Position - cameraPos);
    vec3 R = refract(I, normalize(Normal), ratio);
    PixelColor = vec4(texture(envMap, R).rgb, 1.0);
}
