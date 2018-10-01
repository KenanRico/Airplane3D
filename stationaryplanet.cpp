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
	
	//create references for transformation matrices
	glm::mat4& model = transformation.model;
	glm::mat4& view = transformation.view;
	glm::mat4& projection = transformation.projection;

	/*update transformations (T*R*S*vertex)*/
	//model
	model = glm::scale(model, size.current/size.last);
	model = glm::rotate(model, glm::radians(rotation.speed), rotation.orientation);
	model = glm::translate(model, position.current-position.last);
	//view
	view = glm::lookAt(camera.pos(), camera.lensPos(), camera.straightUp());
	//projection
	projection = glm::perspective(glm::radians(camera.fov()), (float)GameSystem::windowW()/(float)GameSystem::windowH(), 0.1f, camera.renderDistance());

	//apply transformations
	applyTransformations();
}

void StationaryPlanet::render() const{
	Object::render();
}
