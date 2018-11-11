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
#include "pipeline.h"
#include "bullet.h"

#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/glm.hpp>



std::map<std::string, GPUbuffer*> Game::gpu_buffers;
std::map<std::string, unsigned int> Game::shader_pool;
std::vector<Object*> Game::entity_pool;
std::vector<Object*> Game::controllables;
Vehicle* Game::vehicle = nullptr;
std::vector<Lighting*> Game::lightings;



void Game::init(){
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
	GameInitProc::createLightings(&lightings);
}

void Game::runPipeline(){
	/*-------------Update Lighting Environment----------------*/
	Pipeline::EnvironmentUpdater::handleLighting(&lightings);
	/*------------Update Handling Pipeline--------------*/
	Pipeline::Updater::handleControls(&controllables, &entity_pool);
	Pipeline::Updater::handlePhysics(&entity_pool);
	Pipeline::Updater::handlePropertyUpdate(&entity_pool);
	/*---------------Transformation Handler------------------*/
	Pipeline::Transformer::transformAll(&entity_pool, vehicle->viewingCamera());
	/*---------------Check whether object should still exist--------------------*/
	for(std::vector<Object*>::iterator o=entity_pool.begin(); o!=entity_pool.end(); ++o){
		if(!(*o)->isAlive()){
			delete *o;
			entity_pool.erase(o--);
		}
	}
}

void Game::render(){
	Pipeline::Renderer::renderEntities(&entity_pool, &lightings);
}

void Game::free(){
	for(std::map<std::string, GPUbuffer*>::iterator gb=gpu_buffers.begin(); gb!=gpu_buffers.end(); ++gb){
		delete gb->second;
	}
	for(std::vector<Object*>::iterator o=entity_pool.begin(); o!=entity_pool.end(); ++o){
		delete *o;
	}
	for(std::vector<Lighting*>::iterator lit=lightings.begin(); lit!=lightings.end(); ++lit){
		delete *lit;
	}
}
