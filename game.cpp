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

#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/glm.hpp>



std::map<const char*, GPUbuffer*> Game::gpu_buffers;
std::vector<Object*> Game::planets;
std::vector<Camera*> Game::cameras;
std::vector<Camera*>::const_iterator Game::current_camera = cameras.begin();


void Game::init(){

	GameInitProc::createGPUBuffers(&gpu_buffers);
	GameInitProc::loadObjects(&planets, gpu_buffers);
	GameInitProc::createCameras(&cameras);

	current_camera = cameras.begin();

}

void Game::update(){
	for(std::vector<Object*>::iterator o=planets.begin(); o!=planets.end(); ++o){
		(*o)->update(**current_camera);
	}
	(*current_camera)->update();
	if(EventHandler::keyClicked(EventHandler::LSHIFT)){
		(*current_camera)->printInfo();
	}
}

void Game::render(){
	for(std::vector<Object*>::iterator o=planets.begin(); o!=planets.end(); ++o){
		(*o)->render();
	}
}

void Game::free(){
	for(std::map<const char*, GPUbuffer*>::iterator gb=gpu_buffers.begin(); gb!=gpu_buffers.end(); ++gb){
		delete gb->second;
	}
	for(std::vector<Object*>::iterator o=planets.begin(); o!=planets.end(); ++o){
		delete *o;
	}
	for(std::vector<Camera*>::iterator c=cameras.begin(); c!=cameras.end(); ++c){
		delete *c;
	}
}






