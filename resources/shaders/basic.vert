#version 410
layout(location = 0) in vec4 Position;
layout(location = 3) in vec2 TexCoord;
uniform mat4 offset;

out vec2 vTexCoord;

void main()
{
	vTexCoord 	= TexCoord;
	gl_Position = Position;
}