#version 410
layout(location = 0) in vec4 Position;
layout(location = 1) in vec4 Normal;
layout(location = 2) in vec4 Tangent;
layout(location = 3) in vec2 TexCoord;

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;


out vec2 vTexCoord;
out vec4 vNormal;
out mat4 vTBN;

void main()
{
	vec4 BiNormal = vec4(cross(Normal.xyz, Tangent.xyz),0);

	vTBN = mat4(Tangent, BiNormal, Normal, vec4(0,0,0,0));
	vNormal     = Projection * View * Model * Normal;
	vTexCoord   = TexCoord;

	gl_Position = Projection * View * Model * Position;
}