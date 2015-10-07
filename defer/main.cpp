
#include "DefApp.h"

#include "Geometry.h"
#include "Light.h"
#include "Camera.h"

using namespace nsfw;

int main()
{
	DeferredApplication d;

	d.init();
	d.play();
	d.term();

	system("pause");
}


void DeferredApplication::onInit()
{
	auto &w = nsfw::Window::instance();
	auto &a = nsfw::Assets::instance();

	// Setup FBOs
	const char *gpassTextureNames[] = { "GPassAlbedo","GPassPosition","GPassNormal","GPassDepth" };
	const unsigned gpassDepths[] = { 0,0,0,0 }; // GL_RGB8, GL_RGB32, GL_RGB32, GL_DEPTH_COMPONENT
	a.makeFBO("GeometryPass", w.getWidth(), w.getHeight(), 4, gpassTextureNames, gpassDepths);

	const char *lpassTextureNames[] = { "LPassColor" };
	const unsigned lpassDepths[] = { 0 }; // GL_RGB8
	a.makeFBO("LightPass", w.getWidth(), w.getHeight(), 1, lpassTextureNames, lpassDepths); //

	// Load Shaders
	a.loadShader("GeometryPassPhong", "/path/to/gpass/Phong/vertex", "/path/to/gpass/Phong/fragment");
	a.loadShader("LightPassDirectional", "/path/to/lpass/Directional/vertex", "/path/to/lpass/Directional/fragment");
	//a.loadShader("LightPassPoint", "/path/to/lpass/Point/vertex", "/path/to/lpass/Point/fragment");
	a.loadShader("CompPass", "/path/to/cpass/vertex", "/path/to/cpass/fragment");

	// Load any other textures and geometry we want to use
	a.loadFBX("Soulspear", "/path/to/souuuulspppeeeeaaar");
}

void DeferredApplication::onPlay()
{
	m_camera = new Camera;
	m_light = new LightD;
	m_soulspear = new Geometry;

	m_camera->lookAt(glm::vec3(10), glm::vec3(0), glm::vec3(0,1,0));

	m_light->color = glm::vec3(1, 1, 1);
	m_light->direction = glm::normalize(glm::vec3(1, 1, 0));

	m_soulspear->mesh	   = "Soulspear";
	m_soulspear->tris	   = "Soulspear";
	m_soulspear->diffuse   = "Soulspear";
	m_soulspear->normal    = "Soulspear";
	m_soulspear->specular  = "Soulspear";
	m_soulspear->specPower = 40.0f;
	m_soulspear->transform = mat4(1);

	TODO_D("Initialize all of our renderpasses!");
}

void DeferredApplication::onStep()
{
	m_light->update();
	m_camera->update();
	m_soulspear->update();
	TODO_D("Draw all of our renderpasses!");
}

void DeferredApplication::onTerm()
{
	delete m_camera;
	delete m_light;
	delete m_soulspear;
}