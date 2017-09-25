#version 150
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform vec4 ClipPlane;
in vec4 a_position;
in vec2 a_uv1;
out vec2 v_uv1;

uniform float time;

void main()
{
	gl_Position = projection * view * model * a_position;
    v_uv1=a_uv1;
}
