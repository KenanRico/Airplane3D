#include "handlermodule.h"
#include "object.h"

#include <vector>



HandlerModule::HandlerModule(){

}

HandlerModule::~HandlerModule(){

}

void HandlerModule::handlePhysics(std::vector<Object*>* entities_ptr) const{
	std::vector<Object*>::iterator end = entities_ptr->end();
	for(std::vector<Object*>::iterator target = entities_ptr->begin(); target!=end; ++target){
		//update each entity by physics
		struct Object::GeometricProperties* my_geometry = (*target)->getGeometry();
		struct Object::PhysicalProperties* my_physics = (*target)->getPhysics();
		for(std::vector<Object*>::iterator other = entities_ptr->begin(); other!=end; ++other){
			if(target!=other){
				struct Object::GeometricProperties* their_geometry = (*other)->getGeometry();
				struct Object::PhysicalProperties* their_physics = (*other)->getPhysics();
				//gravity
				//my_physics->velocity += (their_geometry->position - my_geometry->position) * their_physics->gravity;
				//collision
			}
		}
	}
}

void HandlerModule::handleControls(std::vector<Object*>* controllables, std::vector<Object*>* entities_ptr) const{
	std::vector<Object*>::iterator end = controllables->end();
	for(std::vector<Object*>::iterator obj = controllables->begin(); obj!=end; ++obj){
		(*obj)->control(entities_ptr);
	}
}

void HandlerModule::handleGeometry(std::vector<Object*>* entities_ptr) const{
	std::vector<Object*>::iterator end = entities_ptr->end();
	for(std::vector<Object*>::iterator obj = entities_ptr->begin(); obj!=end; ++obj){
		//(*obj)->updateGeo();
		struct Object::GeometricProperties* their_geometry = (*obj)->getGeometry();
		struct Object::PhysicalProperties* their_physics = (*obj)->getPhysics();


	}
}
