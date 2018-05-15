#pragma once
#include <string>
#include <iostream>
#include <stdexcept>
#include <GLFW/glfw3.h>

class Window
{
public:
	Window(std::string title, int width, int height, int minorOpenGL = 3, int majorOpenGL = 3);
	~Window();

	int GetWidth();
	int GetHeight();
	std::string GetTitle();

	bool IsOpened();

	//important API
	void Blit();
	void Clear(float r, float g, float b, float a);
	void Clear();

private:
	GLFWwindow * window;

	//purely window properties
	int width;
	int height;
	std::string title;
	int minorOpenGL;
	int majorOpenGL;
};

