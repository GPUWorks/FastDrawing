#pragma once
#include <string>
#include <iostream>
#include <stdexcept>
#include "Camera.h"
#include "glm/glm/matrix.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"
#include <GLFW/glfw3.h>

class Window
{
public:
	Window(const std::string &title, int width, int height, int minorOpenGL = 3, int majorOpenGL = 3);
	~Window();

	int GetWidth();
	int GetHeight();
	std::string GetTitle();

	bool IsOpened();

	//important API
	void Blit();
	void Clear(float r, float g, float b, float a);
	void Clear();
	glm::mat4 GetProjectionMatrix();

	static Window* current;
	Camera* currentCamera;

private:
	GLFWwindow * window;

	int minorOpenGL;
	int majorOpenGL;
	
	//purely window properties
	int width;
	int height;
	std::string title;
	//glm::mat4 projectionMatrix;
	
};

