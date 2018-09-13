#ifndef GAME_SYSTEM_H
#define GAME_SYSTEM_H
//-------------------------------------------------------------
#include <string>

#include <GLFW/glfw3.h>


class GameSystem{
	private:
		enum State {RUN, STOP};
	private:
		static int window_width;
		static int window_height;
		static State state;
		static float time;
		static float delta_time;
		static int FPS;
	private:
		GameSystem() = delete;
		~GameSystem() = delete;
		GameSystem(const GameSystem&) = delete;
		GameSystem& operator=(const GameSystem&) = delete;
	public:
		static int windowW();
		static int windowH();
		static bool isRunning();
		static float getTime();
		static float getDeltaTime();
		static int getFPS();
		static void update();
	public:
		static std::string to_string(int);
};

extern GLFWwindow* window;
//-------------------------------------------------------------
#endif
