#include "camera.h"
#include "eventhandler.h"
#include "logger.h"

#include <math.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>



Camera::Camera(float fo, float d, const glm::vec3& p, const glm::vec3& f):
property((struct CameraProperty){fo, d}),
coord((struct CoordinateSystem){glm::normalize(f), glm::normalize(glm::cross(f,glm::vec3(0.0f,1.0f,0.0f))), glm::cross(coord.front, coord.up)}),
position(p),
lens_pos(p+coord.front){
	coord.right = glm::normalize(glm::cross(coord.front, coord.up));
}

Camera::Camera(const Camera& rhs): property(rhs.property), coord(rhs.coord), position(rhs.position), lens_pos(rhs.lens_pos){

}

Camera::~Camera(){
	//nothing here
}



void Camera::update(float speed){

	//update coord system
	if(EventHandler::keyDown(EventHandler::W)){
		//lift front vector, and change up vector accordingly
		rotate(coord.front, coord.up, coord.right, -0.1f);
	}
	if(EventHandler::keyDown(EventHandler::A)){
		//lift right vector and change up vector accordingly
		rotate(coord.right, coord.up, coord.front, 0.1f);
	}
	if(EventHandler::keyDown(EventHandler::S)){
		//lower front vector, and change up vector accordingly
		rotate(coord.front, coord.up, coord.right, 0.1f);
	}
	if(EventHandler::keyDown(EventHandler::D)){
		//lift right vector and change up vector accordingly
		rotate(coord.right, coord.up, coord.front, -0.1f);
	}


	position += coord.front * speed;

	//update lens
	lens_pos = position + coord.front;
}

const glm::vec3& Camera::pos() const{
	return position;
}

const glm::vec3& Camera::lensPos() const{
	return lens_pos;
}

const glm::vec3& Camera::straightUp() const{
	return coord.up;
}

float Camera::fov() const{
	return property.FOV;
}

float Camera::renderDistance() const{
	return property.render_distance;
}

void Camera::printInfo() const{
	std::string log("Camera position: ");
	log += glm::to_string(position) + std::string("; Camera direction: ") + glm::to_string(coord.front);
	Logger::toConsole(Logger::L_INFO, log);
}


void Camera::rotate(glm::vec3& vec1, glm::vec3& vec2, const glm::vec3& ref, float angle_degree){
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
