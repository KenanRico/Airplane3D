#include "eventhandler.h"

#include <vector>

#include <glfw/glfw3.h>



struct EventHandler::Keyboard EventHandler::keyboard = (struct EventHandler::Keyboard){
	17,
	std::vector<int>{
		GLFW_KEY_ESCAPE,
		GLFW_KEY_W,
		GLFW_KEY_A,
		GLFW_KEY_S,
		GLFW_KEY_D,
		GLFW_KEY_SPACE,
		GLFW_KEY_LEFT_SHIFT,
		GLFW_KEY_C,
		GLFW_KEY_LEFT_CONTROL,
		GLFW_KEY_J,
		GLFW_KEY_1,
		GLFW_KEY_2,
		GLFW_KEY_3,
		GLFW_KEY_G,
		GLFW_KEY_P,
		GLFW_KEY_L,
		GLFW_KEY_H
	},
	(bool*)0,
	(bool*)0 
};
struct EventHandler::Mouse EventHandler::mouse = (struct EventHandler::Mouse){
	{ 0.0f, 0.0f },
	{ {0.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f} },
	{ 0.0f, 0.0f },
	{ false, false, false },
	{ false, false, false }
};


void EventHandler::init(){
	keyboard.click = new bool[keyboard.key_count]();
	keyboard.held = new bool[keyboard.key_count]();
	glfwSetKeyCallback(window, keyboardCallback);
	glfwSetCursorPosCallback(window, mousePosCallback);
	glfwSetMouseButtonCallback(window, mouseClickCallback);
}

void EventHandler::update(){
	mouse.cursor_offset[X] = 0.0f;
	mouse.cursor_offset[Y] = 0.0f;
	mouse.click[LEFT] = false;
	mouse.click[MID] = false;
	mouse.click[RIGHT] = false;
	for(int i=0; i<keyboard.key_count; ++i){
		keyboard.click[i] = false;
	}
	glfwPollEvents();
}

//following are 7 functions to retrieve user input
bool EventHandler::keyClicked(int key){
	return keyboard.click[key];
}
bool EventHandler::keyDown(int key){
	return keyboard.held[key];
}
float EventHandler::cursorPosition(int component){
	return mouse.cursor_position[component];
}
float EventHandler::clickPosition(int button, int component){
	return mouse.click_position[button][component];
}
float EventHandler::cursorOffset(int component){
	return mouse.cursor_offset[component];
}
bool EventHandler::mouseClicked(int button){
	return mouse.click[button];
}
bool EventHandler::mouseHeldDown(int button){
	return mouse.held[button];
}



void EventHandler::end(){
	delete[] keyboard.click;
	delete[] keyboard.held;
}

//callback for key press
void EventHandler::keyboardCallback(GLFWwindow* w, int key, int scancode, int action, int mods){
	for(int i=0; i<keyboard.key_count; ++i){
		if(key==keyboard.keys[i] && action==GLFW_PRESS){
			if(!keyboard.held[i]){
				keyboard.click[i] = true;
				keyboard.held[i] = true;
			}
		}else if(key==keyboard.keys[i] && action==GLFW_RELEASE){
			keyboard.held[i] = false;
		}
	}
}

//callback for cursor position
void EventHandler::mousePosCallback(GLFWwindow* w, double xpos, double ypos){
	mouse.cursor_offset[X] = (float)xpos - mouse.cursor_position[X];
	mouse.cursor_offset[Y] = (float)ypos - mouse.cursor_position[Y];
	mouse.cursor_position[X] = (float)xpos;
	mouse.cursor_position[Y] = (float)ypos;
}

//callback for mouse button click
void EventHandler::mouseClickCallback(GLFWwindow* w, int button, int action, int mods){
	if(button==GLFW_MOUSE_BUTTON_LEFT){
		if(action==GLFW_PRESS){
			if(!mouse.held[LEFT]){
				mouse.click[LEFT] = true;
				mouse.held[LEFT] = true;
			}
		}else if(action==GLFW_RELEASE){
			mouse.held[LEFT] = false;
		}
	}
	if(button==GLFW_MOUSE_BUTTON_MIDDLE){
		if(action==GLFW_PRESS){
			if(!mouse.held[MID]){
				mouse.click[MID] = true;
				mouse.held[MID] = true;
			}
		}else if(action==GLFW_RELEASE){
			mouse.held[MID] = false;
		}
	}
	if(button==GLFW_MOUSE_BUTTON_RIGHT){
		if(action==GLFW_PRESS){
			if(!mouse.held[RIGHT]){
				mouse.click[RIGHT] = true;
				mouse.held[RIGHT] = true;
			}
		}else if(action==GLFW_RELEASE){
			mouse.held[RIGHT] = false;
		}
	}
}
