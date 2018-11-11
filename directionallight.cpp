#include "directionallight.h"
#include "lighting.h"

#include <glm/glm.hpp>



DirectionalLight::DirectionalLight(float _intensity, const struct Color& _color, const glm::vec3& dir):
Lighting(_intensity, _color),
direction(dir){}

DirectionalLight::~DirectionalLight(){}

void DirectionalLight::update(){

}

void DirectionalLight::sendInfoToShader(unsigned int shader){
	unsigned int ambient = glGetUniformLocation(shader, "d_light.ambient");
	glUniform3f(ambient, color.ambient.x, color.ambient.y, color.ambient.z);
	unsigned int diffuse = glGetUniformLocation(shader, "d_light.diffuse");
	glUniform3f(diffuse, color.diffuse.x, color.diffuse.y, color.diffuse.z);
	unsigned int specular = glGetUniformLocation(shader, "d_light.specular");
	glUniform3f(specular, color.specular.x, color.specular.y, color.specular.z);
	unsigned int shading_intensity = glGetUniformLocation(shader, "d_light.intensity");
	glUniform1f(shading_intentity, intensity);
	unsigned int shading_direction = glGetUniformLocation(shader, "d_light.direction");
	glUniform3f(shading_direction, direction.x, direction.y, direction.z);
}
