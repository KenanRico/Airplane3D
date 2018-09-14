#include <glad/glad.h>

#include "stationaryplanet.h"
#include "nonplayableobject.h"
#include "shader.h"
#include "camera.h"
#include "gamesystem.h"
#include "gpubuffer.h"
#include "logger.h"

#include <math.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>



float StationaryPlanet::scale = 20.0f;

/*
StationaryPlanet::StationaryPlanet(
	float* v, unsigned int v_s,
	unsigned int* i, unsigned int i_s, unsigned int i_c,
	unsigned int s,
	const glm::vec3& p,
	float si,
	float rs, const glm::vec3& ro
): NonPlayableObject(v, v_s, i, i_s, i_c, s, p, si*scale), rotation((struct Rotation){rs, ro}){
	//nothing here
}
*/
StationaryPlanet::StationaryPlanet(
	GPUbuffer const * buffers,
	unsigned int s,
	const glm::vec3& p,
	float si,
	float rs, const glm::vec3& ro
): NonPlayableObject(buffers, s, p, si*scale), rotation((struct Rotation){rs, ro}){
	//nothing here
}

StationaryPlanet::~StationaryPlanet(){
	//nothing here
}

void StationaryPlanet::update(const Camera& camera){
	
	//position.current.y += 0.01f;
	//create references for transformation matrices
	glm::mat4& model = transformation.model;
	glm::mat4& view = transformation.view;
	glm::mat4& projection = transformation.projection;

	/*update transformations (T*R*S*vertex)*/
	//model
	model = glm::translate(model, position.current-position.last);
	model = glm::rotate(model, glm::radians(rotation.speed), rotation.orientation);
	model = glm::scale(model, size.current/size.last);
	//view
	view = glm::lookAt(camera.pos(), camera.lensPos(), camera.straightUp());
	//projection
	projection = glm::perspective(glm::radians(camera.fov()), (float)GameSystem::windowW()/(float)GameSystem::windowH(), 0.1f, camera.renderDistance());
	
	//synchronize positioning and sizing
	position.last = position.current;
	size.last = size.current;

	//apply transformations into shader
	Shader::useShader(shader);
	glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

}

void StationaryPlanet::render() const{
	Shader::useShader(shader);
	glBindVertexArray(ri.VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ri.EBO);
	glDrawElements(ri.mode, ri.indices_count, GL_UNSIGNED_INT, 0);
}
