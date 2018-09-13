#include "logger.h"

#include <iostream>
#include <string>


void Logger::toConsole(MsgType mt, const char* msg){
	switch(mt){
		case L_INFO:
			std::cout<<"INFO: "<<msg<<"\n";
			break;
		case L_DEBUG:
			std::cout<<"DEBUG: "<<msg<<"\n";
			break;
		case L_ERROR:
			std::cout<<"ERROR: "<<msg<<"\n";
			break;
		default: break;
	}
}

void Logger::toConsole(MsgType mt, const std::string& msg){
	switch(mt){
		case L_INFO:
			std::cout<<"INFO: "<<msg<<"\n";
			break;
		case L_DEBUG:
			std::cout<<"DEBUG: "<<msg<<"\n";
			break;
		case L_ERROR:
			std::cout<<"ERROR: "<<msg<<"\n";
			break;
		default: break;
	}
}

void Logger::toFile(MsgType mt, const char* msg){
	//implement this
}

void Logger::toFile(MsgType mt, const std::string& msg){
	//implement this
}
