#pragma once
#include "nsfw.h"

namespace nsfw
{

	class Application
	{
	public:
		virtual void onInit() {};
		virtual void onTerm() {};
		virtual void onPlay() {};
		virtual void onStep() {};

		void init(int width = 800, int height = 600, const char *name = "Not Suited For Work")
				{ Window::instance().init(width, height); onInit(); }

		void term()
				{ onTerm(); Assets::instance().term(); Window::instance().term(); }

		void play()
		{
			onPlay();
			while (!Window::instance().getShouldClose())
				step();
		}

		void step()
		{
			Window::instance().step();
			onStep();
		}
	};
}