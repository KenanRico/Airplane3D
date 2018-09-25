#include "vehicle.h"
#include "camera.h"
#include "gamesystem.h"
#include "eventhandler.h"

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>


Vehicle::Vehicle(
	GPUbuffer const * gb, unsigned int s, const glm::vec3& p, float si,
	const glm::vec3& dir, float mag, float max, float min,
	float mra, float ps, float rs
): 
Object(gb, s, p, si),
velocity((struct Velocity){glm::normalize(dir), mag, max, min}),
control((struct Control){mra, ps, rs}),
cameras(
	(struct Cameras){
		{Camera(40.0f, 250.0f, p, velocity.direction), Camera(60.0f, 250.0f, p, velocity.direction), Camera(60.0f, 250.0f, p, -velocity.direction)},
		&cameras.views[FP]
	}
){
	//nothin
}

Vehicle::~Vehicle(){
	//nothin
}


void Vehicle::update(const Camera& camera){

	/*----update cams------*/
	cameras.views[FP].update(velocity.magnitude);
	cameras.views[TP].update(velocity.magnitude);
	cameras.views[rear].update(velocity.magnitude);

	/*-------update vehicle accordingly-------*/
	//update position
	velocity.direction = cameras.views[FP].coord.front;
	position.current = cameras.views[FP].position;
	cameras.views[TP].position = position.current - velocity.direction*5.0f;
	//model
	transformation.model = glm::translate(transformation.model, position.current-position.last);
	transformation.model = glm::scale(transformation.model, size.current/size.last);
	//view
	transformation.view = glm::lookAt(camera.pos(), camera.lensPos(), camera.straightUp());
	//projection
	transformation.projection = glm::perspective(glm::radians(camera.fov()), (float)GameSystem::windowW()/(float)GameSystem::windowH(), 0.1f, camera.renderDistance());
	//apply trans
	applyTransformations();

	/*-------handle input-------*/
	float& speed = velocity.magnitude;
	if(EventHandler::keyDown(EventHandler::SPACE)){
		speed += 0.002f;
	}else{
		speed -= 0.01f;
	}
	const float& max = velocity.max;
	const float& min = velocity.min;
	if(speed>max){
		speed = max;
	}else if(speed<min){
		speed = min;
	}
	if(EventHandler::keyClicked(EventHandler::C)){
		cameras.current = &cameras.views[(cameras.current-cameras.views+1) % 3];

		//cameras.current = (cameras.current+1 > &cameras.views[rear]) ? &cameras.views[FP] : cameras.current+1;
	}
}

void Vehicle::render() const{
	if(cameras.current!=&cameras.views[FP]){
		Object::render();
		std::cout<<glm::to_string(size.current)<<" "<<glm::to_string(position.current)<<"\n";
	}
}

const Camera& Vehicle::viewingCamera() const{
	return *cameras.current;
}
