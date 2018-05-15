#pragma once
#include <vector>
#include <iostream>
#include "include/glad/glad.h"
//#include <GLFW/glfw3.h>

typedef struct {
	float x, y, z;
}Vertex;




class Mesh
{
public:
	Mesh(std::string vertexShaderText, std::string fragmentShaderText);
	~Mesh();

	void SetVertices(std::vector<Vertex> vertices);
	void Bind();
	void Draw();

private:
	//used to automatic assign vertex buffer
	static GLuint vertexBufferCounter;

	GLuint vertexBuffer, vertexArray, vertexShaderID, fragmentShaderID, program;
	GLint mvpLocation, vPosLocation, vColLocation;

	std::string vertexShaderText;
	std::string fragmentShaderText;


	std::vector<Vertex> vertices;
};

