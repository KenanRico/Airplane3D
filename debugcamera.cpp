#include "debugcamera.h"
#include "camera.h"
#include "eventhandler.h"

#include <glm/glm.hpp>


DebugCamera::DebugCamera(float fo, float d, const glm::vec3& p, const glm::vec3& f):
Camera(fo, d, p, f){

}

DebugCamera::DebugCamera(const DebugCamera& rhs):
Camera(rhs){

}

DebugCamera::~DebugCamera(){

}

void DebugCamera::update(float speed){

	//update coord system
	if(EventHandler::keyDown(EventHandler::W)){
		//move forward
		position += coord.front * speed;
	}
	if(EventHandler::keyDown(EventHandler::A)){
		//lift right vector and change up vector accordingly
		rotate(coord.front, coord.right, coord.up, -0.2f);
	}
	if(EventHandler::keyDown(EventHandler::S)){
		//move backwards
		position -= coord.front * speed;
	}
	if(EventHandler::keyDown(EventHandler::D)){
		//lift right vector and change up vector accordingly
		rotate(coord.front, coord.right, coord.up, 0.2f);
	}

	//update lens
	lens_pos = position + coord.front;

}
