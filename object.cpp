#include <glad/glad.h>

#include "object.h"
#include "shader.h"
#include "gamesystem.h"

#include <vector>

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
ri((struct RenderInfo){0,0,0}),
shader(s),
exists(true){
	buffers->queryRenderInfo(&ri.VAO, &ri.EBO, &ri.indices_count, &ri.mode);
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


void Object::updateProperties(){
	//do nothing in base class
}

void Object::computeTransformations(const Camera& camera){
	glm::mat4 identity;
	transformation.model.scale = glm::scale(identity, geometry.size.current);
	transformation.model.translate = glm::translate(identity, geometry.position.current);
	transformation.model.overall = transformation.model.translate * transformation.model.rotate * transformation.model.scale;
	transformation.view = glm::lookAt(camera.pos(), camera.lensPos(), camera.straightUp());
	transformation.projection = glm::perspective(
		glm::radians(camera.fov()), (float)GameSystem::windowW()/(float)GameSystem::windowH(), 0.1f, camera.renderDistance()
	);
}

void Object::syncProperties(){
	//synchronize positioning and sizing
	geometry.position.last = geometry.position.current;
	geometry.rotation.last = geometry.rotation.current;
	geometry.size.last = geometry.size.current;
}


struct Object::GeometricProperties* Object::getGeometry(){
	return &geometry;
}

struct Object::PhysicalProperties* Object::getPhysics(){
	return &physics;
}

void Object::control(std::vector<Object*>*){
	//base objects are uncontrollable
}

bool Object::isAlive() const{
	return exists;
}

