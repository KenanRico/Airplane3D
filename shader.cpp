#include <glad/glad.h>

#include "shader.h"
#include "logger.h"

#include <cstring>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>


unsigned int Shader::initShaders(const char* v_shader, const char* f_shader){
	unsigned int vertexShader = 0;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	std::string vShaderSource("");
	std::fstream vfs(v_shader, std::ios::in);
	if(vfs.is_open()){
		std::string line("");
		while(getline(vfs, line)){
			vShaderSource = vShaderSource+line+"\n";
		}
		std::string msg("Loaded vertex shader from ");
		msg += std::string(v_shader);
		Logger::toConsole(Logger::L_INFO, msg);
	}else{
		std::string msg("Could not open ");
		msg += std::string(v_shader);
		Logger::toConsole(Logger::L_ERROR, msg);
	}
	vfs.close();
	const char* vertexShaderSource = vShaderSource.c_str();
	glShaderSource(vertexShader, 1, &vertexShaderSource, (GLint*)0);
	glCompileShader(vertexShader);
	
	int success = 0;
	char infoLog[512]{};
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if(success){
		std::string msg("Compiled vertex shader ");
		msg += std::string(v_shader);
		Logger::toConsole(Logger::L_INFO, msg);
	}else{
		glGetShaderInfoLog(vertexShader, 512, (GLsizei*)0, infoLog);
		std::string msg("Cannot compile vertext shader for ");
		msg += std::string(v_shader);
		Logger::toConsole(Logger::L_ERROR, msg);
	}

	unsigned int fragmentShader = 0;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	std::string fShaderSource("");
	std::fstream ffs(f_shader, std::ios::in);
	if(ffs.is_open()){
		std::string line("");
		while(getline(ffs, line)){
			fShaderSource = fShaderSource+line+"\n";
		}
		std::string msg("Loaded fragment shader from ");
		msg += std::string(f_shader);
		Logger::toConsole(Logger::L_INFO, msg);
	}else{
		std::string msg("Could not open ");
		msg += std::string(f_shader);
		Logger::toConsole(Logger::L_ERROR, msg);
	}
	ffs.close();
	const char* fragmentShaderSource = fShaderSource.c_str();
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, (GLint*)0);
	glCompileShader(fragmentShader);
	char infoLog2[512]{};
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if(success){
		std::string msg("Compiled fragment shader ");
		msg += std::string(f_shader);
		Logger::toConsole(Logger::L_INFO, msg);
	}else{
		glGetShaderInfoLog(vertexShader, 512, (GLsizei*)0, infoLog2);
		std::string msg("Cannot compile fragment shader for ");
		msg += std::string(f_shader);
		Logger::toConsole(Logger::L_ERROR, msg);
	}

	unsigned int ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return ID;
}

unsigned int Shader::initShaders(const std::string& v_shader, const std::string& f_shader){
	return initShaders(v_shader.c_str(), f_shader.c_str());
}

void Shader::useShader(unsigned int shader_ID){
	glUseProgram(shader_ID);
}
