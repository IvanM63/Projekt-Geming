#include "Texture.h"

using namespace Engine;

Texture::Texture(string imagePath)
{
	Load(imagePath);
}

Texture::~Texture()
{
}

GLuint Texture::GetTextureId()
{
	return this->textureId;
}

int Engine::Texture::GetWidth()
{
	return this->width;
}

int Engine::Texture::GetHeight()
{
	return this->height;
}

void Engine::Texture::Bind()
{
	// All upcoming GL_TEXTURE_2D operations now have effect on our texture object
	glBindTexture(GL_TEXTURE_2D, textureId);
}

void Engine::Texture::UnBind()
{
	// Unbind texture when done, so we won't accidentily mess up our texture.
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Engine::Texture::SetSmooth(bool smooth)
{
	if (smooth) {
		// Set texture filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else {
		// Set texture filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}
}

void Texture::Load(string imagePath)
{
	// Load and create a texture 
	glGenTextures(1, &textureId);
	Bind();
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// Load, create texture 
	unsigned char* image = SOIL_load_image(imagePath.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	UnBind();
}
