#pragma once
#include <unordered_map>
#include <string>

/*
	The asset management object is a place to keep track of all of the memory
	stored on the video card. From this, we can load data from files, or generate
	new objects as they are needed.

	
	In it are two objects.

	The Asset struct contains all of the information necessary to fetch the openGL handle
	from the Assets object. It is templated for typing purposes.

	Assets is the super container for all openGL handles. A safe place to ensure everything
	is properly liberated and allocated and never lost. It also allows us to ensure
	objects don't load the same thing multiple times.

	usage:

	To load an image into the asset library->
		auto &a = Assets::instance();

		a.loadTexture("JohnDiffuseMap","/path/to/file/john/diffuse.png");

	To create an asset reference->
		Asset<TEXTURE> diffuseMap = "JohnDiffuseMap";	

	To use the asset reference to fetch the handle, any of the following will work:
		a[diffuseMap];
		a.get(diffuseMap);
		a.get<TEXTURE>("JohnDiffuseMap");
		a.get(TEXTURE,"JohnDiffuseMap");
		

		*** Implement the necessary LOAD and MAKE functions, as well as the TERM function.
*/

namespace nsfw
{
	// Keep track of the type of handle
	enum TYPE { eNONE, VAO, IBO, VBO, SIZE, FBO, RBO, TEXTURE, SHADER, eSIZE };
	
	// Use a handle type and name to use as an index for each asset
	typedef std::pair<TYPE, std::string>  AssetKey;

	// for explicitness
	typedef unsigned GL_HANDLE;

	// Asset reference object, used to keep a type and name associated with the
	// manner in which the Assets arranges its keys. This is purely sugar.
	template <TYPE T> struct Asset
	{
		const TYPE t;
		std::string name;
		Asset() {}
		Asset(const char *n) : name(n) {}				  // construct w/string if desired
		operator=(const char *s) { name = s; }			  // conviently assign strings directly to reference		
		operator AssetKey() { return AssetKey(t, name); } // for use with Assets::Operator[]
		GL_HANDLE operator*() { Assets::instance()[*this]; } // Overload value-of operator, to dereference
	};


	/*
		Asset management singleton. It should be the only place that the glGen**** functions
		are called, and the only place where glDelete/Destroy/etc. are called. It should
		serve no other purpose than to provide a concise location where all openGL handles are
		kept track of and to provide a layer of indirection between objects in the game and
		the actual asset on the video card.
	*/
	class Assets
	{
	private:
		// Hashing functor object for accepting pair<enum,string> as an index.
		struct Hash { size_t operator()(AssetKey k) { return std::hash<std::string>()(k.second) + (unsigned)k.first; } };
		
		// Store all of our keys in one place!
		std::unordered_map<AssetKey, GL_HANDLE, Hash> handles;
		Assets() {}

	public:
		// Singleton accessor
		static Assets &instance() { static Assets a; return a; }

		//normal get handle function
		GL_HANDLE get(TYPE t, const char *name)	const { return handles.at(AssetKey(t, name)); }

		//templated Get,for sexiness
		template<TYPE t>
		GL_HANDLE get(const char *name)			const { return AssetKey(t, name); }

		// Get via the Asset reference, sexier
		GL_HANDLE get(AssetKey key)				const { return handles.at(key); }

		//Conveniently fetch handle using an Asset object, for even more sexy
		GL_HANDLE operator[](AssetKey key)		const { return get(key); }



		////////////
		// Fill these out!

		// Should also allocate for IBO and VBO
		void makeVAO(const char *name, struct Vertex *verts, unsigned vsize, unsigned *tris, unsigned tsize);

		// should call makeTexture nTextures number of times
		void makeFBO(const char *name, unsigned w, unsigned h, unsigned nTextures, const char *names[], unsigned depths[]);

		// should allocate space for a texture, but not necessarily set its data
		void makeTexture(const char *name, unsigned w, unsigned h, unsigned depth);

		// should load a texture from a file, use makeTexture to alloc, and then copy filedata in
		void loadTexture(const char *name, const char *path);
	
		// should load a shader from file
		void loadShader(const char *name, const char *vpath, const char *fpath);
	
		// should load from an FBX, adding assets to the library as they are discovered
		void loadFBX(const char *name, const char *path);

		// Should load an OBJ from file, adding appropriate assets to the library
		void loadOBJ(const char *name, const char *path);

		// clear out all of the opengl handles!
		void term();
	};
}