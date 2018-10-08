#ifndef EVENT_HANDLER_H
#define EVEnT_HANDLER_H
//------------------------------------------------------------------
#include <glfw/glfw3.h>


class EventHandler{
	public:
		enum KEYS { ESC=0, W=1, A=2, S=3, D=4, SPACE=5, LSHIFT=6, C=7, LCTRL=8, J=9 };
		enum BUTTONS { LEFT=0, MID=1, RIGHT=2 };
		enum COMPONENTS { X=0, Y=1 };
	private:
		static struct Keyboard{
			int key_count;
			bool* click;
			bool* held;
		} keyboard;
		static struct Mouse{
			float cursor_position[2];
			float click_position[3][2];
			float cursor_offset[2];
			bool click[3];
			bool held[3];
		} mouse;
	private:
		EventHandler() = delete;
		~EventHandler() = delete;
		EventHandler(const EventHandler&) = delete;
		EventHandler& operator=(const EventHandler&) = delete;
	public:
		static void init();
		static void update();
		static bool keyClicked(int);
		static bool keyDown(int);
		static float cursorPosition(int);
		static float clickPosition(int, int);
		static float cursorOffset(int);
		static bool mouseClicked(int);
		static bool mouseHeldDown(int);
		static void end();
	private:
		static void keyboardCallback(GLFWwindow*, int, int, int, int);
		static void mousePosCallback(GLFWwindow*, double, double);
		static void mouseClickCallback(GLFWwindow*, int, int, int);
};

extern GLFWwindow* window;

//------------------------------------------------------------------
#endif
