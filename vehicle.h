#ifndef VEHICLE_H
#define VEHICLE_H
//---------------------------------------------------------------------

#include "camera.h"
#include "object.h"
#include "gpubuffer.h"

#include <glm/glm.hpp>


class Vehicle : public Object{
	private:
		enum CameraID {FP=0, TP=1, rear=2};
	private:
		struct Velocity{
			glm::vec3 direction;
			float magnitude;
			float max;
			float min;
		};
		struct Control{
			float max_roll_angle;
			float pitch_sensitivity;
			float roll_sensitivity;
		};
		struct Cameras{
			Camera views[3];
			Camera* current;
		};
	private:
		struct Velocity velocity;
		struct Control control;
		struct Cameras cameras;

	public:
		Vehicle(GPUbuffer const *, unsigned int, const glm::vec3&, float, const glm::vec3&, float, float, float, float, float, float);
		~Vehicle();
	private:
		Vehicle() = delete;
		Vehicle(const Vehicle&) = delete;
		Vehicle& operator=(const Vehicle&) = delete;

	public:
		void update(const Camera&) override;
		void render() const;
		const Camera& viewingCamera() const;
};

//---------------------------------------------------------------------
#endif
