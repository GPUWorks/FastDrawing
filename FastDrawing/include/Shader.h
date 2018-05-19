#pragma once
#include <string>
#include <glad/glad.h>
class Shader {

public:
	Shader(const std::string &vertex, const std::string &fragment) {
		this->vertexShaderText = vertex;
		this->fragmentShaderText = fragment;

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

	void Use() //bind a sheder with gluseprogram
	{
		glUseProgram(this->program);
	}

	GLuint program;
private:
	std::string vertexShaderText;
	std::string fragmentShaderText;
};