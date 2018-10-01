#include <glad/glad.h>

#include "object.h"
#include "shader.h"
#include "gamesystem.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



#define VERTEX_SIZE 3

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


void Object::update(const Camera& camera){

	//model
	transformation.model = glm::scale(transformation.model, size.current/size.last);
	transformation.model = glm::translate(transformation.model, position.current-position.last);
	//view
	transformation.view = glm::lookAt(camera.pos(), camera.lensPos(), camera.straightUp());
	//projection
	transformation.projection = glm::perspective(glm::radians(camera.fov()), (float)GameSystem::windowW()/(float)GameSystem::windowH(), 0.1f, camera.renderDistance());

	applyTransformations();
}

void Object::applyTransformations(){
	//synchronize positioning and sizing
	position.last = position.current;
	size.last = size.current;

	//apply transformations into shader
	Shader::useShader(shader);
	glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(transformation.model));
	glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, glm::value_ptr(transformation.view));
	glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, glm::value_ptr(transformation.projection));
}

void Object::render() const{
	Shader::useShader(shader);
	glBindVertexArray(ri.VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ri.EBO);
	glDrawElements(ri.mode, ri.indices_count, GL_UNSIGNED_INT, 0);
}
