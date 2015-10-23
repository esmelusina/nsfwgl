#pragma once
#include <ogl\gl_core_4_4.h>
#include <nsfw.h>
#include <glm\glm.hpp>

#include "Camera.h"
#include "GameObject.h"

class ForwardPass : public nsfw::RenderPass
{
public:
	void prep()
	{
		glClearColor(0.25f, 0.25f, 0.25f, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(*shader);
	}
	void post() { glUseProgram(0); }

	void draw(const Camera &c, const GameObject &go)
	{
		//Camera
		setUniform("Projection", nsfw::UNIFORM::MAT4, glm::value_ptr(c.getProjection()));
		setUniform("View",	     nsfw::UNIFORM::MAT4, glm::value_ptr(c.getView()));
		//GameObject
		setUniform("Model",		 nsfw::UNIFORM::MAT4, glm::value_ptr(go.transform));
		setUniform("Diffuse",	 nsfw::UNIFORM::TEX2, &(go.diffuse));

		glBindVertexArray(*go.mesh);
		glDrawElements(GL_TRIANGLES, *go.tris, GL_UNSIGNED_INT, 0);
	}
};