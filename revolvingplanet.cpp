#include "revolvingplanet.h"
#include "gpubuffer.h"
#include "object.h"
#include "gamesystem.h"
#include "camera.h"

#include <glm/glm.hpp>



float RevolvingPlanet::scale = 15.0f;


RevolvingPlanet::RevolvingPlanet(GPUbuffer const * buffers, unsigned int s, const glm::vec3& p, float si, float rs, const glm::vec3& ro):
Object(buffers, s, p, si*scale), revolution((struct Revolution){rs, ro}){
	//nothing
}


RevolvingPlanet::~RevolvingPlanet(){
	//nothing
}

void RevolvingPlanet::updateProperties(){
	syncProperties();
	geometry.position.current += glm::normalize(glm::cross(geometry.position.current, revolution.axis))*0.1f;
}

void RevolvingPlanet::computeTransformations(const Camera& camera){
	//create references for transformation matrices
	struct ModelTransformation* model = &(transformation.model);
	glm::mat4* view = &(transformation.view);
	glm::mat4* projection = &(transformation.projection);
	glm::mat4 identity;

	/*update transformations (T*R*S*vertex)*/
	//model
	model->scale = glm::scale(identity, geometry.size.current);
	model->translate = glm::translate(identity, geometry.position.current);
	model->overall = model->translate * model->rotate * model->scale;
	//view
	*view = glm::lookAt(camera.pos(), camera.lensPos(), camera.straightUp());
	//projection
	*projection = glm::perspective(glm::radians(camera.fov()), (float)GameSystem::windowW()/(float)GameSystem::windowH(), 0.1f, camera.renderDistance());
}
