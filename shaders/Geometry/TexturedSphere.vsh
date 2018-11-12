#version 150
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
in vec4 a_position;
out vec4 texCoords;

void main()
{
	gl_Position = projection * view * model * a_position;
	texCoords = a_position;
}
