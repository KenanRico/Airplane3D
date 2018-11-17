#include <glad/glad.h>

#include "gpubuffer.h"


GPUbuffer::GPUbuffer(
	float const * vertices, unsigned int v_size, unsigned int v_dimension,
	float const * normals, unsigned int n_size, unsigned int n_dimension,
	unsigned int const * indices, unsigned int i_size, unsigned int i_count,
	GLenum m
): indices_count(i_count), mode(m){
	//generate VBO (vertex buffer object), assign VB ID, and copy vertex data into VBO
	glGenBuffers(1, &(VBO.vID));
	glBindBuffer(GL_ARRAY_BUFFER, VBO.vID);
	glBufferData(GL_ARRAY_BUFFER, v_size, vertices, GL_STATIC_DRAW);
	glGenBuffers(1, &(VBO.nID));
	glBindBuffer(GL_ARRAY_BUFFER, VBO.nID);
	glBufferData(GL_ARRAY_BUFFER, n_size, normals, GL_STATIC_DRAW);
	//generate VAO and bind to it to create attrib pointers(vertex array object)
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	//bind VBO and VAO
	//set vertex att pointers
	glBindBuffer(GL_ARRAY_BUFFER, VBO.vID);
	glVertexAttribPointer(0, v_dimension, GL_FLOAT, GL_FALSE, v_dimension*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO.nID);
	glVertexAttribPointer(1, n_dimension, GL_FLOAT, GL_FALSE, n_dimension*sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	//generate EBO (element buffer object), assign ID, and copy element data into EBO
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, i_size, indices, GL_STATIC_DRAW);
}

GPUbuffer::GPUbuffer(
	float const * vertices, unsigned int v_size, unsigned int v_dimension,
	unsigned int const * indices, unsigned int i_size, unsigned int i_count,
	GLenum m
): indices_count(i_count), mode(m){
	//generate VBO (vertex buffer object), assign VB ID, and copy vertex data into VBO
	glGenBuffers(1, &(VBO.vID));
	glBindBuffer(GL_ARRAY_BUFFER, VBO.vID);
	glBufferData(GL_ARRAY_BUFFER, v_size, vertices, GL_STATIC_DRAW);
	//generate VAO and bind to it to create attrib pointers(vertex array object)
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	//bind VBO and VAO
	//set vertex att pointers
	glBindBuffer(GL_ARRAY_BUFFER, VBO.vID);
	glVertexAttribPointer(0, v_dimension, GL_FLOAT, GL_FALSE, v_dimension*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//generate EBO (element buffer object), assign ID, and copy element data into EBO
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, i_size, indices, GL_STATIC_DRAW);
}

GPUbuffer::~GPUbuffer(){
	//nothing
	glDeleteBuffers(1, &(VBO.vID));
	glDeleteBuffers(1, &(VBO.nID));
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);
}

void GPUbuffer::queryRenderInfo(unsigned int* ur_VAO, unsigned int* ur_EBO, unsigned int* ur_ic, GLenum* ur_m) const{
 	*ur_VAO = VAO;
	*ur_EBO = EBO;
	*ur_ic = indices_count;
	*ur_m = mode;
}
