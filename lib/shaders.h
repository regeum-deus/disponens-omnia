#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "../include/glad/glad.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

namespace rend {
	class Shader {
	public:
		unsigned int ID;
		Shader(const char *vertexPath, const char *fragmentPath);
		Shader();
		void use();
		void setBool(const std::string &name, bool value) const;
		void setInt(const std::string &name, float value) const;
		void setFloat(const std::string &name, float value) const;
	};
}