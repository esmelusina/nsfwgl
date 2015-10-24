#pragma once
#include <ogl\gl_core_4_4.h>
#include <nsfw.h>
#include <glm\glm.hpp>
#include <glm\ext.hpp>

class PostPass : public nsfw::RenderPass
{
public:
	void prep()
	{
		glUseProgram(*shader);
	}
	void post() { glUseProgram(0); }

	void draw()
	{
		nsfw::Asset<nsfw::ASSET::TEXTURE> fin = "ForwardFinal";
		nsfw::Asset<nsfw::ASSET::TEXTURE> din = "ForwardDepth";
		
		nsfw::Asset<nsfw::ASSET::VAO> qm = "Quad";
		nsfw::Asset<nsfw::ASSET::SIZE> qt = "Quad";
		
		setUniform("Final", nsfw::UNIFORM::TEX2, &fin, 0);
		setUniform("Depth", nsfw::UNIFORM::TEX2, &din, 1);

		glBindVertexArray(*qm);
		glDrawElements(GL_TRIANGLES, *qt, GL_UNSIGNED_INT, 0);
	}
};