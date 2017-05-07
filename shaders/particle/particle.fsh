

#version 150

uniform sampler2D texture1;

in vec2 v_uv1;
in vec4 v_color;
out vec4 PixelColor;

void main()
{
	vec4 tex_color=texture(texture1,v_uv1);
	if(tex_color.a<0.1)
	{
		discard;
	}
	else
	{
		PixelColor = v_color * tex_color;
		
	}
    
}


