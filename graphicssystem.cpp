#include <glad/glad.h>

#include "graphicssystem.h"
#include "gamesystem.h"
#include "eventhandler.h"
#include "shader.h"
#include "logger.h"

#include <vector>

#define _HDR 0



GraphicsSystem::GraphicsSystem():
system_lighting((SystemLighting){LightingState::ON}),
blinn_phong((BlinnPhong){BlinnPhongState::ON}),
gamma((Gamma){GammaCorrectionState::OFF}),
hdr((struct HDR){HDRState::OFF, (unsigned int)(-1), (unsigned int)(-1), (unsigned int)(-1)}){

}

GraphicsSystem::~GraphicsSystem(){
	glDeleteBuffers(1, &hdr.FBO);
	glDeleteTextures(1, &hdr.color_buffer);
}

void GraphicsSystem::setClientShaders(const std::vector<unsigned int>& shaders){
	client_shader_pool = shaders;
}

void GraphicsSystem::init(const std::vector<Object*>& objs, unsigned int shader){
#if _HDR==1
	objects = &objs;
	glGenFramebuffers(1, &hdr.FBO);
	glGenTextures(1, &hdr.color_buffer);
	glBindTexture(GL_TEXTURE_2D, hdr.color_buffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, GameSystem::windowW(), GameSystem::windowH(), 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	hdr.shader = shader;
#endif
}

void GraphicsSystem::update(){
	//lighting
	if(EventHandler::keyDown(EventHandler::L)){
		if(EventHandler::keyDown(EventHandler::ONE) && system_lighting.state!=LightingState::OFF){
			system_lighting.state = LightingState::OFF;
			Logger::toConsole(Logger::L_INFO, "Lighting off");
		}else if(EventHandler::keyDown(EventHandler::TWO) && system_lighting.state!=LightingState::ON){
			system_lighting.state = LightingState::ON;
			Logger::toConsole(Logger::L_INFO, "Lighting on");
		}
	}
	//gamma
	if(EventHandler::keyDown(EventHandler::G)){
		if(EventHandler::keyDown(EventHandler::ONE) && gamma.state!=GammaCorrectionState::OFF){
			gamma.state = GammaCorrectionState::OFF;
			Logger::toConsole(Logger::L_INFO, "Gamma correction off");
		}else if(EventHandler::keyDown(EventHandler::TWO) && gamma.state!=GammaCorrectionState::DEFAULT){
			gamma.state = GammaCorrectionState::DEFAULT;
			Logger::toConsole(Logger::L_INFO, "Gamma correction: default GL gamma correction");
		}else if(EventHandler::keyDown(EventHandler::THREE) && gamma.state!=GammaCorrectionState::CUSTOM){
			gamma.state = GammaCorrectionState::CUSTOM;
			Logger::toConsole(Logger::L_INFO, "Gamma correction: custom gamma correction");
		}
	}
	//blinn phong
	if(EventHandler::keyDown(EventHandler::P)){
		if(EventHandler::keyDown(EventHandler::ONE) && blinn_phong.state!=BlinnPhongState::OFF){
			blinn_phong.state = BlinnPhongState::OFF;
			Logger::toConsole(Logger::L_INFO, "Specular: phong");
		}else if(EventHandler::keyDown(EventHandler::TWO) && blinn_phong.state!=BlinnPhongState::ON){
			blinn_phong.state = BlinnPhongState::ON;
			Logger::toConsole(Logger::L_INFO, "Specular: blinn phong");
		}
	}
	//HDR
	if(EventHandler::keyDown(EventHandler::H)){
		if(EventHandler::keyDown(EventHandler::ONE) && hdr.state!=HDRState::OFF){
			hdr.state = HDRState::OFF;
			Logger::toConsole(Logger::L_INFO, "HDR off");
		}else if(EventHandler::keyDown(EventHandler::TWO) && hdr.state!=HDRState::ON){
			hdr.state = HDRState::ON;
			Logger::toConsole(Logger::L_INFO, "HDR on");
		}
	}

}

void GraphicsSystem::commit() const{

	bool l = system_lighting.state==LightingState::ON;
	bool gc = gamma.state==GammaCorrectionState::CUSTOM;
	gamma.state==GammaCorrectionState::DEFAULT ? glEnable(GL_FRAMEBUFFER_SRGB) : glDisable(GL_FRAMEBUFFER_SRGB);
	bool bp = blinn_phong.state==BlinnPhongState::ON;
#if _HDR==1
	bool h = hdr.state==HDRState::ON;
	if(h){
		glBindFramebuffer(GL_FRAMEBUFFER, hdr.FBO);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//render to hdr shader to get color buffer
		for(std::vector<Object*>::const_iterator obj=objects->begin(); obj!=objects->end(); ++obj){
			const Object& object = **obj;
			Shader::useShader(hdr.shader);
			glBindVertexArray(object.ri.VAO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object.ri.EBO);
			glDrawElements(object.ri.mode, object.ri.indices_count, GL_UNSIGNED_INT, 0);
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
#endif

	for(std::vector<unsigned int>::const_iterator si=client_shader_pool.begin(); si!=client_shader_pool.end(); ++si){
		unsigned int s = *si;
		Shader::useShader(s);
		//lighting, gamma, blinn
		glUniform1i(glGetUniformLocation(s, "lighting"), l);
		glUniform1i(glGetUniformLocation(s, "correct_gamma"), gc);
		glUniform1i(glGetUniformLocation(s, "blinn_phong"), bp);
#if _HDR==1
		//HDR
		if(h){
			//send color buffer to rendering shader
		}
#endif
	}

}

unsigned int GraphicsSystem::getHdrColorBuffer() const{

}
