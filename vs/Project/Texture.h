#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <SOIL/SOIL.h>
#include <SDL/SDL.h>
#include <GL/glew.h>

using namespace std;

namespace Engine {
	class Texture
	{
	public:
		Texture(string imagePath);
		~Texture();
		GLuint GetTextureId();
		int GetWidth();
		int GetHeight();
		void Bind();
		void UnBind();
		void SetSmooth(bool smooth);
	private:
		GLuint textureId;
		int width, height;
		void Load(string imagePath);

	};
}

#endif

