#ifndef LOGGER_H
#define LOGGER_H
//-------------------------------------------------------------
#include <string>


namespace Logger{
	enum MsgType { L_INFO, L_DEBUG, L_ERROR };
	//print to console
	void toConsole(MsgType, const char*);
	void toConsole(MsgType, const std::string&);
	//print to file
	void toFile(MsgType, const char*);
	void toFile(MsgType, const std::string&);
	
};

//-------------------------------------------------------------
#endif
