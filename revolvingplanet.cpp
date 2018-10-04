#include "revolvingplanet.h"
#include "gpubuffer.h"
#include "object.h"
#include "gamesystem.h"
#include "camera.h"

#include <glm/glm.hpp>

#define MODEL

float RevolvingPlanet::scale = 15.0f;


RevolvingPlanet::RevolvingPlanet(GPUbuffer const * buffers, unsigned int s, const glm::vec3& p, float si, float rs, const glm::vec3& ro):
Object(buffers, s, p, si*scale), revolution((struct Revolution){rs, ro}){
	//nothing
}


RevolvingPlanet::~RevolvingPlanet(){
	//nothing
}

void RevolvingPlanet::update(const Camera& camera){

	//update position
	position.current += glm::normalize(glm::cross(position.current, revolution.axis))*0.1f;
	
	//create references for transformation matrices
	struct ModelTransformation* model = &transformation.model;
	glm::mat4* view = &transformation.view;
	glm::mat4* projection = &transformation.projection;

	/*update transformations (T*R*S*vertex)*/
	//model
#ifdef MODEL
	model->scale = glm::scale(model->scale, size.current/size.last);
	model->translate = glm::translate(model->translate, position.current-position.last);
	model->overall = model->translate * model->rotate * model->scale;
#else
	model = glm::scale(model, size.current/size.last);
	model = glm::translate(model, position.current-position.last);
#endif
	//view
	*view = glm::lookAt(camera.pos(), camera.lensPos(), camera.straightUp());
	//projection
	*projection = glm::perspective(glm::radians(camera.fov()), (float)GameSystem::windowW()/(float)GameSystem::windowH(), 0.1f, camera.renderDistance());

	//apply trans
	applyTransformations();
	
}

void RevolvingPlanet::render() const{
	Object::render();
}
