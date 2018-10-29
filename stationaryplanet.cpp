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
Object(buffers, s, p, si*scale), rotation_speed(rs){
	geometry.rotation.orientation = ro;
}

StationaryPlanet::~StationaryPlanet(){
	//nothing here
}


void StationaryPlanet::updateProperties(){
	syncProperties();
	/*-----update geometry----*/
	geometry.rotation.current += rotation_speed;
}

void StationaryPlanet::computeTransformations(const Camera& camera){
	//create references for transformation matrices
	struct ModelTransformation* model = &(transformation.model);
	glm::mat4* view = &(transformation.view);
	glm::mat4* projection = &(transformation.projection);
	glm::mat4 identity;

	/*update transformations (T*R*S*vertex)*/
	//model
	model->scale = glm::scale(identity, geometry.size.current);
	model->rotate = glm::rotate(identity, glm::radians(geometry.rotation.current), geometry.rotation.orientation);
	model->translate = glm::translate(identity, geometry.position.current);
	model->overall = model->translate * model->rotate * model->scale;
	//view
	*view = glm::lookAt(camera.pos(), camera.lensPos(), camera.straightUp());
	//projection
	*projection = glm::perspective(glm::radians(camera.fov()), (float)GameSystem::windowW()/(float)GameSystem::windowH(), 0.1f, camera.renderDistance());
}
