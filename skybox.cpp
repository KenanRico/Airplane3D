#include <glad/glad.h>

#include "skybox.h"
#include "gpubuffer.h"
#include "camera.h"
#include "gamesystem.h"
#include "logger.h"

#include <cstring>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif
#include <stb_image.h>


Skybox::Skybox(): texture_ID(-1){

}

Skybox::~Skybox(){
	if(texture_ID!=(unsigned int)-1){
		glDeleteTextures(1, &texture_ID);
	}
}

void Skybox::initialize(GPUbuffer const * gb, unsigned int s){
	//assign shader
	shader = s;
	//get skybox buffers
	gb->queryRenderInfo(&ri.VAO, &ri.EBO, &ri.indices_count, &ri.mode);
	//gen texture
	glGenTextures(1, &texture_ID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture_ID);
	std::string faces[6] = {"assets/right.png", "assets/left.png", "assets/top.png", "assets/bot.png", "assets/front.png", "assets/back.png", };
	for(int i=0; i<6; ++i){
		int w= 0;
		int h = 0;
		int nr_channels = 0;
		unsigned char* data = stbi_load(faces[i].c_str(), &w, &h, &nr_channels, 0);
		if(data!=nullptr){
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i, 0, GL_SRGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			Logger::toConsole(Logger::L_INFO, std::string("Loaded skybox texture data for " + faces[i]));
		}else{
			Logger::toConsole(Logger::L_ERROR, std::string("Failed to load skybox texture data for " + faces[i]));
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void Skybox::computeTransformations(const Camera& camera){
	glm::mat4 identity;
	//transformation.model.scale = glm::scale(identity, geometry.size.current);
	transformation.model.overall = glm::translate(identity, camera.pos());
	//transformation.model.overall = transformation.model.translate * transformation.model.rotate * transformation.model.scale;
	transformation.view = glm::mat4(glm::mat3(glm::lookAt(camera.pos(), camera.lensPos(), camera.straightUp())));
	transformation.projection = glm::perspective(
		glm::radians(camera.fov()), (float)GameSystem::windowW()/(float)GameSystem::windowH(), 0.1f, camera.renderDistance()
	);
}
