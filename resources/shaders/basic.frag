#version 410

out vec4 FragColor;
in mat4 vTBN;
in vec4 vNormal;
in vec2 vTexCoord;

uniform sampler2D Diffuse;

void main()
{

	vec4 diffuseColor = texture(Diffuse, vTexCoord);
	vec4 lightColor   = vec4(0.8f, 0.2f, 0.4f, 1);
	vec4 lNormal	  = normalize(vec4(1,-1,1,0));

	float lamb = max(0,dot(-lNormal, vNormal));

	

	FragColor = diffuseColor * lamb * lightColor;
	FragColor.a = 1;
}