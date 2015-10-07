#pragma once
#include <list>
#include "Assets.h"
/*
	This file contains a BASE CLASS for a Render Pass object.

	The RenderPass object will use a shader to write
	some such number of objects to some FBO that it keeps track of.

	
	*** You should inherit from this class, implementing the prep, draw, and post functions.

	*** You should also implement the setUniform function, to make future passes
	a little easier to work with.
*/

namespace nsfw
{
	// Add whatever types you want!
	namespace UNIFORM
	{
		enum TYPE { eNONE, FLO1, FLO3, FLO4, MAT4, INT1, TEX2, eSIZE };
	}

	class RenderPass
	{
	protected:
		Asset<ASSET::FBO>	  fbo;		// All renderpasses should use an FBO. 0 is the screen!
		Asset<ASSET::SHADER>  shader;	// All RPs also use a shader!

	public:
		RenderPass(Asset<ASSET::SHADER> a_shader, Asset<ASSET::FBO> a_fbo) : shader(a_shader), fbo(a_fbo) {}
		// uniforms could be set in prep, elsewhere in the application, or in the draw
		// This function should allow you to hide the glUniform* functions into a SWITCH statement.
		// The logic for each uniform is slightly different- not all parameters are necessary.
		// value should be the address of whatever data you want to use- it should match with
		// the uniform we're using. count is for arrays (or texture slot). Normalize is whether or not
		// we want GL to normalize the data coming in or not.

		// We can return whether or not the we were successful (location == -1)
		bool setUniform(const char *name, UNIFORM::TYPE type, const void *value, unsigned count = 1, bool normalize = false);

		// set GL state settings and globally accessible uniforms! Should be called before rendering occurs!
		virtual void prep();

		// reset the GL state- undo what we did just in case.
		virtual void post();
	};
}




/*
Some excluded cleverness:
	static const std::list<RenderPass*> es_rps;
	static const std::list<RenderPass*> &getAll() { return es_rps; }
	RenderPass() { es_rps.push_back(this); }
	virtual ~RenderPass() { es_rps.remove(this); }
*/