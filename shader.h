#ifndef SHADER_H
#define SHADER_H
//-------------------------------------------------------------
#include <string>


namespace Shader{
	unsigned int initShaders(const char*, const char*);
	unsigned int initShaders(const std::string&, const std::string&);
	void useShader(unsigned int);
};

//-------------------------------------------------------------
#endif
