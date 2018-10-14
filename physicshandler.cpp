#include "physicshandler.h"
#include "object.h"

#include <vector>

#include <glm/glm.hpp>


float PhysicsHandler::gravity = 0.0f;
std::vector<Object*> const * PhysicsHandler::object_pool = nullptr;

PhysicsHandler::PhysicsHandler(Object* c): client_object(c){
	//nothin
}

PhysicsHandler::~PhysicsHandler(){

}

void PhysicsHandler::initGlobal(std::vector<Object*> const * optr){
	gravity = 9.81f;
	object_pool = optr;
}

void PhysicsHandler::handleAll(){
	//handle gravity
	glm::vec3 overall_force;
	for(std::vector<Object*>::const_iterator obj=object_pool->begin(); obj!=object_pool->end(); ++obj){
		overall_force += ((*obj)->geometry.position.current - client_object->geometry.position.current) * 0.000001f;
	}
	client_object->geometry.position.current += overall_force;

	//handle collisions
	/*
	for(std::vector<Object*>::const_iterator obj=object_pool->begin(); obj!=object_pool->end(); ++obj){
		if(glm::length(client_object->geometry.position.current, (*obj)->geometry.position.current)<=2.0f){
			if(*obj!=client_object){
				
			}
		}
	}
	*/

}
