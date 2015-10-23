#include "TestApp.h"

void TestApp::onStep()
{
	obj.transform = glm::rotate(nsfw::Window::instance().getTime()*10.f, glm::vec3(0, 1, 0));
	fp.prep();
	fp.draw(camera, obj);
	fp.post();
}

void TestApp::onPlay()
{
	//camera.lookAt(glm::vec3(10,10,10), // offset to the top,right,forward
	//			  glm::vec3(0,0,0),  // origin
	//			  glm::vec3(0,1,0)); // up

	camera.lookAt(glm::vec3(2, 2, 2), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	obj.transform = glm::rotate(nsfw::Window::instance().getTime(),glm::vec3(0,1,0));
	obj.diffuse   = "Magenta"; // Default built-in
	obj.mesh	  = "Cube";	   // Default built-in
	obj.tris	  = "Cube";    // Default built-in

	fp.shader	= "Basic";
}

void TestApp::onInit()
{
	nsfw::Assets::instance().loadShader("Basic", "../resources/shaders/basic.vert",
												 "../resources/shaders/basic.frag");

	nsfw::Assets::instance().loadTexture("Purple", "../resources/textures/purple.png");
}

void TestApp::onTerm()
{
}
