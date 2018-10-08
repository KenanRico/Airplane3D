#include "game.h"
#include "object.h"
#include "gpubuffer.h"
#include "shader.h"
#include "camera.h"
#include "stationaryplanet.h"
#include "revolvingplanet.h"
#include "logger.h"
#include "eventhandler.h"
#include "gameinitproc.h"
#include "vehicle.h"
#include "debugcamera.h"
#include "physicshandler.h"

#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/glm.hpp>



std::map<std::string, GPUbuffer*> Game::gpu_buffers;
std::vector<Object*> Game::objects;
Vehicle* Game::vehicle = nullptr;



void Game::init(){
	PhysicsHandler::initGlobal(&objects);
	GameInitProc::createGPUBuffers(&gpu_buffers);
	GameInitProc::loadObjects(&objects, gpu_buffers);
	//create controllable object
	vehicle = new Vehicle(
		gpu_buffers.find("rectangle frame")->second,
		Shader::initShaders("shaders/VShader.glsl", "shaders/FShader.glsl"),
		glm::vec3(-4.0, 2.0f, 3.0f), 4.0f, glm::vec3(1.0, 0.0, 0.0),
		0.0f, 0.3f, 0.0f, 50.0f, 0.01f, 0.01f
	);
	vehicle->defineWeapon(gpu_buffers.find("marker")->second, "shaders/VShader.glsl", "shaders/FShader.glsl", 1.0f, 5.0f);
	objects.push_back(vehicle);
}

void Game::update(){
	/*-----update objects and cameras-------*/
	for(std::vector<Object*>::iterator o=objects.begin(); o!=objects.end(); ++o){
		(*o)->update(vehicle->viewingCamera());
	}
	//
}

void Game::render(){
	for(std::vector<Object*>::iterator o=objects.begin(); o!=objects.end(); ++o){
		(*o)->render();
	}
}

void Game::free(){
	for(std::map<std::string, GPUbuffer*>::iterator gb=gpu_buffers.begin(); gb!=gpu_buffers.end(); ++gb){
		delete gb->second;
	}
	for(std::vector<Object*>::iterator o=objects.begin(); o!=objects.end(); ++o){
		delete *o;
	}
}
