#include "Mesh.h"
#include "../include/Sprite.h"
#include "Window.h"




int main(int argc, char* args[])
{
	Window window = Window("test", 800, 600);
	Camera camera = Camera();

	std::vector<Vertex> vertices;
	Vertex v1 = { 1.0f, 1.0f, 0.0f,			1.0f,0.0f };
	Vertex v2 = { 1.0f, -1.0f, 0.0f,		1.0f,1.0f};
	Vertex v3 = { -1.0f, -1.0f, 0.0f,		0.0f,1.0f};
	Vertex v4 = { -1.0f,  1.0f, 0.0f,		0.0f, 0.0f };
			

	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);
	vertices.push_back(v4);
	

	std::string vertex = "#version 330 core\n"
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
		"}\n";

	std::string fragment = "#version 330 core\n"
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
		"}\n";

	Mesh mesh = Mesh(vertex, fragment);
	mesh.SetVertices(vertices);
	mesh.Bind();
	mesh.SetTintColor(BLUE);
	/*mesh.pivot = glm::vec3(-0.5f, -1, 0);*/
	mesh.position = glm::vec3(100, 100, 0);
	mesh.rotation = glm::vec3(0, 0, 0);
	mesh.scale += glm::vec3(50, 50, 100);

	Mesh mesh2 = Mesh(vertex, fragment);
	mesh2.SetVertices(vertices);
	mesh2.SetTintColor(RED);
	mesh2.Bind();
	mesh2.position = glm::vec3(2.0f, 2.0f,0);
	mesh2.scale = glm::vec3(1, 2, 1);


	Texture tex = Texture("D:/UNITY/3 anno/FastDrawing/FastDrawing/Assets/mario.png");
	Sprite sprite = Sprite(100, 50);
	sprite.position = glm::vec3(150.0f, 150.0f, 0.0f);
	while (window.IsOpened()) {

		window.Clear();

		sprite.DrawSolidColor(RED);
		//mesh.DrawSolidColor(RED);
		//mesh.DrawTexture(&tex);
		//mesh2.DrawTexture(&tex);

		glfwPollEvents();
		window.Blit();
	}
}
