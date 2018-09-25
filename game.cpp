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

#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/glm.hpp>



std::map<const char*, GPUbuffer*> Game::gpu_buffers;
std::vector<Object*> Game::planets;
Vehicle* Game::vehicle = nullptr;
DebugCamera Game::debug_camera(50.0f, 200.0f, glm::vec3(10.0f, 4.0f, -3.0f), glm::vec3(-1.0f, 0.0f, 0.0f));

Camera const * Game::current_camera = nullptr;



void Game::init(){

	GameInitProc::createGPUBuffers(&gpu_buffers);
	GameInitProc::loadObjects(&planets, gpu_buffers);
	current_camera = &debug_camera;


vehicle = new Vehicle(gpu_buffers.find("rectangle frame")->second, Shader::initShaders("shaders/VShader.glsl", "shaders/FShader.glsl"), glm::vec3(-4.0, 2.0f, 3.0f), 4.0f, glm::vec3(1.0, 0.0, 0.0), 0.0f, 0.1f, 0.0f, 50.0f, 0.01f, 0.01f);

}

void Game::update(){
	if(EventHandler::keyDown(EventHandler::LCTRL) && EventHandler::keyClicked(EventHandler::C)){
		current_camera = (current_camera==&debug_camera) ? &vehicle->viewingCamera() : &debug_camera;
	}

	if(current_camera==&debug_camera){
		debug_camera.update(0.1f);
	}else{
		current_camera = &vehicle->viewingCamera();
		vehicle->update(*current_camera);
	}

	for(std::vector<Object*>::iterator o=planets.begin(); o!=planets.end(); ++o){
		(*o)->update(*current_camera);
	}
	
}

void Game::render(){
	for(std::vector<Object*>::iterator o=planets.begin(); o!=planets.end(); ++o){
		(*o)->render();
	}
	vehicle->render();
}

void Game::free(){
	for(std::map<const char*, GPUbuffer*>::iterator gb=gpu_buffers.begin(); gb!=gpu_buffers.end(); ++gb){
		delete gb->second;
	}
	for(std::vector<Object*>::iterator o=planets.begin(); o!=planets.end(); ++o){
		delete *o;
	}
}


