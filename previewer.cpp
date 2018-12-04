#include <glad/glad.h>

#include "previewer.h"
#include "eventhandler.h"
#include "game.h"
#include "shader.h"

#include <string>
#include <map>



Previewer::Previewer(): gamma(GammaMode::NONE){}

Previewer::~Previewer(){}

void Previewer::update(){
	//update modes
	if(EventHandler::keyDown(EventHandler::G)){
		if(EventHandler::keyDown(EventHandler::ONE)){
			gamma = GammaMode::NONE;
		}else if(EventHandler::keyDown(EventHandler::TWO)){
			gamma = GammaMode::DEFAULT;
		}else if(EventHandler::keyDown(EventHandler::THREE)){
			gamma = GammaMode::CUSTOM;
		}
	}
	//apply modes
	switch(gamma){
		case GammaMode::NONE:
			glDisable(GL_FRAMEBUFFER_SRGB);
			enableShaderGamma(false);
			break;
		case GammaMode::DEFAULT:
			glEnable(GL_FRAMEBUFFER_SRGB);
			enableShaderGamma(false);
			break;
		case GammaMode::CUSTOM:
			glDisable(GL_FRAMEBUFFER_SRGB);
			enableShaderGamma(true);
			break;
		default:
			break;
	}
}

void Previewer::enableShaderGamma(bool enabled) const{
	const std::map<std::string, unsigned int>& shaders = Game::shader_pool;
	for(std::map<std::string, unsigned int>::const_iterator shader=shaders.begin(); shader!=shaders.end(); ++shader){
		unsigned int s = shader->second;
		Shader::useShader(s);
		glUniform1i(glGetUniformLocation(s, "correct_gamma"), enabled);
	}
}
