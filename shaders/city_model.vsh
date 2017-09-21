#version 150

// Scene info
uniform mat4 WorldViewProj;
uniform mat4 View;
uniform vec4 ClipPanel;
// Attributes
in vec4 a_position;
in vec3 a_normal;
in vec2 a_uv1;

// Varyings
out vec3 v_normal;
out vec2 v_uv1;
out float gl_ClipDistance[1];

void main()
{
    gl_Position = WorldViewProj * a_position;

    // Output
    gl_ClipDistance[0] = dot( a_position,ClipPanel);
    v_normal = a_normal;
	v_uv1 = a_uv1;
}
