#ifndef GAME_INIT_PROC
#define GAME_INIT_PROC
//----------------------------------------------------------------------

#include "gpubuffer.h"
#include "object.h"
#include "camera.h"
#include "stationaryplanet.h"
#include "revolvingplanet.h"

#include <vector>
#include <map>


namespace GameInitProc{
	void createGPUBuffers(std::map<std::string, GPUbuffer*>*);
	void loadObjects(std::vector<Object*>*, const std::map<std::string, GPUbuffer*>&);
};

//----------------------------------------------------------------------
#endif
