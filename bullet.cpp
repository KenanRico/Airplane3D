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
	physics_handler.handleAll();
	geometry.position.current += direction * speed;
	computeTransformations(camera);
	applyTransformations();
}

void Bullet::computeTransformations(const Camera& camera){
	//model
	struct ModelTransformation* model = &transformation.model;
	model->scale = glm::scale(model->scale, geometry.size.current/geometry.size.last);
	model->translate = glm::translate(model->translate, geometry.position.current-geometry.position.last);
	model->overall = model->translate * model->rotate * model->scale;
	//view
	transformation.view = glm::lookAt(camera.pos(), camera.lensPos(), camera.straightUp());
	//projection
	transformation.projection = glm::perspective(
		glm::radians(camera.fov()),
		(float)GameSystem::windowW()/(float)GameSystem::windowH(),
		0.1f,
		camera.renderDistance()
	);
}
