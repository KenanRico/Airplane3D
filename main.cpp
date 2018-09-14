#include <glad/glad.h>

#include "logger.h"
#include "gamesystem.h"
#include "game.h"
#include "eventhandler.h"

#include <iostream>
#include <stdexcept>
#include <string>

#include <GLFW/glfw3.h>



GLFWwindow* window = nullptr;
GLfloat game_time = 0.0f;
void framebufferSizeCallback(GLFWwindow* win, int w, int h){
	glViewport(0, 0, w, h);
}


void initGL();
void initGame();
void loop();
void update();
void render();
void endGame();
void endGL();


int main(){
	try{
		initGL();
		initGame();
		loop();
		endGame();
		endGL();
	}catch(const std::exception& Err){
		std::cout<<"EXCEPT: "<<Err.what()<<"\n";
	}
    return 0;
}


void initGL(){
	//init GLFW
	if(!glfwInit()){
		throw std::runtime_error("EXCEPT: could not start GLFW");
	}

	//config GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//create window and make it current context
	if((window = glfwCreateWindow(GameSystem::windowW(), GameSystem::windowH(), "Spaceship", (GLFWmonitor*)0, (GLFWwindow*)0)) != nullptr){
		glfwMakeContextCurrent(window);
	}else{
		throw std::runtime_error("could not create GLFW window");
	}

	//init GLAD
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		throw std::runtime_error("could not start GLAD");
	}

	//set input mode
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//set viewport
	int window_w = 0;
	int window_h = 0;
	glfwGetWindowSize(window, &window_w, &window_h);
	glViewport(0, 0, window_w, window_h);

	//set framebuffersize callback
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	//config depth buffer
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	//config stencil buffer (app dependent)
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	//enable blending (app dependent)
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//all done, print GL version
	Logger::toConsole(Logger::L_INFO, (const char*)glGetString(GL_VERSION));
}

void initGame(){

	Game::init();
	EventHandler::init();
	
}

void loop(){
	while(GameSystem::isRunning()){
		update();
		render();
	}
}
void update(){
	GameSystem::update();
	EventHandler::update();
	Game::update();
}
void render(){
	glClearColor(0.001f, 0.05f, 0.10f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	Game::render();
	glBindVertexArray(0);
	glfwSwapBuffers(window);
}

void endGame(){
	//free cube buffer
	Game::free();
	EventHandler::end();
}

void endGL(){
	//deallocate GL resources, end GL related processes
	glfwTerminate();
	delete window;
}
