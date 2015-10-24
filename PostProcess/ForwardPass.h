#pragma once
#include <ogl\gl_core_4_4.h>
#include <nsfw.h>
#include <glm\glm.hpp>
#include <glm\ext.hpp>

#include "Camera.h"
#include "GameObject.h"

class ForwardPass : public nsfw::RenderPass
{
public:
	void prep()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, *fbo);
		glUseProgram(*shader);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);

		glViewport(0, 0, 800, 600); // Use window dimensions probably
		glClearColor(0.25f, 0.25f, 0.25f, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void post() { glDisable(GL_CULL_FACE); glDisable(GL_DEPTH_TEST); glBindFramebuffer(GL_FRAMEBUFFER, 0); glUseProgram(0); }

	void draw(const Camera &c, const GameObject &go)
	{
		//Camera
		setUniform("Projection", nsfw::UNIFORM::MAT4, glm::value_ptr(c.getProjection()));
		setUniform("View", nsfw::UNIFORM::MAT4, glm::value_ptr(c.getView()));
		////GameObject
		setUniform("Model", nsfw::UNIFORM::MAT4, glm::value_ptr(go.transform));
		setUniform("Diffuse",  nsfw::UNIFORM::TEX2, &(go.diffuse),0);
		setUniform("Specular", nsfw::UNIFORM::TEX2, &(go.diffuse),1);
		setUniform("Normal",   nsfw::UNIFORM::TEX2, &(go.diffuse),2);

		glBindVertexArray(*go.mesh);
		glDrawElements(GL_TRIANGLES, *go.tris, GL_UNSIGNED_INT, 0);
	}
};