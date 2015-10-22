#include <ogl\gl_core_4_4.h>
#include <glfw\glfw3.h>

#include "nsfw.h"

void nsfw::Window::init(unsigned width, unsigned height, const char *title)
{
	glfwInit();
	window = glfwCreateWindow(width,height, title, nullptr, nullptr);
	glfwMakeContextCurrent(window);
	ogl_LoadFunctions();
}

void nsfw::Window::term()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

void nsfw::Window::step()
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}

float nsfw::Window::getTime()		  const { return glfwGetTime(); }
bool nsfw::Window::getKey(unsigned k) const { return glfwGetKey(window, k); }

bool nsfw::Window::getShouldClose() const
{
	return glfwWindowShouldClose(window) == true ||
	 glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS;
}

unsigned nsfw::Window::getWidth()  const { return width; }
unsigned nsfw::Window::getHeight() const { return height; }

glm::mat4 nsfw::Window::getTexelAdjustmentMatrix() const
{
	TODO_D("Implemented, not tested.");

	glm::vec3 texelSize = 1.0f/glm::vec3(width,height,0);
	glm::vec3 halfTexel = texelSize * 0.5f; // bottom left

	// scale up to the appropriate size, then shift it to line up w/center of texels
	return glm::translate(halfTexel) * glm::scale(glm::vec3(1, 1, 1) - texelSize);	
}