#ifndef PHYSICS_HANDLER_H
#define PHYSICS_HANDLER_H
//-------------------------------------------------------

#include <vector>

class Object;

class PhysicsHandler{
	private:
		static float gravity;
		static std::vector<Object*> const * object_pool;
	private:
		Object* client_object;

	public:
		PhysicsHandler(Object*);
		~PhysicsHandler();
	private:
		PhysicsHandler() = delete;
		PhysicsHandler(const PhysicsHandler&) = delete;
		PhysicsHandler& operator=(const PhysicsHandler&) = delete;

	public:
		static void initGlobal(std::vector<Object*> const *);
	public:
		void handleAll();
};

//-------------------------------------------------------
#endif
