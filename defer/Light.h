#pragma once
#include <glm/glm.hpp>

struct LightD
{
	glm::vec3 color;
	glm::vec3 direction;
	void update() {}
};

struct LightP
{
	glm::vec3 color;
	glm::vec3 position;
	float attenuation;
};