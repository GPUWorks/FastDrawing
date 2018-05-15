#include "include/glad/glad.h"
#include "Window.h"





Window::Window(std::string title, int width, int height, int minorOpenGL, int majorOpenGL)
{
	this->title = title;
	this->width = width;
	this->height = height;
	this->minorOpenGL = minorOpenGL;
	this->majorOpenGL = majorOpenGL;

	if (!glfwInit())
	{
		//initialization failed
		throw std::exception("Initialization failed");
	}

	//set opengl versions
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, this->majorOpenGL);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, this->minorOpenGL);

	//window initialization
	this->window = glfwCreateWindow(this->width, this->height, this->title.c_str(), nullptr, nullptr);
	if (!this->window)
	{
		//window initialization failed
		throw std::exception("Window initialization failed");
	}

	//set the current context
	glfwMakeContextCurrent(this->window);
	//load opengl
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSwapInterval(1);
}


Window::~Window()
{

	if (this->window)
	{
		glfwDestroyWindow(this->window);
	}

	glfwTerminate();
}

bool Window::IsOpened() {
	return !glfwWindowShouldClose(this->window);
}

int Window::GetWidth() {
	return this->width;
}

int Window::GetHeight() {
	return this->height;
}

std::string Window::GetTitle() {
	return this->title;
}


void Window::Blit() {
	glfwSwapBuffers(this->window);
}
 
void Window::Clear(float r, float g, float b, float a) {

	//float ratio;
	int width, height;
	glfwGetFramebufferSize(this->window, &width, &height);
	//ratio = width / (float)height;
	glViewport(0, 0, width, height);
	glClearColor(r,g,b,a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Window::Clear() {
	this->Clear(0, 0, 0, 1);
}

