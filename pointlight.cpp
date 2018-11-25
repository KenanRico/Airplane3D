#include <glad/glad.h>

#include "pointlight.h"
#include "lighting.h"
#include "logger.h"

#include <string>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


int PointLight::index = 0;

PointLight::PointLight(float inten, const Color& col, const glm::vec3* pos, const AttenuationFactors& att):
Lighting(inten, col),
position(pos),
attenuation(att){
	//nothin
}

PointLight::~PointLight(){
	//nothin
}

void PointLight::update(){

}

std::string getLightNameInShader(const std::string&, int);
void PointLight::sendInfoToShader(unsigned int shader) const {
	std::string light_name = getLightNameInShader(std::string("pnt_light"), index);
	glUniform3f(glGetUniformLocation(shader, std::string(light_name+".ambient").c_str()), color.ambient.x, color.ambient.y, color.ambient.z);
	glUniform3f(glGetUniformLocation(shader, std::string(light_name+".diffuse").c_str()), color.diffuse.x, color.diffuse.y, color.diffuse.z);
	glUniform3f(glGetUniformLocation(shader, std::string(light_name+".specular").c_str()), color.specular.x, color.specular.y, color.specular.z);
	glUniform1f(glGetUniformLocation(shader, std::string(light_name+".intensity").c_str()), intensity);
	glUniform3f(glGetUniformLocation(shader, std::string(light_name+".position").c_str()), position->x, position->y, position->z);
	glUniform3f(glGetUniformLocation(shader, std::string(light_name+".attenuation").c_str()), attenuation.k, attenuation.kl, attenuation.kq);
	++index;
}

void PointLight::sendResetIndex(unsigned int shader){
	glUniform1i(glGetUniformLocation(shader, "pl_count"), index);
	index = 0;
}

std::string getLightNameInShader(const std::string& light, int ID){
	static int offset = (int)'0'-0;
	return light+"["+std::string(1,(char)(ID+offset))+"]";
}
