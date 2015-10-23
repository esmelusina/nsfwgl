#version 410
layout(location = 0) in vec4 Position;
layout(location = 3) in vec2 TexCoord;

out vec2 vTexCoord;

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;

void main()
{
	vTexCoord = TexCoord;
	gl_Position = Projection * 
						View *
					   Model * Position;
}