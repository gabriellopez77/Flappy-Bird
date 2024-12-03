#pragma once

#include "../Dependencies/stb/stb_image.h"
#include "../Dependencies/glad/glad.h"

class Texture {
public:
	Texture(const char* texturePath, int textureFormat);
	void use() const;

	unsigned char* data;
	unsigned int ID;
	int width;
	int height;
	int nrChannels;
};