#include "transformmodule.h"



TransformationModule::TransformationModule(){

}

TransformationModule::~TransformationModule(){

}

void TransformationModule::transformAll(std::vector<Object*>* entities_ptr){
	glm::mat4 identity;
	for(std::vector<Object*>::itertor obj = entities_ptr->begin(); obj!=end; ++obj){
		struct Object::GeometricProperties* geometry = (*obj)->getGeometry();

		//create references for transformation matrices
		struct ModelTransformation model;
		glm::mat4 view;
		glm::mat4 projection;
	
		/*update transformations (T*R*S*vertex)*/
		//model
		model.scale = glm::scale(identity, geometry->size.current);
		model.translate = glm::translate(identity, geometry->position.current);
		model.overall = model.translate * model.rotate * model.scale;
		//view
		view = glm::lookAt(camera.pos(), camera.lensPos(), camera.straightUp());
		//projection
		projection = glm::perspective(glm::radians(camera.fov()), (float)GameSystem::windowW()/(float)GameSystem::windowH(), 0.1f, camera.renderDistance());

		//send transformation to shader
		Shader::useShader((*obj)->getShader());
		glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(model.overall));
		glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	}
}
