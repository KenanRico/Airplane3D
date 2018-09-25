#include "eventhandler.h"

#include <glfw/glfw3.h>



struct EventHandler::Keyboard EventHandler::keyboard = (struct EventHandler::Keyboard){ 9, (bool*)0 , (bool*)0 };
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
	if(key==GLFW_KEY_ESCAPE && action==GLFW_PRESS){
		if(!keyboard.held[ESC]){
			keyboard.click[ESC] = true;
			keyboard.held[ESC] = true;
		}
	}else if(key==GLFW_KEY_ESCAPE && action==GLFW_RELEASE){
		keyboard.held[ESC] = false;
	}

	if(key==GLFW_KEY_W && action==GLFW_PRESS){
		if(!keyboard.held[W]){
			keyboard.click[W] = true;
			keyboard.held[W] = true;
		}
	}else if(key==GLFW_KEY_W && action==GLFW_RELEASE){
		keyboard.held[W] = false;
	}

	if(key==GLFW_KEY_S && action==GLFW_PRESS){
		if(!keyboard.held[S]){
			keyboard.click[S] = true;
			keyboard.held[S] = true;
		}
	}else if(key==GLFW_KEY_S && action==GLFW_RELEASE){
		keyboard.held[S] = false;
	}

	if(key==GLFW_KEY_A && action==GLFW_PRESS){
		if(!keyboard.held[A]){
			keyboard.click[A] = true;
			keyboard.held[A] = true;
		}
	}else if(key==GLFW_KEY_A && action==GLFW_RELEASE){
		keyboard.held[A] = false;
	}

	if(key==GLFW_KEY_D && action==GLFW_PRESS){
		if(!keyboard.held[D]){
			keyboard.click[D] = true;
			keyboard.held[D] = true;
		}
	}else if(key==GLFW_KEY_D && action==GLFW_RELEASE){
		keyboard.held[D] = false;
	}

	if(key==GLFW_KEY_SPACE && action==GLFW_PRESS){
		if(!keyboard.held[SPACE]){
			keyboard.click[SPACE] = true;
			keyboard.held[SPACE] = true;
		}
	}else if(key==GLFW_KEY_SPACE && action==GLFW_RELEASE){
		keyboard.held[SPACE] = false;
	}

	if(key==GLFW_KEY_LEFT_SHIFT && action==GLFW_PRESS){
		if(!keyboard.held[LSHIFT]){
			keyboard.click[LSHIFT] = true;
			keyboard.held[LSHIFT] = true;
		}
	}else if(key==GLFW_KEY_LEFT_SHIFT && action==GLFW_RELEASE){
		keyboard.held[LSHIFT] = false;
	}

	if(key==GLFW_KEY_C && action==GLFW_PRESS){
		if(!keyboard.held[C]){
			keyboard.click[C] = true;
			keyboard.held[C] = true;
		}
	}else if(key==GLFW_KEY_C && action==GLFW_RELEASE){
		keyboard.held[C] = false;
	}

	if(key==GLFW_KEY_LEFT_CONTROL && action==GLFW_PRESS){
		if(!keyboard.held[LCTRL]){
			keyboard.click[LCTRL] = true;
			keyboard.held[LCTRL] = true;
		}
	}else if(key==GLFW_KEY_LEFT_CONTROL && action==GLFW_RELEASE){
		keyboard.held[LCTRL] = false;
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
