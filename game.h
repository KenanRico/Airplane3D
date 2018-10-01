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
		static std::vector<Object*> planets;
		static Vehicle* vehicle;
		static Camera debug_camera;

		static Camera const* current_camera;

	private:
		Game() = delete;
		~Game() = delete;
		Game(const Game&) = delete;
		Game& operator=(const Game&) = delete;

	public:
		static void init();
		static void update();
		static void render();
		static void free();
};

//-------------------------------------------------------------
#endif
