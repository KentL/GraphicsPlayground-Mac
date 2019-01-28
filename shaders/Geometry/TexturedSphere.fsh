#version 150
out vec4 PixelColor;
in vec4 texCoords;
uniform sampler2D tex;

void main()
{
 vec2 longitudeLatitude = vec2((atan(texCoords.y, texCoords.x) / 3.1415926 + 1.0) * 0.5,(asin(texCoords.z) / 3.1415926 + 0.5));
    PixelColor = texture(tex, longitudeLatitude);;
}


