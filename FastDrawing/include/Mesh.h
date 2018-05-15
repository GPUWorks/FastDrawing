#pragma once
#include <vector>
#include <iostream>
#include "../include/Color.h"
#include "glad/glad.h"
//#include <GLFW/glfw3.h>


#define LAYOUT_POSITION 0

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

	//various drawing
	void DrawSolidColor(Color color);
	void Draw();

private:

	GLuint VBO, VAO, program;
	GLint mvpLocation, vPosLocation, vColLocation;

	std::string vertexShaderText;
	std::string fragmentShaderText;


	std::vector<Vertex> vertices;
};

