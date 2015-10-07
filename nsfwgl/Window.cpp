#include "nsfw.h"

void nsfw::Window::init(unsigned width, unsigned height)
{
	TODO_D("Should create and set an active windowing context. ONLY GLFW! No GL!");
}

void nsfw::Window::step()
{
	TODO_D("GLFW poll events and swap buffers is all that should really be here! No GL!");
}

void nsfw::Window::term()
{
	TODO();
}

float nsfw::Window::getTime() const
{
	TODO();
	return 0.0f;
}

bool nsfw::Window::getKey(unsigned k) const
{
	TODO();
	return false;
}

bool nsfw::Window::getShouldClose() const
{
	TODO();
	return true;
}

unsigned nsfw::Window::getWidth() const
{
	TODO();
	return 0;
}

unsigned nsfw::Window::getHeight() const
{
	TODO();
	return 0;
}

glm::mat4 nsfw::Window::getTexelAdjustmentMatrix() const
{
	TODO_D("Implemented, not tested.");

	glm::vec3 texelSize = 1.0f/glm::vec3(width,height,0);
	glm::vec3 halfTexel = texelSize * 0.5f; // bottom left

	// scale up to the appropriate size, then shift it to line up w/center of texels
	return glm::translate(halfTexel) * glm::scale(glm::vec3(1, 1, 1) - texelSize);	
}