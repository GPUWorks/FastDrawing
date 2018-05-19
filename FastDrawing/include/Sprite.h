#pragma once
#include "Mesh.h"

class Sprite : public Mesh
{
public:
	Sprite(int width, int height) :Mesh(new Shader("#version 330 core\n"
		"layout(location = 0) in vec3 aPos;\n"
		"layout(location = 1) in vec2 aTexCoord;\n"
		"uniform mat4 transform;\n"
		"uniform mat4 view;\n"
		"uniform mat4 projection;\n"
		//"uniform mat4 pivot;\n"
		"out vec2 TexCoord;\n"
		"void main()\n"
		"{\n"
		"gl_Position = projection * view * transform * vec4(aPos.xy, 0.0f, 1.0f);\n"
		"TexCoord = aTexCoord;\n"
		"}\n",

		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"in vec2 TexCoord;\n"
		"uniform sampler2D ourTexture;\n"
		"uniform int useTexture;\n"
		"uniform vec4 ourColor;\n"
		"uniform vec4 tintColor;\n"
		"void main()\n"
		"{\n"
		"if(useTexture == 0) FragColor = ourColor;\n"
		"else FragColor = texture(ourTexture, TexCoord) * tintColor;\n"
		"}\n")
		)
	{
		std::vector<Vertex> vertices;
		Vertex v1 = { width, height, 0.0f,			1.0f,0.0f };
		Vertex v2 = { width, -height, 0.0f,		1.0f,1.0f };
		Vertex v3 = { -width, -height, 0.0f,		0.0f,1.0f };
		Vertex v4 = { -width,  height, 0.0f,		0.0f, 0.0f };

		vertices.push_back(v1);
		vertices.push_back(v2);
		vertices.push_back(v3);
		vertices.push_back(v4);

		SetVertices(vertices);
		Bind();
	}
	~Sprite() {}

private:
	int width;
	int height;
};

