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
#include "pipeline.h"
#include "handlermodule.h"

#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/glm.hpp>

#define OLD 0
#define NEW 1
#define VERSION OLD



std::map<std::string, GPUbuffer*> Game::gpu_buffers;
std::map<std::string, unsigned int> Game::shader_pool;
std::vector<Object*> Game::entity_pool;
std::vector<Object*> Game::controllables;
Vehicle* Game::vehicle = nullptr;
HandlerModule Game::handlers;



void Game::init(){
	PhysicsHandler::initGlobal(&entity_pool);
	GameInitProc::createGPUBuffers(&gpu_buffers);
	GameInitProc::createShaders(&shader_pool);
	GameInitProc::loadObjects(&entity_pool, gpu_buffers, shader_pool);
	Bullet::define(gpu_buffers.find("marker")->second, shader_pool.find("marker")->second);
	//create controllable object
	vehicle = new Vehicle(
		gpu_buffers.find("rectangle frame")->second,
		Shader::initShaders("shaders/VShader.glsl", "shaders/FShader.glsl"),
		glm::vec3(-4.0, 2.0f, 3.0f), 4.0f, glm::vec3(1.0, 0.0, 0.0),
		0.0f, 0.3f, 0.0f, 50.0f, 0.01f, 0.01f
	);
	entity_pool.push_back(vehicle);
	controllables.push_back(vehicle);
}

void Game::runPipeline(){
#if VERSION==OLD
	for(std::vector<Object*>::iterator o=entity_pool.begin(); o!=entity_pool.end(); ++o){
		if(!(*o)->isAlive()){
			delete *o;
			entity_pool.erase(o--);
		}else{
			(*o)->update(vehicle->viewingCamera());
		}
	}
#elif VERSION==NEW
	handlers.handlePhysics(&entities);
	handlers.handleGeometry(&entities);

	transformer.transformAll(&entities);
#endif
	handlers.handleControls(&controllables, &entity_pool);
}

void Game::render(){
#if VERSION==OLD
	for(std::vector<Object*>::iterator o=entity_pool.begin(); o!=entity_pool.end(); ++o){
		(*o)->render();
	}
#elif VERSION==NEW
	Pipeline::Renderer::renderEntities(&entity_pool);
#endif
}

void Game::free(){
	for(std::map<std::string, GPUbuffer*>::iterator gb=gpu_buffers.begin(); gb!=gpu_buffers.end(); ++gb){
		delete gb->second;
	}
	for(std::vector<Object*>::iterator o=entity_pool.begin(); o!=entity_pool.end(); ++o){
		delete *o;
	}
}
