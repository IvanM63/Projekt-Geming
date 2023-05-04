#ifndef QUAD_H
#define QUAD_H

#include <SDL/SDL.h>
#include <GL/glew.h>


namespace Engine {
	class Quad
	{
	public:
		Quad();
		~Quad();
		void Draw();
	private:
		GLuint vbo, ebo, vao;
		void Build();
	};
}

#endif

