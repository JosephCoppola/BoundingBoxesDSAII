#version 330

in vec3 Position_b;

uniform mat4 MVP;

void main()
{
	gl_Position = MVP * vec4(Position_b, 1);
}