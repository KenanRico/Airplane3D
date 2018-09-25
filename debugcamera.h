#ifndef DEBUG_CAMERA_H
#define DEBUG_CAMERA_H
//-------------------------------------------------------------------------------

#include "camera.h"

#include <glm/glm.hpp>


class DebugCamera : public Camera{
	public:
		DebugCamera(float, float, const glm::vec3&, const glm::vec3&);
		DebugCamera(const DebugCamera&);
		~DebugCamera();
	private:
		DebugCamera() = delete;
		DebugCamera& operator=(const DebugCamera&) = delete;

	public:
		void update(float);
};


//-------------------------------------------------------------------------------
#endif
