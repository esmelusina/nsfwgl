#include <ogl\gl_core_4_4.h>
#include "nsfw.h"
#include <fstream>
#include <stb\stb_image.h>

using namespace nsfw::ASSET;

const char *nsfw::TYPE_NAMES[eSIZE + 1] = { "NONE","vao","ibo","vbo","tri-size","fbo","rbo","texture","shader","SIZE" };

#ifdef _DEBUG
#define ASSET_LOG(type) do { std::cerr << "Trying to create key: <" << TYPE_NAMES[type] << ">" << name << std::endl; } while(0)
#else 
#define ASSET_LOG(type) do {} while (0)
#endif


nsfw::GL_HANDLE nsfw::Assets::getVERIFIED(const AssetKey &key) const
{
#ifdef _DEBUG
			if (!handles.count(key))
			{
				std::cerr << "Asset Key not found: <" << TYPE_NAMES[key.first] << ">" << key.second << std::endl;
				return 0;
			}
#endif
			return handles.at(key);
}

bool nsfw::Assets::setINTERNAL(ASSET::GL_HANDLE_TYPE t, const char *name, GL_HANDLE handle)
{
	AssetKey key(t, name);
#ifdef _DEBUG
	if (handles.count(key))
	{
		std::cerr << "Asset Key already exists: <" << TYPE_NAMES[key.first] << ">" << key.second << " ignoring." << std::endl;
		return false;
	}
	else if (handle == 0)
	{
		std::cerr << "Handle is invalid: <" << TYPE_NAMES[key.first] << ">" << key.second << " ignoring." << std::endl;
		return false;

	}
	else std::cerr << "Asset Key successfully created: <" << TYPE_NAMES[key.first] << ">" << key.second << std::endl;
#endif
	handles[key] = handle;
	return true;
}

/*
	Array of Vertices (and how many vertices)
	Array of Indices  (and how many indices)
*/
bool nsfw::Assets::makeVAO(const char *name, const struct Vertex *verts, unsigned vsize,  const unsigned * tris, unsigned tsize)
{
	ASSET_LOG(GL_HANDLE_TYPE::VBO);	 // Array on the video card that stores vertices
	ASSET_LOG(GL_HANDLE_TYPE::IBO);  // Array on the video card that stores which vertices make up triangles
	ASSET_LOG(GL_HANDLE_TYPE::VAO);  // Association between a VBO and IBO
	ASSET_LOG(GL_HANDLE_TYPE::SIZE); // How many triangles does a VAO hold

	unsigned vbo, ibo, vao, size = tsize;

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER,         vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	
	glBufferData(GL_ARRAY_BUFFER,         vsize * sizeof(Vertex),  verts, GL_STATIC_DRAW);	// VBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size  * sizeof(unsigned), tris, GL_STATIC_DRAW);	// IBO
	// VAO
	glEnableVertexAttribArray(0);	// position : Spatial Location
	glEnableVertexAttribArray(1);	// normal	: Direction (normalized)
	glEnableVertexAttribArray(2);	// tangent	: Direction (normalized)
	glEnableVertexAttribArray(3);	// texCoord : Spatial Location (2D)

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)Vertex::POSITION	);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE,  sizeof(Vertex), (void*)Vertex::NORMAL	);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_TRUE,  sizeof(Vertex), (void*)Vertex::TANGENT	);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)Vertex::TEXCOORD	);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER,         0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	setINTERNAL(GL_HANDLE_TYPE::VBO,  name, vbo);
	setINTERNAL(GL_HANDLE_TYPE::IBO,  name, ibo);
	setINTERNAL(GL_HANDLE_TYPE::VAO,  name, vao);
	setINTERNAL(GL_HANDLE_TYPE::SIZE, name, size);
	return true;
}

bool nsfw::Assets::makeFBO(const char * name, unsigned w, unsigned h, unsigned nTextures, const char * names[], const unsigned depths[])
{
	ASSET_LOG(GL_HANDLE_TYPE::FBO);
	unsigned fbo;
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	// 8 guaranteed color attachment 
	// 1 stencil attachment 
	// 1 depth attachment 
	int nColors = 0;
	for (int i = 0; i < nTextures; ++i)
	{
		makeTexture(names[i], w, h, depths[i]);
		unsigned Attachment;
		if      (depths[i] == GL_DEPTH_COMPONENT) Attachment = GL_DEPTH_ATTACHMENT;
		else if (depths[i] ==   GL_DEPTH_STENCIL) Attachment = GL_STENCIL_ATTACHMENT;
		else	/*is a color!*/					  Attachment = GL_COLOR_ATTACHMENT0 + nColors++;

		glFramebufferTexture(GL_FRAMEBUFFER, Attachment, get<TEXTURE>(names[i]), 0);
	}

	GLenum *colorAttachments = new GLenum[nColors];
	for (int i = 0; i < nColors; ++i) colorAttachments[i] = GL_COLOR_ATTACHMENT0 + i;
	glDrawBuffers(nColors, colorAttachments);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	setINTERNAL(GL_HANDLE_TYPE::FBO, name, fbo);
	return true;
}

bool nsfw::Assets::makeTexture(const char * name, unsigned w, unsigned h, unsigned depth, const unsigned char *pixels)
{
	ASSET_LOG(GL_HANDLE_TYPE::TEXTURE);
	unsigned texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	
	// valid values for depth GL_RGBA, GL_RGB, GL_RG, GL_RED, GL_DEPTH_COMPONENT, GL_DEPTH_STENCIL
	glTexImage2D(GL_TEXTURE_2D, 0, depth, w, h, 0, depth, GL_UNSIGNED_BYTE, pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_2D, 0);
	setINTERNAL(GL_HANDLE_TYPE::TEXTURE, name, texture);
	return true;
}

bool nsfw::Assets::loadTexture(const char * name, const char * path)
{
	int w, h, d;

	unsigned char *p = stbi_load(path, &w, &h, &d, STBI_default);

	switch (d)
	{
	case 1: d = GL_RED;  break;
	case 2: d = GL_RG;   break;
	case 3: d = GL_RGB;  break;
	case 4: d = GL_RGBA; break;
	}

	makeTexture(name, w, h, d, p);
	stbi_image_free(p);
	return true;
}

bool nsfw::Assets::loadShader(const char * name, const char * vpath, const char * fpath)
{
	ASSET_LOG(GL_HANDLE_TYPE::SHADER);
	GLuint shader = glCreateProgram();

	std::ifstream vin(vpath); // Fetch from file
	std::string vcontents((std::istreambuf_iterator<char>(vin)),
						   std::istreambuf_iterator<char>());

	std::ifstream fin(fpath);
	std::string fcontents((std::istreambuf_iterator<char>(fin)),
						   std::istreambuf_iterator<char>());

	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

	const char *vs = vcontents.c_str();
	const char *fs = fcontents.c_str();

	glShaderSource(vShader, 1, &vs, 0);
	glShaderSource(fShader, 1, &fs, 0);

	glCompileShader(vShader);
	glCompileShader(fShader);

	glAttachShader(shader, vShader);
	glAttachShader(shader, fShader);

	glLinkProgram(shader);

	glDeleteShader(vShader);
	glDeleteShader(fShader);

	setINTERNAL(GL_HANDLE_TYPE::SHADER, name, shader);
	return true;
}


bool nsfw::Assets::loadFBX(const char * name, const char * path)
{
	//name/meshName
	//name/textureName
	TODO_D("FBX file-loading support needed.\nThis function should call loadTexture and makeVAO internally.\nFBX meshes each have their own name, you may use this to name the meshes as they come in.\nMAKE SURE YOU SUPPORT THE DIFFERENCE BETWEEN FBXVERTEX AND YOUR VERTEX STRUCT!\n");
	return false;
}

bool nsfw::Assets::loadOBJ(const char * name, const char * path)
{
	TODO_D("OBJ file-loading support needed.\nThis function should call makeVAO and loadTexture (if necessary), MAKE SURE TO TAKE THE OBJ DATA AND PROPERLY LINE IT UP WITH YOUR VERTEX ATTRIBUTES (or interleave the data into your vertex struct).\n");
	return false;
}

void nsfw::Assets::init()
{	
	setINTERNAL(FBO, "Screen", 0);
	
	makeVAO("Cube", CubeVerts,24, CubeTris,36);
	makeVAO("Quad", QuadVerts, 4, QuadTris, 6);
	
	unsigned char w[] = {255,  0,255,255};
	makeTexture("Magenta", 1, 1, GL_RGBA, w);	// texture not loaded properly
	unsigned char t[] = {255,255,255,255};
	makeTexture("White",   1, 1, GL_RGBA, t);		// null value
}

// <GL_TYPE Enum, String> : Handle
void nsfw::Assets::term()
{
	for each(std::pair<AssetKey,unsigned> k in handles)
	{
		GLuint handle = k.second;	
		switch (k.first.first)
		{
		case VBO:	  glDeleteBuffers      (1, &handle); break;
		case IBO:	  glDeleteBuffers      (1, &handle); break;
		case VAO:	  glDeleteVertexArrays (1, &handle); break;
		case SHADER:  glDeleteProgram      (    handle); break;
		case TEXTURE: glDeleteTextures     (1, &handle); break;
		case FBO:     glDeleteFramebuffers (1, &handle); break;
		}
	}
}


