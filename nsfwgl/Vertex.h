#pragma once

#include <glm\ext.hpp>
using namespace glm;

namespace nsfw
{
	struct Vertex
	{
		glm::vec4 position;
		glm::vec4 normal;
		glm::vec4 tangent;
		glm::vec2 texCoord;
	};

	const vec4 up(0, 1, 0, 0);
	const vec4 down = -up;
	const vec4 right(1, 0, 0, 0);
	const vec4 left = -right;
	const vec4 forward(0, 0, 1, 0);
	const vec4 backward = -forward;

	const Vertex CubeVerts[] =
		// Bottom
	{   { vec4(-1,-1, 1, 1), down, right, vec2(0,1) },
	    { vec4(1,-1, 1, 1), down, right, vec2(1,1) },
	    { vec4(1,-1,-1, 1), down, right, vec2(1,0) },
	    { vec4(-1,-1,-1, 1), down, right, vec2(0,0) },
		// Top
	    { vec4(-1, 1, 1, 1), up, right, vec2(0,1) },
	    { vec4(1, 1, 1, 1), up, right, vec2(1,1) },
	    { vec4(1, 1,-1, 1), up, right, vec2(1,0) },
	    { vec4(-1, 1,-1, 1), up, right, vec2(0,0) },
		// back
	    { vec4(-1, 1, -1, 1), backward, left, vec2(0,1) },
	    { vec4(1, 1, -1, 1), backward, left, vec2(1,1) },
	    { vec4(1, -1,-1, 1), backward, left, vec2(1,0) },
	    { vec4(-1, -1,-1, 1), backward, left, vec2(0,0) },
		// front
		{ vec4(-1, 1, 1, 1), forward, right, vec2(0,1) },
		{ vec4(1, 1, 1, 1), forward,  right, vec2(1,1) },
		{ vec4(1, -1,1, 1), forward,  right, vec2(1,0) },
		{ vec4(-1, -1,1, 1), forward, right, vec2(0,0) },
		// left
		{ vec4(-1, 1,-1, 1), left, forward, vec2(1,0) },
		{ vec4(-1, 1, 1, 1), left, forward, vec2(1,1) },
		{ vec4(-1,-1, 1, 1), left, forward, vec2(0,1) },
		{ vec4(-1,-1,-1, 1), left, forward, vec2(0,0) },
		// right
		{ vec4(1, 1,-1, 1), right, backward, vec2(1,0) },
		{ vec4(1, 1, 1, 1), right, backward, vec2(1,1) },
		{ vec4(1,-1, 1, 1), right, backward, vec2(0,1) },
		{ vec4(1,-1,-1, 1), right, backward, vec2(0,0) },
	};

	const unsigned CubeTris[] = {
		3,2,0,0,2,1,
		7,4,6,6,4,5,
		11,8,10,10,8,9,
		15, 14, 12, 12, 14, 13,
		19,18,16,16,18,17,
		23,20,22,22,20,21 };


	const Vertex QuadVerts[] =
	{
		{ vec4(-1, 1, 0, 1), backward,  left, vec2(0,1) },
		{ vec4( 1, 1, 0, 1), backward,  left, vec2(1,1) },
		{ vec4( 1,-1, 0, 1), backward,  left, vec2(1,0) },
		{ vec4(-1,-1, 0, 1), backward,  left, vec2(0,0) },
	};

	const unsigned QuadTris[] = { 3,1,0, 3,2,1 };

}