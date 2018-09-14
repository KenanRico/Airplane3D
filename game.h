#ifndef GAME_H
#define GAME_H
//-------------------------------------------------------------
#include "object.h"
#include "camera.h"
#include "gpubuffer.h"

#include <vector>
#include <map>


class Game{
	protected:
		static std::map<const char*, GPUbuffer*> gpu_buffers;
		static std::vector<Object*> planets;
		static std::vector<Camera*> cameras;
		static std::vector<Camera*>::const_iterator current_camera;

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
