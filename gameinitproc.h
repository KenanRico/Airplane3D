#ifndef GAME_INIT_PROC
#define GAME_INIT_PROC
//----------------------------------------------------------------------

#include "gpubuffer.h"
#include "object.h"
#include "camera.h"
#include "stationaryplanet.h"
#include "revolvingplanet.h"
#include "lighting.h"
#include "shadow.h"

#include <vector>
#include <map>


namespace GameInitProc{
	void createGPUBuffers(std::map<std::string, GPUbuffer*>*);
	void generateModels(std::map<std::string, Model>*, const std::map<std::string, GPUbuffer*>&);
	void createShaders(std::map<std::string, unsigned int>*);
	void loadObjects(
		std::vector<Object*>*,
		const std::map<std::string, GPUbuffer*>&,
		const std::map<std::string, unsigned int>&,
		const std::map<std::string, Model>&
	);
	void createLightings(std::vector<Lighting*>*, const std::vector<Object*>&);
	void createShadows(std::vector<Shadow*>*, const std::vector<Lighting*>&);
};

//----------------------------------------------------------------------
#endif
