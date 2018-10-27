#include <glad/glad.h>

#include "pipeline.h"
#include "object.h"
#include "shader.h"

#include <vector>



void Pipeline::Renderer::renderEntities(std::vector<Object*> const * entities){
	std::vector<Object*>::const_iterator end = entities->end();
	for(std::vector<Object*>::const_iterator obj=entities->begin(); obj!=end; ++obj){
		Object* object = *obj;
		Shader::useShader(object->shader);
		glBindVertexArray(object->ri.VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object->ri.EBO);
		glDrawElements(object->ri.mode, object->ri.indices_count, GL_UNSIGNED_INT, 0);
	}
}
