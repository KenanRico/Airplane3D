#include <glad/glad.h>

#include "gameinitproc.h"
#include "gpubuffer.h"
#include "object.h"
#include "camera.h"
#include "stationaryplanet.h"
#include "revolvingplanet.h"
#include "shader.h"

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>

#include <iostream>


void GameInitProc::createGPUBuffers(std::map<std::string, GPUbuffer*>* gpu_buffers){
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
	gpu_buffers->insert(
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
	gpu_buffers->insert(
		std::make_pair("piramid frame", new GPUbuffer(v1, sizeof(v1), 3, i1, sizeof(i1), sizeof(i1)/sizeof(unsigned int), m1))
	);
	//marker
	float v2[] = {
		0.0f,1.0f,0.0f,
		-1.0f,0.0f,0.0f,
		0.0f,-1.0f,0.0f,
		1.0f,0.0f,0.0f,
		0.0f,0.0f,1.0f,
		0.0f,0.0f,-1.0f
	};
	unsigned int i2[] = {0,2, 1,3, 4,5};
	GLenum m2 = GL_LINES;
	gpu_buffers->insert(
		std::make_pair("marker", new GPUbuffer(v2, sizeof(v2), 3, i2, sizeof(i2), sizeof(i2)/sizeof(unsigned int), m2))
	);
}


void GameInitProc::createShaders(std::map<std::string, unsigned int>* shader_pool){
	shader_pool->insert(std::make_pair("marker", Shader::initShaders("shaders/Vmarker.glsl", "shaders/Fmarker.glsl")));
	shader_pool->insert(std::make_pair("basic shader", Shader::initShaders("shaders/VShader.glsl", "shaders/FShader.glsl")));
}


void GameInitProc::loadObjects(std::vector<Object*>* planets, const std::map<std::string, GPUbuffer*>& gpu_buffers, const std::map<std::string, unsigned int>& shader_pool){
	//load conf file
	std::ifstream fs("objectconfigs/obj.conf", std::ios::in);
	//parse file
	std::string line("line");
	while(std::getline(fs, line)){
		std::stringstream ss(line);
		std::string type("");
		ss>>type;
		if(type=="roPlanet"){
			//declare object fields to be parsed into from line
			glm::vec3 pos = glm::vec3();
			float size = 0.0f;
			float rotation_speed = 0.0f;
			glm::vec3 rotation_orientation = glm::vec3();
			//parse into above fields
			ss>>pos.x>>pos.y>>pos.z>>size>>rotation_speed>>rotation_orientation.x>>rotation_orientation.y>>rotation_orientation.z;
			unsigned int s = shader_pool.find("basic shader")->second;
			//unsigned int s = Shader::initShaders("shaders/Vshader.glsl", "shaders/Fshader.glsl");
			planets->push_back(
				new StationaryPlanet(
					gpu_buffers.find("piramid frame")->second, s, pos, size, rotation_speed, glm::normalize(rotation_orientation)
				)
			);
		}else if(type=="rePlanet"){
			//declare object fields to be parsed into from line
			glm::vec3 pos = glm::vec3();
			float size = 0.0f;
			float revolution_speed = 0.0f;
			glm::vec3 revolution_orientation = glm::vec3();
			//parse into above fields
			ss>>pos.x>>pos.y>>pos.z>>size>>revolution_speed>>revolution_orientation.x>>revolution_orientation.y>>revolution_orientation.z;
			unsigned int s = shader_pool.find("basic shader")->second;
			//unsigned int s = Shader::initShaders("shaders/Vshader.glsl", "shaders/Fshader.glsl");
			planets->push_back(
				new RevolvingPlanet(
					gpu_buffers.find("rectangle frame")->second, s, pos, size, revolution_speed, glm::normalize(revolution_orientation)
				)
			);
		}else if(type=="marker"){
			//declare object fields to be parsed into from line
			glm::vec3 pos = glm::vec3();
			float size = 0.0f;
			//parse into above fields
			ss>>pos.x>>pos.y>>pos.z>>size;
			unsigned int s = shader_pool.find("marker")->second;
			//unsigned int s = Shader::initShaders("shaders/Vmarker.glsl", "shaders/Fmarker.glsl");
			planets->push_back(
				new Object(
					gpu_buffers.find("marker")->second, s, pos, size
				)
			);
		}else{

		}
	}
	fs.close();
}

void GameInitProc::createLightings(std::vector<Lighting*>* lightings){
	lightings->push_back(new PointLight(...));
	lightings->push_back(new DirectionLight(...));
}

