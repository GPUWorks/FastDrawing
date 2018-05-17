#include "Mesh.h"
#include "Window.h"




int main(int argc, char* args[])
{
	Window window = Window("test", 400, 400);


	std::vector<Vertex> vertices;
	Vertex v1 = { 0.5f, 0.5f, 0.0f,			1.0f,0.0f };
	Vertex v2 = { 0.5f, -0.5f, 0.0f,		1.0f,1.0f};
	Vertex v3 = { -0.5f, -0.5f, 0.0f,		0.0f,1.0f};
	Vertex v4 = { -0.5f,  0.5f, 0.0f,		0.0f, 0.0f };
			

	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);
	vertices.push_back(v4);
	

	std::string vertex = "#version 330 core\n"
		"layout(location = 0) in vec3 aPos;\n"
		"layout(location = 1) in vec2 aTexCoord;\n"
		"out vec2 TexCoord;\n"
		"void main()\n"
		"{\n"
		"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"TexCoord = aTexCoord;\n"
		"}\n";

	std::string fragment = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"in vec2 TexCoord;\n"
		"uniform sampler2D ourTexture;\n"
		"uniform int useTexture;\n"
		"uniform vec4 ourColor;\n"
		"void main()\n"
		"{\n"
		"if(useTexture == 0) FragColor = ourColor;\n"
		"else FragColor = texture(ourTexture, TexCoord);\n"
		"}\n";

	Mesh mesh = Mesh(vertex, fragment);
	mesh.SetVertices(vertices);
	mesh.Bind();

	Mesh mesh2 = Mesh(vertex, fragment);
	mesh2.SetVertices(vertices);
	mesh2.Bind();

	Texture tex = Texture("D:/UNITY/3 anno/FastDrawing/FastDrawing/Assets/mario.png");

	while (window.IsOpened()) {

		window.Clear();

		mesh.DrawTexture(&tex);
		//mesh2.DrawSolidColor(BLUE);

		glfwPollEvents();
		window.Blit();
	}
}
