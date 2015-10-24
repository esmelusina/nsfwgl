#version 410
out vec4 FragColor;
in vec4 vNormal;
in vec2 vTexCoord;

uniform sampler2D Diffuse;

void main()
{
	vec4 aColor = vec4(.3f,.3f,.3f,1);			// ambient color (light)

	vec4 lColor = vec4(0.8f,0.4f,0.6f,1);		// direcitonal light color
	vec4 lNormal = normalize(vec4(1,-1,1,0));	// directional light normal
	
	vec4 oColor = texture(Diffuse, vTexCoord);	// surface color


	float lamb = max(0,dot(-lNormal, vNormal));
	
	FragColor = oColor * lamb * lColor + aColor * oColor;
	
	FragColor = oColor;
	FragColor.a = 1;
}