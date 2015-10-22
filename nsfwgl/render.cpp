#include <ogl\gl_core_4_4.h>
#include "nsfw.h"


// Each Case should set up a uniform using the pass parameters
bool nsfw::RenderPass::setUniform(const char *name, nsfw::UNIFORM::TYPE type, const void *value, unsigned count, bool normalize) 
{
	GLint loc = glGetUniformLocation(*shader, name);
	switch (type)
	{
	case nsfw::UNIFORM::FLO1: glUniform1fv(loc, count, (const GLfloat*)value); break;
	case nsfw::UNIFORM::FLO3: glUniform3fv(loc, count, (const GLfloat*)value); break;
	case nsfw::UNIFORM::FLO4: glUniform4fv(loc, count, (const GLfloat*)value); break;
	case nsfw::UNIFORM::MAT4: glUniformMatrix4fv(loc, count, normalize, (const GLfloat*)value);  break;
	case nsfw::UNIFORM::INT1: glUniform1iv(loc, count, (const GLint*)value); break;
	case nsfw::UNIFORM::TEX2:
							  glActiveTexture(GL_TEXTURE0 + count);
							  glBindTexture(GL_TEXTURE, *(const GLuint*)value);
							  glUniform1i(loc, count); break;

	default:				  TODO_D("INVALID Uniform type.");	  break;
	}

	return false;
}

// set GL state settings and globally accessible uniforms! Should be called before rendering occurs!
void nsfw::RenderPass::prep() { TODO_D("OVERRIDE: Setup the state of the card for this pass."); }

// reset the GL state- undo what we did just in case.
void nsfw::RenderPass::post() { TODO_D("OVERRIDE: Clean up the state of the card."); }