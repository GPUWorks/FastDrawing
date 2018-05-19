#include <fstream>
#include <sstream>
#include "../include/Gl_log.h"
#include "../include/Mesh.h"
#include "../include/Window.h"



Mesh::Mesh(Shader* shader)
{
	//initialize scale,pos,rot
	this->position = glm::vec3(0);
	this->rotation = glm::vec3(0);
	this->scale = glm::vec3(1);

	this->shader = shader;
}

void Mesh::SetTintColor(Color color)
{
	this->tintColor = new Color(color);
	this->useTint = true;
}
void Mesh::DisableTint()
{
	this->useTint = false;
}

Mesh::~Mesh()
{
}

void Mesh::SetVertices(std::vector<Vertex> vertices, std::vector<int> indices) {

	this->vertices = vertices;
	this->indices = indices;
}

void Mesh::Bind() {

	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);

	glGenBuffers(1, &this->VBO);
	glGenBuffers(1, &this->indexBuffer);

	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);

	//first: layout position
	//second: size of vertex attributes (3 points)
	//third: what type is vertex
	//fourth: be normalized?
	//5: stride
	//6: offset
	glVertexAttribPointer(LAYOUT_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(LAYOUT_POSITION);

	glVertexAttribPointer(LAYOUT_UV, 2/*2 floats*/, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(LAYOUT_UV);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(int), &this->indices[0], GL_STATIC_DRAW);

}
glm::mat4 Mesh::Transform()
{
	glm::mat4 trans(1.0f);
	trans = glm::translate(trans, this->position);
	trans = glm::rotate(trans, glm::radians(this->rotation.x), glm::vec3(1, 0, 0));	//rotate on x
	trans = glm::rotate(trans, glm::radians(this->rotation.y), glm::vec3(0, 1, 0)); //rotate on y
	trans = glm::rotate(trans, glm::radians(this->rotation.z), glm::vec3(0, 0, 1)); //rotate on z
	trans = glm::scale(trans, this->scale);

	//view
	glm::mat4 viewMatrix = glm::mat4(1.0f);
	viewMatrix = glm::translate(viewMatrix, glm::vec3(0, 0, -3));	//camera position

	


	return trans;
}
void Mesh::DrawSolidColor(Color color)
{
	this->shader->Use();

	//uniforms
	ApplyUniformTransformation();

	int colorUniformLocation = glGetUniformLocation(this->shader->program, "ourColor");
	int usetextureUniformLocation = glGetUniformLocation(this->shader->program, "useTexture");
	glUniform1i(usetextureUniformLocation, 0);
	glUniform4f(colorUniformLocation, color.r, color.g, color.b, color.a);

	int tintUniformLocation = glGetUniformLocation(this->shader->program, "tintColor");
	if (this->useTint) {
		glUniform4f(tintUniformLocation, COLOR_SPLIT_PTR(this->tintColor));
	}
	else {
		glUniform4f(tintUniformLocation, 1, 1, 1, 1);
	}

	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBuffer);
	(glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, nullptr));	//must be vertex n of elements
	//glDrawArrays(GL_TRIANGLES, 0, this->vertices.size());	//must be vertex n of elements
}
void Mesh::DrawTexture(Texture* texture)
{
	this->shader->Use();

	int usetextureUniformLocation = glGetUniformLocation(this->shader->program, "useTexture");
	//int textureUniformLocation = glGetUniformLocation(this->program, "ourTexture");
	glUniform1i(usetextureUniformLocation, 1);	//use texture

	int tintUniformLocation = glGetUniformLocation(this->shader->program, "tintColor");
	if (this->useTint) {
		glUniform4f(tintUniformLocation, COLOR_SPLIT_PTR(this->tintColor));
	}
	else {
		glUniform4f(tintUniformLocation, 1,1,1,1);
	}

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->GetID());
	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBuffer);

	ApplyUniformTransformation();

	/*glm::mat4 pivotMat = glm::mat4(1.0f);
	pivotMat = glm::translate(pivotMat, this->pivot);
	int pivotLocation = glGetUniformLocation(this->program, "pivot");
	glUniformMatrix4fv(pivotLocation, 1, GL_FALSE, glm::value_ptr(pivotMat));*/
	

	(glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, nullptr));	//must be vertex n of elements

}
void Mesh::Draw() {


	this->shader->Use();

	ApplyUniformTransformation();

	int usetextureUniformLocation = glGetUniformLocation(this->shader->program, "useTexture");
	//int textureUniformLocation = glGetUniformLocation(this->program, "ourTexture");
	glUniform1i(usetextureUniformLocation, 0);	//do not use texture

	int tintUniformLocation = glGetUniformLocation(this->shader->program, "tintColor");
	if (this->useTint) {
		glUniform4f(tintUniformLocation, COLOR_SPLIT_PTR(this->tintColor));
	}
	else {
		glUniform4f(tintUniformLocation, 1, 1, 1, 1);
	}

	int colorUniformLocation = glGetUniformLocation(this->shader->program, "ourColor");
	glUniform4f(colorUniformLocation, 1, 1, 0, 1);

	GL_CALL(glBindVertexArray(this->VAO));
	GL_CALL(glDrawArrays(GL_TRIANGLES, 0, this->vertices.size() * 5));

}

void Mesh::ApplyUniformTransformation() {

	glm::mat4 mat = Transform();
	int matUniform = glGetUniformLocation(this->shader->program, "transform");
	glUniformMatrix4fv(matUniform, 1, GL_FALSE, glm::value_ptr(mat));

	//projection
	glm::mat4 projectionMatrix = glm::mat4(1.0f);
	projectionMatrix = Window::current->GetProjectionMatrix();
	int projLocation = glGetUniformLocation(this->shader->program, "projection");
	glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	glm::mat4 view = glm::mat4(1.0f);
	// note that we're translating the scene in the reverse direction of where we want to move
	view = Window::current->currentCamera->GetViewMatrix();
	int loc = glGetUniformLocation(this->shader->program, "view");
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(view));
}
