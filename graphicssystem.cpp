#include <glad/glad.h>

#include "graphicssystem.h"
#include "gamesystem.h"
#include "eventhandler.h"
#include "shader.h"

#include <vector>




GraphicsSystem::GraphicsSystem():
system_lighting((SystemLighting){LightingState::ON}),
blinn_phong((BlinnPhong){BlinnPhongState::ON}),
gamma((Gamma){GammaCorrectionState::OFF}),
hdr((HDR){HDRState::OFF, (unsigned int)-1, (unsigned int)-1}){

}

GraphicsSystem::~GraphicsSystem(){
	glDeleteBuffers(1, &hdr.FBO);
	glDeleteTextures(1, &hdr.color_buffer);
}

void GraphicsSystem::setClientShaders(const std::vector<unsigned int>& shaders){
	client_shader_pool = shaders;
}

void GraphicsSystem::initHDR(){
	glGenFramebuffers(1, &hdr.FBO);
	glGenTextures(1, &hdr.color_buffer);
	glBindTexture(GL_TEXTURE_2D, hdr.color_buffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, GameSystem::windowW(), GameSystem::windowH(), 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void GraphicsSystem::update(){
	//lighting
	if(EventHandler::keyDown(EventHandler::L)){
		if(EventHandler::keyDown(EventHandler::ONE)){
			system_lighting.state = LightingState::OFF;
		}else if(EventHandler::keyDown(EventHandler::TWO)){
			system_lighting.state = LightingState::ON;
		}
	}
	//gamma
	if(EventHandler::keyDown(EventHandler::G)){
		if(EventHandler::keyDown(EventHandler::ONE)){
			gamma.state = GammaCorrectionState::OFF;
		}else if(EventHandler::keyDown(EventHandler::TWO)){
			gamma.state = GammaCorrectionState::DEFAULT;
		}else if(EventHandler::keyDown(EventHandler::THREE)){
			gamma.state = GammaCorrectionState::CUSTOM;
		}
	}
	//blinn phong
	if(EventHandler::keyDown(EventHandler::P)){
		if(EventHandler::keyDown(EventHandler::ONE)){
			blinn_phong.state = BlinnPhongState::OFF;
		}else if(EventHandler::keyDown(EventHandler::TWO)){
			blinn_phong.state = BlinnPhongState::ON;
		}
	}
	//HDR
	if(EventHandler::keyDown(EventHandler::H)){
		if(EventHandler::keyDown(EventHandler::ONE)){
			hdr.state = HDRState::OFF;
		}else if(EventHandler::keyDown(EventHandler::TWO)){
			hdr.state = HDRState::ON;
		}
	}

}

void GraphicsSystem::commit() const{
	for(std::vector<unsigned int>::const_iterator si=client_shader_pool.begin(); si!=client_shader_pool.end(); ++si){

		unsigned int s = *si;
		Shader::useShader(s);

		//lighting
		glUniform1i(glGetUniformLocation(s, "lighting"), (system_lighting.state==LightingState::ON));
		//gamma correction
		glUniform1i(glGetUniformLocation(s, "correct_gamma"), (gamma.state==GammaCorrectionState::CUSTOM));
		if(gamma.state==GammaCorrectionState::DEFAULT){
			glEnable(GL_FRAMEBUFFER_SRGB);
		}else{
			glDisable(GL_FRAMEBUFFER_SRGB);
		}
		//blinn phong
		glUniform1i(glGetUniformLocation(s, "blinn_phong"), (blinn_phong.state==BlinnPhongState::ON));
		//HDR

	}
}

unsigned int GraphicsSystem::getHdrColorBuffer() const{

}
