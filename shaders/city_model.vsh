#version 150

// Scene info
uniform mat4 WorldViewProj;

// Attributes
in vec4 a_position;
in vec3 a_normal;
in vec2 a_uv1;

// Varyings
out vec3 v_normal;
out vec2 v_uv1;

void main()
{
    gl_Position = WorldViewProj * a_position;


	// Output
    v_normal = a_normal;
	v_uv1 = a_uv1;
}
