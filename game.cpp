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
#include "lighting.h"
#include "shadow.h"

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
std::vector<Shadow*> Game::shadows;


void Game::init(){
	GameInitProc::createGPUBuffers(&gpu_buffers);
	GameInitProc::createShaders(&shader_pool);
	GameInitProc::loadObjects(&entity_pool, gpu_buffers, shader_pool);
	Bullet::define(gpu_buffers.find("marker")->second, shader_pool.find("marker")->second);
	GameInitProc::createLightings(&lightings, std::vector<Object*>{entity_pool[19], entity_pool[15], entity_pool[11]});
	GameInitProc::createShadows(&shadows, lightings);
	//create controllable object
	vehicle = new Vehicle(
		gpu_buffers.find("rectangle frame")->second,
		shader_pool.find("basic shader 2")->second,
		glm::vec3(-4.0, 2.0f, 3.0f), 4.0f, glm::vec3(1.0, 0.0, 0.0),
		0.0f, 0.3f, 0.0f, 50.0f, 0.01f, 0.01f
	);
	entity_pool.push_back(vehicle);
	controllables.push_back(vehicle);
	//Shadow::initShadowSystem();
}

void Game::runPipeline(){
	/*------------Update Handling Pipeline--------------*/
	Pipeline::Updater::handleControls(&controllables, &entity_pool);
	Pipeline::Updater::handlePhysics(&entity_pool);
	Pipeline::Updater::handlePropertyUpdate(&entity_pool);
	/*---------------Transformation Handler------------------*/
	Pipeline::Transformer::transformAll(&entity_pool, vehicle->viewingCamera());
	/*-------------Update Lighting Environment----------------*/
	Pipeline::EnvironmentUpdater::handleLighting(&lightings);
	/*-------------Update Shadow Mapping----------------*/
	Pipeline::EnvironmentUpdater::updateShadow(&shadows, entity_pool, shader_pool["shadow shader"]);
	/*---------------Check whether object should still exist--------------------*/
	for(std::vector<Object*>::iterator o=entity_pool.begin(); o!=entity_pool.end(); ++o){
		if(!(*o)->isAlive()){
			delete *o;
			entity_pool.erase(o--);
		}
	}
}

void Game::render(){
	Pipeline::Renderer::renderEntities(&entity_pool, vehicle, &lightings, shadows, vehicle->viewingCamera());
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
	for(std::vector<Shadow*>::iterator shadow=shadows.begin(); shadow!=shadows.end(); ++shadow){
		delete *shadow;
	}
}
