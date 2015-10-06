#pragma once
/****************
GLFW Wrapper with BASIC interface.

Extend functionality as you see fit.

This class should ONLY use GLFW!

No OpenGL!!!
*****************/


namespace nsfw
{
	class Window
	{
		class GLFWWindow *window;
		unsigned width, height;		// keep track of width height- needed for glViewport FBO integration

		Window() {}
	public:
		static Window &instance() { static Window w; return w; }
		
		//create the context!
		void init(unsigned width, unsigned height);
		
		// swapBuffers and pollEvents!
		void step();

		// kill the context!
		void term();

		// just wrap what GLFW already does
		float	 getTime();
		bool	 getKey(unsigned k);
		bool	 getShouldClose();
		unsigned getWidth();
		unsigned getHeight();
	};
}