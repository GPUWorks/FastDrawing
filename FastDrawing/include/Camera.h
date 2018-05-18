#pragma once
#include "glm/glm/vec3.hpp"
#include "glm/glm/matrix.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"

class Camera {

public:
	Camera(float orthoSize = 10.0f, float Znear = -0.1f, float Zfar = -100.0f);
	~Camera(){}

	glm::vec3 position;

	float orthoSize;
	float Znear;
	float Zfar;


	glm::mat4 GetViewMatrix() { return glm::lookAtLH(this->position, glm::vec3(0, 0, 1), glm::vec3(0, 1, 0)); }
};
