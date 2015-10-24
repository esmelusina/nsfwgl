#pragma once

#include <Application.h>

#include "ForwardPass.h"
#include "PostPass.h"
#include "GameObject.h"
#include "Camera.h"

class PostProcessApp : public nsfw::Application
{
public:
	ForwardPass fPass;
	PostPass	pPass;

	Camera		camera;
	GameObject	object;

	void onStep();
	void onInit();
	void onPlay();
	void onTerm();
};