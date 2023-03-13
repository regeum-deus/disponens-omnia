#pragma once

#include <iostream>
#include <stdint.h>

#include "../include/glad/glad.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "shaders.h"
#include "textures.h"
#include "transformation.h"

namespace rend {
	class Model {
	public:
		glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);

		glm::mat4 modelspace = glm::mat4(0.0f);

		rend::Shader shader;
		rend::Texture *textures;

		std::string vertexpath = "./res/shaders/default.vertex";
		std::string fragmentpath = "./res/shaders/default.fragment";

		bool textured = false;
		int texture_amount;

		float *vertices; float vertex_count;
		unsigned int *indices; float index_count;
		unsigned int VAO, VBO, EBO;
		
		void shaders();
		void render();
		void render(rend::Camera c);
		Model();
		Model(std::string vss, std::string fss, float *verts, float vertex_count, unsigned int *indices, float index_count, bool vp, bool fp);
		Model(std::string vss, std::string fss, float *verts, float vertex_count, unsigned int *indices, float index_count, bool vp, bool fp, int vaa, int *vas);

		void texture_init(std::string *image_path, int amount);
		void programUsage(void (*_usage)(int));
	
		void model_translate(glm::vec3 vec);
	};
}