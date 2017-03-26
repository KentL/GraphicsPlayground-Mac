#version 150

uniform sampler2D texture0;
in vec2 v_uv1;
out vec4 PixelColor;

void main()
{
    PixelColor = texture(texture0,v_uv1);
	if(PixelColor.a<0.1)
		discard;
}


