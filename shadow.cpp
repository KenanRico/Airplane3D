#include <glad/glad.h>

#include "shadow.h"
#include "lighting.h"
#include "object.h"

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const unsigned int Shadow::shadow_width = 1024;
const unsigned int Shadow::shadow_height = 1024;

Shadow::Shadow(Lighting const * src): depth_map_FBO(-1), depth_map(-1), source(src), light_space_mat(glm::mat4()){
	//init FBO
	glGenFramebuffers(1, &depth_map_FBO);
	//init depthmap texture
	glGenTextures(1, &depth_map);
	glBindTexture(GL_TEXTURE_2D, depth_map);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadow_width, shadow_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, (GLvoid const *)0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float border_color[] = {1.0f, 1.0f, 1.0f, 1.0f};
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border_color);
	glBindTexture(GL_TEXTURE_2D, 0);
	//attach depth map as FBO's depth buffer
	glBindFramebuffer(GL_FRAMEBUFFER, depth_map_FBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth_map, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

Shadow::~Shadow(){
	if(depth_map!=(unsigned int)-1){
		glDeleteTextures(1, &depth_map);
	}
}

void Shadow::updateLightSpaceMat(){
	//calc light space
	source->calcLightSpaceMatrix(&light_space_mat);
}

unsigned int Shadow::getDepthMapFBO() const{
	return depth_map_FBO;
}

const glm::mat4& Shadow::getLSM() const{
	return light_space_mat;
}

unsigned int Shadow::getDepthMapTexture() const{
	return depth_map;
}
