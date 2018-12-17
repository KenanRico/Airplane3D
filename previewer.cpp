#include <glad/glad.h>

#include "previewer.h"
#include "eventhandler.h"
#include "game.h"
#include "shader.h"

#include <string>
#include <map>
#include <cstring>

Previewer::Previewer(){
	//init default settings
	settings.insert(std::make_pair("previewer_lighting", true));
	settings.insert(std::make_pair("previewer_blinn_phong", true));
	settings.insert(std::make_pair("previewer_correct_gamma", false));
}

Previewer::~Previewer(){}

void Previewer::update(){
	/*****update modes*****/
	//lighting
	if(EventHandler::keyDown(EventHandler::L)){
		if(EventHandler::keyDown(EventHandler::ONE)){
			settings["previewer_lighting"] = false;
		}else if(EventHandler::keyDown(EventHandler::TWO)){
			settings["previewer_lighting"] = true;
		}
	}
	//gamma
	if(EventHandler::keyDown(EventHandler::G)){
		if(EventHandler::keyDown(EventHandler::ONE)){
			glDisable(GL_FRAMEBUFFER_SRGB);
			settings["previewer_correct_gamma"] = false;
		}else if(EventHandler::keyDown(EventHandler::TWO)){
			glEnable(GL_FRAMEBUFFER_SRGB);
			settings["previewer_correct_gamma"] = false;
		}else if(EventHandler::keyDown(EventHandler::THREE)){
			glDisable(GL_FRAMEBUFFER_SRGB);
			settings["previewer_correct_gamma"] = true;
		}
	}
	//blinn phong
	if(EventHandler::keyDown(EventHandler::P)){
		if(EventHandler::keyDown(EventHandler::ONE)){
			settings["previewer_blinn_phong"] = false;
		}else if(EventHandler::keyDown(EventHandler::TWO)){
			settings["previewer_blinn_phong"] = true;
		}
	}

	/*********apply settings*********/
	const std::map<std::string, unsigned int>& shaders = Game::shader_pool;
	for(std::map<std::string, unsigned int>::const_iterator shader=shaders.begin(); shader!=shaders.end(); ++shader){
		unsigned int s = shader->second;
		Shader::useShader(s);
		for(std::map<std::string, bool>::const_iterator setting=settings.begin(); setting!=settings.end(); ++setting){
			glUniform1i(glGetUniformLocation(s, setting->first.c_str()), setting->second);
		}
	}

}
