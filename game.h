#ifndef GAME_H
#define GAME_H
//-------------------------------------------------------------
#include "object.h"
#include "camera.h"
#include "gpubuffer.h"
#include "vehicle.h"
#include "debugcamera.h"

#include <string>
#include <vector>
#include <map>


class Game{
	protected:
		static std::map<std::string, GPUbuffer*> gpu_buffers;
		static std::map<std::string, unsigned int> shader_pool;
		static std::vector<Object*> entity_pool;
		static std::vector<Object*> controllables;
		static Vehicle* vehicle;

	private:
		Game() = delete;
		~Game() = delete;
		Game(const Game&) = delete;
		Game& operator=(const Game&) = delete;

	public:
		static void init();
		static void runPipeline();
		static void render();
		static void free();
};

//-------------------------------------------------------------
#endif
