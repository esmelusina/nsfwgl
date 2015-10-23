#pragma once

#include "ForwardPass.h"
#include "Camera.h"
#include "GameObject.h"

#include <nsfw.h>


class TestApp : public nsfw::Application
{
	Camera		camera;
	GameObject	obj;
	ForwardPass fp;
public:
	void onStep();
	void onPlay();
	void onInit();
	void onTerm();
};