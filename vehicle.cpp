#include "vehicle.h"
#include "camera.h"
#include "gamesystem.h"
#include "eventhandler.h"
#include "logger.h"
#include "bullet.h"

#include <math.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>


Vehicle::Vehicle(
	GPUbuffer const * gb, unsigned int s, const glm::vec3& p, float si,
	const glm::vec3& _front, float mag, float max, float min,
	float mra, float ps, float rs
): 
Object(gb, s, p, si),
orientation(
	(struct Orientation){
		glm::normalize(_front),
		glm::normalize(glm::cross(_front, glm::vec3(1.0f, 1.0f, 1.0f))),
		glm::normalize(glm::cross(orientation.front, orientation.up))
	}
),
velocity((struct Velocity){mag, max, min}),
controller((struct Control){mra, ps, rs}),
cameras(
	(struct Cameras){
		{Camera(40.0f, 250.0f, p, orientation.front), Camera(60.0f, 350.0f, p, orientation.front), Camera(60.0f, 250.0f, p, -orientation.front)},
		&cameras.views[FP]
	}
){
	//nothin
}

Vehicle::~Vehicle(){
	//nothin
}


void rotate(glm::vec3&, glm::vec3&, const glm::vec3&, float);

void Vehicle::updateProperties(){
	syncProperties();
	geometry.position.current += velocity.magnitude * orientation.front;
	float& speed = velocity.magnitude;
	speed -= 0.003f;
	const float& max = velocity.max;
	const float& min = velocity.min;
	if(speed>max){
		speed = max;
	}else if(speed<min){
		speed = min;
	}
	Camera* fp = &cameras.views[FP];
	Camera* tp = &cameras.views[TP];
	Camera* r = &cameras.views[rear];
	fp->position = geometry.position.current;
	fp->coord.front = orientation.front;
	fp->coord.up = orientation.up;
	fp->coord.right = orientation.right;
	fp->lens_pos = fp->position + fp->coord.front;
	tp->position = geometry.position.current - orientation.front*(15.0f+velocity.magnitude*20.0f);
	tp->coord.front = orientation.front;
	tp->coord.up = orientation.up;
	tp->coord.right = orientation.right;
	tp->lens_pos = tp->position + tp->coord.front;
	r->position = geometry.position.current;
	r->coord.front = -orientation.front;
	r->coord.up = orientation.up;
	r->coord.right = -orientation.right;
	r->lens_pos = r->position + r->coord.front;
}

const Camera& Vehicle::viewingCamera() const{
	return *cameras.current;
}

const Camera& Vehicle::fpCamera() const{
	return cameras.views[FP];
}

const Camera& Vehicle::tpCamera() const{
	return cameras.views[TP];
}

const Camera& Vehicle::rearCamera() const{
	return cameras.views[rear];
}


void Vehicle::computeTransformations(const Camera& camera){

	glm::mat4 identity;

	//model
	struct ModelTransformation* model = &(transformation.model);
	model->scale = glm::scale(identity, geometry.size.current);
	model->rotate = glm::rotate(identity, acos(glm::dot(glm::vec3(0.0f,0.0f,-1.0f), orientation.front)), orientation.right);
	model->rotate = glm::rotate(model->rotate, acos(glm::dot(glm::vec3(0.0f,1.0f,0.0f), orientation.up)), orientation.front);
	model->rotate = glm::rotate(model->rotate, acos(glm::dot(glm::vec3(1.0f,0.0f,0.0f), orientation.front)), orientation.up);
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

void Vehicle::control(std::vector<Object*>* objects){
	/*-------handle input, update object-------*/
	if(EventHandler::keyDown(EventHandler::W)){
		rotate(orientation.front, orientation.up, orientation.right, -0.3f);
	}
	if(EventHandler::keyDown(EventHandler::A)){
		rotate(orientation.right, orientation.up, orientation.front, 0.3f);
	}
	if(EventHandler::keyDown(EventHandler::S)){
		rotate(orientation.front, orientation.up, orientation.right, 0.3f);
	}
	if(EventHandler::keyDown(EventHandler::D)){
		rotate(orientation.right, orientation.up, orientation.front, -0.3f);
	}
	float& speed = velocity.magnitude;
	if(EventHandler::keyDown(EventHandler::SPACE)){
		speed += 0.004f;
	}
	if(EventHandler::keyClicked(EventHandler::C)){
		cameras.current = &cameras.views[(cameras.current-cameras.views+1) % 3];
	}
	if(EventHandler::keyClicked(EventHandler::J)){
		objects->push_back(new Bullet(geometry.position.current, 1.0f, orientation.front, velocity.magnitude+0.1f, 100.0f, this));
	}
}

void rotate(glm::vec3& vec1, glm::vec3& vec2, const glm::vec3& ref, float angle_degree){
	//define 3x3 identity matrix
	glm::mat3 identity = glm::mat3();
	//define 3x3 lever matrix
	float L[9] = {0.0f,ref.z,-ref.y, -ref.z,0.0f,ref.x, ref.y,-ref.x,0.0f};
	glm::mat3 lever(glm::make_mat3(L));
	//degree to radian
	float angle = glm::radians(angle_degree);
	vec1 = glm::normalize(vec1 * (identity+sin(angle)*lever+(1-cos(angle))*(lever*lever)));
	vec2 = glm::normalize(vec2 * (identity+sin(angle)*lever+(1-cos(angle))*(lever*lever)));
}
