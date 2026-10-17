#include "Texture.h"
#include <stb/stb_image.h>
#include"Paths.h"

Texture::Texture(std::string TextureName, char const* filename)
{
	Name = TextureName;
	int width, height, channels;
	stbi_set_flip_vertically_on_load(true);


	unsigned char* data = stbi_load(Paths::Texture(filename).c_str(), &width, &height, &channels, STBI_rgb_alpha);

	if (data != NULL)
	{
		glActiveTexture(GL_TEXTURE0);
		glGenTextures(1, &ID);
		glBindTexture(GL_TEXTURE_2D, ID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT); //GL_CLAMP_TO_EDGE
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		//glGenerateMipmap(GL_TEXTURE_2D);

		textureSize = { width, height };
	}
	else
	{
		ID = 0;
	}
	stbi_image_free(data);
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, ID);
}