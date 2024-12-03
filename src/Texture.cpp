#include "Texture.h"

#include "iostream"

Texture::Texture(const char* texturePath, int textureFormat) {
	//stbi_set_flip_vertically_on_load(true);

	data = stbi_load(texturePath, &width, &height, &nrChannels, 0);

	if (data == nullptr) {
		std::cout << "failed to load texture\n";
		return;
	}

	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	float color[]{ 1.f, 1.f, 1.f, 1.f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);

	// define o tipo de mipmap
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

	// define o filtro da image
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, textureFormat, width, height, 0, textureFormat, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	// libera a memoria da image
	stbi_image_free(data);

}

void Texture::use() const {
	glBindTexture(GL_TEXTURE_2D, ID);
}