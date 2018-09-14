#include "nonplayableobject.h"
#include "object.h"

#include <glm/glm.hpp>


/*
NonPlayableObject::NonPlayableObject(float* v, unsigned int v_s, unsigned int* i, unsigned int i_s, unsigned int i_c, unsigned int s, const glm::vec3& p, float si):
Object(v, v_s, i, i_s, i_c, s, p, si){
	//nothing here
}
*/
NonPlayableObject::NonPlayableObject(GPUbuffer const * buffers, unsigned int s, const glm::vec3& p, float si):
Object(buffers, s, p, si){
	//nothing here
}

NonPlayableObject::~NonPlayableObject(){
	//nothing here
}
