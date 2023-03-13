#include "transformation.h"


const glm::vec3 rend::UP = glm::vec3(0.0f, 1.0f, 0.0f);
float rend::FOV = 45.0f;


glm::mat4 rend::fromquat(glm::quat quaternion) {
	glm::mat4 mat = glm::toMat4(quaternion);
	return mat;
}

glm::vec4 rend::transform(glm::vec4 vec, glm::vec4 direction, rend::TYPE t) {
	glm::vec4 transformedvec;
	glm::mat4 mat;
	glm::vec3 v(direction);
	switch(t) {
	case rend::TYPE::translation:
		mat = glm::translate(glm::mat4(), glm::vec3(direction));
		break;
	case rend::TYPE::identity:
		mat = glm::mat4(1.0f);
		break;
	case rend::TYPE::scaling:
		mat = glm::scale(glm::mat4(), v);
		break;
	case rend::TYPE::rotation:
		mat = fromquat(glm::quat(v));
		break;
	}

	transformedvec = mat * vec;
	return transformedvec;
}

glm::vec4 rend::full_transform(glm::vec4 vec, glm::vec4 tdirection, glm::vec3 rdirection, glm::vec4 sdirection) {
	glm::mat4 smat;
	
	glm::vec3 v(sdirection);
	smat = glm::scale(glm::mat4(), v);

	glm::mat4 rmat = fromquat(glm::quat(rdirection));

	glm::mat4 tmat = glm::translate(glm::mat4(), glm::vec3(tdirection));
	
	glm::mat4 modelmat = tmat * rmat * smat;
	return modelmat * vec;	
}

rend::Camera::Camera(glm::vec3 position, float a, float n, float f) {
	this->aspect = a;
	this->nearclip = n;
	this->farclip = f;
	this->position = position;
}
void rend::Camera::translate(glm::vec3 vec) {
	this->position += vec;
	this->ViewMatrix = glm::translate(glm::mat4(), this->position);
}

void rend::Camera::lookat(glm::vec3 target) {
	this->ViewMatrix = glm::lookAt(this->position, target, rend::UP);
}

void rend::Camera::perspective() {
	this->projectionMatrix = glm::perspective(glm::radians(FOV), this->aspect, this->nearclip, this->farclip);
}

glm::mat4 rend::MVPcompute(rend::Camera c, glm::mat4 vec3model) {
	glm::mat4 MVP = c.projectionMatrix * c.ViewMatrix * vec3model;
	return MVP;
}