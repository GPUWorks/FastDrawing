#include "../include/Mesh.h"


Mesh::Mesh(std::string vertexShaderText, std::string fragmentShaderText)
{
	this->vertexShaderText = vertexShaderText;
	this->fragmentShaderText = fragmentShaderText;


	//creating vertex shader
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	//assign text to vertex shader
	const char* vertexText = this->vertexShaderText.c_str();
	glShaderSource(vertexShaderID, 1, &vertexText, nullptr);
	//compiling vertex shader
	glCompileShader(vertexShaderID);

	//check vertex shader compilation
	GLint isVertexCompiled;
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &isVertexCompiled);
	if (isVertexCompiled == GL_FALSE)
	{
		//compilation failed
		throw std::exception("Vertex shader compilation failed");
	}
	


	//creating fragment shader
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	//assign text to fragment shader
	const char* fragmentText = this->fragmentShaderText.c_str();
	glShaderSource(fragmentShaderID, 1, &fragmentText, nullptr);
	//compiling fragment shader
	glCompileShader(fragmentShaderID);

	//check fragment shader compilation
	GLint isFragmentCompiled;
	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &isFragmentCompiled);
	if (isFragmentCompiled == GL_FALSE)
	{
		//compilation failed
		throw std::exception("Fragment shader compilation failed");
	}


	//create program with shaders
	this->program = glCreateProgram();
	glAttachShader(this->program, vertexShaderID);
	glAttachShader(this->program, fragmentShaderID);
	glLinkProgram(this->program);
	
	//free shaders
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);


}


Mesh::~Mesh()
{
}

void Mesh::SetVertices(std::vector<Vertex> vertices) {

	this->vertices = vertices;
}

void Mesh::Bind() {

	glGenBuffers(1, &this->VBO);
	
	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(float) *3, &this->vertices[0], GL_STATIC_DRAW);
	
	//first: layout position
	//second: size of vertex attributes (3 points)
	//third: what type is vertex
	//fourth: be normalized?
	glVertexAttribPointer(LAYOUT_POSITION, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(LAYOUT_POSITION);

}


void Mesh::DrawSolidColor(Color color)
{
	glUseProgram(this->program);
	//uniforms
	int colorUniformLocation = glGetUniformLocation(this->program, "ourColor");
	glUniform4f(colorUniformLocation, color.r, color.g, color.b, color.a);

	glBindVertexArray(this->VAO);
	glDrawArrays(GL_TRIANGLES, 0, this->vertices.size() * 3);
}
void Mesh::Draw() {

	glUseProgram(this->program);
	//uniforms
	int colorUniformLocation = glGetUniformLocation(this->program, "ourColor");
	glUniform4f(colorUniformLocation, 1, 1, 0, 1);

	glBindVertexArray(this->VAO);
	glDrawArrays(GL_TRIANGLES, 0, this->vertices.size() * 3);
}

