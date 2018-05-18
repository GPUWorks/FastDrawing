
#include "Camera.h"
#include "Window.h"

Camera::Camera(float orthoSize, float near, float far) {
	
	Window::current->currentCamera = this;
	this->orthoSize = orthoSize;
	this->Znear = near;
	this->Zfar = far;

	this->position = glm::vec3(0, 0, -1);
}
