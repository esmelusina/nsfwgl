#pragma once
#include <nsfw.h>
#include <glm\glm.hpp>

struct Camera
{
	glm::mat4 m_transform;
	float m_near, m_far, m_aspect, m_fov;

	Camera() : m_near(1), m_far(100), m_aspect(800/600.0f), m_fov(90) {}

	void update() {}

	void lookAt(glm::vec3 pos, glm::vec3 target, glm::vec3 up)
	{
		m_transform = glm::inverse(glm::lookAt(pos, target, up));
	}
	
	glm::mat4 getView()		  const { return glm::inverse(m_transform); }
	glm::mat4 getProjection() const { return glm::perspective(m_fov, m_aspect, m_near, m_far); }
};