#include "Mesh.h"

Mesh::Mesh(std::string vertexShaderText, std::string fragmentShaderText)
{
	this->vertexShaderText = vertexShaderText;
	this->fragmentShaderText = fragmentShaderText;


	//creating vertex shader
	this->vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	//assign text to vertex shader
	const char* vertexText = this->vertexShaderText.c_str();
	glShaderSource(this->vertexShaderID, 1, &vertexText, nullptr);
	//compiling vertex shader
	glCompileShader(this->vertexShaderID);

	//check vertex shader compilation
	GLint isVertexCompiled;
	glGetShaderiv(this->vertexShaderID, GL_COMPILE_STATUS, &isVertexCompiled);
	if (isVertexCompiled == GL_FALSE)
	{
		//compilation failed
		throw std::exception("Vertex shader compilation failed");
	}
	


	//creating fragment shader
	this->fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	//assign text to fragment shader
	const char* fragmentText = this->fragmentShaderText.c_str();
	glShaderSource(this->fragmentShaderID, 1, &fragmentText, nullptr);
	//compiling fragment shader
	glCompileShader(this->fragmentShaderID);

	//check fragment shader compilation
	GLint isFragmentCompiled;
	glGetShaderiv(this->fragmentShaderID, GL_COMPILE_STATUS, &isFragmentCompiled);
	if (isFragmentCompiled == GL_FALSE)
	{
		//compilation failed
		throw std::exception("Fragment shader compilation failed");
	}


	//create program with shaders
	this->program = glCreateProgram();
	glAttachShader(this->program, this->vertexShaderID);
	glAttachShader(this->program, this->fragmentShaderID);
	glLinkProgram(this->program);

}


Mesh::~Mesh()
{
}

void Mesh::SetVertices(std::vector<Vertex> vertices) {

	this->vertices = vertices;
}

void Mesh::Bind() {

	glGenBuffers(1, &this->vertexBuffer);
	
	glGenVertexArrays(1, &this->vertexArray);
	glBindVertexArray(this->vertexArray);
	
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) *3 *this->vertices.size(), &this->vertices[0], GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);

}

void Mesh::Draw() {

	glUseProgram(this->program);
	glBindVertexArray(this->vertexArray);
	glDrawArrays(GL_TRIANGLES, 0, this->vertices.size() * 3);
}

