#ifndef GAME_H
#define GAME_H
//-------------------------------------------------------------
#include "object.h"
#include "camera.h"

#include <vector>


class Game{
	private:
		static std::vector<Object*> objects;
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
