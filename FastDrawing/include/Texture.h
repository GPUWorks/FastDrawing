#pragma once
#include <string>
#include "glad/glad.h"

class Texture
{
public:
	Texture(const std::string &filePath);
	~Texture();

	int GetWidth() const
	{
		return width;
	}
	int GetHeight() const
	{
		return height;
	}
	int GetNrChannels() const
	{
		return nrChannels;
	}
	GLuint GetID() const
	{
		return textureID;
	}

private:
	int width, height, nrChannels;
	GLuint textureID;
};

