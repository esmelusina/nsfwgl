#pragma once

#include "../nsfwgl/nsfw.h"

struct Camera;
struct Geometry;
struct LightD;

class GPass;
class LPassD;
class CPass;

class DeferredApplication : public nsfw::Application
{
	Camera   *m_camera;
	Geometry *m_soulspear;
	LightD	 *m_light;

public:
	void onInit();
	void onStep();
	void onTerm();
	void onPlay();
};