#pragma once

#include <glm\glm.hpp>
#include "../nsfwgl/Assets.h"

using namespace nsfw::ASSET;

struct Geometry
{
	glm::mat4 transform;

	nsfw::Asset<VAO> mesh;
	nsfw::Asset<SIZE> tris;

	nsfw::Asset<TEXTURE> diffuse;
	nsfw::Asset<TEXTURE> normal;
	nsfw::Asset<TEXTURE> specular;

	float specPower;

	void update() {}
};