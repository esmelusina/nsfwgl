#include "PostProcessApp.h"
#include <glm\ext.hpp>

void PostProcessApp::onStep()
{
	object.transform = glm::rotate(nsfw::Window::instance().getTime() * 10, glm::vec3(0, 1, 0));

	fPass.prep();
	fPass.draw(camera, object);
	fPass.post();

	pPass.prep();
	pPass.draw();
	pPass.post();
}

void PostProcessApp::onInit()
{
	auto &a = nsfw::Assets::instance();

	a.loadFBX("", "../resources/fbx/soulspear/soulspear.fbx");
	a.loadShader("Forward", "../resources/shaders/forward.vert", "../resources/shaders/forward.frag");
	a.loadShader("Post",	"../resources/shaders/post.vert",	 "../resources/shaders/post.frag");

	const char   *names[] = {"ForwardFinal", "ForwardDepth"};
	const unsigned deps[] = {GL_RGBA, GL_DEPTH_COMPONENT};
	a.makeFBO("Forward",800,600,2,names,deps);
}

void PostProcessApp::onPlay()
{
	camera.lookAt(glm::vec3(2, 2, 2), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	object.diffuse	= "soulspear_diffuse.tga";
	object.normal	= "soulspear_normal.tga";
	object.specular = "soulspear_specular.tga";
	object.mesh		= "SoulSpear_Low:SoulSpear_Low1";
	object.tris		= "SoulSpear_Low:SoulSpear_Low1";

	fPass.fbo	 = "Forward";
	fPass.shader = "Forward";

	pPass.shader = "Post";
}

void PostProcessApp::onTerm()
{
}