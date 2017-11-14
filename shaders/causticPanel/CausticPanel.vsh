#version 150
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat3 modelIT;
uniform vec4 ClipPlane;


in vec3 a_tangent;
in vec3 a_normal;
in vec4 a_position;
in vec2 a_uv1;

out vec2 normal_uv1;
out vec2 normal_uv2;
out vec3 v_normal;
out vec3 v_tangent;
uniform float time;

void main()
{
	gl_Position = projection * view * model * a_position;
    normal_uv1=a_uv1 + time;
    normal_uv2=a_uv1 + time / 2.0;
    v_normal = modelIT * a_normal;
    vec4 t = model * vec4(a_tangent.xyz,1.0);
    v_tangent = t.xyz;

}
