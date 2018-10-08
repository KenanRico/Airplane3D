#include <glad/glad.h>

#include "object.h"
#include "shader.h"
#include "gamesystem.h"
#include "physicshandler.h"

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
geometry((struct GeometricProperties){(struct Position){glm::vec3(0.0f,0.0f,0.0f), p}, (struct Size){glm::vec3(1.0f,1.0f,1.0f), glm::vec3(si, si, si)}}),
physics_handler(this){
	buffers->queryRenderInfo(&ri.VBO, &ri.VAO, &ri.EBO, &ri.indices_count, &ri.mode);
}

Object::~Object(){
	//nothing
}


void Object::update(const Camera& camera){
	physics_handler.handleAll();
	computeTransformations(camera);
	applyTransformations();
}

void Object::computeTransformations(const Camera& camera){
	//model
	struct ModelTransformation* model = &transformation.model;
	model->scale = glm::scale(model->scale, geometry.size.current/geometry.size.last);
	model->translate = glm::translate(model->translate, geometry.position.current-geometry.position.last);
	model->overall = model->translate * model->rotate * model->scale;
	//view
	transformation.view = glm::lookAt(camera.pos(), camera.lensPos(), camera.straightUp());
	//projection
	transformation.projection = glm::perspective(glm::radians(camera.fov()), (float)GameSystem::windowW()/(float)GameSystem::windowH(), 0.1f, camera.renderDistance());
}

void Object::applyTransformations(){
	//synchronize positioning and sizing
	geometry.position.last = geometry.position.current;
	geometry.size.last = geometry.size.current;

	//apply transformations into shader
	Shader::useShader(shader);
	glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(transformation.model.overall));
	glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, glm::value_ptr(transformation.view));
	glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, glm::value_ptr(transformation.projection));
}

void Object::render() const{
	Shader::useShader(shader);
	glBindVertexArray(ri.VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ri.EBO);
	glDrawElements(ri.mode, ri.indices_count, GL_UNSIGNED_INT, 0);
}
