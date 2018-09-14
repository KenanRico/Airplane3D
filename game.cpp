#include <glad/glad.h>

#include "game.h"
#include "object.h"
#include "gpubuffer.h"
#include "shader.h"
#include "camera.h"
#include "nonplayableobject.h"
#include "stationaryplanet.h"
#include "logger.h"
#include "eventhandler.h"

#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/glm.hpp>



std::map<const char*, GPUbuffer*> Game::gpu_buffers;
std::vector<NonPlayableObject*> Game::non_playable_objects;
std::vector<Camera*> Game::cameras;
std::vector<Camera*>::const_iterator Game::current_camera = cameras.begin();


void Game::init(){

	//create gpu vertex buffers
	createGPUBuffers();

	//create objects
	loadObjects();

	//create a camera
	cameras.push_back(new Camera(55.0f, 250.0f, 0.001f, 0.1f, glm::vec3(-25.0f, 0.0f, 1.0f)));
	current_camera = cameras.begin();

}

void Game::update(){
	for(std::vector<NonPlayableObject*>::iterator o=non_playable_objects.begin(); o!=non_playable_objects.end(); ++o){
		(*o)->update(**current_camera);
	}
	(*current_camera)->update();
	if(EventHandler::keyDown(EventHandler::LSHIFT)){
		(*current_camera)->printInfo();
	}
}

void Game::render(){
	for(std::vector<NonPlayableObject*>::iterator o=non_playable_objects.begin(); o!=non_playable_objects.end(); ++o){
		(*o)->render();
	}
}

void Game::free(){
	for(std::map<const char*, GPUbuffer*>::iterator gb=gpu_buffers.begin(); gb!=gpu_buffers.end(); ++gb){
		delete gb->second;
	}
	for(std::vector<NonPlayableObject*>::iterator o=non_playable_objects.begin(); o!=non_playable_objects.end(); ++o){
		delete *o;
	}
	for(std::vector<Camera*>::iterator c=cameras.begin(); c!=cameras.end(); ++c){
		delete *c;
	}
}







void loadObjects(){
	//load conf file
	std::ifstream fs("objectconfigs/obj.conf", std::ios::in);
	//define vertices and indices data
	float cube[] = {
		-1.0f,1.0f,1.0f,
		1.0f,1.0f,1.0f,
		-1.0f,-1.0f,1.0f,
		1.0f,-1.0f,1.0f,
		-1.0f,1.0f,-1.0f,
		1.0f,1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		1.0f,-1.0f,-1.0f
	};
	//unsigned int c_indices[] = {0,1,2, 1,2,3, 4,5,6, 5,6,7, 0,4,2, 4,2,6, 1,3,5, 3,5,7};
	unsigned int c_indices[] = {0,1,3,2,0,4,6,2,3,7,6,4,5,7,5,1,5,4};
	//parse file
	std::string line("line");
	while(std::getline(fs, line)){
		std::stringstream ss(line);
		std::string type("");
		ss>>type;
		if(type=="Planet"){
			//declare object fields to be parsed into from line
			glm::vec3 pos = glm::vec3();
			float size = 0.0f;
			float rotation_speed = 0.0f;
			glm::vec3 rotation_orientation = glm::vec3();
			//parse into above fields
			ss>>pos.x>>pos.y>>pos.z>>size>>rotation_speed>>rotation_orientation.x>>rotation_orientation.y>>rotation_orientation.z;
			//std::cout<<pos.x<<" "<<pos.y<<" "<<pos.z<<" "<<size<<"\n";
			unsigned int s1 = Shader::initShaders("shaders/VShader.glsl", "shaders/FShader.glsl");
			Game::non_playable_objects.push_back(
				new StationaryPlanet(
					Game::gpu_buffers["rectangle frame"], s1, pos, size, rotation_speed, glm::normalize(rotation_orientation)
				)
			);
		}else{

		}
	}
	fs.close();
}

void createGPUBuffers(){
	//rectangle frame
	float v0[] = {
		-1.0f,1.0f,1.0f,
		1.0f,1.0f,1.0f,
		-1.0f,-1.0f,1.0f,
		1.0f,-1.0f,1.0f,
		-1.0f,1.0f,-1.0f,
		1.0f,1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		1.0f,-1.0f,-1.0f
	};
	unsigned int i0[] = {0,1,3,2,0,4,6,2,3,7,6,4,5,7,5,1,5,4};
	GLenum m0 = GL_LINE_LOOP;
	Game::gpu_buffers.insert(
		std::make_pair("rectangle frame", new GPUbuffer(v0, sizeof(v0), 3, i0, sizeof(i0), sizeof(i0)/sizeof(unsigned int), m0))
	);
	//piramid frame
	float v1[] = {
		0.0f,1.0f,0.0f,
		-1.0f,-1.0f,0.0f,
		1.0f,-1.0f,0.0f,
		0.0f,0.0f,-1.0f
	};
	unsigned int i1[] = {0,1,2,0,3,1,2,3};
	GLenum m1 = GL_LINE_LOOP;
	Game::gpu_buffers.insert(
		std::make_pair("piramid frame", new GPUbuffer(v1, sizeof(v1), 3, i1, sizeof(i1), sizeof(i1)/sizeof(unsigned int), m1))
	);
}
