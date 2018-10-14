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
physics_handler(this){
	buffers->queryRenderInfo(&ri.VBO, &ri.VAO, &ri.EBO, &ri.indices_count, &ri.mode);
	geometry.position.last = glm::vec3(0.0f,0.0f,0.0f);
	geometry.position.current = p;
	geometry.size.last = glm::vec3(1.0f,1.0f,1.0f);
	geometry.size.current = glm::vec3(si, si, si);
	geometry.rotation.last = 0.0f;
	geometry.rotation.current = 0.0f;
}

Object::~Object(){
	//nothing
}


void Object::update(const Camera& camera){

	/*-----handle physics----*/
	physics_handler.handleAll();
	
	/*-----compute&apply transforamtions----*/
	struct Transformation transformation;
	computeTransformations(camera, &transformation);
	applyTransformations(&transformation);
}

void Object::computeTransformations(const Camera& camera, struct Transformation* transformation){
	glm::mat4 identity;
	transformation->model.scale = glm::scale(identity, geometry.size.current);
	transformation->model.translate = glm::translate(identity, geometry.position.current);
	transformation->model.overall = transformation->model.translate * transformation->model.rotate * transformation->model.scale;
	transformation->view = glm::lookAt(camera.pos(), camera.lensPos(), camera.straightUp());
	transformation->projection = glm::perspective(glm::radians(camera.fov()), (float)GameSystem::windowW()/(float)GameSystem::windowH(), 0.1f, camera.renderDistance());

}

void Object::applyTransformations(struct Transformation const * transformation){
	//synchronize positioning and sizing
	geometry.position.last = geometry.position.current;
	geometry.rotation.last = geometry.rotation.current;
	geometry.size.last = geometry.size.current;

	//apply transformations into shader
	Shader::useShader(shader);
	glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(transformation->model.overall));
	glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, glm::value_ptr(transformation->view));
	glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, glm::value_ptr(transformation->projection));
}

void Object::render() const{
	Shader::useShader(shader);
	glBindVertexArray(ri.VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ri.EBO);
	glDrawElements(ri.mode, ri.indices_count, GL_UNSIGNED_INT, 0);
}
