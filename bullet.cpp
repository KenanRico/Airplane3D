#include "bullet.h"
#include "camera.h"
#include "object.h"
#include "gpubuffer.h"
#include "gamesystem.h"

#include <glm/glm.hpp>


Bullet::Bullet(
	GPUbuffer const * gb,
	unsigned int s,
	const glm::vec3& pos,
	float si,
	const glm::vec3& dir,
	float sp,
	float pow
): Object{gb, s, pos, si}, direction(dir), speed(sp), power(pow){
	//nothin
}

Bullet::~Bullet(){
	//nothin
}

void Bullet::update(const Camera& camera){

	/*-----handle physics----*/
	physics_handler.handleAll();

	/*-----update geometry----*/
	geometry.position.current += direction * speed;

	/*-----compute&apply transforamtions----*/
	struct Transformation transformation;
	computeTransformations(camera, &transformation);
	applyTransformations(&transformation);
}

void Bullet::computeTransformations(const Camera& camera, struct Transformation* transformation){
	glm::mat4 identity;
	//model
	struct ModelTransformation* model = &(transformation->model);
	model->scale = glm::scale(identity, geometry.size.current);
	model->translate = glm::translate(identity, geometry.position.current);
	model->overall = model->translate * model->rotate * model->scale;
	//view
	transformation->view = glm::lookAt(camera.pos(), camera.lensPos(), camera.straightUp());
	//projection
	transformation->projection = glm::perspective(
		glm::radians(camera.fov()),
		(float)GameSystem::windowW()/(float)GameSystem::windowH(),
		0.1f,
		camera.renderDistance()
	);
}
