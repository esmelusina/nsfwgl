#include "TestApp.h"

void TestApp::onStep()
{
	fp.prep();
	fp.draw(camera, obj);
	fp.post();
}

void TestApp::onPlay()
{
	camera.lookAt(glm::vec3(10,10,10), // offset to the top,right,forward
				  glm::vec3(0,0,0),  // origin
				  glm::vec3(0,1,0)); // up

	obj.transform = glm::mat4(1);
	obj.diffuse   = "Magenta"; // Default built-in
	obj.mesh	  = "Quad";	   // Default built-in
	obj.tris	  = "Quad";    // Default built-in

	fp.shader	= "Basic";
}

void TestApp::onInit()
{
	nsfw::Assets::instance().loadShader("Basic", "../resources/shaders/basic.vert",
												 "../resources/shaders/basic.frag");
}

void TestApp::onTerm()
{
}
