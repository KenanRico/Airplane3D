#include "game.h"
#include "object.h"
#include "shader.h"
#include "camera.h"

#include <vector>

#include <glm/glm.hpp>


std::vector<Object*> Game::objects;
std::vector<Camera*> Game::cameras;
std::vector<Camera*>::const_iterator Game::current_camera = cameras.begin();


void Game::init(){

	//create a triangle
	float triangle[] = {0.0f,0.6f,0.0f, -0.5f,-0.3f,0.0f, 0.5f,-0.3f,0.0f};
	unsigned int t_indices[] = {0, 1, 2};
	unsigned int s0 = Shader::initShaders("shaders/VShader.glsl", "shaders/FShader.glsl");
	objects.push_back(
		new Object(
			triangle, sizeof(triangle), t_indices, sizeof(t_indices), sizeof(t_indices)/sizeof(unsigned int), s0, glm::vec3(2.0f, 0.0f, 0.0f)
		)
	);
	//create a rectangle
	float rectangle[] = {-0.3f,0.4f,0.0f, 0.3f,0.4f,0.0f, -0.3f,-0.4f,0.0f, 0.3f,-0.4,0.0f};
	unsigned int r_indices[] = {0, 1, 2, 1, 2, 3};
	unsigned int s1 = Shader::initShaders("shaders/VShader.glsl", "shaders/FShader.glsl");
	objects.push_back(
		new Object(
			rectangle, sizeof(rectangle), r_indices, sizeof(r_indices), sizeof(r_indices)/sizeof(unsigned int), s1, glm::vec3(0.0f, 0.0f, 1.0f)
		)
	);

	//create a camera
	cameras.push_back(new Camera(55.0f, 150.0f, 0.01f, 0.1f, glm::vec3(-15.0f, 0.0f, 1.0f)));
	current_camera = cameras.begin();
}

void Game::update(){
	for(std::vector<Object*>::iterator o=objects.begin(); o!=objects.end(); ++o){
		(*o)->update(**current_camera);
	}
	(*current_camera)->update();
}

void Game::render(){
	for(std::vector<Object*>::iterator o=objects.begin(); o!=objects.end(); ++o){
		(*o)->render();
	}
}

void Game::free(){
	for(std::vector<Object*>::iterator o=objects.begin(); o!=objects.end(); ++o){
		delete *o;
	}
	for(std::vector<Camera*>::iterator c=cameras.begin(); c!=cameras.end(); ++c){
		delete *c;
	}
}
