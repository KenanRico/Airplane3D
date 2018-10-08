#include "gamesystem.h"
#include "eventhandler.h"

#include <stdexcept>
#include <string>
#include <sstream>
#include <iostream>

#include <GLFW/glfw3.h>

int GameSystem::window_width = 800;
int GameSystem::window_height = 600;
GameSystem::State GameSystem::state = GameSystem::RUN;
float GameSystem::time = glfwGetTime();
float GameSystem::delta_time = 0.0f;
int GameSystem::FPS = 0;


int GameSystem::windowW(){
	return window_width;
}

int GameSystem::windowH(){
	return window_height;
}

bool GameSystem::isRunning(){
	return state==RUN;
}

float GameSystem::getTime(){
	return time;
}

float GameSystem::getDeltaTime(){
	return delta_time;
}

int GameSystem::getFPS(){
	return FPS;
}


void GameSystem::update(){
	//update game state
	if(EventHandler::keyClicked(EventHandler::ESC)){
		state = STOP;
	}
	//update time
	float new_time = glfwGetTime();
	delta_time = new_time - time;
	time = new_time;
	//update FPS
	FPS = (int)(1.0f/delta_time);
	//query window size
	glfwGetWindowSize(window, &window_width, &window_height);
}


std::string GameSystem::to_string(int num){
	std::string result("");
	std::stringstream ss(result);
	ss<<num;
	return ss.str();
}
