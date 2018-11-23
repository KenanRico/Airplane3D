#include <glad/glad.h>

#include "pipeline.h"
#include "object.h"
#include "shader.h"
#include "camera.h"

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


/*---------------------------------------Environment Update--------------------------------------------*/
void Pipeline::EnvironmentUpdater::handleLighting(std::vector<Lighting*>* lightings){
	for(std::vector<Lighting*>::iterator lyt=lightings->begin(); lyt!=lightings->end(); ++lyt){
		(*lyt)->update();
	}
}




/*----------------------------------Update Functions----------------------------------------------*/

void Pipeline::Updater::handlePhysics(std::vector<Object*>* entities_ptr){
	std::vector<Object*>::iterator end = entities_ptr->end();
	for(std::vector<Object*>::iterator target = entities_ptr->begin(); target!=end; ++target){
		//update each entity by physics
		struct Object::GeometricProperties* my_geometry = (*target)->getGeometry();
		struct Object::PhysicalProperties* my_physics = (*target)->getPhysics();
		for(std::vector<Object*>::iterator other = entities_ptr->begin(); other!=end; ++other){
			if(target!=other){
				struct Object::GeometricProperties* their_geometry = (*other)->getGeometry();
				struct Object::PhysicalProperties* their_physics = (*other)->getPhysics();
				//collision
			}
		}
	}
}

void Pipeline::Updater::handleControls(std::vector<Object*>* controllables, std::vector<Object*>* entities_ptr){
	std::vector<Object*>::iterator end = controllables->end();
	for(std::vector<Object*>::iterator obj = controllables->begin(); obj!=end; ++obj){
		(*obj)->control(entities_ptr);
	}
}

void Pipeline::Updater::handlePropertyUpdate(std::vector<Object*>* entities_ptr){
	std::vector<Object*>::iterator end = entities_ptr->end();
	for(std::vector<Object*>::iterator obj = entities_ptr->begin(); obj!=end; ++obj){
		(*obj)->updateProperties();
	}
}




/*-------------------------------------Transform Function-------------------------------------------*/

void Pipeline::Transformer::transformAll(std::vector<Object*>* entities_ptr, const Camera& camera){
	for(std::vector<Object*>::iterator ent=entities_ptr->begin(); ent!=entities_ptr->end(); ++ent){
		(*ent)->computeTransformations(camera);
	}
}





/*-------------------------------------Render Function-------------------------------------------*/

void Pipeline::Renderer::renderEntities(std::vector<Object*> const * entities, std::vector<Lighting*> const * lightings, const Camera& camera){
	std::vector<Object*>::const_iterator end = entities->end();
	for(std::vector<Object*>::const_iterator obj=entities->begin(); obj!=end; ++obj){
		const Object& object = *(*obj);
		//send object data to shader
		unsigned int current_shader = object.shader;
		Shader::useShader(current_shader);
		glUniformMatrix4fv(glGetUniformLocation(current_shader, "model"), 1, GL_FALSE, glm::value_ptr(object.transformation.model.overall));
		glUniformMatrix4fv(glGetUniformLocation(current_shader, "view"), 1, GL_FALSE, glm::value_ptr(object.transformation.view));
		glUniformMatrix4fv(glGetUniformLocation(current_shader, "projection"), 1, GL_FALSE, glm::value_ptr(object.transformation.projection));
		const glm::vec3& camera_pos = camera.pos();
		glUniform3f(glGetUniformLocation(current_shader, "view_pos"), camera_pos.x, camera_pos.y, camera_pos.z);
		//send lighting data to shader
		for(std::vector<Lighting*>::const_iterator lyt=lightings->begin(); lyt!=lightings->end(); ++lyt){
			(*lyt)->sendInfoToShader(current_shader);
		}
		//render
		glBindVertexArray(object.ri.VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object.ri.EBO);
		glDrawElements(object.ri.mode, object.ri.indices_count, GL_UNSIGNED_INT, 0);
	}
}
