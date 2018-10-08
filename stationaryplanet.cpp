#include <glad/glad.h>

#include "stationaryplanet.h"
#include "shader.h"
#include "camera.h"
#include "gamesystem.h"
#include "gpubuffer.h"
#include "logger.h"

#include <math.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>


float StationaryPlanet::scale = 10.0f;

StationaryPlanet::StationaryPlanet(GPUbuffer const * buffers, unsigned int s, const glm::vec3& p, float si, float rs, const glm::vec3& ro):
Object(buffers, s, p, si*scale), rotation((struct Rotation){rs, ro}){
	//nothing here
}

StationaryPlanet::~StationaryPlanet(){
	//nothing here
}

void StationaryPlanet::update(const Camera& camera){
	physics_handler.handleAll();
	computeTransformations(camera);
	applyTransformations();
}

void StationaryPlanet::computeTransformations(const Camera& camera){
	//create references for transformation matrices
	struct ModelTransformation* model = &transformation.model;
	glm::mat4* view = &transformation.view;
	glm::mat4* projection = &transformation.projection;

	/*update transformations (T*R*S*vertex)*/
	//model
	model->scale = glm::scale(model->scale, geometry.size.current/geometry.size.last);
	model->rotate = glm::rotate(model->rotate, glm::radians(rotation.speed), rotation.orientation);
	model->translate = glm::translate(model->translate, geometry.position.current-geometry.position.last);
	model->overall = model->translate * model->rotate * model->scale;
	//view
	*view = glm::lookAt(camera.pos(), camera.lensPos(), camera.straightUp());
	//projection
	*projection = glm::perspective(glm::radians(camera.fov()), (float)GameSystem::windowW()/(float)GameSystem::windowH(), 0.1f, camera.renderDistance());
}

void StationaryPlanet::render() const{
	Object::render();
}
