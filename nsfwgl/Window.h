#pragma once
/****************
GLFW Wrapper with BASIC interface.

Extend functionality as you see fit.

This class should ONLY use GLFW!

No OpenGL!!!
*****************/

#include <glm/glm.hpp>

namespace nsfw
{
	class Window
	{
		class GLFWWindow *window;
		unsigned width, height;		// keep track of width height- needed for glViewport FBO integration

		Window():window(nullptr),width(0),height(0) {}
	public:
		static Window &instance() { static Window w; return w; }
		
		//create the context!
		void init(unsigned width, unsigned height);
		
		// swapBuffers and pollEvents!
		void step();

		// kill the context!
		void term();

		// just wrap what GLFW already does
		float	  getTime()                  const;
		bool	  getKey(unsigned k)         const;
		bool	  getShouldClose()           const;
		unsigned  getWidth()                 const;
		unsigned  getHeight()                const;
		glm::mat4 getTexelAdjustmentMatrix() const;
	};
}