#include "pointlight.h"
#include "lighting.h"

#include <glm/glm.hpp>



PointLight::PointLight(float inten, const Color& col, const glm::vec3& pos, const AttenuationFactors& att):
Lighting(inten, col),
position(pos),
attenuation(att){
	//nothin
}

PointLight::~PointLight(){
	//nothin
}

void PointLight::Update(){

}

void PointLight::sendInfoToShader(unsigned int shader){

}
