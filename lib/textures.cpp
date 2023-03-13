#include "textures.h"

GLenum rend::unit(int index) {
	switch(index) {
	case 0:
		return GL_TEXTURE0;
	case 1:
		return GL_TEXTURE1;
	case 2:
		return GL_TEXTURE2;
	case 3:
		return GL_TEXTURE3;
	case 4:
		return GL_TEXTURE4;
	}
	return -5;
}

rend::Texture::Texture(std::string image_path, int unit) {
	stbi_set_flip_vertically_on_load(true);
	this->textureUnit = rend::unit(unit);
	this->image_data.data = stbi_load(image_path.c_str(), &this->image_data.width, &this->image_data.height, &this->image_data.nrChannels, 0);
	glGenTextures(1, &this->ID);
	glBindTexture(GL_TEXTURE_2D, this->ID);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if(this->image_data.data)  {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->image_data.width, this->image_data.height, 0, GL_RGB, GL_UNSIGNED_BYTE, this->image_data.data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		std::cout << "failed to load texture" << std::endl;
	}

	stbi_image_free(this->image_data.data);
}

rend::Texture::Texture() {
}