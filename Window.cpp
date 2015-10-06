#include "nsfw.h"

void nsfw::Window::init(unsigned width, unsigned height)
{
	TODO_D("Should create and set active a windowing context. ONLY GLFW! No GL!");
}

void nsfw::Window::step()
{
	TODO_D("GLFW poll events and swap buffers is all that should really be here! No GL!");
}

void nsfw::Window::term()
{
	TODO();

}

float nsfw::Window::getTime()
{
	TODO();
	return 0.0f;
}

bool nsfw::Window::getKey(unsigned k)
{
	TODO();
	return false;
}

bool nsfw::Window::getShouldClose()
{
	TODO();
	return false;
}

unsigned nsfw::Window::getWidth()
{
	TODO();
	return 0;
}

unsigned nsfw::Window::getHeight()
{
	TODO();
	return 0;
}
