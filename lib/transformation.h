#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

namespace rend {
	enum class TYPE {
		translation,
		identity,
		scaling,
		rotation,
	};

	extern float FOV;
	extern const glm::vec3 UP;

	glm::mat4 fromquat(glm::quat quaternion);
	glm::vec4 transform(glm::vec4 vec, glm::vec4 direction, rend::TYPE t);
	glm::vec4 full_transform(glm::vec4 vec, glm::vec4 tdirection, glm::vec3 rdirection, glm::vec4 sdirection);

	class Camera {
	public:
		Camera(glm::vec3 position, float a, float n, float f);
		glm::vec3 position;
		glm::mat4 ViewMatrix;
		glm::mat4 projectionMatrix;
		float aspect;
		float nearclip;
		float farclip;
		void translate(glm::vec3 vec);
		void lookat(glm::vec3 target);
		void perspective();
	};

	glm::mat4 MVPcompute(Camera c, glm::mat4 vec3model);

	/*IMPORTANT NOTE
		Okay so to get the projections to work you
		do the following:
			rend::Camera c(<vec3>, <float>, <float>, <float>);
			c.perspective();
			c.lookat(<vec3>);
			glm::mat4 Model = glm::mat4(1.0f);

			//translate the model how you want here

			glm::mat4 mvp = c.projectionMatrix * c.ViewMatrix * Model;

			//give the mvp to the program
			GLuint MatrixID = glGetUniformLocation(<GLuint programID>, "mvp");
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

			
			//----------------
			//in vertex shader
			//----------------
			//layout(location = 0) in vec3 model;
			//
			//uniform mat4 mvp;
			//void main() {
			//	gl_Position = mvp * vec4(model, 1);
			//}

	*/
}