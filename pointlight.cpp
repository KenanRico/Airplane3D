#include <glad/glad.h>

#include "pointlight.h"
#include "lighting.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



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

void PointLight::sendInfoToShader(unsigned int shader) const {
	glUniform3f(glGetUniformLocation(shader, "pnt_light.ambient"), color.ambient.x, color.ambient.y, color.ambient.z);
	glUniform3f(glGetUniformLocation(shader, "pnt_light.diffuse"), color.diffuse.x, color.diffuse.y, color.diffuse.z);
	glUniform3f(glGetUniformLocation(shader, "pnt_light.specular"), color.specular.x, color.specular.y, color.specular.z);
	glUniform1f(glGetUniformLocation(shader, "pnt_light.intensity"), intensity);
	glUniform3f(glGetUniformLocation(shader, "pnt_light.position"), position->x, position->y, position->z);
	glUniform3f(glGetUniformLocation(shader, "pnt_light.attenuation"), attenuation.k, attenuation.kl, attenuation.kq);
}
