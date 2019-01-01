#include "bullet.h"
#include "camera.h"
#include "object.h"
#include "gpubuffer.h"
#include "gamesystem.h"
#include "shader.h"

#include <string>
#include <iostream>

#include <glm/glm.hpp>



unsigned int Bullet::shd = -1;


Bullet::Bullet(
	const glm::vec3& pos,
	float si,
	const glm::vec3& dir,
	float sp,
	float pow,
	Object* src
): Object(bullet_shape, shd, pos, si), direction(dir), speed(sp), power(pow), source(src){
	//nothin
}

Bullet::~Bullet(){
	//nothin
}

void Bullet::updateProperties(){
	syncProperties();
	/*-----update geometry----*/
	geometry.position.current += direction * speed;
	if(glm::length(geometry.position.current - source->getGeometry()->position.current)>150.0f){
		exists = false;
	}
}

void Bullet::computeTransformations(const Camera& camera){
	glm::mat4 identity;
	//model
	struct ModelTransformation* model = &(transformation.model);
	model->scale = glm::scale(identity, geometry.size.current);
	model->translate = glm::translate(identity, geometry.position.current);
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
