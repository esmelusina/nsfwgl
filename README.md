# nsfwgl
Not suited for work, openGL.



Run the solution- it will automatically whine about what features need to be implemented.

This project ONLY brings the glm dependency with it- STBI, GLFW, GL_CORE, FBX, OBJ, and other dependencies will need to be linked to the nsfwgl project as per normal.


The solution uses a build dependency structure. nsfwgl produces a .lib file, that the defer project uses.


This entire solution is logically complete/engineered. It may have features you wish to add or restructure- feel free to do so. Compiling/executing the code will produce a TODO note, indicating the line/file/details about what feature is missing and what you need to modify.


Stepping through the main and understanding the individual activities going on is essential. If all of the TODO messages are resolved correctly and shaders successfully implemented, the project is done.


Description of resources:

_NSFWGL_

Assets : Singleton object used for loading/making/storing openGL handles.


Asset<TYPE> : Reference object to provide a layer of indirection to an individual GL asset in Assets (just some sugar!).

Window : Singleton object used for wrapping GLFW

Render : RenderpPass base object, intended to be inherited from to create shader/FBO associations.

Application : A straightforward application base object intended to be inherited from.

Vertex : A standard vertex format (replace with FBXVertex or whatever you want if you prefer- typedef it out though!).



_DEFER_

DefApp : Implements Application for this particular project.

Camera, Geometry, Light: All contain uniform data necessary for rendering passes to work.

GPass, LPassD, CPass : Each of the render passes for deferred rendering. They implement RenderPass from above.
