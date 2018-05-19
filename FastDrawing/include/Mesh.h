#pragma once
#include <vector>
#include <iostream>
#include "../include/Color.h"
#include "../include/Texture.h"
#include "glm/glm/glm.hpp"
#include "../include/Shader.h"
#include "glm/glm/gtc/matrix_transform.hpp"
#include "glm/glm/gtc/type_ptr.hpp"
#include "glad/glad.h"


#define LAYOUT_POSITION 0
#define LAYOUT_UV 1

typedef struct {
	float x, y, z, u, v;
}Vertex;


class Mesh
{
public:
	Mesh(Shader* shader);
	//Mesh(std::string filePath);
	~Mesh();

	void SetVertices(std::vector<Vertex> vertices, std::vector<int> indices = std::vector<int>{ 0,1,3,1,2,3});	//default triangle
	void Bind();
	void SetTintColor(Color color);
	void DisableTint();

	//various drawing
	void DrawSolidColor(Color color);
	void DrawTexture(Texture* texture);
	void Draw();

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	glm::vec3 pivot;

	Shader* shader;

private:

	glm::mat4 Transform();
	void ApplyUniformTransformation();

	GLuint VBO, VAO, indexBuffer;
	GLint mvpLocation, vPosLocation, vColLocation;

	bool useTint;
	Color* tintColor;

	size_t textureMode, textureWrapping;

	std::vector<Vertex> vertices;
	std::vector<int> indices;
};

//enum TEXTURE_MODE{TWO_D = GL_TEXTURE_2D};
//enum TEXTURE_WRAPPING{REPEAT = GL_REPEAT, MIRRORED_REPEAT = GL_MIRRORED_REPEAT, CLAMP_EDGE = GL_CLAMP_TO_EDGE, CLAMP_BORDER = GL_CLAMP_TO_BORDER};

