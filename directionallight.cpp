#include <glad/glad.h>

#include "directionallight.h"
#include "lighting.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


DirectionalLight::DirectionalLight(float _intensity, const struct Color& _color, const glm::vec3& dir):
Lighting(_intensity, _color),
direction(dir){}

DirectionalLight::~DirectionalLight(){}

void DirectionalLight::update(){
}

void DirectionalLight::sendInfoToShader(unsigned int shader) const {
	unsigned int ambient = glGetUniformLocation(shader, "dir_light.ambient");
	glUniform3f(ambient, color.ambient.x, color.ambient.y, color.ambient.z);
	unsigned int diffuse = glGetUniformLocation(shader, "dir_light.diffuse");
	glUniform3f(diffuse, color.diffuse.x, color.diffuse.y, color.diffuse.z);
	unsigned int specular = glGetUniformLocation(shader, "dir_light.specular");
	glUniform3f(specular, color.specular.x, color.specular.y, color.specular.z);
	unsigned int shading_intensity = glGetUniformLocation(shader, "dir_light.intensity");
	glUniform1f(shading_intensity, intensity);
	unsigned int shading_direction = glGetUniformLocation(shader, "dir_light.direction");
	glUniform3f(shading_direction, direction.x, direction.y, direction.z);
}

void DirectionalLight::calcLightSpaceMatrix(glm::mat4* lsm) const{
	glm::mat4 light_proj = glm::ortho(-50.0f, 50.0f, -50.0f, 50.0f, 1.0f, 48.0f);
	glm::mat4 light_view = glm::lookAt(-direction*45.0f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	*lsm = light_proj*light_view;
}
