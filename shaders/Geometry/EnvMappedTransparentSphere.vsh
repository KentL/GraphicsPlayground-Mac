#version 150
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
in vec4 a_position;

out vec3 Normal;
out vec3 Position;

void main()
{
	gl_Position = projection * view * model * a_position;
	Normal = mat3(transpose(inverse(model))) * a_position.xyz;
	Position = vec3(model * a_position);
}
