#pragma once

#include <iostream>
#include <string.h>

#include "../include/glad/glad.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include "stb_image.h"

namespace rend {
	GLenum unit(int index);
	struct image {
		int width = 0;
		int height = 0;
		int nrChannels = 0;
		unsigned char *data;
	};
	class Texture {
	public:
		GLenum textureUnit;
		image image_data;
		unsigned int ID;
		Texture(std::string image_path, int unit);
		Texture();
	};
}