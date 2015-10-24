#version 410
layout(location = 0) in vec4 Position;
layout(location = 1) in vec4 Normal;
layout(location = 3) in vec2 TexCoord;


uniform mat4 Projection;
uniform mat4 Model;
uniform mat4 View;

out vec2 vTexCoord;
out vec4 vNormal;

void main()
{	
	vNormal 	= Projection * View * Model * Normal;
	vTexCoord 	= TexCoord;
	gl_Position = Projection * View * Model * Position;
}