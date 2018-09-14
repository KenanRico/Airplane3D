#include <glad/glad.h>

#include "object.h"
#include "shader.h"
#include "gamesystem.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



#define VERTEX_SIZE 3

/*
Object::Object(
	float* vertices, unsigned int v_size,
	unsigned int* indices, unsigned int i_size, unsigned int i_count,
	unsigned int s,
	const glm::vec3& p,
	float si
):
ri((struct RenderInfo){0,0,0,i_count}),
shader(s),
position((struct Position){glm::vec3(0.0f,0.0f,0.0f), p}),
size((struct Size){glm::vec3(1.0f,1.0f,1.0f), glm::vec3(si, si, si)}){
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
*/
Object::Object(
	GPUbuffer const * buffers,
	unsigned int s,
	const glm::vec3& p,
	float si
):
ri((struct RenderInfo){0,0,0,0}),
shader(s),
position((struct Position){glm::vec3(0.0f,0.0f,0.0f), p}),
size((struct Size){glm::vec3(1.0f,1.0f,1.0f), glm::vec3(si, si, si)}){
	buffers->queryRenderInfo(&ri.VBO, &ri.VAO, &ri.EBO, &ri.indices_count, &ri.mode);
}

Object::~Object(){
	//nothing
}
