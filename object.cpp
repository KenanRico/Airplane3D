#include <glad/glad.h>

#include "object.h"
#include "shader.h"
#include "gamesystem.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#define VERTEX_SIZE 3

Object::Object(float* vertices, unsigned int v_size, unsigned int* indices, unsigned int i_size, unsigned int i_count, unsigned int s, const glm::vec3& p):
ri((struct RenderInfo){0,0,0,i_count}),
shader(s),
position((struct Position){glm::vec3(0.0f,0.0f,0.0f), p}){
	//generate VBO (vertex buffer object), assign VB ID, and copy vertex data into VBO
	glGenBuffers(1, &ri.VBO);
	glBindBuffer(GL_ARRAY_BUFFER, ri.VBO);
	glBufferData(GL_ARRAY_BUFFER, v_size, vertices, GL_STATIC_DRAW);
	//generate VAO (vertex array object)
	glGenVertexArrays(1, &ri.VAO);
	//bind VBO and VAO
	glBindBuffer(GL_ARRAY_BUFFER, ri.VBO);
	glBindVertexArray(ri.VAO);
	//set vertex attrib pointers
	glVertexAttribPointer(0, VERTEX_SIZE, GL_FLOAT, GL_FALSE, VERTEX_SIZE*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//generate EBO (element buffer object), assign ID, and copy element data into EBO
	glGenBuffers(1, &ri.EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ri.EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, i_size, indices, GL_STATIC_DRAW);
}

Object::~Object(){
	//free objects?
	glDeleteBuffers(1, &ri.VBO);
	glDeleteBuffers(1, &ri.EBO);
}

void Object::update(const Camera& camera){

	//create references for transformation matrices
	glm::mat4& model = transformation.model;
	glm::mat4& view = transformation.view;
	glm::mat4& projection = transformation.projection;

	//update transformations (T*R*S*vertex)
	model = glm::translate(model, position.current-position.last);
	//model = glm::rotate(model, glm::radians(0.5f), glm::vec3(1.0f, 1.0f, 0.0f));
	view = glm::lookAt(camera.pos(), camera.lensPos(), camera.straightUp());
	projection = glm::perspective(glm::radians(camera.fov()), (float)GameSystem::windowW()/(float)GameSystem::windowH(), 0.1f, camera.renderDistance());
	position.last = position.current;

	//apply transformations into shader
	Shader::useShader(shader);
	glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
}

void Object::render() const{
	Shader::useShader(shader);
	glBindVertexArray(ri.VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ri.EBO);
	glDrawElements(GL_TRIANGLES, ri.indices_count, GL_UNSIGNED_INT, 0);
}
