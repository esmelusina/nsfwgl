#pragma once
#include "nsfw.h"

namespace nsfw
{

	class Application
	{
	public:
		virtual void onInit() { TODO_D("OVERRIDE: Load everything here!"); };
		virtual void onTerm() { TODO_D("OVERRIDE: Free your data!"); };
		virtual void onPlay() { TODO_D("OVERRIDE: Create game and renderpass objects here!"); };
		virtual void onStep() { TODO_D("OVERRIDE: Render Passes should draw, objects should update!"); };

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